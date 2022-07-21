////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>

namespace yq {
    template <typename T>
    struct Bivector3 {
        using component_type = T;
        square_t<T>     xy, yz, zx;
        bool operator==(const Bivector3&) const = default;
    };

    YQ_IEEE754_1(Bivector3)

    
    constexpr Bivector3D   operator "" _xy3(unsigned long long int v)
    {
        return {(double) v, 0., 0.};
    }

    constexpr Bivector3D   operator "" _xy3(long double v)
    {
        return {(double) v, 0., 0.};
    }

    constexpr Bivector3D   operator "" _yz3(unsigned long long int v)
    {
        return {0., (double) v,  0.};
    }

    constexpr Bivector3D   operator "" _xz3(long double v)
    {
        return {0., (double) v, 0.};
    }

    constexpr Bivector3D   operator "" _zx3(unsigned long long int v)
    {
        return {0., 0., (double) v};
    }

    constexpr Bivector3D   operator "" _zx3(long double v)
    {
        return {0., 0., (double) v};
    }

    YQ_NAN_1(Bivector3, Bivector3<T>{nan_v<square_t<T>>, nan_v<square_t<T>>, nan_v<square_t<T>>})
    YQ_ZERO_1(Bivector3, Bivector3<T>{zero_v<square_t<T>>, zero_v<square_t<T>>, zero_v<square_t<T>>})

    YQ_IS_NAN_1(Bivector3, is_nan(v.xy) || is_nan(v.yz) || is_nan(v.zx))
    YQ_IS_FINITE_1(Bivector3, is_finite(v.xy) && is_finite(v.yz) && is_finite(v.zx))
}

YQ_TYPE_DECLARE(yq::Bivector3D)
YQ_TYPE_DECLARE(yq::Bivector3F)

