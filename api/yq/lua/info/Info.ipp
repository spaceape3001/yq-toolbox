////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/lua/info/Info.hpp>
#include <yq/meta/Meta.hpp>

namespace yq::lua {
    Info::Info(const char* z) : m_key(z)
    {
    
    }
    
    Info::~Info()
    {
        m_key   = nullptr;
        m_help  = nullptr;
        m_brief = nullptr;
    }

    void    Info::brief(const char* z)
    {
        if(!Meta::thread_safe_write())  
            return;
        m_brief = z;
    }

    void    Info::help(const char* z)
    {
        if(!Meta::thread_safe_write())  
            return;
        m_help = z;
    }
}
