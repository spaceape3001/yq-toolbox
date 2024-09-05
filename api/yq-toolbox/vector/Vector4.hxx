////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_VECTOR_4_HXX 1

/* 
    This is the template IMPLEMENTATION of the vector4 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <yq-toolbox/vector/Vector4.hpp>
#include <yq-toolbox/math/trigonometry.hpp>
#include <yq-toolbox/math/utility.hpp>
#include <yq-toolbox/math/AllComponents.hpp>
#include <yq-toolbox/math/AnyComponents.hpp>

namespace yq {
    #ifdef YQ_MATH_SIZE4_HPP
    template <typename T>
    constexpr Vector4<T>::Vector4(const Size4<T>&v) noexcept : Vector4(v.x, v.y, v.z, v.w)
    {
    }
    #endif
    
    #ifdef YQ_USE_GLM
    template <typename T>
    constexpr Vector4<T>::operator glm::vec<4, T, glm::defaultp>() const noexcept
    {
        return glm::vec<4, T, glm::defaultp>( x, y, z, w );
    }
    #endif

    template <typename T>
    constexpr Vector4<T> Vector4<T>::operator-() const noexcept
    {
        return Vector4(-x,-y,-z,-w);
    }

    template <typename T>
    Vector4<quotient_t<T,T>> Vector4<T>::operator~() const
    {
        auto l = one_v<T>/length();
        return Vector4(x*l, y*l, z*l, w*l);
    }

    template <typename T>
    constexpr square_t<T> Vector4<T>::operator^(two_t) const noexcept
    {
        return x*x + y*y + z*z + w*w;
    }    

    #ifdef YQ_MATH_MULTIVECTOR4_HPP
    template <typename T>
    constexpr Multivector4<T> Vector4<T>::operator+(T b) const noexcept
    {
        return Multivector4<T>(
            b, 
            x, y, z, w, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T> 
        );
    }
    #endif

    #ifdef YQ_MATH_AXBOX4_HPP
    template <typename T>
    constexpr AxBox4<T> Vector4<T>::operator+(const AxBox4<T>&b) const noexcept
    {
        return AxBox4<T>(*this + b.lo, *this + b.hi);
    }
    #endif

    #if defined(YQ_MATH_BIVECTOR4_HPP) && defined(YQ_MATH_MULTIVECTOR4_HPP)
    template <typename T>
    constexpr Multivector4<T> Vector4<T>::operator+(const Bivector4<T>&b) const noexcept
    {
        return Multivector4<T>(
            zero_v<T>, 
            x, y, z, w, 
            b.xy, b.yz, b.zw, b.wx, b.xz, b.yw,
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T> 
        );
    }
    #endif

    #ifdef YQ_MATH_MULTIVECTOR4_HPP
    template <typename T>
    constexpr Multivector4<T> Vector4<T>::operator+(const Multivector4<T>&b) const noexcept
    {
        return Multivector4<T>(
            b.a, 
            x+b.x, y+b.y, z+b.z, w+b.w, 
            b.xy, b.yz, b.zw, b.wx, b.xz, b.yw,
            b.xyz, b.yzw, b.zwx, b.wxy,
            b.xyzw
        );
    }
    #endif

    #ifdef YQ_MATH_POLYGON4_HPP
    template <typename T>
    Polygon4<T> Vector4<T>::operator+(const Polygon4<T>&b) const
    {
        return Polygon4<T>(*this + span(b.vertex));
    }
    #endif

    #ifdef YQ_MATH_POLYLINE4_HPP
    template <typename T>
    Polyline4<T> Vector4<T>::operator+(const Polyline4<T>&b) const
    {
        return Polyline4<T>(*this + span(b.vertex));
    }
    #endif

    #ifdef YQ_MATH_QUADVECTOR4_HPP
    template <typename T>
    constexpr Multivector4<T> Vector4<T>::operator+(const Quadvector4<T>&b) const noexcept
    {
        return Multivector4<T>(
            zero_v<T>, 
            x, y, z, w, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            b.xyzw
        );
    }
    #endif

    #ifdef YQ_MATH_SEGMENT4_HPP
    template <typename T>
    constexpr Segment4<T> Vector4<T>::operator+(const Segment4<T>&rhs) const noexcept
    {
        return Segment4<T>( *this + rhs.a, *this + rhs.b );
    }
    #endif

    #ifdef YQ_MATH_SPHERE4_HPP
    template <typename T>
    constexpr Sphere4<T> Vector4<T>::operator+(const Sphere4<T>&b) const noexcept
    {
        return Sphere4<T>(*this + b.point, b.radius);
    }
    #endif

    #ifdef YQ_MATH_TRIANGLE4_HPP
    template <typename T>
    constexpr Triangle4<T> Vector4<T>::operator+(const Triangle4<T>&rhs) const noexcept
    {
        return Triangle4<T>(*this+rhs.a, *this+rhs.b, *this+rhs.c);
    }
    #endif

    #if defined(YQ_MATH_MULTIVECTOR4_HPP) && defined(YQ_MATH_TRIVECTOR4_HPP)
    template <typename T>
    constexpr Multivector4<T> Vector4<T>::operator+(const Trivector4<T>&b) const noexcept
    {
        return Multivector4<T>(
            zero_v<T>, 
            x, y, z, w, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            b.xyz, b.yzw, b.zwx, b.wxy,
            zero_v<T> 
        );
    }
    #endif

    template <typename T>
    constexpr Vector4<T> Vector4<T>::operator+(const Vector4& b) const noexcept
    {
        return Vector4(x+b.x, y+b.y, z+b.z, w+b.w);
    }

    template <typename T>
    Vector4<T>& Vector4<T>::operator+=(const Vector4& b) noexcept
    {
        x += b.x;
        y += b.y;
        z += b.z;
        w += b.w;
        return *this;
    }

    template <typename T>
    std::vector<Vector4<T>> Vector4<T>::operator+(std::span<const Vector4>bs) const
    {
        return transform(bs, [&](const Vector4<T>& b) -> Vector4<T> {
            return *this + b;
        });
    }

    #ifdef YQ_MATH_MULTIVECTOR4_HPP
    template <typename T>
    constexpr Multivector4<T> Vector4<T>::operator-(T b) const noexcept
    {
        return Multivector4<T>( 
            -b, 
            x, y, z, w, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T> 
        );
    }
    #endif
    
    #ifdef YQ_MATH_AXBOX4_HPP
    template <typename T>
    constexpr AxBox4<T> Vector4<T>::operator-(const AxBox4<T>&b) const noexcept
    {
        return AxBox4<T>(*this - b.hi, *this - b.lo);
    }
    #endif

    #if defined(YQ_MATH_BIVECTOR4_HPP) && defined(YQ_MATH_MULTIVECTOR4_HPP)
    template <typename T>
    constexpr Multivector4<T> Vector4<T>::operator-(const Bivector4<T>& b) const noexcept
    {
        return Multivector4<T>(
            zero_v<T>, 
            x, y, z, w, 
            -b.xy, -b.yz, -b.zw, -b.wx, -b.xz, -b.yw,
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T> 
        );
    }
    #endif

    #ifdef YQ_MATH_MULTIVECTOR4_HPP
    template <typename T>
    constexpr Multivector4<T> Vector4<T>::operator-(const Multivector4<T>& b) const noexcept
    {
        return Multivector4<T>(
            -b.a, 
            x-b.x, y-b.y, z-b.z, w-b.w, 
            -b.xy, -b.yz, -b.zw, -b.wx, -b.xz, -b.yw,
            -b.xyz, -b.yzw, -b.zwx, -b.wxy,
            -b.xyzw
        );
    }
    #endif

    #ifdef YQ_MATH_POLYGON4_HPP
    template <typename T>
    Polygon4<T> Vector4<T>::operator-(const Polygon4<T>&b) const
    {
        return Polygon4<T>(*this - span(b.vertex));
    }
    #endif

    #ifdef YQ_MATH_POLYLINE4_HPP
    template <typename T>
    Polyline4<T> Vector4<T>::operator-(const Polyline4<T>&b) const
    {
        return Polyline4<T>(*this - span(b.vertex));
    }
    #endif

    #if defined(YQ_MATH_MULTIVECTOR4_HPP) && defined(YQ_MATH_QUADVECTOR4_HPP)
    template <typename T>
    constexpr Multivector4<T> Vector4<T>::operator-(const Quadvector4<T>& b) const noexcept
    {
        return Multivector4<T>(
            zero_v<T>, 
            x, y, z, w, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            -b.xyzw
        );
    }
    #endif

    #ifdef YQ_MATH_SEGMENT4_HPP
    template <typename T>
    constexpr Segment4<T> Vector4<T>::operator-(const Segment4<T>&rhs) const noexcept
    {
        return Segment4<T>( *this - rhs.a, *this - rhs.b );
    }
    #endif

    #ifdef YQ_MATH_SPHERE4_HPP
    template <typename T>
    constexpr Sphere4<T> Vector4<T>::operator-(const Sphere4<T>&b) const noexcept
    {
        return Sphere4<T>(*this - b.point, b.radius);
    }
    #endif

    #ifdef YQ_MATH_TRIANGLE4_HPP
    template <typename T>
    constexpr Triangle4<T> Vector4<T>::operator-(const Triangle4<T>&rhs) const noexcept
    {
        return Triangle4<T>(*this-rhs.a, *this-rhs.b, *this-rhs.c);
    }
    #endif

    #if defined(YQ_MATH_MULTIVECTOR4_HPP) && defined(YQ_MATH_TRIVECTOR4_HPP)
    template <typename T>
    constexpr Multivector4<T> Vector4<T>::operator-( const Trivector4<T>& b) const noexcept
    {
        return Multivector4<T>(
            zero_v<T>, 
            x, y, z, w, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            -b.xyz, -b.yzw, -b.zwx, -b.wxy,
            zero_v<T> 
        );
    }    
    #endif

    template <typename T>
    constexpr Vector4<T> Vector4<T>::operator-(const Vector4& b) const noexcept
    {
        return Vector4(x-b.x, y-b.y, z-b.z, w-b.w);
    }
    
    template <typename T>
    Vector4<T>& Vector4<T>::operator-=(const Vector4& b) noexcept
    {
        x -= b.x;
        y -= b.y;
        z -= b.z;
        w -= b.w;
        return *this;
    }

    template <typename T>
    std::vector<Vector4<T>> Vector4<T>::operator-(std::span<const Vector4>bs) const
    {
        return transform(bs, [&](const Vector4<T>& b) -> Vector4<T> {
            return *this - b;
        });
    }

    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U>)
    constexpr Vector4<product_t<T,U>> Vector4<T>::operator*(U b) const noexcept
    {
        return Vector4<product_t<T,U>>(x*b, y*b, z*b, w*b);
    }

    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
    Vector4<T>& Vector4<T>::operator*=(U b) noexcept
    {
        x *= b;
        y *= b;
        z *= b;
        w *= b;
        return *this;
    }

    #if defined(YQ_MATH_VECTOR_1_HPP) && defined(YQ_MATH_TENSOR_4_1_HPP)
    template <typename T>
        template <typename U>
    constexpr Vector1<product_t<T,U>> Vector4<T>::operator*(const Tensor41<U>&b) const noexcept
    {
        return Vector1<product_t<T,U>>(
            x*b.xx + y*b.yx + z*b.zx + w*b.wx
        );
    }
    #endif

    #if defined(YQ_MATH_VECTOR_2_HPP) && defined(YQ_MATH_TENSOR_4_2_HPP)
    template <typename T>   
        template <typename U>
    constexpr Vector2<product_t<T,U>> Vector4<T>::operator*(const Tensor42<U>&b) const noexcept
    {
        return Vector2<product_t<T,U>>(
            x*b.xx + y*b.yx + z*b.zx + w*b.wx,
            x*b.xy + y*b.yy + z*b.zy + w*b.wy
        );
    }
    #endif

    #if defined(YQ_MATH_VECTOR_3_HPP) && defined(YQ_MATH_TENSOR_4_3_HPP)
    template <typename T>
        template <typename U>
    constexpr Vector3<product_t<T,U>> Vector4<T>::operator*(const Tensor43<U>&b) const noexcept
    {
        return Vector3<product_t<T,U>>(
            x*b.xx + y*b.yx + z*b.zx + w*b.wx,
            x*b.xy + y*b.yy + z*b.zy + w*b.wy,
            x*b.xz + y*b.yz + z*b.zz + w*b.wz
        );
    }
    #endif

    #ifdef YQ_MATH_TENSOR_4_4_HPP
    template <typename T>
        template <typename U>
    constexpr Vector4<product_t<T,U>> Vector4<T>::operator*(const Tensor44<U>&b) const noexcept
    {
        return Vector4<product_t<T,U>>(
            x*b.xx + y*b.yx + z*b.zx + w*b.wx,
            x*b.xy + y*b.yy + z*b.zy + w*b.wy,
            x*b.xz + y*b.yz + z*b.zz + w*b.wz,
            x*b.xw + y*b.yw + z*b.zw + w*b.ww
        );
    }
    #endif

    #ifdef YQ_MATH_TENSOR_4_4_HPP
    template <typename T>
        template <typename U>
    requires self_multiply_v<T,U>
    Vector4<T>& Vector4<T>::operator*=(const Tensor44<U>& b) noexcept
    {
        *this = *this * b;
        return *this;
    }
    #endif

    #ifdef YQ_MATH_MULTIVECTOR4_HPP
    template <typename T>
        template <typename U>
    constexpr Multivector4<product_t<T,U>>   Vector4<T>::operator*(const Vector4<U>&b) const noexcept
    {
        return {
            x*b.x+y*b.y+z*b.z+w*b.w, 
            zero_v<product_t<T,U>>, zero_v<product_t<T,U>>, zero_v<product_t<T,U>>, zero_v<product_t<T,U>>,
            x*b.y-y*b.x, y*b.z-z*b.y, z*b.w-w*b.z, w*b.x-x*b.w, x*b.z-z*b.x, y*b.w-w*b.y,
            zero_v<product_t<T,U>>, zero_v<product_t<T,U>>, zero_v<product_t<T,U>>, zero_v<product_t<T,U>>, 
            zero_v<product_t<T,U>>
        };
    }
    #endif

    template <typename T>
        template<typename U>
    constexpr product_t<T,U> Vector4<T>::operator DOT (const Vector4<U>&b) const noexcept
    {
        return x*b.x + y*b.y + z*b.z + w*b.w;
    }


    template <typename T>
        template<typename U>
    constexpr product_t<T,U> Vector4<T>::operator INNER (const Vector4<U>&b) const noexcept
    {
        return x*b.x + y*b.y + z*b.z + w*b.w;
    }

    #ifdef YQ_MATH_BIVECTOR4_HPP
    template <typename T>
        template <typename U>
    constexpr Bivector4<product_t<T,U>> Vector4<T>::operator OUTER(const Vector4<U>&b) const noexcept
    {
        return { x*b.y-y*b.x, y*b.z-z*b.y, z*b.w-w*b.z, w*b.x-x*b.w, x*b.z-z*b.x, y*b.w-w*b.y };
    }
    #endif

    #if defined(YQ_MATH_TENSOR_4_1_HPP) && defined(YQ_MATH_VECTOR_1_HPP)
    template <typename T>
        template <typename U>
    constexpr Tensor41<product_t<T,U>> Vector4<T>::operator OTIMES(const Vector1<U>&b) const noexcept
    {
        return Tensor41<product_t<T,U>>(
            x+b.x,
            y+b.x,
            z+b.x,
            w+b.x
        );
    }
    #endif

    #if defined(YQ_MATH_TENSOR_4_2_HPP) && defined(YQ_MATH_VECTOR_2_HPP)

    template <typename T>
        template <typename U>
    constexpr Tensor42<product_t<T,U>> Vector4<T>::operator OTIMES(const Vector2<U>&b) const noexcept
    {
        return Tensor42<product_t<T,U>>(
            x+b.x, x+b.y,
            y+b.x, y+b.y,
            z+b.x, z+b.y,
            w+b.x, w+b.y
        );
    }
    #endif

    #if defined(YQ_MATH_TENSOR_4_3_HPP) && defined(YQ_MATH_VECTOR_3_HPP)
    template <typename T>
        template <typename U>
    constexpr Tensor43<product_t<T,U>> Vector4<T>::operator OTIMES(const Vector3<U>&b) const noexcept
    {
        return Tensor43<product_t<T,U>>(
            x+b.x, x+b.y, x+b.z,
            y+b.x, y+b.y, y+b.z,
            z+b.x, z+b.y, z+b.z,
            w+b.x, w+b.y, w+b.z
        );
    }
    #endif

    #ifdef YQ_MATH_TENSOR_4_4_HPP
    template <typename T>
        template <typename U>
    constexpr Tensor44<product_t<T,U>> Vector4<T>::operator OTIMES(const Vector4<U>&b) const noexcept
    {
        return Tensor44<product_t<T,U>>(
            x+b.x, x+b.y, x+b.z, x+b.w,
            y+b.x, y+b.y, y+b.z, y+b.w,
            z+b.x, z+b.y, z+b.z, z+b.w,
            w+b.x, w+b.y, w+b.z, w+b.w
        );
    }
    #endif

    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U>)
    constexpr  Vector4<quotient_t<T,U>> Vector4<T>::operator/(U b) const noexcept
    {
        return Vector4<quotient_t<T,U>>(x / b, y / b, z / b, w / b);
    }
    
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_divide_v<T,U>)
    Vector4<T>& Vector4<T>::operator/=(U b) noexcept
    {
        x /= b;
        y /= b;
        z /= b;
        w /= b;
        return *this;
    }

    #ifdef YQ_MATH_MULTIVECTOR4_HPP
    template <typename T>
        template <typename U>
    constexpr Multivector4<quotient_t<T,U>>   Vector4<T>::operator/ (const Vector4<U>&b) const noexcept
    {
        return (*this * b) / b.length²();
    }
    #endif

    #ifdef YQ_MATH_AXBOX4_HPP
    template <typename T>
    constexpr AxBox4<T> Vector4<T>::operator|(const AxBox4<T>&b) const noexcept
    {
        return AxBox4<T>(UNION, {*this, b.lo, b.hi});
    }
    #endif

    #ifdef YQ_MATH_AXBOX4_HPP
    template <typename T>
    constexpr AxBox4<T> Vector4<T>::operator|(const Vector4&b) const noexcept
    {
        return AxBox4<T>(UNION, *this, b);
    }
    #endif
    
    template <typename T>
    constexpr Vector4<T> Vector4<T>::all_add(T b) const noexcept
    {
        return Vector4( x+b, y+b, z+b, w+b );
    }

    template <typename T>
    Vector4<T>&    Vector4<T>::all_decrement(T b) noexcept
    {
        x -= b;
        y -= b;
        z -= b;
        w -= b;
        return *this;
    }

    template <typename T>
    Vector4<T>&    Vector4<T>::all_increment(T b) noexcept
    {
        x += b;
        y += b;
        z += b;
        w += b;
        return *this;
    }
    
    template <typename T>
    constexpr Vector4<T> Vector4<T>::all_subtract(T b) const noexcept
    {
        return Vector4( x-b, y-b, z-b, w-b );
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Vector4<T>::all_test(Pred pred) const noexcept
    {
        return pred(x) && pred(y) && pred(z) && pred(w);
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Vector4<T>::all_test(T b, Pred pred) const noexcept
    {
        return pred(x, b) && pred(y, b) && pred(z, b) && pred(w, b);
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Vector4<T>::all_test(const Vector4& b, Pred pred) const noexcept
    {
        return pred(x, b.x) && pred(y, b.y) && pred(z, b.z) && pred(w, b.w);
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Vector4<T>::any_test(Pred pred) const noexcept
    {
        return pred(x) || pred(y) || pred(z) || pred(w);
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Vector4<T>::any_test(const Vector4& b, Pred pred) const noexcept
    {
        return pred(x, b.x) || pred(y, b.y) || pred(z, b.z) || pred(w, b.w);
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Vector4<T>::any_test(T b, Pred pred) const noexcept
    {
        return pred(x, b) || pred(y, b) || pred(z, b) || pred(w, b);
    }
        
    template <typename T>
        template <typename R>
    bool Vector4<T>::close(const Vector4& expected, const R& compare) const
    {
        return compare((*this-expected).length(), expected.length());
    }

    template <typename T>
        template <typename R>
    bool Vector4<T>::close²(const Vector4& expected, const R& compare) const
    {
        return compare((*this-expected).length²(), expected.length²());
    }

    template <typename T>
    constexpr T     Vector4<T>::cmax() const noexcept
    {
        return std::max({x,y,z,w});
    }

    template <typename T>
    constexpr T     Vector4<T>::cmin() const noexcept
    {
        return std::min({x,y,z,w});
    }

    template <typename T>
    constexpr fourth_t<T>   Vector4<T>::cproduct() const noexcept
    {
        return x*y*z*w;
    }

    template <typename T>
    constexpr T             Vector4<T>::csum() const noexcept
    {
        return x + y + z + w;
    }

    template <typename T>
    constexpr Vector4<T>   Vector4<T>::eabs() const noexcept
    {
        return Vector4( abs(x), abs(y), abs(z), abs(w) );
    }

    template <typename T>
        template <typename U>
    constexpr Vector4<quotient_t<T,U>>  Vector4<T>::ediv(const Vector4<U>&b) const noexcept
    {
        return Vector4<quotient_t<T,U>>(x/b.x, y/b.y, z/b.z, w/b.w);
    }

    template <typename T>
    constexpr Vector4<T>   Vector4<T>::emax(const Vector4&b) const noexcept
    {
        return Vector4(max(x, b.x), max(y, b.y), max(z, b.z), max(w, b.w));
    }
    
    template <typename T>
    constexpr Vector4<T>   Vector4<T>::emin(const Vector4&b) const noexcept
    {
        return Vector4(min(x, b.x), min(y, b.y), min(z, b.z), min(w, b.w));
    }

    template <typename T>
        template <typename U>
    constexpr Vector4<product_t<T,U>>   Vector4<T>::emul(const Vector4<U>&b) const noexcept
    {
        return {x*b.x, y*b.y, z*b.z, w*b.w};
    }
        
    template <typename T>
    constexpr square_t<T> Vector4<T>::length²() const noexcept
    {
        return x*x + y*y + z*z + w*w;
    }    

    template <typename T>
    T    Vector4<T>::length() const
    {
        if constexpr (has_sqrt_v<T>)
            return sqrt(length²());
        return {};
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    
    #ifdef YQ_MATH_MULTIVECTOR4_HPP
    template <typename T>
    constexpr Multivector4<T> operator+(T a, const Vector4<T>& b) noexcept
    {
        return { 
            a, 
            b.x, b.y, b.z, b.w, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T> 
        };
    }
    #endif

    template <typename T>
    std::vector<Vector4<T>>   operator+(std::span<const Vector4<T>>as, const Vector4<T>& b)
    {
        return transform(as, [&](const Vector4<T>&a) -> Vector4<T> {
            return a + b;
        });
    }

    #ifdef YQ_MATH_MULTIVECTOR4_HPP
    template <typename T>
    constexpr Multivector4<T> operator-(T a, const Vector4<T>& b) noexcept
    {
        return { 
            a, 
            -b.x, -b.y, -b.z, -b.w, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T> 
        };
    }
    #endif

    template <typename T>
    std::vector<Vector4<T>>   operator-(std::span<const Vector4<T>>as, const Vector4<T>& b)
    {
        return transform(as, [&](const Vector4<T>&a) -> Vector4<T> {
            return a - b;
        });
    }

    template <typename T, typename U>
    requires (is_arithmetic_v<T>)
    constexpr Vector4<product_t<T,U>> operator*(T a, const Vector4<U>&b) noexcept
    {
        return Vector4<product_t<T,U>>(a*b.x, a*b.y, a*b.z, a*b.w);
    }
    
    template <typename T, typename U>
    requires (is_arithmetic_v<T>)
    std::vector<Vector4<product_t<T,U>>>   operator*(T a, std::span<Vector4<U>>bs)
    {
        return transform(bs, [&](const Vector4<U>&b) -> Vector4<product_t<T,U>> {
            return a * b;
        });
    }

    template <typename T, typename U>
    requires (is_arithmetic_v<U>)
    std::vector<Vector4<product_t<T,U>>>   operator*(std::span<Vector4<T>>as, U b)
    {
        return transform(as, [&](const Vector4<T>&a) -> Vector4<product_t<T,U>> {
            return a * b;
        });
    }

    #if defined(YQ_MATH_TENSOR_4_1_HPP) && defined(YQ_MATH_VECTOR_1_HPP)
    template <typename T, typename U>
    std::vector<Vector1<product_t<T,U>>> operator*(std::span<const Vector4<T>>as, const Tensor41<U>&b)
    {
        return transform(as, [&](const Vector4<T>&v) -> Vector1<product_t<T,U>>{
            return v * b;
        });
    }
    #endif
    
    #if defined(YQ_MATH_TENSOR_4_2_HPP) && defined(YQ_MATH_VECTOR_2_HPP)
    template <typename T, typename U>
    std::vector<Vector2<product_t<T,U>>> operator*(std::span<const Vector4<T>>as, const Tensor42<U>&b)
    {
        return transform(as, [&](const Vector4<T>&v) -> Vector2<product_t<T,U>>{
            return v * b;
        });
    }
    #endif

    #if defined(YQ_MATH_TENSOR_4_3_HPP) && defined(YQ_MATH_VECTOR_3_HPP)
    template <typename T, typename U>
    std::vector<Vector3<product_t<T,U>>> operator*(std::span<const Vector4<T>>as, const Tensor43<U>&b)
    {
        return transform(as, [&](const Vector4<T>&v) -> Vector3<product_t<T,U>>{
            return v * b;
        });
    }
    #endif
    
    #ifdef YQ_MATH_TENSOR_4_4_HPP
    template <typename T, typename U>
    std::vector<Vector4<product_t<T,U>>> operator*(std::span<const Vector4<T>>as, const Tensor44<U>&b)
    {
        return transform(as, [&](const Vector4<T>&v) -> Vector4<product_t<T,U>>{
            return v * b;
        });
    }
    #endif

    template <typename T, typename U>
    requires (is_arithmetic_v<T>)
    constexpr  Vector4<quotient_t<T,U>> operator/(T a, const  Vector4<U>&b) noexcept
    {
        return (a*b) / b.length²();
    }

    template <typename T, typename U>
    requires (is_arithmetic_v<U>)
    std::vector<Vector4<quotient_t<T,U>>>   operator/(std::span<Vector4<T>>as, U b)
    {
        return transform(as, [&](const Vector4<T>&a) -> Vector4<quotient_t<T,U>> {
            return a / b;
        });
    }
    
    template <typename T>
    constexpr Vector4<T>   abs_elem(const Vector4<T>&a) noexcept
    {
        return a.eabs();
    }


    template <typename T>
    AllComponents<Vector4<T>>   all(Vector4<T>& val)
    {
        return { val };
    }

    template <typename T>
    AllComponents<const Vector4<T>>   all(const Vector4<T>& val)
    {
        return { val };
    }
    
    template <typename T>
    requires (std::is_floating_point_v<T> && has_sqrt_v<T>)
    Radian       angle(const Vector4<T>&a, const Vector4<T>& b)
    {
        return acos( std::clamp<T>( (a*b)/(length(a)*length(b)), -one_v<T>, one_v<T>));
    }


    template <typename T>
    AnyComponents<Vector4<T>>   any(Vector4<T>& val)
    {
        return { val };
    }
     
    template <typename T>
    AnyComponents<const Vector4<T>>   any(const Vector4<T>& val)
    {
        return { val };
    }
     
    template <typename T, typename DIM1, typename DIM2>
    requires (std::is_floating_point_v<T> && has_sqrt_v<T>)
    Radian       angle(const Vector4<MKS<T,DIM1>>&a, const Vector4<MKS<T,DIM2>>& b)
    {
        using one_t = MKS<T,dim::None>;
        return acos( std::clamp<one_t>( (a*b)/(length(a)*length(b)), -one_v<T>, one_v<T>));
    }

    template <typename T>
    constexpr T             component_max(const Vector4<T>&a) noexcept
    {
        return a.cmax();
    }

    template <typename T>
    constexpr T             component_min(const Vector4<T>&a) noexcept
    {
        return a.cmin();
    }

    template <typename T>
    constexpr fourth_t<T>     component_product(const Vector4<T>& a) noexcept
    {
        return a.cproduct();
    }

    template <typename T>
    constexpr T   component_sum(const Vector4<T>& a) noexcept
    {
        return a.csum();
    }
    
    template <typename T, typename U>
    constexpr Vector4<quotient_t<T,U>>    div_elem(const Vector4<T>&a, const Vector4<U>&b) noexcept
    {
        return a.ediv(b);
    }

    #if 0
    template <typename T>
    ElemComponents<Vector4<T>>   elem(Vector4<T>& val)
    {
        return { val };
    }
    
    template <typename T>
    ElemComponents<const Vector4<T>>   elem(const Vector4<T>& val)
    {
        return { val };
    }
    #endif
   

    template <typename T, typename R>
    bool is_close(const R& compare, const Vector4<T>& actual, const Vector4<T>& expected)
    {
        return compare(length(actual-expected), length(expected));
    }
    
    template <typename T, typename R>
    bool is_close(const R& compare, const Vector4<T>& actual, std::type_identity_t<T> x, std::type_identity_t<T> y, std::type_identity_t<T> z,std::type_identity_t<T>w)
    {
        return is_close(compare, actual, Vector4<T>(x, y, z, w) );
    }

    template <typename T>
    constexpr square_t<T> length²(const Vector4<T>& a) noexcept
    {
        return a.length²();
    }    

    template <typename T>
    auto    length(const Vector4<T>& a)
    {
        return a.length();
    }
    
    template <typename T>
    constexpr Vector4<T>   max_elem(const Vector4<T>&a, const Vector4<T>&b) noexcept
    {
        return a.emax(b);
    }
    
    template <typename T>
    constexpr Vector4<T>   max_elem(std::initializer_list<Vector4<T>> vs) noexcept
    {
        return max_elem(std::span<const Vector4<T>>(vs.data(), vs.size()));
    }

    template <typename T>
    constexpr Vector4<T>   max_elem(std::span<const Vector4<T>>vs) noexcept
    {
        if(vs.empty())
            return Vector4<T>(NAN);
        return Vector4<T>(
            std::max_element(vs.begin(), vs.end(), Vector4<T>::less_x) -> x,
            std::max_element(vs.begin(), vs.end(), Vector4<T>::less_y) -> y,
            std::max_element(vs.begin(), vs.end(), Vector4<T>::less_z) -> z,
            std::max_element(vs.begin(), vs.end(), Vector4<T>::less_w) -> w
        );
    }

    template <typename T>
    constexpr Vector4<T>   min_elem(const Vector4<T>&a, const Vector4<T>&b) noexcept
    {
        return a.emin(b);
    }

    template <typename T>
    constexpr Vector4<T>   min_elem(std::initializer_list<Vector4<T>>vs) noexcept
    {
        return min_elem(std::span<const Vector4<T>>(vs.data(), vs.size()));
    }

    template <typename T>
    constexpr Vector4<T>   min_elem(std::span<const Vector4<T>>vs) noexcept
    {
        if(vs.empty())
            return Vector4<T>(NAN);
        return Vector4<T>(
            std::min_element(vs.begin(), vs.end(), Vector4<T>::less_x) -> x,
            std::min_element(vs.begin(), vs.end(), Vector4<T>::less_y) -> y,
            std::min_element(vs.begin(), vs.end(), Vector4<T>::less_z) -> z,
            std::min_element(vs.begin(), vs.end(), Vector4<T>::less_w) -> w
        );
    }

    /*! \brief Mid-way divide two vectors
    */
    template <typename T>
    constexpr Vector4<T>    midvector(const Vector4<T>& a, const Vector4<T>& b) noexcept
    {
        if constexpr (has_ieee754_v<T>)
            return ieee754_t<T>(0.5)*(a+b);
        else if constexpr (std::is_integral_v<T>)
            return (a+b) / T(2);
        else
            return {};
    }
    
    template <typename T, typename U>
    constexpr Vector4<product_t<T,U>>    mul_elem(const Vector4<T>&a, const Vector4<T>&b) noexcept
    {
        return a.emul(b);
    }

    template <typename S, typename T>
    S&  as_stream(S& s, const Vector4<T>& v)
    {
        return s << "(" << v.x << "," << v.y << "," << v.z << "," << v.w << ")";
    }
    
    #ifdef YQ_BASIC_STREAM_HPP_
    template <typename T>
    Stream& operator<<(Stream&s, const Vector4<T>& v)
    {
        return as_stream(s, v);
    }
    #endif

    #ifdef _LOG4CPP_CATEGORYSTREAM_HH
    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const Vector4<T>& v)
    {
        return as_stream(s, v);
    }
    #endif
}

