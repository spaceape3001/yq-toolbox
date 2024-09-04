////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/typedef/coord4.hpp>

#include <yq/keywords.hpp>
#include <yq/meta/InfoBinder.hpp>
#include <yq/trait/has_is_finite.hpp>
#include <yq/trait/has_nan.hpp>
#include <yq/trait/has_zero.hpp>
#include <yq/trait/is_arithmetic.hpp>
#include <yq/trait/product.hpp>
#include <yq/trait/quotient.hpp>
#include <yq/trait/self_divide.hpp>
#include <yq/trait/self_multiply.hpp>

namespace log4cpp { class CategoryStream; }

namespace yq {
    class Stream;

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
        constexpr Coord() noexcept = default;
        
        //! Component-wise initializing constructor
        constexpr Coord(T _i, T _j, T _k, T _l) noexcept : 
            i(_i), j(_j), k(_k), l(_l) {}
            
        //! Constructs ALL components to same value
        constexpr Coord(all_t, T _v) noexcept : Coord<T,4>(_v, _v, _v, _v) {}
        
        //! Constructs a ZERO coordinate
        constexpr Coord(zero_t) noexcept : Coord<T,4>(ALL, zero_v<T>) {}

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

        constexpr Coord operator+() const noexcept;
        constexpr Coord operator-() const noexcept;
        constexpr Coord operator+(const Coord& b) const noexcept;
        constexpr Coord operator-(const Coord& b) const noexcept;

        Coord& operator+=(const Coord&) noexcept;
        Coord& operator-=(const Coord&) noexcept;

        //! Scales the coordinate
        template <typename U>
            requires is_arithmetic_v<U>
        constexpr Coord4<product_t<T,U>> operator*(U b) const noexcept;
        
        //! Self-scale the coordinate
        template <typename U>
            requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
        Coord& operator*=(U b) noexcept;

        //! Multiplies two coordinates together, term by term
        template <typename U>
        constexpr Coord4<product_t<T,U>> operator*(const Coord4<U>& b) const noexcept;
        
        //! Self-Multiplies left coordinate with right, term by term
        template <typename U>
            requires self_multiply_v<T,U>
        Coord& operator*=(const Coord4<U>& b) noexcept;

        //! Reduces the cooordinate, returns result
        template <typename U>
            requires is_arithmetic_v<U>
        constexpr Coord4<quotient_t<T,U>> operator/(U b) const noexcept;

        //! Reduces the cooordinate in place, returns result
        template <typename U>
            requires (is_arithmetic_v<U> && self_divide_v<T,U>)
        Coord& operator/=(U b) noexcept;

        //! Divides two coordinates, term by term
        template <typename U>
        constexpr Coord4<quotient_t<T,U>> operator/(const Coord4<U>& b) const noexcept;

        //! Self divides left coordinate by right
        template <typename U>
            requires self_divide_v<T,U>
        Coord& operator/=(const Coord4<U>& b) noexcept;

        template <typename S>
        S&  stream(S&) const;
    };

    YQ_NAN_1(Coord4, Coord4<T>(ALL, nan_v<T>))
    YQ_IS_NAN_1(Coord4, is_nan(v.i) || is_nan(v.j) || is_nan(v.k) || is_nan(v.l))
    YQ_IS_FINITE_1(Coord4, is_finite(v.i) && is_finite(v.j) && is_finite(v.k) && is_finite(v.l))
    YQ_ZERO_1(Coord4, Coord4<T>( ZERO ))

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
    constexpr Coord4<T> max(const Coord4<T>&a, const Coord4<T>& b);

    /*! \brief Min of two coordinates, done by element */
    template <typename T>
    constexpr Coord4<T> min(const Coord4<T>&a, const Coord4<T>& b);

    /*! \brief Product of the components */
    template <typename T>
    constexpr auto product(const Coord4<T>& a);

    /*! \brief Sum of the components */
    template <typename T>
    constexpr T sum(const Coord4<T>& a);



    //  --------------------------------------------------------

    //! Scale the coordinate
    template <typename T, typename U>
        requires is_arithmetic_v<T>
    constexpr Coord4<product_t<T,U>> operator*(T a, const Coord4<U>&b);

    
    //! Helper to stream out a coordinate
    template <typename T>
    Stream& operator<<(Stream&, const Coord4<T>&);

    //! Helper to log out a coordinate
    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const Coord4<T>&);
}

YQ_TYPE_DECLARE(yq::Coord4D);
YQ_TYPE_DECLARE(yq::Coord4F);
YQ_TYPE_DECLARE(yq::Coord4I);
YQ_TYPE_DECLARE(yq::Coord4U);
YQ_TYPE_DECLARE(yq::Coord4Z);

