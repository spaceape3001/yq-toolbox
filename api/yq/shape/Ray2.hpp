////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_RAY2_HPP 1

#include <yq/typedef/ray2.hpp>

#include <yq/vector/Vector2.hpp>

namespace log4cpp { class CategoryStream; }

namespace yq {

    /*! \brief Ray in two dimensions.
    */
    template <typename T>
    struct Ray2 {
    
        //! Component type
        using component_type    = T;
        
        //! Point on the ray
        Vector2<T>              point;
        
        //! Direction of the ray
        Vector2<ieee754_t<T>>   direction;
        
        //! Defaulted equality operator
        constexpr bool operator==(const Ray2& rhs) const noexcept = default;
    };
    
    YQ_IEEE754_1(Ray2)
        
//  --------------------------------------------------------
//  COMPOSITION
    
    YQ_NAN_1(Ray2, { nan_v<Vector2<T>>, nan_v<Vector2<ieee754_t<T>>> })
    YQ_ZERO_1(Ray2, { zero_v<Vector2<T>>, zero_v<Vector2<ieee754_t<T>>> })
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_NAN_1(Ray2, is_nan(v.point) || is_nan(v.direction))
    YQ_IS_FINITE_1(Ray2, is_finite(v.point) && is_finite(v.direction))
    
    
}

YQ_TYPE_DECLARE(yq::Ray2D)
YQ_TYPE_DECLARE(yq::Ray2F)
