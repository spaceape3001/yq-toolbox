////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/Bivector3.hpp>
#include <math/Multivector3.hpp>
#include <math/Trivector3.hpp>
#include <math/Vector3.hpp>

/* 
    This is the template IMPLEMENTATION of the bivector3 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

namespace yq {
    template <typename T>
    constexpr Bivector3<T> Bivector3<T>::operator+() const noexcept
    {
        return *this;
    }

    template <typename T>
    constexpr Bivector3<T> Bivector3<T>::operator-() const noexcept
    {
        return Bivector3(-xy, -yz, -zx);
    }

    template <typename T>
    constexpr Multivector3<T> Bivector3<T>::operator+(T  b) const noexcept
    {
        return Multivector3<T>(
            b, 
            zero_v<T>, zero_v<T>, zero_v<T>, 
            xy, yz, zx, 
            zero_v<T> 
        );
    }



    template <typename T>
    constexpr Bivector3<T> Bivector3<T>::operator+(const Bivector3<T>& b) const noexcept
    {
        return Bivector3(xy+b.xy, yz+b.yz, zx+b.zx);
    }

    template <typename T>
    Bivector3<T>&       Bivector3<T>::operator+=(const Bivector3<T>&b) noexcept
    {
        xy+=b.xy; yz+=b.yz; zx+=b.zx;
        return *this;
    }


    template <typename T>
    constexpr Multivector3<T> Bivector3<T>::operator+(const Multivector3<T>& b) const noexcept
    {
        return Multivector3<T>(
            b.a, 
            b.x, b.y, b.z,
            xy+b.xy, yz+b.yz, zx+b.zx,
            b.xyz
        );
    }

    template <typename T>
    constexpr Multivector3<T> Bivector3<T>::operator+(const Trivector3<T>& b) const noexcept
    {
        return Multivector3<T>(
            zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, 
            xy, yz, zx, 
            b.xyz
        );
    }

    template <typename T>
    constexpr Multivector3<T> Bivector3<T>::operator+(const Vector3<T>& b) const noexcept
    {
        return Multivector3<T>(
            zero_v<T>, 
            b.x, b.y, b.z, 
            xy, yz, zx, 
            zero_v<T> 
        );
    }

    template <typename T>
    constexpr Multivector3<T> Bivector3<T>::operator-(T b) const noexcept
    {
        return Multivector3<T>(
            -b, 
            zero_v<T>, zero_v<T>, zero_v<T>, 
            xy, yz, zx, 
            zero_v<T> 
        );
    }

    template <typename T>
    constexpr Bivector3<T> Bivector3<T>::operator-(const Bivector3<T>& b) const noexcept
    {
        return Bivector3( xy-b.xy, yz-b.yz, zx-b.zx );
    }

    template <typename T>
    Bivector3<T>&       Bivector3<T>::operator-=(const Bivector3<T>&b) noexcept
    {
        xy-=b.xy; yz-=b.yz; zx-=b.zx;
        return *this;
    }


    template <typename T>
    constexpr Multivector3<T> Bivector3<T>::operator-(const Multivector3<T>& b) const noexcept
    {
        return Multivector3<T>(
            -b.a, 
            -b.x, -b.y, -b.z,
            xy-b.xy, yz-b.yz, zx-b.zx,
            -b.xyz
        );
    }

    template <typename T>
    constexpr Multivector3<T> Bivector3<T>::operator-(const Trivector3<T>& b) const noexcept
    {
        return Multivector3<T>(
            zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, 
            xy, yz, zx, 
            -b.xyz
        );
    }


    template <typename T>
    constexpr Multivector3<T> Bivector3<T>::operator-(const Vector3<T>& b) const noexcept
    {
        return Multivector3<T>(
            zero_v<T>, 
            -b.x, -b.y, -b.z, 
            xy, yz, zx, 
            zero_v<T> 
        );
    }


    template <typename T>
        template <typename U>
    requires trait::is_arithmetic_v<U>
    Bivector3<product_t<T,U>> Bivector3<T>::operator*(U b) const noexcept
    {
        return Bivector3<product_t<T,U>>( xy*b, yz*b, zx*b );
    }

    template <typename T>
        template <typename U>
    requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Bivector3<product_t<T,U>>& Bivector3<T>::operator*=(U b) noexcept
    {
        xy*=b, yz*=b, zx*=b;
        return *this;
    }

    /*! \brief Scaling division operator
    
        \note currently limited to floating points due to uncertainty 
    */
    template <typename T>
        template <typename U>
    requires trait::is_arithmetic_v<T>
    Bivector3<quotient_t<T,U>> Bivector3<T>::operator/(U b) const noexcept
    {
        return Bivector3<quotient_t<T,U>>( xy/b, yz/b, zx/b );
    }

    /*! \brief Self-scaling division operator
    
        \note currently limited to floating points due to uncertainty 
    */
    template <typename T>
        template <typename U>
    requires (trait::is_arithmetic_v<T> && trait::self_div_v<T,U>)
    Bivector3<T>& Bivector3<T>::operator/=(U b) noexcept
    {
        xy/=b, yz/=b, zx/=b;
        return *this;
    }


    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename T>
    constexpr Multivector3<T> operator+(T a, const Bivector3<T>& b) noexcept
    {
        return Multivector3<T>(
            a, 
            zero_v<T>, zero_v<T>, zero_v<T>, 
            b.xy, b.yz, b.zx, 
            zero_v<T> 
        );
    }

    template <typename T>
    constexpr Multivector3<T> operator-(T a, const Bivector3<T>& b) noexcept
    {
        return Multivector3<T>(
            a, 
            zero_v<T>, zero_v<T>, zero_v<T>, 
            -b.xy, -b.yz, -b.zx, 
            zero_v<T> 
        );
    }

    template <typename T, typename U>
    requires trait::is_arithmetic_v<T>
    Bivector3<product_t<T,U>> operator*(T a, const Bivector3<U>& b) noexcept
    {
        return Bivector3<product_t<T,U>>( a*b.xy, a*b.yz, a*b.zx );
    }






}
