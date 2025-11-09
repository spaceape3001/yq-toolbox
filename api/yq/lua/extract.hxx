////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/lua/extract.hpp>
#include <yq/meta/MetaBinder.hpp>

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
        auto x    = object(l, n, meta<Obj>());
        if(!x)
            return unexpected(x.error());
        return static_cast<const Obj*>(*x);
    }

    // defined in lualua.hxx
    template <class Obj>
    Expect<const Obj*>  object_as(lua_State*l, int n, const_k)
    {
        auto x    = object(l, n, meta<Obj>(), CONST);
        if(!x)
            return unexpected(x.error());
        return static_cast<const Obj*>(*x);
    }

    template <class Obj>
    Expect<Obj*>        object_as(lua_State*l, global_k, const char* key)
    {
        auto x    = object(l, GLOBAL, key, meta<Obj>());
        if(!x)
            return unexpected(x.error());
        return static_cast<const Obj*>(*x);
    }

    // defined in lualua.hxx
    template <class Obj>
    Expect<const Obj*>  object_as(lua_State*l, global_k, const char* key, const_k)
    {
        auto x    = object(l, GLOBAL, key, meta<Obj>(), CONST);
        if(!x)
            return unexpected(x.error());
        return static_cast<const Obj*>(*x);
    }

    template <class Obj>
    Expect<Obj*>        object_as(lua_State*l, upvalue_k, int n)
    {
        auto x    = object(l, UPVALUE, n, meta<Obj>());
        if(!x)
            return unexpected(x.error());
        return static_cast<const Obj*>(*x);
    }

    // defined in lualua.hxx
    template <class Obj>
    Expect<const Obj*>  object_as(lua_State*l, upvalue_k, int n, const_k)
    {
        auto x    = object(l, UPVALUE, n, meta<Obj>(), CONST);
        if(!x)
            return unexpected(x.error());
        return static_cast<const Obj*>(*x);
    }
}
