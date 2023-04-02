////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstdint>

    //  Linux suppourts int128
using uint128_t = unsigned __int128;
using int128_t  = __int128;

namespace yq {
        //  UINT 128
    struct UInt128 { 
        uint64_t low, high; 
        constexpr UInt128() noexcept : low{}, high{} {}
        constexpr UInt128(uint64_t l, uint64_t h) noexcept : low(l), high(h) {}
        constexpr operator unsigned __int128 () const noexcept { return *(const unsigned __int128*) this; }
    };
    
    // helper until we have 128 bit literals
    inline constexpr uint128_t u128(uint64_t hi, uint64_t lo) noexcept
    {
        return (((uint128_t)hi) << 64) | (uint128_t) lo;
    }
}

