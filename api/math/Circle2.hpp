////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>
#include <math/Vector2.hpp>
#include <math/AxBox2.hpp>

namespace yq {

    /*! \brief Circle in two diemsnions
    */
    template <typename T>
    struct Circle2 {
    
        //! Component type (ie, the template parameter)
        using component_t   = T;

        //! Center point
        Vector2<T>  point;
        
        //! Radius
        T           radius;
        
        //! Equality operator (defaulted)
        constexpr bool operator==(const Circle2&) const noexcept = default;
    };

    YQ_IEEE754_1(Circle2)


//  --------------------------------------------------------
//  COMPOSITION

    YQ_NAN_1(Circle2, { nan_v<Vector2<T>>, nan_v<T> })
    YQ_ZERO_1(Circle2, { zero_v<Vector2<T>>, zero_v<T> })

    /*! \brief Creates cricle from point and radius
    */
    template <typename T>
    Circle2<T>  circle(const Vector2<T>& point, T radius)
    {
        return {point, radius};
    }

//  --------------------------------------------------------
//  BASIC FUNCTIONS

    
    /*! \brief Checks for finiteness
    */
    template <typename T>
    constexpr bool is_finite(const Circle2<T>&v)
    { 
        return is_finite(v.point) && is_finite(v.radius);
    }
    
    YQ_IS_NAN_1(Circle2, is_nan(v.point) || is_nan(v.radius))

    /*! \brief Bounding box for a circle
    */
    template <typename T>
    constexpr AxBox2<T>   aabb(const Circle2<T>&a) noexcept
    {
        T       r   = abs(a.r);
        return {{
            a.pt.x - r,
            a.pt.y - r
        },{
            a.pt.x + r,
            a.pt.y + r
        }};
    }
    
    /*! \brief Checks for validity
    
        A valid circle is one whose radius is greater or equal to zer
    */
    template <typename T>
    constexpr bool  is_valid(const Circle2<T>&a) noexcept
    {
        return a.radius >= T{};
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
//  ADVANCED FUNCTIONS


    /*! \brief Computes the area of a 2D circle
    */
    template <typename T>
    constexpr square_t<T> area(const Circle2<T>& a) noexcept
    {
        return std::numbers::pi_v<ieee754_t<T>> * (a.radius*a.radius);
    }
    
    /*! \brief Computes smallest circle containing the given box
    
        \note The resulting circle will be centered within the box
    */
    template <typename T>
    constexpr Circle2<T>    circumcircle(const AxBox2<T>& a) 
    {
        return { half_v<T> * (a.hi+a.lo), half_v<T>*length(a.hi-a.lo) };
    }
    
    /*! \brief Computes the circumference of a circle
    */
    template <typename T>
    constexpr T     circumference(const Circle2<T>& a) noexcept
    {
        return ieee754_t<T>(2.) * std::numbers::pi_v<ieee754_t<T>> * a.radius;
    }

    /*! \brief Computes the diameter of a circle
    */
    template <typename T>
    constexpr T     diameter(const Circle2<T>&a) noexcept
    {
        return a.radius + a.radius;
    }

    /*! \brief Computes biggest circle within the bounding box
    
        \note The resulting circle will be centered within the box
    */
    template <typename T>
    constexpr Circle2<T>    incircle(const AxBox2<T>& a) noexcept
    {
        return { center(a), 0.5*component_min(a.hi-a.lo) };
    }

    /*! \brief Computes the perimeter (aka circumference) of a circle
    */
    template <typename T>
    constexpr T   permimeter(const Circle2<T>& a) noexcept
    {
        return circumference(a);
    }

}

YQ_TYPE_DECLARE(yq::Circle2D)
YQ_TYPE_DECLARE(yq::Circle2F)
YQ_TYPE_DECLARE(yq::Circle2I)
YQ_TYPE_DECLARE(yq::Circle2U)

