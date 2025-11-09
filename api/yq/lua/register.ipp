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

    ValueInfo*      reg(global_k, const char*k, value_k)
    {
        auto g  = reg_edit(GLOBAL).first;
        if(!g)
            return nullptr;
        return g->add(k, VALUE);
    }
    
    ValueInfo*      reg(global_k, const char*k, bool v)
    {
        auto g  = reg_edit(GLOBAL).first;
        if(!g)
            return nullptr;
        return g->add(k, v);
    }
    
    ValueInfo*      reg(global_k, const char*k, double v)
    {
        auto g  = reg_edit(GLOBAL).first;
        if(!g)
            return nullptr;
        return g->add(k, v);
    }
    
    ValueInfo*      reg(global_k, const char*k, int v)
    {
        auto g  = reg_edit(GLOBAL).first;
        if(!g)
            return nullptr;
        return g->add(k, v);
    }
    
    ValueInfo*      reg(global_k, const char*k, std::string_view v)
    {
        auto g  = reg_edit(GLOBAL).first;
        if(!g)
            return nullptr;
        return g->add(k, v);
    }
    
    ValueInfo*      reg(global_k, const char*k, Object* v)
    {
        auto g  = reg_edit(GLOBAL).first;
        if(!g)
            return nullptr;
        return g->add(k, v);
    }
    
    ValueInfo*      reg(global_k, const char*k, const Object* v)
    {
        auto g  = reg_edit(GLOBAL).first;
        if(!g)
            return nullptr;
        return g->add(k, v);
    }
    
    ValueInfo*      reg(global_k, const char*k, raw_k, void* v)
    {
        auto g  = reg_edit(GLOBAL).first;
        if(!g)
            return nullptr;
        return g->add(k, v);
    }

    FunctionInfo*   reg(global_k, const char*k, function_k)
    {
        auto g  = reg_edit(GLOBAL).first;
        if(!g)
            return nullptr;
        return g->add(k, FUNCTION);
    }
    
    FunctionInfo*   reg(global_k, const char*k, FNLuaCallback v)
    {
        auto g  = reg_edit(GLOBAL).first;
        if(!g)
            return nullptr;
        return g->add(k, v);
    }

        ///

    std::pair<ModuleInfo*,bool>  reg_edit(global_k)
    {
        return Repo::instance().edit(GLOBAL);
    }
    
    std::pair<ModuleInfo*,bool>  reg_edit(module_k, const char*k)
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
