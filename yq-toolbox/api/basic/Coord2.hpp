////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Coord.hpp"

namespace yq {

    template <typename T>
    struct Coord<T,2> {
        using component_type    = T;
        static constexpr const uint8_t  DIMS    = 2;
        T       i, j;
        constexpr bool operator==(const Coord&) const noexcept = default;

        template <typename U>
        requires (!std::is_same_v<T,U>)
        explicit constexpr operator Coord<U,2>() const noexcept
        {
            return { (U) i, (U) j };
        }

        Coord& operator=(T v)
        {
            i = j = v;
            return *this;
        }
        
        constexpr const T&    row() const noexcept { return i; }
        constexpr const T&    column() const noexcept { return j; }
    };


    //  --------------------------------------------------------
    //  COMPOSITION

    template <typename T>
    constexpr Coord2<T>    coord(T i, std::type_identity_t<T> j) noexcept
    {
        return { i, j };
    }
    
    template <typename T>
    constexpr Coord2<T>    coord2(T i)
    {
        return { i, i };
    }


    //  --------------------------------------------------------
    //  BASIC FUNCTIONS

    template <typename T>
    constexpr Coord2<T> max(const Coord2<T>&a, const Coord2<T>& b)
    {
        return { 
            max(a.i, b.i), 
            max(a.j, b.j)
        };
    }

    template <typename T>
    constexpr Coord2<T> min(const Coord2<T>&a, const Coord2<T>& b)
    {
        return { 
            min(a.i, b.i), 
            min(a.j, b.j)
        };
    }

    template <typename T>
    constexpr auto product(const Coord2<T>& a)
    {
        return a.i*a.j;
    }

    template <typename T>
    constexpr T sum(const Coord2<T>& a)
    {
        return a.i+a.j;
    }


    //  --------------------------------------------------------
    //  POSITIVE


    //  --------------------------------------------------------
    //  NEGATIVE

    template <typename T>
    constexpr Coord2<T>    operator-(const Coord2<T>& a)
    {
        return { -a.i, -a.j };
    }


    //  --------------------------------------------------------
    //  NORMALIZATION


    //  --------------------------------------------------------
    //  ADDITION
    
    template <typename T>
    constexpr Coord2<T> operator+(const Coord2<T>&a, const Coord2<T>&b)
    {
        return { a.i+b.i, a.j+b.j };
    }
    
    template <typename T>
    Coord2<T>&  operator+=(Coord2<T>& a, const Coord2<T>& b)
    {
        a.i += b.i;
        a.j += b.j;
        return a;
    }


    //  --------------------------------------------------------
    //  SUBTRACTION

    
    template <typename T>
    constexpr Coord2<T> operator-(const Coord2<T>&a, const Coord2<T>&b)
    {
        return { a.i-b.i, a.j-b.j };
    }
    
    template <typename T>
    Coord2<T>&  operator-=(Coord2<T>& a, const Coord2<T>& b)
    {
        a.i -= b.i;
        a.j -= b.j;
        return a;
    }


    //  --------------------------------------------------------
    //  MULTIPLICATION

    template <typename T, typename U>
    requires (std::is_arithmetic_v<T>)
    constexpr Coord2<decltype(T()*U())> operator*(T a, const Coord2<U>&b)
    {
        return { a*b.i, a*b.j };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U>)
    constexpr Coord2<decltype(T()*U())> operator*(const Coord2<T>& a, U b)
    {
        return { a.i*b, a.j*b };
    }

    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && std::is_same_v<T, decltype(T()*U())>)
    Coord2<T>& operator*=(Coord2<T>& a, U b)
    {
        a.i *= b;
        a.j *= b;
        return a;
    }

    template <typename T, typename U>
    constexpr Coord2<decltype(T()*U())> operator*(const Coord2<T>& a, const Coord2<U>& b)
    {
        return { a.i*b.i, a.j*b.j };
    }
    
    template <typename T, typename U>
    requires (std::is_same_v<T, decltype(T()*U())>)
    Coord2<T>& operator*=(Coord2<T>&a, const Coord2<U>& b)
    {
        a.i *= b.i;
        a.j *= b.j;
        return a;
    }
    
    
    //  --------------------------------------------------------
    //  DIVISION

    template <typename T, typename U>
    requires (std::is_arithmetic_v<U>)
    constexpr Coord2<decltype(T()/U())> operator/(const Coord2<T>& a, U b)
    {
        return { a.i/b, a.j/b };
    }

    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && std::is_same_v<T, decltype(T()/U())>)
    Coord2<T>& operator/=(Coord2<T>& a, U b)
    {
        a.i /= b;
        a.j /= b;
        return a;
    }

    template <typename T, typename U>
    constexpr Coord2<decltype(T()/U())> operator/(const Coord2<T>& a, const Coord2<U>& b)
    {
        return { a.i/b.i, a.j/b.j };
    }

    template <typename T, typename U>
    requires (std::is_same_v<T, decltype(T()/U())>)
    Coord2<T>& operator/=(Coord2<T>& a, const Coord2<U>& b)
    {
        a.i /= b.i;
        a.j /= b.j;
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
    S&  as_stream(S& s, const Coord2<I>& v)
    {
        return s << "[" << v.i << "," << v.j << "]";
    }
    
    template <typename T>
    Stream& operator<<(Stream&s, const Coord2<T>& v)
    {
        return as_stream(s, v);
    }

    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const Coord2<T>& v)
    {
        return as_stream(s, v);
    }
    
}
