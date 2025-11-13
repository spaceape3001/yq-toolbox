////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/lua/info/ArgumentInfo.hpp>
#include <yq/lua/info/FunctionInfo.hpp>
#include <yq/lua/info/ValueInfo.hpp>

namespace yq::lua {
    FunctionInfo::FunctionInfo(const std::string& z) : Info(z)
    {
    }
    
    FunctionInfo::~FunctionInfo() 
    {
        for(auto& i : m_arguments)
            delete i;
        for(auto& i : m_results)
            delete i;
        for(auto& i : m_upvalues)
            delete i;
        m_arguments.clear();
        m_results.clear();
        m_upvalues.clear();
    }

    bool    FunctionInfo::is_global() const 
    {
        return parent() && parent()->is_global();
    }

    bool FunctionInfo::push_it(InstallInfoAPI&api) const
    {
        if(!api.lvm)
            return false;
        if(!m_callback)
            return false;
        if(m_upvalues.empty()){
            lua_pushcfunction(api.lvm, m_callback);
            return true;
        } else {
            // TODO
            return false;
        }
    }
}
