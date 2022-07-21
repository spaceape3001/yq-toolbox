////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "LineCol.hpp"

namespace yq {
    namespace stream {
        LineCol::LineCol(Stream& out) : m_stream(out), m_line(0), m_column(0) 
        {
        }
        
        void    LineCol::close() 
        {
            m_stream.close();
        }

        bool    LineCol::is_open() const
        {
            return m_stream.is_open();
        }

        bool    LineCol::write(const char* z, size_t cb)
        {
            for(size_t i=0;i<cb;++i){
                if(z[i] == '\n'){
                    ++m_line;
                    m_column    = 0;
                } else
                    ++m_column;
            }
            return m_stream.write(z, cb);
        }
    }
}

