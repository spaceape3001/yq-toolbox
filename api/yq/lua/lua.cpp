////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "lualua.hpp"
#include "errors.hpp"
#include <yq/errors.hpp>
#include <lua.hpp>

namespace yq::lua {
    boolean_x           boolean(lua_State*l, global_k, const char* key)
    {
        if(!l)
            return errors::lua_null();
        if(!key)
            return errors::null_pointer();
        if(!*key)
            return errors::bad_argument();

        if(lua_getglobal(l, key) != LUA_OK)
            return errors::lua_badglobal();
        auto ret = boolean(l, STACK, -1);
        lua_pop(l, -1);
        return ret;
    }

    boolean_x           boolean(lua_State*l, stack_k, int n)
    {
        if(!l)
            return errors::lua_null();
        return static_cast<bool>(lua_toboolean(l, n));
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
            return errors::lua_badglobal();
        auto ret = double_(l, STACK, -1);
        lua_pop(l, -1);
        return ret;
    }

    double_x            double_(lua_State*l, stack_k, int n)
    {
        if(!l)
            return errors::lua_null();
        int success    = 0;
        double  v   = lua_tonumberx(l, n, &success);
        if(!success)
            return errors::lua_notnumber();
        return v;
    }
    

    //   Lua helpers (FYI, keep in alphabetical order)
    std::error_code     errored(int n)
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
            return errors::lua_yieldcode();
        case LUA_ERRFILE:
            return errors::lua_file();
        default:
            return errors::lua_unexpected();
        }
    }

    int64_x             integer(lua_State* l, global_k, const char* key)
    {
        if(!l)
            return errors::lua_null();
        if(!key)
            return errors::null_pointer();
        if(!*key)
            return errors::bad_argument();

        if(lua_getglobal(l, key) != LUA_OK)
            return errors::lua_badglobal();
        auto ret = integer(l, STACK, -1);
        lua_pop(l, -1);
        return ret;
    }
    
    int64_x             integer(lua_State* l, stack_k, int n)
    {
        if(!l)
            return errors::lua_null();
        int success    = 0;
        int64_t  v   = lua_tointegerx(l, n, &success);
        if(!success)
            return errors::lua_notnumber();
        return v;
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
            return errors::lua_badglobal();
        auto ret = pointer(l, STACK, -1);
        lua_pop(l, -1);
        return ret;
    }
    
    void_ptr_x          pointer(lua_State* l, stack_k, int n)
    {
        if(!l)
            return errors::lua_null();
        return lua_touserdata(l, -1);
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
    
    std::error_code     push(lua_State* l, int64_t v)
    {
        if(!l)
            return errors::lua_null();
        lua_pushinteger(l,v);
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

    std::error_code     set(lua_State*l, global_k, const char* key, bool v)
    {
        if(!l)
            return errors::lua_null();
        if(!key)
            return errors::null_pointer();
        if(!*key)
            return errors::bad_argument();
            
        push(l, v);
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

        push(l, v);
        lua_setglobal(l, key);
        return {};
    }
    
    std::error_code     set(lua_State*l, global_k, const char* key, int64_t v)
    {
        if(!l)
            return errors::lua_null();
        if(!key)
            return errors::null_pointer();
        if(!*key)
            return errors::bad_argument();

        push(l, v);
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

        push(l, v);
        lua_setglobal(l, key);
        return {};
    }
    
    std::error_code     set(lua_State*l, global_k, const char* key, void* v)
    {
        if(!l)
            return errors::lua_null();
        if(!key)
            return errors::null_pointer();
        if(!*key)
            return errors::bad_argument();

        push(l, v);
        lua_setglobal(l, key);
        return {};
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
            return errors::lua_badglobal();
            
        auto x              = string(l, STACK, -1);
        string_x    ret;
        if(x){
            ret     = std::string(*x);
        } else {
            ret     = unexpected(x.error());
        }
        
        lua_pop(l, -1);
        return ret;
    }

    string_view_x       string(lua_State*l, stack_k, int n)
    {
        if(!l)
            return errors::lua_null();
        size_t  sz  = 0;
        const char* v   = lua_tolstring(l, n, &sz);
        if(!v)
            return errors::lua_badtype();
        return std::string_view(v, sz);
    }

    std::string_view    typestring(int n)
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

    LuaVM* vm(lua_State* l)
    {
        void_ptr_x  x = voidptr(l, GLOBAL, VM);
        if(!x)
            return nullptr;
        return (LuaVM*) *x;
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
            return errors::lua_badglobal();
            
        auto ret            = voidptr(l, STACK, -1);
        lua_pop(l, -1);
        return ret;
    }


    //! Returns LIGHTWEIGHT user data (only)
    void_ptr_x          voidptr(lua_State* l, stack_k, int n)
    {
        if(!l)
            return errors::lua_null();
        if(!lua_islightuserdata(l, n))
            return errors::lua_badtype();
        return lua_touserdata(l,n);
    }
}
