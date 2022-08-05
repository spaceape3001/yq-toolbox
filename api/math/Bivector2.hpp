////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>

namespace yq {
    template <typename T>
    struct Bivector2 {
        using component_type = T;
        square_t<T>     xy;
        auto operator<=>(const Bivector2&) const = default;
    };

    YQ_IEEE754_1(Bivector2)

//  --------------------------------------------------------
//  COMPOSITION

    constexpr Bivector2D  operator "" _xy2(unsigned long long int v) noexcept
    {
        return {(double) v};
    }

    constexpr Bivector2D  operator "" _xy2(long double v) noexcept
    {
        return {(double) v};
    }

    YQ_NAN_1(Bivector2, Bivector2<T>{nan_v<square_t<T>>})
    YQ_ZERO_1(Bivector2, Bivector2<T>{zero_v<square_t<T>>})
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_NAN_1(Bivector2, is_nan(v.xy))
    YQ_IS_FINITE_1(Bivector2, is_finite(v.xy))


//  --------------------------------------------------------
//  POSITIVE

    template <typename T>
    constexpr Bivector2<T> operator+(const Bivector2<T>& a) noexcept
    {
        return a;
    }


//  --------------------------------------------------------
//  NEGATIVE

    template <typename T>
    constexpr Bivector2<T> operator-(const Bivector2<T>& a)
    {
        return {-a.xy};
    }


//  --------------------------------------------------------
//  NORMALIZATION


//  --------------------------------------------------------
//  ADDITION

    template <typename T>
    constexpr Bivector2<T> operator+(const Bivector2<T>& a, const Bivector2<T>& b)
    {
        return {
            a.xy+b.xy
        };
    }

    template <typename T>
    Bivector2<T>& operator+=(Bivector2<T>& a, const Bivector2<T>& b)
    {
        a.xy += b.xy;
        return a;
    }

//  --------------------------------------------------------
//  SUBTRACTION


    template <typename T>
    constexpr Bivector2<T> operator-(const Bivector2<T>& a, const Bivector2<T>& b)
    {
        return {
            a.xy-b.xy
        };
    }

    template <typename T>
    Bivector2<T>& operator-=(Bivector2<T>& a, const Bivector2<T>& b)
    {
        a.xy -= b.xy;
        return a;
    }

//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T>
    requires std::is_floating_point_v<T>
    Bivector2<T> operator*(T a, const Bivector2<T>& b)
    {
        return { a*b.xy };
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    Bivector2<T> operator*(const Bivector2<T>& a, T b)
    {
        return { a.xy*b };
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    Bivector2<T> operator*=(Bivector2<T>& a, T b)
    {
        a.xy *= b;
        return a;
    }

//  --------------------------------------------------------
//  DIVISION

    template <typename T>
    requires std::is_floating_point_v<T>
    Bivector2<T> operator/(const Bivector2<T>& a, T b)
    {
        return { a.xy/b };
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    Bivector2<T> operator/=(Bivector2<T>& a, T b)
    {
        a.xy /= b;
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

YQ_TYPE_DECLARE(yq::Bivector2D)
YQ_TYPE_DECLARE(yq::Bivector2F)

