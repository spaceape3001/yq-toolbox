////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "TriangleData.hpp"
#include <math/preamble.hpp>
#include <math/AxBox4.hpp>
#include <math/Vector4.hpp>

namespace yq {

    YQ_IEEE754_1(Triangle4)

//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Create a triangle from three points */
    template <typename T>
    Triangle4<T>    triangle(const Vector4<T>& a, const Vector4<T>& b, const Vector4<T>& c)
    {
        return { a, b, c };
    }

    YQ_NAN_1(Triangle4, { nan_v<Vector3<T>>, nan_v<Vector3<T>>, nan_v<Vector3<T>> })
    YQ_ZERO_1(Triangle4, { zero_v<Vector3<T>>, zero_v<Vector3<T>>, zero_v<Vector3<T>> })

//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_FINITE_1(Triangle4, is_finite(v.a) && is_finite(v.b) && is_finite(v.c))
    YQ_IS_NAN_1(Triangle4, is_nan(v.a) || is_nan(v.b) || is_nan(v.c) )

    /*! \brief Creates an axially aligned bounding box from the three triangle vertices */
    template <typename T>
    AxBox4<T>   aabb(const Triangle4<T>& tri)
    {
        return { 
            min_elem(min_elem(tri.a, tri.b), tri.c), 
            max_elem(max_elem(tri.a, tri.b), tri.c)
        };
    }

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

    /*! \brief Computes the perimeter of the triangle
    */
    template <typename T>
    requires trait::has_sqrt_v<square_t<T>>
    T       perimeter(const Triangle4<T>& tri)
    {
        return length(tri.b-tri.a)+length(tri.c-tri.b)+length(tri.a-tri.c);
    }

}

YQ_TYPE_DECLARE(yq::Triangle4D)
YQ_TYPE_DECLARE(yq::Triangle4F)
YQ_TYPE_DECLARE(yq::Triangle4I)
YQ_TYPE_DECLARE(yq::Triangle4U)

