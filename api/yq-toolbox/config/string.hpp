////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstddef>

namespace yq {
    //! The reasonable maximum for a raw null terminated string... anything else should be in a string view (at least)
    static constexpr const size_t   kMaxNullTermString     = 8192;

    //! For formatting simple things
    static constexpr const size_t   kMaxFormattingBuffer   = 63;
}
