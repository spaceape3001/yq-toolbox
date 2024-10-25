////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Filter.hpp"
#include <yq/core/DelayInit.hpp>
#include "FilterInfoWriter.hpp"

YQ_OBJECT_IMPLEMENT(yq::post::Filter)

namespace yq::post {
    FilterInfo::FilterInfo(std::string_view zName, const ObjectInfo& base, const std::source_location& sl) :
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

    Filter::Filter(const Param& p) : m_name(p.name)
    {
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

    
    YQ_INVOKE(Filter::init_info();)
}
