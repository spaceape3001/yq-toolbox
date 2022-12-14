////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "TriangleData.hpp"
#include <math/preamble.hpp>
#include <math/Vector2.hpp>

namespace yq {

    YQ_IEEE754_1(Triangle2)


//  --------------------------------------------------------
//  COMPOSITION

    YQ_NAN_1(Triangle2, { nan_v<Vector2<T>>, nan_v<Vector2<T>>, nan_v<Vector2<T>> })
    YQ_ZERO_1(Triangle2, { zero_v<Vector2<T>>, zero_v<Vector2<T>>, zero_v<Vector2<T>> })

    /*! \brief Create a triangle from three points */
    template <typename T>
    Triangle2<T>    triangle(const Vector2<T>& a, const Vector2<T>& b, const Vector2<T>& c)
    {
        return { a, b, c };
    }


//  --------------------------------------------------------
//  GETTERS

//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_FINITE_1(Triangle2, is_finite(v.a) && is_finite(v.b) && is_finite(v.c))
    YQ_IS_NAN_1(Triangle2, is_nan(v.a) || is_nan(v.b) || is_nan(v.c) )

    /*! \brief Creates an axially aligned bounding box from the three triangle vertices */
    template <typename T>
    AxBox2<T>   aabb(const Triangle2<T>& tri)
    {
        return { 
            min_elem(min_elem(tri.a, tri.b), tri.c), 
            max_elem(max_elem(tri.a, tri.b), tri.c)
        };
    }

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
//  UTILITY FUNCTIONS (FOR OTHER ADVANCED THINGS TO WORK)

    /*! \brief "Point area" of the points
    
        This is a helper to area and other functions, 
        simply does an "area" of the point deltas, 
        no sign correction, no scaling.
    */
    template <typename T>
    square_t<T>    point_area(const Triangle2<T>& tri)
    {
        return delta_area(tri.b, tri.a) + delta_area(tri.c, tri.b) + delta_area(tri.a, tri.c);
    }

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

    /*! \brief Computes the area of a 2D triangle
    */
    template <typename T>
    square_t<T>    area(const Triangle2<T>& tri)
    {
        return 0.5*abs(point_area(tri));
    }

    /*! \brief TRUE if the triangle is defined in a counter-clockwise fashion
    */
    template <typename T>
    bool    is_ccw(const Triangle2<T>& tri)
    {
        return point_area(tri) < zero_v<T>;
    }

    /*! \brief TRUE if the triangle is defined in a clockwise fashion
    */
    template <typename T>
    bool    is_clockwise(const Triangle2<T>& tri)
    {
        return point_area(tri) > zero_v<T>;
    }

    /*! \brief Computes the perimeter of the triangle
    */
    template <typename T>
    requires trait::has_sqrt_v<square_t<T>>
    T       perimeter(const Triangle2<T>& tri)
    {
        return length(tri.b-tri.a)+length(tri.c-tri.b)+length(tri.a-tri.c);
    }


}

YQ_TYPE_DECLARE(yq::Triangle2D)
YQ_TYPE_DECLARE(yq::Triangle2F)
YQ_TYPE_DECLARE(yq::Triangle2I)
YQ_TYPE_DECLARE(yq::Triangle2U)

