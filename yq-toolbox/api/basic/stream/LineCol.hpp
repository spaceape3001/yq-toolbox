////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/Stream.hpp>

namespace yq {

    namespace stream {
        /*! \brief Line Counter for a stream

            Wrap this around another stream to get a count of line/columns
            
            \note This starts at 0,0 (c-style)
        */
        class LineCol : public Stream {
        public:
            LineCol(Stream&);
            
            unsigned int    line() const { return m_line; }
            unsigned int    column() const { return m_column; }
            
            void    close() override;
            bool    write(const char* z, size_t cb) override;
            
            bool    is_open() const override;
            
        private:
            Stream&             m_stream;
            unsigned int        m_line;
            unsigned int        m_column;
        };
    }
}
