////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <string_view>
#include <yq/typedef/string_maps.hpp>

namespace yq {
    //! Concatenates the given 32-bit UTF character on to the string as UTF-8
    std::string&  operator+=(std::string&, char32_t);

    /*! \brief Set left to right if left is empty OR override is true
    
        \note if B is empty, this is a NOP
    */
    std::string&    set_if_empty(std::string&, std::string_view, bool fOverride=false);

    /*! \brief Web decodes (with %) the string
    */
    std::string     web_decode(std::string_view);
    
    StringMultiMap  web_decode(StringViewMultiMap);
    
    /*! \brief Web encodes (with %) the string
    */
    std::string     web_encode(std::string_view);
}
