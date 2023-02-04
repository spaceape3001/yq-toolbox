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

#include <math/AxBox2.hpp>

#include <math/Segment1.hpp>
#include <math/Segment2.hpp>
#include <math/Segment3.hpp>
#include <math/Segment4.hpp>
#include <math/SegmentData.hpp>

#include <math/Tensor21.hpp>
#include <math/Tensor22.hpp>
#include <math/Tensor23.hpp>
#include <math/Tensor24.hpp>


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
        template <typename U> requires trait::is_arithmetic_v<U>
    constexpr Segment2<product_t<T,U>>    Segment2<T>::operator*(U rhs) const noexcept
    {
        return Segment2<product_t<T,U>>(a*rhs, b*rhs);
    }
    
    template <typename T>
        template <typename U> requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Segment2<T>&                Segment2<T>::operator*=(U rhs)  noexcept
    {
        a *= rhs;
        b *= rhs;
        return *this;
    }
        
    template <typename T>
        template <typename U> requires trait::is_arithmetic_v<U>
    constexpr Segment2<quotient_t<T,U>>   Segment2<T>::operator/(U rhs) const noexcept
    {
        return Segment2<quotient_t<T,U>>(a/rhs, b/rhs);
    }
    
    
    template <typename T>
        template <typename U> requires (trait::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Segment2<T>&                Segment2<T>::operator/=(U rhs)  noexcept
    {
        a /= rhs;
        b /= rhs;
        return *this;
    }
    
    template <typename T>
        template <typename U>
    Segment1<product_t<T,U>> Segment2<T>::operator*(const Tensor21<U>&rhs) const noexcept
    {
        return Segment1<product_t<T,U>>( a*rhs, b*rhs );
    }
    

    template <typename T>
        template <typename U>
    Segment2<product_t<T,U>> Segment2<T>::operator*(const Tensor22<U>&rhs) const noexcept
    {
        return Segment2<product_t<T,U>>( a*rhs, b*rhs );
    }

    template <typename T>
        template <typename U>
    Segment3<product_t<T,U>> Segment2<T>::operator*(const Tensor23<U>&rhs) const noexcept
    {
        return Segment3<product_t<T,U>>( a*rhs, b*rhs );
    }

    template <typename T>
        template <typename U>
    Segment4<product_t<T,U>> Segment2<T>::operator*(const Tensor24<U>&rhs) const noexcept
    {
        return Segment4<product_t<T,U>>( a*rhs, b*rhs );
    }
    
    template <typename T>
        template <typename U>
    requires trait::self_mul_v<T,U>
    Segment2<T>&    Segment2<T>::operator*=(const Tensor22<U>&rhs) noexcept
    {   
        a *= rhs;
        b *= rhs;
        return *this;
    }
    
    template <typename T>
    constexpr AxBox2<T>     Segment2<T>::bounds() const noexcept
    {
        return AxBox2<T>(UNION, a, b);
    }

    template <typename T>
    constexpr Vector2<T>  Segment2<T>::delta() const noexcept
    {
        return b - a;
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
    requires trait::is_arithmetic_v<T,U>
    constexpr Segment2<product_t<T,U>> operator*(T lhs, const Segment2<T>& rhs) noexcept
    {
        return Segment2<product_t<T,U>>(lhs*rhs.a, lhs*rhs.b);
    }

    template <typename T>
    constexpr AxBox2<T>   aabb(const Segment2<T>& seg) noexcept
    {
        return seg.bounds();
    }
    
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
