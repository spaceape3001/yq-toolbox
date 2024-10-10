////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <string_view>

namespace yq {

    /*! \brief Set left to right if left is empty OR override is true
    
        \note if B is empty, this is a NOP
    */
    std::u32string&    set_if_empty(std::u32string&, std::u32string_view, bool fOverride=false);
    
}
