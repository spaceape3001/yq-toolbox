////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>

namespace yq {
    template <typename T>
    struct Trivector3 {
        using component_type = T;
        cube_t<T>     xyz;
        constexpr auto operator<=>(const Trivector3&) const noexcept = default;
    };

    YQ_IEEE754_1(Trivector3)

//  --------------------------------------------------------
//  COMPOSITION

    constexpr Trivector3D   operator "" _xyz3(unsigned long long int v) noexcept
    {
        return {(double) v};
    }

    constexpr Trivector3D   operator "" _xyz3(long double v) noexcept
    {
        return {(double) v};
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
//  POSITIVE

    template <typename T>
    constexpr Trivector3<T> operator+(const Trivector3<T>&a) noexcept
    {
        return a;
    }


//  --------------------------------------------------------
//  NEGATIVE

    template <typename T>
    constexpr Trivector3<T> operator-(const Trivector3<T>&a) noexcept
    {
        return {-a.xyz};
    }


//  --------------------------------------------------------
//  NORMALIZATION


//  --------------------------------------------------------
//  ADDITION

    template <typename T>
    constexpr Trivector4<T> operator+(const Trivector3<T>& a, const Trivector3<T>& b) noexcept
    {
        return { a.xyz+b.xyz };
    }

    template <typename T>
    Trivector4<T>& operator+=(Trivector3<T>& a, const Trivector3<T>& b) noexcept
    {
        a.xyz+=b.xyz;
        return a;
    }

//  --------------------------------------------------------
//  SUBTRACTION


    template <typename T>
    constexpr Trivector3<T> operator-(const Trivector3<T>& a, const Trivector3<T>& b) noexcept
    {
        return { a.xyz-b.xyz };
    }

    template <typename T>
    Trivector3<T>& operator-=(Trivector3<T>& a, const Trivector3<T>& b) noexcept
    {
        a.xyz-=b.xyz;
        return a;
    }


//  --------------------------------------------------------
//  MULTIPLICATION


    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Trivector3<T> operator*(T a, const Trivector3<T>& b) noexcept
    {
        return { a*b.xyz };
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Trivector3<T> operator*(const Trivector3<T>& a, T b) noexcept
    {
        return { a.xyz*b };
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    Trivector3<T>& operator*=(Trivector3<T>& a, T b) noexcept
    {
        a.xyz *= b;
        return a;
    }

//  --------------------------------------------------------
//  DIVISION

    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Trivector3<T> operator/(const Trivector3<T>& a, T b) noexcept
    {
        return { a.xyz/b };
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Trivector3<T>& operator/=(Trivector3<T>& a, T b) noexcept
    {
        a.xyz /= b;
        return a;
    }

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

}

YQ_TYPE_DECLARE(yq::Trivector3D)
YQ_TYPE_DECLARE(yq::Trivector3F)

