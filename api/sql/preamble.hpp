////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/preamble.hpp>

struct sqlite3;
struct sqlite3_stmt;

namespace yq {
        //  SQL
    struct SqlStatement;
    class SqlLite;
    template <typename S> class SqlQueryImpl;
    using SqlQuery = SqlQueryImpl<SqlStatement>;
    
}
