////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>

namespace yq {
    /*! \brief 4D Tri-vector */
    template <typename T>
    struct Trivector4 {

        //! Component type
        using component_type = T;
        T     xyz, yzw, zwx, wxy;

        //! Defaulted comparison operator
        constexpr bool operator==(const Trivector4&) const noexcept = default;

        /*! \brief Affirmation (positive) operator
        
            \note Here to complement the negation operator
        */
        constexpr Trivector4 operator+() const noexcept
        {
            return *this;
        }

        /*! \brief Negation operator
        */
        constexpr Trivector4 operator-() const noexcept
        {
            return {-xyz, -yzw, -zwx, -wxy};
        }
    };

    YQ_IEEE754_1(Trivector4)


//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Literal to construct a trivector
    */
    constexpr Trivector4D   operator "" _xyz4(unsigned long long int v) noexcept
    {
        return {(double) v, 0., 0., 0.};
    }

    /*! \brief Literal to construct a trivector
    */
    constexpr Trivector4D   operator "" _xyz4(long double v) noexcept
    {
        return {(double) v, 0., 0., 0.};
    }

    /*! \brief Literal to construct a trivector
    */
    constexpr Trivector4D   operator "" _yzw4(unsigned long long int v) noexcept
    {
        return {0., (double) v, 0., 0.};
    }

    /*! \brief Literal to construct a trivector
    */
    constexpr Trivector4D   operator "" _yzw4(long double v) noexcept
    {
        return {0., (double) v, 0., 0.};
    }

    /*! \brief Literal to construct a trivector
    */
    constexpr Trivector4D   operator "" _zwx4(unsigned long long int v) noexcept
    {
        return {0., 0.,  (double) v, 0.};
    }

    /*! \brief Literal to construct a trivector
    */
    constexpr Trivector4D   operator "" _zwx4(long double v) noexcept
    {
        return {0., 0., (double) v,  0.};
    }

    /*! \brief Literal to construct a trivector
    */
    constexpr Trivector4D   operator "" _wxy4(unsigned long long int v) noexcept
    {
        return {0., 0.,  0., (double) v };
    }

    /*! \brief Literal to construct a trivector
    */
    constexpr Trivector4D   operator "" _wxy4(long double v) noexcept
    {
        return {0., 0., 0., (double) v};
    }

    YQ_NAN_1(Trivector4, Trivector4<T>{nan_v<cube_t<T>>, nan_v<cube_t<T>>, nan_v<cube_t<T>>, nan_v<cube_t<T>>})
    YQ_ZERO_1(Trivector4, Trivector4<T>{zero_v<cube_t<T>>, nan_v<cube_t<T>>, nan_v<cube_t<T>>, nan_v<cube_t<T>>})
    

//  --------------------------------------------------------
//  GETTERS


//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_NAN_1(Trivector4, is_nan(v.xyz) || is_nan(v.yzw) || is_nan(v.zwx) || is_nan(v.wxy))
    YQ_IS_FINITE_1(Trivector4, is_finite(v.xyz) && is_finite(v.yzw) && is_finite(v.zwx) && is_finite(v.wxy))



//  --------------------------------------------------------
//  NORMALIZATION


//  --------------------------------------------------------
//  ADDITION

    /*! \brief Addition of two trivectors
    */
    template <typename T>
    constexpr Trivector4<T> operator+(const Trivector4<T>& a, const Trivector4<T>& b) noexcept
    {
        return { a.xyz+b.xyz, a.yzw+b.yzw, a.zwx+b.zwx, a.wxy+b.wxy };
    }

    /*! \brief Self-addition operator
    
        Adds the right to the left term.
    */
    template <typename T>
    Trivector4<T>& operator+(Trivector4<T>& a, const Trivector4<T>& b) noexcept
    {
        a.xyz+=b.xyz; a.yzw+=b.yzw; a.zwx+=b.zwx; a.wxy+=b.wxy;
        return a;
    }

//  --------------------------------------------------------
//  SUBTRACTION

    /*! \brief Subtraction of two trivectors
    */
    template <typename T>
    constexpr Trivector4<T> operator-(const Trivector4<T>& a, const Trivector4<T>& b) noexcept
    {
        return { a.xyz-b.xyz, a.yzw-b.yzw, a.zwx-b.zwx, a.wxy-b.wxy };
    }

    /*! \brief Self-subtraction operator
        
        Subtracts the right from the left term.
    */
    template <typename T>
    Trivector4<T>& operator-(Trivector4<T>& a, const Trivector4<T>& b) noexcept
    {
        a.xyz-=b.xyz; a.yzw-=b.yzw; a.zwx-=b.zwx; a.wxy-=b.wxy;
        return a;
    }

//  --------------------------------------------------------
//  MULTIPLICATION

    /*! \brief Scaling multiplication of trivector
    
        This will (scale) multiply a trivector, returns the result.
    */
    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Trivector4<T> operator*(T a, const Trivector4<T>& b) noexcept
    {
        return { a*b.xyz, a*b.yzw, a*b.zwx, a*b.wxy, };
    }

    /*! \brief Scaling multiplication of trivector
    
        This will (scale) multiply a trivector, returns the result.
    */
    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Trivector4<T> operator*(const Trivector4<T>& a, T b) noexcept
    {
        return { a.xyz*b, a.yzw*b, a.zwx*b, a.wxy*b, };
    }

    /*! \brief Scaling self-multiplication of trivector
        
        This multiplies the trivector (in place) with the right term, returns a reference.
    */
    template <typename T>
    requires std::is_floating_point_v<T>
    Trivector4<T>& operator*=(Trivector4<T>& a, T b) noexcept
    {
        a.xyz*=b; a.yzw*=b; a.zwx*=b; a.wxy*=b;
        return a;
    }

//  --------------------------------------------------------
//  DIVISION

    /*! \brief Scaling division of trivector
        
        This scale divides the trivector with the right.
    */
    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Trivector4<T> operator/(const Trivector4<T>& a, T b) noexcept
    {
        return { a.xyz/b, a.yzw/b, a.zwx/b, a.wxy/b, };
    }

    /*! \brief Self-scaling division of trivector
    
        This reduces the trivector (in place) with the right,
        returns reference to the trivector.
    */
    template <typename T>
    requires std::is_floating_point_v<T>
    Trivector4<T>& operator/=(Trivector4<T>& a, T b) noexcept
    {
        a.xyz/=b; a.yzw/=b; a.zwx/=b; a.wxy/=b;
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

YQ_TYPE_DECLARE(yq::Trivector4D)
YQ_TYPE_DECLARE(yq::Trivector4F)

