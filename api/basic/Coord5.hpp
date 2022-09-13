////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Coord.hpp"

namespace yq {

    /*! \brief Five dimensional coordinate
    
        This is expanded in five diemnsions for the five-dimensional arrays
    */
    template <typename T>
    struct Coord<T,5> {
        using component_type    = T;
        static constexpr const uint8_t  DIMS    = 5;
        T       i, j, k, l, m;

        //! Defaulted equality  operator
        constexpr bool operator==(const Coord&) const noexcept = default;

        //! Conversion operator
        template <typename U>
        requires (!std::is_same_v<T,U>)
        explicit constexpr operator Coord<U,5>() const noexcept
        {
            return { (U) i, (U) j, (U) k, (U) l, (U) m };
        }

        //! Allows for uniform coordinate assignments.
        Coord& operator=(T v)
        {
            i = j = k = l = m = v;
            return *this;
        }
    };


    //  --------------------------------------------------------
    //  COMPOSITION

    /*! \brief Composes a five dimensional coordinate from arguments */
    template <typename T>
    constexpr Coord5<T>    coord(T i, std::type_identity_t<T> j, std::type_identity_t<T> k, std::type_identity_t<T> l, std::type_identity_t<T> m ) noexcept
    {
        return { i, j, k, l, m };
    }
    
    /*! \brief Construct a uniform 5-dimensional coordinate */
    template <typename T>
    constexpr Coord5<T>    coord5(T i)
    {
        return { i, i, i, i, i };
    }


    //  --------------------------------------------------------
    //  BASIC FUNCTIONS

    /*! \brief Max of two coordinates, done by element */
    template <typename T>
    constexpr Coord5<T> max(const Coord5<T>&a, const Coord5<T>& b)
    {
        return { 
            max(a.i, b.i), 
            max(a.j, b.j), 
            max(a.k, b.k), 
            max(a.l, b.l), 
            max(a.m, b.m)
        };
    }

    /*! \brief Min of two coordinates, done by element */
    template <typename T>
    constexpr Coord5<T> min(const Coord5<T>&a, const Coord5<T>& b)
    {
        return { 
            min(a.i, b.i), 
            min(a.j, b.j), 
            min(a.k, b.k), 
            min(a.l, b.l), 
            min(a.m, b.m)
        };
    }

    /*! \brief Product of the components */
    template <typename T>
    constexpr auto product(const Coord5<T>& a)
    {
        return a.i*a.j*a.k*a.l*a.m;
    }

    /*! \brief Sum of the components */
    template <typename T>
    constexpr T sum(const Coord5<T>& a)
    {
        return a.i+a.j+a.k+a.l+a.m;
    }


    //  --------------------------------------------------------
    //  POSITIVE


    //  --------------------------------------------------------
    //  NEGATIVE

    //! Negate the coordinate
    template <typename T>
    constexpr Coord5<T>    operator-(const Coord5<T>& a)
    {
        return { -a.i, -a.j, -a.k, -a.l, -a.m };
    }


    //  --------------------------------------------------------
    //  NORMALIZATION


    //  --------------------------------------------------------
    //  ADDITION
    
    //! Add two coordinates together
    template <typename T>
    constexpr Coord5<T> operator+(const Coord5<T>&a, const Coord5<T>&b)
    {
        return { a.i+b.i, a.j+b.j, a.k+b.k, a.l+b.l, a.m+b.m };
    }
    
    //! Increment left coordinate with right
    template <typename T>
    Coord5<T>&  operator+=(Coord5<T>& a, const Coord5<T>& b)
    {
        a.i += b.i;
        a.j += b.j;
        a.k += b.k;
        a.l += b.l;
        a.m += b.m;
        return a;
    }


    //  --------------------------------------------------------
    //  SUBTRACTION

    
    //! Subtract two coordinates
    template <typename T>
    constexpr Coord5<T> operator-(const Coord5<T>&a, const Coord5<T>&b)
    {
        return { a.i-b.i, a.j-b.j, a.k-b.k, a.l-b.l, a.m-b.m };
    }
    
    //! Decrement the left coordinate with right
    template <typename T>
    Coord5<T>&  operator-=(Coord5<T>& a, const Coord5<T>& b)
    {
        a.i -= b.i;
        a.j -= b.j;
        a.k -= b.k;
        a.l -= b.l;
        a.m -= b.m;
        return a;
    }


    //  --------------------------------------------------------
    //  MULTIPLICATION

    //! Scale the coordinate
    template <typename T, typename U>
    requires (std::is_arithmetic_v<T>)
    constexpr Coord5<decltype(T()*U())> operator*(T a, const Coord5<U>&b)
    {
        return { a*b.i, a*b.j, a*b.k, a*b.l, a*b.m };
    }
    
    //! Scale the coordinate
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U>)
    constexpr Coord5<decltype(T()*U())> operator*(const Coord5<T>& a, U b)
    {
        return { a.i*b,  a.j*b, a.k*b, a.l*b, a.m*b };
    }

    //! Self-scale the coordinate
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && std::is_same_v<T, decltype(T()*U())>)
    Coord5<T>& operator*=(Coord5<T>& a, U b)
    {
        a.i *= b;
        a.j *= b;
        a.k *= b;
        a.l *= b;
        a.m *= b;
        return a;
    }

    //! Multiplies two coordinates together, term by term
    template <typename T, typename U>
    constexpr Coord5<decltype(T()*U())> operator*(const Coord5<T>& a, const Coord5<U>& b)
    {
        return { a.i*b.i, a.j*b.j, a.k*b.k, a.l*b.l, a.m*b.m };
    }

    //! Self-Multiplies left coordinate with right, term by term
    template <typename T, typename U>
    requires (std::is_same_v<T, decltype(T()*U())>)
    Coord5<T>& operator*=(Coord5<T>&a, const Coord5<U>& b)
    {
        a.i *= b.i;
        a.j *= b.j;
        a.k *= b.k;
        a.l *= b.l;
        a.m *= b.m;
        return a;
    }
    
    
    //  --------------------------------------------------------
    //  DIVISION

    //! Reduces the cooordinate, returns result
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U>)
    constexpr Coord5<decltype(T()/U())> operator/(const Coord5<T>& a, U b)
    {
        return { a.i/b, a.j/b, a.k/b, a.l/b, a.m/b };
    }

    //! Reduces the cooordinate in place, returns result
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && std::is_same_v<T, decltype(T()/U())>)
    Coord5<T>& operator/=(Coord5<T>& a, U b)
    {
        a.i /= b;
        a.j /= b;
        a.k /= b;
        a.l /= b;
        a.m /= b;
        return a;
    }

    //! Divides two coordinates, term by term
    template <typename T, typename U>
    constexpr Coord5<decltype(T()/U())> operator/(const Coord5<T>& a, const Coord5<U>& b)
    {
        return { a.i/b.i, a.j/b.j, a.k/b.k, a.l/b.l, a.m/b.m };
    }

    //! Self divides left coordinate by right
    template <typename T, typename U>
    requires (std::is_same_v<T, decltype(T()/U())>)
    Coord5<T>& operator/=(Coord5<T>& a, const Coord5<U>& b)
    {
        a.i /= b.i;
        a.j /= b.j;
        a.k /= b.k;
        a.l /= b.l;
        a.m /= b.m;
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
    S&  as_stream(S& s, const Coord5<I>& v)
    {
        return s << "[" << v.i << "," << v.j << "," << v.k << "," << v.l << "," << v.m << "]";
    }
    
    //! Helper to stream out a coordinate
    template <typename T>
    Stream& operator<<(Stream&s, const Coord5<T>& v)
    {
        return as_stream(s, v);
    }

    //! Helper to log out a coordinate
    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const Coord5<T>& v)
    {
        return as_stream(s, v);
    }
    
}
