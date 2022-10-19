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

namespace yq {
    namespace stream {

        /*! Stream on a Linux File
        
            This calls the direct write() api, a stream to a linux file.
        */
        class OSFile : public Stream, trait::not_copyable, trait::not_moveable {
        public:
            enum {

                //  Causes the filestream to not use a temporary file (*.tmp)
                OVERWRITE       = 1,
                
                //  Does not BACKUP the file (timestamp)
                NO_BACKUP       = 2
            };

            //! Default constructor
            OSFile();
            
            //! Default destructor
            ~OSFile();
            
            //! Opens the specified file path
            bool            open(const std::filesystem::path&, unsigned int options=0);
            
            //! Our path
            const std::filesystem::path&    path() const { return m_path; }
            
            //! The temporary filename, empty if not used
            const std::filesystem::path&    temp_path() const { return m_tmp; }
            
            //! TRUE if this is open
            bool            is_open() const override { return m_fd != -1; }
            
            //! Writes bytes to the file
            virtual bool    write(const char*z, size_t cb) override;
            
            //! Flushes any buffers
            virtual void    flush() override;

            //! Closes the file
            void            close() override;
            

        private:
            std::filesystem::path       m_path, m_tmp;
            
            //  there's already a cache in the file write mechanism
            //static constexpr const size_t   nBuffer = 65536;
            //char                        m_buffer[nBuffer];
            //size_t                      m_index = 0;
            
            //  TODO... the windows stuff
            int                         m_fd    = -1;
            unsigned int                m_options = 0;
            
            void                        do_close();
            void                        do_flush();
            
        };
    }
}
