////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/keywords.hpp>
#include <yq/lua/keywords.hpp>
#include <yq/lua/types.hpp>

namespace yq::lua {
    std::error_code         set(lua_State*, int, table_k, const char*, bool);
    std::error_code         set(lua_State*, int, table_k, const char*, double);
    std::error_code         set(lua_State*, int, table_k, const char*, int);
    std::error_code         set(lua_State*, int, table_k, const char*, std::string_view);
    std::error_code         set(lua_State*, int, table_k, const char*, const_k, const Object*);
    std::error_code         set(lua_State*, int, table_k, const char*, Object*);
    std::error_code         set(lua_State*, int, table_k, const char*, raw_k, void*);
    std::error_code         set(lua_State*, int, table_k, const char*, FNLuaCallback, size_t n=0);
    std::error_code         set(lua_State*, int, table_k, const char*, FNLuaCallback, std::initializer_list<value_t>);

    std::error_code         set(lua_State*, global_k, const char*, bool);
    std::error_code         set(lua_State*, global_k, const char*, double);
    std::error_code         set(lua_State*, global_k, const char*, int);
    std::error_code         set(lua_State*, global_k, const char*, std::string_view);
    std::error_code         set(lua_State*, global_k, const char*, raw_k, void*);
    std::error_code         set(lua_State*, global_k, const char*, FNLuaCallback, size_t n=0);

}
