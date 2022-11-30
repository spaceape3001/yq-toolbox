////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>

namespace yq {

    /*! \brief Four dimensional quadvector
    
        Quadvector for four dimensions.  (ie a measure of hypervolume)
    */
    template <typename T>
    struct Quadvector4 {

        //! Component type
        using component_type = T;

        //! Component
        fourth_t<T>     xyzw;

        //! Defaulted comparison operator
        constexpr auto operator<=>(const Quadvector4&) const noexcept = default;
    };

    YQ_IEEE754_1(Quadvector4)

//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Literal constructor
    */
    constexpr Quadvector4D   operator "" _xyzw4(unsigned long long int v) noexcept
    {
        return {(double) v};
    }

    /*! \brief Literal constructor
    */
    constexpr Quadvector4D   operator "" _xyzw4(long double v) noexcept
    {
        return {(double) v};
    }

    YQ_NAN_1(Quadvector4, Quadvector4<T>{nan_v<fourth_t<T>>})
    YQ_ZERO_1(Quadvector4, Quadvector4<T>{zero_v<fourth_t<T>>})

//  --------------------------------------------------------
//  GETTERS

//  --------------------------------------------------------
//  BASIC FUNCTIONS
    
    YQ_IS_NAN_1(Quadvector4, is_nan(v.xyzw))
    YQ_IS_FINITE_1(Quadvector4, is_finite(v.xyzw))


//  --------------------------------------------------------
//  POSITIVE

    /*! \brief Affirmation (positive) operator
    
        \note Here to complement the negation operator
    */
    template <typename T>
    constexpr Quadvector4<T> operator+(const Quadvector4<T>& a) noexcept
    {
        return a;
    }
    
//  --------------------------------------------------------
//  NEGATIVE

    /*! \brief Negation operator of a bivector
    */
    template <typename T>
    constexpr Quadvector4<T> operator-(const Quadvector4<T>& a) noexcept
    {
        return {-a.xyzw};
    }
    

//  --------------------------------------------------------
//  NORMALIZATION


//  --------------------------------------------------------
//  ADDITION

    /*! \brief Addition operator
    */
    template <typename T>
    constexpr Quadvector4<T> operator+(const Quadvector4<T>& a, const Quadvector4<T>& b) noexcept
    {
        return { a.xyzw + b.xyzw };
    }

    /*! \brief Self-Addition operator
    */
    template <typename T>
    Quadvector4<T>& operator+=(Quadvector4<T>& a, const Quadvector4<T>& b) noexcept
    {
        a.xyzw += b.xyzw;
        return a;
    }


//  --------------------------------------------------------
//  SUBTRACTION

    /*! \brief Subtraction operator
    */
    template <typename T>
    constexpr Quadvector4<T> operator-(const Quadvector4<T>& a, const Quadvector4<T>& b) noexcept
    {
        return { a.xyzw - b.xyzw };
    }

    /*! \brief Self-subtraction operator 
    */
    template <typename T>
    Quadvector4<T>& operator-=(Quadvector4<T>& a, const Quadvector4<T>& b) noexcept
    {
        a.xyzw -= b.xyzw;
        return a;
    }

//  --------------------------------------------------------
//  MULTIPLICATION

    /*! \brief Scaling multiplication operator
    
        \note currently limited to floating points due to uncertainty 
    */
    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Quadvector4<T> operator*(T a, const Quadvector4<T>& b) noexcept
    {
        return { a*b.xyzw };
    }

    /*! \brief Scaling multiplication operator
    
        \note currently limited to floating points due to uncertainty 
    */
    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Quadvector4<T> operator*(const Quadvector4<T>& a, T b) noexcept
    {
        return { a.xyzw*b };
    }

    /*! \brief Self-scaling multiplication operator
    
        \note currently limited to floating points due to uncertainty 
    */
    template <typename T>
    requires std::is_floating_point_v<T>
    Quadvector4<T> operator*=(Quadvector4<T>& a, T b) noexcept
    {
        a.xyzw*=b;
        return a;
    }


//  --------------------------------------------------------
//  DIVISION

    /*! \brief Scaling division operator
    
        \note currently limited to floating points due to uncertainty 
    */
    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Quadvector4<T> operator/(const Quadvector4<T>& a, T b) noexcept
    {
        return { a.xyzw/b };
    }

    /*! \brief Self-scaling division operator
    
        \note currently limited to floating points due to uncertainty 
    */
    template <typename T>
    requires std::is_floating_point_v<T>
    Quadvector4<T> operator/=(Quadvector4<T>& a, T b) noexcept
    {
        a.xyzw/=b;
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

YQ_TYPE_DECLARE(yq::Quadvector4D)
YQ_TYPE_DECLARE(yq::Quadvector4F)

