////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "PBX.hpp"
#include "PBXInfoWriter.hpp"
#include <yq/core/DelayInit.hpp>

YQ_OBJECT_IMPLEMENT(yq::post::PBX)

namespace yq::post {

    PBXInfo::PBXInfo(std::string_view zName, const ObjectInfo& base, const std::source_location& sl) :
        ObjectInfo(zName, base, sl)
    {
        //set(Flag::PBX);
    }

    struct PBX::Entry {
        unsigned            depth;
        const PostInfo*     info    = nullptr;
        const PBXDispatch*  fn      = nullptr;
    };

    PBX::PBX(const Param&p, std::initializer_list<R> classFlags) : Dispatcher(p, classFlags)
    {
        add_role(R::Listener);
    }
    
    PBX::~PBX()
    {
        for(const PBXDispatch* fn : m_custom){
            delete fn;
        }
        m_custom.clear();
    }
    
    void PBX::_add(entry_vector_t& ranked, const PBXDispatch*fn, unsigned depth)
    {
        const PBXInfo*  pbx = fn->pbx_info();
        if(!pbx)
            return ;
        if(!metaInfo().is_derived(*pbx))   // reject if not related to this
            return ;
            
        const PostInfo* ppi = fn->post_info();
        if(!ppi)
            ppi = &meta<Post>();
        ranked.push_back({depth, ppi, fn});
        for(const ObjectInfo* derv : ppi->deriveds(true).all){
            const PostInfo* ppd = static_cast<const PostInfo*>(derv);   // should *NEVER* be wrong given the inheritance
            if(!ppd->is_abstract()){
                ranked.push_back({depth, ppd, fn});
            }
        }
    }
    
    void PBX::_add(entry_vector_t& ranked, const PBXInfo& info, unsigned depth)
    {
        for(const PBXDispatch*fn : info.m_dispatches)
            _add(ranked, fn, depth);
        const ObjectInfo* p   = info.base();
        if(p && p->is_base(meta<Post>())){
            _add(ranked, *static_cast<const PBXInfo*>(p), depth+1);
        }
    }

    void    PBX::_build()
    {
        entry_vector_t   ranked;
        for(const PBXDispatch* fn : m_custom)
            _add(ranked, fn, 0);
        _add(ranked, metaInfo(), 1);
        
        if(!ranked.empty()){
            
            // sort into reverse order... depth 0 is last
            std::stable_sort(ranked.begin(), ranked.end(), 
                [](const Entry& a, const Entry& b) -> bool {
                    if(a.info != b.info)
                        return a.info < b.info;
                    return a.depth < b.depth;
                }
            );
            
            m_dispatch.resize(ranked.size(), nullptr);
            
            const PostInfo* pi  = nullptr;
            size_t          nC  = 0;
            
            for(size_t n=0;n<ranked.size();++n){
                const Entry& r = ranked[n];
                if(pi != r.info){   // edge detection
                    if(pi){
                        m_lookup[pi]    = std::span(&m_dispatch[nC], n-nC);
                    }
                    pi  = r.info;
                }
                
                m_dispatch[n]   = r.fn;
            }
            
            m_lookup[pi] = std::span(&m_dispatch[nC], ranked.size()-nC);
        }
        
        m_built = true;
    }

    bool    PBX::_execute(const PBXDispatch& pfn, const PostCPtr& pp)
    {
        if(pfn.m_trigger){
            FilterResult    chk = pfn.m_trigger->check(*pp);
            if(auto p = std::get_if<bool>(&chk)){
                if(!*p)
                    return false;
            } else {
                if(pfn.m_trigger->mismatch() == MismatchPolicy::Reject)
                    return false;
                if(pfn.m_mismatch == MismatchPolicy::Reject)
                    return false;
            }
        }
        
        return pfn.dispatch(*this, pp);
    }

    void    PBX::receive(const PostCPtr& pp) 
    {
        if(!m_built){
            _build();
        }
        
        if(!pp)     // reject null pointers
            return;
 
        auto itr = m_lookup.find(&pp->metaInfo());
        if(itr == m_lookup.end())
            return ;
        
        for(const PBXDispatch* pfn : itr->second){
            if(_execute(*pfn, pp))
                break;
        }
    }

    static void reg_pbx()
    {
        auto w = writer<PBX>();
        w.description("Abstract PBX Object");
    }
    
    YQ_INVOKE(reg_pbx();)
}

