////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstddef>
#include <cstdint>

namespace yq {
    template <typename> struct Size4;

    using Size4D                    = Size4<double>;
    using Size4F                    = Size4<float>;
    using Size4I                    = Size4<int>;
    using Size4I8                   = Size4<int8_t>;
    using Size4I16                  = Size4<int16_t>;
    using Size4I32                  = Size4<int32_t>;
    using Size4I64                  = Size4<int64_t>;
    using Size4U                    = Size4<unsigned>;
    using Size4U8                   = Size4<int8_t>;
    using Size4U16                  = Size4<int16_t>;
    using Size4U32                  = Size4<int32_t>;
    using Size4U64                  = Size4<int64_t>;
    using Size4Z                    = Size4<size_t>;
}
