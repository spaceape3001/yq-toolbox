////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>
#include <math/Vector2.hpp>

namespace yq {

    /*! \brief Represents a "normal" vector
    
        Container to mark a vector as being a normal
    */
    template <typename T>
    struct Normal2 {
        using component_type    = T;
        Vector2<T>              direction;
        
        constexpr bool operator==(const Normal2& rhs) const noexcept = default;
    };
    
    YQ_IEEE754_1(Normal2)
        
//  --------------------------------------------------------
//  COMPOSITION

    template <typename T>
    Normal2<T>     normal(const Vector2<T>& dir) 
    {
        return { ~dir };
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    Normal2<T>     normal(T x, std::type_identity_t<T> y)
    {
        return { ~Vector2<T>{x,y} };
    }

    YQ_NAN_1(Normal2, { nan_v<Vector2<T>> })
    YQ_ZERO_1(Normal2, { zero_v<Vector2<T>> })
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_NAN_1(Normal2, is_nan(v.direction))
    YQ_IS_FINITE_1(Normal2, is_finite(v.direction))
    
//  --------------------------------------------------------
//  POSITIVE


//  --------------------------------------------------------
//  NEGATIVE


//  --------------------------------------------------------
//  NORMALIZATION


//  --------------------------------------------------------
//  ADDITION


//  --------------------------------------------------------
//  SUBTRACTION


//  --------------------------------------------------------
//  MULTIPLICATION


//  --------------------------------------------------------
//  DIVISION

//  --------------------------------------------------------
//  POWERS

//  --------------------------------------------------------
//  DOT PRODUCT


//  --------------------------------------------------------
//  INNER PRODUCT


//  --------------------------------------------------------
//  OUTER PRODUCT


//  --------------------------------------------------------
//  CROSS PRODUCT


///  --------------------------------------------------------
//  OTIMES PRODUCT

//  --------------------------------------------------------
//  UNIONS

//  --------------------------------------------------------
//  INTERSECTIONS


//  --------------------------------------------------------
//  PROJECTIONS

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

}

YQ_TYPE_DECLARE(yq::Normal2D)
YQ_TYPE_DECLARE(yq::Normal2F)
