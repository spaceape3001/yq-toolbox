////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>

namespace yq {

    /*! \brief 3D Tri-vector */
    template <typename T>
    struct Trivector3 {
        //! Our argument type
        using component_type = T;
        cube_t<T>     xyz;
        
        //! Defaulted comparison operator
        constexpr auto operator<=>(const Trivector3&) const noexcept = default;
    };

    YQ_IEEE754_1(Trivector3)

//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Literal to construct a trivector
    */
    constexpr Trivector3D   operator "" _xyz3(unsigned long long int v) noexcept
    {
        return {(double) v};
    }

    /*! \brief Literal to construct a trivector
    */
    constexpr Trivector3D   operator "" _xyz3(long double v) noexcept
    {
        return {(double) v};
    }

    YQ_NAN_1(Trivector3, Trivector3<T>{nan_v<cube_t<T>>})
    YQ_ZERO_1(Trivector3, Trivector3<T>{zero_v<cube_t<T>>})
    
//  --------------------------------------------------------
//  GETTERS

//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_NAN_1(Trivector3, is_nan(v.xyz))
    YQ_IS_FINITE_1(Trivector3, is_finite(v.xyz))

//  --------------------------------------------------------
//  POSITIVE

    /*! \brief Affirmation (positive) operator
    */
    template <typename T>
    constexpr Trivector3<T> operator+(const Trivector3<T>&a) noexcept
    {
        return a;
    }


//  --------------------------------------------------------
//  NEGATIVE

    /*! \brief Negation operator
    */
    template <typename T>
    constexpr Trivector3<T> operator-(const Trivector3<T>&a) noexcept
    {
        return {-a.xyz};
    }


//  --------------------------------------------------------
//  NORMALIZATION


//  --------------------------------------------------------
//  ADDITION

    /*! \brief Addition of two trivectors
    */
    template <typename T>
    constexpr Trivector4<T> operator+(const Trivector3<T>& a, const Trivector3<T>& b) noexcept
    {
        return { a.xyz+b.xyz };
    }

    /*! \brief Self-addition operator
    
        Adds the right to the left term.
    */
    template <typename T>
    Trivector4<T>& operator+=(Trivector3<T>& a, const Trivector3<T>& b) noexcept
    {
        a.xyz+=b.xyz;
        return a;
    }

//  --------------------------------------------------------
//  SUBTRACTION

    /*! \brief Subtraction of two trivectors
    */
    template <typename T>
    constexpr Trivector3<T> operator-(const Trivector3<T>& a, const Trivector3<T>& b) noexcept
    {
        return { a.xyz-b.xyz };
    }

    /*! \brief Self-subtraction operator
        
        Subtracts the right from the left term.
    */
    template <typename T>
    Trivector3<T>& operator-=(Trivector3<T>& a, const Trivector3<T>& b) noexcept
    {
        a.xyz-=b.xyz;
        return a;
    }


//  --------------------------------------------------------
//  MULTIPLICATION

    /*! \brief Scaling multiplication of trivector
    
        This will (scale) multiply a trivector, returns the result.
    */
    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Trivector3<T> operator*(T a, const Trivector3<T>& b) noexcept
    {
        return { a*b.xyz };
    }

    /*! \brief Scaling multiplication of trivector
    
        This will (scale) multiply a trivector, returns the result.
    */
    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Trivector3<T> operator*(const Trivector3<T>& a, T b) noexcept
    {
        return { a.xyz*b };
    }

    /*! \brief Scaling self-multiplication of trivector
        
        This multiplies the trivector (in place) with the right term, returns a reference.
    */
    template <typename T>
    requires std::is_floating_point_v<T>
    Trivector3<T>& operator*=(Trivector3<T>& a, T b) noexcept
    {
        a.xyz *= b;
        return a;
    }

//  --------------------------------------------------------
//  DIVISION

    /*! \brief Scaling division of trivector
        
        This scale divides the trivector with the right.
    */
    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Trivector3<T> operator/(const Trivector3<T>& a, T b) noexcept
    {
        return { a.xyz/b };
    }

    /*! \brief Self-scaling division of trivector
    
        This reduces the trivector (in place) with the right,
        returns reference to the trivector.
    */
    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Trivector3<T>& operator/=(Trivector3<T>& a, T b) noexcept
    {
        a.xyz /= b;
        return a;
    }

//  --------------------------------------------------------
//  POWERS

//  --------------------------------------------------------
//  DOT PRODUCT


//  --------------------------------------------------------
//  INNER PRODUCT


//  --------------------------------------------------------
//  OUTER PRODUCT


//  --------------------------------------------------------
//  CROSS PRODUCT


///  --------------------------------------------------------
//  OTIMES PRODUCT

//  --------------------------------------------------------
//  UNIONS

//  --------------------------------------------------------
//  INTERSECTIONS


//  --------------------------------------------------------
//  PROJECTIONS

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

}

YQ_TYPE_DECLARE(yq::Trivector3D)
YQ_TYPE_DECLARE(yq::Trivector3F)

