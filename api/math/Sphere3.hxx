////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the sphere3 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <math/AxBox3.hpp>
#include <math/Sphere3.hpp>

namespace yq {
    template <typename T>
    Sphere3<T>::Sphere3(focus_t, const Vector3<T>& focus, const Vector3<T>& edge) : 
        Sphere3(focus, (edge-focus).length()) {}

    template <typename T>
    Sphere3<T>::Sphere3(opposite_t, const Vector3<T>&a, const Vector3<T>&b) : 
        Sphere3(middivide(a,b), middivide((a-b).length())) {}

    template <typename T>
    constexpr Sphere3<T> Sphere3<T>::operator+() const noexcept
    {
        return Sphere3<T>(point, radius);
    }
    
    template <typename T>
    constexpr Sphere3<T> Sphere3<T>::operator-() const noexcept
    {
        return Sphere3<T>(-point, -radius);
    }

    template <typename T>
    constexpr Sphere3<T>   Sphere3<T>::operator+(const Vector3<T>&b) const noexcept
    {
        return Sphere3<T>(point+b, radius);
    }

    template <typename T>
    Sphere3<T>&            Sphere3<T>::operator+=(const Vector3<T>&b) noexcept
    {
        point += b;
        return *this;
    }

    template <typename T>
    constexpr Sphere3<T>   Sphere3<T>::operator-(const Vector3<T>&b) const noexcept
    {
        return Sphere3<T>(point-b,radius);
    }

    template <typename T>
    Sphere3<T>&            Sphere3<T>::operator-=(const Vector3<T>&b) noexcept
    {
        point -= b;
        return *this;
    }
    
    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    Sphere3<product_t<T,U>> Sphere3<T>::operator*(U b) const noexcept
    {
        return Sphere3<product_t<T,U>>( point*b, radius*positive(b));
    }
    
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_mul_v<T,U>)
    Sphere3<T>& Sphere3<T>::operator*=(U b) noexcept
    {
        point  *= b;
        radius *= positive(b);
        return *this;
    }
        
    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    Sphere3<quotient_t<T,U>> Sphere3<T>::operator/(U b) const noexcept
    {
        return Sphere3<quotient_t<T,U>>( point/b, radius/positive(b));
    }
    
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_div_v<T,U>)
    Sphere3<T>& Sphere3<T>::operator/=(U b) noexcept
    {
        point  /= b;
        radius /= positive(b);
        return *this;
    }

    template <typename T>
    constexpr AxBox3<T> Sphere3<T>::bounds() const noexcept
    {
        T       r   = abs(radius);
        return {
            all(point) - r,
            all(point) + r
        };
    }

    template <typename T>
    constexpr T         Sphere3<T>::diameter() const noexcept
    {
        return radius + radius;
    }

    template <typename T>
    constexpr Sphere3<T> Sphere3<T>::fixed() const noexcept
    {
        return Sphere3<T>(point, positive(radius));
    }

    template <typename T>
    constexpr square_t<T>     Sphere3<T>::surface_area() const noexcept
    {
        return 4.0*pi*(radius*radius);
    }

    template <typename T>
    constexpr bool    Sphere3<T>::valid() const noexcept
    {
        return radius >= T{};
    }

    template <typename T>
    constexpr cube_t<T>       Sphere3<T>::volume() const noexcept
    {
        return (4.0/3.0)*pi*(radius*radius*radius);
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    Sphere3<product_t<T,U>> operator*(T a, const Sphere3<U>& b)
    {
        return Sphere3<product_t<T,U>>(a*b.point, positive(a)*b.radius);
    }

    template <typename T>
    constexpr AxBox3<T>   aabb(const Sphere3<T>& sph) noexcept
    {
        return sph.bounds();
    }


    template <typename T>
    constexpr T           diameter(const Sphere3<T>&sph) noexcept
    {
        return sph.diameter();
    }

    template <typename T>
    constexpr bool  is_valid(const Sphere3<T>&sph) noexcept
    {
        return sph.valid();
    }



    template <typename T>
    constexpr square_t<T>     surface_area(const Sphere3<T>& sph) noexcept
    {
        return sph.surface_area();
    }

    template <typename T>
    constexpr cube_t<T>       volume(const Sphere3<T>&sph) noexcept
    {
        return sph.volume();
    }

}
