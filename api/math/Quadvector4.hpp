////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>

namespace yq {
    template <typename T>
    struct Quadvector4 {
        using component_type = T;
        fourth_t<T>     xyzw;
        auto operator<=>(const Quadvector4&) const = default;
    };

    YQ_IEEE754_1(Quadvector4)

    constexpr Quadvector4D   operator "" _xyzw4(unsigned long long int v)
    {
        return {(double) v};
    }

    constexpr Quadvector4D   operator "" _xyzw4(long double v)
    {
        return {(double) v};
    }

    YQ_NAN_1(Quadvector4, Quadvector4<T>{nan_v<fourth_t<T>>})
    YQ_ZERO_1(Quadvector4, Quadvector4<T>{zero_v<fourth_t<T>>})
    
    YQ_IS_NAN_1(Quadvector4, is_nan(v.xyzw))
    YQ_IS_FINITE_1(Quadvector4, is_finite(v.xyzw))
}

YQ_TYPE_DECLARE(yq::Quadvector4D)
YQ_TYPE_DECLARE(yq::Quadvector4F)

