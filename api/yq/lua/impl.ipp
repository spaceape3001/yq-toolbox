////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Object.hpp>
#include <yq/core/Ref.hpp>
#include <yq/lua/errors.hpp>
#include <yq/lua/handler.hpp>
#include <yq/lua/impl.hpp>
#include <yq/lua/keys.hpp>
#include <yq/lua/push.hpp>
#include <yq/lua/set.hpp>
#include <yq/meta/ObjectMeta.hpp>
#include <yq/meta/TypeMeta.hpp>
#include <lua.hpp>

namespace yq::lua {
    std::error_code     _error(int n)
    {
        switch(n){
        case LUA_OK:
            return std::error_code();
        case LUA_ERRRUN:
            return errors::lua_runtime();
        case LUA_ERRMEM:
            return errors::lua_memory();
        case LUA_ERRERR:
            return errors::lua_message();
        case LUA_ERRSYNTAX:
            return errors::lua_syntax();
        case LUA_YIELD:
            return errors::lua_yield_code();
        case LUA_ERRFILE:
            return errors::lua_file();
        default:
            return errors::lua_unexpected();
        }
    }

    XFlags      _flags(lua_State *l, int n)
    {
        lua_pushstring(l, keyFlags);
        lua_gettable(l, n);
        XFlags  flags               = (XFlags::value_type) lua_tointeger(l, -1);
        _pop(l);
        return flags;
    }


    bool    _gc(lua_State*l, int n, object_k)
    {
        if(!l)
            return false;
        if(!lua_istable(l, n))
            return false;

        Object*obj                  = _object(l, n);
        XFlags flags                = _flags(l, n);
        const ObjectMeta*   meta    = _meta(l, n, OBJECT);

        if(!obj || !meta)               // neither meta nor obj
            return false;
        if(&obj->metaInfo() != meta)    // mismatch
            return false;

        if(flags(X::Ref)){
            if(Refable* ref = dynamic_cast<Refable*>(obj)){
                ref -> decRef();
            } else if(flags(X::Delete))
                delete obj;
        } else if(flags(X::Delete)){
            delete obj;
        }

        return true;
    }

    const Meta*         _meta(lua_State*l, int n)
    {
        lua_pushstring(l, keyMeta);
        lua_gettable(l, n);
        const Meta* obj = (const Meta*) lua_touserdata(l, -1);
        _pop(l);
        return obj;
    }
    
    const ObjectMeta*   _meta(lua_State*l, int n, object_k)
    {
        const Meta* m   = _meta(l, n);
        if(!m->is_object())
            return nullptr;
        return static_cast<const ObjectMeta*>(m);
    }
    
    const TypeMeta*     _meta(lua_State*l, int n, type_k)
    {
        const Meta* m   = _meta(l, n);
        if(!m->is_type())
            return nullptr;
        return static_cast<const TypeMeta*>(m);
    }

    void       _metamake(lua_State* l, const ObjectMeta& om)
    {
        std::string name(om.name());
        luaL_newmetatable(l, name.c_str());
        set(l, -1, TABLE, keyGarbageCollection, lh_gc_object);
    }
    
    Object*     _object(lua_State *l, int n)
    {
        lua_pushstring(l, keyPointer);
        lua_gettable(l, n);
        Object* obj = (Object*) lua_touserdata(l, -1);
        _pop(l);
        return obj;
    }
    
    void                _pop(lua_State* l)
    {
        lua_pop(l, 1);
    }

    bool _push(lua_State* l, const value_t& val, unsigned n)
    {
        if(std::get_if<std::monostate>(&val)){
            lua_pushnil(l);
            return true;
        } else if(auto p = std::get_if<std::string>(&val)){
            push(l, *p);
            return true;
        } else if(auto p = std::get_if<bool>(&val)){
            push(l, *p);
            return true;
        } else if(auto p = std::get_if<double>(&val)){
            push(l, *p);
            return true;
        } else if(auto p = std::get_if<int>(&val)){
            lua_pushinteger(l, *p);
            return true;
        } else if(auto p = std::get_if<Object*>(&val)){
            push(l, *p);
            return true;
        } else if(auto p = std::get_if<const Object*>(&val)){
            push(l, *p);
            return true;
        } else if(auto p = std::get_if<void*>(&val)){
            push(l, *p);
            return true;
        } else if(auto p = std::get_if<FNLuaCallback>(&val)){
            push(l, *p, (int) n);
            return true;
        } else  
            return false;
    }

    std::error_code     _push(lua_State* l, Object* obj, XFlags flags)
    {
        if(!l)
            return errors::lua_null();

        if(!obj){
            lua_pushnil(l);
            return {};
        }
        
        lua_newtable(l);
        set(l, -1, TABLE, keyPointer, RAW, obj);
        set(l, -1, TABLE, keyMeta, RAW, (void*) &(obj->metaInfo()));
        set(l, -1, TABLE, keyFlags, flags.value());
        
        Refable* ref    = dynamic_cast<Refable*>(obj);
        if(ref && flags(X::Ref))
            ref -> incRef();
        
        std::string name    = std::string(obj->metaInfo().name());
        luaL_getmetatable(l, name.c_str());
        
        if(lua_isnil(l, -1)){
            _pop(l);
            _metamake(l, obj->metaInfo());
        }
        
        lua_setmetatable(l, -1);    // think this works....
        return {};
    }
        
    std::string_view    _type(int n)
    {
        switch(n){
        case LUA_TNIL:
            return "nil";
        case LUA_TNUMBER:
            return "number";
        case LUA_TBOOLEAN:
            return "boolean";
        case LUA_TSTRING:
            return "string";
        case LUA_TTABLE:
            return "table";
        case LUA_TFUNCTION:
            return "function";
        case LUA_TUSERDATA:
            return "userdata";
        case LUA_TTHREAD:
            return "thread";
        case LUA_TLIGHTUSERDATA:
            return "lightuserdata";
        default:
            return "unknown";
        }
    }
}
