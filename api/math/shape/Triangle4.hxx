////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the triangle4 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <math/shape/Triangle4.hpp>
#include <math/shape/TriangleData.hpp>


namespace yq {
    #ifdef YQ_MATH_SEGMENT4_HPP
    template <typename T>
    constexpr Triangle4<T>::Triangle4(const Segment4<T>&seg, const Vector4<T>& c) noexcept : Triangle4(seg.a, seg.b, c) {}
    #endif

    template <typename T>
    constexpr Triangle4<T>::operator TriangleData<Vector4<T>> () const noexcept 
    { 
        return TriangleData<Vector4<T>>( a, b, c ); 
    }

    template <typename T>
    constexpr Triangle4<T> Triangle4<T>::operator+() const noexcept
    {
        return *this;
    }

    template <typename T>
    constexpr Triangle4<T> Triangle4<T>::operator-() const noexcept
    {
        return Triangle4(-a,-b,-c);
    }
    
    template <typename T>
    constexpr Triangle4<T> Triangle4<T>::operator+(const Vector4<T>&rhs) const noexcept
    {
        return Triangle4(a+rhs, b+rhs, c+rhs);
    }

    template <typename T>
    Triangle4<T>& Triangle4<T>::operator+=(const Vector4<T>&rhs) noexcept
    {
        a += rhs;
        b += rhs;
        c += rhs;
        return *this;
    }
    

    template <typename T>
    constexpr Triangle4<T> Triangle4<T>::operator-(const Vector4<T>&rhs) const noexcept
    {
        return Triangle4(a-rhs, b-rhs, c-rhs);
    }

    template <typename T>
    Triangle4<T>& Triangle4<T>::operator-=(const Vector4<T>&rhs) noexcept
    {
        a -= rhs;
        b -= rhs;
        c -= rhs;
        return *this;
    }
    
    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    constexpr Triangle4<product_t<T,U>> Triangle4<T>::operator*(U rhs) const noexcept
    {
        return Triangle4<product_t<T,U>>( a*rhs, b*rhs, c*rhs );
    }
    
    
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_mul_v<T,U>)
    Triangle4<T>& Triangle4<T>::operator*=(U rhs) noexcept
    {
        a *= rhs;
        b *= rhs;
        c *= rhs;
        return *this;
    }

    #if defined(YQ_MATH_TENSOR_4_2_HPP) && defined(YQ_MATH_TRIANGLE2_HPP) 
    template <typename T>
        template <typename U>
    Triangle2<product_t<T,U>>   Triangle4<T>::operator*(const Tensor42<U>&rhs) const noexcept
    {
        return Triangle2<product_t<T,U>>(a*rhs, b*rhs, c*rhs);
    }
    #endif

    #if defined(YQ_MATH_TENSOR_4_3_HPP) && defined(YQ_MATH_TRIANGLE3_HPP) 
    template <typename T>
        template <typename U>
    Triangle3<product_t<T,U>>   Triangle4<T>::operator*(const Tensor43<U>&rhs) const noexcept
    {
        return Triangle3<product_t<T,U>>(a*rhs, b*rhs, c*rhs);
    }
    #endif

    #ifdef YQ_MATH_TENSOR_4_4_HPP
    template <typename T>
        template <typename U>
    Triangle4<product_t<T,U>>   Triangle4<T>::operator*(const Tensor44<U>&rhs) const noexcept
    {
        return Triangle4<product_t<T,U>>(a*rhs, b*rhs, c*rhs);
    }
    #endif

    #ifdef YQ_MATH_TENSOR_4_4_HPP
    template <typename T>
        template <typename U>
    requires self_mul_v<T,U>
    Triangle4<T>&   Triangle4<T>::operator*=(const Tensor44<U>&rhs) noexcept
    {
        a *= rhs;
        b *= rhs;
        c *= rhs;
        return *this;
    }
    #endif

    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    constexpr Triangle4<quotient_t<T,U>> Triangle4<T>::operator/(U rhs) const noexcept
    {
        return Triangle4<quotient_t<T,U>>(a/rhs, b/rhs, c/rhs);
    }

    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_div_v<T,U>)
    Triangle4<T>& Triangle4<T>::operator/=(U rhs) noexcept
    {
        a /= rhs;
        b /= rhs;
        c /= rhs;
        return *this;
    }

    template <typename T>
    square_t<T>           Triangle4<T>::area() const
    {
        if constexpr (has_sqrt_v<fourth_t<T>>){
            // for 3D and above, we use Heron's formula
            T   sa = edge_a_length();
            T   sb = edge_b_length();
            T   sc = edge_c_length();
            T   s   = middivide(sa+sb+sc);
            return sqrt(s*(s-a)*(s-b)*(s-c));
        
        } else {
            return zero_v<square_t<T>>;
        }
    }
    
    #ifdef YQ_MATH_AXBOX4_HPP
    template <typename T>
    constexpr AxBox4<T>   Triangle4<T>::bounds() const noexcept
    {
        return AxBox4<T>(UNION, { a, b, c });
    }
    #endif
    
    #ifdef YQ_MATH_SEGMENT4_HPP
    template <typename T>
    constexpr Segment4<T>   Triangle4<T>::edge_a() const noexcept
    {
        return Segment4<T>(b, c);
    }
    #endif

    template <typename T>
    constexpr T             Triangle4<T>::edge_a_length() const noexcept
    {
        return (c-b).length();
    }
    
    template <typename T>
    constexpr square_t<T>   Triangle4<T>::edge_a_length²() const noexcept
    {
        return (c-b).length²();
    }
        
    #ifdef YQ_MATH_SEGMENT4_HPP
    template <typename T>
    constexpr Segment4<T>   Triangle4<T>::edge_b() const noexcept
    {
        return Segment4<T>(c, a);
    }
    #endif

    template <typename T>
    constexpr T             Triangle4<T>::edge_b_length() const noexcept
    {
        return (a-c).length();
    }
    
    template <typename T>
    constexpr square_t<T>   Triangle4<T>::edge_b_length²() const noexcept
    {
        return (a-c).length²();
    }

    #ifdef YQ_MATH_SEGMENT4_HPP
    template <typename T>
    constexpr Segment4<T>   Triangle4<T>::edge_c() const noexcept
    {
        return Segment4<T>(a, b);
    }
    #endif

    template <typename T>
    constexpr T             Triangle4<T>::edge_c_length() const noexcept
    {
        return (b-a).length();
    }
    
    template <typename T>
    constexpr square_t<T>   Triangle4<T>::edge_c_length²() const noexcept
    {
        return (b-a).length²();
    }

    template <typename T>
    T       Triangle4<T>::perimeter() const
    {
        return edge_a_length()+edge_b_length()+edge_c_length();
    }

    
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Triangle4<product_t<T,U>> operator*(T lhs, const Triangle4<U>& rhs) noexcept
    {
        return Triangle4<product_t<T,U>>(lhs*rhs.a, lhs*rhs.b, lhs*rhs.c);
    }

    #ifdef YQ_MATH_AXBOX4_HPP
    template <typename T>
    constexpr AxBox4<T>   aabb(const Triangle4<T>& tri) noexcept
    {
        return tri.bounds();
    }
    #endif

    template <typename T>
    T       perimeter(const Triangle4<T>& tri)
    {
        return tri.perimeter();
    }
}
