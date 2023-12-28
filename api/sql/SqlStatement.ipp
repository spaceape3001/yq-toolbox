////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/basic/ByteArray.hpp>
#include <sql/SqlError.hpp>
#include <sql/SqlLite.hpp>
#include <sql/SqlLogging.hpp>
#include <sql/SqlStatement.hpp>
#include <sqlite3.h>

namespace yq {

    bool SqlStatement::exec(SqlLite&db, const std::string& sql)
    {
        if(!db.db()){
            dbError  << "SqlQuery(" << sql << "): Database is CLOSED!";
            return false;
        }
        
        char* zErrMsg   = nullptr;
        if( sqlite3_exec(db.db(), sql.c_str(), nullptr, nullptr, &zErrMsg) != SQLITE_OK){
            dbError << "SqlStatement::exec(" << sql << "): " << zErrMsg;
            sqlite3_free(zErrMsg);
            return false;
        }
        return true;
    }
    
    void    SqlStatement::_kill(sqlite3_stmt*s)
    {
        if(s)
            sqlite3_finalize(s);
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    SqlStatement::SqlStatement(sqlite3* _db, sqlite3_stmt* _stmt) : 
        m_db(_db), m_stmt(_stmt) 
    {
    }

    SqlStatement::~SqlStatement()
    {
    }

    void    SqlStatement::_database(SqlLite&db)
    {
        m_db        = db.db();
    }

    void    SqlStatement::_destroy()
    {
        if(m_stmt)
            sqlite3_finalize(m_stmt);
        m_stmt      = nullptr;
        m_db        = nullptr;
    }

    bool    SqlStatement::_prepare(std::string_view sql, bool isPersistent)
    {
        return _prepare(m_stmt, sql, isPersistent);
    }

    bool    SqlStatement::_prepare(sqlite3_stmt*& stmt, std::string_view sql, bool isPersistent)
    {
        if(!m_db){
            dbError  << "SqlStatement(" << sql << "): Database is CLOSED!";
            return false;
        }

        if(stmt){
            dbError  << "SqlStatement(" << sql << "): Statement already in USE!";
            return false;
        }

        int flags = 0;
        if(isPersistent)
            flags |= SQLITE_PREPARE_PERSISTENT;

        int r = sqlite3_prepare_v3(m_db, sql.data(), sql.size(), flags, &stmt, nullptr);
        if(r== SQLITE_OK) [[likely]]
            return true;
        
        dbError << "SqlStatement(" << sql << "): " << SqlError(r);
        if(stmt){
            sqlite3_finalize(stmt);
            stmt = nullptr;
        }
        return false;
    }

    SqlStatement::AutoFinish  SqlStatement::af()
    {
        return AutoFinish(this);
    }

    SqlStatement::AutoFinish  SqlStatement::autoFinish()
    {
        return AutoFinish(this);
    }

    bool  SqlStatement::bind(int c)
    {
        if(!m_stmt){
            dbError << "SqlStatement::bind(" << c << "): Not properly prepared!";
            return false;
        }
        if(c<1){
            dbError << "SqlStatement::bind(" << c << "): Bad Column Number!";
            return false;
        }
        
        int r = sqlite3_bind_null(m_stmt, c);
        if(r != SQLITE_OK){
            dbError << "SqlStatement::bind(" << c << "): " << SqlError(r);
            return false;
        }
        return true;
    }
    
    bool  SqlStatement::bind(int c, std::span<uint8_t> v)
    {
        if(!m_stmt){
            dbError << "SqlStatement::bind(" << c << "): Not properly prepared!";
            return false;
        }
        if(c<1){
            dbError << "SqlStatement::bind(" << c << "): Bad Column Number!";
            return false;
        }
        
        int r = sqlite3_bind_blob(m_stmt, c, v.data(), v.size(), SQLITE_STATIC);
        if(r != SQLITE_OK){
            dbError << "SqlStatement::bind(" << c << "): " << SqlError(r);
            return false;
        }
        return true;
    }

    bool  SqlStatement::bind(int c, const void* v, size_t cnt)
    {
        if(!m_stmt){
            dbError << "SqlStatement::bind(" << c << "): Not properly prepared!";
            return false;
        }
        if(c<1){
            dbError << "SqlStatement::bind(" << c << "): Bad Column Number!";
            return false;
        }
        
        if(!v){
            dbError << "SqlStatement::bind(" << c << "): Null Pointer!";
            return false;
        }
        
        int r = sqlite3_bind_blob(m_stmt, c, v, cnt, SQLITE_STATIC);
        if(r != SQLITE_OK){
            dbError << "SqlStatement::bind(" << c << "): " << SqlError(r);
            return false;
        }
        return true;
    }
    
    bool  SqlStatement::bind(int c, bool v)
    {
        if(!m_stmt){
            dbError << "SqlStatement::bind(" << c << "): Not properly prepared!";
            return false;
        }
        if(c<1){
            dbError << "SqlStatement::bind(" << c << "): Bad Column Number!";
            return false;
        }
        
        int r = sqlite3_bind_int(m_stmt, c, v ? 1 : 0);
        if(r != SQLITE_OK){
            dbError << "SqlStatement::bind(" << c << "): " << SqlError(r);
            return false;
        }
        return true;
    }
    
    bool  SqlStatement::bind(int c, double v)
    {
        if(!m_stmt){
            dbError << "SqlStatement::bind(" << c << "): Not properly prepared!";
            return false;
        }
        if(c<1){
            dbError << "SqlStatement::bind(" << c << "): Bad Column Number!";
            return false;
        }
        
        int r = sqlite3_bind_double(m_stmt, c, v);
        if(r != SQLITE_OK){
            dbError << "SqlStatement::bind(" << c << "): " << SqlError(r);
            return false;
        }
        return true;
    }
    
    bool  SqlStatement::bind(int c, int v)
    {
        if(!m_stmt){
            dbError << "SqlStatement::bind(" << c << "): Not properly prepared!";
            return false;
        }
        if(c<1){
            dbError << "SqlStatement::bind(" << c << "): Bad Column Number!";
            return false;
        }
        
        int r = sqlite3_bind_int(m_stmt, c, v);
        if(r != SQLITE_OK){
            dbError << "SqlStatement::bind(" << c << "): " << SqlError(r);
            return false;
        }
        return true;
    }
    
    bool  SqlStatement::bind(int c, int64_t v)
    {
        if(!m_stmt){
            dbError << "SqlStatement::bind(" << c << "): Not properly prepared!";
            return false;
        }
        if(c<1){
            dbError << "SqlStatement::bind(" << c << "): Bad Column Number!";
            return false;
        }
        
        int r = sqlite3_bind_int64(m_stmt, c, v);
        if(r != SQLITE_OK){
            dbError << "SqlStatement::bind(" << c << "): " << SqlError(r);
            return false;
        }
        return true;
    }

    bool  SqlStatement::bind(int col, uint64_t v)
    {
        return bind(col, (int64_t) v);
    }

    bool  SqlStatement::bind(int c, const std::filesystem::path&v)
    {
        if(!m_stmt){
            dbError << "SqlStatement::bind(" << c << "): Not properly prepared!";
            return false;
        }
        if(c<1){
            dbError << "SqlStatement::bind(" << c << "): Bad Column Number!";
            return false;
        }
        
        auto    d = v.native();
        int r = sqlite3_bind_text(m_stmt, c, d.data(), d.size(), SQLITE_TRANSIENT);
        if(r != SQLITE_OK){
            dbError << "SqlStatement::bind(" << c << "): " << SqlError(r);
            return false;
        }
        return true;
    }
    
    bool  SqlStatement::bind(int col, const std::string& s)
    {
        return bind(col, (std::string_view) s);
    }

    bool  SqlStatement::bind(int c, std::string_view v)
    {
        if(!m_stmt){
            dbError << "SqlStatement::bind(" << c << "): Not properly prepared!";
            return false;
        }
        if(c<1){
            dbError << "SqlStatement::bind(" << c << "): Bad Column Number!";
            return false;
        }
        
        int r = sqlite3_bind_text(m_stmt, c, v.data(), v.size(), SQLITE_STATIC);
        if(r != SQLITE_OK){
            dbError << "SqlStatement::bind(" << c << "): " << SqlError(r);
            return false;
        }
        return true;
    }
    
    int                 SqlStatement::column_count() const
    {
        if(!m_stmt)
            return 0;
        return sqlite3_column_count(m_stmt);
    }
    

    std::string_view    SqlStatement::column_name(int i) const
    {
        if(!m_stmt)
            return std::string_view();
        const char* zname = sqlite3_column_name(m_stmt, i-1);
        if(zname)
            return std::string_view(zname);
        return std::string_view();
    }

    int64_t  SqlStatement::last_id() const
    {
        if(!m_db)
            return 0;
        return sqlite3_last_insert_rowid(m_db);
    }
    
    void  SqlStatement::reset()
    {
        if(m_stmt){
            sqlite3_reset(m_stmt);
            sqlite3_clear_bindings(m_stmt);
        }
    }

    std::string_view    SqlStatement::sql() const
    {
        if(m_stmt){
            return sqlite3_sql(m_stmt);
        } else
            return std::string_view();
    }

    SQResult SqlStatement::step(bool noisy)
    {
        if(!m_stmt){
            dbError <<"SqlStatement::step(): Calling on an uninitalized statement!";
            return SQResult::Error;
        }
        
        int r   = sqlite3_step(m_stmt);
        switch(r){
        case SQLITE_OK:
        case SQLITE_DONE:
            return SQResult::Done;
        case SQLITE_ROW:
            return SQResult::Row;
        case SQLITE_BUSY:
            if(noisy){
                dbError << "SqlStatement::step(): BUSY, try again later.";
            }
            return SQResult::Busy;
        default:
            if(noisy && m_db){
                r   = sqlite3_extended_errcode(m_db);
                dbError << "SqlStatement::step(\"" << sql() << "\"): " << SqlError{r} << "\n" << sqlite3_errmsg(m_db);
            }
            return SQResult::Error;
        }
    }


    bool                SqlStatement::v_bool(int c) const
    {
        if(!m_stmt)
            return false;
        return sqlite3_column_int(m_stmt, c-1) ? true : false;
    }
    
    std::span<const uint8_t>       SqlStatement::v_blob(int c) const
    {
        if(!m_stmt)
            return {};
        const uint8_t*  data = (const uint8_t*) sqlite3_column_blob(m_stmt, c-1);
        size_t          sz  = sqlite3_column_bytes(m_stmt, c-1);
        return std::span<const uint8_t>( data, sz );
    }
    
    ByteArray           SqlStatement::v_bytes(int c) const
    {
        const char*  data = (const char*) sqlite3_column_blob(m_stmt, c-1);
        size_t          sz  = sqlite3_column_bytes(m_stmt, c-1);
        return ByteArray( data, sz );
    }

    double              SqlStatement::v_double(int c) const
    {
        if(!m_stmt)
            return 0.0;
        return sqlite3_column_double(m_stmt, c-1);
    }
    
    int                 SqlStatement::v_int(int c) const
    {
        if(!m_stmt)
            return 0;
        return sqlite3_column_int(m_stmt, c-1);
    }
    
    int64_t             SqlStatement::v_int64(int c) const
    {
        if(!m_stmt)
            return 0;
        return sqlite3_column_int64(m_stmt, c-1);
    }

    std::string         SqlStatement::v_string(int col) const
    {
        return std::string(v_text(col));
    }
    
    std::string_view    SqlStatement::v_text(int c) const
    {
        if(!m_stmt)
            return std::string_view();
        const char* data    = (const char*) sqlite3_column_text(m_stmt, c-1);
        if(!data)
            return std::string_view();
        int  sz = sqlite3_column_bytes(m_stmt, c-1);
        if(data && (sz>0) && !data[sz-1]) // delete final NULL
            --sz;
        return std::string_view(data, sz);
    }

    uint64_t            SqlStatement::v_uint64(int col) const
    {
        return (uint64_t) v_int64(col);
    }
    
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


    SqlStatement::AutoFinish::AutoFinish(AutoFinish&&mv) : q(mv.q)
    {
        mv.q    = nullptr;
    }
    
    SqlStatement::AutoFinish& SqlStatement::AutoFinish::operator=(AutoFinish&&mv)
    {
        if(this != &mv){
            if(q)
                q -> reset();
            q       = mv.q;
            mv.q    = nullptr;
        }
        return *this;
    }
    
    SqlStatement::AutoFinish::~AutoFinish()
    {
        if(q){
            q -> reset();
            q   = nullptr;
        }
    }
}
