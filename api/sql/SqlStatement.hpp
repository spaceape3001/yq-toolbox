////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <sql/preamble.hpp>
#include <0/trait/not_copyable.hpp>
#include <span>


namespace yq {
    enum class SQResult : int8_t {
        Error   = -2,
        Busy    = -1,
        Done    = 0,
        Row     = 1
    };

    inline constexpr bool is_good(SQResult r)
    {
        return (r==SQResult::Done) || (r==SQResult::Row);
    }

    /*! \brief Basic API for SQL Statements
    
        This is the basic SQL helpers.
    *//*
        Due to evolving the API, we needed to split the SqlQuery up, bringing the basics 
        to a common class, thus SqlStatement was chosen w/o getting really weird on the 
        naming scheme.
    */
    class SqlStatement {
    public:

        class AutoFinish;
        
        static bool             exec(SqlLite&, const std::string&);
        
        
        
        AutoFinish  af();
        AutoFinish  autoFinish();

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

        //! Sqlite3 database pointer
        sqlite3*            database() const { return m_db; }
        
        /*! \brief Returns the last ID (database-connection-wide)
        
            \note this will NOT work if the database-pointer is NULL
        */
        int64_t             last_id() const;

                //! Reset for a new bind/values
        void                reset();
        
        std::string_view    sql() const;

        //! Steps/executes the statement
        SQResult            step(bool noisy=false);

        //! Sqlite3 statement pointer
        sqlite3_stmt*       stmt() const { return m_stmt; }

        //! TRUE if this has a statement
        bool                valid() const { return m_stmt != nullptr; }

        //! \brief Conviences to is_good(step())
        //bool                exec(bool noisy=true);
        

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

        SqlStatement(sqlite3* _db=nullptr, sqlite3_stmt* _stmt=nullptr);
        ~SqlStatement();

    protected:

        sqlite3*            m_db;
        sqlite3_stmt*       m_stmt;

        void    _database(SqlLite&);
        
        /*! \brief Finalizing Destructor
        
            This destroys the statement and sets the points to null
        */
        void    _destroy();
        
        static void     _kill(sqlite3_stmt*);

        /*! \brief Prepares the statement
        
            This routine assumes m_db is correct, uses it to prepare a statement.
            
            \param[in] isPersistent set to make the statement persistent (ie, used a LOT...good default)
        */
        bool    _prepare(std::string_view sql, bool isPersistent=true);

        bool    _prepare(sqlite3_stmt*&, std::string_view sql, bool isPersistent=true);
    };


    class SqlStatement::AutoFinish : not_copyable {
    public:
        AutoFinish(){}
        AutoFinish(AutoFinish&&);
        AutoFinish& operator=(AutoFinish&&);
        ~AutoFinish();
    private:
        friend class SqlStatement;
        SqlStatement*       q = nullptr;
        AutoFinish(SqlStatement* _q) : q(_q) {}
    };
}
