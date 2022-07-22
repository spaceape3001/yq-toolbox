////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "First.hpp"

namespace yq {
    namespace stream {
        First::First(Stream& s) : m_stream(s), m_triggered(false)
        {
        }
        
        First::~First()
        {
        }
        
        void    First::close() 
        {
            if(m_stream.is_open()){
                if(!m_triggered){
                    first_write();
                    m_triggered = true;
                }
                m_stream.close();
            }
        }

        void    First::flush() 
        {
            m_stream.flush();
        }
        
        bool    First::is_open() const 
        {
            return m_stream.is_open();
        }
        
        bool    First::write(const char*z, size_t cb) 
        {
            if(!m_triggered){
                first_write();
                m_triggered = true;
            }
            return write(z, cb);
        }
    }
}

