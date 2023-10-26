////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_SPHERE4_HPP 1

#include <math/preamble.hpp>
#include <math/vector/Vector4.hpp>

namespace yq {

    /*! \brief Hypersphere in four dimensions
    */
    template <typename T>
    struct Sphere4 {
        //! Our component type (captures the template parameter)
        using component_type   = T;

        //! Point/origin of the hypersphere
        Vector4<T>  center;

        //! Radius of the hypersphere
        T           radius;
        
        //! Default constructor
        constexpr Sphere4() noexcept = default;

        //! Component wise constructor
        constexpr Sphere4(const Vector4<T>& pt, T r) : center(pt), radius(r) {}

        //! Not a number constructor
        consteval Sphere4(nan_t) : Sphere4(Vector4<T>(NAN), nan_v<T>) {}
        
        //! Unit sphere constructor
        consteval Sphere4(unit_t) : Sphere4(Vector4<T>(ZERO), one_v<T>) {}

        //! Zero constructor
        consteval Sphere4(zero_t) : Sphere4(Vector4<T>(ZERO), zero_v<T>) {}

        //! Construct with focus and distance
        constexpr Sphere4(focus_t, const Vector4<T>& focus, const T dist) noexcept : Sphere4(focus, dist) {}

        //! Construct with focus and point
        Sphere4(focus_t, const Vector4<T>& focus, const Vector4<T>& edge);

        //! Construct with two opposite points
        Sphere4(opposite_t, const Vector4<T>&, const Vector4<T>&);

        //! Convert to another sphere with compatible data type
        template <typename U>
        requires std::is_nothrow_convertible_v<T,U>
        explicit constexpr operator Sphere4<U>() const noexcept
        {
            return { (Vector4<U>) center, (U) radius };
        }
        
        //! Convert to another sphere with compatible data type
        template <typename U>
        requires (std::is_convertible_v<T,U> && !std::is_nothrow_convertible_v<T,U>)
        explicit constexpr operator Sphere4<U>() const 
        {
            return { (Vector4<U>) center, (U) radius };
        }

        //! Defaulted equality operator
        constexpr bool operator==(const Sphere4&) const noexcept = default;

        //! Positive (affirmative) operator
        constexpr Sphere4   operator+() const noexcept;

        //! Negation operator
        constexpr Sphere4   operator-() const noexcept;
        
        //! Return a moved sphere by the given displacement
        constexpr Sphere4   operator+(const Vector4<T>&) const noexcept;

        //! Moves the sphere by the given displacement
        Sphere4&            operator+=(const Vector4<T>&) noexcept;

        //! Return a sphere anti-moved by the given displacement
        constexpr Sphere4   operator-(const Vector4<T>&) const noexcept;

        //! Moves the sphere against the given displacement
        Sphere4&            operator-=(const Vector4<T>&) noexcept;
        
        //! Returns a scaled sphere by the given term
        template <typename U>
        requires is_arithmetic_v<U>
        Sphere4<product_t<T,U>> operator*(U) const noexcept;
        
        //! Scales this sphere by the given amount
        template <typename U>
        requires (is_arithmetic_v<U> && self_mul_v<T,U>)
        Sphere4<T>& operator*=(U) noexcept;
            
        //! Returns a reduced sphere by the given term
        template <typename U>
        requires is_arithmetic_v<U>
        Sphere4<quotient_t<T,U>> operator/(U) const noexcept;
        
        //! Reduces this sphere by the given amount
        template <typename U>
        requires (is_arithmetic_v<U> && self_div_v<T,U>)
        Sphere4<T>& operator/=(U) noexcept;
        
                //! Returns the bounding box for this sphere
        constexpr AxBox4<T>   bounds() const noexcept;

        /*! \brief Checks if the center is inside (or touching) the sphere
        */
        constexpr bool          contains(const Vector4<T>& pt) const noexcept;

        /*! \brief Computes the diameter of a hyper sphere
        */
        constexpr T     diameter() const noexcept;

        //! Returns a fixed copy of the circle (if it's invalid and possible to do)
        constexpr Sphere4   fixed() const noexcept;
        
        //! Computes the hypervolume of this sphere
        constexpr fourth_t<T>   hypervolume() const noexcept;

        //! TRUE if the radius is greater than zero!
        constexpr bool    valid() const noexcept;

    };
    
    YQ_IEEE754_1(Sphere4)
    YQ_INTEGER_1(Sphere4)
    YQ_IS_INTEGER_1(Sphere4)


//  --------------------------------------------------------
//  COMPOSITION

    //! Creates a hypersphere from a center and radius
    template <typename T>
    Sphere4<T>  hypersphere(const Vector4<T>& center, T radius)
    {
        return {center, radius};
    }

    //! Creates a hypersphere from a center and radius
    template <typename T>
    Sphere4<T>  sphere(const Vector4<T>& center, T radius)
    {
        return {center, radius};
    }

    YQ_NAN_1(Sphere4, Sphere4<T>(NAN))
    YQ_ZERO_1(Sphere4, Sphere4<T>(ZERO))

//  --------------------------------------------------------
//  --------------------------------------------------------
    
    YQ_IS_FINITE_1(Sphere4, is_finite(v.center) && is_finite(v.radius))
    YQ_IS_NAN_1(Sphere4, is_nan(v.center) || is_nan(v.radius))

    //! Scales the right sphere by the left amount
    template <typename T, typename U>
    requires is_arithmetic_v<T>
    Sphere4<product_t<T,U>> operator*(T a, const Sphere4<U>& b);

    //! Returns the axially aligned box of a sphere
    template <typename T>
    AxBox4<T>   aabb(const Sphere4<T>& sph);

    /*! \brief Computes the diameter of a hyper sphere
    */
    template <typename T>
    constexpr T  diameter(const Sphere4<T>& sph) noexcept;


}

YQ_TYPE_DECLARE(yq::Sphere4D)
YQ_TYPE_DECLARE(yq::Sphere4F)
YQ_TYPE_DECLARE(yq::Sphere4I)
YQ_TYPE_DECLARE(yq::Sphere4U)

