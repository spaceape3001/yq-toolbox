////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/errors.hpp>
#include <yq/lua/errors.hpp>
#include <yq/lua/impl.hpp>
#include <yq/lua/set.hpp>
#include <lua.hpp>

namespace yq::lua {

    std::error_code      set(lua_State*l, int n, table_k, const char* key, bool v)
    {   
        if(!l)
            return errors::lua_null();
        if(!key)
            return errors::null_pointer();
        if(!*key)
            return errors::bad_argument();

        int tm  = lua_absindex(l, n);
        lua_pushboolean(l, v);
        lua_setfield(l, tm, key);
        return {};
    }
    
    std::error_code         set(lua_State*l, int n, table_k, const char* key, double v)
    {
        if(!l)
            return errors::lua_null();
        if(!key)
            return errors::null_pointer();
        if(!*key)
            return errors::bad_argument();

        int tm  = lua_absindex(l, n);
        lua_pushnumber(l, v);
        lua_setfield(l, tm, key);
        return {};
    }
    
    std::error_code         set(lua_State*l, int n, table_k, const char* key, int v)
    {
        if(!l)
            return errors::lua_null();
        if(!key)
            return errors::null_pointer();
        if(!*key)
            return errors::bad_argument();

        int tm  = lua_absindex(l, n);
        lua_pushinteger(l, v);
        lua_setfield(l, tm, key);
        return {};
    }
    
    std::error_code         set(lua_State*l, int n, table_k, const char* key, std::string_view v)
    {
        if(!l)
            return errors::lua_null();
        if(!key)
            return errors::null_pointer();
        if(!*key)
            return errors::bad_argument();

        int tm  = lua_absindex(l, n);
        lua_pushlstring(l, v.data(), v.size());
        lua_setfield(l, tm, key);
        return {};
    }
    
    std::error_code         set(lua_State*l, int n, table_k, const char* key, const_k, const Object* v)
    {
        if(!l)
            return errors::lua_null();
        if(!key)
            return errors::null_pointer();
        if(!*key)
            return errors::bad_argument();
        if(!v)
            return errors::null_pointer();

        int tm  = lua_absindex(l, n);
        _push(l, const_cast<Object*>(v), X::Const );
        lua_setfield(l, tm, key);
        return {};
    }
    
    std::error_code         set(lua_State*l, int n, table_k, const char*key, Object*v)
    {
        if(!l)
            return errors::lua_null();
        if(!key)
            return errors::null_pointer();
        if(!*key)
            return errors::bad_argument();
        if(!v)
            return errors::null_pointer();

        int tm  = lua_absindex(l, n);
        _push(l, v, XFlags{} );
        lua_setfield(l, tm, key);
        return {};
    }
    
    std::error_code         set(lua_State*l, int n, table_k, const char* key, raw_k, void* v)
    {
        if(!l)
            return errors::lua_null();
        if(!key)
            return errors::null_pointer();
        if(!*key)
            return errors::bad_argument();
        if(!v)
            return errors::null_pointer();

        int tm  = lua_absindex(l, n);
        lua_pushlightuserdata(l, v );
        lua_setfield(l, tm, key);
        return {};
    }
    
    std::error_code         set(lua_State*l, int n, table_k, const char* key, FNLuaCallback v, size_t cnt)
    {
        if(!l)
            return errors::lua_null();
        if(!key)
            return errors::null_pointer();
        if(!*key)
            return errors::bad_argument();
        if(!v)
            return errors::null_pointer();
        if((int) cnt > MAX_UPVALUES)
            return errors::lua_too_many_upvalues();
        if((int) cnt > lua_gettop(l))
            return errors::lua_insufficent_upvalue_arguments();

        int tm  = lua_absindex(l, n);
        lua_pushcclosure(l, v, (int) cnt );
        lua_setfield(l, tm, key);
        return {};
    }

    std::error_code     set(lua_State*l, global_k, const char* key, bool v)
    {
        if(!l)
            return errors::lua_null();
        if(!key)
            return errors::null_pointer();
        if(!*key)
            return errors::bad_argument();
            
        lua_pushboolean(l, v);
        lua_setglobal(l, key);
        return {};
    }
    
    std::error_code     set(lua_State*l, global_k, const char* key, double v)
    {
        if(!l)
            return errors::lua_null();
        if(!key)
            return errors::null_pointer();
        if(!*key)
            return errors::bad_argument();

        lua_pushnumber(l, v);
        lua_setglobal(l, key);
        return {};
    }
    
    std::error_code     set(lua_State*l, global_k, const char* key, int v)
    {
        if(!l)
            return errors::lua_null();
        if(!key)
            return errors::null_pointer();
        if(!*key)
            return errors::bad_argument();

        lua_pushinteger(l, v);
        lua_setglobal(l, key);
        return {};
    }
    
    std::error_code     set(lua_State*l, global_k, const char* key, std::string_view v)
    {
        if(!l)
            return errors::lua_null();
        if(!key)
            return errors::null_pointer();
        if(!*key)
            return errors::bad_argument();

        lua_pushlstring(l, v.data(), v.size());
        lua_setglobal(l, key);
        return {};
    }
    
    std::error_code     set(lua_State*l, global_k, const char* key, raw_k, void* v)
    {
        if(!l)
            return errors::lua_null();
        if(!key)
            return errors::null_pointer();
        if(!*key)
            return errors::bad_argument();

        lua_pushlightuserdata(l, v);
        lua_setglobal(l, key);
        return {};
    }
    
}
