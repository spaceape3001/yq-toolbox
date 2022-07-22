////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <basic/meta/Global.hpp>
#include <basic/DelayInit.hpp>
#include <basic/meta/ReservedIDs.hpp>

namespace yq {
    GlobalInfo&     GlobalInfo::instance()
    {
        static GlobalInfo*  s_ret   = new GlobalInfo;
        return *s_ret;
    }

    GlobalInfo::GlobalInfo(const std::source_location& sl) : CompoundInfo("Global", sl, nullptr, MC_Global)
    {
    }

    void     GlobalInfo::sweep_impl() 
    {   
        CompoundInfo::sweep_impl();
        gather(m_properties);
        gather(m_methods);
        for(const Meta* m : m_methods.all)
            const_cast<Meta*>(m) -> m_flags |= GLOBAL | STATIC;
        for(const Meta* m : m_properties.all)
            const_cast<Meta*>(m) -> m_flags |= GLOBAL | STATIC;
    }
    
    
    const GlobalInfo&        InfoBinder<Global>::bind()
    {
        return GlobalInfo::instance();
    }
    
    GlobalInfo&       InfoBinder<Global>::edit()
    {
        return GlobalInfo::instance();
    }
}

YQ_INVOKE(
    yq::GlobalInfo::instance();
);
