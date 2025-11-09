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
    

    boolean_x           boolean(lua_State*l, global_k, const char* key)
    {
        if(!l)
            return errors::lua_null();
        if(!key)
            return errors::null_pointer();
        if(!*key)
            return errors::bad_argument();

        if(lua_getglobal(l, key) != LUA_OK)
            return errors::lua_bad_global();
        auto ret = boolean(l, -1);
        lua_pop(l, -1);
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
    
    double_x            double_(lua_State* l, global_k, const char* key)
    {
        if(!l)
            return errors::lua_null();
        if(!key)
            return errors::null_pointer();
        if(!*key)
            return errors::bad_argument();

        if(lua_getglobal(l, key) != LUA_OK)
            return errors::lua_bad_global();
        auto ret = double_(l, -1);
        lua_pop(l, -1);
        return ret;
    }

    double_x            double_(lua_State*l, upvalue_k, int n)
    {
        if((n<0) || (n>MAX_UPVALUES))
            return errors::bad_argument();
        return double_(l, lua_upvalueindex(n));
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

    integer_x             integer(lua_State* l, global_k, const char* key)
    {
        if(!l)
            return errors::lua_null();
        if(!key)
            return errors::null_pointer();
        if(!*key)
            return errors::bad_argument();

        if(lua_getglobal(l, key) != LUA_OK)
            return errors::lua_bad_global();
        auto ret = integer(l, -1);
        lua_pop(l, -1);
        return ret;
    }
    
    integer_x             integer(lua_State* l, upvalue_k, int n)
    {
        if((n<0) || (n>MAX_UPVALUES))
            return errors::bad_argument();
        return integer(l, lua_upvalueindex(n));
    }
    


    object_ptr_x        object(lua_State* l, int n)
    {
        if(!l)
            return errors::lua_null();
            
        if(!lua_istable(l, n))
            return errors::lua_not_table();
            
        XFlags  flags               = _flags(l, n);
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
        if(lua_getglobal(l, key) != LUA_OK)
            return errors::lua_bad_global();
            
        auto ret            = object(l, -1);
        lua_pop(l, -1);
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
        if(lua_getglobal(l, key) != LUA_OK)
            return errors::lua_bad_global();
            
        auto ret            = object(l, -1, CONST);
        lua_pop(l, -1);
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
        if(lua_getglobal(l, key) != LUA_OK)
            return errors::lua_bad_global();
            
        auto ret            = object(l, -1, om);
        lua_pop(l, -1);
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
        if(lua_getglobal(l, key) != LUA_OK)
            return errors::lua_bad_global();
            
        auto ret            = object(l, -1, om, CONST);
        lua_pop(l, -1);
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
    
    void_ptr_x          pointer(lua_State* l, int n)
    {
        if(!l)
            return errors::lua_null();
        return lua_touserdata(l, -1);
    }

    void_ptr_x          pointer(lua_State* l, global_k, const char*key)
    {
        if(!l)
            return errors::lua_null();
        if(!key)
            return errors::null_pointer();
        if(!*key)
            return errors::bad_argument();
        
        if(lua_getglobal(l, key) != LUA_OK)
            return errors::lua_bad_global();
        auto ret = pointer(l, -1);
        lua_pop(l, -1);
        return ret;
    }

    
    string_view_x       string(lua_State*l, int n)
    {
        if(!l)
            return errors::lua_null();
        size_t  sz  = 0;
        const char* v   = lua_tolstring(l, n, &sz);
        if(!v)
            return errors::lua_bad_type();
        return std::string_view(v, sz);
    }

    string_x            string(lua_State*l, global_k, const char*key)
    {
        if(!l)
            return errors::lua_null();
        if(!key)
            return errors::null_pointer();
        if(!*key)
            return errors::bad_argument();
        
        if(lua_getglobal(l, key) != LUA_OK)
            return errors::lua_bad_global();
            
        auto x              = string(l, -1);
        string_x    ret;
        if(x){
            ret     = std::string(*x);
        } else {
            ret     = unexpected(x.error());
        }
        
        lua_pop(l, -1);
        return ret;
    }

    string_view_x       string(lua_State*l, upvalue_k, int n)
    {
        if((n<0) || (n>MAX_UPVALUES))
            return errors::bad_argument();
        return string(l, lua_upvalueindex(n));
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
        
        if(lua_getglobal(l, key) != LUA_OK)
            return errors::lua_bad_global();
            
        auto ret            = voidptr(l, -1);
        lua_pop(l, -1);
        return ret;
    }

    void_ptr_x          voidptr(lua_State* l, upvalue_k, int n)
    {
        if((n<0) || (n>MAX_UPVALUES))
            return errors::bad_argument();
        return voidptr(l, lua_upvalueindex(n));
    }
}
