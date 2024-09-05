////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq-toolbox/typedef/coord2.hpp>

#include <yq-toolbox/keywords.hpp>
#include <yq-toolbox/meta/InfoBinder.hpp>
#include <yq-toolbox/trait/has_is_finite.hpp>
#include <yq-toolbox/trait/has_nan.hpp>
#include <yq-toolbox/trait/has_zero.hpp>
#include <yq-toolbox/trait/is_arithmetic.hpp>
#include <yq-toolbox/trait/product.hpp>
#include <yq-toolbox/trait/quotient.hpp>
#include <yq-toolbox/trait/self_divide.hpp>
#include <yq-toolbox/trait/self_multiply.hpp>

namespace log4cpp { class CategoryStream; }

namespace yq {
    class Stream;

    /*! \brief Two dimensional coordinate
    
        This is expanded in two diemnsions for the two-dimensional coordinate.
    */
    template <typename T>
    struct Coord<T,2> {
    
        //! Component type
        using component_type    = T;
        
        //! Number of dimensions;
        static constexpr const uint8_t  DIMS    = 2;
        
        //! Coordinate in I
        T       i;
        
        //! Coordinate in J
        T       j;

        //! Default constructor
        constexpr Coord() noexcept = default;
        
        //! Initializing constructor (by components)
        constexpr Coord(T _i, T _j) noexcept : 
            i(_i), j(_j) {}
            
        //! Constructs all elements from single value
        constexpr Coord(all_t, T _v) noexcept : Coord<T,2>(_v, _v) {}
        
        //! Constructs as a zero value for all components
        constexpr Coord(zero_t) noexcept : Coord<T,2>(ALL, zero_v<T>) {}

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

        constexpr Coord operator+() const noexcept;
        constexpr Coord operator-() const noexcept;
        constexpr Coord operator+(const Coord& b) const noexcept;
        constexpr Coord operator-(const Coord& b) const noexcept;

        Coord& operator+=(const Coord&) noexcept;
        Coord& operator-=(const Coord&) noexcept;

        //! Scales the coordinate
        template <typename U>
            requires is_arithmetic_v<U>
        constexpr Coord2<product_t<T,U>> operator*(U b) const noexcept;
        
        //! Self-scale the coordinate
        template <typename U>
            requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
        Coord& operator*=(U b) noexcept;

        //! Multiplies two coordinates together, term by term
        template <typename U>
        constexpr Coord2<product_t<T,U>> operator*(const Coord2<U>& b) const noexcept;
        
        //! Self-Multiplies left coordinate with right, term by term
        template <typename U>
            requires self_multiply_v<T,U>
        Coord& operator*=(const Coord2<U>& b) noexcept;

        //! Reduces the cooordinate, returns result
        template <typename U>
            requires is_arithmetic_v<U>
        constexpr Coord2<quotient_t<T,U>> operator/(U b) const noexcept;

        //! Reduces the cooordinate in place, returns result
        template <typename U>
            requires (is_arithmetic_v<U> && self_divide_v<T,U>)
        Coord& operator/=(U b) noexcept;

        //! Divides two coordinates, term by term
        template <typename U>
        constexpr Coord2<quotient_t<T,U>> operator/(const Coord2<U>& b) const noexcept;

        //! Self divides left coordinate by right
        template <typename U>
            requires self_divide_v<T,U>
        Coord& operator/=(const Coord2<U>& b) noexcept;

        template <typename S>
        S&  stream(S&) const;
    };

    YQ_NAN_1(Coord2, Coord2<T>( nan_v<T>, nan_v<T> ))
    YQ_IS_NAN_1(Coord2, is_nan(v.i) || is_nan(v.j) )
    YQ_IS_FINITE_1(Coord2, is_finite(v.i) && is_finite(v.j) )
    YQ_ZERO_1(Coord2, Coord2<T>( zero_v<T>, zero_v<T> ))

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
    constexpr Coord2<T> max(const Coord2<T>&a, const Coord2<T>& b);

    /*! \brief Min of two coordinates, done by element */
    template <typename T>
    constexpr Coord2<T> min(const Coord2<T>&a, const Coord2<T>& b);

    /*! \brief Product of the components */
    template <typename T>
    constexpr auto product(const Coord2<T>& a);

    /*! \brief Sum of the components */
    template <typename T>
    constexpr T sum(const Coord2<T>& a);


    //  --------------------------------------------------------

    //! Scale the coordinate
    template <typename T, typename U>
        requires is_arithmetic_v<T>
    constexpr Coord2<product_t<T,U>> operator*(T a, const Coord2<U>&b);
    
    //! Helper to stream out a coordinate
    template <typename T>
    Stream& operator<<(Stream&, const Coord2<T>&);

    //! Helper to log out a coordinate
    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const Coord2<T>&);
}

YQ_TYPE_DECLARE(yq::Coord2D);
YQ_TYPE_DECLARE(yq::Coord2F);
YQ_TYPE_DECLARE(yq::Coord2I);
YQ_TYPE_DECLARE(yq::Coord2U);
YQ_TYPE_DECLARE(yq::Coord2Z);

