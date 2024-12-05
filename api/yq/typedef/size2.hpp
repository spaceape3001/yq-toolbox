////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstddef>
#include <cstdint>
#include <yq/unit/declare.hpp>

namespace yq {
    template <typename> struct Size2;

    using Size2D                    = Size2<double>;
    using Size2F                    = Size2<float>;
    using Size2I                    = Size2<int>;
    using Size2I8                   = Size2<int8_t>;
    using Size2I16                  = Size2<int16_t>;
    using Size2I32                  = Size2<int32_t>;
    using Size2I64                  = Size2<int64_t>;
    using Size2U                    = Size2<unsigned>;
    using Size2U8                   = Size2<int8_t>;
    using Size2U16                  = Size2<int16_t>;
    using Size2U32                  = Size2<int32_t>;
    using Size2U64                  = Size2<int64_t>;
    using Size2Z                    = Size2<size_t>;
    using Size2M                    = Size2<unit::Meter>;
    using Size2MM                   = Size2<unit::Millimeter>;
    using Size2CM                   = Size2<unit::Centimeter>;
}
