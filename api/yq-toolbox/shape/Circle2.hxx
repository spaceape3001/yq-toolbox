////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq-toolbox/shape/Circle2.hpp>

/* 
    This is the template IMPLEMENTATION of the circle2 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

namespace yq {
    template <typename T>
    Circle2<T>::Circle2(focus_t, const Vector2<T>& focus, const Vector2<T>& edge) : 
        Circle2(focus, (edge-focus).length()) {}

    template <typename T>
    Circle2<T>::Circle2(opposite_t, const Vector2<T>&a, const Vector2<T>&b) : 
        Circle2(middivide(a,b), middivide((a-b).length())) {}

    template <typename T>
    constexpr Circle2<T> Circle2<T>::operator+() const noexcept
    {
        return Circle2<T>(center, radius);
    }
    
    template <typename T>
    constexpr Circle2<T> Circle2<T>::operator-() const noexcept
    {
        return Circle2<T>(-center, -radius);
    }

    template <typename T>
    constexpr Circle2<T>   Circle2<T>::operator+(const Vector2<T>&b) const noexcept
    {
        return Circle2<T>(center+b, radius);
    }

    template <typename T>
    Circle2<T>&            Circle2<T>::operator+=(const Vector2<T>&b) noexcept
    {
        center += b;
        return *this;
    }

    template <typename T>
    constexpr Circle2<T>   Circle2<T>::operator-(const Vector2<T>&b) const noexcept
    {
        return Circle2<T>(center-b,radius);
    }

    template <typename T>
    Circle2<T>&            Circle2<T>::operator-=(const Vector2<T>&b) noexcept
    {
        center -= b;
        return *this;
    }
    
    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    Circle2<product_t<T,U>> Circle2<T>::operator*(U b) const noexcept
    {
        return Circle2<product_t<T,U>>( center*b, radius*positive(b));
    }
    
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
    Circle2<T>& Circle2<T>::operator*=(U b) noexcept
    {
        center  *= b;
        radius *= positive(b);
        return *this;
    }
        
    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    Circle2<quotient_t<T,U>> Circle2<T>::operator/(U b) const noexcept
    {
        return Circle2<quotient_t<T,U>>( center/b, radius/positive(b));
    }
    
    
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_divide_v<T,U>)
    Circle2<T>& Circle2<T>::operator/=(U b) noexcept
    {
        center  /= b;
        radius /= positive(b);
        return *this;
    }

    template <typename T>
    constexpr square_t<T> Circle2<T>::area() const noexcept
    {
        if constexpr ( has_ieee754_v<T> )
            return std::numbers::pi_v<ieee754_t<T>> * (radius*radius);
        else
            return {};
    }

    #ifdef YQ_MATH_AXBOX2_HPP
    template <typename T>
    constexpr AxBox2<T>   Circle2<T>::bounds() const noexcept 
    {
        T       r   = abs(radius);
        return AxBox2<T>(all(center) - r, all(center) + r);
    }
    #endif
    
    template <typename T>
    constexpr T     Circle2<T>::circumference() const noexcept
    {
        if constexpr ( has_ieee754_v<T> )
            return ieee754_t<T>(2.) * std::numbers::pi_v<ieee754_t<T>> * radius;
        else
            return {};
    }

    template <typename T>
    constexpr bool  Circle2<T>::contains(const Vector2<T>& pt) const noexcept
    {
        return (pt-center).length²() <= radius * radius;
    }

    template <typename T>
    constexpr T     Circle2<T>::diameter() const noexcept
    {
        return radius + radius;
    }

    template <typename T>
    constexpr Circle2<T> Circle2<T>::fixed() const noexcept
    {
        return Circle2<T>(center, positive(radius));
    }

    template <typename T>
    constexpr bool    Circle2<T>::valid() const noexcept
    {
        return radius >= T{};
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    Circle2<product_t<T,U>> operator*(T a, const Circle2<U>& b)
    {
        return Circle2<product_t<T,U>>(a*b.center, positive(a)*b.radius);
    }

    #ifdef YQ_MATH_AXBOX2_HPP
    template <typename T>
    constexpr AxBox2<T>   aabb(const Circle2<T>& cir) noexcept
    {   
        return cir.bounds();
    }
    #endif
    
    template <typename T>
    constexpr square_t<T> area(const Circle2<T>& cir) noexcept
    {
        return cir.area();
    }
    
    
    /*! \brief Computes the circumference of a circle
    */
    template <typename T>
    constexpr T     circumference(const Circle2<T>& cir) noexcept
    {
        return cir.circumference();
    }

    /*! \brief Computes the diameter of a circle
    */
    template <typename T>
    constexpr T     diameter(const Circle2<T>& cir) noexcept
    {
        return cir.diameter();
    }

    template <typename T>
    constexpr bool  is_valid(const Circle2<T>&cir) noexcept
    {
        return cir.valid();
    }


    template <typename T>
    constexpr T   permimeter(const Circle2<T>& cir) noexcept
    {
        return cir.circumference();
    }
}
