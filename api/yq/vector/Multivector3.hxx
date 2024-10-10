////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the multivector3 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <yq-toolbox/vector/Bivector3.hpp>
#include <yq-toolbox/vector/Multivector3.hpp>
#include <yq-toolbox/vector/Trivector3.hpp>
#include <yq-toolbox/vector/Vector3.hpp>


namespace yq {
    template <typename T>
    constexpr Multivector3<T> Multivector3<T>::operator+() const noexcept
    {
        return *this;
    }


    template <typename T>
    constexpr Multivector3<T> Multivector3<T>::operator-() const noexcept
    {
        return Multivector3(-a, -x, -y, -z, -xy, -yz, -zx, -xyz );
    }

    template <typename T>
    constexpr Multivector3<T> Multivector3<T>::operator+(T b) const noexcept
    {
        return Multivector3(
            a+b,
            x, y, z,
            xy, yz, zx, 
            xyz
        );
    }

    template <typename T>
    Multivector3<T>& Multivector3<T>::operator+=(T b) noexcept
    {
        a += b;
        return *this;
    }


    template <typename T>
    constexpr Multivector3<T> Multivector3<T>::operator+(const Bivector3<T>& b) const noexcept
    {
        return Multivector3(
            a,
            x, y, z, 
            xy+b.xy, yz+b.yz, zx+b.zx,
            xyz
        );
    }

    template <typename T>
    Multivector3<T>& Multivector3<T>::operator+=(const Bivector3<T>& b) noexcept
    {
        xy+=b.xy; yz+=b.yz; zx+=b.zx;
        return *this;
    }

    template <typename T>
    constexpr Multivector3<T> Multivector3<T>::operator+(const Multivector3<T>& b) const noexcept
    {
        return Multivector3(
            a+b.a,
            x+b.x, y+b.y, z+b.z,
            xy+b.xy, yz+b.yz, zx+b.zx,
            xyz+b.xyz
        );
    }

    template <typename T>
    Multivector3<T>& Multivector3<T>::operator+=(const Multivector3<T>& b) noexcept
    {
        a += b.a;
        x += b.x; y += b.y; z += b.z;
        xy+=b.xy; yz+=b.yz; zx+=b.zx;
        xyz += b.xyz;
        return *this;
    }

    template <typename T>
    constexpr Multivector3<T> Multivector3<T>::operator+(const Trivector3<T>& b) const noexcept
    {
        return Multivector3(
            a,
            x, y, z, 
            xy, yz, zx, 
            xyz+b.xyz
        );
    }

    template <typename T>
    Multivector3<T>& Multivector3<T>::operator+=(const Trivector3<T>& b) noexcept
    {
        xyz += b.xyz;
        return *this;
    }
    

    template <typename T>
    constexpr Multivector3<T> Multivector3<T>::operator+(const Vector3<T>&  b) const noexcept
    {
        return Multivector3(
            a,
            x+b.x, y+b.y, z+b.z,
            xy, yz, zx,
            xyz
        );
    }

    template <typename T>
    Multivector3<T>& Multivector3<T>::operator+=(const Vector3<T>& b) noexcept
    {
        x += b.x; y += b.y; z += b.z;
        return *this;
    }


    template <typename T>
    constexpr Multivector3<T> Multivector3<T>::operator-(const Bivector3<T>& b) const noexcept
    {
        return Multivector3(
            a,
            x, y, z, 
            xy-b.xy, yz-b.yz, zx-b.zx,
            xyz
        );
    }

    template <typename T>
    Multivector3<T>& Multivector3<T>::operator-=(const Bivector3<T>& b) noexcept
    {
        xy-=b.xy; yz-=b.yz; zx-=b.zx;
        return *this;
    }

    template <typename T>
    constexpr Multivector3<T> Multivector3<T>::operator-(const Multivector3<T>& b) const noexcept
    {
        return Multivector3(
            a-b.a,
            x-b.x, y-b.y, z-b.z,
            xy-b.xy, yz-b.yz, zx-b.zx,
            xyz-b.xyz
        );
    }

    template <typename T>
    Multivector3<T>& Multivector3<T>::operator-=(const Multivector3<T>& b) noexcept
    {
        a -= b.a;
        x -= b.x; y -= b.y; z -= b.z;
        xy-=b.xy; yz-=b.yz; zx-=b.zx;
        xyz -= b.xyz;
        return *this;
    }

    template <typename T>
    constexpr Multivector3<T> Multivector3<T>::operator-(const Trivector3<T>& b) const noexcept
    {
        return Multivector3(
            a,
            x, y, z, 
            xy, yz, zx, 
            xyz-b.xyz
        );
    }

    template <typename T>
    Multivector3<T>& Multivector3<T>::operator-=(const Trivector3<T>& b) noexcept
    {
        xyz -= b.xyz;
        return *this;
    }
    
    template <typename T>
    constexpr Multivector3<T> Multivector3<T>::operator-(T b) const noexcept
    {
        return Multivector3(
            a-b,
            x, y, z,
            xy, yz, zx, 
            xyz
        );
    }

    template <typename T>
    Multivector3<T>& Multivector3<T>::operator-=(T b) noexcept
    {
        a -= b;
        return *this;
    }

    template <typename T>
    constexpr Multivector3<T> Multivector3<T>::operator-(const Vector3<T>& b) const noexcept
    {
        return Multivector3(
            a,
            x-b.x, y-b.y, z-b.z,
            xy, yz, zx,
            xyz
        );
    }

    template <typename T>
    Multivector3<T>& Multivector3<T>::operator-=(const Vector3<T>& b) noexcept
    {
        x -= b.x; y -= b.y; z -= b.z;
        return *this;
    }
    

    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    constexpr Multivector3<product_t<T,U>> Multivector3<T>::operator*(U b) const noexcept
    {
        return Multivector3<product_t<T,U>>(
            a*b, 
            x*b, y*b, z*b,
            xy*b, yz*b, zx*b,
            xyz*b
        );
    }

    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
    Multivector3<T>& Multivector3<T>::operator*=(U b) noexcept
    {
        a  *=b; 
        x  *=b; y *=b; z *=b;
        xy *=b; yz*=b; zx*=b;
        xyz*=b;
        return *this;
    }



    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    constexpr Multivector3<quotient_t<T,U>> Multivector3<T>::operator/(U b) const noexcept
    {
        return Multivector3<quotient_t<T,U>>(
            a/b, 
            x/b, y/b, z/b,
            xy/b, yz/b, zx/b,
            xyz/b
        );
    }

    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_divide_v<T,U>)
    Multivector3<T>& Multivector3<T>::operator/=(U b) noexcept
    {
        a  /=b; 
        x  /=b; y /=b; z /=b;
        xy /=b; yz/=b; zx/=b;
        xyz/=b;
        return *this;
    }
    

    template <typename T>
    constexpr Bivector3<T> Multivector3<T>::bivector() const noexcept
    {
        return Bivector3<T>( xy, yz, zx );
    }

    template <typename T>
    constexpr Trivector3<T> Multivector3<T>::trivector() const noexcept
    {
        return Trivector3<T>( xyz );
    }

    template <typename T>
    constexpr Vector3<T> Multivector3<T>::vector() const noexcept
    {
        return Vector3<T>( x, y, z );
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


    template <typename T>
    constexpr Multivector3<T> operator+(T a, const Multivector3<T>& b) noexcept
    {
        return Multivector3<T>(
            a+b.a, 
            b.x, b.y, b.z,
            b.xy, b.yz, b.zx,
            b.xyz
        );
    }

    template <typename T>
    constexpr Multivector3<T> operator-(T a, const Multivector3<T>& b) noexcept
    {
        return Multivector3<T>(
            a-b.a, 
            -b.x, -b.y, -b.z,
            -b.xy, -b.yz, -b.zx,
            -b.xyz
        );
    }

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Multivector3<product_t<T,U>> operator*(T a, const Multivector3<U>&b) noexcept
    {
        return Multivector3<product_t<T,U>>(
            a*b.a, 
            a*b.x, a*b.y, a*b.z,
            a*b.xy, a*b.yz, a*b.zx,
            a*b.xyz
        );
    }


    template <typename T>
    constexpr Bivector3<T> bivector(const Multivector3<T>& a) noexcept
    {
        return a.bivector();
    }

    template <typename T>
    constexpr Trivector3<T> trivector(const Multivector3<T>& a) noexcept
    {
        return a.trivector();
    }

    template <typename T>
    constexpr Vector3<T> vector(const Multivector3<T>& a) noexcept
    {
        return a.vector();
    }
}
