////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "File.hpp"


namespace yq {
    namespace stream {
        File::File()
        {
        }

        File::~File()
        {
            close();
        }

        void        File::close()
        {
            if(m_file.is_open()){
                m_path.clear();
                m_file.flush();
                m_file.close();
            }
        }

        void    File::flush() 
        {
            if(m_file.is_open())
                m_file.flush();
        }

        bool        File::is_open() const
        {
            return m_file.is_open();
        }

        bool        File::open(const std::filesystem::path& pth)
        {
            if(m_file.is_open())
                return false;
            m_file.open(pth, std::ios_base::binary);
            if(m_file){
                m_path      = pth;
                return true;
            } else
                return false;
        }

        bool    File::write(const char*z, size_t cb) 
        {
            if(m_file.is_open()){
                m_file.write(z, cb);
                return true;
            } else
                return false;
        }

    }
}

