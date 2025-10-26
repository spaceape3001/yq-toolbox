////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/ErrorDB.hpp>

namespace yq::errors {
    using lua_badglobal             = error_db::entry<"Not a global">;
    using lua_badtype               = error_db::entry<"Not the type expected">;
    using lua_badvm                 = error_db::entry<"Bad LuaVM">;
    using lua_file                  = error_db::entry<"Lua file error">;
    using lua_message               = error_db::entry<"Lua error in message handler">;
    using lua_memory                = error_db::entry<"Lua memory allocation error">;
    using lua_notnumber             = error_db::entry<"Lua value is not, nor could be converted to, a number">;
    using lua_null                  = error_db::entry<"Null LuaState">;
    using lua_runtime               = error_db::entry<"Runtime Lua error">;
    using lua_syntax                = error_db::entry<"Lua syntax error">;
    using lua_unexpected            = error_db::entry<"Unexpected Lua error">;
    using lua_yieldcode             = error_db::entry<"Lua thread/coroutine yielding">;
}
