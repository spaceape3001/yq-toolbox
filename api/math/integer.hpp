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
}
