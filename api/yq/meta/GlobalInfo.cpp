////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/meta/GlobalInfo.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/meta/ReservedIDs.hpp>

namespace yq {
    GlobalInfo&     GlobalInfo::instance()
    {
        static GlobalInfo*  s_ret   = new GlobalInfo;
        return *s_ret;
    }

    GlobalInfo::GlobalInfo(std::string_view name, const std::source_location& sl) : CompoundMeta(name, sl, nullptr, MC_Global)
    {
        set(Flag::GLOBAL);
    }

    void     GlobalInfo::sweep_impl() 
    {   
        CompoundMeta::sweep_impl();
        gather(m_properties);
        gather(m_methods);
        for(const Meta* m : m_methods.all)
            const_cast<Meta*>(m) -> set({ Flag::GLOBAL,  Flag::STATIC });
        for(const Meta* m : m_properties.all)
            const_cast<Meta*>(m) -> set({ Flag::GLOBAL, Flag::STATIC });
    }
    
    
    const GlobalInfo&        InfoBinder<Global>::bind()
    {
        return GlobalInfo::instance();
    }
    
    GlobalInfo&       InfoBinder<Global>::edit()
    {
        return GlobalInfo::instance();
    }

    GlobalInfo*  to_global(Meta*m)
    {
        return (m && m->is_global() && m->is_compound()) ? static_cast<GlobalInfo*>(m) : nullptr;
    }
    
    const GlobalInfo*  to_global(const Meta*m)
    {
        return (m && m->is_global() && m->is_compound()) ? static_cast<const GlobalInfo*>(m) : nullptr;
    }
}

YQ_INVOKE(
    yq::GlobalInfo::instance();
);
