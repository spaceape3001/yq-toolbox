////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Normal3.hpp"

namespace yq {
    template <typename T>
    struct Plane3 {
        using component_type    = T;
        using ieee754_type      = ieee754_t<T>;
        using normal_type       = Normal3<ieee754_type>;
    
        normal_type     normal;
        T               distance;
        
        constexpr bool operator==(const Plane3&) const noexcept = default;
    };

    YQ_IEEE754_1(Plane3)
    YQ_NAN_1(Plane3, { nan_v<Normal3<ieee754_t<T>>>, nan_v<T> })
    YQ_ZERO_1(Plane3, { zero_v<Normal3<ieee754_t<T>>>, zero_v<T> })
    
    
    YQ_IS_FINITE_1(Plane3, is_finite(v.normal) && is_finite(v.distance))
    YQ_IS_NAN_1(Plane3, is_nan(v.normal) || is_nan(v.distance))
}

YQ_TYPE_DECLARE(yq::Plane3D)
YQ_TYPE_DECLARE(yq::Plane3F)
