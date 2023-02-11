////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/Stream.hpp>
#include <basic/trait/not_copyable.hpp>
#include <basic/trait/not_moveable.hpp>
#include <filesystem>
#include <fstream>

namespace yq {
    namespace stream {

        /*! \brief Stream based on C++ ofstream
        */
        class File : public Stream, not_copyable, not_moveable {
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
            std::ofstream           m_file;
            std::filesystem::path   m_path;
        };

    }
}
