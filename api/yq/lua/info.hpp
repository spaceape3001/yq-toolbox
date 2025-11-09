////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/lua/types.hpp>
#include <yq/meta/MetaBinder.hpp>

namespace yq::lua {
    const ModuleInfo*       info(global_k);
    const ModuleInfo*       info(module_k, const char*);
    const ObjectInfo*       info(const ObjectMeta&);
    const TypeInfo*         info(const TypeMeta&);
    
    template <typename T>
    requires is_object_v<T>
    const ObjectInfo*       info()
    {
        return info(meta<T>());
    }

    template <typename T>
    requires is_type_v<T>
    const TypeInfo*         info()
    {
        return info(meta<T>());
    }
    
    bool    has(lua_State*, global_k, const char*);
}
