////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Filter.hpp"
#include "FilterInfoWriter.hpp"

YQ_OBJECT_IMPLEMENT(yq::post::Filter)

namespace yq::post {
    FilterInfo::FilterInfo(std::string_view zName, ObjectInfo& base, const std::source_location& sl) :
        ObjectInfo(zName, base, sl)
    {
        set(Flag::POST);
        set(Flag::FILTER);
    }
    
    void Filter::init_info()
    {
        static std::atomic_flag     seen;
        if(seen.test_and_set())
            return ;
            
        auto w = writer<Filter>();
        w.description("Abstract Post Filter");
        w.property("name", &Filter::name_get).setter(&Filter::name_set).description("Filter name");
    }

    Filter::Filter(const Param& cfg) : m_name(cfg.name)
    {
        if(auto p = std::get_if<bool>(&cfg.mismatches)){
            if(*p){
                m_mismatch    = ALL;
            }
        }
        
        if(auto p = std::get_if<MismatchPolicy>(&cfg.mismatches)){
            if(*p == MismatchPolicy::Accept){
                m_mismatch    = ALL;
            }
        }
        
        if(auto p = std::get_if<MismatchFlags>(&cfg.mismatches)){
            m_mismatch    = *p;
        }
    }
    
    Filter::~Filter()
    {
    }
    
    std::string_view    Filter::name() const
    {
        if(!m_name.empty())
            return m_name;
        return metaInfo().name();
    }

    void    Filter::name(std::string_view v)
    {
        m_name  = std::string(v);
    }

    std::string         Filter::name_get() const
    {
        return std::string(name());
    }
    
    //! Setter for the name property
    void                Filter::name_set(const std::string&v)
    {
        m_name  = v;
    }

    FilterResult    Filter::check(const Dispatcher&src, const Dispatcher&tgt, const Post&pp) const
    {
        return metaInfo().accept(*this, src, tgt, pp);
    }

    bool    Filter::passed(const Dispatcher& src, const Dispatcher& tgt, const Post& pp) const
    {
        FilterResult    chk  = check(src, tgt, pp);
        if(auto p = std::get_if<bool>(&chk))
            return *p;
        if(auto p = std::get_if<MismatchFlags>(&chk))
            return (*p - m_mismatch) != MismatchFlags();
        return false;   // should never hit here
    }
}
