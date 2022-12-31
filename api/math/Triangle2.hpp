////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "TriangleData.hpp"
#include <math/preamble.hpp>
#include <math/Vector2.hpp>
#include <math/TriangleData.hpp>

namespace yq {

    /*! \brief 2D triangle
    */
    template <typename T>
    struct Triangle2 {
        //! Capture the template parameter
        using component_type    = T;
    
        Vector2<T>   a, b, c;
        
        //! Defaulted equality operator
        constexpr bool operator==(const Triangle2&) const noexcept = default;
        
        //! Implicit conversion to triangle data
        constexpr operator TriangleData<Vector2<T>> () const noexcept 
        { 
            return { a, b, c }; 
        }

        //! Area of this triangle
        constexpr square_t<T>    area() const noexcept
        {
            return middivice(abs(point_area()));
        }
        
        /*! \brief Returns the bounding box for this triangle
        */
        constexpr AxBox2<T>   bounds() const noexcept
        {
            return {
                min_elem(min_elem(a, b), c), 
                max_elem(max_elem(a, b), c)
            };
        }
        
        //! TRUE if this triangle is wound in counter-clockwise with its points
        constexpr bool    is_ccw() const noexcept
        {
            return point_area() < zero_v<T>;
        }
        
        //! TRUE if this triangle is wound in clockwise with its points
        constexpr bool      is_clockwise() const noexcept
        {
            return point_area() > zero_v<T>;
        }
        
        //! Perimeter of this triangel
        //! \note Might not be reliable for non-floating point types
        T       perimeter() const
        {
            return (b-a).length() + (c-b).length() + (a-c).length();
        }

        /*! \brief "Point area" of the points
        
            This is a helper to area and other functions, 
            simply does an "area" of the point deltas, 
            no sign correction, no scaling.
        */
        constexpr square_t<T>   point_area() const noexcept
        {
            return delta_area(b, a) + delta_area(c, b) + delta_area(a, c);
        }
    };

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
    constexpr AxBox2<T>   aabb(const Triangle2<T>& tri) noexcept
    {
        return tri.bounds();
    }


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
        return tri.point_area();
    }

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

    /*! \brief Computes the area of a 2D triangle
    */
    template <typename T>
    constexpr square_t<T>    area(const Triangle2<T>& tri) noexcept
    {
        return tri.area();
    }

    /*! \brief TRUE if the triangle is defined in a counter-clockwise fashion
    */
    template <typename T>
    constexpr bool    is_ccw(const Triangle2<T>& tri)noexcept
    {
        return tri.is_ccw();
    }

    /*! \brief TRUE if the triangle is defined in a clockwise fashion
    */
    template <typename T>
    bool    is_clockwise(const Triangle2<T>& tri)
    {
        return tri.is_clockwise();
    }

    /*! \brief Computes the perimeter of the triangle
    */
    template <typename T>
    T       perimeter(const Triangle2<T>& tri)
    {   
        return tri.perimeter();
    }


}

YQ_TYPE_DECLARE(yq::Triangle2D)
YQ_TYPE_DECLARE(yq::Triangle2F)
YQ_TYPE_DECLARE(yq::Triangle2I)
YQ_TYPE_DECLARE(yq::Triangle2U)

