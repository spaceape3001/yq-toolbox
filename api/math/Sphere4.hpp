////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_SPHERE4_HPP 1

#include <math/preamble.hpp>
#include <math/Vector4.hpp>

namespace yq {

    /*! \brief Hypersphere in four dimensions
    */
    template <typename T>
    struct Sphere4 {
        //! Our component type (captures the template parameter)
        using component_type   = T;

        //! Point/origin of the hypersphere
        Vector4<T>  point;

        //! Radius of the hypersphere
        T           radius;
        
        constexpr Sphere4() noexcept = default;
        constexpr Sphere4(const Vector4<T>& pt, T r) : point(pt), radius(r) {}
        constexpr Sphere4(nan_t) : Sphere4(Vector4<T>(NAN), nan_v<T>) {}
        constexpr Sphere4(zero_t) : Sphere4(Vector4<T>(ZERO), zero_v<T>) {}

        constexpr Sphere4(focus_t, const Vector4<T>& focus, const T dist) noexcept : Sphere4(focus, dist) {}
        Sphere4(focus_t, const Vector4<T>& focus, const Vector4<T>& edge);
        Sphere4(opposite_t, const Vector4<T>&, const Vector4<T>&);

        template <typename U>
        requires std::is_nothrow_convertible_v<T,U>
        explicit constexpr operator Sphere4<U>() const noexcept
        {
            return { (Vector4<U>) point, (U) radius };
        }
        
        template <typename U>
        requires (std::is_convertible_v<T,U> && !std::is_nothrow_convertible_v<T,U>)
        explicit constexpr operator Sphere4<U>() const 
        {
            return { (Vector4<U>) point, (U) radius };
        }

        //! Defaulted equality operator
        constexpr bool operator==(const Sphere4&) const noexcept = default;

        constexpr Sphere4   operator+() const noexcept;
        constexpr Sphere4   operator-() const noexcept;
        
        constexpr Sphere4   operator+(const Vector4<T>&) const noexcept;
        Sphere4&            operator+=(const Vector4<T>&) noexcept;
        constexpr Sphere4   operator-(const Vector4<T>&) const noexcept;
        Sphere4&            operator-=(const Vector4<T>&) noexcept;
        
        template <typename U>
        requires is_arithmetic_v<U>
        Sphere4<product_t<T,U>> operator*(U) const noexcept;
        
        template <typename U>
        requires (is_arithmetic_v<U> && self_mul_v<T,U>)
        Sphere4<T>& operator*=(U) noexcept;
            
        template <typename U>
        requires is_arithmetic_v<U>
        Sphere4<quotient_t<T,U>> operator/(U) const noexcept;
        
        template <typename U>
        requires (is_arithmetic_v<U> && self_div_v<T,U>)
        Sphere4<T>& operator/=(U) noexcept;
        
                //! Returns the bounding box for this sphere
        constexpr AxBox4<T>   bounds() const noexcept;

        /*! \brief Checks if the point is inside (or touching) the sphere
        */
        constexpr bool          contains(const Vector4<T>& pt) const noexcept;

        /*! \brief Computes the diameter of a hyper sphere
        */
        constexpr T     diameter() const noexcept;
    };
    
    YQ_IEEE754_1(Sphere4)
    YQ_INTEGER_1(Sphere4)
    YQ_IS_INTEGER_1(Sphere4)


//  --------------------------------------------------------
//  COMPOSITION

    //! Creates a hypersphere from a point and radius
    template <typename T>
    Sphere4<T>  hypersphere(const Vector4<T>& point, T radius)
    {
        return {point, radius};
    }

    //! Creates a hypersphere from a point and radius
    template <typename T>
    Sphere4<T>  sphere(const Vector4<T>& point, T radius)
    {
        return {point, radius};
    }

    YQ_NAN_1(Sphere4, Sphere4<T>(NAN))
    YQ_ZERO_1(Sphere4, Sphere4<T>(ZERO))

//  --------------------------------------------------------
//  --------------------------------------------------------
    
    YQ_IS_FINITE_1(Sphere4, is_finite(v.point) && is_finite(v.radius))
    YQ_IS_NAN_1(Sphere4, is_nan(v.point) || is_nan(v.radius))

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

