////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Coord.hpp"
#include <trait/has_zero.hpp>
#include <keywords.hpp>

namespace yq {

    /*! \brief One dimensional coordinate
    
        This is expanded in one diemnsion for the one-dimensional coordinate.
    */
    template <typename T>
    struct Coord<T,1> {
    
        //! Component type
        using component_type    = T;
        
        //! Number of dimensions
        static constexpr const uint8_t  DIMS    = 1;
        
        //! Data (I-value)
        T       i;

        //! Default constructor
        constexpr Coord<T,1>() noexcept = default;
        
        //! Initializing constructor
        constexpr Coord<T,1>(T _i) noexcept : 
            i(_i)  {}
            
        //! All components to given value
        constexpr Coord<T,1>(all_t, T _v) noexcept : Coord<T,1>(_v) {}
        
        //! Zero initializes
        constexpr Coord<T,1>(zero_t) noexcept : Coord<T,1>(ALL, zero_v<T>) {}

        //! Defaulted spaceship  operator
        constexpr auto operator<=>(const Coord&) const noexcept = default;

        //! Conversion operator to other 1-dimensional coordinates
        template <typename U>
        requires (!std::is_same_v<T,U>)
        explicit constexpr operator Coord<U,1>() const noexcept
        {
            return { (U) i };
        }

        //! Allows for uniform coordinate assignment.
        Coord& operator=(T v)
        {
            i = v;
            return *this;
        }
    };


    //  --------------------------------------------------------
    //  COMPOSITION

    /*! \brief Composes a one dimensional coordinate from arguments */
    template <typename T>
    constexpr Coord1<T>    coord(T i) noexcept
    {
        return { i };
    }
    
    /*! \brief Construct a uniform 1-dimensional coordinate */
    template <typename T>
    constexpr Coord1<T>    coord1(T i)
    {
        return { i };
    }


    //  --------------------------------------------------------
    //  BASIC FUNCTIONS

    /*! \brief Max of two coordinates, done by element */
    template <typename T>
    constexpr Coord1<T> max(const Coord1<T>&a, const Coord1<T>& b)
    {
        return { 
            max(a.i, b.i)
        };
    }

    /*! \brief Min of two coordinates, done by element */
    template <typename T>
    constexpr Coord1<T> min(const Coord1<T>&a, const Coord1<T>& b)
    {
        return { 
            min(a.i, b.i)
        };
    }

    /*! \brief Product of the components */
    template <typename T>
    constexpr T product(const Coord1<T>& a)
    {
        return a.i;
    }

    /*! \brief Sum of the components */
    template <typename T>
    constexpr T sum(const Coord1<T>& a)
    {
        return a.i;
    }

    //  --------------------------------------------------------
    //  POSITIVE


    //  --------------------------------------------------------
    //  NEGATIVE

    //! Negate the coordinate
    template <typename T>
    constexpr Coord1<T>    operator-(const Coord1<T>& a)
    {
        return { -a.i };
    }


    //  --------------------------------------------------------
    //  NORMALIZATION


    //  --------------------------------------------------------
    //  ADDITION
    
    //! Add two coordinates together
    template <typename T>
    constexpr Coord1<T> operator+(const Coord1<T>&a, const Coord1<T>&b)
    {
        return { a.i+b.i };
    }
    
    //! Increment left coordinate with right
    template <typename T>
    Coord1<T>&  operator+=(Coord1<T>& a, const Coord1<T>& b)
    {
        a.i += b.i;
        return a;
    }


    //  --------------------------------------------------------
    //  SUBTRACTION

    
    //! Subtract two coordinates
    template <typename T>
    constexpr Coord1<T> operator-(const Coord1<T>&a, const Coord1<T>&b)
    {
        return { a.i-b.i };
    }
    
    //! Decrement the left coordinate with right
    template <typename T>
    Coord1<T>&  operator-=(Coord1<T>& a, const Coord1<T>& b)
    {
        a.i -= b.i;
        return a;
    }


    //  --------------------------------------------------------
    //  MULTIPLICATION

    //! Scale the coordinate
    template <typename T, typename U>
    requires (std::is_arithmetic_v<T>)
    constexpr Coord1<decltype(T()*U())> operator*(T a, const Coord1<U>&b)
    {
        return { a*b.i };
    }
    
    //! Scale the coordinate
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U>)
    constexpr Coord1<decltype(T()*U())> operator*(const Coord1<T>& a, U b)
    {
        return { a.i*b };
    }

    //! Self-scale the left coordinate with the right
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && std::is_same_v<T, decltype(T()*U())>)
    Coord1<T>& operator*=(Coord1<T>& a, U b)
    {
        a.i *= b;
        return a;
    }

    //! Multiplies two coordinates together, term by term
    template <typename T, typename U>
    constexpr Coord1<decltype(T()*U())> operator*(const Coord1<T>& a, const Coord1<U>& b)
    {
        return { a.i*b.i };
    }
    
    //! Self-Multiplies left coordinate with right, term by term
    template <typename T, typename U>
    requires (std::is_same_v<T, decltype(T()*U())>)
    Coord1<T>& operator*=(Coord1<T>&a, const Coord1<U>& b)
    {
        a.i *= b.i;
        return a;
    }
    
    
    //  --------------------------------------------------------
    //  DIVISION

    //! Reduces the cooordinate, returns result
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U>)
    constexpr Coord1<decltype(T()/U())> operator/(const Coord1<T>& a, U b)
    {
        return { a.i/b };
    }

    //! Reduces the cooordinate in place, returns result
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && std::is_same_v<T, decltype(T()/U())>)
    Coord1<T>& operator/=(Coord1<T>& a, U b)
    {
        a.i /= b;
        return a;
    }

    //! Divides two coordinates, term by term
    template <typename T, typename U>
    constexpr Coord1<decltype(T()/U())> operator/(const Coord1<T>& a, const Coord1<U>& b)
    {
        return { a.i/b.i };
    }

    //! Self divides left coordinate by right
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

    //! Helper to stream out a coordinate
    template <typename S, typename I>
    S&  as_stream(S& s, const Coord1<I>& v)
    {
        return s << "[" << v.i << "]";
    }
    
    //! Helper to stream out a coordinate
    template <typename T>
    Stream& operator<<(Stream&s, const Coord1<T>& v)
    {
        return as_stream(s, v);
    }

    //! Helper to log out a coordinate
    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const Coord1<T>& v)
    {
        return as_stream(s, v);
    }
    
}
