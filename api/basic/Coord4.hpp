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

    /*! \brief Four dimensional coordinate
    
        This is expanded in four diemnsions for the four-dimensional coordinate.
    */
    template <typename T>
    struct Coord<T,4> {
    
        //! Component type
        using component_type    = T;
        
        //! Number of dimensions
        static constexpr const uint8_t  DIMS    = 4;
        
        //! Coordinate in I
        T   i;

        //! Coordinate in J
        T   j;

        //! Coordinate in K
        T   k;

        //! Coordinate in L
        T   l;

        //! Default constructor
        constexpr Coord<T,4>() noexcept = default;
        
        //! Component-wise initializing constructor
        constexpr Coord<T,4>(T _i, T _j, T _k, T _l) noexcept : 
            i(_i), j(_j), k(_k), l(_l) {}
            
        //! Constructs ALL components to same value
        constexpr Coord<T,4>(all_t, T _v) noexcept : Coord<T,4>(_v, _v, _v, _v) {}
        
        //! Constructs a ZERO coordinate
        constexpr Coord<T,4>(zero_t) noexcept : Coord<T,4>(ALL, zero_v<T>) {}

        //! Defaulted equality  operator
        constexpr bool operator==(const Coord&) const noexcept = default;

        //! Conversion operator to other 4-dimensional coordinates
        template <typename U>
        requires (!std::is_same_v<T,U>)
        explicit constexpr operator Coord<U,4>() const noexcept
        {
            return { (U) i, (U) j, (U) k, (U) l };
        }

        //! Allows for uniform coordinate assignments.
        Coord& operator=(T v)
        {
            i = j = k = l = v;
            return *this;
        }
    };


    //  --------------------------------------------------------
    //  COMPOSITION

    /*! \brief Composes a four dimensional coordinate from arguments */
    template <typename T>
    constexpr Coord4<T>    coord(T i, std::type_identity_t<T> j, std::type_identity_t<T> k, std::type_identity_t<T> l) noexcept
    {
        return { i, j, k, l };
    }
    
    /*! \brief Construct a uniform 4-dimensional coordinate */
    template <typename T>
    constexpr Coord4<T>    coord4(T i)
    {
        return { i, i, i, i };
    }


    //  --------------------------------------------------------
    //  BASIC FUNCTIONS

    /*! \brief Max of two coordinates, done by element */
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

    /*! \brief Min of two coordinates, done by element */
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

    /*! \brief Product of the components */
    template <typename T>
    constexpr auto product(const Coord4<T>& a)
    {
        return a.i*a.j*a.k*a.l;
    }

    /*! \brief Sum of the components */
    template <typename T>
    constexpr T sum(const Coord4<T>& a)
    {
        return a.i+a.j+a.k+a.l;
    }

    //  --------------------------------------------------------
    //  POSITIVE


    //  --------------------------------------------------------
    //  NEGATIVE

    //! Negate the coordinate
    template <typename T>
    constexpr Coord4<T>    operator-(const Coord4<T>& a)
    {
        return { -a.i, -a.j, -a.k, -a.l };
    }


    //  --------------------------------------------------------
    //  NORMALIZATION


    //  --------------------------------------------------------
    //  ADDITION
    
    //! Add two coordinates together
    template <typename T>
    constexpr Coord4<T> operator+(const Coord4<T>&a, const Coord4<T>&b)
    {
        return { a.i+b.i, a.j+b.j, a.k+b.k, a.l+b.l };
    }
    
    //! Increment left coordinate with right
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
    
    //! Subtract two coordinates
    template <typename T>
    constexpr Coord4<T> operator-(const Coord4<T>&a, const Coord4<T>&b)
    {
        return { a.i-b.i, a.j-b.j, a.k-b.k, a.l-b.l };
    }
    
    //! Decrement the left coordinate with right
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

    //! Scale the coordinate
    template <typename T, typename U>
    requires (std::is_arithmetic_v<T>)
    constexpr Coord4<decltype(T()*U())> operator*(T a, const Coord4<U>&b)
    {
        return { a*b.i, a*b.j, a*b.k, a*b.l };
    }
    
    //! Scale the coordinate
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U>)
    constexpr Coord4<decltype(T()*U())> operator*(const Coord4<T>& a, U b)
    {
        return { a.i*b, a.j*b, a.k*b, a.l*b };
    }

    //! Scale the coordinate
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

    //! Multiplies two coordinates together, term by term
    template <typename T, typename U>
    constexpr Coord4<decltype(T()*U())> operator*(const Coord4<T>& a, const Coord4<U>& b)
    {
        return { a.i*b.i, a.j*b.j, a.k*b.k, a.l*b.l };
    }
    
    //! Self-Multiplies left coordinate with right, term by term
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

    //! Reduces the cooordinate, returns result
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U>)
    constexpr Coord4<decltype(T()/U())> operator/(const Coord4<T>& a, U b)
    {
        return { a.i/b, a.j/b, a.k/b, a.l/b };
    }

    //! Reduces the cooordinate in place, returns result
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

    //! Divides two coordinates, term by term
    template <typename T, typename U>
    constexpr Coord4<decltype(T()/U())> operator/(const Coord4<T>& a, const Coord4<U>& b)
    {
        return { a.i/b.i, a.j/b.j, a.k/b.k, a.l/b.l };
    }

    //! Self divides left coordinate by right
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

    //! Helper to stream out a coordinate
    template <typename S, typename I>
    S&  as_stream(S& s, const Coord4<I>& v)
    {
        return s << "[" << v.i << "," << v.j << "," << v.k << "," << v.l << "]";
    }
    
    //! Helper to stream out a coordinate
    template <typename T>
    Stream& operator<<(Stream&s, const Coord4<T>& v)
    {
        return as_stream(s, v);
    }

    //! Helper to log out a coordinate
    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const Coord4<T>& v)
    {
        return as_stream(s, v);
    }
    
}
