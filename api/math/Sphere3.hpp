////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>
#include <math/Vector3.hpp>

namespace yq {

    /*! \brief Sphere in three dimensions
    
        This structure represents a sphere with an origin/point and a radius
    */
    template <typename T>
    struct Sphere3 {
        //! Our component type (captures the template parameter)
        using component_type   = T;

        //! Point/origin of the sphere
        Vector3<T>  point;
        
        //! Radius of the sphere
        T           radius;
        
        constexpr Sphere3() noexcept = default;
        constexpr Sphere3(const Vector3<T>& pt, T r) : point(pt), radius(r) {}
        constexpr Sphere3(nan_t) : Sphere3(Vector3<T>(NAN), nan_v<T>) {}
        constexpr Sphere3(zero_t) : Sphere3(Vector3<T>(ZERO), zero_v<T>) {}

        //! Defaulted equality operator
        constexpr bool operator==(const Sphere3&) const noexcept = default;
        
        constexpr Sphere3   operator+() const noexcept;
        constexpr Sphere3   operator-() const noexcept;
        
        constexpr Sphere3   operator+(const Vector3<T>&) const noexcept;
        Sphere3&            operator+=(const Vector3<T>&) noexcept;
        constexpr Sphere3   operator-(const Vector3<T>&) const noexcept;
        Sphere3&            operator-=(const Vector3<T>&) noexcept;
        
        template <typename U>
        requires trait::is_arithmetic_v<U>
        Sphere3<trait::product_t<T,U>> operator*(U) const noexcept;
        
        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
        Sphere3<T>& operator*=(U) noexcept;
            
        template <typename U>
        requires trait::is_arithmetic_v<U>
        Sphere3<trait::quotient_t<T,U>> operator/(U) const noexcept;
        
        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_div_v<T,U>)
        Sphere3<T>& operator/=(U) noexcept;


        constexpr AxBox3<T> bounds() const noexcept;

        /*! \brief Computes the diameter of a sphere
        */
        constexpr T           diameter() const noexcept;

        /*! \brief Computes the surface area of a 3D sphere
        */
        constexpr trait::square_t<T>     surface_area() const noexcept;

        //! Returns a fixed copy of the circle (if it's invalid and possible to do)
        constexpr Sphere3   fixed() const noexcept;

        //! TRUE if the radius is greater than zero!
        constexpr bool    valid() const noexcept;

        /*! \brief Computes the volume of a 3D sphere
        */
        constexpr trait::cube_t<T>       volume() const noexcept;
    };

    YQ_IEEE754_1(Sphere3)

//  --------------------------------------------------------
//  COMPOSITION

    YQ_NAN_1(Sphere3, Sphere3<T>(NAN))
    YQ_ZERO_1(Sphere3, Sphere3<T>(ZERO))

    //! Creates a sphere from a point and radius
    template <typename T>
    constexpr Sphere3<T>  sphere(const Vector3<T>& point, std::type_identity_t<T> radius) noexcept
    {
        return {point, radius};
    }

//  --------------------------------------------------------
//  --------------------------------------------------------

    YQ_IS_FINITE_1(Sphere3, is_finite(v.point) && is_finite(v.radius))
    YQ_IS_NAN_1(Sphere3, is_nan(v.point) || is_nan(v.radius))

    template <typename T, typename U>
    requires trait::is_arithmetic_v<T>
    Sphere3<trait::product_t<T,U>> operator*(T, const Sphere3<U>&);

    //! Returns the axially aligned box of a sphere
    template <typename T>
    constexpr AxBox3<T>   aabb(const Sphere3<T>& sph) noexcept;


    /*! \brief Computes the diameter of a sphere
    */
    template <typename T>
    constexpr T           diameter(const Sphere3<T>&sph) noexcept;

    /*! \brief Checks for validity
    
        A valid sphere is one whose radius is greater or equal to zer
    */
    template <typename T>
    constexpr bool  is_valid(const Sphere3<T>&sph) noexcept;


    /*! \brief Computes the surface area of a 3D sphere
    */
    template <typename T>
    constexpr trait::square_t<T>     surface_area(const Sphere3<T>& sph) noexcept;

    /*! \brief Computes the volume of a 3D sphere
    */
    template <typename T>
    constexpr trait::cube_t<T>       volume(const Sphere3<T>&sph) noexcept;
}

YQ_TYPE_DECLARE(yq::Sphere3D)
YQ_TYPE_DECLARE(yq::Sphere3F)
YQ_TYPE_DECLARE(yq::Sphere3I)
YQ_TYPE_DECLARE(yq::Sphere3U)

