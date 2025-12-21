////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Any.hpp>
#include <yq/lua/errors.hpp>
#include <yq/lua/impl.hpp>
#include <yq/lua/push.hpp>

#include <lua.hpp>

namespace yq::lua {

    std::error_code     push(lua_State* l, const Any& v)
    {
        if(!l)
            return errors::lua_null();
        
        if(!v.valid()){
            lua_pushnil(l);
            return {};
        }    
        
        return _push(l, v.type(), v.raw_ptr(), X::Any);
    }

    std::error_code     push(lua_State* l, bool v)
    {
        if(!l)
            return errors::lua_null();
        lua_pushboolean(l, v);
        return {};
    }
    
    std::error_code     push(lua_State* l, double v)
    {
        if(!l)
            return errors::lua_null();
        lua_pushnumber(l, v);
        return {};
    }
    
    std::error_code     push(lua_State* l, int v)
    {
        if(!l)
            return errors::lua_null();
        lua_pushinteger(l,v);
        return {};
    }
    

    std::error_code     push(lua_State* l, std::nullptr_t)
    {
        if(!l)
            return errors::lua_null();
        lua_pushnil(l);
        return {};
    }
    
    std::error_code     push(lua_State* l, std::string_view v)
    {
        if(!l)
            return errors::lua_null();
        lua_pushlstring(l, v.data(), v.size());
        return {};
    }
    
    std::error_code     push(lua_State* l, void* v)
    {
        if(!l)
            return errors::lua_null();
        lua_pushlightuserdata(l, v);
        return {};
    }

    std::error_code     push(lua_State* l, raw_k, void* v)
    {
        if(!l)
            return errors::lua_null();
        lua_pushlightuserdata(l, v);
        return {};
    }

    std::error_code     push(lua_State*l, FNLuaCallback fn)
    {
        if(!l)
            return errors::lua_null();
        if(!fn)
            return errors::null_pointer();
        lua_pushcfunction(l, fn);
        return {};
    }
    
    std::error_code     push(lua_State*l, FNLuaCallback fn, size_t n)
    {
        if(!l)
            return errors::lua_null();
        if(!fn)
            return errors::null_pointer();
        if(n>MAX_UPVALUES)
            return errors::lua_too_many_upvalues();
        if(lua_gettop(l) < (int) n)
            return errors::lua_insufficent_upvalue_arguments();
        lua_pushcclosure(l, fn, (int) n);
        return {};
    }

    std::error_code     push(lua_State*l, FNLuaCallback fn, std::initializer_list<value_t> values)
    {
        if(!l)
            return errors::lua_null();
        if(!fn)
            return errors::null_pointer();
        if((int) values.size()>MAX_UPVALUES)
            return errors::lua_too_many_upvalues();
        for(auto& v : values)
            _push(l, v);
        lua_pushcclosure(l, fn, (int) values.size());
        return {};
    }

    std::error_code     push(lua_State*l, meta_k, const Meta*m, XFlags flags)
    {
        if(!m)
            return errors::null_pointer();
        return _push(l, m, flags|X::Object);
    }

    std::error_code     push(lua_State*l, meta_k, const ObjectMeta*om, XFlags flags)
    {
        if(!om)
            return errors::null_pointer();
        return _push(l, om, flags|X::Object);
    }
    
    std::error_code     push(lua_State*l, meta_k, const TypeMeta*tm, XFlags flags)
    {
        if(!tm)
            return errors::null_pointer();
        return _push(l, tm, flags|X::Type);
    }

    std::error_code     push(lua_State*l, const_k, const Object* obj)
    {
        return _push(l, (Object*) obj, X::Const);
    }
    
    std::error_code     push(lua_State*l, Object* obj)
    {
        return _push(l, obj, XFlags{});
    }

    std::error_code         push(lua_State*l, object_k, const_k, const Object*obj)
    {
        return _push(l, (Object*) obj, X::Const);
    }
    
    std::error_code         push(lua_State*l, object_k, Object*obj)
    {
        return _push(l, obj, XFlags{});
    }

    std::error_code         push(lua_State* l, std::span<const char*> vals)
    {
        lua_newtable(l);
        int n   = lua_gettop(l);
        int cnt = 1;
        for(const char* s : vals){
            if(s){
                push(l, s);
            } else
                lua_pushnil(l);
            lua_seti(l, n, cnt);
            ++cnt;
        }
        return {};
    }

    std::error_code         push(lua_State* l, std::span<const std::string_view> vals)
    {
        lua_newtable(l);
        int n   = lua_gettop(l);
        int cnt = 1;
        for(const std::string_view& s : vals){
            push(l, s);
            lua_seti(l, n, cnt);
            ++cnt;
        }
        return {};
    }
    
    std::error_code         push(lua_State* l, std::span<const std::string> vals)
    {
        lua_newtable(l);
        int n   = lua_gettop(l);
        int cnt = 1;
        for(const std::string& s : vals){
            push(l, s);
            lua_seti(l, n, cnt);
            ++cnt;
        }
        return {};
    }

    std::error_code         push(lua_State*l, const Meta&m, void*ptr)
    {
        return errors::todo();
    }

    std::error_code     push_any_impl(lua_State* l, const TypeMeta& tm, const void* ptr)
    {
        if(!l)
            return errors::lua_null();
        if(!ptr){
            lua_pushnil(l);
            return {};
        }
        return _push(l, tm, ptr, X::Any);
    }
}
