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
    class SqlQuery : public SqlStatement, trait::not_moveable, trait::not_copyable {
    public:
    
        SqlQuery(SqlLite&, std::string_view, bool isPersistent=true);
        ~SqlQuery();
        
        
    };
    
}
