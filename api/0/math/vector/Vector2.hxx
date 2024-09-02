////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_VECTOR_2_HXX 1

/* 
    This is the template IMPLEMENTATION of the vector2 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <0/math/vector/Vector2.hpp>

#include <yq/math/tolerance/Absolute.hpp>
#include <yq/math/AllComponents.hpp>
#include <yq/math/AnyComponents.hpp>

#include <0/math/trig.hpp>
#include <0/math/utility.hpp>


namespace yq {
    #ifdef YQ_MATH_SIZE2_HPP
    template <typename T>
    constexpr Vector2<T>::Vector2(const Size2<T>&v) noexcept : Vector2(v.x, v.y)
    {
    }
    #endif

    #ifdef YQ_USE_GLM
    template <typename T>
    constexpr Vector2<T>::operator glm::vec<2, T, glm::defaultp>() const noexcept
    {
        return glm::vec<2, T, glm::defaultp>( x, y );
    }
    #endif

    //! Negation (negative) operator
    template <typename T>
    constexpr Vector2<T> Vector2<T>::operator-() const noexcept
    {
        return Vector2(-x,-y);
    }

    template <typename T>
    Vector2<quotient_t<T,T>> Vector2<T>::operator~() const
    {
        auto l = one_v<T>/length();
        return Vector2<quotient_t<T,T>>(x*l, y*l);
    }

    template <typename T>
    constexpr square_t<T> Vector2<T>::operator^(two_t) const noexcept
    {
        return x*x + y*y;
    }    

    template <typename T>
    constexpr Multivector2<T> Vector2<T>::operator+(T b) const noexcept
    {
        return Multivector2<T>(
            b, 
            x, y, 
            zero_v<T> 
        );
    }
    
    #ifdef YQ_MATH_AXBOX2_HPP
    template <typename T>
    constexpr AxBox2<T> Vector2<T>::operator+(const AxBox2<T>&b) const noexcept
    {
        return AxBox2<T>(*this + b.lo, *this + b.hi);
    }
    #endif

    #if defined(YQ_MATH_BIVECTOR2_HPP) && defined(YQ_MATH_MULTIVECTOR2_HPP)
    template <typename T>
    constexpr Multivector2<T> Vector2<T>::operator+(const Bivector2<T>& b) const noexcept
    {
        return Multivector2<T>(
            zero_v<T>, 
            x, y, 
            b.xy 
        );
    }
    #endif

    #ifdef YQ_MATH_CIRCLE2_HPP
    template <typename T>
    constexpr Circle2<T> Vector2<T>::operator+(const Circle2<T>&b) const noexcept
    {
        return Circle2<T>(*this + b.point, b.radius);
    }
    #endif
    
    #ifdef YQ_MATH_MULTIVECTOR2_HPP
    template <typename T>
    constexpr Multivector2<T> Vector2<T>::operator+(const Multivector2<T>& b) const noexcept
    {
        return Multivector2<T>(
            b.a, 
            x+b.x, y+b.y,
            b.xy
        );
    }
    #endif

    #ifdef YQ_MATH_POLYGON2_HPP
    template <typename T>
    Polygon2<T> Vector2<T>::operator+(const Polygon2<T>&b) const
    {
        return Polygon2<T>(*this + span(b.vertex));
    }
    #endif

    #ifdef YQ_MATH_POLYLINE2_HPP
    template <typename T>
    Polyline2<T> Vector2<T>::operator+(const Polyline2<T>&b) const
    {
        return Polyline2<T>(*this + span(b.vertex));
    }
    #endif

    #ifdef YQ_MATH_QUADRILATERAL2_HPP
    template <typename T>
    constexpr Quadrilateral2<T>   Vector2<T>::operator+(const Quadrilateral2<T>&b) const noexcept
    {
        return Quadrilateral2<T>(*this + b.a, *this + b.b, *this + b.c, *this + b.d);
    }
    #endif

    #ifdef YQ_MATH_RECTANGLE2_HPP
    template <typename T>
    constexpr Rectangle2<T> Vector2<T>::operator+(const Rectangle2<T>&b) const noexcept
    {
        return Rectangle2<T>(*this+b.pos, b.size);
    }
    #endif

    #ifdef YQ_MATH_SEGMENT2_HPP
    template <typename T>
    constexpr Segment2<T> Vector2<T>::operator+(const Segment2<T>&rhs) const noexcept
    {
        return Segment2<T>( *this + rhs.a, *this + rhs.b );
    }
    #endif

    #if defined(YQ_MATH_RECTANGLE2_HPP) && defined(YQ_MATH_SIZE2_HPP)
    template <typename T>
    constexpr Rectangle2<T> Vector2<T>::operator+(const Size2<T>&b) const noexcept
    {
        return Rectangle2<T>(*this, b);
    }
    #endif

    #ifdef YQ_MATH_TRIANGLE2_HPP
    template <typename T>
    constexpr Triangle2<T> Vector2<T>::operator+(const Triangle2<T>&rhs) const noexcept
    {
        return Triangle2<T>(*this+rhs.a, *this+rhs.b, *this+rhs.c);
    }
    #endif

    template <typename T>
    constexpr Vector2<T> Vector2<T>::operator+(const Vector2& b) const noexcept
    {
        return Vector2(x+b.x, y+b.y);
    }
    
    template <typename T>
    Vector2<T>& Vector2<T>::operator+=(const Vector2& b) noexcept
    {
        x += b.x;
        y += b.y;
        return *this;
    }

    template <typename T>
    std::vector<Vector2<T>> Vector2<T>::operator+(std::span<const Vector2>bs) const
    {
        return transform(bs, [&](const Vector2<T>& b) -> Vector2<T> {
            return *this + b;
        });
    }

    #ifdef YQ_MATH_MULTIVECTOR2_HPP
    template <typename T>
    constexpr Multivector2<T> Vector2<T>::operator-(T b) const noexcept
    {
        return { 
            -b, 
            x, y, 
            zero_v<T>
        };
    }
    #endif
    
    #ifdef YQ_MATH_AXBOX2_HPP
    template <typename T>
    constexpr AxBox2<T> Vector2<T>::operator-(const AxBox2<T>&b) const noexcept
    {
        return AxBox2<T>(*this - b.hi, *this - b.lo);
    }
    #endif

    #if defined(YQ_MATH_BIVECTOR2_HPP) && defined(YQ_MATH_MULTIVECTOR2_HPP)
    template <typename T>
    constexpr Multivector2<T> Vector2<T>::operator-(const Bivector2<T>& b) const noexcept
    {
        return { 
            zero_v<T>, 
            x, y, 
            -b.xy 
        };
    }
    #endif

    #ifdef YQ_MATH_CIRCLE2_HPP
    template <typename T>
    constexpr Circle2<T> Vector2<T>::operator-(const Circle2<T>&b) const noexcept
    {
        return Circle2<T>(*this - b.point, b.radius);
    }
    #endif

    #ifdef YQ_MATH_MULTIVECTOR2_HPP
    template <typename T>
    constexpr Multivector2<T> Vector2<T>::operator-(const Multivector2<T>& b) const noexcept
    {
        return { 
            -b.a, 
            x-b.x, y-b.y,
            -b.xy
        };
    }
    #endif

    #ifdef YQ_MATH_POLYGON2_HPP
    template <typename T>
    Polygon2<T> Vector2<T>::operator-(const Polygon2<T>&b) const
    {
        return Polygon2<T>(*this - span(b.vertex));
    }
    #endif

    #ifdef YQ_MATH_POLYLINE2_HPP
    template <typename T>
    Polyline2<T> Vector2<T>::operator-(const Polyline2<T>&b) const
    {
        return Polygon2<T>(*this - span(b.vertex));
    }
    #endif

    #ifdef YQ_MATH_QUADRILATERAL2_HPP
    template <typename T>
    constexpr Quadrilateral2<T>   Vector2<T>::operator-(const Quadrilateral2<T>&b) const noexcept
    {
        return Quadrilateral2<T>(*this - b.a, *this - b.b, *this - b.c, *this - b.d);
    }
    #endif

    #ifdef YQ_MATH_SEGMENT2_HPP
    template <typename T>
    constexpr Segment2<T> Vector2<T>::operator-(const Segment2<T>&rhs) const noexcept
    {
        return Segment2<T>( *this - rhs.a, *this - rhs.b );
    }
    #endif

    #ifdef YQ_MATH_TRIANGLE2_HPP
    template <typename T>
    constexpr Triangle2<T> Vector2<T>::operator-(const Triangle2<T>&rhs) const noexcept
    {
        return Triangle2<T>(*this-rhs.a, *this-rhs.b, *this-rhs.c);
    }
    #endif

    template <typename T>
    constexpr Vector2<T> Vector2<T>::operator-(const Vector2& b) const noexcept
    {
        return Vector2(x-b.x, y-b.y);
    }


    template <typename T>
    Vector2<T>& Vector2<T>::operator-=(const Vector2& b) noexcept
    {
        x -= b.x;
        y -= b.y;
        return *this;
    }

    template <typename T>
    std::vector<Vector2<T>> Vector2<T>::operator-(std::span<const Vector2>bs) const 
    {
        return transform(bs, [&](const Vector2<T>& b) -> Vector2<T> {
            return *this - b;
        });
    }

    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U>)
    constexpr Vector2<product_t<T,U>> Vector2<T>::operator*(U b) const noexcept
    {
        return Vector2<product_t<T,U>>(x*b, y*b);
    }

    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
    Vector2<T>& Vector2<T>::operator*=(U b) noexcept
    {
        x *= b;
        y *= b;
        return *this;
    }
    
    #if defined(YQ_MATH_VECTOR_1_HPP) && defined(YQ_MATH_TENSOR_2_1_HPP)
    template <typename T>
        template <typename U>
    constexpr Vector1<product_t<T,U>> Vector2<T>::operator*(const Tensor21<U>&b) const noexcept
    {
        return Vector1<product_t<T,U>>(
            x*b.xx + y*b.yx
        );
    }
    #endif

    #ifdef YQ_MATH_TENSOR_2_2_HPP
    template <typename T>
        template <typename U>
    constexpr Vector2<product_t<T,U>> Vector2<T>::operator*(const Tensor22<U>&b) const noexcept
    {
        return Vector2<product_t<T,U>>(
            x*b.xx + y*b.yx,
            x*b.xy + y*b.yy
        );
    }
    #endif

    #ifdef YQ_MATH_TENSOR_2_2_HPP
    template <typename T>
        template <typename U>
    requires self_multiply_v<T,U>
    Vector2<T>&  Vector2<T>::operator*=(const Tensor22<U>&b) noexcept
    {
        *this = *this * b;
        return *this;
    }
    #endif

    #if defined(YQ_MATH_VECTOR_3_HPP) && defined(YQ_MATH_TENSOR_2_3_HPP)
    template <typename T>
        template <typename U>
    constexpr Vector3<product_t<T,U>> Vector2<T>::operator*(const Tensor23<U>&b) const noexcept
    {
        return Vector3<product_t<T,U>>(
            x*b.xx + y*b.yx,
            x*b.xy + y*b.yy,
            x*b.xz + y*b.yz
        );
    }
    #endif

    #if defined(YQ_MATH_VECTOR_4_HPP) && defined(YQ_MATH_TENSOR_2_4_HPP)
    template <typename T>
        template <typename U>
    constexpr Vector4<product_t<T,U>> Vector2<T>::operator*(const Tensor24<U>&b) const noexcept
    {
        return Vector4<product_t<T,U>>(
            x*b.xx + y*b.yx,
            x*b.xy + y*b.yy,
            x*b.xz + y*b.yz,
            x*b.xw + y*b.yw
        );
    }
    #endif

    #ifdef YQ_MATH_MULTIVECTOR2_HPP
    template <typename T>
        template <typename U>
    constexpr Multivector2<product_t<T,U>> Vector2<T>::operator*(const Vector2<U>&b) const noexcept
    {
        return Multivector2<product_t<T,U>>( x*b.x+y*b.y, zero_v<product_t<T,U>>, zero_v<product_t<T,U>>, x*b.y-y*b.x );
    }
    #endif

    template <typename T>
        template <typename U>
    constexpr product_t<T,U> Vector2<T>::operator DOT (const Vector2<U>&b) const noexcept
    {
        return x*b.x + y*b.y;
    }

    template <typename T>
        template <typename U>
    constexpr product_t<T,U> Vector2<T>::operator CROSS (const Vector2<U>&b) const noexcept
    {
        return x*b.y-y*b.x;
    }

    template <typename T>
        template <typename U>
    constexpr product_t<T,U> Vector2<T>::operator INNER (const Vector2<U>&b) const noexcept
    {
        return x*b.x + y*b.y;
    }

    #ifdef YQ_MATH_BIVECTOR2_HPP
    template <typename T>
        template <typename U>
    constexpr Bivector2<product_t<T,U>> Vector2<T>::operator OUTER (const Vector2<U>& b) const noexcept
    {
        return Bivector2<product_t<T,U>>( x*b.y-y*b.x );
    }
    #endif

    #if defined(YQ_MATH_VECTOR_1_HPP) && defined(YQ_MATH_TENSOR_2_1_HPP)
    template <typename T>
        template <typename U>
    constexpr Tensor21<product_t<T,U>> Vector2<T>::operator OTIMES(const Vector1<U>&b) const noexcept
    {
        return Tensor21<product_t<T,U>>(
            x+b.x,
            y+b.x
        );
    }
    #endif

    #ifdef YQ_MATH_TENSOR_2_2_HPP
    template <typename T>
        template <typename U>
    constexpr Tensor22<product_t<T,U>> Vector2<T>::operator OTIMES(const Vector2<U>&b) const noexcept
    {
        return Tensor22<product_t<T,U>>(
            x+b.x, x+b.y,
            y+b.x, y+b.y
        );
    }
    #endif

    #if defined(YQ_MATH_VECTOR_3_HPP) && defined(YQ_MATH_TENSOR_2_3_HPP)
    template <typename T>
        template <typename U>
    constexpr Tensor23<product_t<T,U>> Vector2<T>::operator OTIMES(const Vector3<U>&b) const noexcept
    {
        return Tensor23<product_t<T,U>>(
            x+b.x, x+b.y, x+b.z,
            y+b.x, y+b.y, y+b.z
        );
    }
    #endif
    
    #if defined(YQ_MATH_VECTOR_4_HPP) && defined(YQ_MATH_TENSOR_2_4_HPP)
    template <typename T>
        template <typename U>
    constexpr Tensor24<product_t<T,U>> Vector2<T>::operator OTIMES(const Vector4<U>&b) const noexcept
    {
        return Tensor24<product_t<T,U>>(
            x+b.x, x+b.y, x+b.z, x+b.w,
            y+b.x, y+b.y, y+b.z, y+b.w
        );
    }
    #endif

    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U>)
    constexpr  Vector2<quotient_t<T,U>> Vector2<T>::operator/(U b) const noexcept
    {
        return Vector2<product_t<T,U>>(x / b, y / b);
    }

    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_divide_v<T,U>)
    Vector2<T>& Vector2<T>::operator/=(U b) noexcept
    {
        x /= b;
        y /= b;
        return *this;
    }

    //! Division of left vector by the right
    template <typename T>
        template <typename U>
    constexpr Multivector2<quotient_t<T,U>>   Vector2<T>::operator/ (const Vector2<U>&b) const noexcept
    {
        return (*this * b) / b.length²();
    }

    //! Union
    #ifdef YQ_MATH_AXBOX2_HPP
    template <typename T>
    constexpr AxBox2<T> Vector2<T>::operator|(const AxBox2<T>&b) const noexcept
    {
        return AxBox2<T>(UNION, {*this, b.lo, b.hi});
    }
    #endif

    #ifdef YQ_MATH_AXBOX2_HPP
    template <typename T>
    constexpr AxBox2<T> Vector2<T>::operator|(const Vector2&b) const noexcept
    {
        return AxBox2<T>(UNION, *this, b);
    }
    #endif

    template <typename T>
    constexpr Vector2<T> Vector2<T>::all_add(T b) const noexcept
    {
        return Vector2( x+b, y+b );
    }
    
    template <typename T>
    Vector2<T>&    Vector2<T>::all_decrement(T b) noexcept
    {
        x -= b;
        y -= b;
        return *this;
    }

    template <typename T>
    Vector2<T>&    Vector2<T>::all_increment(T b) noexcept
    {
        x += b;
        y += b;
        return *this;
    }

    template <typename T>
    constexpr Vector2<T> Vector2<T>::all_subtract(T b) const noexcept
    {
        return Vector2( x-b, y-b );
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Vector2<T>::all_test(Pred pred) const noexcept
    {
        return pred(x) && pred(y);
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Vector2<T>::all_test(const Vector2& b, Pred pred) const noexcept
    {
        return pred(x, b.x) && pred(y, b.y);
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Vector2<T>::all_test(T b, Pred pred) const noexcept
    {
        return pred(x, b) && pred(y, b);
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Vector2<T>::any_test(Pred pred) const noexcept
    {
        return pred(x) || pred(y);
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Vector2<T>::any_test(const Vector2& b, Pred pred) const noexcept
    {
        return pred(x, b.x) || pred(y, b.y);
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Vector2<T>::any_test(T b, Pred pred) const noexcept
    {
        return pred(x, b) || pred(y, b);
    }
        
    template <typename T>
        template <typename R>
    bool Vector2<T>::close(const Vector2&b, R compare) const 
    {
        return compare((*this-b).length(), b.length());
    }

    template <typename T>
    constexpr T     Vector2<T>::cmax() const noexcept
    {
        return max(x, y);
    }

    template <typename T>
    constexpr T     Vector2<T>::cmin() const noexcept
    {
        return min(x, y);
    }

    template <typename T>
    constexpr square_t<T>     Vector2<T>::cproduct() const noexcept
    {
        return x*y;
    }

    template <typename T>
    constexpr T   Vector2<T>::csum() const noexcept
    {
        return x + y;
    }

    template <typename T>
    constexpr Vector2<T>   Vector2<T>::eabs() const noexcept
    {
        return Vector2( abs(x), abs(y) );
    }

    template <typename T>
        template <typename U>
    constexpr Vector2<quotient_t<T,U>>    Vector2<T>::ediv(const Vector2<U>&b) const noexcept
    {
        return Vector2<quotient_t<T,U>>(x/b.x, y/b.y);
    }

    template <typename T>
    constexpr Vector2<T>   Vector2<T>::emax(const Vector2&b) const noexcept
    {
        return Vector2(max(x, b.x), max(y, b.y));
    }

    template <typename T>
    constexpr Vector2<T>   Vector2<T>::emax(T b) const noexcept
    {
        return Vector2(max(x, b), max(y, b));
    }

    template <typename T>
    constexpr Vector2<T>   Vector2<T>::emin(const Vector2&b) const noexcept
    {
        return Vector2(min(x, b.x), min(y, b.y));
    }

    template <typename T>
    constexpr Vector2<T>   Vector2<T>::emin(T b) const noexcept
    {
        return Vector2(min(x, b), min(y, b));
    }

    template <typename T>
        template <typename U>
    constexpr Vector2<product_t<T,U>>    Vector2<T>::emul(const Vector2<U>&b) const noexcept
    {
        return Vector2<product_t<T,U>>(x*b.x, y*b.y);
    }

    template <typename T>
    constexpr square_t<T> Vector2<T>::length²() const noexcept
    {
        return x*x + y*y;
    }    
    
    template <typename T>
    T       Vector2<T>::length() const
    {
        if constexpr (has_sqrt_v<square_t<T>>)
            return sqrt(length²());
        return {};
    }

    template <typename T>
    constexpr Vector3<T> Vector2<T>::z(T _z) const noexcept
    {
        return Vector3<T>( x, y, _z );
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    #ifdef YQ_MATH_MULTIVECTOR2_HPP
    template <typename T>
    constexpr Multivector2<T> operator+(T a, const Vector2<T>& b) noexcept
    {
        return Multivector2<T>(
            a, 
            b.x, b.y, 
            {} 
        );
    }
    #endif

    template <typename T>
    std::vector<Vector2<T>>   operator+(std::span<const Vector2<T>>as, Vector2<T>b)
    {
        return transform(as, [&](const Vector2<T>&a) -> Vector2<T> {
            return a + b;
        });
    }

    #ifdef YQ_MATH_MULTIVECTOR2_HPP
    template <typename T>
    constexpr Multivector2<T> operator-(T a, const Vector2<T>& b) noexcept
    {
        return Multivector2<T>(
            a, 
            -b.x, -b.y, 
            {} 
        );
    }
    #endif

    template <typename T>
    std::vector<Vector2<T>>   operator-(std::span<const Vector2<T>>as, Vector2<T>b)
    {
        return transform(as, [&](const Vector2<T>&a) -> Vector2<T> {
            return a - b;
        });
    }

    template <typename T, typename U>
    requires (is_arithmetic_v<T>)
    constexpr Vector2<product_t<T,U>> operator*(T a, const Vector2<U>&b) noexcept
    {
        return Vector2<product_t<T,U>>(a*b.x, a*b.y);
    }

    template <typename T, typename U>
    requires (is_arithmetic_v<T>)
    std::vector<Vector2<product_t<T,U>>>   operator*(T a, std::span<const Vector2<U>>bs)
    {
        return transform(bs, [&](const Vector2<U>&b) -> Vector2<product_t<T,U>> {
            return a * b;
        });
    }

    template <typename T, typename U>
    requires (is_arithmetic_v<U>)
    std::vector<Vector2<product_t<T,U>>>   operator*(std::span<const Vector2<T>>as, U b)
    {
        return transform(as, [&](const Vector2<T>&a) -> Vector2<product_t<T,U>> {
            return a * b;
        });
    }

    #if defined(YQ_MATH_TENSOR_2_1_HPP) && defined(YQ_MATH_VECTOR_1_HPP)
    template <typename T, typename U>
    std::vector<Vector1<product_t<T,U>>> operator*(std::span<const Vector2<T>>as, const Tensor21<U>&b)
    {
        return transform(as, [&](const Vector2<T>&v) -> Vector1<product_t<T,U>>{
            return v * b;
        });
    }
    #endif
    
    #ifdef YQ_MATH_TENSOR_2_2_HPP
    template <typename T, typename U>
    std::vector<Vector2<product_t<T,U>>> operator*(std::span<const Vector2<T>>as, const Tensor22<U>&b)
    {
        return transform(as, [&](const Vector2<T>&v) -> Vector2<product_t<T,U>>{
            return v * b;
        });
    }
    #endif

    #if defined(YQ_MATH_TENSOR_2_3_HPP) && defined(YQ_MATH_VECTOR_3_HPP)
    template <typename T, typename U>
    std::vector<Vector3<product_t<T,U>>> operator*(std::span<const Vector2<T>>as, const Tensor23<U>&b)
    {
        return transform(as, [&](const Vector2<T>&v) -> Vector3<product_t<T,U>>{
            return v * b;
        });
    }
    #endif
    
    #if defined(YQ_MATH_TENSOR_2_4_HPP) && defined(YQ_MATH_VECTOR_4_HPP)
    template <typename T, typename U>
    std::vector<Vector4<product_t<T,U>>> operator*(std::span<const Vector2<T>>as, const Tensor24<U>&b)
    {
        return transform(as, [&](const Vector2<T>&v) -> Vector4<product_t<T,U>>{
            return v * b;
        });
    }
    #endif

    template <typename T, typename U>
    requires (is_arithmetic_v<T>)
    constexpr  Vector2<quotient_t<T,U>> operator/(T a, const  Vector2<U>&b) noexcept
    {
        return (a*b) / b.length²();
    }

    template <typename T, typename U>
    requires (is_arithmetic_v<U>)
    std::vector<Vector2<quotient_t<T,U>>>   operator/(std::span<const Vector2<T>>as, U b)
    {
        return transform(as, [&](const Vector2<T>&a) -> Vector2<quotient_t<T,U>> {
            return a / b;
        });
    }

    template <typename T>
    constexpr Vector2<T>   abs_elem(const Vector2<T>&a) noexcept
    {
        return a.eabs();
    }

    template <typename T>
    AllComponents<Vector2<T>>   all(Vector2<T>& val)
    {
        return { val };
    }

    template <typename T>
    AllComponents<const Vector2<T>>   all(const Vector2<T>& val)
    {
        return { val };
    }

    template <typename T>
    requires (std::is_floating_point_v<T> && has_sqrt_v<T>)
    Radian       angle(const Vector2<T>&a, const Vector2<T>& b)
    {
        return acos( std::clamp<T>( (a*b)/(length(a)*length(b)), -one_v<T>, one_v<T>));
    }


    template <typename T, typename DIM1, typename DIM2>
    requires (std::is_floating_point_v<T> && has_sqrt_v<T>)
    Radian      angle(const Vector2<MKS<T,DIM1>>&a, const Vector2<MKS<T,DIM2>>& b)
    {
        using one_t = MKS<T,dim::None>;
        return acos( std::clamp<one_t>( (a*b)/(length(a)*length(b)), -one_v<T>, one_v<T>));
    }

    template <typename T>
    AnyComponents<Vector2<T>>   any(Vector2<T>& val)
    {
        return { val };
    }
    
    template <typename T>
    AnyComponents<const Vector2<T>>   any(const Vector2<T>& val)
    {
        return { val };
    }

    inline Vector2D     ccw(Radian az)
    {
        return Vector2D(cos(az), sin(az) );
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    Radian   ccw(const Vector2<T>& a)
    {
        return atan(a.y, a.x);
    }

    template <typename T, typename DIM>
    requires std::is_floating_point_v<T>
    Radian   ccw(const Vector2<MKS<T,DIM>>& a)
    {
        return atan(a.y, a.x);
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    MKS<T,dim::Angle>   clockwise(const Vector2<T>& a)
    {
        return atan(a.y, a.x);
    }

    template <typename T, typename DIM>
    requires std::is_floating_point_v<T>
    MKS<T,dim::Angle>   clockwise(const Vector2<MKS<T,DIM>>& a)
    {
        return atan(a.y, a.x);
    }

    inline Vector2D     clockwise(Radian az)
    {
        return Vector2D( sin(az), cos(az) );
    }

    template <typename T>
    constexpr T             component_max(const Vector2<T>&a) noexcept
    {
        return a.cmax();
    }

    template <typename T>
    constexpr T             component_min(const Vector2<T>&a) noexcept
    {
        return a.cmin();
    }

    template <typename T>
    constexpr square_t<T>     component_product(const Vector2<T>& a) noexcept
    {
        return a.cproduct();
    }

    template <typename T>
    constexpr T   component_sum(const Vector2<T>& a) noexcept
    {
        return a.csum();
    }

    template <typename T>
    constexpr square_t<T>    delta_area(const Vector2<T>&a, const Vector2<T>& b) noexcept
    {
        return a.x*b.y-a.y*b.x;
    }

    template <typename T>
    constexpr square_t<T>    delta_area(const std::span<Vector2<T>>& vertex) noexcept
    {
        if(vertex.empty())
            return square_t<T>{};

        size_t  n   = vertex.size();
        square_t<T> ret = delta_area(vertex[n-1],vertex[0]);
        --n;
        for(size_t i=0;i<n;++n)
            ret += delta_area(vertex[i], vertex[i+1]);
        return ret;
    }

    template <typename T, typename U>
    constexpr Vector2<quotient_t<T,U>>    div_elem(const Vector2<T>&a, const Vector2<U>&b) noexcept
    {
        return a.ediv(b);
    }

    #if 0
    template <typename T>
    ElemComponents<Vector2<T>>   elem(Vector2<T>& val)
    {
        return { val };
    }

    template <typename T>
    ElemComponents<const Vector2<T>>   elem(const Vector2<T>& val)
    {
        return { val };
    }
    #endif


    template <typename T, typename R>
    bool is_close(const R& compare, const Vector2<T>& actual, const Vector2<T>& expected)
    {
        return compare(length(actual-expected), length(expected));
    }

    template <typename T, typename R>
    bool is_close(const R& compare, const Vector2<T>& actual, std::type_identity_t<T> x, std::type_identity_t<T> y)
    {
        return is_close(compare, actual, Vector2<T>(x, y) );
    }

    /*! \brief Square of the vector's length
    
        This returns the SQUARE of the given vector's length.
    */
    template <typename T>
    constexpr square_t<T> length²(const Vector2<T>& vec) noexcept
    {
        return vec.length²();
    }    

    /*! \brief Length of the vector
        
        This returns the length of the given vector.
    */
    template <typename T>
    requires has_sqrt_v<T>
    auto    length(const Vector2<T>& a)
    {
        return sqrt(length²(a));
    }

    template <typename T>
    constexpr Vector2<T>   max_elem(const Vector2<T>&a, const Vector2<T>&b) noexcept
    {
        return a.emax(b);
    }

    template <typename T>
    constexpr Vector2<T>   max_elem(std::initializer_list<Vector2<T>> vs) noexcept
    {
        return max_elem(std::span<const Vector2<T>>(vs.data(), vs.size()));
    }

    template <typename T>
    constexpr Vector2<T>   max_elem(std::span<const Vector2<T>>vs) noexcept
    {
        if(vs.empty())
            return Vector2<T>(NAN);
        return Vector2<T>(
            std::max_element(vs.begin(), vs.end(), Vector2<T>::less_x) -> x,
            std::max_element(vs.begin(), vs.end(), Vector2<T>::less_y) -> y
        );
    }


    /*! \brief Mid-way divide two vectors
    */
    template <typename T>
    constexpr Vector2<T>  midvector(const Vector2<T>& a, const Vector2<T>& b) noexcept
    {
        if constexpr (has_ieee754_v<T>)
            return ieee754_t<T>(0.5)*(a+b);
        else if constexpr (std::is_integral_v<T>)
            return (a+b) / T(2);
        else
            return {};
    }

    template <typename T>
    constexpr Vector2<T>   min_elem(const Vector2<T>&a, const Vector2<T>&b) noexcept
    {
        return a.emin(b);
    }

    template <typename T>
    constexpr Vector2<T>   min_elem(std::initializer_list<Vector2<T>>vs) noexcept
    {
        return min_elem(std::span<const Vector2<T>>(vs.data(), vs.size()));
    }

    template <typename T>
    constexpr Vector2<T>   min_elem(std::span<const Vector2<T>>vs) noexcept
    {
        if(vs.empty())
            return Vector2<T>(NAN);
        return Vector2<T>(
            std::min_element(vs.begin(), vs.end(), Vector2<T>::less_x) -> x,
            std::min_element(vs.begin(), vs.end(), Vector2<T>::less_y) -> y
        );
    }

    template <typename T, typename U>
    constexpr Vector2<product_t<T,U>>    mul_elem(const Vector2<T>&a, const Vector2<U>&b) noexcept
    {
        return a.emul(b);
    }

    template <typename S, typename T>
    S&  as_stream(S& s, const Vector2<T>& v)
    {
        return s << "(" << v.x << "," << v.y << ")";
    }
    
    #ifdef YQ_BASIC_STREAM_HPP_
    template <typename T>
    Stream& operator<<(Stream&s, const Vector2<T>& v)
    {
        return as_stream(s, v);
    }
    #endif

    #ifdef _LOG4CPP_CATEGORYSTREAM_HH
    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const Vector2<T>& v)
    {
        return as_stream(s, v);
    }
    #endif
}
