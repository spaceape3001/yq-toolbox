////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the vector3 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include "Bivector3.hpp"
#include "Multivector3.hpp"
#include "Trivector3.hpp"

#include "Vector1.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"

namespace yq {
    template <typename T>
    constexpr Vector3<T>::operator glm::vec<3, T, glm::defaultp>() const noexcept
    {
        return glm::vec<3, T, glm::defaultp>( x, y, z );
    }

    template <typename T>
    constexpr Vector3<T> Vector3<T>::operator-() const noexcept
    {
        return Vector3(-x,-y,-z);
    }

    template <typename T>
    Vector3<quotient_t<T,T>> Vector3<T>::operator~() const
    {
        auto l = one_v<T>/length();
        return Vector3<quotient_t<T,T>>(x*l, y*l, z*l);
    }

    template <typename T>
    constexpr square_t<T> Vector3<T>::operator^(two_t) const noexcept
    {
        return x*x + y*y + z*z;
    }    

    template <typename T>
    constexpr Multivector3<T> Vector3<T>::operator+(T b) const noexcept
    {
        return { 
            b, 
            x, y, z,
            {}, {}, {}, 
            {} 
        };
    }

    template <typename T>
    constexpr Multivector3<T> Vector3<T>::operator+(const Bivector3<T>& b) const noexcept
    {
        return { 
            {}, 
            x, y, z,
            b.xy, b.yz, b.zx,
            {} 
        };
    }

    template <typename T>
    constexpr Multivector3<T> Vector3<T>::operator+(const Multivector3<T>& b) const noexcept
    {
        return { 
            b.a, 
            x+b.x, y+b.y, z+b.z, 
            b.xy, b.yz, b.zx,
            b.xyz
        };
    }

    template <typename T>
    constexpr Multivector3<T> Vector3<T>::operator+(const Trivector3<T>& b) const noexcept
    {
        return { 
            {}, 
            x, y, z,
            {}, {}, {}, 
            b.xyz
        };
    }
    
    template <typename T>
    constexpr Vector3<T> Vector3<T>::operator+(const Vector3& b) const noexcept
    {
        return Vector3(x+b.x, y+b.y, z+b.z);
    }

    template <typename T>
    Vector3<T>& Vector3<T>::operator+=(const Vector3& b) noexcept
    {
        x += b.x;
        y += b.y;
        z += b.z;
        return *this;
    }
    
    template <typename T>
    constexpr Multivector3<T> Vector3<T>::operator-(const Bivector3<T>& b) const noexcept
    {
        return { 
            {}, 
            x, y, z,
            -b.xy, -b.yz, -b.zx,
            {} 
        };
    }

    template <typename T>
    constexpr Multivector3<T> Vector3<T>::operator-(const Multivector3<T>& b) const noexcept
    {
        return { 
            -b.a, 
            x-b.x, y-b.y, z-b.z, 
            -b.xy, -b.yz, -b.zx,
            -b.xyz
        };
    }

    template <typename T>
    constexpr Multivector3<T> Vector3<T>::operator-(const Trivector3<T>& b) const noexcept
    {
        return { 
            {}, 
            x, y, z,
            {}, {}, {}, 
            -b.xyz
        };
    }

    template <typename T>
    constexpr Multivector3<T> Vector3<T>::operator-(T b) const noexcept
    {
        return { 
            -b, 
            x, y, z,
            {}, {}, {}, 
            {} 
        };
    }

    template <typename T>
    constexpr Vector3<T> Vector3<T>::operator-(const Vector3& b) const noexcept
    {
        return Vector3(x-b.x, y-b.y, z-b.z);
    }

    template <typename T>
    Vector3<T>& Vector3<T>::operator-=(const Vector3& b) noexcept
    {
        x -= b.x;
        y -= b.y;
        z -= b.z;
        return *this;
    }

    template <typename T>
        template <typename U>
    requires (trait::is_arithmetic_v<U>)
    constexpr Vector3<product_t<T,U>> Vector3<T>::operator*(U b) const noexcept
    {
        return Vector3<product_t<T,U>>(x*b, y*b, z*b);
    }

    template <typename T>
        template <typename U>
    requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Vector3<T>& Vector3<T>::operator*=(U b) noexcept
    {
        x *= b;
        y *= b;
        z *= b;
        return *this;
    }

    template <typename T>
        template <typename U>
    constexpr product_t<T,U> Vector3<T>::operator DOT (const Vector3<U>&b) const noexcept
    {
        return x*b.x + y*b.y + z*b.z;
    }


    template <typename T>
        template <typename U>
    constexpr product_t<T,U> Vector3<T>::operator INNER (const Vector3<U>&b) const noexcept
    {
        return x*b.x + y*b.y + z*b.z;
    }

    template <typename T>
        template <typename U>
    constexpr Vector3<product_t<T,U>> Vector3<T>::operator CROSS (const Vector3<U>&b) const noexcept
    {
        return Vector3<product_t<T,U>>(
            y*b.z-z*b.y, 
            z*b.x-x*b.z, 
            x*b.y-y*b.x 
        );
    }

    template <typename T>
        template <typename U>
    constexpr Bivector3<product_t<T,U>> Vector3<T>::operator OUTER (const Vector3<U>& b) noexcept
    {
        return { x*b.y-y*b.x, y*b.z-z*b.y, z*b.x-x*b.z };
    }

    template <typename T>
        template <typename U>
    requires (std::is_arithmetic_v<U>)
    constexpr  Vector3<quotient_t<T,U>> Vector3<T>::operator/(U b) const noexcept
    {
        return Vector3<quotient_t<T,U>>(x / b, y / b, z / b);
    }

    template <typename T>
        template <typename U>
    requires (std::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Vector3<T>& Vector3<T>::operator/=(U b) noexcept
    {
        x /= b;
        y /= b;
        z /= b;
        return *this;
    }

    template <typename T>
    constexpr Vector3<T> Vector3<T>::all_add(T b) const noexcept
    {
        return { x+b, y+b, z+b };
    }
    
    template <typename T>
    constexpr Vector3<T> Vector3<T>::all_subtract(T b) const noexcept
    {
        return { x-b, y-b, z-b };
    }
    
    template <typename T>
    constexpr T Vector3<T>::cmax() const noexcept
    {
        return max(max(x, y), z);
    }

    template <typename T>
    constexpr T Vector3<T>::cmin() const noexcept
    {
        return min(min(x, y), z);
    }

    template <typename T>
    constexpr cube_t<T>     Vector3<T>::cproduct() const noexcept
    {
        return x*y*z;
    }
    
    template <typename T>
    constexpr T   Vector3<T>::csum() const noexcept
    {
        return x + y + z;
    }
    
    template <typename T>
    constexpr Vector3<T>   Vector3<T>::eabs() const noexcept
    {
        return { abs(x), abs(y), abs(z) };
    }

    template <typename T>
        template <typename U>
    constexpr Vector3<quotient_t<T,U>>    Vector3<T>::ediv(const Vector3<U>&b) const noexcept
    {
        return {x/b.x, y/b.y, z/b.z};
    }

    template <typename T>
    constexpr Vector3<T>   Vector3<T>::emax(const Vector3&b) const noexcept
    {
        return {max(x, b.x), max(y, b.y), max(z, b.z)};
    }

    template <typename T>
    constexpr Vector3<T>   Vector3<T>::emin(const Vector3&b) const noexcept
    {
        return {min(x, b.x), min(y, b.y), min(z, b.z)};
    }    

    template <typename T>
        template <typename U>
    constexpr Vector3<product_t<T,U>>    Vector3<T>::emul(const Vector3<U>&b) const noexcept
    {
        return {x*b.x, y*b.y, z*b.z};
    }

    template <typename T>
    constexpr square_t<T> Vector3<T>::length²() const noexcept
    {
        return x*x + y*y + z*z;
    }    
    
    template <typename T>
    T       Vector3<T>::length() const
    {
        if constexpr (trait::has_sqrt_v<square_t<T>>)
            return sqrt(length²());
        return {};
    }
}
