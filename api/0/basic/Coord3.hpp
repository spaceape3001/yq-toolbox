////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Coord.hpp"
#include <0/trait/has_zero.hpp>
#include <0/keywords.hpp>

namespace yq {

    /*! \brief Three dimensional coordinate
    
        This is expanded in three diemnsions for the three-dimensional coordinate.
    */
    template <typename T>
    struct Coord<T,3> {
    
        //! Component type
        using component_type    = T;
        
        //! Number of dimensions
        static constexpr const uint8_t  DIMS    = 3;
        
        //! Coordinate in I
        T       i;

        //! Coordinate in J
        T       j;

        //! Coordinate in K
        T       k;

        //! Default constructor
        constexpr Coord() noexcept = default;
        
        //! Initializing constructor
        constexpr Coord(T _i, T _j, T _k) noexcept : 
            i(_i), j(_j), k(_k) {}
            
        //! Constructs all elements to same value
        constexpr Coord(all_t, T _v) noexcept : Coord<T,3>(_v, _v, _v) {}
        
        //! Zero constructor
        constexpr Coord(zero_t) noexcept : Coord<T,3>(ALL, zero_v<T>) {}

        //! Defaulted equality  operator
        constexpr bool operator==(const Coord&) const noexcept = default;

        //! Conversion operator to other 3-dimensional coordinates
        template <typename U>
        requires (!std::is_same_v<T,U>)
        explicit constexpr operator Coord<U,3>() const noexcept
        {
            return { (U) i, (U) j, (U) k };
        }

        //! Allows for uniform coordinate assignments.
        Coord& operator=(T v)
        {
            i = j = k = v;
            return *this;
        }
    };


    //  --------------------------------------------------------
    //  COMPOSITION

    /*! \brief Composes a three dimensional coordinate from arguments */
    template <typename T>
    constexpr Coord3<T>    coord(T i, std::type_identity_t<T> j, std::type_identity_t<T> k) noexcept
    {
        return { i, j, k};
    }
    
    /*! \brief Construct a uniform 3-dimensional coordinate */
    template <typename T>
    constexpr Coord3<T>    coord3(T i)
    {
        return { i, i, i };
    }


    //  --------------------------------------------------------
    //  BASIC FUNCTIONS

    /*! \brief Max of two coordinates, done by element */
    template <typename T>
    constexpr Coord3<T> max(const Coord3<T>&a, const Coord3<T>& b)
    {
        return { 
            max(a.i, b.i), 
            max(a.j, b.j), 
            max(a.k, b.k)
        };
    }

    /*! \brief Min of two coordinates, done by element */
    template <typename T>
    constexpr Coord3<T> min(const Coord3<T>&a, const Coord3<T>& b)
    {
        return { 
            min(a.i, b.i), 
            min(a.j, b.j), 
            min(a.k, b.k)
        };
    }

    /*! \brief Product of the components */
    template <typename T>
    constexpr auto product(const Coord3<T>& a)
    {
        return a.i*a.j*a.k;
    }

    /*! \brief Sum of the components */
    template <typename T>
    constexpr T sum(const Coord3<T>& a)
    {
        return a.i+a.j+a.k;
    }


    //  --------------------------------------------------------
    //  POSITIVE


    //  --------------------------------------------------------
    //  NEGATIVE

    //! Negate the coordinate
    template <typename T>
    constexpr Coord3<T>    operator-(const Coord3<T>& a)
    {
        return { -a.i, -a.j, -a.k };
    }


    //  --------------------------------------------------------
    //  NORMALIZATION


    //  --------------------------------------------------------
    //  ADDITION
    
    //! Add two coordinates together
    template <typename T>
    constexpr Coord3<T> operator+(const Coord3<T>&a, const Coord3<T>&b)
    {
        return { a.i+b.i, a.j+b.j, a.k+b.k };
    }
    
    //! Increment left coordinate with right
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

    //! Subtract two coordinates
    template <typename T>
    constexpr Coord3<T> operator-(const Coord3<T>&a, const Coord3<T>&b)
    {
        return { a.i-b.i, a.j-b.j, a.k-b.k };
    }
    
    //! Decrement the left coordinate with right
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

    //! Scale the coordinate
    template <typename T, typename U>
    requires (std::is_arithmetic_v<T>)
    constexpr Coord3<decltype(T()*U())> operator*(T a, const Coord3<U>&b)
    {
        return { a*b.i, a*b.j, a*b.k };
    }
    
    //! Scale the coordinate
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U>)
    constexpr Coord3<decltype(T()*U())> operator*(const Coord3<T>& a, U b)
    {
        return { a.i*b, a.j*b, a.k*b };
    }

    //! Self-scale the left coordinate with the right
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && std::is_same_v<T, decltype(T()*U())>)
    Coord3<T>& operator*=(Coord3<T>& a, U b)
    {
        a.i *= b;
        a.j *= b;
        a.k *= b;
        return a;
    }

    //! Multiplies two coordinates together, term by term
    template <typename T, typename U>
    constexpr Coord3<decltype(T()*U())> operator*(const Coord3<T>& a, const Coord3<U>& b)
    {
        return { a.i*b.i, a.j*b.j, a.k*b.k };
    }
    
    //! Self-Multiplies left coordinate with right, term by term
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

    //! Reduces the cooordinate, returns result
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U>)
    constexpr Coord3<decltype(T()/U())> operator/(const Coord3<T>& a, U b)
    {
        return { a.i/b, a.j/b, a.k/b };
    }

    //! Reduces the cooordinate in place, returns result
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && std::is_same_v<T, decltype(T()/U())>)
    Coord3<T>& operator/=(Coord3<T>& a, U b)
    {
        a.i /= b;
        a.j /= b;
        a.k /= b;
        return a;
    }

    //! Divides two coordinates, term by term
    template <typename T, typename U>
    constexpr Coord3<decltype(T()/U())> operator/(const Coord3<T>& a, const Coord3<U>& b)
    {
        return { a.i/b.i, a.j/b.j, a.k/b.k };
    }

    //! Self divides left coordinate by right
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

    //! Helper to stream out a coordinate
    template <typename S, typename I>
    S&  as_stream(S& s, const Coord3<I>& v)
    {
        return s << "[" << v.i << "," << v.j << "," << v.k << "]";
    }
    
    //! Helper to stream out a coordinate
    template <typename T>
    Stream& operator<<(Stream&s, const Coord3<T>& v)
    {
        return as_stream(s, v);
    }

    //! Helper to log out a coordinate
    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const Coord3<T>& v)
    {
        return as_stream(s, v);
    }
    
}
