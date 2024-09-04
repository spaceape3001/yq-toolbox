////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstddef>
#include <cstdint>

namespace yq {
    template <typename> struct Size3;

    using Size3D                    = Size3<double>;
    using Size3F                    = Size3<float>;
    using Size3I                    = Size3<int>;
    using Size3I8                   = Size3<int8_t>;
    using Size3I16                  = Size3<int16_t>;
    using Size3I32                  = Size3<int32_t>;
    using Size3I64                  = Size3<int64_t>;
    using Size3U                    = Size3<unsigned>;
    using Size3U8                   = Size3<int8_t>;
    using Size3U16                  = Size3<int16_t>;
    using Size3U32                  = Size3<int32_t>;
    using Size3U64                  = Size3<int64_t>;
    using Size3Z                    = Size3<size_t>;
}
