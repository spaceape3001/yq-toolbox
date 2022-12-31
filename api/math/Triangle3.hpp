////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>
#include <math/AxBox3.hpp>
#include <math/Triangle2.hpp>
#include <math/Vector3.hpp>

namespace yq {
    /*! \brief 3D triangle
    */
    template <typename T>
    struct Triangle3 {
        //! Capture the template parameter
        using component_type    = T;
    
        Vector3<T>   a, b, c;
        
        //! Defaulted equality operator
        constexpr bool operator==(const Triangle3&) const noexcept = default;
        
        //! Implicit conversion to triangle data
        constexpr operator TriangleData<Vector3<T>> () const noexcept 
        { 
            return { a, b, c }; 
        }

        /*! \brief Returns the bounding box for this triangle
        */
        constexpr AxBox3<T>   bounds() const noexcept
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
    
    YQ_IEEE754_1(Triangle3)

//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Create a triangle from three points */
    template <typename T>
    Triangle3<T>    triangle(const Vector3<T>& a, const Vector3<T>& b, const Vector3<T>& c)
    {
        return { a, b, c };
    }

    YQ_NAN_1(Triangle3, { nan_v<Vector3<T>>, nan_v<Vector3<T>>, nan_v<Vector3<T>> })
    YQ_ZERO_1(Triangle3, { zero_v<Vector3<T>>, zero_v<Vector3<T>>, zero_v<Vector3<T>> })

//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_FINITE_1(Triangle3, is_finite(v.a) && is_finite(v.b) && is_finite(v.c))
    YQ_IS_NAN_1(Triangle3, is_nan(v.a) || is_nan(v.b) || is_nan(v.c) )

    
    /*! \brief Creates an axially aligned bounding box from the three triangle vertices */
    template <typename T>
    constexpr AxBox3<T>   aabb(const Triangle3<T>& tri) noexcept
    {
        return tri.bounds();
    }

    /*! \brief Reduces 3D triangle into 2D along xy plane */
    template <typename T>
    Triangle2<T>   xy(const Triangle3<T>& a)
    {
        return { xy(a.a), xy(a.b), xy(a.c) };
    }
    
    /*! \brief Promotes 2D triangle to 3D triangle */
    template <typename T>
    Triangle3<T>   xy(const Triangle2<T>& a, std::type_identity_t<T> z)
    {
        return { xy(a.a, z), xy(a.b, z), xy(a.c, z) };
    }

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

    /*! \brief Computes the perimeter of the triangle
    */
    template <typename T>
    T       perimeter(const Triangle3<T>& tri)
    {
        return tri.perimeter();
    }

}

YQ_TYPE_DECLARE(yq::Triangle3D)
YQ_TYPE_DECLARE(yq::Triangle3F)
YQ_TYPE_DECLARE(yq::Triangle3I)
YQ_TYPE_DECLARE(yq::Triangle3U)

