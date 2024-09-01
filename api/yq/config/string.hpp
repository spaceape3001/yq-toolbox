////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstddef>
#include <string>
#include <string_view>

namespace yq {
    using std::literals::string_literals::operator""s;
    using std::literals::string_view_literals::operator""sv;

    using string_t      = std::u32string;
    using string_view_t = std::u32string_view;

    //! The reasonable maximum for a raw null terminated string... anything else should be in a string view (at least)
    static constexpr const size_t   kMaxNullTermString     = 8192;

    //! For formatting simple things
    static constexpr const size_t   kMaxFormattingBuffer   = 63;
}
