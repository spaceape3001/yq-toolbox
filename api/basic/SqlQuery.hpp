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

struct sqlite3_stmt;

namespace yq {
    class SqlLite;
    class ByteArray;
    
    /*! \brief SQL "Query" class

        Helper to query the sqlite database.  Construction with SQL is mandatory.
        
        \note COLUMNS & PARAMETERS are 1-based, so they go 1...N
    */
    class SqlQuery : trait::not_moveable, trait::not_copyable {
    public:
        enum Result {
            Error   = -2,
            Busy    = -1,
            Done    = 0,
            Row     = 1
        };
        
        static bool exec(SqlLite&, const std::string&);
    
        SqlQuery(SqlLite&, std::string_view, bool isPersistent=true);
        ~SqlQuery();
        
        bool                valid() const { return m_stmt != nullptr; }
        sqlite3_stmt*       stmt() const { return m_stmt; }
        std::string_view    sql() const;
        
        //! Reset for a new bind/values
        void                reset();
        
        //! Steps/executes the statement
        Result              step(bool noisy=false);
        
        //! Binds NULL to column
        //! 
        //! \param[in] c    Parameter/column index, starts at ONE
        bool                bind(int col);

        //! Binds a BLOB
        //! \note this data MUST be available until unbind() is called (or reset_all)
        //! 
        //! \param[in] col  Parameter/column index, starts at ONE
        //! \param[in] v    BLOB to push in
        bool                bind(int col, std::span<uint8_t> v);
        
        bool                bind(int col, const void*, size_t);


        //! \brief Binds a Boolean (maps to 0/1)
        //! 
        //! \param[in] col  Parameter/column index, starts at ONE
        //! \param[in] v    Boolean parameter (will be mapped to 0/1)
        bool                bind(int col, bool v);
        //! \brief Binds a double
        //! 
        //! \param[in] col  Parameter/column index, starts at ONE
        bool                bind(int col, double);
        //! \brief Binds an integer
        //! 
        //! \param[in] col  Parameter/column index, starts at ONE
        bool                bind(int col, int);
        
        //! \brief Binds a 64-bit integer
        //! 
        //! \param[in] col  Parameter/column index, starts at ONE
        bool                bind(int col, int64_t);

        //! \brief Binds a 64-bit unsigned integer
        //! 
        //! \param[in] col  Parameter/column index, starts at ONE
        bool                bind(int col, uint64_t);

        
        //! \brief Binds a filesystem path
        //! 
        //! \param[in] col  Parameter/column index, starts at ONE
        bool                bind(int col, const std::filesystem::path&);
        
        //! Binds a TEXT
        //! \note this data MUST be available until unbind() is called (or reset_all)
        //! \param[in] col  Parameter/column index, starts at ONE
        bool                bind(int col, std::string_view);
        bool                bind(int col, const std::string&);
        
        //! \brief Returns the column count
        int                 column_count() const;
        
        //! \brief Gets the name of the column
        //! \param[in] c    Parameter/column index, starts at ONE
        std::string_view    column_name(int c) const;
        
        //! \brief Conviences to is_good(step())
        //bool                exec(bool noisy=true);
        
        //! Returns the last ID (database-connection-wide)
        int64_t             last_id() const;

        //! \brief Result value as double
        //! \param[in] col  Parameter/column index, starts at ONE
        bool                v_bool(int col) const;

        //! \brief Result value as blob
        //! \note COPY this off ASAP if desired to be kept or passed-along
        //! \param[in] col  Parameter/column index, starts at ONE
        std::span<const uint8_t>  v_blob(int col) const;
        
        ByteArray           v_bytes(int col) const;

        //! \brief Result value as double
        //! \param[in] col  Parameter/column index, starts at ONE
        double              v_double(int col) const;

        //! \brief Result value as integer
        //! \param[in] col  Parameter/column index, starts at ONE
        int                 v_int(int col) const;

        //! \brief Result value as 64-bit integer
        //! \param[in] col  Parameter/column index, starts at ONE
        int64_t             v_int64(int col) const;
        uint64_t            v_uint64(int col) const;

        std::string         v_string(int col) const;

        
        //! \brief Result value as string
        //! \note COPY this off ASAP if desired to be kept or passed-along
        //! \param[in] col  Parameter/column index, starts at ONE
        std::string_view    v_text(int col) const;
        
        struct AutoFinish;
        AutoFinish  af();
        AutoFinish  autoFinish();
    private:
        SqlLite&                 m_db;
        mutable sqlite3_stmt    *m_stmt = nullptr;
    #ifndef NDEBUG
        std::string             m_sql;
    #endif
    };

    struct SqlQuery::AutoFinish : trait::not_copyable {
        AutoFinish(){}
        AutoFinish(AutoFinish&&);
        AutoFinish& operator=(AutoFinish&&);
        ~AutoFinish();
    private:
        friend class SqlQuery;
        SqlQuery*       q = nullptr;
        AutoFinish(SqlQuery* _q);
    };
    
    inline constexpr bool is_good(SqlQuery::Result r)
    {
        return (r==SqlQuery::Done) || (r==SqlQuery::Row);
    }
}
