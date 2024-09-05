////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <cstdint>

namespace yq {
    template <typename> struct HSL;

    using HSL3D   = HSL<double>;
    using HSL3F   = HSL<float>;
    using HSL3I   = HSL<int>;
    using HSL3U   = HSL<unsigned>;
    using HSL3U8  = HSL<uint8_t>;
    using HSL3U16 = HSL<uint16_t>;
}
