////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the quadvector4 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <math/vector/Quadvector4.hpp>

namespace yq {

    template <typename T>
    constexpr Quadvector4<T> Quadvector4<T>::operator+() const noexcept
    {
        return *this;
    }
    

    template <typename T>
    constexpr Quadvector4<T> Quadvector4<T>::operator-() const noexcept
    {
        return Quadvector4(-xyzw);
    }

    #ifdef YQ_MATH_MULTIVECTOR4_HPP
    template <typename T>
    constexpr Multivector4<T> Quadvector4<T>::operator+(T b) const noexcept
    {
        return Multivector4<T>(
            b, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            xyzw 
        );
    }
    #endif

    #if defined(YQ_MATH_BIVECTOR4_HPP) && defined(YQ_MATH_MULTIVECTOR4_HPP)
    template <typename T>
    constexpr Multivector4<T> Quadvector4<T>::operator+(const Bivector4<T>& b) const noexcept
    {
        return Multivector4<T>(
            zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            b.xy, b.yz, b.zw, b.wx, b.xz, b.yw,
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            xyzw 
        );
    }
    #endif
    
    #ifdef YQ_MATH_MULTIVECTOR4_HPP
    template <typename T>
    constexpr Multivector4<T> Quadvector4<T>::operator+(const Multivector4<T>& b) const noexcept
    {
        return Multivector4<T>(
            b.a, 
            b.x, b.y, b.z, b.w, 
            b.xy, b.yz, b.zw, b.wx, b.xz, b.yw,
            b.xyz, b.yzw, b.zwx, b.wxy,
            xyzw + b.xyzw
        );
    }
    #endif

    template <typename T>
    constexpr Quadvector4<T> Quadvector4<T>::operator+(const Quadvector4<T>& b) const noexcept
    {
        return Quadvector4(xyzw + b.xyzw);
    }

    template <typename T>
    Quadvector4<T>& Quadvector4<T>::operator+=(const Quadvector4<T>& b) noexcept
    {
        xyzw += b.xyzw;
        return *this;
    }

    #if defined(YQ_MATH_MULTIVECTOR4_HPP) && defined(YQ_MATH_TRIVECTOR4_HPP)
    template <typename T>
    constexpr Multivector4<T> Quadvector4<T>::operator+(const Trivector4<T>& b) const noexcept
    {
        return Multivector4<T>(
            zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            b.xyz, b.yzw, b.zwx, b.wxy, 
            xyzw 
        );
    }
    #endif
    
    #if defined(YQ_MATH_MULTIVECTOR4_HPP) && defined(YQ_MATH_VECTOR_4_HPP)
    template <typename T>
    constexpr Multivector4<T> Quadvector4<T>::operator+(const Vector4<T>& b) const noexcept
    {
        return Multivector4<T>(
            zero_v<T>, 
            b.x, b.y, b.z, b.w, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            xyzw 
        );
    }
    #endif
    
    #ifdef YQ_MATH_MULTIVECTOR4_HPP
    template <typename T>
    constexpr Multivector4<T> Quadvector4<T>::operator-(T b) const noexcept
    {
        return Multivector4<T>(
            -b, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            xyzw
        );
    }
    #endif

    #if defined(YQ_MATH_BIVECTOR4_HPP) && defined(YQ_MATH_MULTIVECTOR4_HPP)
    template <typename T>
    constexpr Multivector4<T> Quadvector4<T>::operator-(const Bivector4<T>& b) const noexcept
    {
        return Multivector4<T>(
            zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            -b.xy, -b.yz, -b.zw, -b.wx, -b.xz, -b.yw,
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            xyzw
        );
    }
    #endif
    
    #ifdef YQ_MATH_MULTIVECTOR4_HPP
    template <typename T>
    constexpr Multivector4<T> Quadvector4<T>::operator-(const Multivector4<T>& b) const noexcept
    {
        return Multivector4<T>(
            -b.a, 
            -b.x, -b.y, -b.z, -b.w, 
            -b.xy, -b.yz, -b.zw, -b.wx, -b.xz, -b.yw,
            -b.xyz, -b.yzw, -b.zwx, -b.wxy,
            xyzw -b.xyzw
        );
    }
    #endif

    template <typename T>
    constexpr Quadvector4<T> Quadvector4<T>::operator-(const Quadvector4<T>& b) const noexcept
    {
        return { xyzw - b.xyzw };
    }

    template <typename T>
    Quadvector4<T>& Quadvector4<T>::operator-=(const Quadvector4<T>& b) noexcept
    {
        xyzw -= b.xyzw;
        return *this;
    }
    
    #if defined(YQ_MATH_MULTIVECTOR4_HPP) && defined(YQ_MATH_TRIVECTOR4_HPP)
    template <typename T>
    constexpr Multivector4<T> Quadvector4<T>::operator-(const Trivector4<T>& b) const noexcept
    {
        return Multivector4<T>(
            zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            -b.xyz, -b.yzw, -b.zwx, -b.wxy, 
            xyzw
        );
    }
    #endif

    #if defined(YQ_MATH_MULTIVECTOR4_HPP) && defined(YQ_MATH_VECTOR_4_HPP)
    template <typename T>
    constexpr Multivector4<T> Quadvector4<T>::operator-(const Vector4<T>& b) const noexcept
    {
        return Multivector4<T>(
            zero_v<T>, 
            -b.x, -b.y, -b.z, -b.w, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            xyzw
        );
    }
    #endif


    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    constexpr Quadvector4<product_t<T,U>> Quadvector4<T>::operator*(U b) const noexcept
    {
        return Quadvector4<product_t<T,U>>( xyzw*b );
    }

    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_mul_v<T,U>)
    Quadvector4<T>& Quadvector4<T>::operator*=(U b) noexcept
    {
        xyzw*=b;
        return *this;
    }


    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    constexpr Quadvector4<quotient_t<T,U>> Quadvector4<T>::operator/(U b) const noexcept
    {
        return Quadvector4<quotient_t<T,U>>( xyzw/b );
    }

    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_div_v<T,U>)
    Quadvector4<T>& Quadvector4<T>::operator/=(U b) noexcept
    {
        xyzw/=b;
        return *this;
    }
    
    
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    #ifdef YQ_MATH_MULTIVECTOR4_HPP
    template <typename T>
    constexpr Multivector4<T> operator+(T a, const Quadvector4<T>& b) noexcept
    {
        return Multivector4<T>(
            a,
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            b.xyzw 
        );
    }
    #endif

    #ifdef YQ_MATH_MULTIVECTOR4_HPP
    template <typename T>
    constexpr Multivector4<T> operator-(T a, const Quadvector4<T>& b) noexcept
    {
        return Multivector4<T>(
            a,
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            -b.xyzw 
        );
    }
    #endif


    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Quadvector4<product_t<T,U>> operator*(T a, const Quadvector4<U>& b) noexcept
    {
        return Quadvector4<product_t<T,U>>( a*b.xyzw );
    }
    
}
