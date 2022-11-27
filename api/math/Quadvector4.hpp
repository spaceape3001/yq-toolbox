////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>

namespace yq {
    template <typename T>
    struct Quadvector4 {
        using component_type = T;
        fourth_t<T>     xyzw;
        constexpr auto operator<=>(const Quadvector4&) const noexcept = default;
    };

    YQ_IEEE754_1(Quadvector4)

//  --------------------------------------------------------
//  COMPOSITION

    constexpr Quadvector4D   operator "" _xyzw4(unsigned long long int v) noexcept
    {
        return {(double) v};
    }

    constexpr Quadvector4D   operator "" _xyzw4(long double v) noexcept
    {
        return {(double) v};
    }

    YQ_NAN_1(Quadvector4, Quadvector4<T>{nan_v<fourth_t<T>>})
    YQ_ZERO_1(Quadvector4, Quadvector4<T>{zero_v<fourth_t<T>>})

//  --------------------------------------------------------
//  GETTERS

//  --------------------------------------------------------
//  BASIC FUNCTIONS
    
    YQ_IS_NAN_1(Quadvector4, is_nan(v.xyzw))
    YQ_IS_FINITE_1(Quadvector4, is_finite(v.xyzw))


//  --------------------------------------------------------
//  POSITIVE


    template <typename T>
    constexpr Quadvector4<T> operator+(const Quadvector4<T>& a) noexcept
    {
        return a;
    }
    
//  --------------------------------------------------------
//  NEGATIVE

    template <typename T>
    constexpr Quadvector4<T> operator-(const Quadvector4<T>& a) noexcept
    {
        return {-a.xyzw};
    }
    

//  --------------------------------------------------------
//  NORMALIZATION


//  --------------------------------------------------------
//  ADDITION

    template <typename T>
    constexpr Quadvector4<T> operator+(const Quadvector4<T>& a, const Quadvector4<T>& b) noexcept
    {
        return { a.xyzw + b.xyzw };
    }

    template <typename T>
    Quadvector4<T>& operator+=(Quadvector4<T>& a, const Quadvector4<T>& b) noexcept
    {
        a.xyzw += b.xyzw;
        return a;
    }


//  --------------------------------------------------------
//  SUBTRACTION

    template <typename T>
    constexpr Quadvector4<T> operator-(const Quadvector4<T>& a, const Quadvector4<T>& b) noexcept
    {
        return { a.xyzw - b.xyzw };
    }

    template <typename T>
    Quadvector4<T>& operator-=(Quadvector4<T>& a, const Quadvector4<T>& b) noexcept
    {
        a.xyzw -= b.xyzw;
        return a;
    }

//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Quadvector4<T> operator*(T a, const Quadvector4<T>& b) noexcept
    {
        return { a*b.xyzw };
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Quadvector4<T> operator*(const Quadvector4<T>& a, T b) noexcept
    {
        return { a.xyzw*b };
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    Quadvector4<T> operator*=(Quadvector4<T>& a, T b) noexcept
    {
        a.xyzw*=b;
        return a;
    }


//  --------------------------------------------------------
//  DIVISION

    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Quadvector4<T> operator/(const Quadvector4<T>& a, T b) noexcept
    {
        return { a.xyzw/b };
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    Quadvector4<T> operator/=(Quadvector4<T>& a, T b) noexcept
    {
        a.xyzw/=b;
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

YQ_TYPE_DECLARE(yq::Quadvector4D)
YQ_TYPE_DECLARE(yq::Quadvector4F)

