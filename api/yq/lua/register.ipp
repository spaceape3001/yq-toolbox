////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/lua/register.hpp>
#include <yq/lua/repo.hpp>
#include <yq/lua/info/ModuleInfo.hpp>

namespace yq::lua {

    ValueInfo*      reg(global_k, const std::string&k, value_k)
    {
        auto g  = reg_edit(GLOBAL).first;
        if(!g)
            return nullptr;
        return g->add(k, VALUE);
    }
    
    ValueInfo*      reg(global_k, const std::string&k, bool v)
    {
        auto g  = reg_edit(GLOBAL).first;
        if(!g)
            return nullptr;
        return g->add(k, v);
    }
    
    ValueInfo*      reg(global_k, const std::string&k, double v)
    {
        auto g  = reg_edit(GLOBAL).first;
        if(!g)
            return nullptr;
        return g->add(k, v);
    }
    
    ValueInfo*      reg(global_k, const std::string&k, int v)
    {
        auto g  = reg_edit(GLOBAL).first;
        if(!g)
            return nullptr;
        return g->add(k, v);
    }
    
    ValueInfo*      reg(global_k, const std::string&k, std::string_view v)
    {
        auto g  = reg_edit(GLOBAL).first;
        if(!g)
            return nullptr;
        return g->add(k, v);
    }
    
    ValueInfo*      reg(global_k, const std::string&k, Object* v)
    {
        auto g  = reg_edit(GLOBAL).first;
        if(!g)
            return nullptr;
        return g->add(k, v);
    }
    
    ValueInfo*      reg(global_k, const std::string&k, const Object* v)
    {
        auto g  = reg_edit(GLOBAL).first;
        if(!g)
            return nullptr;
        return g->add(k, v);
    }
    
    ValueInfo*      reg(global_k, const std::string&k, raw_k, void* v)
    {
        auto g  = reg_edit(GLOBAL).first;
        if(!g)
            return nullptr;
        return g->add(k, v);
    }

    FunctionInfo*   reg(global_k, const std::string&k, function_k)
    {
        auto g  = reg_edit(GLOBAL).first;
        if(!g)
            return nullptr;
        return g->add(k, FUNCTION);
    }
    
    FunctionInfo*   reg(global_k, const std::string&k, FNLuaCallback v)
    {
        auto g  = reg_edit(GLOBAL).first;
        if(!g)
            return nullptr;
        return g->add(k, v);
    }

    ModuleInfo*     reg(module_k, const std::string&k)
    {
        return reg_edit(MODULE, k).first;
    }

    ObjectInfo*     reg(const ObjectMeta& om)
    {
        return reg_edit(om).first;
    }
    
    TypeInfo*       reg(const TypeMeta&tm)
    {
        return reg_edit(tm).first;
    }

        ///

    std::pair<ModuleInfo*,bool>  reg_edit(global_k)
    {
        return Repo::instance().edit(GLOBAL);
    }
    
    std::pair<ModuleInfo*,bool>  reg_edit(module_k, const std::string&k)
    {
        return Repo::instance().edit(MODULE, k);
    }
    
    std::pair<ObjectInfo*,bool>  reg_edit(const ObjectMeta&om)
    {
        return Repo::instance().edit(om);
    }
    
    std::pair<TypeInfo*,bool>  reg_edit(const TypeMeta&tm)
    {
        return Repo::instance().edit(tm);
    }
}
