////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/lua/repo.hpp>
#include <yq/lua/info/TypeInfo.hxx>
#include <yq/meta/ObjectMeta.hpp>
#include <yq/meta/TypeMeta.hpp>

namespace yq::lua {
    template <typename T>
    std::pair<TypedObjectInfo<T>*,bool>      Repo::edit(object_k)
    {
        if(!Meta::thread_safe_write())
            return { nullptr, false };
    
        Meta::id_t  id  = meta<T>().id();
        
        auto x = m_objects.find(id);
        if(x != m_objects.end())
            return { static_cast<TypedObjectInfo<T>*>(const_cast<ObjectInfo*>(x->second)), false };
        
        TypedObjectInfo<T>*   tti = new TypedObjectInfo<T>();
        m_objects[id]  = tti;
        return { tti, true };
    }

    template <typename T>
    std::pair<TypedTypeInfo<T>*,bool>      Repo::edit(type_k)
    {
        if(!Meta::thread_safe_write())
            return { nullptr, false };
    
        Meta::id_t  id  = meta<T>().id();
        
        auto x = m_types.find(id);
        if(x != m_types.end())
            return { static_cast<TypedTypeInfo<T>*>(const_cast<TypeInfo*>(x->second)), false };
        
        TypedTypeInfo<T>*   tti = new TypedTypeInfo<T>();
        m_types[id]  = tti;
        return { tti, true };
    }
}
