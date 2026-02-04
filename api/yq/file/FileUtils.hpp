////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/keywords.hpp>
#include <yq/file/SizeTimestamp.hpp>
#include <yq/typedef/filesystem_path.hpp>
#include <yq/typedef/url.hpp>
//#include <iosfwd>
#include <vector>

namespace yq {
    class ByteArray;
    struct SizeTimestamp;
    
    #if 0
    namespace file {
        namespace load {
            ByteArray   as_bytes(const filesystem_path_t&);
            std::string as_string(const filesystem_path_t&);
        }

        bool            backup(const filesystem_path_t&, const char* suffix="bck");
        bool            exists(const filesystem_path_t&);
        std::string     last_modified(const std::filesystme::path&);
        bool            is_readable(const filesystem_path_t&);
        size_t          size_of(const filesystem_path_t&);
        
        bool            save(const filesystem_path_t&, const char*, size_t);
        bool            save(const filesystem_path_t&, std::string_view);
        bool            save(const filesystem_path_t&, const ByteArray&);
        bool            save(const filesystem_path_t&, const std::vector<char>&);
        uint128_t       timestamp(const filesystem_path_t&);
    }
    #endif
    
    //! Renames an existing file to a "backup" file, clearing the way for a save w/o clobbering
    bool            file_backup(const char*, const char* suffix="bck");
    
    //! Loads up the contents of the file as a byte array.
    ByteArray       file_bytes(const filesystem_path_t&);
    
    //! Loads up the contents of the file as a string
    std::string     file_string(const filesystem_path_t&);
    
    //! Faster (OS-api based) test for file existence
    bool            file_exists(const char*);

    //! Faster (OS-api based) test for file existence
    bool            file_exists(const filesystem_path_t&);
    
    //! Returns the file's last modification date as a string (YYYYMMDD-HHMMSS.ZZZZZZZZZ)
    std::string     file_modified(const char*);
    
    //! Faster (OS-api based) test for whether a file is readable
    bool            file_readable(const char*);

    //! Faster (OS-api based) test for whether a file is readable
    bool            file_readable(const filesystem_path_t&);
    
    //! Returns the byte count for the given file
    size_t          file_size(const char*);
    
    //! Writes the given data block to the specified file
    bool            file_write(const filesystem_path_t&, const char*, size_t);

    //! Writes the given data block to the specified file
    bool            file_write(const filesystem_path_t&, std::string_view);

    //! Writes the given data block to the specified file
    bool            file_write(const filesystem_path_t&, const ByteArray&);

    //! Writes the given data block to the specified file
    bool            file_write(const filesystem_path_t&, const std::vector<char>&);


    /*! \brief Size and time for last modification

        This queries and returns the file size and timestamp to the last update.  Nothing's guaranteed to uint128_t except
        that it changes once a nanosecond.
    */
    SizeTimestamp   file_size_and_timestamp(const filesystem_path_t&);
    //uint128_t       file_timestamp(const filesystem_path_t&);

    /*! \brief Convience function for reading a file into a simple buffer

        \note This will return an empty vector if an error occurs or the file is zero size.
        \return File contents
    */
    //Vector<uint8_t> file_load_all(const char*);
    //Vector<uint8_t> file_load_all(const std::string&);
    //Vector<uint8_t> file_load_all(const QString&);

    //Vector<char> file_load_char(const char*);
    //Vector<char> file_load_char(const std::string&);
    //Vector<char> file_load_char(const QString&);


    
    //! "Sanitizes" a user-supplied path
    //!
    //! This sanitizes a user supplied path by removing extra slashes, hiddens, etc
    std::string         path_sanitize(std::string_view);
    
    //! Returns the LAST file extension (no leading '.') or empty if none
    std::string_view    file_extension(std::string_view);

    //! Returns the LAST file extension (no leading '.') from the path or empty if none
    std::string         file_extension(const Url&);
    
    //! Redoes all extensions
    std::filesystem::path   remap_extension(const std::filesystem::path&, all_k, std::string_view);
    
    //! Redoes final suffix
    std::filesystem::path   remap_extension(const std::filesystem::path&, last_k, std::string_view);
    
    //! Adds to the "stem" or the stuff before extensions
    std::filesystem::path   append_stem(const std::filesystem::path&, std::string_view);
    
    std::filesystem::path   symlink_target(const std::filesystem::path&);
    std::filesystem::path   symlink_target(const char*);
}
