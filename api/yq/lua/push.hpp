////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/lua/types.hpp>

namespace yq::lua {
    std::error_code         push(lua_State*, const Any&);
    std::error_code         push(lua_State*, bool);
    std::error_code         push(lua_State*, double);
    std::error_code         push(lua_State*, int);
    std::error_code         push(lua_State*, const_k, const Object*);
    std::error_code         push(lua_State*, Object*);
    std::error_code         push(lua_State*, object_k, const_k, const Object*);
    std::error_code         push(lua_State*, object_k, Object*);
    std::error_code         push(lua_State*, std::nullptr_t);
    std::error_code         push(lua_State*, std::string_view);
    std::error_code         push(lua_State*, void*);
    std::error_code         push(lua_State*, raw_k, void*);
    
    std::error_code         push(lua_State*, FNLuaCallback);
    std::error_code         push(lua_State*, FNLuaCallback, size_t);
}
