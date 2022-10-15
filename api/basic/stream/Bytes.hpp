////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/Stream.hpp>

namespace yq {
    class ByteArray;
    
    namespace stream {
    
        /*! \brief Stream to a byte array
        
            Use this wrapper to turn a byte array into a streamable object.  It 
            takes in a REFERENCE to a byte array which must remain viable/valid 
            for the lifespan of this class.
        */
        class Bytes : public Stream {
        public:

            //! Constructor that takes a byte array
            Bytes(ByteArray& bytes) : m_bytes(bytes) {}
            ~Bytes(){}

            //! Writes characters to the byte array
            bool write(const char* buf, size_t cb) override;

        private:
            ByteArray&  m_bytes;
        };
    }
}
