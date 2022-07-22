////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/preamble.hpp>

namespace yq {
    Vector<std::string>  dir_files(const char*);
    Vector<std::string>  dir_directories(const char*);

    //  Make the path (including the specified filename)
    bool            make_path(const std::filesystem::path&);

    //  Make the path (not including the specified filename)
    bool            make_parent_path(const std::filesystem::path&);


    namespace dir {
        
        enum Options {
            //  No extensions
            NO_EXT      = 0x1,
            
            //  Allow hidden
            HIDDEN      = 0x2,
            
            //  Allow dot & dot-dot
            DOT_OR_DDOT = 0x4,
            
            NO_DIRS     = 0x8,
            NO_FILES    = 0x10
        };

        using   path        = std::filesystem::path;
        using   path_vec    = Vector<path>;
        
        //  supposed to find all children with specfieid name
        path_vec        all_children(const path& dir, std::string_view name);

        //  supposed to find all children with specfieid name
        path_vec        all_children(const std::vector<path>& dir, std::string_view name);

        path            first_child(const path& dir, std::string_view name);
        path            first_child(const std::vector<path>&, std::string_view name);
        
        //  Finds all chlidren (not hidden)
        Vector<std::string>  subdirectory_names(const path&, unsigned options=0) ;
        Vector<std::string>  subdirectory_names(const std::vector<path>&, unsigned options=0) ;

        //  Finds all chlidren (not hidden)
        StringSet       subdirectory_names_set(const path&, unsigned options=0) ;
        StringSet       subdirectory_names_set(const std::vector<path>&, unsigned options=0) ;

        //  Finds all chlidren (not hidden)
        path_vec        subdirectories(const path&, unsigned options=0);
        path_vec        subdirectories(const std::vector<path>&, unsigned options=0);
        
        bool            child_exists(const path&, std::string_view name);
        bool            child_exists(const std::vector<path>&, std::string_view name);
        
        template <typename P>
        auto    for_all_children(const std::filesystem::path& d, unsigned options, P pred)
        {
            std::error_code ec;
            using result_t  = decltype(pred({}));
            for(auto const& de : std::filesystem::directory_iterator(d, ec)){
                auto p  = de.path();
                if((options & NO_EXT) && !p.extension().empty())
                    continue;

                auto f  = p.filename().string();
                if((!(options & DOT_OR_DDOT)) && ((f == ".") || (f == "..")))
                    continue;

                if((!(options & HIDDEN)) && f.c_str()[0] == '.')
                    continue;

                if((options & NO_DIRS) && std::filesystem::is_directory(p))
                    continue;

                if((options & NO_FILES) && !std::filesystem::is_directory(p))
                    continue;
                
                if constexpr (std::is_same_v<result_t,void>){
                    pred(p);
                } else {
                    result_t    r = pred(p);
                    if(r != result_t{})
                        return r;
                }
            }
            
           
            if constexpr (!std::is_same_v<result_t,void>)
                return result_t{};
            else
                return;
        }

        template <typename P>
        auto    for_all_children(const std::vector<std::filesystem::path>& dirs, unsigned options, P pred)
        {
            using result_t  = decltype(pred({}));
            for(const std::filesystem::path& d : dirs){
                if constexpr (std::is_same_v<result_t,void>){
                    for_all_children(d, options, pred);
                } else {
                    result_t    r   = for_all_children(d, options, pred);
                    if(r != result_t{})
                        return r;
                }
            }
           
            if constexpr (!std::is_same_v<result_t,void>)
                return result_t{};
            else
                return;
        }
    }
    }
