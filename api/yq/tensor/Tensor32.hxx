////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the tensor32 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <yq/tensor/Tensor32.hpp>
#include <yq/math/utility.hpp>

#include <yq/math/AllComponents.hpp>
#include <yq/math/AnyComponents.hpp>

namespace yq {
    #ifdef YQ_USE_GLM
    template <typename T>
        template <glm::qualifier Q>
    constexpr Tensor32<T>::Tensor32(const glm::mat<3,2,T,Q>& t) noexcept :
        xx(t.x.x), xy(t.y.x),
        yx(t.x.y), yy(t.y.y),
        zx(t.x.z), zy(t.y.z)
    {
    }
    #endif

    #ifdef YQ_USE_GLM
    template <typename T>
    constexpr Tensor32<T>::operator glm::mat<3,2,T,glm::defaultp>() const noexcept 
    {
        return glm::mat<3,2,T,glm::defaultp>(
            xx, yx, zx, 
            xy, yy, zy
        );
    }
    #endif


    template <typename T>
    constexpr Tensor32<T>  Tensor32<T>::operator+() const noexcept
    { 
        return *this; 
    }

    template <typename T>
    constexpr Tensor32<T>  Tensor32<T>::operator-() const noexcept
    {
        return Tensor32(
            -xx, -xy,
            -yx, -yy,
            -zx, -zy
        );
    }

    template <typename T>
    constexpr Tensor32<T>  Tensor32<T>::operator+ (const Tensor32<T> &b)  const noexcept
    {
        return Tensor32(
            xx+b.xx, xy+b.xy,
            yx+b.yx, yy+b.yy,
            zx+b.zx, zy+b.zy
        );
    }

    template <typename T>
    Tensor32<T>&   Tensor32<T>::operator+=(const Tensor32<T> &b) noexcept
    {
        xx+=b.xx;  xy+=b.xy;
        yx+=b.yx;  yy+=b.yy;
        zx+=b.zx;  zy+=b.zy;
        return *this;
    }

    template <typename T>
    constexpr Tensor32<T>   Tensor32<T>::operator- (const Tensor32<T> &b) const noexcept
    {
        return Tensor32(
            xx-b.xx, xy-b.xy,
            yx-b.yx, yy-b.yy,
            zx-b.zx, zy-b.zy
        );
    }
    

    template <typename T>
    Tensor32<T>&   Tensor32<T>::operator-=(const Tensor32<T> &b) noexcept
    {
        xx-=b.xx;  xy-=b.xy;
        yx-=b.yx;  yy-=b.yy;
        zx-=b.zx;  zy-=b.zy;
        return *this;
    }

    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    constexpr Tensor32<product_t<T,U>>  Tensor32<T>::operator*(U b) const noexcept
    {
        return Tensor32<product_t<T,U>>(
            xx*b, xy*b,
            yx*b, yy*b,
            zx*b, zy*b
        );
    }
    
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
    Tensor32<T>&  Tensor32<T>::operator*=(U b) noexcept
    {
        xx*=b; xy*=b;
        yx*=b; yy*=b;
        zx*=b; zy*=b;        
        return *this;
    }

    #if defined(YQ_MATH_POLYGON2_HPP) && defined(YQ_MATH_POLYGON3_HPP)
    template <typename T>
        template <typename U>
    Polygon3<product_t<T,U>>  Tensor32<T>::operator*(const Polygon2<U>&b) const
    {
        return Polygon3<product_t<T,U>>( *this * b.vertex );
    }
    #endif
    
    #if defined(YQ_MATH_POLYLINE2_HPP) && defined(YQ_MATH_POLYLINE3_HPP)
    template <typename T>
        template <typename U>
    Polyline3<product_t<T,U>>  Tensor32<T>::operator*(const Polyline2<U>&b) const
    {
        return Polyline3<product_t<T,U>>( *this * b.vertex );
    }
    #endif

    #if defined(YQ_MATH_SEGMENT2_HPP) && defined(YQ_MATH_SEGMENT3_HPP)
    template <typename T>
        template <typename U>
    constexpr Segment3<product_t<T,U>>  Tensor32<T>::operator*(const Segment2<U>&rhs) const noexcept
    {
        return Segment3<product_t<T,U>>( *this * rhs.a, *this * rhs.b );
    }
    #endif


    #if defined(YQ_MATH_TENSOR_2_1_HPP) && defined(YQ_MATH_TENSOR_3_1_HPP)
    template <typename T>
        template <typename U>
    constexpr Tensor31<product_t<T,U>> Tensor32<T>::operator*(const Tensor21<U>& b) const noexcept
    {
        return Tensor31<product_t<T,U>>(
            xx*b.xx + xy*b.yx,

            yx*b.xx + yy*b.yx,

            zx*b.xx + zy*b.yx
        );
    }
    #endif
    
    #ifdef YQ_MATH_TENSOR_2_2_HPP
    template <typename T>
        template <typename U>
    constexpr Tensor32<product_t<T,U>> Tensor32<T>::operator*(const Tensor22<U>& b) const noexcept
    {
        return Tensor32<product_t<T,U>>(
            xx*b.xx + xy*b.yx,
            xx*b.xy + xy*b.yy,

            yx*b.xx + yy*b.yx,
            yx*b.xy + yy*b.yy,

            zx*b.xx + zy*b.yx,
            zx*b.xy + zy*b.yy
        );
    }
    #endif
    
    #ifdef YQ_MATH_TENSOR_2_2_HPP
    template <typename T>
        template <typename U>
    requires self_multiply_v<T,U>
    Tensor32<T>& Tensor32<T>::operator*=(const Tensor22<U>& b) noexcept
    {
        *this = *this * b;
        return *this;
    }
    #endif

    #if defined(YQ_MATH_TENSOR_2_3_HPP) && defined(YQ_MATH_TENSOR_3_3_HPP)
    template <typename T>
        template <typename U>
    constexpr Tensor33<product_t<T,U>> Tensor32<T>::operator*(const Tensor23<U>& b) const noexcept
    {
        return Tensor33<product_t<T,U>>(
            xx*b.xx + xy*b.yx,
            xx*b.xy + xy*b.yy,
            xx*b.xz + xy*b.yz,

            yx*b.xx + yy*b.yx,
            yx*b.xy + yy*b.yy,
            yx*b.xz + yy*b.yz,

            zx*b.xx + zy*b.yx,
            zx*b.xy + zy*b.yy,
            zx*b.xz + zy*b.yz
        );
    }
    #endif
    
    #if defined(YQ_MATH_TENSOR_2_4_HPP) && defined(YQ_MATH_TENSOR_3_4_HPP)
    template <typename T>
        template <typename U>
    constexpr Tensor34<product_t<T,U>> Tensor32<T>::operator*(const Tensor24<U>& b) const noexcept
    {
        return Tensor34<product_t<T,U>>(
            xx*b.xx + xy*b.yx,
            xx*b.xy + xy*b.yy,
            xx*b.xz + xy*b.yz,
            xx*b.xw + xy*b.yw,

            yx*b.xx + yy*b.yx,
            yx*b.xy + yy*b.yy,
            yx*b.xz + yy*b.yz,
            yx*b.xw + yy*b.yw,

            zx*b.xx + zy*b.yx,
            zx*b.xy + zy*b.yy,
            zx*b.xz + zy*b.yz,
            zx*b.xw + zy*b.yw
        );
    }
    #endif

    #if defined(YQ_MATH_TRIANGLE2_HPP) && defined(YQ_MATH_TRIANGLE3_HPP)
    template <typename T>
        template <typename U>
    Triangle3<product_t<T,U>> Tensor32<T>::operator*(const Triangle2<U>&rhs) const noexcept
    {
        return Triangle3<product_t<T,U>>( *this * rhs.a, *this * rhs.b, *this * rhs.c );
    }
    #endif
        
    template <typename T>
        template <typename U>
    constexpr Vector3<product_t<T,U>> Tensor32<T>::operator*(const Vector2<U>&b) const noexcept
    {
        return Vector3<product_t<T,U>>(
            xx*b.x + xy*b.y,
            yx*b.x + yy*b.y,
            zx*b.x + zy*b.y
        );
    }

    template <typename T>
        template <typename U>
    std::vector<Vector3<product_t<T,U>>>    Tensor32<T>::operator*(std::span<const Vector2<U>> bs) const
    {
        return transform(bs, [&](const Vector2<U>& b) -> Vector3<product_t<T,U>> {
            return *this * b;
        });
    }

    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    constexpr Tensor32<quotient_t<T,U>>  Tensor32<T>::operator/(U b) const noexcept
    {
        return Tensor32<quotient_t<T,U>>(
            xx/b, xy/b,
            yx/b, yy/b,
            zx/b, zy/b
        );
    }
    
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_divide_v<T,U>)
    Tensor32<T>&  Tensor32<T>::operator/=(U b) noexcept
    {
        xx/=b; xy/=b;
        yx/=b; yy/=b;
        zx/=b; zy/=b;        
        return *this;
    }


    template <typename T>
    constexpr Tensor32<T> Tensor32<T>::all_add(T b) const noexcept
    {
        return Tensor32( 
            xx+b, xy+b,
            yx+b, yy+b,
            zx+b, zy+b
         );
    }

    template <typename T>
    Tensor32<T>&    Tensor32<T>::all_decrement(T b) noexcept
    {
        xx-=b; xy-=b;
        yx-=b; yy-=b;
        zx-=b; zy-=b;
        return *this;
    }

    template <typename T>
    Tensor32<T>&    Tensor32<T>::all_increment(T b) noexcept
    {
        xx+=b; xy+=b;
        yx+=b; yy+=b;
        zx+=b; zy+=b;
        return *this;
    }
    
    template <typename T>
    constexpr Tensor32<T> Tensor32<T>::all_subtract(T b) const noexcept
    {
        return Tensor32( 
            xx-b, xy-b,
            yx-b, yy-b,
            zx-b, zy-b
         );
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Tensor32<T>::all_test(Pred pred) const noexcept
    {
        return 
            pred(xx) && pred(xy) && 
            pred(yx) && pred(yy) && 
            pred(zx) && pred(zy)
        ;
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Tensor32<T>::all_test(const Tensor32& b, Pred pred) const noexcept
    {
        return 
            pred(xx, b.xx) && pred(xy, b.xy) &&
            pred(yx, b.yx) && pred(yy, b.yy) &&
            pred(zx, b.zx) && pred(zy, b.zy)
        ;
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Tensor32<T>::all_test(T b, Pred pred) const noexcept
    {
        return 
            pred(xx, b) && pred(xy, b) && 
            pred(yx, b) && pred(yy, b) && 
            pred(zx, b) && pred(zy, b)
        ;
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Tensor32<T>::any_test(Pred pred) const noexcept
    {
        return 
            pred(xx) || pred(xy) || 
            pred(yx) || pred(yy) || 
            pred(zx) || pred(zy)
        ;
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Tensor32<T>::any_test(const Tensor32& b, Pred pred) const noexcept
    {
        return 
            pred(xx, b.xx) || pred(xy, b.xy) || 
            pred(yx, b.yx) || pred(yy, b.yy) || 
            pred(zx, b.zx) || pred(zy, b.zy) 
        ;
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Tensor32<T>::any_test(T b, Pred pred) const noexcept
    {
        return 
            pred(xx, b) || pred(xy, b) || 
            pred(yx, b) || pred(yy, b) || 
            pred(zx, b) || pred(zy, b) 
        ;
    }

    #ifdef YQ_MATH_TENSOR_2_3_HPP
    template <typename T>
    constexpr Tensor23<T> Tensor32<T>::transpose() const noexcept
    {
        return Tensor23<T>(
            xx, yx, zx,
            xy, yy, zy
        );
    }
    #endif

    template <typename T>
    constexpr Vector3<T>  Tensor32<T>::x_column() const noexcept
    {
        return Vector3<T>(xx, yx, zx);
    }

    template <typename T>
    Tensor32<T>& Tensor32<T>::x_column(const Vector3<T>& v)
    {
        xx = v.x;
        yx = v.y;
        zx = v.z;
        return *this;
    }

    template <typename T>
    Tensor32<T>& Tensor32<T>::x_column(T _xx, T _yx, T _zx)
    {
        xx = _xx;
        yx = _yx;
        zx = _zx;
        return *this;
    }

    template <typename T>
    constexpr Vector2<T>  Tensor32<T>::x_row() const noexcept
    {
        return Vector2<T>(xx, xy);
    }

    template <typename T>
    Tensor32<T>& Tensor32<T>::x_row(const Vector2<T>& v)
    {
        xx = v.x;
        xy = v.y;
        return *this;
    }

    template <typename T>
    Tensor32<T>& Tensor32<T>::x_row(T _xx, T _xy)
    {
        xx = _xx;
        xy = _xy;
        return *this;
    }

    template <typename T>
    constexpr Vector3<T>  Tensor32<T>::y_column() const noexcept
    {
        return Vector3<T>(xy, yy, zy);
    }

    template <typename T>
    Tensor32<T>& Tensor32<T>::y_column(const Vector3<T>& v)
    {
        xy = v.x;
        yy = v.y;
        zy = v.z;
        return *this;
    }

    template <typename T>
    Tensor32<T>& Tensor32<T>::y_column(T _xy, T _yy, T _zy)
    {
        xy = _xy;
        yy = _yy;
        zy = _zy;
        return *this;
    }

    template <typename T>
    constexpr Vector2<T>  Tensor32<T>::y_row() const noexcept
    {
        return Vector2<T>(yx, yy);
    }

    template <typename T>
    Tensor32<T>& Tensor32<T>::y_row(const Vector2<T>& v)
    {
        yx = v.x;
        yy = v.y;
        return *this;
    }

    template <typename T>
    Tensor32<T>& Tensor32<T>::y_row(T _yx, T _yy)
    {
        yx = _yx;
        yy = _yy;
        return *this;
    }

    template <typename T>
    constexpr Vector2<T>  Tensor32<T>::z_row() const noexcept
    {
        return Vector2<T>(zx, zy);
    }

    template <typename T>
    Tensor32<T>& Tensor32<T>::z_row(const Vector2<T>& v)
    {
        zx = v.x;
        zy = v.y;
        return *this;
    }

    template <typename T>
    Tensor32<T>& Tensor32<T>::z_row(T _zx, T _zy)
    {
        zx = _zx;
        zy = _zy;
        return *this;
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Tensor32<product_t<T,U>>  operator*(T a, const Tensor32<U>& b)
    {
        return Tensor32<product_t<T,U>>(
            a*b.xx, a*b.xy,
            a*b.yx, a*b.yy,
            a*b.zx, a*b.zy
        );
    }

    template <typename T>
    AllComponents<Tensor32<T>>   all(Tensor32<T>& val)
    {
        return { val };
    }

    template <typename T>
    AllComponents<const Tensor32<T>>   all(const Tensor32<T>& val)
    {
        return { val };
    }
    
    template <typename T>
    AnyComponents<Tensor32<T>>   any(Tensor32<T>& val)
    {
        return { val };
    }

    template <typename T>
    AnyComponents<const Tensor32<T>>   any(const Tensor32<T>& val)
    {
        return { val };
    }
    
    #if 0
    template <typename T>
    ElemComponents<Tensor32<T>>   elem(Tensor32<T>& val)
    {
        return { val };
    }

    template <typename T>
    ElemComponents<const Tensor32<T>>   elem(const Tensor32<T>& val)
    {
        return { val };
    }
    #endif
    
    #ifdef YQ_MATH_TENSOR_2_3_HPP
    template <typename T>
    constexpr Tensor23<T>  transpose(const Tensor32<T>&v)
    {
        return v.transpose();
    }
    #endif
    
    template <typename T>
    constexpr Vector3<T>  x_column(const Tensor32<T>&ten) 
    {
        return ten.x_column();
    }

    template <typename T>
    constexpr Vector2<T>  x_row(const Tensor32<T>&ten)
    {
        return ten.x_row();
    }

    template <typename T>
    constexpr Vector3<T>  y_column(const Tensor32<T>&ten) 
    {
        return ten.y_column();
    }

    template <typename T>
    constexpr Vector2<T>  y_row(const Tensor32<T>&ten)
    {
        return ten.y_row();
    }

    template <typename T>
    constexpr Vector2<T>  z_row(const Tensor32<T>&ten)
    {
        return ten.z_row();
    }




}
