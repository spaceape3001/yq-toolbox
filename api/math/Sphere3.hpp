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

    /*! \brief Sphere in three dimensions
    
        This structure represents a sphere with an origin/point and a radius
    */
    template <typename T>
    struct Sphere3 {
        //! Our component type (captures the template parameter)
        using component_t   = T;

        //! Point/origin of the sphere
        Vector3<T>  point;
        
        //! Radius of the sphere
        T           radius;
        
        //! Defaulted equality operator
        constexpr bool operator==(const Sphere3&) const noexcept = default;
        
        constexpr AxBox3<T> bounds() const noexcept
        {
            T       r   = abs(radius);
            return {
                all(point) - r,
                all(point) + r
            };
        }

        /*! \brief Computes the diameter of a sphere
        */
        constexpr T           diameter() const noexcept
        {
            return radius + radius;
        }

        /*! \brief Computes the surface area of a 3D sphere
        */
        constexpr square_t<T>     surface_area() const noexcept
        {
            return 4.0*pi*(radius*radius);
        }

        /*! \brief Computes the volume of a 3D sphere
        */
        constexpr cube_t<T>       volume() const noexcept
        {
            return (4.0/3.0)*pi*(radius*radius*radius);
        }
    };

    YQ_IEEE754_1(Sphere3)

//  --------------------------------------------------------
//  COMPOSITION

    YQ_NAN_1(Sphere3, { nan_v<Vector3<T>>, nan_v<T> })
    YQ_ZERO_1(Sphere3, { zero_v<Vector3<T>>, zero_v<T> })

    //! Creates a sphere from a point and radius
    template <typename T>
    constexpr Sphere3<T>  sphere(const Vector3<T>& point, std::type_identity_t<T> radius) noexcept
    {
        return {point, radius};
    }

//  --------------------------------------------------------
//  GETTERS

//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_FINITE_1(Sphere3, is_finite(v.point) && is_finite(v.radius))
    YQ_IS_NAN_1(Sphere3, is_nan(v.point) || is_nan(v.radius))

    //! Returns the axially aligned box of a sphere
    template <typename T>
    constexpr AxBox3<T>   aabb(const Sphere3<T>& sph) noexcept
    {
        return sph.bounds();
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
    constexpr T           diameter(const Sphere3<T>&sph) noexcept
    {
        return sph.diameter();
    }

    /*! \brief Computes the surface area of a 3D sphere
    */
    template <typename T>
    constexpr square_t<T>     surface_area(const Sphere3<T>& sph) noexcept
    {
        return sph.surface_area();
    }

    /*! \brief Computes the volume of a 3D sphere
    */
    template <typename T>
    constexpr cube_t<T>       volume(const Sphere3<T>&sph) noexcept
    {
        return sph.volume();
    }
}

YQ_TYPE_DECLARE(yq::Sphere3D)
YQ_TYPE_DECLARE(yq::Sphere3F)
YQ_TYPE_DECLARE(yq::Sphere3I)
YQ_TYPE_DECLARE(yq::Sphere3U)

