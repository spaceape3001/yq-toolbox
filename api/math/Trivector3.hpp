////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>

namespace yq {

    /*! \brief 3D Tri-vector */
    template <typename T>
    struct Trivector3 {
        //! Our argument type
        using component_type = T;
        T     xyz;

        constexpr Trivector3() noexcept = default;
        constexpr Trivector3(T _xyz) noexcept : xyz(_xyz) {}
        constexpr Trivector3(all_t, T v) noexcept : xyz(v) {}
        template <typename=void> requires trait::has_nan_v<T>
        consteval Trivector3(nan_t) noexcept : Trivector3(ALL, nan_v<T>) {}
        consteval Trivector3(one_t) noexcept : Trivector3(ALL, one_v<T>) {}
        constexpr Trivector3(xyz_t, T v) noexcept : xyz(v) {}
        consteval Trivector3(xyz_t) noexcept : Trivector3(XYZ, one_v<T>) {}
        consteval Trivector3(zero_t) noexcept : Trivector3(ALL, zero_v<T>) {}
        
        //! Defaulted comparison operator
        constexpr auto operator<=>(const Trivector3&) const noexcept = default;

        /*! \brief Affirmation (positive) operator
        */
        constexpr Trivector3 operator+() const noexcept;

        /*! \brief Negation operator
        */
        constexpr Trivector3 operator-() const noexcept;

        constexpr Multivector3<T> operator+(T b) const noexcept;
        constexpr Trivector3 operator+(const Trivector3& b) const noexcept;
        Trivector3& operator+=(const Trivector3& b) noexcept;
        constexpr Multivector3<T> operator+(const Bivector3<T>& b) const noexcept;
        constexpr Multivector3<T> operator+(const Multivector3<T>& b) const noexcept;
        constexpr Multivector3<T> operator+(const Vector3<T>& b) const noexcept;
        constexpr Multivector3<T> operator-(T b) const noexcept;
        constexpr Trivector3 operator-(const Trivector3& b) const noexcept;
        Trivector3& operator-=(const Trivector3& b) noexcept;
        constexpr Multivector3<T> operator-(const Bivector3<T>& b) const noexcept;
        constexpr Multivector3<T> operator-(const Multivector3<T>& b) const noexcept;
        constexpr Multivector3<T> operator-(const Vector3<T>& b) const noexcept;

        template <typename U>
        requires trait::is_arithmetic_v<U>
        constexpr Trivector3<product_t<T,U>> operator*(U b) const noexcept;

        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
        Trivector3& operator*=(U b) noexcept;

        template <typename U>
        requires trait::is_arithmetic_v<U>
        constexpr Trivector3<quotient_t<T,U>> operator/(const U b) const noexcept;

        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_div_v<T,U>)
        constexpr Trivector3& operator/=(U b) noexcept;
    };

    YQ_IEEE754_1(Trivector3)

//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Literal to construct a trivector
    */
    constexpr Trivector3D   operator "" _xyz3(unsigned long long int v) noexcept
    {
        return Trivector3D(XYZ, (double) v);
    }

    /*! \brief Literal to construct a trivector
    */
    constexpr Trivector3D   operator "" _xyz3(long double v) noexcept
    {
        return Trivector3D(XYZ, (double) v);
    }

    YQ_NAN_1(Trivector3, Trivector3<T>{nan_v<cube_t<T>>})
    YQ_ZERO_1(Trivector3, Trivector3<T>{zero_v<cube_t<T>>})
    
//  --------------------------------------------------------
//  GETTERS

//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_NAN_1(Trivector3, is_nan(v.xyz))
    YQ_IS_FINITE_1(Trivector3, is_finite(v.xyz))


//  --------------------------------------------------------
//  --------------------------------------------------------

    template <typename T>
    constexpr Multivector3<T> operator+(T a, const Trivector3<T>& b) noexcept;

    template <typename T>
    constexpr Multivector3<T> operator-(T a, const Trivector3<T>& b) noexcept;

    /*! \brief Scaling multiplication of trivector
    
        This will (scale) multiply a trivector, returns the result.
    */
    template <typename T, typename U>
    requires trait::is_arithmetic_v<T>
    constexpr Trivector3<T> operator*(T a, const Trivector3<U>& b) noexcept;



}

YQ_TYPE_DECLARE(yq::Trivector3D)
YQ_TYPE_DECLARE(yq::Trivector3F)

