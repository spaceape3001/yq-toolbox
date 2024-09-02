////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once


/* 
    This is the template IMPLEMENTATION of the quadrilateral2 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <0/math/shape/Quadrilateral2.hpp>
#include <0/math/shape/QuadrilateralData.hpp>

namespace yq {
    #ifdef YQ_MATH_AXBOX2_HPP
    template <typename T>
    constexpr Quadrilateral2<T>::Quadrilateral2(const AxBox2<T>&box) noexcept :
        Quadrilateral2(box.ll(), box.hl(), box.hh(), box.lh()) {}
    #endif
    
    #ifdef YQ_MATH_RECTANGLE2_HPP
    template <typename T>
    constexpr Quadrilateral2<T>::Quadrilateral2(const Rectangle2<T>&rect) noexcept :
        Quadrilateral2(rect.southwest(), rect.southeast(), rect.northeast(), rect.northwest()) {}
    #endif

    template <typename T>
    constexpr Quadrilateral2<T>::operator QuadrilateralData<Vector2<T>>() const noexcept
    {
        return QuadrilateralData<Vector2<T>>( a, b, c, d );
    }

    template <typename T>
    constexpr Quadrilateral2<T> Quadrilateral2<T>::operator+() const noexcept
    {
        return *this;
    }
    
    template <typename T>
    constexpr Quadrilateral2<T> Quadrilateral2<T>::operator-() const noexcept
    {
        return Quadrilateral2<T>( -a, -b, -c, -d );
    }

    template <typename T>
    constexpr Quadrilateral2<T> Quadrilateral2<T>::operator+(const Vector2<T>&rhs) const noexcept
    {
        return Quadrilateral2<T>(a+rhs, b+rhs, c+rhs, d+rhs);
    }

    template <typename T>
    Quadrilateral2<T>& Quadrilateral2<T>::operator+=(const Vector2<T>&rhs) noexcept
    {
        a += rhs;
        b += rhs;
        c += rhs;
        d += rhs;
        return *this;
    }

    template <typename T>
    constexpr Quadrilateral2<T> Quadrilateral2<T>::operator-(const Vector2<T>&rhs) const noexcept
    {
        return Quadrilateral2<T>(a-rhs, b-rhs, c-rhs, d-rhs);
    }

    template <typename T>
    Quadrilateral2<T>& Quadrilateral2<T>::operator-=(const Vector2<T>&rhs) noexcept
    {
        a -= rhs;
        b -= rhs;
        c -= rhs;
        d -= rhs;
        return *this;
    }

    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    constexpr Quadrilateral2<product_t<T,U>>  Quadrilateral2<T>::operator*(U rhs) const noexcept
    {
        return Quadrilateral2<product_t<T,U>>( a*rhs, b*rhs, c*rhs, d*rhs );
    }

    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
    Quadrilateral2<T>& Quadrilateral2<T>::operator*=(U rhs) noexcept
    {
        a *= rhs;
        b *= rhs;
        c *= rhs;
        d *= rhs;
        return *this;
    }

    #ifdef YQ_MATH_TENSOR_2_2_HPP
    template <typename T>
        template <typename U>
    constexpr Quadrilateral2<product_t<T,U>>  Quadrilateral2<T>::operator*(const Tensor22<U>&rhs) const noexcept
    {
        return Quadrilateral2<product_t<T,U>>( a*rhs, b*rhs, c*rhs, d*rhs );
    }
    #endif

    #ifdef YQ_MATH_TENSOR_2_2_HPP
    template <typename T>
        template <typename U>
    requires self_multiply_v<T,U>
    Quadrilateral2<T>& Quadrilateral2<T>::operator*=(const Tensor22<U>&rhs) noexcept
    {
        a *= rhs;
        b *= rhs;
        c *= rhs;
        d *= rhs;
        return *this;
    }
    #endif


    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    constexpr Quadrilateral2<quotient_t<T,U>>  Quadrilateral2<T>::operator/(U rhs) const noexcept
    {
        return Quadrilateral2<quotient_t<T,U>>( a/rhs, b/rhs, c/rhs, d/rhs );
    }

    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_divide_v<T,U>)
    Quadrilateral2<T>& Quadrilateral2<T>::operator/=(U rhs) noexcept
    {
        a /= rhs;
        b /= rhs;
        c /= rhs;
        d /= rhs;
        return *this;
    }

    template <typename T>
    constexpr square_t<T> Quadrilateral2<T>::_area() const noexcept
    {
        return delta_area(b, a) + delta_area(c, b) + delta_area(d, c) + delta_area(a, d);
    }

    template <typename T>
    constexpr square_t<T> Quadrilateral2<T>::area() const noexcept
    {
        return middivide(abs(_area()));
    }

    #ifdef YQ_MATH_AXBOX2_HPP
    template <typename T>
    constexpr AxBox2<T>   Quadrilateral2<T>::bounds() const noexcept 
    {
        return AxBox2<T>(UNION, { a, b, c, d });
    }
    #endif

    template <typename T>
    constexpr bool      Quadrilateral2<T>::is_ccw() const noexcept
    {
        return _area() < zero_v<square_t<T>>;
    }

    template <typename T>
    constexpr bool      Quadrilateral2<T>::is_clockwise() const noexcept
    {
        return _area() > zero_v<square_t<T>>;
    }

    template <typename T>
    T         Quadrilateral2<T>::perimeter() const
    {
        return (b-a).length() + (c-b).length() + (d-c).length() + (a-d).length();
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    #ifdef YQ_MATH_AXBOX2_HPP
    template <typename T>
    Quadrilateral2<T> quadrilateral(const AxBox2<T>& ax)
    {
        return Quadrilateral2<T>(ax);
    }
    #endif

    #ifdef YQ_MATH_RECTANGLE2_HPP
    template <typename T>
    Quadrilateral2<T> quadrilateral(const Rectangle2<T>& rect)
    {
        return Quadrilateral2<T>(rect);
    }
    #endif

    template <typename T, typename U>
    constexpr Quadrilateral2<product_t<T,U>> operator*(T lhs, const Quadrilateral2<U>&rhs) noexcept
    {
        return Quadrilateral2<product_t<T,U>>(lhs * rhs.a, lhs * rhs.b, lhs * rhs.c, lhs * rhs.d);
    }

    #ifdef YQ_MATH_AXBOX2_HPP
    template <typename T>
    AxBox2<T>   aabb(const Quadrilateral2<T>& quad)
    {
        return quad.bounds();
    }
    #endif

    template <typename T>
    square_t<T>    area(const Quadrilateral2<T>& quad)
    {
        return quad.area();
    }

    template <typename T>
    bool    is_ccw(const Quadrilateral2<T>& quad)
    {
        return quad.is_ccw();
    }

    template <typename T>
    T       perimeter(const Quadrilateral2<T>& quad)
    {
        return quad.perimeter();
    }
}
