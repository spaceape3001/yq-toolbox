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
#include <yq/lua/logging.hpp>
#include <yq/lua/push.hpp>
#include <yq/lua/repo.hpp>
#include <yq/lua/set.hpp>
#include <yq/lua/info/ObjectInfo.hpp>
#include <yq/lua/info/TypeInfo.hpp>
#include <yq/meta/ObjectMeta.hpp>
#include <yq/meta/ReservedIDs.hpp>
#include <yq/meta/TypeMeta.hpp>
#include <lua.hpp>

namespace yq::lua {

    void                _metamake(lua_State* l, meta_k, const Meta&, const std::string&);
    void                _metamake(lua_State* l, const ObjectMeta&, const std::string&);
    void                _metamake(lua_State* l, const TypeMeta&, const std::string&);
    void                _metamake(lua_State* l, const UntypeMeta&, const std::string&);

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

    // Assumes the top item is a meta
    void    _metaadd(lua_State*l, const std::vector<const ModuleInfo*>& modules)
    {
        int     tm  = lua_gettop(l);
        InstallInfoAPI api{.lvm=l};
        
        bool    nIdx    = false;
        bool    nCall   = false;
        for(const ModuleInfo* mi : modules){
            nIdx    = nIdx  || mi->augment(HAS, Phase::NewIndex);
            nCall   = nCall || mi->augment(HAS, Phase::Call);
        }
        
        lua_newtable(l);
        int     ct      = lua_gettop(l);
        for(const ModuleInfo* mi : modules){
            for(auto& i : mi->components()){
                if(i.second->push_it(api))
                    lua_setfield(l, ct, i.first.c_str());
            }
            mi->augment(api, Phase::Index);
        }
        lua_setfield(l, tm, "__index");
        
        if(nIdx){
            lua_newtable(l);
            for(const ModuleInfo* mi : modules)
                mi->augment(api, Phase::NewIndex);
            lua_setfield(l, tm, "__newindex");
        }
        
        if(nCall){
            lua_newtable(l);
            for(const ModuleInfo* mi : modules)
                mi->augment(api, Phase::Call);
            lua_setfield(l, tm, "__call");
        }
    }


    void       _metamake(lua_State* l, meta_k, const Meta& m)
    {
        _metaadd(l, _modules(META, m));
    }

    void       _metamake(lua_State* l, const ObjectMeta& om)
    {
        set(l, -1, TABLE, keyGarbageCollection, lh_gc_object);
        _metaadd(l, _modules(om));
    }
    
    void        _metamake(lua_State* l, const TypeMeta& tm)
    {
        set(l, -1, TABLE, keyGarbageCollection, lh_gc_type);
        _metaadd(l, _modules(tm));
    }

    //void                _metamake(lua_State* l, const UntypeMeta& um)
    //{
        //_metaadd(l, _modules(um));
    //}
    
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
    
    const Meta* _metatype(lua_State*l,int n)
    {
        switch(lua_type(l,n)){
        case LUA_TNIL:
            return nullptr;
        case LUA_TBOOLEAN:
            return &yq::meta<bool>();
        case LUA_TSTRING:
            return &yq::meta<std::string>();
        case LUA_TNUMBER:
            if(lua_isinteger(l,n))
                return &yq::meta<int>();
            else
                return &yq::meta<double>();
        case LUA_TTABLE:
            return _meta(l,n);
        default:
            return nullptr;
        }
    }

    
    // all modules that meta will use (as data)
    std::vector<const ModuleInfo*>  _modules(const ObjectMeta&om)
    {
        static const Repo&  _r  = Repo::instance();

        std::vector<const ModuleInfo*> ret;
        if(const ModuleInfo* mi = _r.info(om)){
            if(mi)
                ret.push_back(mi);
        }
        
        for(const ObjectMeta* p = om.base(); p; p = om.base()){
            if(const ObjectInfo* mi = _r.info(*p)){
                if(mi)
                    ret.push_back(mi);
            }
        }
        
        return ret;
    }

    std::vector<const ModuleInfo*>  _modules(const TypeMeta&tm)
    {
        static const Repo&  _r  = Repo::instance();

        std::vector<const ModuleInfo*> ret;
        if(const ModuleInfo* mi = _r.info(tm))
            ret.push_back(mi);
        if(const ModuleInfo* mi = _r.info(ANY))
            ret.push_back(mi);        
        return ret;
    }

#if 0
    std::vector<const ModuleInfo*>  _modules(const UntypeMeta&tm)
    {
        static const Repo&  _r  = Repo::instance();

        std::vector<const ModuleInfo*> ret;
        if(const ModuleInfo* mi = _r.info(tm))
            ret.push_back(mi);
        return ret;
    }
#endif
    
    // all modules that meta will use (as a meta type)
    std::vector<const ModuleInfo*>  _modules(meta_k, const Meta&m)
    {
        static const Repo&  _r  = Repo::instance();
        
        std::vector<const ModuleInfo*> ret;
        if(const ModuleInfo* mi = _r.info(META, m))
            ret.push_back(mi);
        
        if(m.is_object()){
            for(const ObjectMeta* p = static_cast<const ObjectMeta&>(m).base(); p; p = p->base()){
                if(const ModuleInfo* mi = _r.info(META, *p))
                    ret.push_back(mi);
            }
        } else if(m.is_type()){
            if(const ModuleInfo* mi = _r.info(META, MT_Type))
                ret.push_back(mi);
        }
        
        if(const ModuleInfo* mi = _r.info(META, MT_Meta))
            ret.push_back(mi);
        return ret;
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
        } else if(auto p = std::get_if<const Meta*>(&val)){
            lua_pushlightuserdata(l, (void*) *p);
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
        if(luaL_newmetatable(l, name.c_str()))
            _metamake(l, obj->metaInfo());
        
        lua_setmetatable(l, -2);    // think this works....
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
        if(luaL_newmetatable(l, name.c_str()))
            _metamake(l, type);
        
        lua_setmetatable(l, -2);    // think this works....
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
        if(luaL_newmetatable(l, name.c_str()))
            _metamake(l, META, *m);
        lua_setmetatable(l, -2);    // think this works....
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

        
    std::string_view    _typename(int n)
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
