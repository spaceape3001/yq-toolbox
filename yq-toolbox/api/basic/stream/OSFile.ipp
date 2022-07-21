////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "OSFile.hpp"

#include <basic/FileUtils.hpp>
#include <basic/TextUtils.hpp>
#include <basic/ByteArray.hpp>

#include <cstring>

#include <fcntl.h>
#include <unistd.h>


namespace yq {

    namespace stream {

        OSFile::OSFile()
        {
        }

        OSFile::~OSFile()
        {
            if(is_open()){
                do_flush();
                do_close();
            }
        }

        void    OSFile::close()
        {
            if(!is_open())
                return ;
            do_flush();
            do_close();
        }

        void            OSFile::do_close()
        {
            ::close(m_fd);
            m_fd        = -1;
            
            if(!(m_options & OVERWRITE)){
                if(!(m_options & NO_BACKUP))
                    file_backup(m_path.c_str());
                rename(m_tmp.c_str(), m_path.c_str());
            }
        }

        void            OSFile::do_flush()
        {
            syncfs(m_fd);
        }

        void    OSFile::flush() 
        {
            if(!is_open())
                return ;
            do_flush();
        }

        bool            OSFile::open(const std::filesystem::path& pth, unsigned int options)
        {
            if(is_open())
                return false;
            
            std::filesystem::path       p;
            int                         flags   = O_CREAT | O_WRONLY;
            
            m_path      = pth;
            m_options   = options;
            
            if(options & OVERWRITE){
                p   = pth;                    //  no chance of changing your mind?
                if(!(options & NO_BACKUP))   // move old into backup
                    file_backup(pth.c_str());
            } else {
                m_tmp   = m_path.concat("*.tmp");
            }
            
            m_fd    = ::open(p.c_str(), flags, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
            
            return m_fd != -1;
        }

        bool    OSFile::write(const char*z, size_t cb)
        {
            if(!is_open())
                return false;
            if(!z)
                return false;
            if(!cb)     // what does it mean to write empty?  Considering it a success
                return true;
            
            do {
                ssize_t     cnt =  ::write(m_fd, z, cb);
                if(cnt <= 0)   //  error, no more
                    return false;
                    
                z  += cnt;
                cb -= cnt;
            } while(cb);
            return true;
        }
    }

}

