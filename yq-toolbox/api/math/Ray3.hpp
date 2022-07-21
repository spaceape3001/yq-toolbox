////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>
#include <math/Vector3.hpp>

namespace yq {
    template <typename T>
    struct Ray3 {
        using component_type    = T;
        Vector3<T>              point;
        Vector3<ieee754_t<T>>   direction;
        
        constexpr bool operator==(const Ray3& rhs) const noexcept = default;
    };
    
    YQ_IEEE754_1(Ray3)
        
//  --------------------------------------------------------
//  COMPOSITION
    
    YQ_NAN_1(Ray3, { nan_v<Vector3<T>>, nan_v<Vector3<ieee754_t<T>>> })
    YQ_ZERO_1(Ray3, { zero_v<Vector3<T>>, zero_v<Vector3<ieee754_t<T>>> })
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_NAN_1(Ray3, is_nan(v.point) || is_nan(v.direction))
    YQ_IS_FINITE_1(Ray3, is_finite(v.point) && is_finite(v.direction))
    
    
}

YQ_TYPE_DECLARE(yq::Ray3D)
YQ_TYPE_DECLARE(yq::Ray3F)
