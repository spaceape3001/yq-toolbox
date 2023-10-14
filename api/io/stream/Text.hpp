////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <io/Stream.hpp>
#include <string>

namespace yq::stream {
    //! Wrapper to stream to a std::string
    class Text : public Stream {
    public:
    
        //! Constructor that takes in a reference to ta strign
        //! \note This must remain VALID the entire duration of this class
        Text(std::string& bytes) : m_bytes(bytes) {}
        
        //! Destructor
        ~Text(){}

        //! Overload that appends to the string
        bool write(const char* buf, size_t cb) override;

    private:
        
        Text(const Text&) = delete;
        Text(Text&&) = delete;
        Text& operator=(const Text&) = delete;
        Text& operator=(Text&&) = delete;
    
        std::string&  m_bytes;
    };
}
