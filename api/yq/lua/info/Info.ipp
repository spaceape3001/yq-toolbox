////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/lua/info/Info.hpp>
#include <yq/meta/Meta.hpp>

namespace yq::lua {
    Info::Info(const std::string& k) : m_key(k)
    {
    
    }
    
    Info::~Info()
    {
    }

    void    Info::brief(const std::string& z)
    {
        if(!Meta::thread_safe_write())  
            return;
        m_brief = z;
    }

    void    Info::help(const std::string& z)
    {
        if(!Meta::thread_safe_write())  
            return;
        m_help = z;
    }
}
