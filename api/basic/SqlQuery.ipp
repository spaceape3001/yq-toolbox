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

    SqlQuery::SqlQuery(SqlLite&db, std::string_view sql, bool isPersistent) : SqlStatement(nullptr, db.db())
    {
        _prepare(sql, isPersistent);
    }
    
    SqlQuery::~SqlQuery()
    {
        _destroy();
    }
    
    //bool     SqlQuery::exec(bool noisy)
    //{
        //return is_good(step(noisy));
    //}

}
