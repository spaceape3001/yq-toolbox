////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <sqlite3.h>

namespace log4cpp { class CategoryStream; }

namespace yq {
    struct SqlError {
        int     result = SQLITE_OK;
    };

    log4cpp::CategoryStream&    operator<<(log4cpp::CategoryStream& str, SqlError ec);
}
