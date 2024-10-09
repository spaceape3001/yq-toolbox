////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_RAY4_HPP 1

#include <yq/typedef/ray4.hpp>

#include <yq-toolbox/vector/Vector4.hpp>

namespace log4cpp { class CategoryStream; }

namespace yq {

    /*! \brief Ray in four dimensions.
    */
    template <typename T>
    struct Ray4 {

        //! Component type
        using component_type    = T;

        //! Point on the ray
        Vector4<T>              point;

        //! Direction of the ray
        Vector4<ieee754_t<T>>   direction;
        
        //! Defaulted equality operator
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
