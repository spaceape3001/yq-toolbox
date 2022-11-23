////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "TriangleData.hpp"
#include <math/preamble.hpp>
#include <math/AxBox3.hpp>
#include <math/Triangle2.hpp>
#include <math/Vector3.hpp>

namespace yq {
    YQ_IEEE754_1(Triangle3)

//  --------------------------------------------------------
//  COMPOSITION

    template <typename T>
    Triangle3<T>    triangle(const Vector3<T>& a, const Vector3<T>& b, const Vector3<T>& c)
    {
        return { a, b, c };
    }

    YQ_NAN_1(Triangle3, { nan_v<Vector3<T>>, nan_v<Vector3<T>>, nan_v<Vector3<T>> })
    YQ_ZERO_1(Triangle3, { zero_v<Vector3<T>>, zero_v<Vector3<T>>, zero_v<Vector3<T>> })

//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_NAN_1(Triangle3, is_nan(v.a) || is_nan(v.b) || is_nan(v.c) )

    
    template <typename T>
    AxBox3<T>   aabb(const Triangle3<T>& tri)
    {
        return { 
            min_elem(min_elem(tri.a, tri.b), tri.c), 
            max_elem(max_elem(tri.a, tri.b), tri.c)
        };
    }

    /*! \brief Checks for finiteness
    */
    template <typename T>
    constexpr bool is_finite(const Triangle3<T>&v)
    { 
        return is_finite(v.a) && is_finite(v.b) && is_finite(v.c);
    }

    template <typename T>
    Triangle2<T>   xy(const Triangle3<T>& a)
    {
        return { xy(a.a), xy(a.b), xy(a.c) };
    }
    
    template <typename T>
    Triangle3<T>   xy(const Triangle2<T>& a, std::type_identity_t<T> z)
    {
        return { xy(a.a, z), xy(a.b, z), xy(a.c, z) };
    }

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

    template <typename T>
    requires has_sqrt_v<square_t<T>>
    T       perimeter(const Triangle3<T>& tri)
    {
        return length(tri.b-tri.a)+length(tri.c-tri.b)+length(tri.a-tri.c);
    }

}

YQ_TYPE_DECLARE(yq::Triangle3D)
YQ_TYPE_DECLARE(yq::Triangle3F)
YQ_TYPE_DECLARE(yq::Triangle3I)
YQ_TYPE_DECLARE(yq::Triangle3U)

