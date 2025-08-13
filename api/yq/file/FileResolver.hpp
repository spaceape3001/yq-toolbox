////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/keywords.hpp>
#include <yq/typedef/filesystem_path.hpp>
#include <vector>

namespace yq {

    //! Search path for files
    class FileResolver {
    public:
    
        //! Default constructor
        FileResolver();
        
        //! Copy constructor
        FileResolver(const FileResolver&);
        FileResolver(FileResolver&&);

        ~FileResolver();

        //! Adds the specified path
        void    add_path(const filesystem_path_t&);
        
        //! Tests to see if this path is *IN* the path vector
        bool    has_path(const filesystem_path_t&) const;
        
        //! Resolves a file to an existing file with a FULL relative path
        filesystem_path_t       resolve(std::string_view) const;

        //! Resolves a file to an existing file with a partial path
        //! \note This implies recursive
        filesystem_path_t       partial(std::string_view) const;
        
        std::vector<filesystem_path_t>  all_partial(std::string_view) const;
        
        const std::vector<filesystem_path_t>& paths() const { return m_paths; }
        
        FileResolver& operator=(const FileResolver&);
        FileResolver& operator=(FileResolver&&);
        bool    operator==(const FileResolver&) const;

        //! Full resolution (by default)
        filesystem_path_t       operator()(std::string_view) const;
        filesystem_path_t       operator()(full_k, std::string_view) const;
        filesystem_path_t       operator()(partial_k, std::string_view) const;

    private:
    
        std::vector<filesystem_path_t>  m_paths;
    
    };
}
