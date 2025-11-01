////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "lualua.hpp"
#include "errors.hpp"
#include <yq/errors.hpp>
#include <yq/core/Any.hpp>
#include <yq/core/Flags.hpp>
#include <yq/core/Object.hpp>
#include <yq/core/Ref.hpp>
#include <yq/meta/ObjectMeta.hpp>
#include <lua.hpp>

namespace yq::lua {
    enum class X : uint8_t {
        Const,
        Delete,
        Ref
    };
    using XFlags    = Flags<X>;
    
    inline void _pop(lua_State* l)
    {
        lua_pop(l, 1);
    }
    
    const ObjectMeta*   _meta(lua_State*l, int n)
    {
        lua_pushliteral(l, "_meta");
        lua_gettable(l, n);
        const ObjectMeta* obj = (const ObjectMeta*) lua_touserdata(l, -1);
        _pop(l);
        return obj;
    }

    Object*     _object(lua_State *l, int n)
    {
        lua_pushliteral(l, "_ptr");
        lua_gettable(l, n);
        Object* obj = (Object*) lua_touserdata(l, -1);
        _pop(l);
        return obj;
    }
    
    XFlags      _flags(lua_State *l, int n)
    {
        lua_pushliteral(l, "_flags");
        lua_gettable(l, n);
        XFlags  flags               = (XFlags::value_type) lua_tointeger(l, -1);
        _pop(l);
        return flags;
    }

    int     gc_object(lua_State*l)
    {
        if(!l)
            return 0;
        if(!lua_istable(l, 1))
            return 0;
            
        Object*obj                  = _object(l, 1);
        XFlags flags                = _flags(l, 1);
        const ObjectMeta*   meta    = _meta(l, 1);
            
        if(!obj || !meta)               // neither meta nor obj
            return 0;
        if(&obj->metaInfo() != meta)    // mismatch
            return 0;
        
        if(flags(X::Ref)){
            if(Refable* ref = dynamic_cast<Refable*>(obj)){
                ref -> decRef();
            } else if(flags(X::Delete))
                delete obj;
        } else if(flags(X::Delete)){
            delete obj;
        }
        
        _pop(l);
        return -1;
    }

    void    fill_metatable(lua_State* l, const ObjectMeta& om)
    {
        int     tm  = lua_gettop(l);
        
        lua_pushcfunction(l, gc_object);
        lua_pushliteral(l, "__gc");
        lua_settable(l, tm);
        
        
        // *TODO*
    }
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //  API

    Object*             object(lua_State* l, stack_k, int n)
    {
        if(!l)
            return nullptr;
            
        if(!lua_istable(l, n))
            return nullptr;
            
        Object* obj                 = _object(l, n);
        const ObjectMeta*   meta    = _meta(l, n);
        if(meta != &obj->metaInfo())    // sanity check
            return nullptr;
        
        XFlags  flags   = _flags(l, n);
        if(flags(X::Const))
            return nullptr;
            
        return obj;
    }

    const Object*       object(lua_State* l, stack_k, int n, const_k)
    {
        if(!l)
            return nullptr;
            
        if(!lua_istable(l, n))
            return nullptr;
            
        const Object*       obj     = _object(l, n);
        const ObjectMeta*   meta    = _meta(l, n);
        if(meta != &obj->metaInfo())    // sanity check
            return nullptr;
        return obj;
    }

    
    std::error_code     push(lua_State* l, Object* obj, XFlags flags)
    {
        if(!l)
            return errors::lua_null();

        if(!obj){
            lua_pushnil(l);
            return {};
        }
        
        lua_newtable(l);
        
        lua_pushliteral(l, "_ptr");
        lua_pushlightuserdata(l, obj);
        lua_settable(l,  -1);
        
        lua_pushliteral(l, "_meta");
        lua_pushlightuserdata(l, (void*) &(obj->metaInfo()));
        lua_settable(l,  -1);
        
        lua_pushliteral(l, "_flags");
        lua_pushinteger(l, flags.value());
        lua_settable(l, -1);
        
        Refable* ref    = dynamic_cast<Refable*>(obj);
        if(ref && flags(X::Ref))
            ref -> incRef();
        
        std::string name    = std::string(obj->metaInfo().name());
        luaL_getmetatable(l, name.c_str());
        
        if(lua_isnil(l, -1)){
            _pop(l);
            luaL_newmetatable(l, name.c_str());
            fill_metatable(l, obj->metaInfo());
        }
        
        lua_setmetatable(l, -1);    // think this works....
        return {};
    }
    

    std::error_code     push(lua_State*l, const_k, const Object* obj)
    {
        return push(l, (Object*) obj, X::Const);
    }
    
    std::error_code     push(lua_State*l, Object* obj)
    {
        return push(l, obj, {});
    }
}

