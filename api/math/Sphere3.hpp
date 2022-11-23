////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>
#include <math/AxBox3.hpp>
#include <math/Vector3.hpp>

namespace yq {
    template <typename T>
    struct Sphere3 {
        using component_t   = T;

        Vector3<T>  point;
        T           radius;
        
        constexpr bool operator==(const Sphere3&) const noexcept = default;
    };

    YQ_IEEE754_1(Sphere3)

//  --------------------------------------------------------
//  COMPOSITION

    YQ_NAN_1(Sphere3, { nan_v<Vector3<T>>, nan_v<T> })
    YQ_ZERO_1(Sphere3, { zero_v<Vector3<T>>, zero_v<T> })


    template <typename T>
    constexpr Sphere3<T>  sphere(const Vector3<T>& point, T radius) noexcept
    {
        return {point, radius};
    }

//  --------------------------------------------------------
//  GETTERS

//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_NAN_1(Sphere3, is_nan(v.point) || is_nan(v.radius))

    template <typename T>
    constexpr AxBox3<T>   aabb(const Sphere3<T>&a) noexcept
    {
        T       r   = abs(a.r);
        return {{
            a.pt.x - r,
            a.pt.y - r,
            a.pt.z - r
        },{
            a.pt.x + r,
            a.pt.y + r,
            a.pt.z + r
        }};
    }

    /*! \brief Checks for finiteness
    */
    template <typename T>
    constexpr bool is_finite(const Sphere3<T>&v)
    { 
        return is_finite(v.point) && is_finite(v.radius);
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


    /*! \brief Computes the diameter of a sphere
    */
    template <typename T>
    constexpr T           diameter(const Sphere3<T>&a) noexcept
    {
        return a.radius + a.radius;
    }

    /*! \brief Computes the surface area of a 3D sphere
    */
    template <typename T>
    constexpr square_t<T>     surface_area(const Sphere3<T>& sp) noexcept
    {
        return 4.0*pi*(sp.radius*sp.radius);
    }

    
    template <typename T>
    constexpr cube_t<T>       volume(const Sphere3<T>&sp) noexcept
    {
        return (4.0/3.0)*pi*(sp.radius*sp.radius*sp.radius);
    }
}

YQ_TYPE_DECLARE(yq::Sphere3D)
YQ_TYPE_DECLARE(yq::Sphere3F)
YQ_TYPE_DECLARE(yq::Sphere3I)
YQ_TYPE_DECLARE(yq::Sphere3U)

