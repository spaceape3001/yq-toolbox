////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once


/* 
    This is the template IMPLEMENTATION of the triangle3 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <yq/shape/Triangle3.hpp>
#include <yq/shape/TriangleData.hpp>

#include <yq/trait/fourth.hpp>
#include <yq/trait/has_sqrt.hpp>

namespace yq {
    #ifdef YQ_MATH_SEGMENT3_HPP
    template <typename T>
    constexpr Triangle3<T>::Triangle3(const Segment3<T>&seg, const Vector3<T>& c) noexcept : Triangle3(seg.a, seg.b, c) {}
    #endif

    template <typename T>
    constexpr Triangle3<T>::operator TriangleData<Vector3<T>> () const noexcept 
    { 
        return TriangleData<Vector3<T>>( a, b, c ); 
    }

    template <typename T>
    constexpr Triangle3<T> Triangle3<T>::operator+() const noexcept
    {
        return *this;
    }

    template <typename T>
    constexpr Triangle3<T> Triangle3<T>::operator-() const noexcept
    {
        return Triangle3(-a,-b,-c);
    }
    
    template <typename T>
    constexpr Triangle3<T> Triangle3<T>::operator+(const Vector3<T>&rhs) const noexcept
    {
        return Triangle3(a+rhs, b+rhs, c+rhs);
    }

    template <typename T>
    Triangle3<T>& Triangle3<T>::operator+=(const Vector3<T>&rhs) noexcept
    {
        a += rhs;
        b += rhs;
        c += rhs;
        return *this;
    }
    

    template <typename T>
    constexpr Triangle3<T> Triangle3<T>::operator-(const Vector3<T>&rhs) const noexcept
    {
        return Triangle3(a-rhs, b-rhs, c-rhs);
    }

    template <typename T>
    Triangle3<T>& Triangle3<T>::operator-=(const Vector3<T>&rhs) noexcept
    {
        a -= rhs;
        b -= rhs;
        c -= rhs;
        return *this;
    }
    
    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    constexpr Triangle3<product_t<T,U>> Triangle3<T>::operator*(U rhs) const noexcept
    {
        return Triangle3<product_t<T,U>>( a*rhs, b*rhs, c*rhs );
    }
    
    
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
    Triangle3<T>& Triangle3<T>::operator*=(U rhs) noexcept
    {
        a *= rhs;
        b *= rhs;
        c *= rhs;
        return *this;
    }

    #if defined(YQ_MATH_TRIANGLE2_HPP) && defined(YQ_MATH_TENSOR_3_2_HPP)
    template <typename T>
        template <typename U>
    Triangle2<product_t<T,U>>   Triangle3<T>::operator*(const Tensor32<U>&rhs) const noexcept
    {
        return Triangle2<product_t<T,U>>(a*rhs, b*rhs, c*rhs);
    }
    #endif

    #ifdef YQ_MATH_TENSOR_3_3_HPP
    template <typename T>
        template <typename U>
    Triangle3<product_t<T,U>>   Triangle3<T>::operator*(const Tensor33<U>&rhs) const noexcept
    {
        return Triangle3<product_t<T,U>>(a*rhs, b*rhs, c*rhs);
    }
    #endif

    #if defined(YQ_MATH_TRIANGLE4_HPP) && defined(YQ_MATH_TENSOR_3_4_HPP)
    template <typename T>
        template <typename U>
    Triangle4<product_t<T,U>>   Triangle3<T>::operator*(const Tensor34<U>&rhs) const noexcept
    {
        return Triangle4<product_t<T,U>>(a*rhs, b*rhs, c*rhs);
    }
    #endif

    #ifdef YQ_MATH_TENSOR_3_3_HPP
    template <typename T>
        template <typename U>
    requires self_multiply_v<T,U>
    Triangle3<T>&   Triangle3<T>::operator*=(const Tensor33<U>&rhs) noexcept
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
    constexpr Triangle3<quotient_t<T,U>> Triangle3<T>::operator/(U rhs) const noexcept
    {
        return Triangle3<quotient_t<T,U>>(a/rhs, b/rhs, c/rhs);
    }

    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_divide_v<T,U>)
    Triangle3<T>& Triangle3<T>::operator/=(U rhs) noexcept
    {
        a /= rhs;
        b /= rhs;
        c /= rhs;
        return *this;
    }

    
    template <typename T>
    square_t<T>           Triangle3<T>::area() const
    {
        if constexpr (has_sqrt_v<fourth_t<T>>){
            // for 3D and above, we use Heron's formula
            T   sa = edge_a_length();
            T   sb = edge_b_length();
            T   sc = edge_c_length();
            T   s   = middivide(sa+sb+sc);
            return sqrt(s*(s-sa)*(s-sb)*(s-sc));
        
        } else {
            return zero_v<square_t<T>>;
        }
    }

    #ifdef YQ_MATH_AXBOX3_HPP
    template <typename T>
    constexpr AxBox3<T>   Triangle3<T>::bounds() const noexcept
    {
        return AxBox3<T>(UNION, { a, b, c });
    }
    #endif
    
    #ifdef YQ_MATH_SEGMENT3_HPP
    template <typename T>
    constexpr Segment3<T>   Triangle3<T>::edge_a() const noexcept
    {
        return Segment3<T>(b, c);
    }
    #endif

    template <typename T>
    constexpr T             Triangle3<T>::edge_a_length() const noexcept
    {
        return (c-b).length();
    }
    
    template <typename T>
    constexpr square_t<T>   Triangle3<T>::edge_a_length²() const noexcept
    {
        return (c-b).length²();
    }
     
    #ifdef YQ_MATH_SEGMENT3_HPP
    template <typename T>
    constexpr Segment3<T>   Triangle3<T>::edge_b() const noexcept
    {
        return Segment3<T>(c, a);
    }
    #endif

    template <typename T>
    constexpr T             Triangle3<T>::edge_b_length() const noexcept
    {
        return (a-c).length();
    }
    
    template <typename T>
    constexpr square_t<T>   Triangle3<T>::edge_b_length²() const noexcept
    {
        return (a-c).length²();
    }

    #ifdef YQ_MATH_SEGMENT3_HPP
    template <typename T>
    constexpr Segment3<T>   Triangle3<T>::edge_c() const noexcept
    {
        return Segment3<T>(a, b);
    }
    #endif

    template <typename T>
    constexpr T             Triangle3<T>::edge_c_length() const noexcept
    {
        return (b-a).length();
    }
    
    template <typename T>
    constexpr square_t<T>   Triangle3<T>::edge_c_length²() const noexcept
    {
        return (b-a).length²();
    }

    template <typename T>
    T       Triangle3<T>::perimeter() const
    {
        return edge_a_length()+edge_b_length()+edge_c_length();
    }

    #ifdef YQ_MATH_TRIANGLE2_HPP
    template <typename T>
    constexpr Triangle2<T>    Triangle3<T>::xy() const noexcept
    {
        return Triangle2<T>(a.xy(), b.xy(), c.xy());
    }
    #endif
    
    #ifdef YQ_MATH_TRIANGLE2_HPP
    template <typename T>
    constexpr Triangle2<T>    Triangle3<T>::yz() const noexcept
    {
        return Triangle2<T>(a.yz(), b.yz(), c.yz());
    }
    #endif
    
    #ifdef YQ_MATH_TRIANGLE2_HPP
    template <typename T>
    constexpr Triangle2<T>    Triangle3<T>::zx() const noexcept
    {
        return Triangle2<T>(a.zx(), b.zx(), c.zx());
    }
    #endif

    
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Triangle3<product_t<T,U>> operator*(T lhs, const Triangle3<U>& rhs) noexcept
    {
        return Triangle3<product_t<T,U>>(lhs*rhs.a, lhs*rhs.b, lhs*rhs.c);
    }

    #ifdef YQ_MATH_AXBOX3_HPP
    template <typename T>
    constexpr AxBox3<T>   aabb(const Triangle3<T>& tri) noexcept
    {
        return tri.bounds();
    }
    #endif

    #if 0
    #ifdef YQ_MATH_TRIANGLE2_HPP
    template <typename T>
    Triangle2<T>   xy(const Triangle3<T>& a)
    {
        return { xy(a.a), xy(a.b), xy(a.c) };
    }
    #endif
    
    #ifdef YQ_MATH_TRIANGLE2_HPP
    template <typename T>
    Triangle3<T>   xy(const Triangle2<T>& a, std::type_identity_t<T> z)
    {
        return { xy(a.a, z), xy(a.b, z), xy(a.c, z) };
    }
    #endif
    #endif

    template <typename T>
    T       perimeter(const Triangle3<T>& tri)
    {
        return tri.perimeter();
    }

}
