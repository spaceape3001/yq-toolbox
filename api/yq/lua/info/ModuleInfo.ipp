////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ModuleInfo.hpp"
#include <yq/meta/Meta.hpp>

namespace yq::lua {
    ModuleInfo::ModuleInfo(const std::string& z) : Info(z)
    {
    }
    
    ModuleInfo::~ModuleInfo() 
    {
        for(auto& x : m_components)
            delete x.second;
        m_components.clear();
    }

    FunctionInfo*       ModuleInfo::add(const std::string& k, function_k)
    {
        auto [x,f] = edit(FUNCTION, k);
        if(!f)
            return nullptr;
        return x;
    }
    

    ValueInfo*          ModuleInfo::add(const std::string& k, value_k)
    {
        auto [x,f] = edit(VALUE, k);
        if(!f)
            return nullptr;
        return x;
    }
    
    FunctionInfo*       ModuleInfo::add(const std::string& k, FNLuaCallback fn)
    {
        if(!fn)
            return nullptr;
            
        auto [x,f]  = edit(FUNCTION, k);
        if(!f)
            return nullptr;
            
        x -> m_callback = fn;
        return x;
    }
    
    ValueInfo*          ModuleInfo::add(const std::string& k, bool v)
    {
        auto [x,f]  = edit(VALUE, k);
        if(!f)
            return nullptr;
            
        x -> m_type     = Type::Boolean;
        x -> m_value    = v;
        return x;
    }
    
    ValueInfo*          ModuleInfo::add(const std::string&k, double v)
    {
        auto [x,f]  = edit(VALUE, k);
        if(!f)
            return nullptr;
            
        x -> m_type     = Type::Double;
        x -> m_value    = v;
        return x;
    }
    
    ValueInfo*          ModuleInfo::add(const std::string&k, int v)
    {
        auto [x,f]  = edit(VALUE, k);
        if(!f)
            return nullptr;
            
        x -> m_type     = Type::Integer;
        x -> m_value    = v;
        return x;
    }
    
    ValueInfo*          ModuleInfo::add(const std::string&k, std::string_view v)
    {
        auto [x,f]  = edit(VALUE, k);
        if(!f)
            return nullptr;
            
        x -> m_type     = Type::String;
        x -> m_value    = std::string(v);
        return x;
    }
    
    ValueInfo*          ModuleInfo::add(const std::string&k, const Object* v)
    {
        if(!v)
            return nullptr;
            
        Repo::instance().edit(v->metaInfo());
            
        auto [x,f]  = edit(VALUE, k);
        if(!f)
            return nullptr;
            
        x -> m_type     = &(v->metaInfo());
        x -> m_value    = v;
        return x;
    }
    
    ValueInfo*          ModuleInfo::add(const std::string&k, Object* v)
    {
        if(!v)
            return nullptr;

        Repo::instance().edit(v->metaInfo());

        auto [x,f]  = edit(VALUE, k);
        if(!f)
            return nullptr;
            
        x -> m_type     = &(v->metaInfo());
        x -> m_value    = v;
        
        return x;
    }
    
    ValueInfo*          ModuleInfo::add(const std::string&k, raw_k, void* v)
    {
        if(!v)
            return nullptr;

        auto [x,f]  = edit(VALUE, k);
        if(!f)
            return nullptr;
            
        x -> m_type     = Type::Pointer;
        x -> m_value    = v;
        
        return x;
    }

    std::pair<FunctionInfo*,bool>   ModuleInfo::edit(function_k, const std::string& k)
    {
        if(k.empty() || !Meta::thread_safe_write())
            return { nullptr, false };
        auto x = m_components.find(k);
        if(x != m_components.end())
            return { dynamic_cast<FunctionInfo*>(const_cast<Info*>(x->second)), false };
        FunctionInfo* ret  = new FunctionInfo(k);
        ret -> m_parent = this;
        m_components[k] = ret;
        return { ret, true };
    }

    std::pair<ValueInfo*,bool>   ModuleInfo::edit(value_k, const std::string& k)
    {
        if(k.empty() || !Meta::thread_safe_write())
            return { nullptr, false };
        auto x = m_components.find(k);
        if(x != m_components.end())
            return { dynamic_cast<ValueInfo*>(const_cast<Info*>(x->second)), false };
        ValueInfo* ret  = new ValueInfo(k);
        ret -> m_parent = this;
        m_components[k] = ret;
        return { ret, true };
    }
    
    const Info*         ModuleInfo::info(const std::string&k) const
    {
        if(k.empty())
            return nullptr;
        auto x = m_components.find(k);
        if(x != m_components.end())
            return x->second;
        return nullptr;
    }
    
    const FunctionInfo* ModuleInfo::info(function_k, const std::string& k) const
    {
        if(k.empty())
            return nullptr;
        auto x = m_components.find(k);
        if(x != m_components.end())
            return dynamic_cast<const FunctionInfo*>(x->second);
        return nullptr;
    }

    const ValueInfo*    ModuleInfo::info(value_k, const std::string& k) const
    {
        if(k.empty())
            return nullptr;
        auto x = m_components.find(k);
        if(x != m_components.end())
            return dynamic_cast<const ValueInfo*>(x->second);
        return nullptr;
    }
    
    bool    ModuleInfo::install(InstallInfoAPI& api) const 
    {
        if(!api.lvm)
            return false;

        lua_getglobal(api.lvm, key().c_str());
        if(lua_type(api.lvm, -1) != LUA_TTABLE){    // in case there's an existing package
            _pop(api.lvm);
            lua_newtable(api.lvm);
        }
        int tm  = lua_gettop(api.lvm);
        for(auto& i : m_components){
            if(i.second->push_it(api))
                lua_setfield(api.lvm, tm, i.first.c_str());
        }
        lua_setglobal(api.lvm, key().c_str());
        return true;
    }

    //////////////////

    GlobalModuleInfo::GlobalModuleInfo() : ModuleInfo("_G")
    {
    }
    
    GlobalModuleInfo::~GlobalModuleInfo()
    {
    }

    bool    GlobalModuleInfo::install(InstallInfoAPI& api) const 
    {
        if(!api.lvm)
            return false;
        for(auto& i : m_components){
            if(i.second->push_it(api))
                lua_setglobal(api.lvm, i.first.c_str());
        }
        return true;
    }
}
