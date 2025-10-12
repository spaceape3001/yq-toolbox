////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstdint>

namespace yq {
    template <typename> struct RGBA;

    using RGBA4D                    = RGBA<double>;
    using RGBA4F                    = RGBA<float>;
    using RGBA4I                    = RGBA<int>;
    using RGBA4I8                   = RGBA<int8_t>;
    using RGBA4I16                  = RGBA<int16_t>;
    using RGBA4I32                  = RGBA<int32_t>;
    using RGBA4U                    = RGBA<unsigned>;
    using RGBA4U8                   = RGBA<uint8_t>;
    using RGBA4U16                  = RGBA<uint16_t>;
    using RGBA4U32                  = RGBA<uint32_t>;
}
