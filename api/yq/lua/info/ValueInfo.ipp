////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/lua/info/ValueInfo.hpp>
#include <yq/meta/Meta.hpp>

namespace yq::lua {
    ValueInfo::ValueInfo(const std::string& k) : Info(k)
    {
    }
    
    ValueInfo::~ValueInfo() = default;

    bool    ValueInfo::is_global() const 
    {
        return parent() && parent()->is_global();
    }

    bool    ValueInfo::push_it(InstallInfoAPI&api) const
    {
        if(!api.lvm)
            return false;
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
