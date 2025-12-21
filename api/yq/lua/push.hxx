////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/errors.hpp>
#include <yq/core/Ref.hpp>
#include <yq/lua/errors.hpp>
#include <yq/lua/impl.hpp>
#include <yq/lua/keywords.hpp>
#include <yq/lua/push.hpp>
#include <yq/meta/MetaBinder.hpp>
#include <lua.hpp>

namespace yq::lua {

    template <class Obj>
    requires (std::is_base_of_v<Refable, Obj> && std::is_base_of_v<Object, Obj>)
    std::error_code     push(lua_State*l, Ref<Obj> ptr)
    {
        return _push(l, ptr.ptr(), { X::Ref });
    }

    template <class Obj>
    requires (std::is_base_of_v<Refable, Obj> && std::is_base_of_v<Object, Obj>)
    std::error_code     push(lua_State*l, Ref<const Obj> ptr)
    {
        return _push(l, const_cast<Object*>(ptr.ptr()), { X::Const, X::Ref });
    }

    template <typename A, typename ... Args>
    std::error_code     push(lua_State*l, all_k, A arg, Args... args)
    {
        if(!l)
            return errors::lua_null();
        
        push(l, arg);
        if constexpr (sizeof...(args) > 0){
            push(l, ALL, args...);
        }
        return {};
    }

    template <typename ... Args>
    std::error_code     push(lua_State*l, FNLuaCallback fn, upvalues_k, Args... args)
    {
        static_assert(sizeof...(args) <= (size_t) MAX_UPVALUES, "Lua cannot take more upvalues");

        if(!l)
            return errors::lua_null();
        if(!fn)
            return errors::null_pointer();
        
        push(l, ALL, args...);
        lua_pushcclosure(l, fn, (size_t) sizeof...(args));
        return {};
    }
    
    template <typename T>
    std::error_code         push(lua_State*l, any_k, const T&val)
    {
        return _push(l, ::yq::meta<T>(), &val, { X::Any });
    }

}
