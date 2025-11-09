////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/lua/info/ValueInfo.hpp>
#include <yq/meta/Meta.hpp>

namespace yq::lua {
    ValueInfo::ValueInfo(const char* k) : Info(k)
    {
    }
    
    ValueInfo::~ValueInfo() = default;

    void    ValueInfo::install(InstallInfoAPI& api) const 
    {
        if(!api.lvm)
            return ;
        
        // global detection (later)
        if(push_it(api))
            lua_setglobal(api.lvm, key());
    }

    bool    ValueInfo::is_global() const 
    {
        return parent() && parent()->is_global();
    }

    bool    ValueInfo::push_it(InstallInfoAPI&api) const
    {
        return _push(api.lvm, m_value);
    }

    void       ValueInfo::type(const type_t& type)
    {
        if(!Meta::thread_safe_write())
            return;
        if(m_type != type_t())
            return ;
        m_type      = type;
    }
}
