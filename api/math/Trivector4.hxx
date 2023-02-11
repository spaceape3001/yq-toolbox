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

#include <math/Bivector4.hpp>
#include <math/Multivector4.hpp>
#include <math/Quadvector4.hpp>
#include <math/Trivector4.hpp>


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
    
    template <typename T>
    constexpr Trivector4<T> Trivector4<T>::operator-(const Trivector4<T>& b) const noexcept
    {
        return Trivector4( xyz-b.xyz, yzw-b.yzw, zwx-b.zwx, wxy-b.wxy );
    }

        
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
    requires (is_arithmetic_v<U> && self_mul_v<T,U>)
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
    requires (is_arithmetic_v<U> && self_div_v<T,U>)
    Trivector4<T>& Trivector4<T>::operator/=(U b) noexcept
    {
        xyz/=b; yzw/=b; zwx/=b; wxy/=b;
        return *this;
    }


    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

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

    /*! Scalar/trivector subtraction
    */
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

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Trivector4<product_t<T,U>> operator*(T a, const Trivector4<U>& b) noexcept
    {
        return Trivector4<product_t<T,U>>( a*b.xyz, a*b.yzw, a*b.zwx, a*b.wxy );
    }

}
