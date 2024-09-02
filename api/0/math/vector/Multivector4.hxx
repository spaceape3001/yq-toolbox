////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/math/vector/Multivector4.hpp>

/* 
    This is the template IMPLEMENTATION of the multivector4 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

namespace yq {

    template <typename T>
    constexpr Multivector4<T> Multivector4<T>::operator+() const noexcept
    {
        return *this;
    }

    template <typename T>
    constexpr Multivector4<T> Multivector4<T>::operator-() const noexcept
    {
        return Multivector4<T>(
            -a, 
            -x, -y, -z, -w,
            -xy, -yz, -zw, -wx, -xz, -yw,
            -xyz, -yzw, -zwx, -wxy, 
            -xyzw
        );
    }

    template <typename T>
    constexpr Multivector4<T> Multivector4<T>::operator+(T b) const noexcept
    {
        return Multivector4<T>(
            a+b,
            x, y, z, w,
            xy, yz, zw, wx, xz, yw, 
            xyz, yzw, zwx, wxy, 
            xyzw
        );
    }
    
    template <typename T>
    Multivector4<T>& Multivector4<T>::operator+=(T b) noexcept
    {
        a += b;
        return *this;
    }


    template <typename T>
    constexpr Multivector4<T> Multivector4<T>::operator+(const Bivector4<T>& b) const noexcept
    {
        return Multivector4<T>(
            a,
            x, y, z, w, 
            xy+b.xy, yz+b.yz, zw+b.zw, wx+b.wx, xz+b.xz, yw+b.yw,
            xyz, yzw, zwx, wxy, 
            xyzw
        );
    }

    template <typename T>
    Multivector4<T>& Multivector4<T>::operator+=(const Bivector4<T>& b) noexcept
    {
        xy+=b.xy; yz+=b.yz; zw+=b.zw; wx+=b.wx; xz+=b.xz; yw+=b.yw;
        return *this;
    }
    
    template <typename T>
    constexpr Multivector4<T> Multivector4<T>::operator+(const Multivector4<T>& b) const noexcept
    {
        return Multivector4<T>(
            a+b.a,
            x+b.x, y+b.y, z+b.z, w+b.w,
            xy+b.xy, yz+b.yz, zw+b.zw, wx+b.wx, xz+b.xz, yw+b.yw,
            xyz+b.xyz, yzw+b.yzw, zwx+b.zwx, wxy+b.wxy,
            xyzw+b.xyzw
        );
    }

    template <typename T>
    Multivector4<T>& Multivector4<T>::operator+=(const Multivector4<T>& b) noexcept
    {
        a += b.a;
        x += b.x; y += b.y; z += b.z; w += b.w;
        xy += b.xy; yz += b.yz; zw += b.zw; wx += b.wx; xz += b.xz; yw += b.yw;
        xyz += b.xyz; yzw += b.yzw; zwx += b.zwx; wxy += b.wxy;
        xyzw += b.xyzw;
        return *this;
    }

    template <typename T>
    constexpr Multivector4<T> Multivector4<T>::operator+(const Quadvector4<T>& b) const noexcept
    {
        return Multivector4<T>(
            a,
            x, y, z, w, 
            xy, yz, zw, wx, xz, yw, 
            xyz, yzw, zwx, wxy, 
            xyzw+b.xyzw
        );
    }

    template <typename T>
    Multivector4<T>& Multivector4<T>::operator+=(const Quadvector4<T>& b) noexcept
    {
        xyzw += b.xyzw;
        return *this;
    }
    
    template <typename T>
    constexpr Multivector4<T> Multivector4<T>::operator+(const Trivector4<T>& b) const noexcept
    {
        return Multivector4<T>(
            a,
            x, y, z, w, 
            xy, yz, zw, wx, xz, yw, 
            xyz+b.xyz, yzw+b.yzw, zwx+b.zwx, wxy+b.wxy,
            xyzw
        );
    }

    template <typename T>
    Multivector4<T>& Multivector4<T>::operator+=(const Trivector4<T>& b) noexcept
    {
        xyz+=b.xyz; yzw+=b.yzw; zwx+=b.zwx; wxy+=b.wxy;
        return *this;
    }
    

    template <typename T>
    constexpr Multivector4<T> Multivector4<T>::operator+(const Vector4<T>&  b) const noexcept
    {
        return Multivector4<T>(
            a,
            x+b.x, y+b.y, z+b.z, w+b.w,
            xy, yz, zw, wx, xz, yw, 
            xyz, yzw, zwx, wxy, 
            xyzw
        );
    }

    template <typename T>
    Multivector4<T>& Multivector4<T>::operator+=(const Vector4<T>& b) noexcept
    {
        x += b.x; y += b.y; z += b.z; w += b.w;
        return *this;
    }
    
    template <typename T>
    constexpr Multivector4<T> Multivector4<T>::operator-(T b) const noexcept
    {
        return Multivector4<T>(
            a-b,
            x, y, z, w,
            xy, yz, zw, wx, xz, yw, 
            xyz, yzw, zwx, wxy, 
            xyzw
        );
    }

    template <typename T>
    Multivector4<T>& Multivector4<T>::operator-=(T b) noexcept
    {
        a -= b;
        return *this;
    }
    
    template <typename T>
    constexpr Multivector4<T> Multivector4<T>::operator-(const Bivector4<T>& b) const noexcept
    {
        return Multivector4<T>(
            a,
            x, y, z, w, 
            xy-b.xy, yz-b.yz, zw-b.zw, wx-b.wx, xz-b.xz, yw-b.yw,
            xyz, yzw, zwx, wxy, 
            xyzw
        );
    }

    template <typename T>
    Multivector4<T>& Multivector4<T>::operator-=(const Bivector4<T>& b) noexcept
    {
        xy-=b.xy; yz-=b.yz; zw-=b.zw; wx-=b.wx; xz-=b.xz; yw-=b.yw;
        return *this;
    }
    
    template <typename T>
    constexpr Multivector4<T> Multivector4<T>::operator-(const Multivector4<T>& b) const noexcept
    {
        return Multivector4<T>(
            a-b.a,
            x-b.x, y-b.y, z-b.z, w-b.w,
            xy-b.xy, yz-b.yz, zw-b.zw, wx-b.wx, xz-b.xz, yw-b.yw,
            xyz-b.xyz, yzw-b.yzw, zwx-b.zwx, wxy-b.wxy,
            xyzw-b.xyzw
        );
    }

    template <typename T>
    Multivector4<T>& Multivector4<T>::operator-=(const Multivector4<T>& b) noexcept
    {
        a -= b.a;
        x -= b.x; y -= b.y; z -= b.z; w -= b.w;
        xy -= b.xy; yz -= b.yz; zw -= b.zw; wx -= b.wx; xz -= b.xz; yw -= b.yw;
        xyz -= b.xyz; yzw -= b.yzw; zwx -= b.zwx; wxy -= b.wxy;
        xyzw -= b.xyzw;
        return *this;
    }

    template <typename T>
    constexpr Multivector4<T> Multivector4<T>::operator-(const Quadvector4<T>& b) const noexcept
    {
        return Multivector4<T>(
            a,
            x, y, z, w, 
            xy, yz, zw, wx, xz, yw, 
            xyz, yzw, zwx, wxy, 
            xyzw-b.xyzw
        );
    }

    template <typename T>
    Multivector4<T>& Multivector4<T>::operator-=(const Quadvector4<T>& b) noexcept
    {
        xyzw -= b.xyzw;
        return *this;
    }
    
    template <typename T>
    constexpr Multivector4<T> Multivector4<T>::operator-(const Trivector4<T>& b) const noexcept
    {
        return Multivector4<T>(
            a,
            x, y, z, w, 
            xy, yz, zw, wx, xz, yw, 
            xyz-b.xyz, yzw-b.yzw, zwx-b.zwx, wxy-b.wxy,
            xyzw
        );
    }

    template <typename T>
    Multivector4<T>& Multivector4<T>::operator-=(const Trivector4<T>& b) noexcept
    {
        xyz-=b.xyz; yzw-=b.yzw; zwx-=b.zwx; wxy-=b.wxy;
        return *this;
    }
        

    template <typename T>
    constexpr Multivector4<T> Multivector4<T>::operator-(const Vector4<T>& b) const noexcept
    {
        return Multivector4<T>(
            a,
            x-b.x, y-b.y, z-b.z, w-b.w,
            xy, yz, zw, wx, xz, yw, 
            xyz, yzw, zwx, wxy, 
            xyzw
        );
    }

    template <typename T>
    Multivector4<T>& Multivector4<T>::operator-=(const Vector4<T>& b) noexcept
    {
        x -= b.x; y -= b.y; z -= b.z; w -= b.w;
        return *this;
    }

    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    constexpr Multivector4<product_t<T,U>> Multivector4<T>::operator*(U b) const noexcept
    {
        return Multivector4<product_t<T,U>>(
            a*b, 
            x*b, y*b, z*b, w*b,
            xy*b, yz*b, zw*b, wx*b, xz*b, yw*b,
            xyz*b, yzw*b, zwx*b, wxy*b,
            xyzw*b
        );
    }

    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
    Multivector4<T>& Multivector4<T>::operator*=(U b) noexcept
    {
        a   *=b; 
        x   *=b; y  *=b; z  *=b; w  *=b;
        xy  *=b; yz *=b; zw *=b; wx *=b; xz *=b; yw *=b;
        xyz *=b; yzw*=b; zwx*=b; wxy*=b;
        xyzw*=b;
        return *this;
    }

    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    constexpr Multivector4<quotient_t<T,U>> Multivector4<T>::operator/(U b) const noexcept
    {
        return Multivector4<quotient_t<T,U>>(
            a/b, 
            x/b, y/b, z/b, w/b,
            xy/b, yz/b, zw/b, wx/b, xz/b, yw/b,
            xyz/b, yzw/b, zwx/b, wxy/b,
            xyzw/b
        );
    }

    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_divide_v<T,U>)
    Multivector4<T>& Multivector4<T>::operator/=(U b) noexcept
    {
        a   /=b; 
        x   /=b; y  /=b; z  /=b; w  /=b;
        xy  /=b; yz /=b; zw /=b; wx /=b; xz /=b; yw /=b;
        xyz /=b; yzw/=b; zwx/=b; wxy/=b;
        xyzw/=b;
        return *this;
    }

    
    template <typename T>
    constexpr Bivector4<T> Multivector4<T>::bivector() const noexcept
    {
        return { xy, yz, zw, wx, xz, yw };
    }

    template <typename T>
    constexpr Quadvector4<T> Multivector4<T>::quadvector() const noexcept
    {
        return { xyzw };
    }

    template <typename T>
    constexpr Trivector4<T> Multivector4<T>::trivector() const noexcept
    {
        return { xyz, yzw, zwx, wxy };
    }

    template <typename T>
    constexpr Vector4<T> Multivector4<T>::vector() const noexcept
    {
        return { x, y, z, w };
    }


    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename T>
    constexpr Multivector4<T> operator+(T a, const Multivector4<T>& b) noexcept
    {
        return Multivector4<T>(
            a+b.a, 
            b.x, b.y, b.z, b.w,
            b.xy, b.yz, b.zw, b.wx, b.xz, b.yw,
            b.xyz, b.yzw, b.zwx, b.wxy,
            b.xyzw
        );
    }

    template <typename T>
    constexpr Multivector4<T> operator-(T a, const Multivector4<T>& b) noexcept
    {
        return Multivector4<T>(
            a-b.a, 
            -b.x, -b.y, -b.z, -b.w,
            -b.xy, -b.yz, -b.zw, -b.wx, -b.xz, -b.yw,
            -b.xyz, -b.yzw, -b.zwx, -b.wxy,
            -b.xyzw
        );
    }

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Multivector4<product_t<T,U>> operator*(T a, const Multivector4<U>&b) noexcept
    {
        return Multivector4<product_t<T,U>>(
            a*b.a, 
            a*b.x, a*b.y, a*b.z, a*b.w,
            a*b.xy, a*b.yz, a*b.zw, a*b.wx, a*b.xz, a*b.yw,
            a*b.xyz, a*b.yzw, a*b.zwx, a*b.wxy,
            a*b.xyzw
        );
    }



    template <typename T>
    constexpr Bivector4<T> bivector(const Multivector4<T>& a) noexcept
    {
        return a.bivector();
    }

    template <typename T>
    constexpr Quadvector4<T> quadvector(const Multivector4<T>& a) noexcept
    {
        return a.quadvector();
    }

    template <typename T>
    constexpr Trivector4<T> trivector(const Multivector4<T>& a) noexcept
    {
        return a.trivector();
    }

    template <typename T>
    constexpr Vector4<T> vector(const Multivector4<T>& a) noexcept
    {
        return a.vector();
    }
}
