////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstdint>

namespace yq {
    template <typename> struct HSV;

    using HSV3D   = HSV<double>;
    using HSV3F   = HSV<float>;
    using HSV3I   = HSV<int>;
    using HSV3U   = HSV<unsigned>;
    using HSV3U8  = HSV<uint8_t>;
    using HSV3U16 = HSV<uint16_t>;
}
