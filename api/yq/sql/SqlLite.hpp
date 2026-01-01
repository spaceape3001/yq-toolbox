////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/sql/forward.hpp>
#include <yq/typedef/filesystem_path.hpp>
#include <yq/typedef/string_sets.hpp>

struct sqlite3;

namespace yq {
    
    /*! \brief "Connection" to a SQLLite database
    */
    class SqlLite {
    public:
    
        enum {
            ReadOnly        = 0x1,
            ReadWrite       = 0x2,
            Create          = 0x4,
            DeleteOnClose   = 0x8,
            Exclusive       = 0x10,
            AutoProxy       = 0x20,
            Uri             = 0x40,
            Memory          = 0x80,
            MainDB          = 0x100,
            TempDB          = 0x200,
            TransientDB     = 0x400,
            MainJournal     = 0x800,
            TempJournal     = 0x1000,
            SubJournal      = 0x2000,
            SuperJournal    = 0x4000,
            NoMutex         = 0x8000,
            FullMutex       = 0x10000,
            SharedCache     = 0x20000,
            PrivateCache    = 0x40000,
            Wal             = 0x80000,
            NoFollow        = 0x0100000,
            ExRescode       = 0x0200000
        };
    
        //! Default constructor (call open() to open it)
        SqlLite();
        
        //! Destructor (will close the database, if open)
        ~SqlLite();
        
        //! Opens the database at the specified location with the specified flags
        bool        open(const std::filesystem::path&, int flags=0);
        
        //! SQLite Database pointer (so, use this to make the queries)
        sqlite3*    db() const { return m_database; }
        
        //! True if the database is open and usable
        bool        is_open() const;
        
        //! Closes the database
        void        close();
        
        //! Filepath to the database
        const std::filesystem::path&    file() const { return m_file; }
        
        //! Queries and returns a set of table names.
        string_set_t    tables() const;
        
        //! Queries to see if specified table exists in the database
        bool            has_table(std::string_view) const;
    
        //! Calls the checkpoint method on the database (IIRC, thats equivalent to a "flush")
        void            checkpoint();
    
    private:
        SqlLite(const SqlLite&) = delete;
        SqlLite(SqlLite&&) = delete;
        SqlLite& operator=(const SqlLite&) = delete;
        SqlLite& operator=(SqlLite&&) = delete;
        
        static bool         config_sqlite();
        static int          tables_callback(void* ret, int, char**argv, char**);
        
    
        std::filesystem::path   m_file;
        mutable sqlite3*        m_database = nullptr;
    };

}
