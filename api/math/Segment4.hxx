////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the segment4 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <math/Segment4.hpp>
#include <math/SegmentData.hpp>

namespace yq {

    template <typename T>
    constexpr Segment4<T>::operator SegmentData<Vector4<T>>() const noexcept
    {
        return SegmentData<Vector4<T>>( a, b );
    }

    template <typename T>
    constexpr Segment4<T> Segment4<T>::operator+() const noexcept
    {
        return *this;
    }

    template <typename T>
    constexpr Segment4<T> Segment4<T>::operator-() const noexcept
    {
        return Segment4(-a, -b);
    }
    
    template <typename T>
    Segment4<T> Segment4<T>::operator+(const Vector4<T>& rhs) const noexcept
    {
        return Segment4( a+rhs, b+rhs);
    }

    template <typename T>
    Segment4<T> Segment4<T>::operator-(const Vector4<T>&rhs) const noexcept
    {
        return Segment4( a-rhs, b-rhs);
    }
    
    template <typename T>
    Segment4<T>& Segment4<T>::operator+=(const Vector4<T>&rhs) noexcept
    {
        a += rhs;
        b += rhs;
        return *this;
    }

    template <typename T>
    Segment4<T>& Segment4<T>::operator-=(const Vector4<T>&rhs) noexcept
    {
        a -= rhs;
        b -= rhs;
        return *this;
    }

    template <typename T>
        template <typename U> requires is_arithmetic_v<U>
    constexpr Segment4<product_t<T,U>>    Segment4<T>::operator*(U rhs) const noexcept
    {
        return Segment4<product_t<T,U>>(a*rhs, b*rhs);
    }
    
    template <typename T>
        template <typename U> requires (is_arithmetic_v<U> && self_mul_v<T,U>)
    Segment4<T>&                Segment4<T>::operator*=(U rhs)  noexcept
    {
        a *= rhs;
        b *= rhs;
        return *this;
    }
        
    #if defined(YQ_MATH_SEGMENT1_HPP) && defined(YQ_MATH_TENSOR_4_1_HPP)
    template <typename T>
        template <typename U>
    Segment1<product_t<T,U>> Segment4<T>::operator*(const Tensor41<U>&rhs) const noexcept
    {
        return Segment1<product_t<T,U>>( a*rhs, b*rhs );
    }
    #endif

    #if defined(YQ_MATH_SEGMENT2_HPP) && defined(YQ_MATH_TENSOR_4_2_HPP)
    template <typename T>
        template <typename U>
    Segment2<product_t<T,U>> Segment4<T>::operator*(const Tensor42<U>&rhs) const noexcept
    {
        return Segment2<product_t<T,U>>( a*rhs, b*rhs );
    }
    #endif

    #if defined(YQ_MATH_SEGMENT3_HPP) && defined(YQ_MATH_TENSOR_4_3_HPP)
    template <typename T>
        template <typename U>
    Segment3<product_t<T,U>> Segment4<T>::operator*(const Tensor43<U>&rhs) const noexcept
    {
        return Segment3<product_t<T,U>>( a*rhs, b*rhs );
    }
    #endif

    #ifdef YQ_MATH_TENSOR_4_4_HPP
    template <typename T>
        template <typename U>
    Segment4<product_t<T,U>> Segment4<T>::operator*(const Tensor44<U>&rhs) const noexcept
    {
        return Segment4<product_t<T,U>>( a*rhs, b*rhs );
    }
    #endif
    
    #ifdef YQ_MATH_TENSOR_4_4_HPP
    template <typename T>
        template <typename U>
    requires self_mul_v<T,U>
    Segment4<T>&    Segment4<T>::operator*=(const Tensor44<U>&rhs) noexcept
    {   
        a *= rhs;
        b *= rhs;
        return *this;
    }
    #endif

    template <typename T>
        template <typename U> requires is_arithmetic_v<U>
    constexpr Segment4<quotient_t<T,U>>   Segment4<T>::operator/(U rhs) const noexcept
    {
        return Segment4<quotient_t<T,U>>(a/rhs, b/rhs);
    }
    
    
    template <typename T>
        template <typename U> requires (is_arithmetic_v<U> && self_div_v<T,U>)
    Segment4<T>&                Segment4<T>::operator/=(U rhs)  noexcept
    {
        a /= rhs;
        b /= rhs;
        return *this;
    }
    
    #ifdef YQ_MATH_AXBOX4_HPP
    template <typename T>
    constexpr AxBox4<T>     Segment4<T>::bounds() const noexcept
    {
        return AxBox4<T>(UNION, a, b);
    }
    #endif

    template <typename T>
    constexpr Vector4<T>  Segment4<T>::delta() const noexcept
    {
        return b - a;
    }

    template <typename T>
        template <typename>
    requires is_floating_point_v<T>
    constexpr std::pair<unity_t<T>, bool>   Segment4<T>::fraction_w(T w, T ep) const noexcept
    {
        if(abs(a.w-b.w) <= ep)
            return {zero_v<unity_t<T>>, false};
        return {(w-a.w)/(b.w-a.w), true};
    }

    template <typename T>
        template <typename>
    requires is_floating_point_v<T>
    constexpr std::pair<unity_t<T>, bool>   Segment4<T>::fraction_x(T x, T ep) const noexcept
    {
        if(abs(a.x-b.x) <= ep)
            return {zero_v<unity_t<T>>, false};
        return {(x-a.x)/(b.x-a.x), true};
    }
    
    template <typename T>
        template <typename>
    requires is_floating_point_v<T>
    constexpr std::pair<unity_t<T>, bool>   Segment4<T>::fraction_y(T y, T ep) const noexcept
    {
        if(abs(a.y-b.y) <= ep)
            return {zero_v<unity_t<T>>, false};
        return {(y-a.y)/(b.y-a.y), true};
    }

    template <typename T>
        template <typename>
    requires is_floating_point_v<T>
    constexpr std::pair<unity_t<T>, bool>   Segment4<T>::fraction_z(T z, T ep) const noexcept
    {
        if(abs(a.z-b.z) <= ep)
            return {zero_v<unity_t<T>>, false};
        return {(z-a.z)/(b.z-a.z), true};
    }

    template <typename T>
        template <typename>
    requires is_floating_point_v<T>
    constexpr std::pair<Vector4<T>, bool> Segment4<T>::intercept_w(T w, T ep) const noexcept
    {
        auto [ f, b ] = fraction_w(w, ep);
        if(!b)
            return {Vector4<T>(ZERO), false};
            
        unity_t<T>  g = one_v<T> - f;
        
        return Vector4<T>(
            g*a.x + f*b.x,
            g*a.y + f*b.y,
            g*a.z + f*b.z,
            w
        );
    }

    template <typename T>
        template <typename>
    requires is_floating_point_v<T>
    constexpr std::pair<Vector4<T>, bool> Segment4<T>::intercept_x(T x, T ep) const noexcept
    {
        auto [ f, b ] = fraction_x(x, ep);
        if(!b)
            return {Vector4<T>(ZERO), false};
            
        unity_t<T>  g = one_v<T> - f;
        
        return Vector4<T>(
            x,
            g*a.y + f*b.y,
            g*a.z + f*b.z,
            g*a.w + f*b.w
        );
    }

    template <typename T>
        template <typename>
    requires is_floating_point_v<T>
    constexpr std::pair<Vector4<T>, bool> Segment4<T>::intercept_y(T y, T ep) const noexcept
    {
        auto [ f, b ] = fraction_y(y, ep);
        if(!b)
            return {Vector4<T>(ZERO), false};
            
        unity_t<T>  g = one_v<T> - f;
        
        return Vector4<T>(
            g*a.x + f*b.x,
            y,
            g*a.z + f*b.z,
            g*a.w + f*b.w
        );
    }

    template <typename T>
        template <typename>
    requires is_floating_point_v<T>
    constexpr std::pair<Vector4<T>, bool> Segment4<T>::intercept_z(T z, T ep) const noexcept
    {
        auto [ f, b ] = fraction_z(z, ep);
        if(!b)
            return {Vector4<T>(ZERO), false};
            
        unity_t<T>  g = one_v<T> - f;
        
        return Vector4<T>(
            g*a.x + f*b.x,
            g*a.y + f*b.y,
            z,
            g*a.w + f*b.w
        );
    }

    template <typename T>
    T   Segment4<T>::length() const 
    { 
        return delta().length(); 
    }

    template <typename T>
    constexpr square_t<T> Segment4<T>::length²() const noexcept
    {
        return delta().length²();
    }
    
    template <typename T>
    Vector4<T>  Segment4<T>::midpoint() const
    {
        return midvector(a, b);
    }

    template <typename T>
        template <typename>
    requires has_ieee754_v<T>
    constexpr Vector4<T>     Segment4<T>::point(ieee754_t<T> f) const noexcept
    {
        return (one_v<ieee754_t<T>> - f) * a + f * b;
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename T, typename U>
    requires is_arithmetic_v<T,U>
    constexpr Segment4<product_t<T,U>> operator*(T lhs, const Segment4<T>& rhs) noexcept
    {
        return Segment4<product_t<T,U>>(lhs*rhs.a, lhs*rhs.b);
    }

    #ifdef YQ_MATH_AXBOX4_HPP
    template <typename T>
    constexpr AxBox4<T>   aabb(const Segment4<T>& seg) noexcept
    {
        return seg.bounds();
    }
    #endif

    template <typename T>
    T       length(const Segment4<T>& seg)
    {
        return seg.length();
    }

    template <typename T>
    constexpr Vector4<T>     midpoint(const Segment4<T>& seg) noexcept
    {
        return seg.midpoint();
    }
    
    template <typename T>
    requires has_ieee754_v<T>
    constexpr Vector4<T>     point(const Segment4<T>& seg, ieee754_t<T> f) noexcept
    {
        return seg.point(f);
    }
}
