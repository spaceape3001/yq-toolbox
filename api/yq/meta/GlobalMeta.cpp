////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/meta/GlobalMeta.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/meta/ReservedIDs.hpp>

namespace yq {
    GlobalMeta&     GlobalMeta::instance()
    {
        static GlobalMeta*  s_ret   = new GlobalMeta;
        return *s_ret;
    }

    GlobalMeta::GlobalMeta(std::string_view name, const std::source_location& sl) : CompoundMeta(name, sl, nullptr, MC_Global)
    {
        set(Flag::GLOBAL);
    }

    void     GlobalMeta::sweep_impl() 
    {   
        CompoundMeta::sweep_impl();
        gather(m_properties);
        gather(m_methods);
        for(const Meta* m : m_methods.all)
            const_cast<Meta*>(m) -> set({ Flag::GLOBAL,  Flag::STATIC });
        for(const Meta* m : m_properties.all)
            const_cast<Meta*>(m) -> set({ Flag::GLOBAL, Flag::STATIC });
    }
    
    
    const GlobalMeta&        MetaBinder<Global>::bind()
    {
        return GlobalMeta::instance();
    }
    
    GlobalMeta&       MetaBinder<Global>::edit()
    {
        return GlobalMeta::instance();
    }

    GlobalMeta*  to_global(Meta*m)
    {
        return (m && m->is_global() && m->is_compound()) ? static_cast<GlobalMeta*>(m) : nullptr;
    }
    
    const GlobalMeta*  to_global(const Meta*m)
    {
        return (m && m->is_global() && m->is_compound()) ? static_cast<const GlobalMeta*>(m) : nullptr;
    }
}

YQ_INVOKE(
    yq::GlobalMeta::instance();
);
