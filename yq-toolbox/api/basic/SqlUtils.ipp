////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////


#include "SqlUtils.hpp"
#include "SqlLite.hpp"
#include "SqlLogging.hpp"
#include "SqlQuery.hpp"
#include <basic/FileUtils.hpp>
#include <basic/TextUtils.hpp>

namespace yq {
    bool    db_run_script(std::string_view script, SqlLite& db)
    {
        std::string         buffer;
        buffer.reserve(script.size());
    
        vsplit(script, '\n', [&](std::string_view l){
            l = trimmed(l);
            if(is_blank(l))
                return;
            if(starts(l, "--")){
                return ;
            }
            buffer += l;
            buffer += ' ';
        });
        
        for(std::string_view sql : split(buffer, ';')){
            std::string s = copy(trimmed(sql));
            if(!SqlQuery::exec(db, s))
                return false;
        }
        return true;
    }
    
    bool    db_run_script_file(const std::filesystem::path& file, SqlLite& db)
    {
        dbInfo << "db_script_file " << file;
        if(!std::filesystem::exists(file)){
            dbError << "db_run_script_file(" << file << "): does not exist!";
            return false;
        }
        
        std::string     text    = file_string(file);
        if(text.empty())
            return true;
        return db_run_script(text, db);
    }
}
