////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_PLANE3_HPP 1

#include <yq/typedef/plane3.hpp>

#include <yq-toolbox/shape/Normal3.hpp>

namespace log4cpp { class CategoryStream; }

namespace yq {
    /*! \brief A plane in three dimensions
    */
    template <typename T>
    struct Plane3 {
        
        //! Type of the component (ie captures our template argument)
        using component_type    = T;
        
        //! The underlying IEEE 754 data type
        using ieee754_type      = ieee754_t<T>;
        
        //! The relevant normal type
        using normal_type       = Normal3<ieee754_type>;
    
        //! Normal
        normal_type     normal;
        
        //! Distance from the origin in the unit-space of T
        T               distance;
        
        //! Defaulted comparison operator
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
