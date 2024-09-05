////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <functional>
#include <yq-toolbox/sql/SqlStatement.hpp>
#include <type_traits>
#include <map>
#include <tuple>

struct sqlite3_stmt;

namespace yq {
    class SqlLite;
    
    /*
        We also need to detangle the sql-helpers (bind/etc) from the container
    */

    /*! \brief Argument sensitive SQL Query
    
        This is a helper to allow the query to be changed based on parameters, 
        but mostly retain the advantages of saving a prepared SQL Query for
        future use.
    */
    template <typename S, typename... Params>
    class SqlQueryMap : public S {
    public:
        static_assert(std::is_base_of_v<SqlStatement, S>);

        using FNSql = std::function<std::string(Params...)>;
        using Args  = std::tuple<Params...>;
        using Map   = std::map<Args, sqlite3_stmt*>;
    
        SqlQueryMap(SqlLite&sl, FNSql fn)
        {
            SqlStatement::_database(sl);
            m_sql   = fn;
        }
        
        void    apply(Params... params)
        {
            Args    key(params...);
            auto [i, ins]           = m_stmts.emplace(Map::value_pair(key));
            if(ins){
                std::string sql     = FNSql(params...);
                i->second           = nullptr;
                SqlStatement::_prepare(i->second, sql, true);
            }
            SqlStatement::m_stmt    = i->second;
        }
        
        ~SqlQueryMap()
        {
            SqlStatement::m_stmt        = nullptr;
            for(auto& i : m_stmts){
                if(i.second)
                    SqlStatement::_kill(i.second);
            }
            m_stmts.clear();
        }
        
    private:
        SqlQueryMap(const SqlQueryMap&) = delete;
        SqlQueryMap(SqlQueryMap&&) = delete;
        SqlQueryMap& operator=(const SqlQueryMap&) = delete;
        SqlQueryMap& operator=(SqlQueryMap&&) = delete;
        
        Map         m_stmts;
        FNSql       m_sql;
    };
}

