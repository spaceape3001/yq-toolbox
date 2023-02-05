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

#include <math/Bivector2.hpp>
#include <math/Multivector2.hpp>
#include <math/Vector2.hpp>

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

    template <typename T>
    constexpr Multivector2<T> Bivector2<T>::operator+(T b) const noexcept
    {
        return Multivector2<T>(
            b, 
            zero_v<T>, zero_v<T>,
            xy
        );
    }

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
    
    template <typename T>
    constexpr Multivector2<T> Bivector2<T>::operator+(const Multivector2<T>& b) const noexcept
    {
        return Multivector2<T>(
            b.a, 
            b.x, b.y,
            xy+b.xy
        );
    }

    template <typename T>
    constexpr Multivector2<T> Bivector2<T>::operator+(const Vector2<T>& b) const noexcept
    {
        return Multivector2<T>(
            zero_v<T>, 
            b.x, b.y, 
            xy 
        );
    }

    template <typename T>
    constexpr Multivector2<T> Bivector2<T>::operator-(T b) const noexcept
    {
        return Multivector2<T>(
            -b, 
            zero_v<T>, zero_v<T>,
            xy
        );
    }

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

    template <typename T>
    constexpr Multivector2<T> Bivector2<T>::operator-(const Multivector2<T>& b) const noexcept
    {
        return Multivector2<T>(
            -b.a, 
            -b.x, -b.y,
            xy-b.xy
        );
    }

    template <typename T>
    constexpr Multivector2<T> Bivector2<T>::operator-(const Vector2<T>& b) const noexcept
    {
        return Multivector2<T>(
            zero_v<T>, 
            -b.x, -b.y, 
            xy 
        );
    }


    template <typename T>
        template <typename U>
    requires trait::is_arithmetic_v<U>
    constexpr Bivector2<trait::product_t<T,U>> Bivector2<T>::operator*(U b) const noexcept
    {
        return Bivector2<trait::product_t<T,U>>( xy*b );
    }

    template <typename T>
        template <typename U>
    requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Bivector2<T>& Bivector2<T>::operator*=(U b) noexcept
    {
        xy *= b;
        return *this;
    }

    template <typename T>
        template <typename U>
    requires trait::is_arithmetic_v<T>
    constexpr Bivector2<trait::quotient_t<T,U>> Bivector2<T>::operator/(U b) noexcept
    {
        return Bivector2<trait::quotient_t<T,U>>( xy/b );
    }

    template <typename T>
        template <typename U>
    requires (trait::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Bivector2<T>& Bivector2<T>::operator/=(U b) noexcept
    {
        xy /= b;
        return *this;
    }


    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    //! Adds scalar with bivector
    template <typename T>
    constexpr Multivector2<T> operator+(T a, const Bivector2<T>& b) noexcept
    {
        return Multivector2<T>(
            a, 
            zero_v<T>, zero_v<T>,
            b.xy
        );
    }

    template <typename T>
    constexpr Multivector2<T> operator-(T a, const Bivector2<T>& b) noexcept
    {
        return { 
            a, 
            zero_v<T>, zero_v<T>,
            -b.xy 
        };
    }    

    /*! \brief Scaling multiplication operator
    
        \note currently limited to floating points due to uncertainty 
    */
    template <typename T, typename U>
    requires trait::is_arithmetic_v<T>
    constexpr Bivector2<trait::product_t<T,U>> operator*(T a, const Bivector2<U>& b) noexcept
    {
        return Bivector2<trait::product_t<T,U>>( a*b.xy );
    }

}
