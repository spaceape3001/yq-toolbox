////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the trivector4 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <yq/vector/Trivector4.hpp>


namespace yq {
    template <typename T>
    constexpr Trivector4<T> Trivector4<T>::operator+() const noexcept
    {
        return *this;
    }

    template <typename T>
    constexpr Trivector4<T> Trivector4<T>::operator-() const noexcept
    {
        return Trivector4(-xyz, -yzw, -zwx, -wxy);
    }

    #ifdef YQ_MATH_MULTIVECTOR4_HPP
    template <typename T>
    constexpr Multivector4<T> Trivector4<T>::operator+(T b) const noexcept
    {
        return Multivector4<T>(
            b, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            xyz, yzw, zwx, wxy, 
            zero_v<T> 
        );
    }
    #endif

    #if defined(YQ_MATH_BIVECTOR4_HPP) && defined(YQ_MATH_MULTIVECTOR4_HPP)
    template <typename T>
    constexpr Multivector4<T> Trivector4<T>::operator+(const Bivector4<T>& b) const noexcept
    {
        return Multivector4<T>(
            zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            b.xy, b.yz, b.zw, b.wx, b.xz, b.yw,
            xyz, yzw, zwx, wxy, 
            zero_v<T> 
        );
    }
    #endif

    #ifdef YQ_MATH_MULTIVECTOR4_HPP
    template <typename T>
    constexpr Multivector4<T> Trivector4<T>::operator+(const Multivector4<T>& b) const noexcept
    {
        return Multivector4<T>(
            b.a, 
            b.x, b.y, b.z, b.w, 
            b.xy, b.yz, b.zw, b.wx, b.xz, b.yw,
            xyz+b.xyz, yzw+b.yzw, zwx+b.zwx, wxy+b.wxy,
            b.xyzw
        );
    }
    #endif

    #if defined(YQ_MATH_MULTIVECTOR4_HPP) && defined(YQ_MATH_QUADVECTOR4_HPP)
    template <typename T>
    constexpr Multivector4<T> Trivector4<T>::operator+(const Quadvector4<T>& b) const noexcept
    {
        return Multivector4<T>(
            zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            xyz, yzw, zwx, wxy, 
            b.xyzw 
        );
    }
    #endif
    
    template <typename T>
    constexpr Trivector4<T> Trivector4<T>::operator+(const Trivector4<T>& b) const noexcept
    {
        return Trivector4( xyz+b.xyz, yzw+b.yzw, zwx+b.zwx, wxy+b.wxy );
    }

    template <typename T>
    Trivector4<T>& Trivector4<T>::operator+=(const Trivector4<T>& b) noexcept
    {
        xyz+=b.xyz; yzw+=b.yzw; zwx+=b.zwx; wxy+=b.wxy;
        return *this;
    }

    #if defined(YQ_MATH_MULTIVECTOR4_HPP) && defined(YQ_MATH_VECTOR_4_HPP)
    template <typename T>
    constexpr Multivector4<T> Trivector4<T>::operator+(const Vector4<T>& b) const noexcept
    {
        return Multivector4<T>(
            zero_v<T>, 
            b.x, b.y, b.z, b.w, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            xyz, yzw, zwx, wxy, 
            zero_v<T> 
        );
    }
    #endif
    
    #ifdef YQ_MATH_MULTIVECTOR4_HPP
    template <typename T>
    constexpr Multivector4<T> Trivector4<T>::operator-(T b) const noexcept
    {
        return Multivector4<T>(
            -b, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            xyz, yzw, zwx, wxy, 
            zero_v<T> 
        );
    }
    #endif

    #if defined(YQ_MATH_BIVECTOR4_HPP) && defined(YQ_MATH_MULTIVECTOR4_HPP)
    template <typename T>
    constexpr Multivector4<T> Trivector4<T>::operator-(const Bivector4<T>& b) const noexcept
    {
        return Multivector4<T>(
            zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            -b.xy, -b.yz, -b.zw, -b.wx, -b.xz, -b.yw,
            xyz, yzw, zwx, wxy, 
            zero_v<T> 
        );
    }
    #endif

    #ifdef YQ_MATH_MULTIVECTOR4_HPP
    template <typename T>
    constexpr Multivector4<T> Trivector4<T>::operator-(const Multivector4<T>& b) const noexcept
    {
        return Multivector4<T>(
            -b.a, 
            -b.x, -b.y, -b.z, -b.w, 
            -b.xy, -b.yz, -b.zw, -b.wx, -b.xz, -b.yw,
            xyz-b.xyz, yzw-b.yzw, zwx-b.zwx, wxy-b.wxy,
            -b.xyzw
        );
    }
    #endif

    #if defined(YQ_MATH_MULTIVECTOR4_HPP) && defined(YQ_MATH_QUADVECTOR4_HPP)
    template <typename T>
    constexpr Multivector4<T> Trivector4<T>::operator-(const Quadvector4<T>& b) const noexcept
    {
        return Multivector4<T>(
            zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            xyz, yzw, zwx, wxy, 
            -b.xyzw 
        );
    }
    #endif
    
    template <typename T>
    constexpr Trivector4<T> Trivector4<T>::operator-(const Trivector4<T>& b) const noexcept
    {
        return Trivector4( xyz-b.xyz, yzw-b.yzw, zwx-b.zwx, wxy-b.wxy );
    }

        
    #if defined(YQ_MATH_MULTIVECTOR4_HPP) && defined(YQ_MATH_VECTOR_4_HPP)
    template <typename T>
    constexpr Multivector4<T> Trivector4<T>::operator-(const Vector4<T>& b) const noexcept
    {
        return Multivector4<T>(
            zero_v<T>, 
            -b.x, -b.y, -b.z, -b.w, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            xyz, yzw, zwx, wxy, 
            zero_v<T> 
        );
    }
    #endif

    template <typename T>
    Trivector4<T>& Trivector4<T>::operator-=(const Trivector4<T>& b) noexcept
    {
        xyz-=b.xyz; yzw-=b.yzw; zwx-=b.zwx; wxy-=b.wxy;
        return *this;
    }
    
    
    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    constexpr Trivector4<product_t<T,U>> Trivector4<T>::operator*(U b) const noexcept
    {
        return Trivector4<product_t<T,U>>( xyz*b, yzw*b, zwx*b, wxy*b );
    }

    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
    Trivector4<T>& Trivector4<T>::operator*=(U b) noexcept
    {
        xyz*=b; yzw*=b; zwx*=b; wxy*=b;
        return *this;
    }

    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    constexpr Trivector4<quotient_t<T,U>> Trivector4<T>::operator/(U b) const noexcept
    {
        return Trivector4<quotient_t<T,U>>( xyz/b, yzw/b, zwx/b, wxy/b );
    }

    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_divide_v<T,U>)
    Trivector4<T>& Trivector4<T>::operator/=(U b) noexcept
    {
        xyz/=b; yzw/=b; zwx/=b; wxy/=b;
        return *this;
    }


    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    #ifdef YQ_MATH_MULTIVECTOR4_HPP
    template <typename T>
    constexpr Multivector4<T> operator+(T a, const Trivector4<T>& b) noexcept
    {
        return Multivector4<T>(
            a, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            b.xyz, b.yzw, b.zwx, b.wxy, 
            zero_v<T> 
        );
    }
    #endif

    #ifdef YQ_MATH_MULTIVECTOR4_HPP
    template <typename T>
    constexpr Multivector4<T> operator-(T a, const Trivector4<T>& b) noexcept
    {
        return Multivector4<T>(
            a, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            -b.xyz, -b.yzw, -b.zwx, -b.wxy, 
            zero_v<T> 
        );
    }
    #endif

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Trivector4<product_t<T,U>> operator*(T a, const Trivector4<U>& b) noexcept
    {
        return Trivector4<product_t<T,U>>( a*b.xyz, a*b.yzw, a*b.zwx, a*b.wxy );
    }

}
