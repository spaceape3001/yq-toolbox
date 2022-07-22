////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>

namespace yq {
    template <typename T>
    struct Trivector4 {
        using component_type = T;
        cube_t<T>     xyz, yzw, zwx, wxy;
        bool operator==(const Trivector4&) const = default;
    };

    YQ_IEEE754_1(Trivector4)

    constexpr Trivector4D   operator "" _xyz4(unsigned long long int v)
    {
        return {(double) v, 0., 0., 0.};
    }

    constexpr Trivector4D   operator "" _xyz4(long double v)
    {
        return {(double) v, 0., 0., 0.};
    }

    constexpr Trivector4D   operator "" _yzw4(unsigned long long int v)
    {
        return {0., (double) v, 0., 0.};
    }

    constexpr Trivector4D   operator "" _yzw4(long double v)
    {
        return {0., (double) v, 0., 0.};
    }

    constexpr Trivector4D   operator "" _zwx4(unsigned long long int v)
    {
        return {0., 0.,  (double) v, 0.};
    }

    constexpr Trivector4D   operator "" _zwx4(long double v)
    {
        return {0., 0., (double) v,  0.};
    }

    constexpr Trivector4D   operator "" _wxy4(unsigned long long int v)
    {
        return {0., 0.,  0., (double) v };
    }

    constexpr Trivector4D   operator "" _wxy4(long double v)
    {
        return {0., 0., 0., (double) v};
    }

    YQ_NAN_1(Trivector4, Trivector4<T>{nan_v<cube_t<T>>, nan_v<cube_t<T>>, nan_v<cube_t<T>>, nan_v<cube_t<T>>})
    YQ_ZERO_1(Trivector4, Trivector4<T>{zero_v<cube_t<T>>, nan_v<cube_t<T>>, nan_v<cube_t<T>>, nan_v<cube_t<T>>})
    
    YQ_IS_NAN_1(Trivector4, is_nan(v.xyz) || is_nan(v.yzw) || is_nan(v.zwx) || is_nan(v.wxy))
    YQ_IS_FINITE_1(Trivector4, is_finite(v.xyz) && is_finite(v.yzw) && is_finite(v.zwx) && is_finite(v.wxy))
}

YQ_TYPE_DECLARE(yq::Trivector4D)
YQ_TYPE_DECLARE(yq::Trivector4F)

