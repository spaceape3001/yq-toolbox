////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Coord.hpp"

namespace yq {

    template <typename T>
    struct Coord<T,3> {
        using component_type    = T;
        static constexpr const uint8_t  DIMS    = 3;
        T       i, j, k;
        constexpr bool operator==(const Coord&) const noexcept = default;

        template <typename U>
        requires (!std::is_same_v<T,U>)
        explicit constexpr operator Coord<U,3>() const noexcept
        {
            return { (U) i, (U) j, (U) k };
        }

        Coord& operator=(T v)
        {
            i = j = k = v;
            return *this;
        }
    };


    //  --------------------------------------------------------
    //  COMPOSITION

    template <typename T>
    constexpr Coord3<T>    coord(T i, std::type_identity_t<T> j, std::type_identity_t<T> k) noexcept
    {
        return { i, j, k};
    }
    
    template <typename T>
    constexpr Coord3<T>    coord3(T i)
    {
        return { i, i, i };
    }


    //  --------------------------------------------------------
    //  BASIC FUNCTIONS

    template <typename T>
    constexpr Coord3<T> max(const Coord3<T>&a, const Coord3<T>& b)
    {
        return { 
            max(a.i, b.i), 
            max(a.j, b.j), 
            max(a.k, b.k)
        };
    }

    template <typename T>
    constexpr Coord3<T> min(const Coord3<T>&a, const Coord3<T>& b)
    {
        return { 
            min(a.i, b.i), 
            min(a.j, b.j), 
            min(a.k, b.k)
        };
    }

    template <typename T>
    constexpr auto product(const Coord3<T>& a)
    {
        return a.i*a.j*a.k;
    }

    template <typename T>
    constexpr T sum(const Coord3<T>& a)
    {
        return a.i+a.j+a.k;
    }


    //  --------------------------------------------------------
    //  POSITIVE


    //  --------------------------------------------------------
    //  NEGATIVE

    template <typename T>
    constexpr Coord3<T>    operator-(const Coord3<T>& a)
    {
        return { -a.i, -a.j, -a.k };
    }


    //  --------------------------------------------------------
    //  NORMALIZATION


    //  --------------------------------------------------------
    //  ADDITION
    
    template <typename T>
    constexpr Coord3<T> operator+(const Coord3<T>&a, const Coord3<T>&b)
    {
        return { a.i+b.i, a.j+b.j, a.k+b.k };
    }
    
    template <typename T>
    Coord3<T>&  operator+=(Coord3<T>& a, const Coord3<T>& b)
    {
        a.i += b.i;
        a.j += b.j;
        a.k += b.k;
        return a;
    }


    //  --------------------------------------------------------
    //  SUBTRACTION

    
    template <typename T>
    constexpr Coord3<T> operator-(const Coord3<T>&a, const Coord3<T>&b)
    {
        return { a.i-b.i, a.j-b.j, a.k-b.k };
    }
    
    template <typename T>
    Coord3<T>&  operator-=(Coord3<T>& a, const Coord3<T>& b)
    {
        a.i -= b.i;
        a.j -= b.j;
        a.k -= b.k;
        return a;
    }


    //  --------------------------------------------------------
    //  MULTIPLICATION

    template <typename T, typename U>
    requires (std::is_arithmetic_v<T>)
    constexpr Coord3<decltype(T()*U())> operator*(T a, const Coord3<U>&b)
    {
        return { a*b.i, a*b.j, a*b.k };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U>)
    constexpr Coord3<decltype(T()*U())> operator*(const Coord3<T>& a, U b)
    {
        return { a.i*b, a.j*b, a.k*b };
    }

    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && std::is_same_v<T, decltype(T()*U())>)
    Coord3<T>& operator*=(Coord3<T>& a, U b)
    {
        a.i *= b;
        a.j *= b;
        a.k *= b;
        return a;
    }

    template <typename T, typename U>
    constexpr Coord3<decltype(T()*U())> operator*(const Coord3<T>& a, const Coord3<U>& b)
    {
        return { a.i*b.i, a.j*b.j, a.k*b.k };
    }
    
    template <typename T, typename U>
    requires (std::is_same_v<T, decltype(T()*U())>)
    Coord3<T>& operator*=(Coord3<T>&a, const Coord3<U>& b)
    {
        a.i *= b.i;
        a.j *= b.j;
        a.k *= b.k;
        return a;
    }
    
    
    //  --------------------------------------------------------
    //  DIVISION

    template <typename T, typename U>
    requires (std::is_arithmetic_v<U>)
    constexpr Coord3<decltype(T()/U())> operator/(const Coord3<T>& a, U b)
    {
        return { a.i/b, a.j/b, a.k/b };
    }

    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && std::is_same_v<T, decltype(T()/U())>)
    Coord3<T>& operator/=(Coord3<T>& a, U b)
    {
        a.i /= b;
        a.j /= b;
        a.k /= b;
        return a;
    }

    template <typename T, typename U>
    constexpr Coord3<decltype(T()/U())> operator/(const Coord3<T>& a, const Coord3<U>& b)
    {
        return { a.i/b.i, a.j/b.j, a.k/b.k };
    }

    template <typename T, typename U>
    requires (std::is_same_v<T, decltype(T()/U())>)
    Coord3<T>& operator/=(Coord3<T>& a, const Coord3<U>& b)
    {
        a.i /= b.i;
        a.j /= b.j;
        a.k /= b.k;
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
    S&  as_stream(S& s, const Coord3<I>& v)
    {
        return s << "[" << v.i << "," << v.j << "," << v.k << "]";
    }
    
    template <typename T>
    Stream& operator<<(Stream&s, const Coord3<T>& v)
    {
        return as_stream(s, v);
    }

    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const Coord3<T>& v)
    {
        return as_stream(s, v);
    }
    
}
