////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/shape/Oval2.hpp>
#include <yq/math/AllComponents.hpp>
#include <yq/math/AnyComponents.hpp>
#include <yq/trait/has_abs.hpp>

/* 
    This is the template IMPLEMENTATION of the circle2 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

namespace yq {
    template <typename T>
    constexpr Oval2<T> Oval2<T>::operator+() const noexcept
    {
        return Oval2<T>(center, radius);
    }
    
    template <typename T>
    constexpr Oval2<T> Oval2<T>::operator-() const noexcept
    {
        return Oval2<T>(-center, -radius);
    }

    template <typename T>
    constexpr Oval2<T>   Oval2<T>::operator+(const Vector2<T>&b) const noexcept
    {
        return Oval2<T>(center+b, radius);
    }

    template <typename T>
    Oval2<T>&            Oval2<T>::operator+=(const Vector2<T>&b) noexcept
    {
        center += b;
        return *this;
    }

    template <typename T>
    constexpr Oval2<T>   Oval2<T>::operator-(const Vector2<T>&b) const noexcept
    {
        return Oval2<T>(center-b,radius);
    }

    template <typename T>
    Oval2<T>&            Oval2<T>::operator-=(const Vector2<T>&b) noexcept
    {
        center -= b;
        return *this;
    }
    
    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    Oval2<product_t<T,U>> Oval2<T>::operator*(U b) const noexcept
    {
        return Oval2<product_t<T,U>>( center*b, radius*positive(b));
    }
    
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
    Oval2<T>& Oval2<T>::operator*=(U b) noexcept
    {
        center  *= b;
        radius *= positive(b);
        return *this;
    }
        
    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    Oval2<quotient_t<T,U>> Oval2<T>::operator/(U b) const noexcept
    {
        return Oval2<quotient_t<T,U>>( center/b, radius/positive(b));
    }
    
    
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_divide_v<T,U>)
    Oval2<T>& Oval2<T>::operator/=(U b) noexcept
    {
        center  /= b;
        radius /= positive(b);
        return *this;
    }

    template <typename T>
    constexpr square_t<T> Oval2<T>::area() const noexcept
    {
        if constexpr ( has_ieee754_v<T> )
            return std::numbers::pi_v<ieee754_t<T>> * (radius.x*radius.y);
        else
            return {};
    }

    #ifdef YQ_MATH_AXBOX2_HPP
    template <typename T>
    constexpr AxBox2<T>   Oval2<T>::bounds() const noexcept 
    {
        auto r   = radius.eabs();
        return AxBox2<T>(center - r, center + r);
    }
    #endif
    
    //template <typename T>
    //constexpr T     Oval2<T>::circumference() const noexcept
    //{
        //if constexpr ( has_ieee754_v<T> )
            //return ieee754_t<T>(2.) * std::numbers::pi_v<ieee754_t<T>> * radius;
        //else
            //return {};
    //}

    template <typename T>
    constexpr bool  Oval2<T>::contains(const Vector2<T>& pt) const noexcept
    {
        return (pt-center).length²() <= radius * radius;
    }

    template <typename T>
    constexpr Oval2<T> Oval2<T>::fixed() const noexcept
    {
        return Oval2<T>(center, positive(radius));
    }

    template <typename T>
    constexpr bool    Oval2<T>::valid() const noexcept
    {
        return (radius.x >= T{}) && (radius.y >= T{});
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    Oval2<product_t<T,U>> operator*(T a, const Oval2<U>& b)
    {
        return Oval2<product_t<T,U>>(a*b.center, positive(a)*b.radius);
    }

    #ifdef YQ_MATH_AXBOX2_HPP
    template <typename T>
    constexpr AxBox2<T>   aabb(const Oval2<T>& cir) noexcept
    {   
        return cir.bounds();
    }
    #endif
    
    template <typename T>
    constexpr square_t<T> area(const Oval2<T>& cir) noexcept
    {
        return cir.area();
    }
    
    template <typename T>
    constexpr bool  is_valid(const Oval2<T>&cir) noexcept
    {
        return cir.valid();
    }
}
