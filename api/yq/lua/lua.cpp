////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "lualua.hpp"
#include "errors.hpp"
#include <lua.hpp>

namespace yq::lua {
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
        if(!l)
            return nullptr;
        
        //int t = lua_getglobal(l, "___");
        
            
        //  TODO
        return nullptr;
    }
}
