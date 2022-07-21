////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>

namespace yq {
    template <typename T>
    struct Bivector2 {
        using component_type = T;
        square_t<T>     xy;
        auto operator<=>(const Bivector2&) const = default;
    };

    YQ_IEEE754_1(Bivector2)

    constexpr Bivector2D  operator "" _xy2(unsigned long long int v)
    {
        return {(double) v};
    }

    constexpr Bivector2D  operator "" _xy2(long double v)
    {
        return {(double) v};
    }

    YQ_NAN_1(Bivector2, Bivector2<T>{nan_v<square_t<T>>})
    YQ_ZERO_1(Bivector2, Bivector2<T>{zero_v<square_t<T>>})
    
    YQ_IS_NAN_1(Bivector2, is_nan(v.xy))
    YQ_IS_FINITE_1(Bivector2, is_finite(v.xy))
}

YQ_TYPE_DECLARE(yq::Bivector2D)
YQ_TYPE_DECLARE(yq::Bivector2F)

