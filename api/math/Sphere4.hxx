////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the sphere4 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <math/AxBox4.hpp>
#include <math/Sphere4.hpp>

namespace yq {
    template <typename T>
    constexpr Sphere4<T> Sphere4<T>::operator+() const noexcept
    {
        return Sphere4<T>(point, radius);
    }
    
    template <typename T>
    constexpr Sphere4<T> Sphere4<T>::operator-() const noexcept
    {
        return Sphere4<T>(-point, -radius);
    }

    template <typename T>
    constexpr Sphere4<T>   Sphere4<T>::operator+(const Vector4<T>&b) const noexcept
    {
        return Sphere4<T>(point+b, radius);
    }

    template <typename T>
    Sphere4<T>&            Sphere4<T>::operator+=(const Vector4<T>&b) noexcept
    {
        point += b;
        return *this;
    }

    template <typename T>
    constexpr Sphere4<T>   Sphere4<T>::operator-(const Vector4<T>&b) const noexcept
    {
        return Sphere4<T>(point-b,radius);
    }

    template <typename T>
    Sphere4<T>&            Sphere4<T>::operator-=(const Vector4<T>&b) noexcept
    {
        point -= b;
        return *this;
    }
    
    template <typename T>
        template <typename U>
    requires trait::is_arithmetic_v<U>
    Sphere4<trait::product_t<T,U>> Sphere4<T>::operator*(U b) const noexcept
    {
        return Sphere4<trait::product_t<T,U>>( point*b, radius*positive(b));
    }
    
    template <typename T>
        template <typename U>
    requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Sphere4<T>& Sphere4<T>::operator*=(U b) noexcept
    {
        point  *= b;
        radius *= positive(b);
        return *this;
    }
        
    template <typename T>
        template <typename U>
    requires trait::is_arithmetic_v<U>
    Sphere4<trait::quotient_t<T,U>> Sphere4<T>::operator/(U b) const noexcept
    {
        return Sphere4<trait::quotient_t<T,U>>( point/b, radius/positive(b));
    }
    
    template <typename T>
        template <typename U>
    requires (trait::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Sphere4<T>& Sphere4<T>::operator/=(U b) noexcept
    {
        point  /= b;
        radius /= positive(b);
        return *this;
    }


    template <typename T>
    constexpr AxBox4<T>   Sphere4<T>::bounds() const noexcept
    {
        T       r   = abs(radius);
        return { all(point) - r, all(point) + r };
    }

    template <typename T>
    constexpr T     Sphere4<T>::diameter() const noexcept
    {
        return radius + radius;
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename T, typename U>
    requires trait::is_arithmetic_v<T>
    Sphere4<trait::product_t<T,U>> operator*(T a, const Sphere4<U>& b)
    {
        return Sphere4<trait::product_t<T,U>>(a*b.point, positive(a)*b.radius);
    }

    //! Returns the axially aligned box of a sphere
    template <typename T>
    AxBox4<T>   aabb(const Sphere4<T>& sph)
    {
        return sph.bounds();
    }

    /*! \brief Computes the diameter of a hyper sphere
    */
    template <typename T>
    constexpr T  diameter(const Sphere4<T>& sph) noexcept
    {   
        return sph.diameter();
    }

}
