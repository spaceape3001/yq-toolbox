////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/basic/preamble.hpp>

struct sqlite3;
struct sqlite3_stmt;

namespace yq {
        //  SQL
    struct SqlStatement;
    class SqlLite;
    template <typename S> class SqlQueryImpl;
    using SqlQuery = SqlQueryImpl<SqlStatement>;
    
}
