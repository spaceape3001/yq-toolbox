////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>
#include <math/Vector2.hpp>
#include <math/Bivector2.hpp>

namespace yq {
    template <typename T>
    struct Multivector2 {
        unity_t<T>      a;
        T               x, y;
        square_t<T>     xy;
        
        bool operator==(const Multivector2&) const = default;
    };

    YQ_IEEE754_1(Multivector2)
    YQ_NAN_1(Multivector2, Multivector2<T>{nan_v<unity_t<T>>, nan_v<T>, nan_v<T>, nan_v<square_t<T>>})
    YQ_ZERO_1(Multivector2, Multivector2<T>{zero_v<unity_t<T>>, zero_v<T>, zero_v<T>, zero_v<square_t<T>>})
    
    YQ_IS_NAN_1(Multivector2, is_nan(v.a) || is_nan(v.x) || is_nan(v.y) || is_nan(v.xy))
    YQ_IS_FINITE_1(Multivector2, is_finite(v.a) && is_finite(v.x) && is_finite(v.y) && is_finite(v.xy))
}

YQ_TYPE_DECLARE(Multivector2D)
YQ_TYPE_DECLARE(Multivector2F)
