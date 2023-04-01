////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <filesystem>
#include <vector>

namespace yq {

    //! Search path for files
    class FileResolver {
    public:
    
        FileResolver();
        FileResolver(const FileResolver&);
        FileResolver(FileResolver&&);

        ~FileResolver();

        
        void    add_path(const std::filesystem::path&);
        
        //! Resolves a file to an existing file with a FULL relative path
        std::filesystem::path       resolve(std::string_view) const;

        //! Resolves a file to an existing file with a partial path
        //! \note This implies recursive
        std::filesystem::path       partial(std::string_view) const;
        
        std::vector<std::filesystem::path>  all_partial(std::string_view) const;
        
        const std::vector<std::filesystem::path>& paths() const { return m_paths; }
        
        FileResolver& operator=(const FileResolver&);
        FileResolver& operator=(FileResolver&&);
        bool    operator==(const FileResolver&) const;
        
    private:
    
        std::vector<std::filesystem::path>  m_paths;
    
    };
}
