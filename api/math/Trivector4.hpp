////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>

namespace yq {
    template <typename T>
    struct Trivector4 {
        using component_type = T;
        cube_t<T>     xyz, yzw, zwx, wxy;
        constexpr bool operator==(const Trivector4&) const noexcept = default;
    };

    YQ_IEEE754_1(Trivector4)


//  --------------------------------------------------------
//  COMPOSITION

    constexpr Trivector4D   operator "" _xyz4(unsigned long long int v) noexcept
    {
        return {(double) v, 0., 0., 0.};
    }

    constexpr Trivector4D   operator "" _xyz4(long double v) noexcept
    {
        return {(double) v, 0., 0., 0.};
    }

    constexpr Trivector4D   operator "" _yzw4(unsigned long long int v) noexcept
    {
        return {0., (double) v, 0., 0.};
    }

    constexpr Trivector4D   operator "" _yzw4(long double v) noexcept
    {
        return {0., (double) v, 0., 0.};
    }

    constexpr Trivector4D   operator "" _zwx4(unsigned long long int v) noexcept
    {
        return {0., 0.,  (double) v, 0.};
    }

    constexpr Trivector4D   operator "" _zwx4(long double v) noexcept
    {
        return {0., 0., (double) v,  0.};
    }

    constexpr Trivector4D   operator "" _wxy4(unsigned long long int v) noexcept
    {
        return {0., 0.,  0., (double) v };
    }

    constexpr Trivector4D   operator "" _wxy4(long double v) noexcept
    {
        return {0., 0., 0., (double) v};
    }

    YQ_NAN_1(Trivector4, Trivector4<T>{nan_v<cube_t<T>>, nan_v<cube_t<T>>, nan_v<cube_t<T>>, nan_v<cube_t<T>>})
    YQ_ZERO_1(Trivector4, Trivector4<T>{zero_v<cube_t<T>>, nan_v<cube_t<T>>, nan_v<cube_t<T>>, nan_v<cube_t<T>>})
    

//  --------------------------------------------------------
//  GETTERS


//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_NAN_1(Trivector4, is_nan(v.xyz) || is_nan(v.yzw) || is_nan(v.zwx) || is_nan(v.wxy))
    YQ_IS_FINITE_1(Trivector4, is_finite(v.xyz) && is_finite(v.yzw) && is_finite(v.zwx) && is_finite(v.wxy))


//  --------------------------------------------------------
//  POSITIVE

    template <typename T>
    constexpr Trivector4<T> operator+(const Trivector4<T>&a) noexcept
    {
        return a;
    }

//  --------------------------------------------------------
//  NEGATIVE

    template <typename T>
    constexpr Trivector4<T> operator-(const Trivector4<T>&a) noexcept
    {
        return {-a.xyz, -a.yzw, -a.zwx, -a.wxy};
    }


//  --------------------------------------------------------
//  NORMALIZATION


//  --------------------------------------------------------
//  ADDITION

    template <typename T>
    constexpr Trivector4<T> operator+(const Trivector4<T>& a, const Trivector4<T>& b) noexcept
    {
        return { a.xyz+b.xyz, a.yzw+b.yzw, a.zwx+b.zwx, a.wxy+b.wxy };
    }

    template <typename T>
    Trivector4<T>& operator+(Trivector4<T>& a, const Trivector4<T>& b) noexcept
    {
        a.xyz+=b.xyz; a.yzw+=b.yzw; a.zwx+=b.zwx; a.wxy+=b.wxy;
        return a;
    }



//  --------------------------------------------------------
//  SUBTRACTION

    template <typename T>
    constexpr Trivector4<T> operator-(const Trivector4<T>& a, const Trivector4<T>& b) noexcept
    {
        return { a.xyz-b.xyz, a.yzw-b.yzw, a.zwx-b.zwx, a.wxy-b.wxy };
    }

    template <typename T>
    Trivector4<T>& operator-(Trivector4<T>& a, const Trivector4<T>& b) noexcept
    {
        a.xyz-=b.xyz; a.yzw-=b.yzw; a.zwx-=b.zwx; a.wxy-=b.wxy;
        return a;
    }

//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Trivector4<T> operator*(T a, const Trivector4<T>& b) noexcept
    {
        return { a*b.xyz, a*b.yzw, a*b.zwx, a*b.wxy, };
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Trivector4<T> operator*(const Trivector4<T>& a, T b) noexcept
    {
        return { a.xyz*b, a.yzw*b, a.zwx*b, a.wxy*b, };
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    Trivector4<T>& operator*=(Trivector4<T>& a, T b) noexcept
    {
        a.xyz*=b; a.yzw*=b; a.zwx*=b; a.wxy*=b;
        return a;
    }

//  --------------------------------------------------------
//  DIVISION

    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Trivector4<T> operator/(const Trivector4<T>& a, T b) noexcept
    {
        return { a.xyz/b, a.yzw/b, a.zwx/b, a.wxy/b, };
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    Trivector4<T>& operator/=(Trivector4<T>& a, T b) noexcept
    {
        a.xyz/=b; a.yzw/=b; a.zwx/=b; a.wxy/=b;
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

YQ_TYPE_DECLARE(yq::Trivector4D)
YQ_TYPE_DECLARE(yq::Trivector4F)

