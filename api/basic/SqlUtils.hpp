////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/preamble.hpp>

namespace yq {
    class SqlLite;

    /*! \brief Runs the specified script against the database

        This routine runs the specified script of semi-colon separated SQL statements.  
        Comments start on newlines with "--".

        \param[in] script   SQL script
        \param[in] db       the database
        
        \return TRUE if all statements executed successfully
    */
    bool            db_run_script(std::string_view script, SqlLite& db);

    /*! \brief Runs the specified script from the given filename

        See db_run_script for syntax.  This loads up the file, runs that.
        
        \param[in]  zFile   The file to load
        \param[in]  db      The database
        
        \return TRUE if the file exists and all statements executed successfully

    */
    bool            db_run_script_file(const std::filesystem::path& file, SqlLite& db);

}
