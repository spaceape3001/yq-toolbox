////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the segment3 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <math/AxBox3.hpp>

#include <math/Segment1.hpp>
#include <math/Segment2.hpp>
#include <math/Segment3.hpp>
#include <math/Segment4.hpp>
#include <math/SegmentData.hpp>

#include <math/Tensor31.hpp>
#include <math/Tensor32.hpp>
#include <math/Tensor33.hpp>
#include <math/Tensor34.hpp>

namespace yq {
    template <typename T>
    constexpr Segment3<T>::operator SegmentData<Vector3<T>>() const noexcept
    {
        return SegmentData<Vector3<T>>( a, b );
    }

    template <typename T>
    constexpr Segment3<T> Segment3<T>::operator+() const noexcept
    {
        return *this;
    }

    template <typename T>
    constexpr Segment3<T> Segment3<T>::operator-() const noexcept
    {
        return Segment3(-a, -b);
    }
    
    template <typename T>
    Segment3<T> Segment3<T>::operator+(const Vector3<T>& rhs) const noexcept
    {
        return Segment3( a+rhs, b+rhs);
    }

    template <typename T>
    Segment3<T> Segment3<T>::operator-(const Vector3<T>&rhs) const noexcept
    {
        return Segment3( a-rhs, b-rhs);
    }
    
    template <typename T>
    Segment3<T>& Segment3<T>::operator+=(const Vector3<T>&rhs) noexcept
    {
        a += rhs;
        b += rhs;
        return *this;
    }

    template <typename T>
    Segment3<T>& Segment3<T>::operator-=(const Vector3<T>&rhs) noexcept
    {
        a -= rhs;
        b -= rhs;
        return *this;
    }

    template <typename T>
        template <typename U> requires is_arithmetic_v<U>
    constexpr Segment3<product_t<T,U>>    Segment3<T>::operator*(U rhs) const noexcept
    {
        return Segment3<product_t<T,U>>(a*rhs, b*rhs);
    }
    
    template <typename T>
        template <typename U> requires (is_arithmetic_v<U> && self_mul_v<T,U>)
    Segment3<T>&                Segment3<T>::operator*=(U rhs)  noexcept
    {
        a *= rhs;
        b *= rhs;
        return *this;
    }
        
    template <typename T>
        template <typename U>
    Segment1<product_t<T,U>> Segment3<T>::operator*(const Tensor31<U>&rhs) const noexcept
    {
        return Segment1<product_t<T,U>>( a*rhs, b*rhs );
    }
    

    template <typename T>
        template <typename U>
    Segment2<product_t<T,U>> Segment3<T>::operator*(const Tensor32<U>&rhs) const noexcept
    {
        return Segment2<product_t<T,U>>( a*rhs, b*rhs );
    }

    template <typename T>
        template <typename U>
    Segment3<product_t<T,U>> Segment3<T>::operator*(const Tensor33<U>&rhs) const noexcept
    {
        return Segment3<product_t<T,U>>( a*rhs, b*rhs );
    }

    template <typename T>
        template <typename U>
    Segment4<product_t<T,U>> Segment3<T>::operator*(const Tensor34<U>&rhs) const noexcept
    {
        return Segment4<product_t<T,U>>( a*rhs, b*rhs );
    }
    
    template <typename T>
        template <typename U>
    requires self_mul_v<T,U>
    Segment3<T>&    Segment3<T>::operator*=(const Tensor33<U>&rhs) noexcept
    {   
        a *= rhs;
        b *= rhs;
        return *this;
    }

    template <typename T>
        template <typename U> requires is_arithmetic_v<U>
    constexpr Segment3<quotient_t<T,U>>   Segment3<T>::operator/(U rhs) const noexcept
    {
        return Segment3<quotient_t<T,U>>(a/rhs, b/rhs);
    }
    
    
    template <typename T>
        template <typename U> requires (is_arithmetic_v<U> && self_div_v<T,U>)
    Segment3<T>&                Segment3<T>::operator/=(U rhs)  noexcept
    {
        a /= rhs;
        b /= rhs;
        return *this;
    }
    
    template <typename T>
    constexpr AxBox3<T>     Segment3<T>::bounds() const noexcept
    {
        return AxBox3<T>(UNION, a, b);
    }

    template <typename T>
    constexpr Vector3<T>  Segment3<T>::delta() const noexcept
    {
        return b - a;
    }
    
    template <typename T>
    T   Segment3<T>::length() const 
    { 
        return delta().length(); 
    }

    template <typename T>
    constexpr square_t<T> Segment3<T>::length²() const noexcept
    {
        return delta().length²();
    }
    
    template <typename T>
    constexpr Vector3<T>  Segment3<T>::midpoint() const noexcept
    {
        return midvector(a, b);
    }

    template <typename T>
        template <typename>
    requires has_ieee754_v<T>
    constexpr Vector3<T>     Segment3<T>::point(ieee754_t<T> f) const noexcept
    {
        return (one_v<ieee754_t<T>> - f) * a + f * b;
    }
            

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename T, typename U>
    requires is_arithmetic_v<T,U>
    constexpr Segment3<product_t<T,U>> operator*(T lhs, const Segment3<T>& rhs) noexcept
    {
        return Segment3<product_t<T,U>>(lhs*rhs.a, lhs*rhs.b);
    }

    /*! \brief Creates axially aligned bounding box from the segment
    */
    template <typename T>
    constexpr AxBox3<T>   aabb(const Segment3<T>& seg) noexcept
    {
        return seg.bounds();
    }


    /*! \brief Computes the length of the segmetn
    */
    template <typename T>
    T       length(const Segment3<T>& seg)
    {
        return seg.length();
    }

    /*! \brief Computes the midpoint of the segmetn
    */
    template <typename T>
    constexpr Vector3<T>     midpoint(const Segment3<T>& seg) noexcept
    {
        return seg.midpoint();
    }

    /*! \brief Computes a point along the segment based on a fractional position
    
        \param[in]  seg Segment
        \param[in]  f   Fractional point
    */
    template <typename T>
    requires has_ieee754_v<T>
    constexpr Vector3<T>     point(const Segment3<T>& seg, ieee754_t<T> f) noexcept
    {
        return seg.point(f);
    }

}
