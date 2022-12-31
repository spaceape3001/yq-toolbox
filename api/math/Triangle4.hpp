////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>
#include <math/AxBox4.hpp>
#include <math/Vector4.hpp>
#include <math/TriangleData.hpp>

namespace yq {

    /*! \brief 3D triangle
    */
    template <typename T>
    struct Triangle4 {
        //! Capture the template parameter
        using component_type    = T;
    
        Vector4<T>   a, b, c;
        
        //! Defaulted equality operator
        constexpr bool operator==(const Triangle4&) const noexcept = default;
        
        //! Implicit conversion to triangle data
        constexpr operator TriangleData<Vector4<T>> () const noexcept 
        { 
            return { a, b, c }; 
        }

        /*! \brief Returns the bounding box for this triangle
        */
        constexpr AxBox4<T>   bounds() const noexcept
        {
            return {
                min_elem(min_elem(a, b), c), 
                max_elem(max_elem(a, b), c)
            };
        }

        //! Perimeter of this triangel
        //! \note Might not be reliable for non-floating point types
        T       perimeter() const
        {
            return (b-a).length() + (c-b).length() + (a-c).length();
        }
    };

    YQ_IEEE754_1(Triangle4)

//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Create a triangle from three points */
    template <typename T>
    Triangle4<T>    triangle(const Vector4<T>& a, const Vector4<T>& b, const Vector4<T>& c)
    {
        return { a, b, c };
    }

    YQ_NAN_1(Triangle4, { nan_v<Vector4<T>>, nan_v<Vector4<T>>, nan_v<Vector4<T>> })
    YQ_ZERO_1(Triangle4, { zero_v<Vector4<T>>, zero_v<Vector4<T>>, zero_v<Vector4<T>> })

//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_FINITE_1(Triangle4, is_finite(v.a) && is_finite(v.b) && is_finite(v.c))
    YQ_IS_NAN_1(Triangle4, is_nan(v.a) || is_nan(v.b) || is_nan(v.c) )

    /*! \brief Creates an axially aligned bounding box from the three triangle vertices */
    template <typename T>
    constexpr AxBox4<T>   aabb(const Triangle4<T>& tri) noexcept
    {
        return tri.bounds();
    }

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

    /*! \brief Computes the perimeter of the triangle
    */
    template <typename T>
    constexpr T       perimeter(const Triangle4<T>& tri)noexcept
    {
        return tri.perimeter();
    }

}

YQ_TYPE_DECLARE(yq::Triangle4D)
YQ_TYPE_DECLARE(yq::Triangle4F)
YQ_TYPE_DECLARE(yq::Triangle4I)
YQ_TYPE_DECLARE(yq::Triangle4U)

