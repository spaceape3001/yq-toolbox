////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>
#include <math/Vector1.hpp>

namespace yq {
    template <typename T>
    struct Multivector1 {
        unity_t<T>  a;
        T           x;
        
        bool operator==(const Multivector1&) const = default;
    };

    YQ_IEEE754_1(Multivector1)
    YQ_NAN_1(Multivector1, Multivector1<T>{nan_v<unity_t<T>>, nan_v<T>})
    YQ_ZERO_1(Multivector1, Multivector1<T>{zero_v<unity_t<T>>, zero_v<T>})
    
    YQ_IS_NAN_1(Multivector1, is_nan(v.a) || is_nan(v.x) )
    YQ_IS_FINITE_1(Multivector1, is_finite(v.a) && is_finite(v.x))
}

YQ_TYPE_DECLARE(Multivector1D)
YQ_TYPE_DECLARE(Multivector1F)
