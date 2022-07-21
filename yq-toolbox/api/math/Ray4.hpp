////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>
#include <math/Vector4.hpp>

namespace yq {
    template <typename T>
    struct Ray4 {
        using component_type    = T;
        Vector4<T>              point;
        Vector4<ieee754_t<T>>   direction;
        
        constexpr bool operator==(const Ray4& rhs) const noexcept = default;
    };
    
    YQ_IEEE754_1(Ray4)
        
//  --------------------------------------------------------
//  COMPOSITION
    
    YQ_NAN_1(Ray4, { nan_v<Vector4<T>>, nan_v<Vector4<ieee754_t<T>>> })
    YQ_ZERO_1(Ray4, { zero_v<Vector4<T>>, zero_v<Vector4<ieee754_t<T>>> })
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_NAN_1(Ray4, is_nan(v.point) || is_nan(v.direction))
    YQ_IS_FINITE_1(Ray4, is_finite(v.point) && is_finite(v.direction))
    
    
}

YQ_TYPE_DECLARE(yq::Ray4D)
YQ_TYPE_DECLARE(yq::Ray4F)
