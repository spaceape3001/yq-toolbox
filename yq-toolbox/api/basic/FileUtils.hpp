////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/preamble.hpp>
#include <basic/SizeTimestamp.hpp>
#include <iosfwd>


namespace yq {
    class ByteArray;
    
    #if 0
    namespace file {
        namespace load {
            ByteArray   as_bytes(const std::filesystem::path&);
            std::string as_string(const std::filesystem::path&);
        }

        bool            backup(const std::filesystem::path&, const char* suffix="bck");
        bool            exists(const std::filesystem::path&);
        std::string     last_modified(const std::filesystme::path&);
        bool            is_readable(const std::filesystem::path&);
        size_t          size_of(const std::filesystem::path&);
        
        bool            save(const std::filesystem::path&, const char*, size_t);
        bool            save(const std::filesystem::path&, std::string_view);
        bool            save(const std::filesystem::path&, const ByteArray&);
        bool            save(const std::filesystem::path&, const std::vector<char>&);
        uint128_t       timestamp(const std::filesystem::path&);
    }
    #endif
    

    bool            file_backup(const char*, const char* suffix="bck");
    ByteArray       file_bytes(const std::filesystem::path&);
    std::string     file_string(const std::filesystem::path&);
    bool            file_exists(const char*);
    bool            file_exists(const std::filesystem::path&);
    std::string     file_modified(const char*);
    bool            file_readable(const char*);
    size_t          file_size(const char*);
    
    bool            file_write(const std::filesystem::path&, const char*, size_t);
    bool            file_write(const std::filesystem::path&, std::string_view);
    bool            file_write(const std::filesystem::path&, const ByteArray&);
    bool            file_write(const std::filesystem::path&, const std::vector<char>&);


    /*! \brief Size and time for last modification

        This queries and returns the file size and timestamp to the last update.  Nothing's guaranteed to uint128_t except
        that it changes once a nanosecond.
    */
    SizeTimestamp   file_size_and_timestamp(const std::filesystem::path&);
    //uint128_t       file_timestamp(const std::filesystem::path&);

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
    
    inline std::filesystem::path   operator "" _fp(const char* z) { return std::filesystem::path(z); }
    
}
