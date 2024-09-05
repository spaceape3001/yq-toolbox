////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_NORMAL3_HPP 1

#include <yq-toolbox/typedef/normal3.hpp>

#include <yq-toolbox/vector/Vector3.hpp>

namespace log4cpp { class CategoryStream; }

namespace yq {
    /*! \brief Represents a "normal" vector
    
        Container to mark a vector as being a normal
    */
    template <typename T>
    struct Normal3 {
        //! Component type (captures the template parameter)
        using component_type    = T;

        //! Direction vector
        Vector3<T>              direction;
        
        //! Defaulted comparison operator
        constexpr bool operator==(const Normal3& rhs) const noexcept = default;
    };
    
    YQ_IEEE754_1(Normal3)

//  --------------------------------------------------------
//  COMPOSITION
    
    YQ_NAN_1(Normal3, { nan_v<Vector3<T>> })
    YQ_ZERO_1(Normal3, { zero_v<Vector3<T>> })
    
//  --------------------------------------------------------

    //! Creates a normal from a vector
    template <typename T>
    Normal3<T>     normal(const Vector3<T>& dir) 
    {
        return { ~dir };
    }

    //! Creates a normal from two parameters
    template <typename T>
    requires std::is_floating_point_v<T>
    Normal3<T>     normal(T x, std::type_identity_t<T> y, std::type_identity_t<T> z)
    {
        return { ~Vector3<T>{x,y,z} };
    }

//  BASIC FUNCTIONS

    YQ_IS_NAN_1(Normal3, is_nan(v.direction))
    YQ_IS_FINITE_1(Normal3, is_finite(v.direction))

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

YQ_TYPE_DECLARE(yq::Normal3D)
YQ_TYPE_DECLARE(yq::Normal3F)
