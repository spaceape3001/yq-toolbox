////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the multivector1 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <0/math/vector/Multivector1.hpp>
#include <0/math/vector/Vector1.hpp>

namespace yq {
    template <typename T>
    constexpr Multivector1<T> Multivector1<T>::operator+() const noexcept
    {
        return *this;
    }

    template <typename T>
    constexpr Multivector1<T> Multivector1<T>::operator-() const noexcept
    {
        return Multivector1(-a, -x);
    }


    template <typename T>
    constexpr Multivector1<T> Multivector1<T>::operator+(T  b) const noexcept
    {
        return Multivector1(
            a+b,
            x
        );
    }

    template <typename T>
    Multivector1<T>& Multivector1<T>::operator+=(T  b) noexcept
    {
        a += b;
        return *this;
    }

    template <typename T>
    constexpr Multivector1<T> Multivector1<T>::operator+(const Multivector1<T>&  b) const noexcept
    {
        return Multivector1(
            a+b.a,
            x+b.x
        );
    }

    template <typename T>
    Multivector1<T>& Multivector1<T>::operator+=(const Multivector1<T>& b) noexcept
    {
        a += b.a;
        x += b.x;
        return *this;
    }


    template <typename T>
    constexpr Multivector1<T> Multivector1<T>::operator+(const Vector1<T>&  b) const noexcept
    {
        return Multivector1(
            a,
            x+b.x
        );
    }

    template <typename T>
    Multivector1<T>& Multivector1<T>::operator+=(const Vector1<T>& b) noexcept
    {
        x += b.x;
        return *this;
    }

    template <typename T>
    constexpr Multivector1<T> Multivector1<T>::operator-(T b) const noexcept
    {
        return Multivector1(
            a-b,
            x
        );
    }

    template <typename T>
    Multivector1<T>& Multivector1<T>::operator-=(T b) noexcept
    {
        a -= b;
        return *this;
    }

    template <typename T>
    constexpr Multivector1<T> Multivector1<T>::operator-(const Multivector1<T>& b) const noexcept
    {
        return Multivector1(
            a-b.a,
            x-b.x
        );
    }

    template <typename T>
    Multivector1<T>& Multivector1<T>::operator-=(const Multivector1<T>& b) noexcept
    {
        a -= b.a;
        x -= b.x;
        return *this;
    }
    

    template <typename T>
    constexpr Multivector1<T> Multivector1<T>::operator-(const Vector1<T>& b) const noexcept
    {
        return Multivector1(
            a,
            x-b.x
        );
    }

    template <typename T>
    Multivector1<T>& Multivector1<T>::operator-=(const Vector1<T>& b) noexcept
    {
        x -= b.x;
        return *this;
    }


    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    constexpr Multivector1<product_t<T,U>> Multivector1<T>::operator*(U b) const noexcept
    {
        return Multivector1<product_t<T,U>>( a*b, x*b );
    }

    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
    Multivector1<T>& Multivector1<T>::operator*=(U b) noexcept
    {
        a*=b; x*=b;
        return *this;
    }

    template <typename T>
        template <typename U>
    constexpr Multivector1<product_t<T,U>> Multivector1<T>::operator*(const Vector1<U>& b) const noexcept
    {
        return Multivector1<product_t<T,U>>( x*b.x, a*b.x );
    }

    template <typename T>
        template <typename U>
    requires self_multiply_v<T,U>
    Multivector1<T>& Multivector1<T>::operator*=(const Vector1<U>& b) noexcept
    {
        x *= b.x;
        a *= b.x;
        return *this;
    }

    template <typename T>
        template <typename U>
    constexpr Multivector1<product_t<T,U>> Multivector1<T>::operator*(const Multivector1<U>& b) const noexcept
    {
        return Multivector1<product_t<T,U>>( a*b.a+x*b.x, a*b.x+x*b.a );
    }
    
    template <typename T>
        template <typename U>
    requires self_multiply_v<T,U>
    Multivector1<T>& Multivector1<T>::operator*=(const Multivector1<U>& b) noexcept
    {
        a   = a*b;
        return *this;
    }

    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    constexpr Multivector1<quotient_t<T,U>> Multivector1<T>::operator/(U b) const noexcept
    {
        return Multivector1<quotient_t<T,U>>( a/b, x/b );
    }

    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_divide_v<T,U>)
    Multivector1<T>& Multivector1<T>::operator/=(U b) noexcept
    {
        a/=b; x/=b;
        return *this;
    }
    
    //  NOTE we're missing some others divisions... TODO

    template <typename T>
        template <typename U>
    constexpr product_t<T,U>   Multivector1<T>::operator INNER(const Multivector1<U>&b)  const noexcept
    {
        return x * b.x;
    }

    template <typename T>
        template <typename U>
    constexpr product_t<T,U>   Multivector1<T>::operator INNER(const Vector1<U>&b) const noexcept
    {
        return x * b.x;
    }


    template <typename T>
    constexpr Vector1<T>  Multivector1<T>::vector() const noexcept
    {
        return Vector1<T>(x);
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename T>
    constexpr Multivector1<T> operator+(T a, const Multivector1<T>& b) noexcept
    {
        return Multivector1<T>(
            a+b.a, 
            b.x 
        );
    }

    template <typename T>
    constexpr Multivector1<T> operator-(T a, const Multivector1<T>& b) noexcept
    {
        return Multivector1<T>(
            a-b.a, 
            -b.x 
        );
    }

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Multivector1<product_t<T,U>> operator*(T a, const Multivector1<U>&b) noexcept
    {
        return Multivector1<product_t<T,U>>( a*b.a, a*b.x );
    }

    template <typename T>
    constexpr Vector1<T> vector(const Multivector1<T>& a) noexcept
    {
        return a.vector();
    }

}
