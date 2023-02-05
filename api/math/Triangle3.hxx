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

#include <math/AxBox3.hpp>
#include <math/Tensor32.hpp>
#include <math/Tensor33.hpp>
#include <math/Tensor34.hpp>
#include <math/Triangle2.hpp>
#include <math/Triangle3.hpp>
#include <math/Triangle4.hpp>
#include <math/TriangleData.hpp>


namespace yq {
    template <typename T>
    constexpr Triangle3<T>::Triangle3(const Segment3<T>&seg, const Vector3<T>& c) noexcept : Triangle3(seg.a, seg.b, c) {}

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
    requires trait::is_arithmetic_v<U>
    constexpr Triangle3<product_t<T,U>> Triangle3<T>::operator*(U rhs) const noexcept
    {
        return Triangle3<product_t<T,U>>( a*rhs, b*rhs, c*rhs );
    }
    
    
    template <typename T>
        template <typename U>
    requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Triangle3<T>& Triangle3<T>::operator*=(U rhs) noexcept
    {
        a *= rhs;
        b *= rhs;
        c *= rhs;
        return *this;
    }

    template <typename T>
        template <typename U>
    Triangle2<product_t<T,U>>   Triangle3<T>::operator*(const Tensor32<U>&rhs) const noexcept
    {
        return Triangle2<product_t<T,U>>(a*rhs, b*rhs, c*rhs);
    }

    template <typename T>
        template <typename U>
    Triangle3<product_t<T,U>>   Triangle3<T>::operator*(const Tensor33<U>&rhs) const noexcept
    {
        return Triangle3<product_t<T,U>>(a*rhs, b*rhs, c*rhs);
    }

    template <typename T>
        template <typename U>
    Triangle4<product_t<T,U>>   Triangle3<T>::operator*(const Tensor34<U>&rhs) const noexcept
    {
        return Triangle4<product_t<T,U>>(a*rhs, b*rhs, c*rhs);
    }

    template <typename T>
        template <typename U>
    requires trait::self_mul_v<T,U>
    Triangle3<T>&   Triangle3<T>::operator*=(const Tensor33<U>&rhs) noexcept
    {
        a *= rhs;
        b *= rhs;
        c *= rhs;
        return *this;
    }

    template <typename T>
        template <typename U>
    requires trait::is_arithmetic_v<U>
    constexpr Triangle3<quotient_t<T,U>> Triangle3<T>::operator/(U rhs) const noexcept
    {
        return Triangle3<quotient_t<T,U>>(a/rhs, b/rhs, c/rhs);
    }

    template <typename T>
        template <typename U>
    requires (trait::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Triangle3<T>& Triangle3<T>::operator/=(U rhs) noexcept
    {
        a /= rhs;
        b /= rhs;
        c /= rhs;
        return *this;
    }

    
    template <typename T>
    constexpr AxBox3<T>   Triangle3<T>::bounds() const noexcept
    {
        return AxBox3<T>(UNION, { a, b, c });
    }
    
    template <typename T>
    constexpr Segment3<T>   Triangle3<T>::edge_a() const noexcept
    {
        return Segment3<T>(b, c);
    }

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
        
    template <typename T>
    constexpr Segment3<T>   Triangle3<T>::edge_b() const noexcept
    {
        return Segment3<T>(c, a);
    }

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

    template <typename T>
    constexpr Segment3<T>   Triangle3<T>::edge_c() const noexcept
    {
        return Segment3<T>(a, b);
    }

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

    template <typename T>
    constexpr Triangle2<T>    Triangle3<T>::xy() const noexcept
    {
        return Triangle2<T>(a.xy(), b.xy(), c.xy());
    }
    
    template <typename T>
    constexpr Triangle2<T>    Triangle3<T>::yz() const noexcept
    {
        return Triangle2<T>(a.yz(), b.yz(), c.yz());
    }
    
    template <typename T>
    constexpr Triangle2<T>    Triangle3<T>::zx() const noexcept
    {
        return Triangle2<T>(a.zx(), b.zx(), c.zx());
    }

    
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename T, typename U>
    requires trait::is_arithmetic_v<T>
    constexpr Triangle3<product_t<T,U>> operator*(T lhs, const Triangle3<U>& rhs) noexcept
    {
        return Triangle3<product_t<T,U>>(lhs*rhs.a, lhs*rhs.b, lhs*rhs.c);
    }

    template <typename T>
    constexpr AxBox3<T>   aabb(const Triangle3<T>& tri) noexcept
    {
        return tri.bounds();
    }

    #if 0
    template <typename T>
    Triangle2<T>   xy(const Triangle3<T>& a)
    {
        return { xy(a.a), xy(a.b), xy(a.c) };
    }
    
    template <typename T>
    Triangle3<T>   xy(const Triangle2<T>& a, std::type_identity_t<T> z)
    {
        return { xy(a.a, z), xy(a.b, z), xy(a.c, z) };
    }
    #endif

    template <typename T>
    T       perimeter(const Triangle3<T>& tri)
    {
        return tri.perimeter();
    }

}
