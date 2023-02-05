////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/AxBox2.hpp>
#include <math/Tensor22.hpp>
#include <math/Tensor23.hpp>
#include <math/Tensor24.hpp>
#include <math/Triangle2.hpp>
#include <math/Triangle3.hpp>
#include <math/Triangle4.hpp>
#include <math/TriangleData.hpp>

/* 
    This is the template IMPLEMENTATION of the triangle2 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

namespace yq {
    template <typename T>
    constexpr Triangle2<T>::Triangle2(const Segment2<T>&seg, const Vector2<T>& c) noexcept : Triangle2(seg.a, seg.b, c) {}

    template <typename T>
    constexpr Triangle2<T>::operator TriangleData<Vector2<T>> () const noexcept 
    { 
        return TriangleData<Vector2<T>>( a, b, c ); 
    }

    template <typename T>
    constexpr Triangle2<T> Triangle2<T>::operator+() const noexcept
    {
        return *this;
    }

    template <typename T>
    constexpr Triangle2<T> Triangle2<T>::operator-() const noexcept
    {
        return Triangle2(-a,-b,-c);
    }
    
    template <typename T>
    constexpr Triangle2<T> Triangle2<T>::operator+(const Vector2<T>&rhs) const noexcept
    {
        return Triangle2(a+rhs, b+rhs, c+rhs);
    }

    template <typename T>
    Triangle2<T>& Triangle2<T>::operator+=(const Vector2<T>&rhs) noexcept
    {
        a += rhs;
        b += rhs;
        c += rhs;
        return *this;
    }
    

    template <typename T>
    constexpr Triangle2<T> Triangle2<T>::operator-(const Vector2<T>&rhs) const noexcept
    {
        return Triangle2(a-rhs, b-rhs, c-rhs);
    }

    template <typename T>
    Triangle2<T>& Triangle2<T>::operator-=(const Vector2<T>&rhs) noexcept
    {
        a -= rhs;
        b -= rhs;
        c -= rhs;
        return *this;
    }
    
    template <typename T>
        template <typename U>
    requires trait::is_arithmetic_v<U>
    constexpr Triangle2<trait::product_t<T,U>> Triangle2<T>::operator*(U rhs) const noexcept
    {
        return Triangle2<trait::product_t<T,U>>( a*rhs, b*rhs, c*rhs );
    }
    
    
    template <typename T>
        template <typename U>
    requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Triangle2<T>& Triangle2<T>::operator*=(U rhs) noexcept
    {
        a *= rhs;
        b *= rhs;
        c *= rhs;
        return *this;
    }

    template <typename T>
        template <typename U>
    Triangle2<trait::product_t<T,U>>   Triangle2<T>::operator*(const Tensor22<U>&rhs) const noexcept
    {
        return Triangle2<trait::product_t<T,U>>(a*rhs, b*rhs, c*rhs);
    }

    template <typename T>
        template <typename U>
    Triangle3<trait::product_t<T,U>>   Triangle2<T>::operator*(const Tensor23<U>&rhs) const noexcept
    {
        return Triangle3<trait::product_t<T,U>>(a*rhs, b*rhs, c*rhs);
    }

    template <typename T>
        template <typename U>
    Triangle4<trait::product_t<T,U>>   Triangle2<T>::operator*(const Tensor24<U>&rhs) const noexcept
    {
        return Triangle4<trait::product_t<T,U>>(a*rhs, b*rhs, c*rhs);
    }

    template <typename T>
        template <typename U>
    requires trait::self_mul_v<T,U>
    Triangle2<T>&   Triangle2<T>::operator*=(const Tensor22<U>&rhs) noexcept
    {
        a *= rhs;
        b *= rhs;
        c *= rhs;
        return *this;
    }

    template <typename T>
        template <typename U>
    requires trait::is_arithmetic_v<U>
    constexpr Triangle2<trait::quotient_t<T,U>> Triangle2<T>::operator/(U rhs) const noexcept
    {
        return Triangle2<trait::quotient_t<T,U>>(a/rhs, b/rhs, c/rhs);
    }

    template <typename T>
        template <typename U>
    requires (trait::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Triangle2<T>& Triangle2<T>::operator/=(U rhs) noexcept
    {
        a /= rhs;
        b /= rhs;
        c /= rhs;
        return *this;
    }


    template <typename T>
    constexpr trait::square_t<T>   Triangle2<T>::_area() const noexcept
    {
        return delta_area(b, a) + delta_area(c, b) + delta_area(a, c);
    }

    template <typename T>
    constexpr trait::square_t<T>    Triangle2<T>::area() const noexcept
    {
        return middivide(abs(_area()));
    }
    
    template <typename T>
    constexpr AxBox2<T>   Triangle2<T>::bounds() const noexcept
    {
        return AxBox2<T>(UNION, { a, b, c });
    }
    
    template <typename T>
    constexpr Segment2<T>   Triangle2<T>::edge_a() const noexcept
    {
        return Segment2<T>(b, c);
    }

    template <typename T>
    constexpr T             Triangle2<T>::edge_a_length() const noexcept
    {
        return (c-b).length();
    }
    
    template <typename T>
    constexpr trait::square_t<T>   Triangle2<T>::edge_a_length²() const noexcept
    {
        return (c-b).length²();
    }
        
    template <typename T>
    constexpr Segment2<T>   Triangle2<T>::edge_b() const noexcept
    {
        return Segment2<T>(c, a);
    }

    template <typename T>
    constexpr T             Triangle2<T>::edge_b_length() const noexcept
    {
        return (a-c).length();
    }
    
    template <typename T>
    constexpr trait::square_t<T>   Triangle2<T>::edge_b_length²() const noexcept
    {
        return (a-c).length²();
    }

    template <typename T>
    constexpr Segment2<T>   Triangle2<T>::edge_c() const noexcept
    {
        return Segment2<T>(a, b);
    }

    template <typename T>
    constexpr T             Triangle2<T>::edge_c_length() const noexcept
    {
        return (b-a).length();
    }
    
    template <typename T>
    constexpr trait::square_t<T>   Triangle2<T>::edge_c_length²() const noexcept
    {
        return (b-a).length²();
    }

    template <typename T>
    constexpr bool    Triangle2<T>::is_ccw() const noexcept
    {
        return _area() < zero_v<T>;
    }
    
    template <typename T>
    constexpr bool      Triangle2<T>::is_clockwise() const noexcept
    {
        return _area() > zero_v<T>;
    }
    
    template <typename T>
    T       Triangle2<T>::perimeter() const
    {
        return edge_a_length()+edge_b_length()+edge_c_length();
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename T, typename U>
    requires trait::is_arithmetic_v<T>
    constexpr Triangle2<trait::product_t<T,U>> operator*(T lhs, const Triangle2<U>& rhs) noexcept
    {
        return Triangle2<trait::product_t<T,U>>(lhs*rhs.a, lhs*rhs.b, lhs*rhs.c);
    }

    template <typename T>
    constexpr AxBox2<T>   aabb(const Triangle2<T>& tri) noexcept
    {
        return tri.bounds();
    }

    template <typename T>
    constexpr trait::square_t<T>    area(const Triangle2<T>& tri) noexcept
    {
        return tri.area();
    }

    template <typename T>
    constexpr bool    is_ccw(const Triangle2<T>& tri)noexcept
    {
        return tri.is_ccw();
    }

    template <typename T>
    constexpr bool    is_clockwise(const Triangle2<T>& tri) noexcept
    {
        return tri.is_clockwise();
    }

    template <typename T>
    T       perimeter(const Triangle2<T>& tri)
    {   
        return tri.perimeter();
    }

}
