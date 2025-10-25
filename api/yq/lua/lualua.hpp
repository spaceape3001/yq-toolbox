////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

struct lua_State;

#include <system_error>
#include <yq/typedef/expected.hpp>

namespace yq {
    class LuaVM;
}

namespace yq::lua {
    //   Lua helpers (FYI, keep in alphabetical order)
    std::error_code     errored(int);
    std::string_view    typestring(int);
    LuaVM*              vm(lua_State*);
}
