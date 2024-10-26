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
    
    PBX::PBX(const Param&p, std::initializer_list<R> classFlags) : Dispatcher(p, classFlags)
    {
        add_role(R::Listener);
    }
    
    PBX::~PBX()
    {
    }
    
    void PBX::_add(rank_vector_t& ranked, const PBXDispatch*fn, unsigned depth)
    {
        if(!metaInfo().is_derived(fn->pbx_info()))   // reject if not related to this
            return ;
            
        const PostInfo& ppi = fn->post_info();
        ranked.push_back({depth, &ppi, fn});
        for(const ObjectInfo* derv : ppi.deriveds(true).all){
            const PostInfo* ppd = static_cast<const PostInfo*>(derv);   // should *NEVER* be wrong given the inheritance
            ranked.push_back({depth, ppd, fn});
        }
    }
    
    void PBX::_add(rank_vector_t& ranked, const PBXInfo& info, unsigned depth)
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
        rank_vector_t   ranked;
        for(const PBXDispatch* fn : m_custom)
            _add(ranked, fn, 0);
        _add(ranked, metaInfo(), 1);
        
        // sort into reverse order... depth 0 is last
        std::stable_sort(ranked.begin(), ranked.end(), 
            [](const Rank& a, const Rank& b) -> bool {
                return a.depth > b.depth;
            }
        );
        
        for(const Rank& r : ranked){
            m_dispatch[r.info]  = r.fn;
        }
        
        m_built = true;
    }

    void    PBX::receive(const PostCPtr& pp) 
    {
        if(!m_built){
            _build();
        }
        
        if(!pp)     // reject null pointers
            return;
            
        bool    f   = false;
        auto itr = m_dispatch.find(&pp->metaInfo());
        if(itr != m_dispatch.end()){
            f       = itr->second -> handle(this, pp);
        }
        
        if(!f){
            handle(pp);
        }
    }

    static void reg_pbx()
    {
        auto w = writer<PBX>();
        w.description("Abstract PBX Object");
    }
    
    YQ_INVOKE(reg_pbx();)
}

