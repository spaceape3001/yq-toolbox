////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Coord.hpp"

namespace yq {

    template <typename T>
    struct Coord<T,1> {
        using component_type    = T;
        static constexpr const uint8_t  DIMS    = 1;
        T       i;
        constexpr bool operator==(const Coord&) const noexcept = default;

        template <typename U>
        requires (!std::is_same_v<T,U>)
        explicit constexpr operator Coord<U,1>() const noexcept
        {
            return { (U) i };
        }

        Coord& operator=(T v)
        {
            i = v;
            return *this;
        }
    };


    //  --------------------------------------------------------
    //  COMPOSITION

    template <typename T>
    constexpr Coord1<T>    coord(T i) noexcept
    {
        return { i };
    }
    
    template <typename T>
    constexpr Coord1<T>    coord1(T i)
    {
        return { i };
    }


    //  --------------------------------------------------------
    //  BASIC FUNCTIONS

    template <typename T>
    constexpr Coord1<T> max(const Coord1<T>&a, const Coord1<T>& b)
    {
        return { 
            max(a.i, b.i)
        };
    }

    template <typename T>
    constexpr Coord1<T> min(const Coord1<T>&a, const Coord1<T>& b)
    {
        return { 
            min(a.i, b.i)
        };
    }

    template <typename T>
    constexpr T product(const Coord1<T>& a)
    {
        return a.i;
    }

    template <typename T>
    constexpr T sum(const Coord1<T>& a)
    {
        return a.i;
    }

    //  --------------------------------------------------------
    //  POSITIVE


    //  --------------------------------------------------------
    //  NEGATIVE

    template <typename T>
    constexpr Coord1<T>    operator-(const Coord1<T>& a)
    {
        return { -a.i };
    }


    //  --------------------------------------------------------
    //  NORMALIZATION


    //  --------------------------------------------------------
    //  ADDITION
    
    template <typename T>
    constexpr Coord1<T> operator+(const Coord1<T>&a, const Coord1<T>&b)
    {
        return { a.i+b.i };
    }
    
    template <typename T>
    Coord1<T>&  operator+=(Coord1<T>& a, const Coord1<T>& b)
    {
        a.i += b.i;
        return a;
    }


    //  --------------------------------------------------------
    //  SUBTRACTION

    
    template <typename T>
    constexpr Coord1<T> operator-(const Coord1<T>&a, const Coord1<T>&b)
    {
        return { a.i-b.i };
    }
    
    template <typename T>
    Coord1<T>&  operator-=(Coord1<T>& a, const Coord1<T>& b)
    {
        a.i -= b.i;
        return a;
    }


    //  --------------------------------------------------------
    //  MULTIPLICATION

    template <typename T, typename U>
    requires (std::is_arithmetic_v<T>)
    constexpr Coord1<decltype(T()*U())> operator*(T a, const Coord1<U>&b)
    {
        return { a*b.i };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U>)
    constexpr Coord1<decltype(T()*U())> operator*(const Coord1<T>& a, U b)
    {
        return { a.i*b };
    }

    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && std::is_same_v<T, decltype(T()*U())>)
    Coord1<T>& operator*=(Coord1<T>& a, U b)
    {
        a.i *= b;
        return a;
    }

    template <typename T, typename U>
    constexpr Coord1<decltype(T()*U())> operator*(const Coord1<T>& a, const Coord1<U>& b)
    {
        return { a.i*b.i };
    }
    
    template <typename T, typename U>
    requires (std::is_same_v<T, decltype(T()*U())>)
    Coord1<T>& operator*=(Coord1<T>&a, const Coord1<U>& b)
    {
        a.i *= b.i;
        return a;
    }
    
    
    //  --------------------------------------------------------
    //  DIVISION

    template <typename T, typename U>
    requires (std::is_arithmetic_v<U>)
    constexpr Coord1<decltype(T()/U())> operator/(const Coord1<T>& a, U b)
    {
        return { a.i/b };
    }

    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && std::is_same_v<T, decltype(T()/U())>)
    Coord1<T>& operator/=(Coord1<T>& a, U b)
    {
        a.i /= b;
        return a;
    }

    template <typename T, typename U>
    constexpr Coord1<decltype(T()/U())> operator/(const Coord1<T>& a, const Coord1<U>& b)
    {
        return { a.i/b.i };
    }

    template <typename T, typename U>
    requires (std::is_same_v<T, decltype(T()/U())>)
    Coord1<T>& operator/=(Coord1<T>& a, const Coord1<U>& b)
    {
        a.i /= b.i;
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
    S&  as_stream(S& s, const Coord1<I>& v)
    {
        return s << "[" << v.i << "]";
    }
    
    template <typename T>
    Stream& operator<<(Stream&s, const Coord1<T>& v)
    {
        return as_stream(s, v);
    }

    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const Coord1<T>& v)
    {
        return as_stream(s, v);
    }
    
}
