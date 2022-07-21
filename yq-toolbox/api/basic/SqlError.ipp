////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <basic/SqlError.hpp>
#include <log4cpp/CategoryStream.hh>

namespace yq {
    log4cpp::CategoryStream&    operator<<(log4cpp::CategoryStream& str, SqlError ec)
    {
        const char* why = sqlite3_errstr(ec.result);
        if(!why)
            why = "Unknown Reason";
        str << why;
        return str;
    }
}
