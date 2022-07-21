////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Coord.hpp"

namespace yq {

    template <typename T>
    struct Coord<T,4> {
        using component_type    = T;
        static constexpr const uint8_t  DIMS    = 4;
        T       i, j, k, l;
        constexpr bool operator==(const Coord&) const noexcept = default;

        template <typename U>
        requires (!std::is_same_v<T,U>)
        explicit constexpr operator Coord<U,4>() const noexcept
        {
            return { (U) i, (U) j, (U) k, (U) l };
        }

        Coord& operator=(T v)
        {
            i = j = k = l = v;
            return *this;
        }
    };


    //  --------------------------------------------------------
    //  COMPOSITION

    template <typename T>
    constexpr Coord4<T>    coord(T i, std::type_identity_t<T> j, std::type_identity_t<T> k, std::type_identity_t<T> l) noexcept
    {
        return { i, j, k, l };
    }
    
    template <typename T>
    constexpr Coord4<T>    coord4(T i)
    {
        return { i, i, i, i };
    }


    //  --------------------------------------------------------
    //  BASIC FUNCTIONS

    template <typename T>
    constexpr Coord4<T> max(const Coord4<T>&a, const Coord4<T>& b)
    {
        return { 
            max(a.i, b.i), 
            max(a.j, b.j), 
            max(a.k, b.k), 
            max(a.l, b.l)
        };
    }

    template <typename T>
    constexpr Coord4<T> min(const Coord4<T>&a, const Coord4<T>& b)
    {
        return { 
            min(a.i, b.i), 
            min(a.j, b.j), 
            min(a.k, b.k), 
            min(a.l, b.l)
        };
    }

    template <typename T>
    constexpr auto product(const Coord4<T>& a)
    {
        return a.i*a.j*a.k*a.l;
    }

    template <typename T>
    constexpr T sum(const Coord4<T>& a)
    {
        return a.i+a.j+a.k+a.l;
    }

    //  --------------------------------------------------------
    //  POSITIVE


    //  --------------------------------------------------------
    //  NEGATIVE

    template <typename T>
    constexpr Coord4<T>    operator-(const Coord4<T>& a)
    {
        return { -a.i, -a.j, -a.k, -a.l };
    }


    //  --------------------------------------------------------
    //  NORMALIZATION


    //  --------------------------------------------------------
    //  ADDITION
    
    template <typename T>
    constexpr Coord4<T> operator+(const Coord4<T>&a, const Coord4<T>&b)
    {
        return { a.i+b.i, a.j+b.j, a.k+b.k, a.l+b.l };
    }
    
    template <typename T>
    Coord4<T>&  operator+=(Coord4<T>& a, const Coord4<T>& b)
    {
        a.i += b.i;
        a.j += b.j;
        a.k += b.k;
        a.l += b.l;
        return a;
    }


    //  --------------------------------------------------------
    //  SUBTRACTION

    
    template <typename T>
    constexpr Coord4<T> operator-(const Coord4<T>&a, const Coord4<T>&b)
    {
        return { a.i-b.i, a.j-b.j, a.k-b.k, a.l-b.l };
    }
    
    template <typename T>
    Coord4<T>&  operator-=(Coord4<T>& a, const Coord4<T>& b)
    {
        a.i -= b.i;
        a.j -= b.j;
        a.k -= b.k;
        a.l -= b.l;
        return a;
    }


    //  --------------------------------------------------------
    //  MULTIPLICATION

    template <typename T, typename U>
    requires (std::is_arithmetic_v<T>)
    constexpr Coord4<decltype(T()*U())> operator*(T a, const Coord4<U>&b)
    {
        return { a*b.i, a*b.j, a*b.k, a*b.l };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U>)
    constexpr Coord4<decltype(T()*U())> operator*(const Coord4<T>& a, U b)
    {
        return { a.i*b, a.j*b, a.k*b, a.l*b };
    }

    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && std::is_same_v<T, decltype(T()*U())>)
    Coord4<T>& operator*=(Coord4<T>& a, U b)
    {
        a.i *= b;
        a.j *= b;
        a.k *= b;
        a.l *= b;
        return a;
    }

    template <typename T, typename U>
    constexpr Coord4<decltype(T()*U())> operator*(const Coord4<T>& a, const Coord4<U>& b)
    {
        return { a.i*b.i, a.j*b.j, a.k*b.k, a.l*b.l };
    }
    
    template <typename T, typename U>
    requires (std::is_same_v<T, decltype(T()*U())>)
    Coord4<T>& operator*=(Coord4<T>&a, const Coord4<U>& b)
    {
        a.i *= b.i;
        a.j *= b.j;
        a.k *= b.k;
        a.l *= b.l;
        return a;
    }
    
    
    //  --------------------------------------------------------
    //  DIVISION

    template <typename T, typename U>
    requires (std::is_arithmetic_v<U>)
    constexpr Coord4<decltype(T()/U())> operator/(const Coord4<T>& a, U b)
    {
        return { a.i/b, a.j/b, a.k/b, a.l/b };
    }

    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && std::is_same_v<T, decltype(T()/U())>)
    Coord4<T>& operator/=(Coord4<T>& a, U b)
    {
        a.i /= b;
        a.j /= b;
        a.k /= b;
        a.l /= b;
        return a;
    }

    template <typename T, typename U>
    constexpr Coord4<decltype(T()/U())> operator/(const Coord4<T>& a, const Coord4<U>& b)
    {
        return { a.i/b.i, a.j/b.j, a.k/b.k, a.l/b.l };
    }

    template <typename T, typename U>
    requires (std::is_same_v<T, decltype(T()/U())>)
    Coord4<T>& operator/=(Coord4<T>& a, const Coord4<U>& b)
    {
        a.i /= b.i;
        a.j /= b.j;
        a.k /= b.k;
        a.l /= b.l;
        return a;
    }

    //  --------------------------------------------------------
    //  DOT PRODUCT


    //  --------------------------------------------------------
    //  INNER PRODUCT


    //  --------------------------------------------------------
    //  OUTER PRODUCT


    ///  --------------------------------------------------------
    //  OTIMES PRODUCT

    //  --------------------------------------------------------
    //  PROJECTIONS

    //  --------------------------------------------------------
    //  ADVANCED FUNCTIONS


    //  --------------------------------------------------------
    //  CONDITIONAL INCLUDES

    template <typename S, typename I>
    S&  as_stream(S& s, const Coord4<I>& v)
    {
        return s << "[" << v.i << "," << v.j << "," << v.k << "," << v.l << "]";
    }
    
    template <typename T>
    Stream& operator<<(Stream&s, const Coord4<T>& v)
    {
        return as_stream(s, v);
    }

    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const Coord4<T>& v)
    {
        return as_stream(s, v);
    }
    
}
