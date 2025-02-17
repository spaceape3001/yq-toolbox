////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Stream.hpp>

namespace yq::stream {

    /*! \brief Wrapper stream to alert derived class that writing has started
    */
    class First : public Stream {
    public:
    
        //! Constructor, takes a stream that MUST remain valid
        First(Stream&);
        
        //! Destructor
        ~First();
        
        //! TRUE if the object has been triggered
        bool    triggered() const { return m_triggered; }
        
        //! TRUE if the underlying stream is open
        bool    is_open() const override;
        
        //! Overloaded write
        bool    write(const char*, size_t) override;
        
        //! Flushes the underlying stream
        void    flush() override;
        
        //! Closes the stream (and underlying stream)
        void    close() override;
        
    protected:
        //!  CALLED on first write (or dtor)
        virtual void    first_write() = 0;
    private:
    
        First(const First&) = delete;
        First(First&&) = delete;
        First& operator=(const First&) = delete;
        First& operator=(First&&) = delete;
        
        Stream& m_stream;
        bool    m_triggered;
    };
}
