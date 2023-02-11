////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/Stream.hpp>
#include <basic/trait/not_copyable.hpp>
#include <basic/trait/not_moveable.hpp>
#include <string>

namespace yq {
    class String;
    
    namespace stream {
    
        //! Wrapper to stream to a std::string
        class Text : public Stream, not_copyable, not_moveable {
        public:
        
            //! Constructor that takes in a reference to ta strign
            //! \note This must remain VALID the entire duration of this class
            Text(std::string& bytes) : m_bytes(bytes) {}
            
            //! Destructor
            ~Text(){}

            //! Overload that appends to the string
            bool write(const char* buf, size_t cb) override;

        private:
            std::string&  m_bytes;
        };
    }
}
