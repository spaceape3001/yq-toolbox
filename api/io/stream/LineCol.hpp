////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <io/Stream.hpp>

namespace yq {

    namespace stream {
        /*! \brief Line Counter for a stream

            Wrap this around another stream to get a count of line/columns
            
            \note This starts at 0,0 (c-style)
        */
        class LineCol : public Stream {
        public:
        
            //! Constructor with other stream that must remain valid throughout the duration of this class
            LineCol(Stream&);
            
            //! Current line
            unsigned int    line() const { return m_line; }
            
            //! Current column
            unsigned int    column() const { return m_column; }
            
            //! Close the underlying stream
            void    close() override;
            
            //! Writes data to other stream
            bool    write(const char* z, size_t cb) override;
            
            //! TRUE if the stream is open
            bool    is_open() const override;
            
        private:
            Stream&             m_stream;
            unsigned int        m_line;
            unsigned int        m_column;
        };
    }
}
