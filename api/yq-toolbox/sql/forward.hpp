////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstdint>

struct sqlite3;
struct sqlite3_stmt;

namespace yq {
    enum class SQResult : int8_t {
        Error   = -2,
        Busy    = -1,
        Done    = 0,
        Row     = 1
    };
    
    struct QueryUrl;
       //  SQL
    struct SqlStatement;
    class SqlLite;
    template <typename S> class SqlQueryImpl;
    using SqlQuery = SqlQueryImpl<SqlStatement>;
}
