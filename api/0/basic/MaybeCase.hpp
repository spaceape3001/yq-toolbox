////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string_view>

namespace yq {

    //! Used for situations that may or may not be case sensitive... note one-way on construction
    struct MaybeCase {
        bool  igCase = false;
        
        bool    operator()(const std::string_view&, const std::string_view&) const;
        bool    operator()(char, char) const;
        bool    operator()(char32_t, char32_t) const;
    };
}
