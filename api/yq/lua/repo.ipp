////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/lua/repo.hpp>
#include <yq/lua/info/FunctionInfo.hpp>
#include <yq/lua/info/ModuleInfo.hpp>
#include <yq/lua/info/ObjectInfo.hpp>
#include <yq/lua/info/TypeInfo.hpp>
#include <yq/lua/info/ValueInfo.hpp>
#include <yq/meta/Meta.hpp>
#include <yq/text/match.hpp>

namespace yq::lua {
    Repo&    Repo::instance()
    {
        static Repo*    s_repo = new Repo;
        return *s_repo;
    }
    
    Repo::Repo(const std::source_location& sl) : Meta("yq::lua::Repo", sl)
    {
    }
    
    Repo::~Repo() 
    {
        // kinda pointless as we're a meta thing
    
        if(m_global){
            delete m_global;
            m_global = nullptr;
        }
        for(auto& i : m_modules)
            delete i.second;
        m_modules.clear();

        for(auto& i : m_objects)
            delete i.second;
        m_objects.clear();

        for(auto& i : m_types)
            delete i.second;
        m_types.clear();
    }

/*
    std::pair<FunctionInfo*, bool>  Repo::create(global_k, const char*k, function_k)
    {
        if(!k || !*k || !thread_safe_write())
            return { nullptr, false };
            
        auto i = m_globals.find(k);
        if(i != m_globals.end())
            return { dynamic_cast<FunctionInfo*>(const_cast<Info*>(i->second)), false };
        
        FunctionInfo*   ret = new FunctionInfo(k);
        m_globals[k]    = ret;
        m_infos.insert({k, ret});
        return { ret, true };
    }
    
    std::pair<ValueInfo*, bool>     Repo::create(global_k, const char*k, value_k)
    {
        if(!k || !*k || !thread_safe_write())
            return { nullptr, false };

        auto i = m_globals.find(k);
        if(i != m_globals.end())
            return { dynamic_cast<ValueInfo*>(const_cast<Info*>(i->second)), false };
            
        ValueInfo*  ret = new  ValueInfo(k);
        m_globals[k]    = ret;
        m_infos.insert({k, ret});
        return { ret, true };
    }
    
*/

    std::pair<ModuleInfo*,bool>         Repo::edit(global_k)
    {
        if(!thread_safe_write())
            return { nullptr, false };
        if(m_global)
            return { m_global, false };
        m_global    = new GlobalModuleInfo;
        m_global -> brief("Lua globals");
        m_global -> help(R"VOGON(
This is the lua global table.  Listed are functions/values registered with
our lua registry.        
)VOGON");
        return { m_global, true };
    }

    std::pair<ModuleInfo*,bool>         Repo::edit(module_k, const std::string&k)
    {
        if(k.empty() || !thread_safe_write())
            return { nullptr, false };

        auto i = m_modules.find(k);
        if(i != m_modules.end())
            return { const_cast<ModuleInfo*>(i->second), false };

        ModuleInfo* ret = new ModuleInfo(k);
        m_modules[k] = ret;
        return { ret, true };
    }
    
    std::pair<ObjectInfo*,bool>         Repo::edit(const ObjectMeta& om)
    {
        if(!thread_safe_write())
            return { nullptr, false };
            
        auto i = m_objects.find(om.id());
        if(i != m_objects.end())
            return { const_cast<ObjectInfo*>(i->second), false };

        ObjectInfo* ret = new ObjectInfo(om);
        m_objects[om.id()]  = ret;
        return { ret, true };
    }
    
    std::pair<TypeInfo*,bool>           Repo::edit(const TypeMeta& tm)
    {
        if(!thread_safe_write())
            return { nullptr, false };
            
        auto i = m_types.find(tm.id());
        if(i != m_types.end())
            return { const_cast<TypeInfo*>(i->second), false };

        TypeInfo* ret = new TypeInfo(tm);
        m_types[tm.id()] = ret;
        return { ret, true };
    }
    
    const ModuleInfo*     Repo::info(global_k) const
    {
        return m_global;
    }
/*
    const Info*     Repo::info(global_k, const char* k) const
    {
        if(!k || !*k)
            return nullptr;
        auto i = m_globals.find(k);
        if(i != m_globals.end())
            return i->second;
        return nullptr;
    }
*/
    
    const ModuleInfo*     Repo::info(module_k, const std::string& k) const
    {
        if(k.empty())
            return nullptr;
        if(is_similar(k, "_G"))
            return m_global;
        auto i = m_modules.find(k);
        if(i != m_modules.end())
            return i->second;
        return nullptr;
    }
    
    const ObjectInfo*     Repo::info(const ObjectMeta& om) const
    {
        auto i = m_objects.find(om.id());
        if(i != m_objects.end())
            return i->second;
        return nullptr;
    }
    
    const TypeInfo*     Repo::info(const TypeMeta& tm) const
    {
        auto i = m_types.find(tm.id());
        if(i != m_types.end())
            return i->second;
        return nullptr;
    }

    
    
#if 0
    bool _push(lua_State* l, const value_t& val, int n=-1);
#endif

}
