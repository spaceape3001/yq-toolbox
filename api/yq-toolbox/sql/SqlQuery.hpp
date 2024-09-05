////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <span>
#include <yq-toolbox/sql/forward.hpp>
#include <yq-toolbox/sql/SqlStatement.hpp>

namespace yq {
    
    /*! \brief SQL "Query" class

        Helper to query the sqlite database.  Construction with SQL is mandatory.
        
        \note COLUMNS & PARAMETERS are 1-based, so they go 1...N
    */
    template <typename S>
    class SqlQueryImpl : public S {
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
        
        SqlQueryImpl(const SqlQueryImpl&) = delete;
        SqlQueryImpl(SqlQueryImpl&&) = delete;
        SqlQueryImpl& operator=(const SqlQueryImpl&) = delete;
        SqlQueryImpl& operator=(SqlQueryImpl&&) = delete;
    };
    
}
