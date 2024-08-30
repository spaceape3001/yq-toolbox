////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <string_view>

namespace yq {
    using std::literals::string_literals::operator""s;
    using std::literals::string_view_literals::operator""sv;

    using string_t      = std::u32string;
    using string_view_t = std::u32string_view;
}
