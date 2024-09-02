////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_SPHERE3_HPP 1


#include <0/math/preamble.hpp>
#include <0/math/vector/Vector3.hpp>

#include <yq/keywords.hpp>
#include <yq/trait/product.hpp>
#include <yq/trait/quotient.hpp>
#include <yq/trait/self_divide.hpp>
#include <yq/trait/self_multiply.hpp>

namespace yq {

    /*! \brief Sphere in three dimensions
    
        This structure represents a sphere with an origin/center and a radius
    */
    template <typename T>
    struct Sphere3 {
        //! Our component type (captures the template parameter)
        using component_type   = T;

        //! Point/origin of the sphere
        Vector3<T>  center;
        
        //! Radius of the sphere
        T           radius;
        
        //! Default constructor
        constexpr Sphere3() noexcept = default;
        
        //! Component wise constructor
        constexpr Sphere3(const Vector3<T>& pt, T r) : center(pt), radius(r) {}
        
        //! Not a number constructor
        consteval Sphere3(nan_t) : Sphere3(Vector3<T>(NAN), nan_v<T>) {}
        
        //! Unit sphere constructor
        consteval Sphere3(unit_t) : Sphere3(Vector3<T>(ZERO), one_v<T>) {}
        
        //! Zero constructor
        consteval Sphere3(zero_t) : Sphere3(Vector3<T>(ZERO), zero_v<T>) {}

        //! Construct with focus and distance
        constexpr Sphere3(focus_t, const Vector3<T>& focus, const T dist) noexcept : Sphere3(focus, dist) {}
        
        //! Construct with focus and point
        Sphere3(focus_t, const Vector3<T>& focus, const Vector3<T>& edge);
        
        //! Construct with two opposite points
        Sphere3(opposite_t, const Vector3<T>&, const Vector3<T>&);

        //! Convert to another sphere with compatible data type
        template <typename U>
        requires std::is_nothrow_convertible_v<T,U>
        explicit constexpr operator Sphere3<U>() const noexcept
        {
            return { (Vector3<U>) center, (U) radius };
        }
        
        //! Convert to another sphere with compatible data type
        template <typename U>
        requires (std::is_convertible_v<T,U> && !std::is_nothrow_convertible_v<T,U>)
        explicit constexpr operator Sphere3<U>() const 
        {
            return { (Vector3<U>) center, (U) radius };
        }

        //! Defaulted equality operator
        constexpr bool operator==(const Sphere3&) const noexcept = default;
        
        //! Positive (affirmative) operator
        constexpr Sphere3   operator+() const noexcept;
        
        //! Negation operator
        constexpr Sphere3   operator-() const noexcept;
        
        //! Return a moved sphere by the given displacement
        constexpr Sphere3   operator+(const Vector3<T>&) const noexcept;
        
        //! Moves the sphere by the given displacement
        Sphere3&            operator+=(const Vector3<T>&) noexcept;
        
        //! Return a sphere anti-moved by the given displacement
        constexpr Sphere3   operator-(const Vector3<T>&) const noexcept;
        
        //! Moves the sphere against the given displacement
        Sphere3&            operator-=(const Vector3<T>&) noexcept;
        
        //! Returns a scaled sphere by the given term
        template <typename U>
        requires is_arithmetic_v<U>
        Sphere3<product_t<T,U>> operator*(U) const noexcept;
        
        //! Scales this sphere by the given amount
        template <typename U>
        requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
        Sphere3<T>& operator*=(U) noexcept;
            
        //! Returns a reduced sphere by the given term
        template <typename U>
        requires is_arithmetic_v<U>
        Sphere3<quotient_t<T,U>> operator/(U) const noexcept;
        
        //! Reduces this sphere by the given amount
        template <typename U>
        requires (is_arithmetic_v<U> && self_divide_v<T,U>)
        Sphere3<T>& operator/=(U) noexcept;

        //! Bounding box for this sphere
        constexpr AxBox3<T> bounds() const noexcept;

        /*! \brief Checks if the center is inside (or touching) the sphere
        */
        constexpr bool          contains(const Vector3<T>& pt) const noexcept;

        /*! \brief Computes the diameter of a sphere
        */
        constexpr T           diameter() const noexcept;

        /*! \brief Computes the surface area of a 3D sphere
        */
        constexpr square_t<T>     surface_area() const noexcept;

        //! Returns a fixed copy of the circle (if it's invalid and possible to do)
        constexpr Sphere3   fixed() const noexcept;

        //! TRUE if the radius is greater than zero!
        constexpr bool    valid() const noexcept;

        /*! \brief Computes the volume of a 3D sphere
        */
        constexpr cube_t<T>       volume() const noexcept;
    };

    YQ_IEEE754_1(Sphere3)
    YQ_INTEGER_1(Sphere3)
    YQ_IS_INTEGER_1(Sphere3)

//  --------------------------------------------------------
//  COMPOSITION

    YQ_NAN_1(Sphere3, Sphere3<T>(NAN))
    YQ_ZERO_1(Sphere3, Sphere3<T>(ZERO))

    //! Creates a sphere from a center and radius
    template <typename T>
    constexpr Sphere3<T>  sphere(const Vector3<T>& center, std::type_identity_t<T> radius) noexcept
    {
        return {center, radius};
    }

//  --------------------------------------------------------
//  --------------------------------------------------------

    YQ_IS_FINITE_1(Sphere3, is_finite(v.center) && is_finite(v.radius))
    YQ_IS_NAN_1(Sphere3, is_nan(v.center) || is_nan(v.radius))

    //! Scales the right sphere by the left amount
    template <typename T, typename U>
    requires is_arithmetic_v<T>
    Sphere3<product_t<T,U>> operator*(T, const Sphere3<U>&);

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
    constexpr square_t<T>     surface_area(const Sphere3<T>& sph) noexcept;

    /*! \brief Computes the volume of a 3D sphere
    */
    template <typename T>
    constexpr cube_t<T>       volume(const Sphere3<T>&sph) noexcept;
}

YQ_TYPE_DECLARE(yq::Sphere3D)
YQ_TYPE_DECLARE(yq::Sphere3F)
YQ_TYPE_DECLARE(yq::Sphere3I)
YQ_TYPE_DECLARE(yq::Sphere3U)

