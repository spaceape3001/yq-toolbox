////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstddef>

namespace yq {

    //! Abstract baseis for a stream, yes it'll use virtuals
    class Stream {
    public:
        /*! \brief NULL stream
        
            This returns a reference to a null stream, whose write is neutered.  
            Note, it may still incur formatting charges.
        */
            
        static Stream&  null();

        virtual ~Stream(){}
        
        /*! \brief Finish
        
            Call when done/finished
        */
        virtual void    close() {}
        
        /*! \brief Flush any and all buffers to destination
        
            This forces the stream to flush any buffers.
            For streams that wrap other streams, flush
            your buffer, then call flush on the sub-stream.
        */
        virtual void    flush() {}
        

        /*! \brief  Check to see if the stream is open
        
            \note It's NOT an error to still call write on a closed stream,  simply for avoiding expensive stuff
        */
        virtual bool    is_open() const { return false; }


        /*! \brief Writes data
        
            \param[in] z    Pointer to character buffer
            \param[in] cb   Number of bytes to write
            \return TRUE if successful, FALSE otherwise
        */
        virtual bool    write(const char*z, size_t cb) = 0;
    };
}


