////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/errors.hpp>
#include <yq/core/Any.hpp>
#include <yq/core/Object.hpp>
#include <yq/lua/extract.hpp>
#include <yq/lua/errors.hpp>
#include <yq/lua/impl.hpp>
#include <yq/lua/keys.hpp>
#include <yq/meta/ObjectMeta.hpp>
#include <lua.hpp>

namespace yq::lua {

    boolean_x           boolean(lua_State*l, int n)
    {
        if(!l)
            return errors::lua_null();
        return static_cast<bool>(lua_toboolean(l, n));
    }

    boolean_x           boolean(lua_State* l, int n, table_k, const char*key)
    {
        if(!l)
            return errors::lua_null();
        if(!key)
            return errors::null_pointer();
        if(!*key)
            return errors::bad_argument();

        lua_getfield(l, n, key);
        auto ret = boolean(l, -1);
        _pop(l);
        return ret;
    }

    boolean_x           boolean(lua_State*l, global_k, const char* key)
    {
        if(!l)
            return errors::lua_null();
        if(!key)
            return errors::null_pointer();
        if(!*key)
            return errors::bad_argument();

        lua_getglobal(l, key);

        auto ret = boolean(l, -1);
        _pop(l);
        return ret;
    }

    boolean_x           boolean(lua_State* l, upvalue_k, int n)
    {
        if((n<0) || (n>MAX_UPVALUES))
            return errors::bad_argument();
        return boolean(l, lua_upvalueindex(n));
    }
    
    double_x            double_(lua_State*l, int n)
    {
        if(!l)
            return errors::lua_null();
        int success    = 0;
        double  v   = lua_tonumberx(l, n, &success);
        if(!success)
            return errors::lua_not_number();
        return v;
    }
    
    double_x            double_(lua_State* l, int n, table_k, const char* key)
    {
        if(!l)
            return errors::lua_null();
        if(!key)
            return errors::null_pointer();
        if(!*key)
            return errors::bad_argument();

        lua_getfield(l, n, key);
        auto ret = double_(l, -1);
        _pop(l);
        return ret;
    }

    double_x            double_(lua_State* l, global_k, const char* key)
    {
        if(!l)
            return errors::lua_null();
        if(!key)
            return errors::null_pointer();
        if(!*key)
            return errors::bad_argument();

        lua_getglobal(l, key);
        auto ret = double_(l, -1);
        _pop(l);
        return ret;
    }

    double_x            double_(lua_State*l, upvalue_k, int n)
    {
        if((n<0) || (n>MAX_UPVALUES))
            return errors::bad_argument();
        return double_(l, lua_upvalueindex(n));
    }

    integer_x   _enumeration(lua_State*l, int n, const EnumDef& eDef, const TypeMeta&tm)
    {
        if(!l)
            return errors::lua_null();
        switch(lua_type(l,n)){
        case LUA_TSTRING:
            return eDef.value_of(lua_tostring(l,n));
        case LUA_TNUMBER:
            return integer(l, n);
        case LUA_TTABLE:
            if(_meta(l,n,TYPE) != &tm)
                return errors::bad_argument();
            return _enum(l,n);
        default:
            return errors::bad_argument();
        }
    }

    integer_x             integer(lua_State* l, int n)
    {
        if(!l)
            return errors::lua_null();
        int success    = 0;
        int  v   = lua_tointegerx(l, n, &success);
        if(!success)
            return errors::lua_not_number();
        return v;
    }

    integer_x       integer(lua_State* l, int n, table_k, const char* key)
    {
        if(!l)
            return errors::lua_null();
        if(!key)
            return errors::null_pointer();
        if(!*key)
            return errors::bad_argument();
            
        lua_getfield(l, n, key);
        auto x = integer(l, -1);
        _pop(l);
        return x;
    }
    

    integer_x             integer(lua_State* l, global_k, const char* key)
    {
        if(!l)
            return errors::lua_null();
        if(!key)
            return errors::null_pointer();
        if(!*key)
            return errors::bad_argument();

        lua_getglobal(l, key);
        auto ret = integer(l, -1);
        _pop(l);
        return ret;
    }
    
    integer_x             integer(lua_State* l, upvalue_k, int n)
    {
        if((n<0) || (n>MAX_UPVALUES))
            return errors::bad_argument();
        return integer(l, lua_upvalueindex(n));
    }

    static meta_x   meta_by_number(lua_State* l, int n)
    {
        Meta::id_t  i   = lua_tointeger(l, n);
        if(!i)  
            return errors::lua_not_meta();
        const Meta*m    = Meta::lookup(i);
        if(!m)
            return errors::lua_not_meta();
        return m;
    }

    static meta_x   meta_by_table(lua_State* l, int n)
    {
        const Meta* m   = _meta(l, n);
        if(!m)
            return errors::lua_not_meta();
        return m;
    }

    meta_x  meta(lua_State* l, int n)
    {
        if(!l)
            return errors::lua_null();

        switch(lua_type(l,n)){
        case LUA_TNUMBER:
            return meta_by_number(l, n);
        case LUA_TTABLE:
            return meta_by_table(l, n);
        default:
            return errors::lua_not_meta();
        }
    }


    meta_x  meta(lua_State*l, int n, table_k, const char* key)
    {
        if(!l)
            return errors::lua_null();
        if(!key)
            return errors::null_pointer();
        if(!*key)
            return errors::bad_argument();

        lua_getfield(l, n, key);
        auto ret   = meta(l, -1);
        _pop(l);
        return ret;
    }
    
    meta_x  meta(lua_State*l, global_k, const char* key)
    {
        if(!l)
            return errors::lua_null();
        if(!key)
            return errors::null_pointer();
        if(!*key)
            return errors::bad_argument();

        lua_getglobal(l, key);
        auto ret            = meta(l, -1);
        _pop(l);
        return ret;
    }
    
    meta_x  meta(lua_State*l, upvalue_k, int n)
    {
        if((n<0) || (n>MAX_UPVALUES))
            return errors::bad_argument();
        return meta(l, lua_upvalueindex(n));
    }

    object_ptr_x        object(lua_State* l, int n)
    {
        if(!l)
            return errors::lua_null();
            
        if(!lua_istable(l, n))
            return errors::lua_not_table();
            
        XFlags  flags               = _flags(l, n);
        if(flags(X::Meta))
            return errors::lua_is_meta();
        if(flags(X::Const))
            return errors::lua_const_object();

        const ObjectMeta*   meta    = _meta(l, n, OBJECT);
        if(!meta)
            return errors::lua_no_meta();

        Object* obj                 = _object(l, n);
        if(!obj)
            return errors::lua_null_pointer();
        if(meta != &obj->metaInfo())    // sanity check
            return errors::lua_meta_mismatch();
        
        return obj;
    }

    object_cptr_x       object(lua_State* l, int n, const_k)
    {
        if(!l)
            return errors::lua_null();
            
        if(!lua_istable(l, n))
            return errors::lua_not_table();
            
        XFlags  flags               = _flags(l, n);
        if(flags(X::Meta))
            return errors::lua_is_meta();

        const ObjectMeta*   meta    = _meta(l, n, OBJECT);
        if(!meta)
            return errors::lua_no_meta();

        const Object*       obj     = _object(l, n);
        if(!obj)
            return errors::lua_null_pointer();
        if(meta != &obj->metaInfo())    // sanity check
            return errors::lua_meta_mismatch();

        return obj;
    }

    object_ptr_x        object(lua_State* l, int n, const ObjectMeta& om)
    {
        if(!l)
            return errors::lua_null();
            
        if(!lua_istable(l, n))
            return errors::lua_not_table();

        XFlags  flags               = _flags(l, n);
        if(flags(X::Const))
            return errors::lua_const_object();
        if(flags(X::Meta))
            return errors::lua_is_meta();
            
        const ObjectMeta*   meta    = _meta(l, n, OBJECT);
        if(!meta)
            return errors::lua_no_meta();
            
        if(!meta->is_base(om))
            return errors::lua_wrong_object_type();

        Object* obj                 = _object(l, n);
        if(!obj)
            return errors::lua_null_pointer();
        if(meta != &obj->metaInfo())    // sanity check
            return errors::lua_meta_mismatch();
        
            
        return obj;
    }

    object_cptr_x       object(lua_State* l, int n, const ObjectMeta& om, const_k)
    {
        if(!l)
            return errors::lua_null();
            
        if(!lua_istable(l, n))
            return errors::lua_not_table();

        XFlags  flags               = _flags(l, n);
        if(flags(X::Meta))
            return errors::lua_is_meta();

            
        const ObjectMeta*   meta    = _meta(l, n, OBJECT);
        if(!meta)
            return errors::lua_no_meta();

        if(!meta->is_base(om))
            return errors::lua_wrong_object_type();

        const Object*       obj     = _object(l, n);
        if(!obj)
            return errors::lua_null_pointer();
        if(meta != &obj->metaInfo())    // sanity check
            return errors::lua_meta_mismatch();
        return obj;
    }
    
    object_ptr_x        object(lua_State*l, global_k, const char*key)
    {
        if(!l)
            return errors::lua_null();
        if(!key)
            return errors::null_pointer();
        if(!*key)
            return errors::bad_argument();

        lua_getglobal(l, key);
        auto ret            = object(l, -1);
        _pop(l);
        return ret;
    }
    
    object_cptr_x       object(lua_State*l, global_k, const char*key, const_k)
    {
        if(!l)
            return errors::lua_null();
        if(!key)
            return errors::null_pointer();
        if(!*key)
            return errors::bad_argument();

        lua_getglobal(l, key);
            
        auto ret            = object(l, -1, CONST);
        _pop(l);
        return ret;
    }
    
    object_ptr_x        object(lua_State*l, global_k, const char*key, const ObjectMeta&om)
    {
        if(!l)
            return errors::lua_null();
        if(!key)
            return errors::null_pointer();
        if(!*key)
            return errors::bad_argument();

        lua_getglobal(l, key);
            
        auto ret            = object(l, -1, om);
        _pop(l);
        return ret;
    }
    
    object_cptr_x       object(lua_State*l, global_k, const char*key, const ObjectMeta&om, const_k)
    {
        if(!l)
            return errors::lua_null();
        if(!key)
            return errors::null_pointer();
        if(!*key)
            return errors::bad_argument();
        lua_getglobal(l, key);
            
        auto ret            = object(l, -1, om, CONST);
        _pop(l);
        return ret;
    }

    object_ptr_x        object(lua_State* l, upvalue_k, int n)
    {
        if((n<0) || (n>MAX_UPVALUES))
            return errors::bad_argument();
        return object(l, lua_upvalueindex(n));
    }

    object_cptr_x       object(lua_State* l, upvalue_k, int n, const_k)
    {
        if((n<0) || (n>MAX_UPVALUES))
            return errors::bad_argument();
        return object(l, lua_upvalueindex(n), CONST);
    }

    object_ptr_x        object(lua_State* l, upvalue_k, int n, const ObjectMeta& om)
    {
        if((n<0) || (n>MAX_UPVALUES))
            return errors::bad_argument();
        return object(l, lua_upvalueindex(n), om);
    }
    
    object_cptr_x       object(lua_State* l, upvalue_k, int n, const ObjectMeta& om, const_k)
    {
        if((n<0) || (n>MAX_UPVALUES))
            return errors::bad_argument();
        return object(l, lua_upvalueindex(n), om, CONST);
    }
    
    static object_meta_x    object_meta_by_number(lua_State*l, int n)
    {
        const ObjectMeta* tm  = ObjectMeta::find(lua_tointeger(l,n));
        if(!tm)
            return errors::bad_argument();
        return tm;
    }
    
    static object_meta_x    object_meta_by_string(lua_State*l, int n)
    {
        const char*z    = lua_tostring(l, n);
        if(!n)
            return errors::bad_argument();
        const ObjectMeta* tm  = ObjectMeta::find(z);
        if(!tm)
            return errors::bad_argument();
        return tm;
    }

    static object_meta_x    object_meta_by_table(lua_State*l, int n)
    {
        const Meta* m   = _meta(l, n);
        if(!m)
            return errors::lua_no_meta();
        if(!m->is_object())
            return errors::lua_not_typed_data();
        return static_cast<const ObjectMeta*>(m);
    }

    object_meta_x           object_meta(lua_State*l, int n)
    {
        if(!l)
            return errors::lua_null();

        switch(lua_type(l,n)){
        case LUA_TSTRING:
            return object_meta_by_string(l, n);
        case LUA_TNUMBER:
            return object_meta_by_number(l, n);
        case LUA_TTABLE:
            return object_meta_by_table(l, n);
        default:
            return errors::lua_not_meta();
        }
    }
    
    object_meta_x           object_meta(lua_State*l, global_k, const char* key)
    {
        if(!l)
            return errors::lua_null();
        if(!key)
            return errors::null_pointer();
        if(!*key)
            return errors::bad_argument();
        lua_getglobal(l, key);

        auto ret            = object_meta(l, -1);
        _pop(l);
        return ret;
    }
    
    object_meta_x           object_meta(lua_State*l, upvalue_k, int n)
    {
        if((n<0) || (n>MAX_UPVALUES))
            return errors::bad_argument();
        return object_meta(l, lua_upvalueindex(n));
    }
    
    
    void_ptr_x          pointer(lua_State* l, int n)
    {
        if(!l)
            return errors::lua_null();
        return lua_touserdata(l, -1);
    }

    void_ptr_x          pointer(lua_State* l, int n, table_k, const char*key)
    {
        if(!l)
            return errors::lua_null();
        if(!key)
            return errors::null_pointer();
        if(!*key)
            return errors::bad_argument();
        
        lua_getfield(l, n, key);
        auto ret = pointer(l, -1);
        _pop(l);
        return ret;
    }

    void_ptr_x          pointer(lua_State* l, global_k, const char*key)
    {
        if(!l)
            return errors::lua_null();
        if(!key)
            return errors::null_pointer();
        if(!*key)
            return errors::bad_argument();
        
        lua_getglobal(l, key);
        auto ret = pointer(l, -1);
        _pop(l);
        return ret;
    }

    string_x        string(lua_State*l, int n)
    {
        if(!l)
            return errors::lua_null();
        size_t sz = 0;
        const char* v   = lua_tolstring(l, n, &sz);
        if(!v)
            return errors::lua_bad_type();
        return std::string(v);
    }

    string_x            string(lua_State*l, global_k, const char*key)
    {
        if(!l)
            return errors::lua_null();
        if(!key)
            return errors::null_pointer();
        if(!*key)
            return errors::bad_argument();
        
        lua_getglobal(l, key);
            
        auto x              = string(l, -1);
        string_x    ret;
        if(x){
            ret     = *x;
        } else {
            ret     = unexpected(x.error());
        }
        
        _pop(l);
        return ret;
    }

    string_x       string(lua_State*l, upvalue_k, int n)
    {
        if((n<0) || (n>MAX_UPVALUES))
            return errors::bad_argument();
        return string(l, lua_upvalueindex(n));
    }
    
    static type_meta_x type_meta_by_string(lua_State* l, int n)
    {
        const char*z    = lua_tostring(l, n);
        if(!n)
            return errors::bad_argument();
        const TypeMeta* tm  = TypeMeta::find(z);
        if(!tm)
            return errors::bad_argument();
        return tm;
    }

    static type_meta_x type_meta_by_number(lua_State* l, int n)
    {
        const TypeMeta* tm  = TypeMeta::find(lua_tointeger(l,n));
        if(!tm)
            return errors::bad_argument();
        return tm;
    }

    static type_meta_x type_meta_by_table(lua_State* l, int n)
    {
        const Meta* m   = _meta(l, n);
        if(!m)
            return errors::lua_no_meta();
        if(!m->is_type())
            return errors::lua_not_typed_data();
        return static_cast<const TypeMeta*>(m);
    }

    type_meta_x     type_meta(lua_State*l, int n)
    {
        if(!l)
            return errors::lua_null();

        switch(lua_type(l,n)){
        case LUA_TSTRING:
            return type_meta_by_string(l, n);
        case LUA_TNUMBER:
            return type_meta_by_number(l, n);
        case LUA_TTABLE:
            return type_meta_by_table(l, n);
        default:
            return errors::lua_not_meta();
        }
    }
    
    type_meta_x     type_meta(lua_State*l, global_k, const char* key)
    {
        if(!l)
            return errors::lua_null();
        if(!key)
            return errors::null_pointer();
        if(!*key)
            return errors::bad_argument();
        
        lua_getglobal(l, key);
        auto ret = type_meta(l, -1);
        _pop(l);
        return ret;
    }
    
    type_meta_x     type_meta(lua_State*l, upvalue_k, int n)
    {
        if((n<0) || (n>MAX_UPVALUES))
            return errors::bad_argument();
        return type_meta(l, lua_upvalueindex(n));
    }
    

    any_x  value(lua_State* l, int n)
    {
        if(!l)
            return errors::lua_null();

        // TODO
        return errors::todo();
    }

    any_x  value(lua_State* l, upvalue_k, int n)
    {
        if((n<0) || (n>MAX_UPVALUES))
            return errors::bad_argument();
        return value(l, lua_upvalueindex(n));
    }

    void_ptr_x          voidptr(lua_State* l, int n)
    {
        if(!l)
            return errors::lua_null();
        if(!lua_islightuserdata(l, n))
            return errors::lua_bad_type();
        return lua_touserdata(l,n);
    }

    void_ptr_x          voidptr(lua_State*l, global_k, const char*key)
    {
        if(!l)
            return errors::lua_null();
        if(!key)
            return errors::null_pointer();
        if(!*key)
            return errors::bad_argument();
        
        lua_getglobal(l, key);
            
        auto ret            = voidptr(l, -1);
        _pop(l);
        return ret;
    }

    void_ptr_x          voidptr(lua_State* l, upvalue_k, int n)
    {
        if((n<0) || (n>MAX_UPVALUES))
            return errors::bad_argument();
        return voidptr(l, lua_upvalueindex(n));
    }
}
