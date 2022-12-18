////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/preamble.hpp>
#include <basic/trait/not_moveable.hpp>
#include <basic/trait/not_copyable.hpp>
#include <span>
#include <basic/SqlStatement.hpp>

struct sqlite3;
struct sqlite3_stmt;

namespace yq {
    
    /*! \brief SQL "Query" class

        Helper to query the sqlite database.  Construction with SQL is mandatory.
        
        \note COLUMNS & PARAMETERS are 1-based, so they go 1...N
    */
    template <typename S>
    class SqlQueryImpl : public S, trait::not_moveable, trait::not_copyable {
    public:
    
        static_assert(std::is_base_of_v<SqlStatement, S>);
    
        SqlQueryImpl(SqlLite&db, std::string_view sql, bool isPersistent=true)
        {
            SqlStatement::_database(db);
            SqlStatement::_prepare(sql, isPersistent);
        }
        
        ~SqlQueryImpl()
        {
            SqlStatement::_destroy();
        }
        
    };
    
}
