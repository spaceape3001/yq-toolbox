////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <basic/Set.hpp>
#include <basic/SqlError.hpp>
#include <basic/SqlLite.hpp>
#include <basic/SqlLogging.hpp>
#include <basic/SqlQuery.hpp>
#include <sqlite3.h>

namespace yq {

    bool    SqlLite::config_sqlite()
    {
        sqlite3_config(SQLITE_CONFIG_MULTITHREAD );
        return true;
    }

    int     SqlLite::tables_callback(void* ret, int, char**argv, char**)  
    {
        (*(string_set_t*) ret) << argv[0];
        return 0;
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    SqlLite::SqlLite() : m_database(nullptr) 
    {
    }
    
    SqlLite::~SqlLite()
    {
        close();
    }
    
    void        SqlLite::checkpoint()
    {
        sqlite3_wal_checkpoint_v2(m_database, nullptr, SQLITE_CHECKPOINT_FULL, nullptr, nullptr);
    }

    void        SqlLite::close()
    {
        if(m_database != nullptr){
            sqlite3_close_v2(m_database);
            m_database  = nullptr;
        }
    }

    bool        SqlLite::has_table(std::string_view s) const
    {
        SqlQuery    sql((SqlLite&) *this, "SELECT COUNT(1) FROM sqlite_master WHERE type='table' AND name=?");
        sql.bind(1, s);
        if(sql.step() == SqlQuery::Row){
            return sql.v_bool(1);
        } else
            return false;
    }

    bool        SqlLite::is_open() const
    {
        return m_database != nullptr;
    }
    
    bool        SqlLite::open(const std::filesystem::path& file, int flags)
    {
        if(is_open())
            return false;
        if(file.empty())
            return false;
            
        [[maybe_unused]] static bool fConfig = config_sqlite();
            
        int     r;
        if(flags){
            r = sqlite3_open_v2(file.c_str(), &m_database, flags, nullptr);
        } else {
            r = sqlite3_open(file.c_str(), &m_database);
        }
        
        if(r != SQLITE_OK){
            dbError << "Database (" << file << ") failed to open: " << SqlError(r);
            m_database = nullptr;
            return false;
        }
        
        sqlite3_extended_result_codes(m_database, 1);
        m_file  = file;
        return true;
    }
    
    
    string_set_t    SqlLite::tables() const
    {
        string_set_t    ret;
        if(m_database){
            char* zErrMsg   = nullptr;
            if(sqlite3_exec(m_database, "SELECT name FROM sqlite_master WHERE type='table'", 
                SqlLite::tables_callback, &ret, &zErrMsg) != SQLITE_OK
            ){
                dbError << "SqlLite::tables() : " << zErrMsg;
                sqlite3_free(zErrMsg);
            }
        }
        return ret;
    }
    
}
