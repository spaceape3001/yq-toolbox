////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>
#include <math/Vector3.hpp>
#include "TetrahedronData.hpp"

namespace yq {

    YQ_IEEE754_1(Tetrahedron3)

//  --------------------------------------------------------
//  COMPOSITION

    template <typename T>
    Tetrahedron3<T>    tetrahedron(const Vector3<T>& a, const Vector3<T>& b, const Vector3<T>& c, const Vector3<T>& d)
    {
        return { a, b, c, d };
    }

    YQ_NAN_1(Tetrahedron3, { nan_v<Vector3<T>>, nan_v<Vector3<T>>, nan_v<Vector3<T>>, nan_v<Vector3<T>> })
    YQ_ZERO_1(Tetrahedron3, { zero_v<Vector3<T>>, zero_v<Vector3<T>>, zero_v<Vector3<T>>, zero_v<Vector3<T>> })

//  --------------------------------------------------------
//  BASIC FUNCTIONS

    /*! \brief Checks for finiteness
    */
    template <typename T>
    constexpr bool is_finite(const Tetrahedron3<T>&v)
    { 
        return is_finite(v.a) && is_finite(v.b) && is_finite(v.c) && is_finite(v.d);
    }

    YQ_IS_NAN_1(Tetrahedron3, is_nan(v.a) || is_nan(v.b) || is_nan(v.c) || is_nan(v.d))


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

YQ_TYPE_DECLARE(yq::Tetrahedron3D)
YQ_TYPE_DECLARE(yq::Tetrahedron3F)
YQ_TYPE_DECLARE(yq::Tetrahedron3I)
YQ_TYPE_DECLARE(yq::Tetrahedron3U)

