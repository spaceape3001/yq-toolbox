////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the segment1 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <math/AxBox1.hpp>

#include <math/Segment1.hpp>
#include <math/Segment2.hpp>
#include <math/Segment3.hpp>
#include <math/Segment4.hpp>
#include <math/SegmentData.hpp>

#include <math/Tensor11.hpp>
#include <math/Tensor12.hpp>
#include <math/Tensor13.hpp>
#include <math/Tensor14.hpp>

namespace yq {
    template <typename T>
    constexpr Segment1<T>::operator SegmentData<Vector1<T>>() const noexcept
    {
        return SegmentData<Vector1<T>>( a, b );
    }

    template <typename T>
    constexpr Segment1<T> Segment1<T>::operator+() const noexcept
    {
        return *this;
    }

    template <typename T>
    constexpr Segment1<T> Segment1<T>::operator-() const noexcept
    {
        return Segment1(-a, -b);
    }
    
    template <typename T>
    Segment1<T> Segment1<T>::operator+(const Vector1<T>& rhs) const noexcept
    {
        return Segment1( a+rhs, b+rhs);
    }

    template <typename T>
    Segment1<T> Segment1<T>::operator-(const Vector1<T>&rhs) const noexcept
    {
        return Segment1( a-rhs, b-rhs);
    }
    
    template <typename T>
    Segment1<T>& Segment1<T>::operator+=(const Vector1<T>&rhs) noexcept
    {
        a += rhs;
        b += rhs;
        return *this;
    }

    template <typename T>
    Segment1<T>& Segment1<T>::operator-=(const Vector1<T>&rhs) noexcept
    {
        a -= rhs;
        b -= rhs;
        return *this;
    }
    
    template <typename T>
        template <typename U> requires trait::is_arithmetic_v<U>
    constexpr Segment1<trait::product_t<T,U>>    Segment1<T>::operator*(U rhs) const noexcept
    {
        return Segment1<trait::product_t<T,U>>(a*rhs, b*rhs);
    }
    
    template <typename T>
        template <typename U> requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Segment1<T>&                Segment1<T>::operator*=(U rhs)  noexcept
    {
        a *= rhs;
        b *= rhs;
        return *this;
    }
        
    template <typename T>
        template <typename U>
    Segment1<trait::product_t<T,U>> Segment1<T>::operator*(const Tensor11<U>&rhs) const noexcept
    {
        return Segment1<trait::product_t<T,U>>( a*rhs, b*rhs );
    }
    

    template <typename T>
        template <typename U>
    Segment2<trait::product_t<T,U>> Segment1<T>::operator*(const Tensor12<U>&rhs) const noexcept
    {
        return Segment2<trait::product_t<T,U>>( a*rhs, b*rhs );
    }

    template <typename T>
        template <typename U>
    Segment3<trait::product_t<T,U>> Segment1<T>::operator*(const Tensor13<U>&rhs) const noexcept
    {
        return Segment3<trait::product_t<T,U>>( a*rhs, b*rhs );
    }

    template <typename T>
        template <typename U>
    Segment4<trait::product_t<T,U>> Segment1<T>::operator*(const Tensor14<U>&rhs) const noexcept
    {
        return Segment4<trait::product_t<T,U>>( a*rhs, b*rhs );
    }
    
    template <typename T>
        template <typename U>
    requires trait::self_mul_v<T,U>
    Segment1<T>&    Segment1<T>::operator*=(const Tensor11<U>&rhs) noexcept
    {   
        a *= rhs;
        b *= rhs;
        return *this;
    }

    template <typename T>
        template <typename U> requires trait::is_arithmetic_v<U>
    constexpr Segment1<trait::quotient_t<T,U>>   Segment1<T>::operator/(U rhs) const noexcept
    {
        return Segment1<trait::quotient_t<T,U>>(a/rhs, b/rhs);
    }
    
    
    template <typename T>
        template <typename U> requires (trait::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Segment1<T>&                Segment1<T>::operator/=(U rhs)  noexcept
    {
        a /= rhs;
        b /= rhs;
        return *this;
    }
    
    
    template <typename T>
    constexpr AxBox1<T>     Segment1<T>::bounds() const noexcept
    {
        return AxBox1<T>(UNION, a, b);
    }
    
    template <typename T>
    constexpr Vector1<T>  Segment1<T>::delta() const noexcept
    {
        return b - a;
    }

    template <typename T>
    T   Segment1<T>::length() const 
    { 
        return delta().length(); 
    }

    template <typename T>
    constexpr trait::square_t<T> Segment1<T>::length²() const noexcept
    {
        return delta().length²();
    }
    
    template <typename T>
    Vector1<T>  Segment1<T>::midpoint() const
    {
        return midvector(a, b);
    }
    
    template <typename T>
        template <typename>
    requires has_ieee754_v<T>
    constexpr Vector1<T>     Segment1<T>::point(ieee754_t<T> f) const noexcept
    {
        return (one_v<ieee754_t<T>> - f) * a + f * b;
    }


    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename T, typename U>
    requires trait::is_arithmetic_v<T,U>
    constexpr Segment1<trait::product_t<T,U>> operator*(T lhs, const Segment1<T>& rhs) noexcept
    {
        return Segment1<trait::product_t<T,U>>(lhs*rhs.a, lhs*rhs.b);
    }

    template <typename T>
    constexpr AxBox1<T>   aabb(const Segment1<T>& seg) noexcept
    {
        return seg.bounds();
    }

    template <typename T>
    T       length(const Segment1<T>& seg)
    {
        return seg.length();
    }
    
    /*! \brief Computes the midpoint of the segmetn
    */
    template <typename T>
    constexpr Vector1<T>     midpoint(const Segment1<T>& seg) noexcept
    {
        return seg.midpoint();
    }

    /*! \brief Computes a point along the segment based on a fractional position
    
        \param[in]  seg Segment
        \param[in]  f   Fractional point
    */
    template <typename T>
    requires has_ieee754_v<T>
    constexpr Vector1<T>     point(const Segment1<T>& seg, ieee754_t<T> f) noexcept
    {
        return seg.point(f);
    }
    }
