////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the segment2 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <math/Segment2.hpp>
#include <math/SegmentData.hpp>

namespace yq {

    template <typename T>
    constexpr Segment2<T>::operator SegmentData<Vector2<T>>() const noexcept
    {
        return SegmentData<Vector2<T>>( a, b );
    }


    template <typename T>
    constexpr Segment2<T> Segment2<T>::operator+() const noexcept
    {
        return *this;
    }

    template <typename T>
    constexpr Segment2<T> Segment2<T>::operator-() const noexcept
    {
        return Segment2(-a, -b);
    }
    
    template <typename T>
    Segment2<T> Segment2<T>::operator+(const Vector2<T>& rhs) const noexcept
    {
        return Segment2( a+rhs, b+rhs);
    }

    template <typename T>
    Segment2<T> Segment2<T>::operator-(const Vector2<T>&rhs) const noexcept
    {
        return Segment2( a-rhs, b-rhs);
    }
    
    template <typename T>
    Segment2<T>& Segment2<T>::operator+=(const Vector2<T>&rhs) noexcept
    {
        a += rhs;
        b += rhs;
        return *this;
    }

    template <typename T>
    Segment2<T>& Segment2<T>::operator-=(const Vector2<T>&rhs) noexcept
    {
        a -= rhs;
        b -= rhs;
        return *this;
    }
    
    template <typename T>
        template <typename U> requires is_arithmetic_v<U>
    constexpr Segment2<product_t<T,U>>    Segment2<T>::operator*(U rhs) const noexcept
    {
        return Segment2<product_t<T,U>>(a*rhs, b*rhs);
    }
    
    template <typename T>
        template <typename U> requires (is_arithmetic_v<U> && self_mul_v<T,U>)
    Segment2<T>&                Segment2<T>::operator*=(U rhs)  noexcept
    {
        a *= rhs;
        b *= rhs;
        return *this;
    }
        
    #if defined(YQ_MATH_SEGMENT1_HPP) && defined(YQ_MATH_TENSOR_2_1_HPP)
    template <typename T>
        template <typename U>
    Segment1<product_t<T,U>> Segment2<T>::operator*(const Tensor21<U>&rhs) const noexcept
    {
        return Segment1<product_t<T,U>>( a*rhs, b*rhs );
    }
    #endif
    
    #ifdef YQ_MATH_TENSOR_2_2_HPP
    template <typename T>
        template <typename U>
    Segment2<product_t<T,U>> Segment2<T>::operator*(const Tensor22<U>&rhs) const noexcept
    {
        return Segment2<product_t<T,U>>( a*rhs, b*rhs );
    }
    #endif

    #if defined(YQ_MATH_SEGMENT3_HPP) && defined(YQ_MATH_TENSOR_2_3_HPP)
    template <typename T>
        template <typename U>
    Segment3<product_t<T,U>> Segment2<T>::operator*(const Tensor23<U>&rhs) const noexcept
    {
        return Segment3<product_t<T,U>>( a*rhs, b*rhs );
    }
    #endif

    #if defined(YQ_MATH_SEGMENT4_HPP) && defined(YQ_MATH_TENSOR_2_4_HPP)
    template <typename T>
        template <typename U>
    Segment4<product_t<T,U>> Segment2<T>::operator*(const Tensor24<U>&rhs) const noexcept
    {
        return Segment4<product_t<T,U>>( a*rhs, b*rhs );
    }
    #endif
    
    #ifdef YQ_MATH_TENSOR_2_2_HPP
    template <typename T>
        template <typename U>
    requires self_mul_v<T,U>
    Segment2<T>&    Segment2<T>::operator*=(const Tensor22<U>&rhs) noexcept
    {   
        a *= rhs;
        b *= rhs;
        return *this;
    }
    #endif
    
    template <typename T>
        template <typename U> requires is_arithmetic_v<U>
    constexpr Segment2<quotient_t<T,U>>   Segment2<T>::operator/(U rhs) const noexcept
    {
        return Segment2<quotient_t<T,U>>(a/rhs, b/rhs);
    }
    
    template <typename T>
        template <typename U> requires (is_arithmetic_v<U> && self_div_v<T,U>)
    Segment2<T>&                Segment2<T>::operator/=(U rhs)  noexcept
    {
        a /= rhs;
        b /= rhs;
        return *this;
    }
    
    #ifdef YQ_MATH_AXBOX2_HPP
    template <typename T>
    constexpr AxBox2<T>     Segment2<T>::bounds() const noexcept
    {
        return AxBox2<T>(UNION, a, b);
    }
    #endif

    template <typename T>
    constexpr Vector2<T>  Segment2<T>::delta() const noexcept
    {
        return b - a;
    }
    
    template <typename T>
    constexpr std::pair<unity_t<T>, bool>   Segment2<T>::fraction_x(T x, T ep) const noexcept
    {
        if(abs(a.x-b.x) <= ep)
            return {zero_v<unity_t<T>>, false};
        return {(x-a.x)/(b.x-a.x), true};
    }
    
    template <typename T>
    constexpr std::pair<unity_t<T>, bool>   Segment2<T>::fraction_y(T y, T ep) const noexcept
    {
        if(abs(a.y-b.y) <= ep)
            return {zero_v<unity_t<T>>, false};
        return {(y-a.y)/(b.y-a.y), true};
    }

    template <typename T>
    constexpr std::pair<Vector2<T>, bool> Segment2<T>::intercept_x(T x, T ep) const noexcept
    {
        auto [ f, b ] = fraction_x(x, ep);
        if(!b)
            return {Vector2<T>(ZERO), false};
            
        unity_t<T>  g = one_v<T> - f;
        
        return Vector2<T>(
            x,
            g*a.y + f*b.y
        );
    }

    template <typename T>
    constexpr std::pair<Vector2<T>, bool> Segment2<T>::intercept_y(T y, T ep) const noexcept
    {
        auto [ f, b ] = fraction_y(y, ep);
        if(!b)
            return {Vector2<T>(ZERO), false};
            
        unity_t<T>  g = one_v<T> - f;
        
        return Vector2<T>(
            g*a.x + f*b.x,
            y
        );
    }

    template <typename T>
    T   Segment2<T>::length() const 
    { 
        return delta().length(); 
    }

    template <typename T>
    constexpr square_t<T> Segment2<T>::length²() const noexcept
    {
        return delta().length²();
    }
    
    template <typename T>
    constexpr Vector2<T>  Segment2<T>::midpoint() const noexcept
    {
        return midvector(a, b);
    }

    template <typename T>
    template <typename>
    requires has_ieee754_v<T>
    constexpr Vector2<T>     Segment2<T>::point(ieee754_t<T> f) const noexcept
    {
        return (one_v<ieee754_t<T>> - f) * a + f * b;
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename T, typename U>
    requires is_arithmetic_v<T,U>
    constexpr Segment2<product_t<T,U>> operator*(T lhs, const Segment2<T>& rhs) noexcept
    {
        return Segment2<product_t<T,U>>(lhs*rhs.a, lhs*rhs.b);
    }

    #ifdef YQ_MATH_AXBOX2_HPP
    template <typename T>
    constexpr AxBox2<T>   aabb(const Segment2<T>& seg) noexcept
    {
        return seg.bounds();
    }
    #endif
    
    template <typename T>
    T       length(const Segment2<T>& seg)
    {
        return seg.length();
    }

    template <typename T>
    constexpr Vector2<T>     midpoint(const Segment2<T>& seg) noexcept
    {
        return seg.midpoint();
    }

    template <typename T>
    requires has_ieee754_v<T>
    constexpr Vector2<T>     point(const Segment2<T>& seg, ieee754_t<T> f) noexcept
    {
        return seg.point(f);
    }

}
