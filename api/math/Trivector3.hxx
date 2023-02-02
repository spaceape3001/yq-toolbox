////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the trivector3 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

namespace yq {
    template <typename T>
    constexpr Trivector3<T> Trivector3<T>::operator+() const noexcept
    {
        return *this;
    }

    template <typename T>
    constexpr Trivector3<T> Trivector3<T>::operator-() const noexcept
    {
        return Trivector3<T>(-xyz);
    }

    template <typename T>
    constexpr Multivector3<T> Trivector3<T>::operator+(T b) const noexcept
    {
        return Multivector3<T>(
            b, 
            zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, 
            xyz 
        );
    }    

    template <typename T>
    constexpr Trivector3<T> Trivector3<T>::operator+(const Trivector3<T>& b) const noexcept
    {
        return Trivector3<T>( xyz+b.xyz );
    }

    template <typename T>
    Trivector3<T>& Trivector3<T>::operator+=(const Trivector3<T>& b) noexcept
    {
        xyz+=b.xyz;
        return *this;
    }

    template <typename T>
    constexpr Multivector3<T> Trivector3<T>::operator+(const Bivector3<T>& b) const noexcept
    {
        return Multivector3<T>(
            zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>,
            b.xy, b.yz, b.zx,
            xyz 
        );
    }
    
    template <typename T>
    constexpr Multivector3<T> Trivector3<T>::operator+(const Multivector3<T>& b) const noexcept
    {
        return Multivector3<T>(
            b.a, 
            b.x, b.y, b.z,
            b.xy, b.yz, b.zx,
            xyz + b.xyz
        );
    }
    
    template <typename T>
    constexpr Multivector3<T> Trivector3<T>::operator+(const Vector3<T>& b) const noexcept
    {
        return Multivector3<T>(
            zero_v<T>, 
            b.x, b.y, b.z,
            zero_v<T>, zero_v<T>, zero_v<T>, 
            xyz 
        );
    }
    
    template <typename T>
    constexpr Multivector3<T> Trivector3<T>::operator-(T b) const noexcept
    {
        return Multivector3<T>(
            -b, 
            zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, 
            xyz 
        );
    }

    template <typename T>
    constexpr Trivector3<T> Trivector3<T>::operator-(const Trivector3<T>& b) const noexcept
    {
        return Trivector3( xyz-b.xyz );
    }

    template <typename T>
    Trivector3<T>& Trivector3<T>::operator-=(const Trivector3<T>& b) noexcept
    {
        xyz-=b.xyz;
        return *this;
    }


    template <typename T>
    constexpr Multivector3<T> Trivector3<T>::operator-(const Bivector3<T>& b) const noexcept
    {
        return Multivector3<T>(
            zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>,
            -b.xy, -b.yz, -b.zx,
            xyz 
        );
    }
    
    template <typename T>
    constexpr Multivector3<T> Trivector3<T>::operator-(const Multivector3<T>& b) const noexcept
    {
        return Multivector3<T>(
            -b.a, 
            -b.x, -b.y, -b.z,
            -b.xy, -b.yz, -b.zx,
            xyz - b.xyz
        );
    }
    


    template <typename T>
    constexpr Multivector3<T> Trivector3<T>::operator-(const Vector3<T>& b) const noexcept
    {
        return Multivector3<T>(
            zero_v<T>, 
            -b.x, -b.y, -b.z,
            zero_v<T>, zero_v<T>, zero_v<T>, 
            xyz 
        );
    }
    
    template <typename T>
        template <typename U>
    requires trait::is_arithmetic_v<T>
    constexpr Trivector3<product_t<T,U>> Trivector3<T>::operator*(U b) const noexcept
    {
        return Trivector3<product_t<T,U>>( xyz*b );
    }

    template <typename T>
        template <typename U>
    requires (trait::is_arithmetic_v<T> && trait::self_mul_v<T,U>)
    Trivector3<T>& Trivector3<T>::operator*=(U b) noexcept
    {
        xyz *= b;
        return *this;
    }

    template <typename T>
        template <typename U>
    requires trait::is_arithmetic_v<T>
    constexpr Trivector3<quotient_t<T,U>> Trivector3<T>::operator/(const U b) const noexcept
    {
        return Trivector3<quotient_t<T,U>>( xyz/b );
    }

    /*! \brief Self-scaling division of trivector
    
        This reduces the trivector (in place) with the right,
        returns reference to the trivector.
    */
    template <typename T>
        template <typename U>
    requires (trait::is_arithmetic_v<T> && trait::self_div_v<T,U>)
    constexpr Trivector3<T>& Trivector3<T>::operator/=(U b) noexcept
    {
        xyz /= b;
        return *this;
    }


    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


    template <typename T>
    constexpr Multivector3<T> operator+(T a, const Trivector3<T>& b) noexcept
    {
        return Multivector3<T>(
            a, 
            zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, 
            b.xyz
        );
    }

    template <typename T>
    constexpr Multivector3<T> operator-(T a, const Trivector3<T>& b) noexcept
    {
        return Multivector3<T>(
            a, 
            zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, 
            -b.xyz
        );
    }

    template <typename T, typename U>
    requires trait::is_arithmetic_v<T>
    constexpr Trivector3<product_t<T,U>> operator*(T a, const Trivector3<U>& b) noexcept
    {
        return Trivector3<product_t<T,U>>( a*b.xyz );
    }


}
