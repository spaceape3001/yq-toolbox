////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/preamble.hpp>
#include <basic/trait/not_moveable.hpp>
#include <basic/trait/not_copyable.hpp>

struct sqlite3;

namespace yq {
    
    class SqlLite : trait::not_moveable, trait::not_copyable {
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
    
        SqlLite();
        ~SqlLite();
        bool        open(const std::filesystem::path&, int flags=0);
        sqlite3*    db() const { return m_database; }
        bool        is_open() const;
        void        close();
        const std::filesystem::path&    file() const { return m_file; }
        
        //! Queries and returns a set of table names.
        string_set_t    tables() const;
        
        bool            has_table(std::string_view) const;
    
        void            checkpoint();
    
    private:
        
        static bool         config_sqlite();
        static int          tables_callback(void* ret, int, char**argv, char**);
        
    
        std::filesystem::path   m_file;
        mutable sqlite3*        m_database = nullptr;
    };

}
