////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Coord.hpp"
#include <trait/has_zero.hpp>
#include <basic/keywords.hpp>

namespace yq {

    /*! \brief Two dimensional coordinate
    
        This is expanded in two diemnsions for the two-dimensional coordinate.
    */
    template <typename T>
    struct Coord<T,2> {
        using component_type    = T;
        static constexpr const uint8_t  DIMS    = 2;
        T       i, j;

        constexpr Coord<T,2>() noexcept = default;
        constexpr Coord<T,2>(T _i, T _j) noexcept : 
            i(_i), j(_j) {}
        constexpr Coord<T,2>(all_t, T _v) noexcept : Coord<T,2>(_v, _v) {}
        constexpr Coord<T,2>(zero_t) noexcept : Coord<T,2>(ALL, zero_v<T>) {}

        //! Defaulted equality  operator
        constexpr bool operator==(const Coord&) const noexcept = default;

        //! Conversion operator to other 2-dimensional coordinates
        template <typename U>
        requires (!std::is_same_v<T,U>)
        explicit constexpr operator Coord<U,2>() const noexcept
        {
            return { (U) i, (U) j };
        }

        //! Allows for uniform coordinate assignments.
        Coord& operator=(T v)
        {
            i = j = v;
            return *this;
        }
        
        //! Alias for row index (matrix-style)
        constexpr const T&    row() const noexcept { return i; }
        
        //! Alias for column index (matrix-style)
        constexpr const T&    column() const noexcept { return j; }
    };


    //  --------------------------------------------------------
    //  COMPOSITION

    /*! \brief Composes a two dimensional coordinate from arguments */
    template <typename T>
    constexpr Coord2<T>    coord(T i, std::type_identity_t<T> j) noexcept
    {
        return { i, j };
    }
    
    /*! \brief Construct a uniform 2-dimensional coordinate */
    template <typename T>
    constexpr Coord2<T>    coord2(T i)
    {
        return { i, i };
    }


    //  --------------------------------------------------------
    //  BASIC FUNCTIONS

    /*! \brief Max of two coordinates, done by element */
    template <typename T>
    constexpr Coord2<T> max(const Coord2<T>&a, const Coord2<T>& b)
    {
        return { 
            max(a.i, b.i), 
            max(a.j, b.j)
        };
    }

    /*! \brief Min of two coordinates, done by element */
    template <typename T>
    constexpr Coord2<T> min(const Coord2<T>&a, const Coord2<T>& b)
    {
        return { 
            min(a.i, b.i), 
            min(a.j, b.j)
        };
    }

    /*! \brief Product of the components */
    template <typename T>
    constexpr auto product(const Coord2<T>& a)
    {
        return a.i*a.j;
    }

    /*! \brief Sum of the components */
    template <typename T>
    constexpr T sum(const Coord2<T>& a)
    {
        return a.i+a.j;
    }


    //  --------------------------------------------------------
    //  POSITIVE


    //  --------------------------------------------------------
    //  NEGATIVE

    //! Negate the coordinate
    template <typename T>
    constexpr Coord2<T>    operator-(const Coord2<T>& a)
    {
        return { -a.i, -a.j };
    }


    //  --------------------------------------------------------
    //  NORMALIZATION


    //  --------------------------------------------------------
    //  ADDITION
    
    //! Add two coordinates together
    template <typename T>
    constexpr Coord2<T> operator+(const Coord2<T>&a, const Coord2<T>&b)
    {
        return { a.i+b.i, a.j+b.j };
    }
    
    //! Increment left coordinate with right
    template <typename T>
    Coord2<T>&  operator+=(Coord2<T>& a, const Coord2<T>& b)
    {
        a.i += b.i;
        a.j += b.j;
        return a;
    }


    //  --------------------------------------------------------
    //  SUBTRACTION

    
    //! Subtract two coordinates
    template <typename T>
    constexpr Coord2<T> operator-(const Coord2<T>&a, const Coord2<T>&b)
    {
        return { a.i-b.i, a.j-b.j };
    }
    
    //! Decrement the left coordinate with right
    template <typename T>
    Coord2<T>&  operator-=(Coord2<T>& a, const Coord2<T>& b)
    {
        a.i -= b.i;
        a.j -= b.j;
        return a;
    }


    //  --------------------------------------------------------
    //  MULTIPLICATION

    //! Scale the coordinate
    template <typename T, typename U>
    requires (std::is_arithmetic_v<T>)
    constexpr Coord2<decltype(T()*U())> operator*(T a, const Coord2<U>&b)
    {
        return { a*b.i, a*b.j };
    }
    
    //! Scale the coordinate
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U>)
    constexpr Coord2<decltype(T()*U())> operator*(const Coord2<T>& a, U b)
    {
        return { a.i*b, a.j*b };
    }

    //! Self-scale the left coordinate with the right
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && std::is_same_v<T, decltype(T()*U())>)
    Coord2<T>& operator*=(Coord2<T>& a, U b)
    {
        a.i *= b;
        a.j *= b;
        return a;
    }

    //! Multiplies two coordinates together, term by term
    template <typename T, typename U>
    constexpr Coord2<decltype(T()*U())> operator*(const Coord2<T>& a, const Coord2<U>& b)
    {
        return { a.i*b.i, a.j*b.j };
    }
    
    //! Self-Multiplies left coordinate with right, term by term
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

    //! Reduces the cooordinate, returns result
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U>)
    constexpr Coord2<decltype(T()/U())> operator/(const Coord2<T>& a, U b)
    {
        return { a.i/b, a.j/b };
    }

    //! Reduces the cooordinate in place, returns result
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && std::is_same_v<T, decltype(T()/U())>)
    Coord2<T>& operator/=(Coord2<T>& a, U b)
    {
        a.i /= b;
        a.j /= b;
        return a;
    }

    //! Divides two coordinates, term by term
    template <typename T, typename U>
    constexpr Coord2<decltype(T()/U())> operator/(const Coord2<T>& a, const Coord2<U>& b)
    {
        return { a.i/b.i, a.j/b.j };
    }

    //! Self divides left coordinate by right
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

    //! Helper to stream out a coordinate
    template <typename S, typename I>
    S&  as_stream(S& s, const Coord2<I>& v)
    {
        return s << "[" << v.i << "," << v.j << "]";
    }
    
    //! Helper to stream out a coordinate
    template <typename T>
    Stream& operator<<(Stream&s, const Coord2<T>& v)
    {
        return as_stream(s, v);
    }

    //! Helper to log out a coordinate
    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const Coord2<T>& v)
    {
        return as_stream(s, v);
    }
    
}
