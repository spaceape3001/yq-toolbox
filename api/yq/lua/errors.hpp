////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/ErrorDB.hpp>

namespace yq::errors {
    using lua_badvm                 = error_db::entry<"Bad LuaVM">;
    using lua_file                  = error_db::entry<"Lua file error">;
    using lua_message               = error_db::entry<"Lua error in message handler">;
    using lua_memory                = error_db::entry<"Lua memory allocation error">;
    using lua_runtime               = error_db::entry<"Runtime Lua error">;
    using lua_syntax                = error_db::entry<"Lua syntax error">;
    using lua_unexpected            = error_db::entry<"Unexpected Lua error">;
    using lua_yieldcode             = error_db::entry<"Lua thread/coroutine yielding">;
}
