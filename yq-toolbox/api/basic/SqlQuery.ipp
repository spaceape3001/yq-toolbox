////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <basic/ByteArray.hpp>
#include <basic/SqlQuery.hpp>
#include <basic/SqlError.hpp>
#include <basic/SqlLite.hpp>
#include <basic/SqlLogging.hpp>
#include <basic/TextUtils.hpp>
#include <sqlite3.h>

namespace yq {

    bool SqlQuery::exec(SqlLite&db, const std::string& sql)
    {
        char* zErrMsg   = nullptr;
        if( sqlite3_exec(db.db(), sql.c_str(), nullptr, nullptr, &zErrMsg) != SQLITE_OK){
            dbError << "SqlQuery::exec(" << sql << "): " << zErrMsg;
            sqlite3_free(zErrMsg);
            return false;
        }
        return true;
    }


    SqlQuery::SqlQuery(SqlLite&db, std::string_view sql, bool isPersistent) : m_db(db), m_stmt(nullptr)
    {
        if(!db.db()){
            dbError  << "SqlQuery(" << sql << "): Database is CLOSED!";
            return;
        }

    #ifndef NDEBUG
        m_sql   = copy(sql);
    #endif
    
        int flags = 0;
        if(isPersistent)
            flags |= SQLITE_PREPARE_PERSISTENT;
        int r = sqlite3_prepare_v3(db.db(), sql.data(), sql.size(), flags, &m_stmt, nullptr);
        if(r!= SQLITE_OK){
            dbError << "SqlQuery(" << sql << "): " << SqlError(r);
            if(m_stmt){
                sqlite3_finalize(m_stmt);
                m_stmt = nullptr;
            }
        }
    }
    
    //SqlQuery::SqlQuery(SqlQuery&&mv) : m_stmt(mv.m_stmt)
    //{
        //mv.m_stmt    = nullptr;
    //}
    
    SqlQuery::~SqlQuery()
    {
        if(m_stmt){
            sqlite3_finalize(m_stmt);
            m_stmt = nullptr;
        }
    }
    
    //SqlQuery&   SqlQuery::operator=(SqlQuery&&mv)
    //{
        //if(this != &mv){
            //if(m_stmt)
                //sqlite3_finalize(m_stmt);
            //m_stmt  = mv.m_stmt;
            //mv.m_stmt = nullptr;
        //}
        //return *this;
    //}
    
    
    SqlQuery::AutoFinish  SqlQuery::af()
    {
        return AutoFinish(this);
    }

    SqlQuery::AutoFinish  SqlQuery::autoFinish()
    {
        return AutoFinish(this);
    }

    bool  SqlQuery::bind(int c)
    {
        if(!m_stmt){
            dbError << "SqlQuery::bind(" << c << "): Not properly prepared!";
            return false;
        }
        if(c<1){
            dbError << "SqlQuery::bind(" << c << "): Bad Column Number!";
            return false;
        }
        
        int r = sqlite3_bind_null(m_stmt, c);
        if(r != SQLITE_OK){
            dbError << "SqlQuery::bind(" << c << "): " << SqlError(r);
            return false;
        }
        return true;
    }
    
    bool  SqlQuery::bind(int c, std::span<uint8_t> v)
    {
        if(!m_stmt){
            dbError << "SqlQuery::bind(" << c << "): Not properly prepared!";
            return false;
        }
        if(c<1){
            dbError << "SqlQuery::bind(" << c << "): Bad Column Number!";
            return false;
        }
        
        int r = sqlite3_bind_blob(m_stmt, c, v.data(), v.size(), SQLITE_STATIC);
        if(r != SQLITE_OK){
            dbError << "SqlQuery::bind(" << c << "): " << SqlError(r);
            return false;
        }
        return true;
    }

    bool  SqlQuery::bind(int c, const void* v, size_t cnt)
    {
        if(!m_stmt){
            dbError << "SqlQuery::bind(" << c << "): Not properly prepared!";
            return false;
        }
        if(c<1){
            dbError << "SqlQuery::bind(" << c << "): Bad Column Number!";
            return false;
        }
        
        if(!v){
            dbError << "SqlQuery::bind(" << c << "): Null Pointer!";
            return false;
        }
        
        int r = sqlite3_bind_blob(m_stmt, c, v, cnt, SQLITE_STATIC);
        if(r != SQLITE_OK){
            dbError << "SqlQuery::bind(" << c << "): " << SqlError(r);
            return false;
        }
        return true;
    }
    
    bool  SqlQuery::bind(int c, bool v)
    {
        if(!m_stmt){
            dbError << "SqlQuery::bind(" << c << "): Not properly prepared!";
            return false;
        }
        if(c<1){
            dbError << "SqlQuery::bind(" << c << "): Bad Column Number!";
            return false;
        }
        
        int r = sqlite3_bind_int(m_stmt, c, v ? 1 : 0);
        if(r != SQLITE_OK){
            dbError << "SqlQuery::bind(" << c << "): " << SqlError(r);
            return false;
        }
        return true;
    }
    
    bool  SqlQuery::bind(int c, double v)
    {
        if(!m_stmt){
            dbError << "SqlQuery::bind(" << c << "): Not properly prepared!";
            return false;
        }
        if(c<1){
            dbError << "SqlQuery::bind(" << c << "): Bad Column Number!";
            return false;
        }
        
        int r = sqlite3_bind_double(m_stmt, c, v);
        if(r != SQLITE_OK){
            dbError << "SqlQuery::bind(" << c << "): " << SqlError(r);
            return false;
        }
        return true;
    }
    
    bool  SqlQuery::bind(int c, int v)
    {
        if(!m_stmt){
            dbError << "SqlQuery::bind(" << c << "): Not properly prepared!";
            return false;
        }
        if(c<1){
            dbError << "SqlQuery::bind(" << c << "): Bad Column Number!";
            return false;
        }
        
        int r = sqlite3_bind_int(m_stmt, c, v);
        if(r != SQLITE_OK){
            dbError << "SqlQuery::bind(" << c << "): " << SqlError(r);
            return false;
        }
        return true;
    }
    
    bool  SqlQuery::bind(int c, int64_t v)
    {
        if(!m_stmt){
            dbError << "SqlQuery::bind(" << c << "): Not properly prepared!";
            return false;
        }
        if(c<1){
            dbError << "SqlQuery::bind(" << c << "): Bad Column Number!";
            return false;
        }
        
        int r = sqlite3_bind_int64(m_stmt, c, v);
        if(r != SQLITE_OK){
            dbError << "SqlQuery::bind(" << c << "): " << SqlError(r);
            return false;
        }
        return true;
    }

    bool  SqlQuery::bind(int col, uint64_t v)
    {
        return bind(col, (int64_t) v);
    }

    bool  SqlQuery::bind(int c, const std::filesystem::path&v)
    {
        if(!m_stmt){
            dbError << "SqlQuery::bind(" << c << "): Not properly prepared!";
            return false;
        }
        if(c<1){
            dbError << "SqlQuery::bind(" << c << "): Bad Column Number!";
            return false;
        }
        
        auto    d = v.native();
        int r = sqlite3_bind_text(m_stmt, c, d.data(), d.size(), SQLITE_TRANSIENT);
        if(r != SQLITE_OK){
            dbError << "SqlQuery::bind(" << c << "): " << SqlError(r);
            return false;
        }
        return true;
    }
    
    bool  SqlQuery::bind(int col, const std::string& s)
    {
        return bind(col, (std::string_view) s);
    }

    bool  SqlQuery::bind(int c, std::string_view v)
    {
        if(!m_stmt){
            dbError << "SqlQuery::bind(" << c << "): Not properly prepared!";
            return false;
        }
        if(c<1){
            dbError << "SqlQuery::bind(" << c << "): Bad Column Number!";
            return false;
        }
        
        int r = sqlite3_bind_text(m_stmt, c, v.data(), v.size(), SQLITE_STATIC);
        if(r != SQLITE_OK){
            dbError << "SqlQuery::bind(" << c << "): " << SqlError(r);
            return false;
        }
        return true;
    }
    
    int                 SqlQuery::column_count() const
    {
        if(!m_stmt)
            return 0;
        return sqlite3_column_count(m_stmt);
    }
    

    std::string_view    SqlQuery::column_name(int i) const
    {
        if(!m_stmt)
            return std::string_view();
        const char* zname = sqlite3_column_name(m_stmt, i-1);
        if(zname)
            return std::string_view(zname);
        return std::string_view();
    }

    //bool     SqlQuery::exec(bool noisy)
    //{
        //return is_good(step(noisy));
    //}

    int64_t  SqlQuery::last_id() const
    {
        return sqlite3_last_insert_rowid(m_db.db());
    }

    void  SqlQuery::reset()
    {
        if(m_stmt){
            sqlite3_reset(m_stmt);
            sqlite3_clear_bindings(m_stmt);
        }
    }


    std::string_view    SqlQuery::sql() const
    {
        if(m_stmt){
            return sqlite3_sql(m_stmt);
        } else
            return std::string_view();
    }

    SqlQuery::Result SqlQuery::step(bool noisy)
    {
        if(!m_stmt){
            dbError <<"SqlQuery::step(): Calling on an uninitalized statement!";
            return Error;
        }
        
        int r   = sqlite3_step(m_stmt);
        switch(r){
        case SQLITE_OK:
        case SQLITE_DONE:
            return Done;
        case SQLITE_ROW:
            return Row;
        case SQLITE_BUSY:
            if(noisy){
                dbError << "SqlQuery::step(): BUSY, try again later.";
            }
            return Busy;
        default:
            if(noisy){
                r   = sqlite3_extended_errcode(m_db.db());
                dbError << "SqlQuery::step("
                #ifndef NDEBUG
                    << m_sql <<
                #endif
                "): " << SqlError{r} << "\n" << sqlite3_errmsg(m_db.db());
            }
            return Error;
        }
    }

    bool                SqlQuery::v_bool(int c) const
    {
        if(!m_stmt)
            return false;
        return sqlite3_column_int(m_stmt, c-1) ? true : false;
    }
    
    std::span<const uint8_t>       SqlQuery::v_blob(int c) const
    {
        if(!m_stmt)
            return {};
        const uint8_t*  data = (const uint8_t*) sqlite3_column_blob(m_stmt, c-1);
        size_t          sz  = sqlite3_column_bytes(m_stmt, c-1);
        return std::span<const uint8_t>( data, sz );
    }
    
    ByteArray           SqlQuery::v_bytes(int c) const
    {
        const char*  data = (const char*) sqlite3_column_blob(m_stmt, c-1);
        size_t          sz  = sqlite3_column_bytes(m_stmt, c-1);
        return ByteArray( data, sz );
    }

    double              SqlQuery::v_double(int c) const
    {
        if(!m_stmt)
            return 0.0;
        return sqlite3_column_double(m_stmt, c-1);
    }
    
    int                 SqlQuery::v_int(int c) const
    {
        if(!m_stmt)
            return 0;
        return sqlite3_column_int(m_stmt, c-1);
    }
    
    int64_t             SqlQuery::v_int64(int c) const
    {
        if(!m_stmt)
            return 0;
        return sqlite3_column_int64(m_stmt, c-1);
    }

    std::string         SqlQuery::v_string(int col) const
    {
        return std::string(v_text(col));
    }
    
    std::string_view    SqlQuery::v_text(int c) const
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

    uint64_t            SqlQuery::v_uint64(int col) const
    {
        return (uint64_t) v_int64(col);
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    SqlQuery::AutoFinish::AutoFinish(SqlQuery* _q) : q(_q)
    {
    }
    
    SqlQuery::AutoFinish::AutoFinish(AutoFinish&&mv) : q(mv.q)
    {
        mv.q    = nullptr;
    }
    
    SqlQuery::AutoFinish& SqlQuery::AutoFinish::operator=(AutoFinish&&mv)
    {
        if(this != &mv){
            if(q)
                q -> reset();
            q       = mv.q;
            mv.q    = nullptr;
        }
        return *this;
    }
    
    SqlQuery::AutoFinish::~AutoFinish()
    {
        if(q){
            q -> reset();
            q   = nullptr;
        }
    }
}
