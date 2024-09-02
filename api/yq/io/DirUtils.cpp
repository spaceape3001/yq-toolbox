////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/io/DirUtils.hpp>
#include <yq/container/Set.hpp>
#include <yq/container/Vector.hpp>
#include <yq/text/match.hpp>
//#include <0/basic/TextUtils.hpp>

#include <sys/stat.h>
#include <dirent.h>

namespace yq {

    string_vector_t  dir_files(const char* iDir)
    {
        string_vector_t  ret;
        DIR*            d   = opendir(iDir);
        if(d){
            while(struct dirent* r = readdir(d)){
                if(r -> d_type != DT_REG)
                    continue;
                ret.push_back(r->d_name);
            }
            closedir(d);
        }
        return ret;
    }

    string_vector_t  dir_directories(const char* iDir)
    {
        string_vector_t  ret;
        DIR*            d   = opendir(iDir);
        if(d){
            while(struct dirent* r = readdir(d)){
                if(r -> d_type != DT_DIR)
                    continue;
                if(r->d_name[0] == '.'){
                    if(r->d_name[1] == '.' || r->d_name[1] == '\0')
                        continue;
                }
                ret.push_back(r->d_name);
            }
            closedir(d);
        }
        return ret;
    }

    bool            make_path(const filesystem_path_t&p)
    {
        std::error_code ec;
        std::filesystem::create_directories(p, ec);
        return ec == std::error_code();
    }


    //  Make the filesystem_path_t (not including the specified filename)
    bool            make_parent_path(const filesystem_path_t&p)
    {
        std::error_code ec;
        std::filesystem::create_directories(p.parent_path(), ec);
        return ec == std::error_code();
    }


    namespace dir {

        // FIXME .... none of these deal with sub-directories!

        path_vec_t        all_children(const filesystem_path_t& d, std::string_view name)
        {
            path_vec_t    ret;
            for_all_children(d, 0, [&](const filesystem_path_t& p) { 
                if(is_similar(p.filename().c_str(), name)){
                    ret.push_back(p); 
                }
            });
            return ret;
        }

        path_vec_t        all_children(const std::vector<filesystem_path_t>& dirs, std::string_view name)
        {
            path_vec_t    ret;
            for_all_children(dirs, 0, [&](const filesystem_path_t& p) { 
                if(is_similar(p.filename().c_str(), name)){
                    ret.push_back(p); 
                }
            });
            return ret;
        }
        
        filesystem_path_t            first_child(const filesystem_path_t& d, std::string_view name)
        {
            // FIXME WARNING... paths....
            return for_all_children( d, 0, [&](const filesystem_path_t&p) -> auto {
                //yInfo() << "   Checking " << d << " '" << p << "' for " << name;
                return is_similar(p.filename().c_str(), name) ? p : filesystem_path_t();
            });
        }
        
        filesystem_path_t            first_child(const std::vector<filesystem_path_t>& d, std::string_view name)
        {
            // FIXME WARNING... paths.... 
            return for_all_children( d, 0, [&](const filesystem_path_t&p) -> auto {
                //yInfo() << "   Checking " << p << " for " << name;
                return is_similar(p.filename().c_str(), name) ? p : filesystem_path_t();
            });
        }

        
        string_vector_t  subdirectory_names(const filesystem_path_t&d, unsigned options) 
        {
            string_vector_t  ret;
            for_all_children(d, options | NO_FILES, [&](const filesystem_path_t&p){
                ret.push_back(p.filename().string());
            });
            return ret;
        }
        
        string_vector_t  subdirectory_names(const std::vector<filesystem_path_t>&dirs, unsigned options) 
        {
            string_vector_t  ret;
            for_all_children(dirs, options | NO_FILES, [&](const filesystem_path_t&p){
                ret.push_back(p.filename().string());
            });
            return ret;
        }


        //  Finds all chlidren (not hidden)
        string_xset_t      subdirectory_names_set(const filesystem_path_t&d, unsigned options) 
        {
            string_xset_t   ret;
            for_all_children(d, options | NO_FILES, [&](const filesystem_path_t&p){
                ret.insert(p.filename().string());
            });
            return ret;
        }
        
        string_xset_t       subdirectory_names_set(const std::vector<filesystem_path_t>&dirs, unsigned options) 
        {
            string_xset_t   ret;
            for_all_children(dirs, options | NO_FILES, [&](const filesystem_path_t&p){
                ret.insert(p.filename().string());
            });
            return ret;
        }


        //  Finds all chlidren (not hidden)
        path_vec_t        subdirectories(const filesystem_path_t&d, unsigned options)
        {
            path_vec_t    ret;
            for_all_children(d, options | NO_FILES, [&](const filesystem_path_t&p){
                ret.push_back(p);
            });
            return ret;
        }
        
        path_vec_t        subdirectories(const std::vector<filesystem_path_t>&dirs, unsigned options)
        {
            path_vec_t    ret;
            for_all_children(dirs, options | NO_FILES, [&](const filesystem_path_t&p){
                ret.push_back(p);
            });
            return ret;
        }

        bool            child_exists(const filesystem_path_t&d, std::string_view name)
        {
            return for_all_children(d, 0, [&](const filesystem_path_t&p) -> bool {
                return is_similar(p.filename().c_str(), name);
            });
        }

        bool            child_exists(const std::vector<filesystem_path_t>&dirs, std::string_view name)
        {
            return for_all_children(dirs, 0, [&](const filesystem_path_t&p) -> bool {
                return is_similar(p.filename().c_str(), name);
            });
        }
    }
}
