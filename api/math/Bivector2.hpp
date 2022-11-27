////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>

namespace yq {
    /*! \brief 2D Bivector
    
        Two dimensional bivector
    */
    template <typename T>
    struct Bivector2 {
    
        //! Component type
        using component_type = T;
        
        //! The value... since it's a unit area, square of T
        square_t<T>     xy;
        
        //! Defaulted comparison operator
        constexpr auto operator<=>(const Bivector2&) const noexcept = default;
    };

    YQ_IEEE754_1(Bivector2)

//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Literal constructor
    */
    constexpr Bivector2D  operator "" _xy2(unsigned long long int v) noexcept
    {
        return {(double) v};
    }

    /*! \brief Literal constructor
    */
    constexpr Bivector2D  operator "" _xy2(long double v) noexcept
    {
        return {(double) v};
    }

    
    YQ_NAN_1(Bivector2, Bivector2<T>{nan_v<square_t<T>>})
    YQ_ZERO_1(Bivector2, Bivector2<T>{zero_v<square_t<T>>})
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS

    /*! \brief Checks for finiteness
    */
    template <typename T>
    constexpr bool is_finite(const Bivector2<T>&v)
    {
        return is_finite(v.xy);
    }

    YQ_IS_NAN_1(Bivector2, is_nan(v.xy))


//  --------------------------------------------------------
//  POSITIVE

    /*! \brief Affirmation (positive) operator
    
        \note Here to complement the negation operator
    */
    template <typename T>
    constexpr Bivector2<T> operator+(const Bivector2<T>& a) noexcept
    {
        return a;
    }


//  --------------------------------------------------------
//  NEGATIVE

    /*! \brief Negation operator of a bivector
    */
    template <typename T>
    constexpr Bivector2<T> operator-(const Bivector2<T>& a) noexcept
    {
        return {-a.xy};
    }


//  --------------------------------------------------------
//  NORMALIZATION


//  --------------------------------------------------------
//  ADDITION

    /*! \brief Addition operator
    */
    template <typename T>
    constexpr Bivector2<T> operator+(const Bivector2<T>& a, const Bivector2<T>& b) noexcept
    {
        return {
            a.xy+b.xy
        };
    }

    /*! \brief Self-Addition operator
    */
    template <typename T>
    Bivector2<T>& operator+=(Bivector2<T>& a, const Bivector2<T>& b) noexcept
    {
        a.xy += b.xy;
        return a;
    }

//  --------------------------------------------------------
//  SUBTRACTION

    /*! \brief Subtraction operator
    */
    template <typename T>
    constexpr Bivector2<T> operator-(const Bivector2<T>& a, const Bivector2<T>& b) noexcept
    {
        return {
            a.xy-b.xy
        };
    }

    /*! \brief Self-subtraction operator 
    */
    template <typename T>
    Bivector2<T>& operator-=(Bivector2<T>& a, const Bivector2<T>& b) noexcept
    {
        a.xy -= b.xy;
        return a;
    }

//  --------------------------------------------------------
//  MULTIPLICATION

    /*! \brief Scaling multiplication operator
    
        \note currently limited to floating points due to uncertainty 
    */
    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Bivector2<T> operator*(T a, const Bivector2<T>& b) noexcept
    {
        return { a*b.xy };
    }

    /*! \brief Scaling multiplication operator
    
        \note currently limited to floating points due to uncertainty 
    */
    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Bivector2<T> operator*(const Bivector2<T>& a, T b) noexcept
    {
        return { a.xy*b };
    }

    /*! \brief Self-scaling multiplication operator
    
        \note currently limited to floating points due to uncertainty 
    */
    template <typename T>
    requires std::is_floating_point_v<T>
    Bivector2<T> operator*=(Bivector2<T>& a, T b) noexcept
    {
        a.xy *= b;
        return a;
    }

//  --------------------------------------------------------
//  DIVISION

    /*! \brief Scaling division operator
    
        \note currently limited to floating points due to uncertainty 
    */
    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Bivector2<T> operator/(const Bivector2<T>& a, T b) noexcept
    {
        return { a.xy/b };
    }

    /*! \brief Self-scaling division operator
    
        \note currently limited to floating points due to uncertainty 
    */
    template <typename T>
    requires std::is_floating_point_v<T>
    Bivector2<T> operator/=(Bivector2<T>& a, T b) noexcept
    {
        a.xy /= b;
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

    /*! \brief Outer product for 2 dimensional vectors
    
        \note currently limited to floating points due to uncertainty 
    */
    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Bivector2<T> operator OUTER (const Vector2<T>&a, const Vector2<T>& b) noexcept
    {
        return { a.x*b.y-a.y*b.x };
    }


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

YQ_TYPE_DECLARE(yq::Bivector2D)
YQ_TYPE_DECLARE(yq::Bivector2F)

