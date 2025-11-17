////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/lua/info.hpp>
#include <yq/lua/repo.hpp>
#include <yq/meta/Meta.hpp>

namespace yq::lua {
    const ModuleInfo*   info(global_k)
    {
        return Repo::instance().info(GLOBAL);
    }
    
    const ModuleInfo*   info(module_k, const char*k)
    {
        return Repo::instance().info(MODULE, k);
    }
    
    const ObjectInfo*   info(const ObjectMeta&om)
    {
        return Repo::instance().info(om);
    }
    
    const TypeInfo*     info(const TypeMeta&tm)
    {
        return Repo::instance().info(tm);
    }

    const ModuleInfo*       info(meta_k, const Meta& m)
    {
        return Repo::instance().info(META, m);
    }
    
    const ModuleInfo*       info(meta_k, uint32_t id)
    {
        return Repo::instance().info(META, id);
    }
}
