////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

struct lua_State;

#include <system_error>
#include <yq/keywords.hpp>
#include <yq/typedef/expected.hpp>

namespace yq {
    class LuaVM;
}

namespace yq::lua {

    static constexpr const char*        VM      = "**vm";

    /*
        LUA helpers in this file
        
        
        Stack... note, number is as pushed on the stack, so use negatives to get 
        the last item pushed (ie -1)
    */
    std::error_code     errored(int);
    
    boolean_x           boolean(lua_State*, global_k, const char*);
    boolean_x           boolean(lua_State*, stack_k, int);
    
    double_x            double_(lua_State*, global_k, const char*);
    double_x            double_(lua_State*, stack_k, int);

    int64_x             integer(lua_State*, global_k, const char*);
    int64_x             integer(lua_State*, stack_k, int);

    //! Returns user data as a pointer (may or may not be lightweight)
    void_ptr_x          pointer(lua_State*, global_k, const char*);

    //! Returns user data as a pointer (may or may not be lightweight)
    void_ptr_x          pointer(lua_State*, stack_k, int);
    
    std::error_code     push(lua_State*, bool);
    std::error_code     push(lua_State*, double);
    std::error_code     push(lua_State*, int64_t);
    std::error_code     push(lua_State*, std::string_view);
    std::error_code     push(lua_State*, void*);
    
    std::error_code     set(lua_State*, global_k, const char*, bool);
    std::error_code     set(lua_State*, global_k, const char*, double);
    std::error_code     set(lua_State*, global_k, const char*, int64_t);
    std::error_code     set(lua_State*, global_k, const char*, std::string_view);
    std::error_code     set(lua_State*, global_k, const char*, void*);

    //! Global as a string... 
    string_x            string(lua_State*, global_k, const char*);

    //! Stack value as a string... 
    //! \note This will convert said value to a STRING
    string_view_x       string(lua_State*, stack_k, int);

    std::string_view    typestring(int);

    LuaVM*              vm(lua_State*);

    //! Returns LIGHTWEIGHT user data (only)
    void_ptr_x          voidptr(lua_State*, stack_k, int);

    //! Returns LIGHTWEIGHT user data (only)
    void_ptr_x          voidptr(lua_State*, global_k, const char*);
}
