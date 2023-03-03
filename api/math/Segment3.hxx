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

#include <math/Segment3.hpp>
#include <math/SegmentData.hpp>
#include <math/errors.hpp>

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
        
    #if defined(YQ_MATH_SEGMENT1_HPP) && defined(YQ_MATH_TENSOR_3_1_HPP)
    template <typename T>
        template <typename U>
    Segment1<product_t<T,U>> Segment3<T>::operator*(const Tensor31<U>&rhs) const noexcept
    {
        return Segment1<product_t<T,U>>( a*rhs, b*rhs );
    }
    #endif
    
    #if defined(YQ_MATH_SEGMENT2_HPP) && defined(YQ_MATH_TENSOR_3_2_HPP)
    template <typename T>
        template <typename U>
    Segment2<product_t<T,U>> Segment3<T>::operator*(const Tensor32<U>&rhs) const noexcept
    {
        return Segment2<product_t<T,U>>( a*rhs, b*rhs );
    }
    #endif

    #ifdef YQ_MATH_TENSOR_3_3_HPP
    template <typename T>
        template <typename U>
    Segment3<product_t<T,U>> Segment3<T>::operator*(const Tensor33<U>&rhs) const noexcept
    {
        return Segment3<product_t<T,U>>( a*rhs, b*rhs );
    }
    #endif

    #if defined(YQ_MATH_SEGMENT4_HPP) && defined(YQ_MATH_TENSOR_3_4_HPP)
    template <typename T>
        template <typename U>
    Segment4<product_t<T,U>> Segment3<T>::operator*(const Tensor34<U>&rhs) const noexcept
    {
        return Segment4<product_t<T,U>>( a*rhs, b*rhs );
    }
    #endif
    
    #ifdef YQ_MATH_TENSOR_3_3_HPP
    template <typename T>
        template <typename U>
    requires self_mul_v<T,U>
    Segment3<T>&    Segment3<T>::operator*=(const Tensor33<U>&rhs) noexcept
    {   
        a *= rhs;
        b *= rhs;
        return *this;
    }
    #endif

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
    
    #ifdef YQ_MATH_AXBOX3_HPP
    template <typename T>
    constexpr AxBox3<T>     Segment3<T>::bounds() const noexcept
    {
        return AxBox3<T>(UNION, a, b);
    }
    #endif

    template <typename T>
    constexpr Vector3<T>  Segment3<T>::delta() const noexcept
    {
        return b - a;
    }
    
    template <typename T>
    Expect<unity_t<T>>   Segment3<T>::fraction_x(T x, T ep) const noexcept
    {
        if(abs(a.x-b.x) <= ep)
            return errors::degenerate_dimension();
        return (x-a.x)/(b.x-a.x);
    }
    
    template <typename T>
    Expect<unity_t<T>>   Segment3<T>::fraction_y(T y, T ep) const noexcept
    {
        if(abs(a.y-b.y) <= ep)
            return errors::degenerate_dimension();
        return (y-a.y)/(b.y-a.y);
    }

    template <typename T>
    Expect<unity_t<T>>   Segment3<T>::fraction_z(T z, T ep) const noexcept
    {
        if(abs(a.z-b.z) <= ep)
            return errors::degenerate_dimension();
        return (z-a.z)/(b.z-a.z);
    }
    
    template <typename T>
    Expect<Vector3<T>>  Segment3<T>::intercept_x(T x, T ep) const noexcept
    {
        auto ic = fraction_x(x, ep);
        if(!ic)
            return ic;
            
        unity_t<T>  f = *ic;
        unity_t<T>  g = one_v<T> - f;

        return Vector3<T>(
            x,
            g*a.y + f*b.y,
            g*a.z + f*b.z
        );
    }

    template <typename T>
    Expect<Vector3<T>>  Segment3<T>::intercept_y(T y, T ep) const noexcept
    {
        auto ic = fraction_y(y, ep);
        if(!ic)
            return ic;
            
        unity_t<T>  f = *ic;
        unity_t<T>  g = one_v<T> - f;
        
        return Vector3<T>(
            g*a.x + f*b.x,
            y,
            g*a.z + f*b.z
        );
    }

    template <typename T>
    Expect<Vector3<T>>  Segment3<T>::intercept_z(T z, T ep) const noexcept
    {
        auto ic = fraction_z(z, ep);
        if(!ic)
            return ic;
            
        unity_t<T>  f = *ic;
        unity_t<T>  g = one_v<T> - f;
        
        return Vector3<T>(
            g*a.x + f*b.x,
            g*a.y + f*b.y,
            z
        );
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

    #ifdef YQ_MATH_AXBOX3_HPP
    template <typename T>
    constexpr AxBox3<T>   aabb(const Segment3<T>& seg) noexcept
    {
        return seg.bounds();
    }
    #endif


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
