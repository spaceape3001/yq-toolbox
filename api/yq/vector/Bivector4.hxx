////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the bivector4 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <yq/vector/Bivector4.hpp>

namespace yq {

    template <typename T>
    constexpr Bivector4<T> Bivector4<T>::operator+() const noexcept
    {
        return *this;
    }


    template <typename T>
    constexpr Bivector4<T> Bivector4<T>::operator-() const noexcept
    {
        return Bivector4(-xy, -yz, -zw, -wx, -xz, -yw);
    }

    #ifdef YQ_MATH_MULTIVECTOR4_HPP
    template <typename T>
    constexpr Multivector4<T> Bivector4<T>::operator+(T b) const noexcept
    {
        return Multivector4<T>(
            b, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            xy, yz, zw, wx, xz, yw, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T> 
        );
    }
    #endif

    template <typename T>
    constexpr Bivector4<T> Bivector4<T>::operator+(const Bivector4<T>& b) const noexcept
    {
        return Bivector4(xy+b.xy, yz+b.yz, zw+b.zw, wx+b.wx, xz+b.xz, yw+b.yw);
    }

    template <typename T>
    Bivector4<T>&       Bivector4<T>::operator+=(const Bivector4<T>&b) noexcept
    {
        xy+=b.xy; yz+=b.yz; zw+=b.zw; wx+=b.wx; xz+=b.xz; yw+=b.yw;
        return *this;
    }

    #ifdef YQ_MATH_MULTIVECTOR4_HPP
    template <typename T>
    constexpr Multivector4<T> Bivector4<T>::operator+(const Multivector4<T>& b) const noexcept
    {
        return Multivector4<T>(
            b.a,
            b.x, b.y, b.z, b.w,
            xy+b.xy, yz+b.yz, zw+b.zw, wx+b.wx, xz+b.xz, yw+b.yw,
            b.xyz, b.yzw, b.zwx, b.wxy,
            b.xyzw
        );
    }
    #endif

    #if defined(YQ_MATH_MULTIVECTOR4_HPP) && defined(YQ_MATH_QUADVECTOR4_HPP)
    template <typename T>
    constexpr Multivector4<T> Bivector4<T>::operator+(const Quadvector4<T>& b) const noexcept
    {
        return Multivector4<T>(
            zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            xy, yz, zw, wx, xz, yw, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            b.xyzw
        );
    }
    #endif

    #if defined(YQ_MATH_MULTIVECTOR4_HPP) && defined(YQ_MATH_TRIVECTOR4_HPP)
    template <typename T>
    constexpr Multivector4<T> Bivector4<T>::operator+(const Trivector4<T>& b) const noexcept
    {
        return Multivector4<T>(
            zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            xy, yz, zw, wx, xz, yw, 
            b.xyz, b.yzw, b.zwx, b.wxy,
            zero_v<T> 
        );
    }
    #endif

    #if defined(YQ_MATH_MULTIVECTOR4_HPP) && defined(YQ_MATH_VECTOR_4_HPP)
    template <typename T>
    constexpr Multivector4<T> Bivector4<T>::operator+(const Vector4<T>& b) const noexcept
    {
        return Multivector4<T>(
            zero_v<T>, 
            b.x, b.y, b.z, b.w,
            xy, yz, zw, wx, xz, yw, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T> 
        );
    }
    #endif
    
    #ifdef YQ_MATH_MULTIVECTOR4_HPP
    template <typename T>
    constexpr Multivector4<T> Bivector4<T>::operator-(T b) const noexcept
    {
        return Multivector4<T>( 
            -b, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            xy, yz, zw, wx, xz, yw, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T> 
        );
    }
    #endif

    template <typename T>
    constexpr Bivector4<T> Bivector4<T>::operator-(const Bivector4<T>& b) const noexcept
    {
        return Bivector4(xy-b.xy, yz-b.yz, zw-b.zw, wx-b.wx, xz-b.xz, yw-b.yw);
    }

    template <typename T>
    Bivector4<T>&       Bivector4<T>::operator-=(const Bivector4<T>&b) noexcept
    {
        xy-=b.xy; yz-=b.yz; zw-=b.zw; wx-=b.wx; xz-=b.xz; yw-=b.yw;
        return *this;
    }

    #ifdef YQ_MATH_MULTIVECTOR4_HPP
    template <typename T>
    constexpr Multivector4<T> Bivector4<T>::operator-(const Multivector4<T>& b) const noexcept
    {
        return Multivector4<T>(
            -b.a,
            -b.x, -b.y, -b.z, -b.w,
            xy-b.xy, yz-b.yz, zw-b.zw, wx-b.wx, xz-b.xz, yw-b.yw,
            -b.xyz, -b.yzw, -b.zwx, -b.wxy,
            -b.xyzw
        );
    }
    #endif

    #if defined(YQ_MATH_MULTIVECTOR4_HPP) && defined(YQ_MATH_QUADVECTOR4_HPP)
    template <typename T>
    constexpr Multivector4<T> Bivector4<T>::operator-(const Quadvector4<T>& b) const noexcept
    {
        return Multivector4<T>(
            zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            xy, yz, zw, wx, xz, yw, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            -b.xyzw
        );
    }
    #endif

    #if defined(YQ_MATH_MULTIVECTOR4_HPP) && defined(YQ_MATH_TRIVECTOR4_HPP)
    template <typename T>
    constexpr Multivector4<T> Bivector4<T>::operator-(const Trivector4<T>& b) const noexcept
    {
        return Multivector4<T>(
            zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            xy, yz, zw, wx, xz, yw, 
            -b.xyz, -b.yzw, -b.zwx, -b.wxy,
            zero_v<T> 
        );
    }
    #endif

    #if defined(YQ_MATH_MULTIVECTOR4_HPP) && defined(YQ_MATH_VECTOR_4_HPP)
    template <typename T>
    constexpr Multivector4<T> Bivector4<T>::operator-(const Vector4<T>& b) const noexcept
    {
        return Multivector4<T>(
            zero_v<T>, 
            -b.x, -b.y, -b.z, -b.w,
            xy, yz, zw, wx, xz, yw, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T> 
        );
    }
    #endif
    
    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    constexpr Bivector4<product_t<T,U>> Bivector4<T>::operator*(U b) const noexcept
    {
        return Bivector4<product_t<T,U>>( xy*b, yz*b, zw*b, wx*b, xz*b, yw*b );
    }

    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
    Bivector4<T>& Bivector4<T>::operator*=(U b) noexcept
    {
        xy*=b, yz*=b, zw*=b, wx*=b, xz*=b, yw*=b;
        return *this;
    }

    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    constexpr Bivector4<quotient_t<T,U>> Bivector4<T>::operator/(U b) const noexcept
    {
        return Bivector4<quotient_t<T,U>>( xy/b, yz/b, zw/b, wx/b, xz/b, yw/b );
    }

    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_divide_v<T,U>)
    Bivector4<T>& Bivector4<T>::operator/=(U b) noexcept
    {
        xy/=b, yz/=b, zw/=b, wx/=b, xz/=b, yw/=b;
        return *this;
    }


    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    #ifdef YQ_MATH_MULTIVECTOR4_HPP
    template <typename T>
    constexpr Multivector4<T> operator+(T a, const Bivector4<T>& b) noexcept
    {
        return Multivector4<T>(
            a, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            b.xy, b.yz, b.zw, b.wx, b.xz, b.yw, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T> 
        );
    }
    #endif

    #ifdef YQ_MATH_MULTIVECTOR4_HPP
    template <typename T>
    constexpr Multivector4<T> operator-(T a, const Bivector4<T>& b) noexcept
    {
        return Multivector4<T>(
            a, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            -b.xy, -b.yz, -b.zw, -b.wx, -b.xz, -b.yw, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T> 
        );
    }
    #endif
    
    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Bivector4<product_t<T,U>> operator*(T a, const Bivector4<U>& b) noexcept
    {
        return Bivector4<product_t<T,U>>( a*b.xy, a*b.yz, a*b.zw, a*b.wx, a*b.xz, a*b.yw );
    }



}
