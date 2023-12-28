////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <sql/preamble.hpp>
#include <0/trait/not_moveable.hpp>
#include <0/trait/not_copyable.hpp>
#include <span>
#include <sql/SqlStatement.hpp>


namespace yq {
    
    /*! \brief SQL "Query" class

        Helper to query the sqlite database.  Construction with SQL is mandatory.
        
        \note COLUMNS & PARAMETERS are 1-based, so they go 1...N
    */
    template <typename S>
    class SqlQueryImpl : public S, not_moveable, not_copyable {
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
