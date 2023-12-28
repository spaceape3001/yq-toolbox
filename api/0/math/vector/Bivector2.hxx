////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the bivector2 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <0/math/vector/Bivector2.hpp>

namespace yq {
    template <typename T>
    constexpr Bivector2<T> Bivector2<T>::operator+() const noexcept 
    { 
        return *this; 
    }

    template <typename T>
    constexpr Bivector2<T> Bivector2<T>::operator-() const noexcept
    {
        return Bivector2(-xy);
    }

    #ifdef YQ_MATH_MULTIVECTOR2_HPP
    template <typename T>
    constexpr Multivector2<T> Bivector2<T>::operator+(T b) const noexcept
    {
        return Multivector2<T>(
            b, 
            zero_v<T>, zero_v<T>,
            xy
        );
    }
    #endif

    template <typename T>
    constexpr Bivector2<T> Bivector2<T>::operator+(const Bivector2<T>& b) const noexcept
    {
        return Bivector2(
            xy+b.xy
        );
    }

    template <typename T>
    Bivector2<T>& Bivector2<T>::operator+=(const Bivector2<T>& b) noexcept
    {
        xy += b.xy;
        return *this;
    }
    
    #ifdef YQ_MATH_MULTIVECTOR2_HPP
    template <typename T>
    constexpr Multivector2<T> Bivector2<T>::operator+(const Multivector2<T>& b) const noexcept
    {
        return Multivector2<T>(
            b.a, 
            b.x, b.y,
            xy+b.xy
        );
    }
    #endif

    #if defined(YQ_MATH_MULTIVECTOR2_HPP) && defined(YQ_MATH_VECTOR_2_HPP)
    template <typename T>
    constexpr Multivector2<T> Bivector2<T>::operator+(const Vector2<T>& b) const noexcept
    {
        return Multivector2<T>(
            zero_v<T>, 
            b.x, b.y, 
            xy 
        );
    }
    #endif

    #ifdef YQ_MATH_MULTIVECTOR2_HPP
    template <typename T>
    constexpr Multivector2<T> Bivector2<T>::operator-(T b) const noexcept
    {
        return Multivector2<T>(
            -b, 
            zero_v<T>, zero_v<T>,
            xy
        );
    }
    #endif

    template <typename T>
    constexpr Bivector2<T> Bivector2<T>::operator-( const Bivector2<T>& b) const noexcept
    {
        return Bivector2(
            xy-b.xy
        );
    }

    template <typename T>
    Bivector2<T>& Bivector2<T>::operator-=(const Bivector2<T>& b) noexcept
    {
        xy -= b.xy;
        return *this;
    }

    #ifdef YQ_MATH_MULTIVECTOR2_HPP
    template <typename T>
    constexpr Multivector2<T> Bivector2<T>::operator-(const Multivector2<T>& b) const noexcept
    {
        return Multivector2<T>(
            -b.a, 
            -b.x, -b.y,
            xy-b.xy
        );
    }
    #endif

    #if defined(YQ_MATH_MULTIVECTOR2_HPP) && defined(YQ_MATH_VECTOR_2_HPP)
    template <typename T>
    constexpr Multivector2<T> Bivector2<T>::operator-(const Vector2<T>& b) const noexcept
    {
        return Multivector2<T>(
            zero_v<T>, 
            -b.x, -b.y, 
            xy 
        );
    }
    #endif


    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    constexpr Bivector2<product_t<T,U>> Bivector2<T>::operator*(U b) const noexcept
    {
        return Bivector2<product_t<T,U>>( xy*b );
    }

    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_mul_v<T,U>)
    Bivector2<T>& Bivector2<T>::operator*=(U b) noexcept
    {
        xy *= b;
        return *this;
    }

    template <typename T>
        template <typename U>
    requires is_arithmetic_v<T>
    constexpr Bivector2<quotient_t<T,U>> Bivector2<T>::operator/(U b) noexcept
    {
        return Bivector2<quotient_t<T,U>>( xy/b );
    }

    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_div_v<T,U>)
    Bivector2<T>& Bivector2<T>::operator/=(U b) noexcept
    {
        xy /= b;
        return *this;
    }


    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    #ifdef YQ_MATH_MULTIVECTOR2_HPP
    template <typename T>
    constexpr Multivector2<T> operator+(T a, const Bivector2<T>& b) noexcept
    {
        return Multivector2<T>(
            a, 
            zero_v<T>, zero_v<T>,
            b.xy
        );
    }
    #endif

    #ifdef YQ_MATH_MULTIVECTOR2_HPP
    template <typename T>
    constexpr Multivector2<T> operator-(T a, const Bivector2<T>& b) noexcept
    {
        return { 
            a, 
            zero_v<T>, zero_v<T>,
            -b.xy 
        };
    }    
    #endif

    /*! \brief Scaling multiplication operator
    
        \note currently limited to floating points due to uncertainty 
    */
    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Bivector2<product_t<T,U>> operator*(T a, const Bivector2<U>& b) noexcept
    {
        return Bivector2<product_t<T,U>>( a*b.xy );
    }

}
