////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/Stream.hpp>
#include <filesystem>
#include <fstream>

namespace yq {
    namespace stream {

        /*! \brief Stream based on C++ ofstream
        */
        class File : public Stream {
        public:

            File();
            ~File();
            
            bool        open(const std::filesystem::path&);
            void        close() override;
            bool        is_open() const override;
            
            virtual bool    write(const char*z, size_t cb) override;
            virtual void    flush() override;
            
            const std::filesystem::path&   path() const { return m_path; }
            
        private:
            std::ofstream           m_file;
            std::filesystem::path   m_path;
        };

    }
}
