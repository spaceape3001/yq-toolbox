////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/AxBox2.hpp>
#include <math/Circle2.hpp>

/* 
    This is the template IMPLEMENTATION of the circle2 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

namespace yq {
    template <typename T>
    constexpr Circle2<T> Circle2<T>::operator+() const noexcept
    {
        return Circle2<T>(point, radius);
    }
    
    template <typename T>
    constexpr Circle2<T> Circle2<T>::operator-() const noexcept
    {
        return Circle2<T>(-point, -radius);
    }

    template <typename T>
    constexpr Circle2<T>   Circle2<T>::operator+(const Vector2<T>&b) const noexcept
    {
        return Circle2<T>(point+b, radius);
    }

    template <typename T>
    Circle2<T>&            Circle2<T>::operator+=(const Vector2<T>&b) noexcept
    {
        point += b;
        return *this;
    }

    template <typename T>
    constexpr Circle2<T>   Circle2<T>::operator-(const Vector2<T>&b) const noexcept
    {
        return Circle2<T>(point-b,radius);
    }

    template <typename T>
    Circle2<T>&            Circle2<T>::operator-=(const Vector2<T>&b) noexcept
    {
        point -= b;
        return *this;
    }
    
    template <typename T>
        template <typename U>
    requires trait::is_arithmetic_v<U>
    Circle2<trait::product_t<T,U>> Circle2<T>::operator*(U b) const noexcept
    {
        return Circle2<trait::product_t<T,U>>( point*b, radius*positive(b));
    }
    
    template <typename T>
        template <typename U>
    requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Circle2<T>& Circle2<T>::operator*=(U b) noexcept
    {
        point  *= b;
        radius *= positive(b);
        return *this;
    }
        
    template <typename T>
        template <typename U>
    requires trait::is_arithmetic_v<U>
    Circle2<trait::quotient_t<T,U>> Circle2<T>::operator/(U b) const noexcept
    {
        return Circle2<trait::quotient_t<T,U>>( point/b, radius/positive(b));
    }
    
    
    template <typename T>
        template <typename U>
    requires (trait::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Circle2<T>& Circle2<T>::operator/=(U b) noexcept
    {
        point  /= b;
        radius /= positive(b);
        return *this;
    }

    template <typename T>
    constexpr trait::square_t<T> Circle2<T>::area() const noexcept
    {
        if constexpr ( has_ieee754_v<T> )
            return std::numbers::pi_v<ieee754_t<T>> * (radius*radius);
        else
            return {};
    }

    template <typename T>
    constexpr AxBox2<T>   Circle2<T>::bounds() const noexcept 
    {
        T       r   = abs(radius);
        return AxBox2<T>(all(point) - r, all(point) + r);
    }
    
    template <typename T>
    constexpr T     Circle2<T>::circumference() const noexcept
    {
        if constexpr ( has_ieee754_v<T> )
            return ieee754_t<T>(2.) * std::numbers::pi_v<ieee754_t<T>> * radius;
        else
            return {};
    }

    template <typename T>
    constexpr T     Circle2<T>::diameter() const noexcept
    {
        return radius + radius;
    }

    template <typename T>
    constexpr Circle2<T> Circle2<T>::fixed() const noexcept
    {
        return Circle2<T>(point, positive(radius));
    }

    template <typename T>
    constexpr bool    Circle2<T>::valid() const noexcept
    {
        return radius >= T{};
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename T, typename U>
    requires trait::is_arithmetic_v<T>
    Circle2<trait::product_t<T,U>> operator*(T a, const Circle2<U>& b)
    {
        return Circle2<trait::product_t<T,U>>(a*b.point, positive(a)*b.radius);
    }

    template <typename T>
    constexpr AxBox2<T>   aabb(const Circle2<T>& cir) noexcept
    {   
        return cir.bounds();
    }
    
    template <typename T>
    constexpr trait::square_t<T> area(const Circle2<T>& cir) noexcept
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
