////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/Bivector2.hpp>
#include <math/Multivector2.hpp>
#include <math/Vector2.hpp>

/* 
    This is the template IMPLEMENTATION of the multivector2 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

namespace yq {
    template <typename T>
    constexpr Multivector2<T> Multivector2<T>::operator+() const noexcept
    {
        return *this;
    }

    template <typename T>
    constexpr Multivector2<T> Multivector2<T>::operator-() const noexcept
    {
        return {-a, -x, -y, -xy};
    }

    template <typename T>
    constexpr Multivector2<T> Multivector2<T>::operator+(T  b) const noexcept
    {
        return Multivector2(
            a+b,
            x, y,
            xy
        );
    }

    template <typename T>
    Multivector2<T>& Multivector2<T>::operator+=(T b) noexcept
    {
        a += b;
        return *this;
    }

    template <typename T>
    constexpr Multivector2<T> Multivector2<T>::operator+(const Bivector2<T>& b) const noexcept
    {
        return Multivector2(
            a,
            x, y,
            xy + b.xy
        );
    }

    template <typename T>
    Multivector2<T>& Multivector2<T>::operator+=(const Bivector2<T>& b) noexcept
    {
        xy += b.xy;
        return *this;
    }

    template <typename T>
    constexpr Multivector2<T> Multivector2<T>::operator+(const Multivector2<T>& b) const noexcept
    {
        return Multivector2(
            a+b.a,
            x+b.x, y+b.y,
            xy+b.xy
        );
    }

    template <typename T>
    Multivector2<T>& Multivector2<T>::operator+=(const Multivector2<T>& b) noexcept
    {
        a += b.a;
        x += b.x; y += b.y; 
        xy += b.xy;
        return *this;
    }
        

    template <typename T>
    constexpr Multivector2<T> Multivector2<T>::operator+(const Vector2<T>& b) const noexcept
    {
        return Multivector2(
            a,
            x+b.x, y+b.y,
            xy
        );
    }

    template <typename T>
    Multivector2<T>& Multivector2<T>::operator+=(const Vector2<T>& b) noexcept
    {
        x += b.x; y += b.y; 
        return *this;
    }

    template <typename T>
    constexpr Multivector2<T> Multivector2<T>::operator-(T b) const noexcept
    {
        return Multivector2(
            a-b,
            x, y,
            xy
        );
    }

    template <typename T>
    Multivector2<T>& Multivector2<T>::operator-=(T b) noexcept
    {
        a -= b;
        return *this;
    }

    template <typename T>
    constexpr Multivector2<T> Multivector2<T>::operator-(const Bivector2<T>& b) const noexcept
    {
        return Multivector2(
            a,
            x, y,
            xy - b.xy
        );
    }

    template <typename T>
    Multivector2<T>& Multivector2<T>::operator-=(const Bivector2<T>& b) noexcept
    {
        xy -= b.xy;
        return *this;
    }

    template <typename T>
    constexpr Multivector2<T> Multivector2<T>::operator-(const Multivector2<T>& b) const noexcept
    {
        return Multivector2(
            a-b.a,
            x-b.x, y-b.y,
            xy-b.xy
        );
    }

    template <typename T>
    Multivector2<T>& Multivector2<T>::operator-=(const Multivector2<T>& b) noexcept
    {
        a -= b.a;
        x -= b.x; y -= b.y; 
        xy -= b.xy;
        return *this;
    }
    

    template <typename T>
    constexpr Multivector2<T> Multivector2<T>::operator-(const Vector2<T>& b) const noexcept
    {
        return Multivector2(
            a,
            x-b.x, y-b.y,
            xy
        );
    }

    template <typename T>
    Multivector2<T>& Multivector2<T>::operator-=(const Vector2<T>& b) noexcept
    {
        x -= b.x; y -= b.y; 
        return *this;
    }
    
    template <typename T>
        template <typename U>
    requires trait::is_arithmetic_v<U>
    constexpr Multivector2<product_t<T,U>> Multivector2<T>::operator*(U b) const noexcept
    {
        return Multivector2<product_t<T,U>>(
            a*b, 
            x*b, y*b, 
            xy*b 
        );
    }

    //! Self-scalaring multiplying left multivector by right scalar
    template <typename T>
        template <typename U>
    requires trait::is_arithmetic_v<U>
    Multivector2<T>& Multivector2<T>::operator*=(U b) noexcept
    {
        a  *= b;
        x  *= b; y *= b; 
        xy *= b;
        return *this;
    }

    //! Scaling division, reducing the left mulitvector by the right value
    template <typename T>
        template <typename U>
    requires trait::is_arithmetic_v<U>
    constexpr Multivector2<quotient_t<T,U>> Multivector2<T>::operator/(U b) const noexcept
    {
        return Multivector2<quotient_t<T,U>>(
            a/b, 
            x/b, y/b, 
            xy/b 
        );
    }

    //! Self-scaling division, reducing the left mulitvector by the right value
    template <typename T>
        template <typename U>
    requires trait::is_arithmetic_v<U>
    Multivector2<T>& Multivector2<T>::operator/=(U b) noexcept
    {
        a  /= b;
        x  /= b; y /= b; 
        xy /= b;
        return *this;
    }

    template <typename T>
    constexpr Bivector2<T>  Multivector2<T>::bivector() const noexcept 
    { 
        return Bivector2<T>(xy); 
    }

    template <typename T>
    constexpr Vector2<T>    Multivector2<T>::vector() const noexcept 
    { 
        return Vector2<T>(x,y); 
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


    //! Subtracts multivector from scalar
    template <typename T>
    constexpr Multivector2<T> operator-(T a, const Multivector2<T>& b) noexcept
    {
        return { 
            a-b.a, 
            -b.x, -b.y, 
            -b.xy
        };
    }

    template <typename T>
    constexpr Multivector2<T> operator+(T a, const Multivector2<T>& b) noexcept
    {
        return { 
            a+b.a, 
            b.x, b.y, 
            b.xy
        };
    }

    template <typename T, typename U>
    requires trait::is_arithmetic_v<U>
    constexpr Multivector2<product_t<T,U>> operator*(T a, const Multivector2<U>&b) noexcept
    {
        return Multivector2<product_t<T,U>>(
            a*b.a, 
            a*b.x, a*b.y, 
            a*b.xy 
        );
    }
    
    template <typename T>
    constexpr Bivector2<T> bivector(const Multivector2<T>& a) noexcept
    {
        return a.bivector();
    }

    template <typename T>
    constexpr Vector2<T> vector(const Multivector2<T>& a) noexcept
    {
        return a.vector();
    }

}
