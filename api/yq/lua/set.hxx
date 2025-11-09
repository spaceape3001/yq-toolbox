////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/lua/set.hpp>

namespace yq::lua {
    template <typename ... Args>
    std::error_code     set(lua_State* l, global_k, const char*key, FNLuaCallback fn, upvalues_k, Args... args)
    {
        if(!l)
            return errors::lua_null();
        if(!fn)
            return errors::null_pointer();
        if(!key)
            return errors::null_pointer();
        if(!*key)
            return errors::bad_argument();

        std::error_code ec = push(l, fn, UPVALUES, args...);
        if(ec != std::error_code())
            return ec;
        lua_setglobal(l, key);
        return {};
    }

    template <typename ... Args>
    std::error_code     set(lua_State* l, int n, table_k, const char*key, FNLuaCallback fn, upvalues_k, Args... args)
    {
        if(!l)
            return errors::lua_null();
        if(!fn)
            return errors::null_pointer();
        if(!key)
            return errors::null_pointer();
        if(!*key)
            return errors::bad_argument();

        std::error_code ec = push(l, fn, UPVALUES, args...);
        if(ec != std::error_code())
            return ec;
        lua_setglobal(l, key);
        return {};
    }
}
