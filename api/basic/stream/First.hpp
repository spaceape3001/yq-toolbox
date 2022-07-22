////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/Stream.hpp>

namespace yq {
    namespace stream {
        class First : public Stream {
        public:
            First(Stream&);
            ~First();
            bool    triggered() const { return m_triggered; }
            bool    is_open() const override;
            bool    write(const char*, size_t) override;
            void    flush() override;
            void    close() override;
            
        protected:
            //  CALLED on first write (or dtor)
            virtual void    first_write() = 0;
        private:
            Stream& m_stream;
            bool    m_triggered;
        };
    }
}
