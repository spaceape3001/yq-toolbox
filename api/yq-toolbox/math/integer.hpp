////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <type_traits>

namespace yq {
    //! Quick check for power of two in N
    template <typename T>
    requires std::is_integral_v<T>
    constexpr bool is_power_two(T n)
    {
        return n && ((n & (n-1)) == 0ULL);
    }
    
    //! Approximate log in base two
    //! \note It'll be exact for powers of two
    template <typename T>
    requires std::is_integral_v<T>
    constexpr T log_two_approximate(T v)
    {
        T  n   = 0;
        for(;v; ++n)
            v >>= 1;
        return n;
    }
    
        // This routine taken from ImGui, see their MIT license 
    template <typename T>
    requires std::is_integral_v<T>
    constexpr T two_alignment(T size, T align)
    {
        return (size + align - 1) & ~(align - 1);
    }
    
        //! Rounds up to the nearest power of two
    template <typename T>
    requires std::is_integral_v<T>
    constexpr T round_up_power_two(T n)
    {
        return 1 << (log_two_approximate(n)+1);
    }
    
}
