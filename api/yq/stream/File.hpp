////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Stream.hpp>
#include <filesystem>
#include <fstream>

namespace yq::stream {

    /*! \brief Stream based on C++ ofstream
    
        \note This stream is part of the yq_file library, link appropriately.
    */
    class File : public Stream {
    public:

        //! Default constructor
        File();
        
        //! Default destructor
        ~File();
        
        //! Opens the specified filename
        bool        open(const std::filesystem::path&);
        
        //! Closes the stream
        void        close() override;
        
        //! True if open
        bool        is_open() const override;
        
        //! Writes the specified data tot eh stream
        virtual bool    write(const char*z, size_t cb) override;
        
        //! Flushes the stream
        virtual void    flush() override;
        
        //! Path of the stream
        const std::filesystem::path&   path() const { return m_path; }
        
    private:
        File(const File&) = delete;
        File(File&&) = delete;
        File& operator=(const File&) = delete;
        File& operator=(File&&) = delete;
    
        std::ofstream           m_file;
        std::filesystem::path   m_path;
    };

}
