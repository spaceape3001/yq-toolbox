////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstddef>
#include <cstdint>

namespace yq {
    template <typename> struct Size1;

    using Size1D                    = Size1<double>;
    using Size1F                    = Size1<float>;
    using Size1I                    = Size1<int>;
    using Size1I8                   = Size1<int8_t>;
    using Size1I16                  = Size1<int16_t>;
    using Size1I32                  = Size1<int32_t>;
    using Size1I64                  = Size1<int64_t>;
    using Size1U                    = Size1<unsigned>;
    using Size1U8                   = Size1<int8_t>;
    using Size1U16                  = Size1<int16_t>;
    using Size1U32                  = Size1<int32_t>;
    using Size1U64                  = Size1<int64_t>;
    using Size1Z                    = Size1<size_t>;
}
