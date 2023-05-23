////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Coord.hpp"
#include <trait/has_zero.hpp>

namespace yq {

    /*! \brief Six dimensional coordinate
    
        This is expanded in six diemnsions for the six-dimensional coordinate.
    */
    template <typename T>
    struct Coord<T,6> {
        using component_type    = T;
        static constexpr const uint8_t  DIMS    = 6;
        T       i, j, k, l, m, n;
        
        constexpr Coord<T,6>() noexcept = default;
        constexpr Coord<T,6>(T _i, T _j, T _k, T _l, T _m, T _n) noexcept : 
            i(_i), j(_j), k(_k), l(_l), m(_m), n(_n) {}
        constexpr Coord<T,6>(all_t, T _v) noexcept : Coord<T,6>(_v, _v, _v, _v, _v, _v) {}
        constexpr Coord<T,6>(zero_t) noexcept : Coord<T,6>(ALL, zero_v<T>) {}
        
        //! Defaulted equality  operator
        constexpr bool operator==(const Coord&) const noexcept = default;
        
        //! Conversion operator to other 6-dimensional coordinates
        template <typename U>
        requires (!std::is_same_v<T,U>)
        explicit constexpr operator Coord<U,6>() const noexcept
        {
            return { (U) i, (U) j, (U) k, (U) l, (U) m, (U) n };
        }
        
        //! Allows for uniform coordinate assignments.
        Coord& operator=(T v)
        {
            i = j = k = l = m = n = v;
            return *this;
        }
    };


    //  --------------------------------------------------------
    //  COMPOSITION

    /*! \brief Composes a six dimensional coordinate from arguments */
    template <typename T>
    constexpr Coord6<T>    coord(T i, std::type_identity_t<T> j, std::type_identity_t<T> k, std::type_identity_t<T> l, std::type_identity_t<T> m, std::type_identity_t<T> n) noexcept
    {
        return { i, j, k, l, m, n };
    }
    
    /*! \brief Construct a uniform 6-dimensional coordinate */
    template <typename T>
    constexpr Coord6<T>    coord6(T i)
    {
        return { i, i, i, i, i, i };
    }


    //  --------------------------------------------------------
    //  BASIC FUNCTIONS

    /*! \brief Max of two coordinates, done by element */
    template <typename T>
    constexpr Coord6<T> max(const Coord6<T>&a, const Coord6<T>& b)
    {
        return { 
            max(a.i, b.i), 
            max(a.j, b.j), 
            max(a.k, b.k), 
            max(a.l, b.l), 
            max(a.m, b.m), 
            max(a.n, b.n)
        };
    }

    /*! \brief Min of two coordinates, done by element */
    template <typename T>
    constexpr Coord6<T> min(const Coord6<T>&a, const Coord6<T>& b)
    {
        return { 
            min(a.i, b.i), 
            min(a.j, b.j), 
            min(a.k, b.k), 
            min(a.l, b.l), 
            min(a.m, b.m), 
            min(a.n, b.n)
        };
    }

    /*! \brief Product of the components */
    template <typename T>
    constexpr auto product(const Coord6<T>& a)
    {
        return a.i*a.j*a.k*a.l*a.m*a.n;
    }

    /*! \brief Sum of the components */
    template <typename T>
    constexpr T sum(const Coord6<T>& a)
    {
        return a.i+a.j+a.k+a.l+a.m+a.n;
    }
    
    //  --------------------------------------------------------
    //  POSITIVE


    //  --------------------------------------------------------
    //  NEGATIVE

    //! Negate the coordinate
    template <typename T>
    constexpr Coord6<T>    operator-(const Coord6<T>& a)
    {
        return { -a.i, -a.j, -a.k, -a.l, -a.m, -a.n };
    }


    //  --------------------------------------------------------
    //  NORMALIZATION


    //  --------------------------------------------------------
    //  ADDITION
    
    //! Add two coordinates together
    template <typename T>
    constexpr Coord6<T> operator+(const Coord6<T>&a, const Coord6<T>&b)
    {
        return { a.i+b.i, a.j+b.j, a.k+b.k, a.l+b.l, a.m+b.m, a.n+b.n };
    }
    
    //! Increment left coordinate with right
    template <typename T>
    Coord6<T>&  operator+=(Coord6<T>& a, const Coord6<T>& b)
    {
        a.i += b.i;
        a.j += b.j;
        a.k += b.k;
        a.l += b.l;
        a.m += b.m;
        a.n += b.n;
        return a;
    }


    //  --------------------------------------------------------
    //  SUBTRACTION

    //! Subtract two coordinates
    template <typename T>
    constexpr Coord6<T> operator-(const Coord6<T>&a, const Coord6<T>&b)
    {
        return { a.i-b.i, a.j-b.j, a.k-b.k, a.l-b.l, a.m-b.m, a.n-b.n };
    }
    
    //! Decrement the left coordinate with right
    template <typename T>
    Coord6<T>&  operator-=(Coord6<T>& a, const Coord6<T>& b)
    {
        a.i -= b.i;
        a.j -= b.j;
        a.k -= b.k;
        a.l -= b.l;
        a.m -= b.m;
        a.n -= b.n;
        return a;
    }


    //  --------------------------------------------------------
    //  MULTIPLICATION

    //! Scale the coordinate
    template <typename T, typename U>
    requires (std::is_arithmetic_v<T>)
    constexpr Coord6<decltype(T()*U())> operator*(T a, const Coord6<U>&b)
    {
        return { a*b.i, a*b.j, a*b.k, a*b.l, a*b.m, a*b.n };
    }
    
    //! Scale the coordinate
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U>)
    constexpr Coord6<decltype(T()*U())> operator*(const Coord6<T>& a, U b)
    {
        return { a.i*b,  a.j*b, a.k*b, a.l*b, a.m*b, a.n*b };
    }

    //! Self-scale the coordinate
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && std::is_same_v<T, decltype(T()*U())>)
    Coord6<T>& operator*=(Coord6<T>& a, U b)
    {
        a.i *= b;
        a.j *= b;
        a.k *= b;
        a.l *= b;
        a.m *= b;
        a.n *= b;
        return a;
    }

    //! Multiplies two coordinates together, term by term
    template <typename T, typename U>
    constexpr Coord6<decltype(T()*U())> operator*(const Coord6<T>& a, const Coord6<U>& b)
    {
        return { a.i*b.i, a.j*b.j, a.k*b.k, a.l*b.l, a.m*b.m, a.n*b.n };
    }
    
    //! Self-Multiplies left coordinate with right, term by term
    template <typename T, typename U>
    requires (std::is_same_v<T, decltype(T()*U())>)
    Coord6<T>& operator*=(Coord6<T>&a, const Coord6<U>& b)
    {
        a.i *= b.i;
        a.j *= b.j;
        a.k *= b.k;
        a.l *= b.l;
        a.m *= b.m;
        a.n *= b.n;
        return a;
    }
    
    
    //  --------------------------------------------------------
    //  DIVISION

    //! Reduces the cooordinate, returns result
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U>)
    constexpr Coord6<decltype(T()/U())> operator/(const Coord6<T>& a, U b)
    {
        return { a.i/b,  a.j/b, a.k/b, a.l/b, a.m/b, a.n/b };
    }

    //! Reduces the cooordinate in place, returns result
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && std::is_same_v<T, decltype(T()/U())>)
    Coord6<T>& operator/=(Coord6<T>& a, U b)
    {
        a.i /= b;
        a.j /= b;
        a.k /= b;
        a.l /= b;
        a.m /= b;
        a.n /= b;
        return a;
    }

    //! Divides two coordinates, term by term
    template <typename T, typename U>
    constexpr Coord6<decltype(T()/U())> operator/(const Coord6<T>& a, const Coord6<U>& b)
    {
        return { a.i/b.i, a.j/b.j, a.k/b.k, a.l/b.l, a.m/b.m, a.n/b.n };
    }

    //! Self divides left coordinate by right
    template <typename T, typename U>
    requires (std::is_same_v<T, decltype(T()/U())>)
    Coord6<T>& operator/=(Coord6<T>& a, const Coord6<U>& b)
    {
        a.i /= b.i;
        a.j /= b.j;
        a.k /= b.k;
        a.l /= b.l;
        a.m /= b.m;
        a.n /= b.n;
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
    S&  as_stream(S& s, const Coord6<I>& v)
    {
        return s << "[" << v.i << "," << v.j << "," << v.k << "," << v.l << "," << v.m << "," << v.n << "]";
    }
    
    //! Helper to stream out a coordinate
    template <typename T>
    Stream& operator<<(Stream&s, const Coord6<T>& v)
    {
        return as_stream(s, v);
    }

    //! Helper to log out a coordinate
    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const Coord6<T>& v)
    {
        return as_stream(s, v);
    }
    
}
