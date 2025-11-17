////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/lua/extract.hpp>
#include <yq/meta/MetaBinder.hpp>
#include <yq/core/ErrorDB.hpp>

namespace yq::lua {

    //////////////////////////////////////////////////////////////////////////////
    //  Extracting

    #if 0
        // TBD....
    template <typename T>
    auto  extract(lua_State* l, int n)
    {
        return Extractor<T>::get(l, n);
    }
    #endif

    template <class Obj>
    Expect<Obj*>        object_as(lua_State*l, int n)
    {
        auto x    = object(l, n, ::yq::meta<Obj>());
        if(!x)
            return unexpected(x.error());
        return static_cast<const Obj*>(*x);
    }

    // defined in lualua.hxx
    template <class Obj>
    Expect<const Obj*>  object_as(lua_State*l, int n, const_k)
    {
        auto x    = object(l, n, ::yq::meta<Obj>(), CONST);
        if(!x)
            return unexpected(x.error());
        return static_cast<const Obj*>(*x);
    }

    template <class Obj>
    Expect<Obj*>        object_as(lua_State*l, global_k, const char* key)
    {
        auto x    = object(l, GLOBAL, key, ::yq::meta<Obj>());
        if(!x)
            return unexpected(x.error());
        return static_cast<const Obj*>(*x);
    }

    // defined in lualua.hxx
    template <class Obj>
    Expect<const Obj*>  object_as(lua_State*l, global_k, const char* key, const_k)
    {
        auto x    = object(l, GLOBAL, key, ::yq::meta<Obj>(), CONST);
        if(!x)
            return unexpected(x.error());
        return static_cast<const Obj*>(*x);
    }

    template <class Obj>
    Expect<Obj*>        object_as(lua_State*l, upvalue_k, int n)
    {
        auto x    = object(l, UPVALUE, n, ::yq::meta<Obj>());
        if(!x)
            return unexpected(x.error());
        return static_cast<const Obj*>(*x);
    }

    // defined in lualua.hxx
    template <class Obj>
    Expect<const Obj*>  object_as(lua_State*l, upvalue_k, int n, const_k)
    {
        auto x    = object(l, UPVALUE, n, ::yq::meta<Obj>(), CONST);
        if(!x)
            return unexpected(x.error());
        return static_cast<const Obj*>(*x);
    }

    
    template <class Obj>
    Expect<const typename Obj::MyInfo*>     object_meta_as(lua_State* l, int n)
    {
        auto x = object_meta(l,n);
        if(!x)
            return unexpected(x.error());
        return dynamic_cast<const typename Obj::MyInfo*>(*x);
    }
    
    template <class Obj>
    Expect<const typename Obj::MyInfo*>     object_meta_as(lua_State*l, global_k, const char* key)
    {
        auto x = object_meta(l,GLOBAL,key);
        if(!x)
            return unexpected(x.error());
        return dynamic_cast<const typename Obj::MyInfo*>(*x);
    }
    
    template <class Obj>
    Expect<const typename Obj::MyInfo*>     object_meta_as(lua_State*l, upvalue_k, int n)
    {
        auto x = object_meta(l,UPVALUE,n);
        if(!x)
            return unexpected(x.error());
        return dynamic_cast<const typename Obj::MyInfo*>(*x);
    }
    
}
