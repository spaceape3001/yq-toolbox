////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/keywords.hpp>
#include <yq/coord/forward.hpp>
#include <yq/meta/InfoBinder.hpp>
#include <yq/trait/has_zero.hpp>
#include <yq/trait/is_arithmetic.hpp>
#include <yq/trait/product.hpp>
#include <yq/trait/quotient.hpp>
#include <yq/trait/self_divide.hpp>
#include <yq/trait/self_multiply.hpp>

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


        constexpr Coord operator+() const noexcept;
        constexpr Coord operator-() const noexcept;
        constexpr Coord operator+(const Coord& b) const noexcept;
        constexpr Coord operator-(const Coord& b) const noexcept;

        Coord& operator+=(const Coord&) noexcept;
        Coord& operator-=(const Coord&) noexcept;

        //! Scales the coordinate
        template <typename U>
            requires is_arithmetic_v<U>
        constexpr Coord3<product_t<T,U>> operator*(U b) const noexcept;
        
        //! Self-scale the coordinate
        template <typename U>
            requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
        Coord& operator*=(U b) noexcept;

        //! Multiplies two coordinates together, term by term
        template <typename U>
        constexpr Coord3<product_t<T,U>> operator*(const Coord3<U>& b) const noexcept;
        
        //! Self-Multiplies left coordinate with right, term by term
        template <typename U>
            requires self_multiply_v<T,U>
        Coord& operator*=(const Coord3<U>& b) noexcept;

        //! Reduces the cooordinate, returns result
        template <typename U>
            requires is_arithmetic_v<U>
        constexpr Coord3<quotient_t<T,U>> operator/(U b) const noexcept;

        //! Reduces the cooordinate in place, returns result
        template <typename U>
            requires (is_arithmetic_v<U> && self_divide_v<T,U>)
        Coord& operator/=(U b) noexcept;

        //! Divides two coordinates, term by term
        template <typename U>
        constexpr Coord3<quotient_t<T,U>> operator/(const Coord3<U>& b) const noexcept;

        //! Self divides left coordinate by right
        template <typename U>
            requires self_divide_v<T,U>
        Coord& operator/=(const Coord3<U>& b) noexcept;

        template <typename S>
        S&  stream(S&) const;
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
    constexpr Coord3<T> max(const Coord3<T>&a, const Coord3<T>& b);

    /*! \brief Min of two coordinates, done by element */
    template <typename T>
    constexpr Coord3<T> min(const Coord3<T>&a, const Coord3<T>& b);

    /*! \brief Product of the components */
    template <typename T>
    constexpr auto product(const Coord3<T>& a);

    /*! \brief Sum of the components */
    template <typename T>
    constexpr T sum(const Coord3<T>& a);

    //  --------------------------------------------------------

    //! Scale the coordinate
    template <typename T, typename U>
        requires is_arithmetic_v<T>
    constexpr Coord3<product_t<T,U>> operator*(T a, const Coord3<U>&b);
    
    //! Helper to stream out a coordinate
    template <typename T>
    Stream& operator<<(Stream&, const Coord3<T>&);

    //! Helper to log out a coordinate
    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const Coord3<T>&);
}

YQ_TYPE_DECLARE(yq::Coord3D);
YQ_TYPE_DECLARE(yq::Coord3F);
YQ_TYPE_DECLARE(yq::Coord3I);
YQ_TYPE_DECLARE(yq::Coord3U);
YQ_TYPE_DECLARE(yq::Coord3Z);
