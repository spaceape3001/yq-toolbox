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
#include <yq/lua/repo.hpp>
#include <yq/lua/set.hpp>
#include <yq/lua/info/TypeInfo.hpp>
#include <yq/meta/ObjectMeta.hpp>
#include <yq/meta/ReservedIDs.hpp>
#include <yq/meta/TypeMeta.hpp>
#include <lua.hpp>

namespace yq::lua {

    void                _metamake(lua_State* l, meta_k, const Meta&, const std::string&);
    void                _metamake(lua_State* l, const ObjectMeta&, const std::string&);
    void                _metamake(lua_State* l, const TypeMeta&, const std::string&);

    std::string         _metatablename(meta_k, const Meta&);
    std::string         _metatablename(const Meta&);
    

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
        lua_getfield(l, n, keyFlags);
        XFlags  flags               = (XFlags::value_type) lua_tointeger(l, -1);
        _pop(l);
        return flags;
    }

    std::error_code    _gc(lua_State*l, int n, type_k)
    {
        if(!l)
            return errors::lua_null();
        if(!lua_istable(l, n))
            return errors::lua_not_table();

        XFlags flags                = _flags(l, n);
        if(!flags(X::Type))
            return errors::lua_not_typed_data();
        if(flags(X::Meta))
            return errors::lua_is_meta();
            
        const TypeMeta* type        = _meta(l, n, TYPE);
        if(!type)
            return errors::lua_no_meta();
        
        void*   ptr                 = _pointer(l, n);
        if(!ptr)
            return errors::null_pointer();
        
        type->destroy(ptr);
        return {};
    }

    std::error_code    _gc(lua_State*l, int n, object_k)
    {
        if(!l)
            return errors::lua_null();
        if(!lua_istable(l, n))
            return errors::lua_not_table();

        XFlags flags                = _flags(l, n);
        if(!flags(X::Object))
            return errors::lua_not_object();
        if(flags(X::Meta))
            return errors::lua_is_meta();

        Object*obj                  = _object(l, n);
        if(!obj)
            return errors::null_pointer();
        
        const ObjectMeta*   meta    = _meta(l, n, OBJECT);
        if(!meta)
            return errors::lua_no_meta();
        if(&obj->metaInfo() != meta)    // mismatch
            return errors::lua_meta_mismatch();

        if(flags(X::Ref)){
            if(Refable* ref = dynamic_cast<Refable*>(obj)){
                ref -> decRef();
            } else if(flags(X::Delete))
                delete obj;
        } else if(flags(X::Delete)){
            delete obj;
        }

        return {};
    }

    const Meta*         _meta(lua_State*l, int n)
    {
        lua_getfield(l, n, keyMeta);
        const Meta* obj = (const Meta*) lua_touserdata(l, -1);
        _pop(l);
        return obj;
    }
    
    const ObjectMeta*   _meta(lua_State*l, int n, object_k)
    {
        const Meta* m   = _meta(l, n);
        if(!m)
            return nullptr;
        if(!m->is_object())
            return nullptr;
        return static_cast<const ObjectMeta*>(m);
    }
    
    const TypeMeta*     _meta(lua_State*l, int n, type_k)
    {
        const Meta* m   = _meta(l, n);
        if(!m)
            return nullptr;
        if(!m->is_type())
            return nullptr;
        return static_cast<const TypeMeta*>(m);
    }
    
    void        _metaadd(lua_State* l, const ModuleInfo& info)
    {
        int     tm  = lua_gettop(l);
        InstallInfoAPI  api{.lvm=l};
        for(auto& i : info.components()){
            if(i.second->push_it(api))
                lua_setfield(l, tm, i.first.c_str());
        }
    }
    
    void        _metaadd(lua_State* l, meta_k, const ObjectMeta& om)
    {
        if(const ObjectMeta* base = om.base())
            _metaadd(l, META, *base);
        if(const ModuleInfo* mi = info(META, om))
            _metaadd(l, *mi);
    }
    
    void        _metaadd(lua_State*l, const ObjectMeta& om)
    {
        if(const ObjectMeta* base = om.base())
            _metaadd(l, *base);
        if(const ObjectInfo* mi = info(om))
            _metaadd(l, (const ModuleInfo&) *mi);
    }
    
    void        _metaadd(lua_State*l, const TypeMeta& tm)
    {
        if(const TypeInfo* ti = info(tm))
            _metaadd(l, *ti);
    }

    void       _metamake(lua_State* l, meta_k, const Meta& m, const std::string& name)
    {
        luaL_newmetatable(l, name.c_str());
        if(const ModuleInfo* mi = info(META, MT_Meta))
            _metaadd(l, *mi);
    
        if(m.is_object()){
            _metaadd(l, META, static_cast<const ObjectMeta&>(m));
        } 
        if(m.is_type()){
            if(const ModuleInfo* mi = info(META, MT_Type))
                _metaadd(l, *mi);
            if(const ModuleInfo* mi = info(META, m))
                _metaadd(l, *mi);
        }
    }

    void       _metamake(lua_State* l, const ObjectMeta& om, const std::string& name)
    {
        luaL_newmetatable(l, name.c_str());
        set(l, -1, TABLE, keyGarbageCollection, lh_gc_object);
        _metaadd(l, om);
    }
    
    void        _metamake(lua_State* l, const TypeMeta& tm, const std::string& name)
    {
        luaL_newmetatable(l, name.c_str());
        set(l, -1, TABLE, keyGarbageCollection, lh_gc_type);
        _metaadd(l, tm);
    }
    
    std::string         _metatablename(meta_k, const Meta& m)
    {
        if(m.name().empty())
            return std::format("[meta]:{}", m.id());
        else
            return std::format("[meta]:{}", m.name());
    }

    std::string         _metatablename(const Meta& m)
    {
        if(m.name().empty())
            return std::format("{}", m.id());
        else
            return std::string(m.name());
    }
    

    Object*     _object(lua_State *l, int n)
    {
        lua_getfield(l, n, keyPointer);
        Object* obj = (Object*) lua_touserdata(l, -1);
        _pop(l);
        return obj;
    }

    void*               _pointer(lua_State* l, int n)
    {
        lua_getfield(l, n, keyPointer);
        void* obj = lua_touserdata(l, -1);
        _pop(l);
        return obj;
    }
    
    void                _pop(lua_State* l)
    {
        lua_pop(l, 1);
    }

    std::error_code _push(lua_State* l, const value_t& val, unsigned n)
    {
        if(std::get_if<std::monostate>(&val)){
            lua_pushnil(l);
            return {};
        } else if(auto p = std::get_if<std::string>(&val)){
            return push(l, *p);
        } else if(auto p = std::get_if<bool>(&val)){
            return push(l, *p);
        } else if(auto p = std::get_if<double>(&val)){
            return push(l, *p);
        } else if(auto p = std::get_if<int>(&val)){
            lua_pushinteger(l, *p);
            return {};
        } else if(auto p = std::get_if<Object*>(&val)){
            return push(l, *p);
        } else if(auto p = std::get_if<const Object*>(&val)){
            return push(l, *p);
        } else if(auto p = std::get_if<void*>(&val)){
            return push(l, *p);
        } else if(auto p = std::get_if<FNLuaCallback>(&val)){
            return push(l, *p, (int) n);
        } else  
            return errors::lua_bad_type();
    }

    std::error_code     _push(lua_State* l, Object* obj, XFlags flags)
    {
        if(!l)
            return errors::lua_null();

        if(!obj){
            lua_pushnil(l);
            return {};
        }
        
        flags |= X::Object;
        
        lua_newtable(l);
        set(l, -1, TABLE, keyPointer, RAW, obj);
        set(l, -1, TABLE, keyMeta, RAW, (void*) &(obj->metaInfo()));
        set(l, -1, TABLE, keyFlags, flags.value());
        
        Refable* ref    = dynamic_cast<Refable*>(obj);
        if(ref && flags(X::Ref))
            ref -> incRef();
        
        std::string name    = _metatablename(obj->metaInfo());
        luaL_getmetatable(l, name.c_str());
        
        if(lua_isnil(l, -1)){
            _pop(l);
            _metamake(l, obj->metaInfo(), name);
        }
        
        lua_setmetatable(l, -1);    // think this works....
        return {};
    }
    
    std::error_code _push(lua_State* l, const TypeMeta& type, const void* ptr, XFlags flags)
    {
        if(!l || !ptr)
            return errors::lua_null();
        
        const TypeInfo* tinfo   = Repo::instance().info(type);
        bool    pushed  = false;
        if(tinfo){
            if(FNLuaDivertor fn = tinfo->divertor()){
                if(!fn(l, ptr))
                    return errors::lua_push_failed();
                return {};
            }
            if(FNLuaPush fn = tinfo->pusher()){
                if(!fn(l, ptr))
                    return errors::lua_push_failed();
                if(lua_type(l, -1) != LUA_TTABLE)   // some simple types might do a direct LUA push (w/o table)
                    return {};
                pushed  = true;
            }
        }
        
        if(!pushed){
            lua_newtable(l);
            void*   data    = type.copy(ALLOCATE, ptr);
            set(l, -1, TABLE, keyPointer, RAW, data);
        }

        flags |= X::Type;
        set(l, -1, TABLE, keyMeta, RAW, (void*) &type);
        set(l, -1, TABLE, keyFlags, flags.value());
        
        std::string name    = _metatablename(type);
        luaL_getmetatable(l, name.c_str());
        
        if(lua_isnil(l, -1)){
            _pop(l);
            _metamake(l, type, name);
        }
        
        lua_setmetatable(l, -1);    // think this works....
        return {};
    }

    std::error_code     _push(lua_State*l, const Meta* m, XFlags flags)
    {
        if(!l || !m)
            return errors::lua_null();
            
        flags |= X::Meta;
        lua_newtable(l);
        set(l, -1, TABLE, keyMeta, RAW, (void*) m);
        set(l, -1, TABLE, keyFlags, flags.value());
        
        std::string name    = _metatablename(*m);
        luaL_getmetatable(l, name.c_str());
        if(lua_isnil(l, -1)){
            _pop(l);
            _metamake(l, META, *m, name);
        }
        
        lua_setmetatable(l, -1);    // think this works....
        return {};
    }
    
    std::error_code _push(lua_State* l, const Any& any, XFlags flags)
    {
        if(!any.invalid()){
            lua_pushnil(l);
            return {};
        }
        return _push(l, any.type(), any.raw_ptr(), flags);
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
