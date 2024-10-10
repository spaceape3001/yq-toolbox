////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Null.hpp"

namespace yq::stream {
    Null::Null() = default;
    Null::~Null() = default;

    bool    Null::is_open() const 
    { 
        return false; 
    }
    
    bool    Null::write(const char*, size_t) 
    { 
        return true; 
    }
}
