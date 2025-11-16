////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/lua/extract.hpp>
#include <yq/lua/handler.hpp>
#include <yq/lua/info.hpp>
#include <yq/lua/push.hpp>
#include <yq/lua/register.hpp>
#include <yq/lua/set.hpp>
#include <yq/lua/writer.hpp>

namespace yq::lua {
    // Set all KNOWN valid globals into the given lua state machine
    void    configure(lua_State*);

    bool    has(lua_State* l, global_k, const char* key);

    Stream* stream(lua_State*, error_k);
    Stream* stream(lua_State*, output_k);
    Stream* stream(lua_State*, warning_k);

    // LuaVM from the lua state (could be null if unavailble)
    LuaVM*  vm(lua_State*);
    
    void    initialize();
 
    void    complaint(lua_State*l, std::string_view txt);
    void    warning(lua_State*l, std::string_view txt);
}

namespace yq {
    void    lua_initialize();
}
