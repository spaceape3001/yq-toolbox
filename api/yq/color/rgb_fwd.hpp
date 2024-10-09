////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstdint>

namespace yq {
    template <typename> struct RGB;

    using RGB3D                     = RGB<double>;
    using RGB3F                     = RGB<float>;
    using RGB3I                     = RGB<int>;
    using RGB3U                     = RGB<unsigned>;
    using RGB3U8                    = RGB<uint8_t>;
    using RGB3U16                   = RGB<uint16_t>;
}
