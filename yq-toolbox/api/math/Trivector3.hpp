////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>

namespace yq {
    template <typename T>
    struct Trivector3 {
        using component_type = T;
        cube_t<T>     xyz;
        auto operator<=>(const Trivector3&) const = default;
    };

    YQ_IEEE754_1(Trivector3)

    constexpr Trivector3D   operator "" _xyz3(unsigned long long int v)
    {
        return {(double) v};
    }

    constexpr Trivector3D   operator "" _xyz3(long double v)
    {
        return {(double) v};
    }

    YQ_NAN_1(Trivector3, Trivector3<T>{nan_v<cube_t<T>>})
    YQ_ZERO_1(Trivector3, Trivector3<T>{zero_v<cube_t<T>>})
    
    YQ_IS_NAN_1(Trivector3, is_nan(v.xyz))
    YQ_IS_FINITE_1(Trivector3, is_finite(v.xyz))
}

YQ_TYPE_DECLARE(yq::Trivector3D)
YQ_TYPE_DECLARE(yq::Trivector3F)

