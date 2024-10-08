////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstdint>
#include <yq/typedef/128.hpp>

namespace yq {
    //!  128 bit integer adapter
    //!  This is an 128 bit integer that can do seemless interaction with 64-bit integers
    struct UInt128 { 
        uint64_t low, high; 
        
        //! Default constructor
        constexpr UInt128() noexcept : low{}, high{} {}
        
        //! Construct by parts
        constexpr UInt128(uint64_t l, uint64_t h) noexcept : low(l), high(h) {}
        
        //! Returns the 128 bit integer
        constexpr operator unsigned __int128 () const noexcept { return *(const unsigned __int128*) this; }
    };
    
    // helper until we have 128 bit literals
    inline constexpr uint128_t u128(uint64_t hi, uint64_t lo) noexcept
    {
        return (((uint128_t)hi) << 64) | (uint128_t) lo;
    }
}

