////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstddef>
#include <cstdint>
#include <limits>

namespace yq {
    template <typename T, T> struct Counter;
    
    //!  Standard "zero-point" counter
    template <typename T>
    using Count     = Counter<T,T(0)>;

    //!  Counter that resets to numeric-maximum
    template <typename T>
    using HCount    = Counter<T,std::numeric_limits<T>::max()>;

    //!  Counter that resets to numeric-minimum
    template <typename T>
    using LCount    = Counter<T,std::numeric_limits<T>::min()>;
    
    using CountI    = Count<int>;
    using CountI8   = Count<int8_t>;
    using CountI16  = Count<int16_t>;
    using CountI32  = Count<int32_t>;
    using CountI64  = Count<int64_t>;

    using CountU    = Count<unsigned int>;
    using CountU8   = Count<uint8_t>;
    using CountU16  = Count<uint16_t>;
    using CountU32  = Count<uint32_t>;
    using CountU64  = Count<uint64_t>;

    using CountZ    = Count<size_t>;

    using HCountI   = HCount<int>;
    using HCountI8  = HCount<int8_t>;
    using HCountI16 = HCount<int16_t>;
    using HCountI32 = HCount<int32_t>;
    using HCountI64 = HCount<int64_t>;

    using HCountU   = HCount<unsigned int>;
    using HCountU8  = HCount<uint8_t>;
    using HCountU16 = HCount<uint16_t>;
    using HCountU32 = HCount<uint32_t>;
    using HCountU64 = HCount<uint64_t>;

    using HCountZ   = HCount<size_t>;

    using LCountI   = LCount<int>;
    using LCountI8  = LCount<int8_t>;
    using LCountI16 = LCount<int16_t>;
    using LCountI32 = LCount<int32_t>;
    using LCountI64 = LCount<int64_t>;

    using LCountU   = LCount<unsigned int>;
    using LCountU8  = LCount<uint8_t>;
    using LCountU16 = LCount<uint16_t>;
    using LCountU32 = LCount<uint32_t>;
    using LCountU64 = LCount<uint64_t>;

    using LCountZ   = LCount<size_t>;
}
