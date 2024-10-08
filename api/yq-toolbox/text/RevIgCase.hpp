////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string_view>

namespace yq {

    /*! \brief Useful parameter for case-insensitive string keys in sets and maps
    */
    struct RevIgCase {
        bool    operator()(const std::string_view&, const std::string_view&) const;
        bool    operator()(const std::u32string_view&, const std::u32string_view&) const;
        bool    operator()(char, char) const;
        bool    operator()(char32_t, char32_t) const;
    };
}
