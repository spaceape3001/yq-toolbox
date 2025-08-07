////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/typedef/filesystem_path.hpp>
#include <yq/typedef/string_sets.hpp>
#include <yq/typedef/string_vectors.hpp>
#include <filesystem>

namespace yq {
    //! List all files in given directory
    string_vector_t  dir_files(const char*);
    
    //! List all subdirectories in given directory
    string_vector_t  dir_directories(const char*);

    //  Make the filesystem_path_t (including the specified filename)
    bool            make_path(const filesystem_path_t&);

    //  Make the filesystem_path_t (not including the specified filename)
    bool            make_parent_path(const filesystem_path_t&);


    namespace dir {
        
        enum Options {
            //  No extensions
            NO_EXT      = 0x1,
            
            //! Allow hidden files
            HIDDEN      = 0x2,
            
            //! Allow dot & dot-dot
            DOT_OR_DDOT = 0x4,
            
            NO_DIRS     = 0x8,
            NO_FILES    = 0x10
        };

        using   path_vec_t    = std::vector<filesystem_path_t>;
        
        //!  Finds all children with specfied name (case insensitive)
        path_vec_t          all_children(const filesystem_path_t& dir, std::string_view name);

        //!  Finds all children with specfied name (case insensitive) across provided directories
        path_vec_t          all_children(const std::vector<filesystem_path_t>& dir, std::string_view name);

        //! Returns the first child with the specified case insensitive name
        filesystem_path_t           first_child(const filesystem_path_t& dir, std::string_view name);

        //! Returns the first child with the specified case insensitive name in the given directories
        filesystem_path_t           first_child(const std::vector<filesystem_path_t>&, std::string_view name);
        
        //!  Finds all chlidren (not hidden unless HIDDEN option is used)
        string_vector_t     subdirectory_names(const filesystem_path_t&, unsigned options=0) ;

        //!  Finds all chlidren for vector of directories (not hidden unless HIDDEN option is used)
        string_vector_t     subdirectory_names(const std::vector<filesystem_path_t>&, unsigned options=0) ;

        //! Finds all children (not hidden unless HIDDEN option is used)
        //! \return Set of names
        string_xset_t       subdirectory_names_set(const filesystem_path_t&, unsigned options=0) ;

        //! Finds all children (not hidden unless HIDDEN option is used)
        //! \return Set of names
        string_xset_t       subdirectory_names_set(const std::vector<filesystem_path_t>&, unsigned options=0) ;

        //! Gets all subdirectories
        path_vec_t          subdirectories(const filesystem_path_t&, unsigned options=0);

        //! Gets all subdirectories
        path_vec_t          subdirectories(const std::vector<filesystem_path_t>&, unsigned options=0);
        
        bool            child_exists(const filesystem_path_t&, std::string_view name);
        bool            child_exists(const std::vector<filesystem_path_t>&, std::string_view name);
        
        template <typename P>
        auto    for_all_children(const filesystem_path_t& d, unsigned options, P pred)
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
        auto    for_all_children(const std::vector<filesystem_path_t>& dirs, unsigned options, P pred)
        {
            using result_t  = decltype(pred({}));
            for(const filesystem_path_t& d : dirs){
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
