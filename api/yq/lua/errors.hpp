////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/ErrorDB.hpp>

namespace yq::errors {
    using lua_bad_global                        = error_db::entry<"Not a global">;
    using lua_bad_type                          = error_db::entry<"Not the type expected">;
    using lua_bad_vm                            = error_db::entry<"Bad LuaVM">;
    using lua_file                              = error_db::entry<"Lua file error">;
    using lua_insufficent_upvalue_arguments     = error_db::entry<"Insufficient arguments on stack to push a cfunction closure">;
    using lua_is_meta                           = error_db::entry<"Lua item is a meta type when it's not expected to be">;
    using lua_message                           = error_db::entry<"Lua error in message handler">;
    using lua_memory                            = error_db::entry<"Lua memory allocation error">;
    using lua_meta_mismatch                     = error_db::entry<"Lua table disagrees to the object's meta">;
    using lua_no_meta                           = error_db::entry<"Lua table does not contain a meta field">;
    using lua_const_object                      = error_db::entry<"Lua object is marked const, cannot be returned otherwise">;
    using lua_not_meta                          = error_db::entry<"Lua item is not a meta">;
    using lua_not_number                        = error_db::entry<"Lua value is not, nor could be converted to, a number">;
    using lua_not_object                        = error_db::entry<"Lua item is not an object">;
    using lua_not_table                         = error_db::entry<"Lua item is not a table">;
    using lua_not_typed_data                    = error_db::entry<"Lua item is not typed data">;
    using lua_not_object                        = error_db::entry<"Lua item is not an object">;
    using lua_null                              = error_db::entry<"Null LuaState">;
    using lua_null_pointer                      = error_db::entry<"Lua table does not contain a valid pointer field">;
    using lua_push_failed                       = error_db::entry<"Lua failed to push value">;
    using lua_value_out_of_range                = error_db::entry<"Value is out of range">;
    using lua_runtime                           = error_db::entry<"Runtime Lua error">;
    using lua_syntax                            = error_db::entry<"Lua syntax error">;
    using lua_too_many_upvalues                 = error_db::entry<"Too many upvalues for LUA function">;
    using lua_unexpected                        = error_db::entry<"Unexpected Lua error">;
    using lua_wrong_object_type                 = error_db::entry<"Lua, Wrong object type">;
    using lua_yield_code                        = error_db::entry<"Lua thread/coroutine yielding">;
}
