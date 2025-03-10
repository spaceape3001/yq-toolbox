////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the tensor24 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <yq/tensor/Tensor24.hpp>
#include <yq/math/utility.hpp>

#include <yq/math/AllComponents.hpp>
#include <yq/math/AnyComponents.hpp>

namespace yq {
    #ifdef YQ_USE_GLM
    template <typename T>
        template <glm::qualifier Q>
    constexpr Tensor24<T>::Tensor24(const glm::mat<2,4,T,Q>& t) noexcept :
        xx(t[0][0]), xy(t[1][0]), xz(t[2][0]), xw(t[3][0]),
        yx(t[0][1]), yy(t[1][1]), yz(t[2][1]), yw(t[3][1])
    {
    }
    #endif

    #ifdef YQ_USE_GLM
    template <typename T>
    constexpr Tensor24<T>::operator glm::mat<2,4,T,glm::defaultp>() const noexcept 
    {
        return glm::mat<2,4,T,glm::defaultp>(
            xx, yx, 
            xy, yy, 
            xz, yz, 
            xw, yw
        );
    }
    #endif

    template <typename T>
    constexpr Tensor24<T>  Tensor24<T>::operator+() const noexcept
    { 
        return *this; 
    }

    template <typename T>
    constexpr Tensor24<T>  Tensor24<T>::operator-() const noexcept
    {
        return Tensor24(
            -xx, -xy, -xz, -xw,
            -yx, -yy, -yz, -yw
        );
    }
    
    
    template <typename T>
    constexpr Tensor24<T>   Tensor24<T>::operator+ (const Tensor24<T> &b) const noexcept
    {
        return Tensor24(
            xx+b.xx, xy+b.xy, xz+b.xz, xw+b.xw,
            yx+b.yx, yy+b.yy, yz+b.yz, yw+b.yw
        );
    }

    template <typename T>
    Tensor24<T>&   Tensor24<T>::operator+=(const Tensor24<T> &b) noexcept
    {
        xx+=b.xx;  xy+=b.xy;  xz+=b.xz;  xw+=b.xw;
        yx+=b.yx;  yy+=b.yy;  yz+=b.yz;  yw+=b.yw;
        return *this;
    }
    
    template <typename T>
    constexpr Tensor24<T>   Tensor24<T>::operator- (const Tensor24<T> &b) const noexcept
    {
        return Tensor24(
            xx-b.xx, xy-b.xy, xz-b.xz, xw-b.xw,
            yx-b.yx, yy-b.yy, yz-b.yz, yw-b.yw
        );
    }
    

    template <typename T>
    Tensor24<T>&   Tensor24<T>::operator-=(const Tensor24<T> &b) noexcept
    {
        xx-=b.xx;  xy-=b.xy;  xz-=b.xz;  xw-=b.xw;
        yx-=b.yx;  yy-=b.yy;  yz-=b.yz;  yw-=b.yw;
        return *this;
    }

    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    constexpr Tensor24<product_t<T,U>>  Tensor24<T>::operator*(U b) const noexcept
    {
        return Tensor24<product_t<T,U>>(
            xx*b, xy*b, xz*b, xw*b,
            yx*b, yy*b, yz*b, yw*b
        );
    }
    
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
    Tensor24<T>&  Tensor24<T>::operator*=(U b) noexcept
    {
        xx*=b; xy*=b; xz*=b; xw*=b;
        yx*=b; yy*=b; yz*=b; yw*=b;        
        return *this;
    }

    #if defined(YQ_MATH_POLYGON2_HPP) && defined(YQ_MATH_POLYGON4_HPP)
    template <typename T>
        template <typename U>
    Polygon2<product_t<T,U>>  Tensor24<T>::operator*(const Polygon4<U>&b) const
    {
        return Polygon2<product_t<T,U>>( *this * b.vertex );
    }
    #endif
    
    #if defined(YQ_MATH_POLYLINE2_HPP) && defined(YQ_MATH_POLYLINE4_HPP)
    template <typename T>
        template <typename U>
    Polyline2<product_t<T,U>>  Tensor24<T>::operator*(const Polyline4<U>&b) const
    {
        return Polyline2<product_t<T,U>>( *this * b.vertex );
        
    }
    #endif

    #if defined(YQ_MATH_SEGMENT2_HPP) && defined(YQ_MATH_SEGMENT4_HPP)
    template <typename T>
        template <typename U>
    constexpr Segment2<product_t<T,U>>  Tensor24<T>::operator*(const Segment4<U>&rhs) const noexcept
    {
        return Segment2<product_t<T,U>>( *this * rhs.a, *this * rhs.b );
    }
    #endif

    #if defined(YQ_MATH_TENSOR_2_1_HPP) && defined(YQ_MATH_TENSOR_4_1_HPP)
    template <typename T>
        template <typename U>
    constexpr Tensor21<product_t<T,U>> Tensor24<T>::operator*(const Tensor41<U>& b) const noexcept
    {
        return Tensor21<product_t<T,U>>(
            xx*b.xx + xy*b.yx + xz*b.zx + xw*b.wx,

            yx*b.xx + yy*b.yx + yz*b.zx + yw*b.wx
        );
    }
    #endif
    
    #if defined(YQ_MATH_TENSOR_2_2_HPP) && defined(YQ_MATH_TENSOR_4_2_HPP)
    template <typename T>
        template <typename U>
    constexpr Tensor22<product_t<T,U>> Tensor24<T>::operator*(const Tensor42<U>& b) const noexcept
    {
        return Tensor22<product_t<T,U>>(
            xx*b.xx + xy*b.yx + xz*b.zx + xw*b.wx,
            xx*b.xy + xy*b.yy + xz*b.zy + xw*b.wy,

            yx*b.xx + yy*b.yx + yz*b.zx + yw*b.wx,
            yx*b.xy + yy*b.yy + yz*b.zy + yw*b.wy
        );
    }
    #endif
    
    #if defined(YQ_MATH_TENSOR_2_3_HPP) && defined(YQ_MATH_TENSOR_4_3_HPP)
    template <typename T>
        template <typename U>
    constexpr Tensor23<product_t<T,U>> Tensor24<T>::operator*(const Tensor43<U>& b) const noexcept
    {
        return Tensor23<product_t<T,U>>(
            xx*b.xx + xy*b.yx + xz*b.zx + xw*b.wx,
            xx*b.xy + xy*b.yy + xz*b.zy + xw*b.wy,
            xx*b.xz + xy*b.yz + xz*b.zz + xw*b.wz,

            yx*b.xx + yy*b.yx + yz*b.zx + yw*b.wx,
            yx*b.xy + yy*b.yy + yz*b.zy + yw*b.wy,
            yx*b.xz + yy*b.yz + yz*b.zz + yw*b.wz
        );
    }
    #endif
    
    #ifdef YQ_MATH_TENSOR_4_4_HPP
    template <typename T>
        template <typename U>
    constexpr Tensor24<product_t<T,U>> Tensor24<T>::operator*(const Tensor44<U>& b) const noexcept
    {
        return Tensor24<product_t<T,U>>(
            xx*b.xx + xy*b.yx + xz*b.zx + xw*b.wx,
            xx*b.xy + xy*b.yy + xz*b.zy + xw*b.wy,
            xx*b.xz + xy*b.yz + xz*b.zz + xw*b.wz,
            xx*b.xw + xy*b.yw + xz*b.zw + xw*b.ww,

            yx*b.xx + yy*b.yx + yz*b.zx + yw*b.wx,
            yx*b.xy + yy*b.yy + yz*b.zy + yw*b.wy,
            yx*b.xz + yy*b.yz + yz*b.zz + yw*b.wz,
            yx*b.xw + yy*b.yw + yz*b.zw + yw*b.ww
        );
    }
    #endif
    
    #ifdef YQ_MATH_TENSOR_4_4_HPP
    template <typename T>
        template <typename U>
    requires self_multiply_v<T,U>
    Tensor24<T>& Tensor24<T>::operator*=(const Tensor44<U>& b) noexcept
    {
        *this = *this * b;
        return *this;
    }
    #endif
    
    #if defined(YQ_MATH_TRIANGLE2_HPP) && defined(YQ_MATH_TRIANGLE4_HPP)
    template <typename T>
        template <typename U>
    Triangle2<product_t<T,U>> Tensor24<T>::operator*(const Triangle4<U>&rhs) const noexcept
    {
        return Triangle2<product_t<T,U>>( *this * rhs.a, *this * rhs.b, *this * rhs.c );
    }
    #endif

    template <typename T>
        template <typename U>
    constexpr Vector2<product_t<T,U>> Tensor24<T>::operator*(const Vector4<U>&b) const noexcept
    {
        return Vector2<product_t<T,U>>(
            xx*b.x + xy*b.y + xz*b.z + xw*b.w,
            yx*b.x + yy*b.y + yz*b.z + yw*b.w
        );
    }

    template <typename T>
        template <typename U>
    std::vector<Vector2<product_t<T,U>>>    Tensor24<T>::operator*(std::span<const Vector4<U>> bs) const
    {
        return transform(bs, [&](const Vector4<U>& b) -> Vector2<product_t<T,U>> {
            return *this * b;
        });
    }

    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    constexpr Tensor24<quotient_t<T,U>>  Tensor24<T>::operator/(U b) const noexcept
    {
        return Tensor24<quotient_t<T,U>>(
            xx/b, xy/b, xz/b, xw/b,
            yx/b, yy/b, yz/b, yw/b
        );
    }
    
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_divide_v<T,U>)
    Tensor24<T>&  Tensor24<T>::operator/=(U b) noexcept
    {
        xx/=b; xy/=b; xz/=b; xw/=b;
        yx/=b; yy/=b; yz/=b; yw/=b;        
        return *this;
    }


    template <typename T>
    constexpr Tensor24<T> Tensor24<T>::all_add(T b) const noexcept
    {
        return Tensor24( 
            xx+b, xy+b, xz+b, xw+b,
            yx+b, yy+b, yz+b, yw+b
         );
    }

    template <typename T>
    Tensor24<T>&    Tensor24<T>::all_decrement(T b) noexcept
    {
        xx-=b; xy-=b; xz-=b; xw-=b;
        yx-=b; yy-=b; yz-=b; yw-=b;
        return *this;
    }

    template <typename T>
    Tensor24<T>&    Tensor24<T>::all_increment(T b) noexcept
    {
        xx+=b; xy+=b; xz+=b; xw+=b;
        yx+=b; yy+=b; yz+=b; yw+=b;
        return *this;
    }
    
    template <typename T>
    constexpr Tensor24<T> Tensor24<T>::all_subtract(T b) const noexcept
    {
        return Tensor24( 
            xx-b, xy-b, xz-b, xw-b,
            yx-b, yy-b, yz-b, yw-b
         );
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Tensor24<T>::all_test(Pred pred) const noexcept
    {
        return 
            pred(xx) && pred(xy) && pred(xz) && pred(xw) &&
            pred(yx) && pred(yy) && pred(yz) && pred(yw)
        ;
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Tensor24<T>::all_test(const Tensor24& b, Pred pred) const noexcept
    {
        return 
            pred(xx, b.xx) && pred(xy, b.xy) && pred(xz, b.xz) && pred(xw, b.xw) &&
            pred(yx, b.yx) && pred(yy, b.yy) && pred(yz, b.yz) && pred(yw, b.yw)
        ;
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Tensor24<T>::all_test(T b, Pred pred) const noexcept
    {
        return 
            pred(xx, b) && pred(xy, b) && pred(xz, b) && pred(xw, b) &&
            pred(yx, b) && pred(yy, b) && pred(yz, b) && pred(yw, b) 
        ;
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Tensor24<T>::any_test(Pred pred) const noexcept
    {
        return 
            pred(xx) || pred(xy) || pred(xz) || pred(xw) ||
            pred(yx) || pred(yy) || pred(yz) || pred(yw)
        ;
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Tensor24<T>::any_test(const Tensor24& b, Pred pred) const noexcept
    {
        return 
            pred(xx, b.xx) || pred(xy, b.xy) || pred(xz, b.xz) || pred(xw, b.xw) ||
            pred(yx, b.yx) || pred(yy, b.yy) || pred(yz, b.yz) || pred(yw, b.yw)
        ;
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Tensor24<T>::any_test(T b, Pred pred) const noexcept
    {
        return 
            pred(xx, b) || pred(xy, b) || pred(xz, b) || pred(xw, b) ||
            pred(yx, b) || pred(yy, b) || pred(yz, b) || pred(yw, b) 
        ;
    }
     
    #ifdef YQ_MATH_TENSOR_4_2_HPP
    template <typename T>
    constexpr Tensor42<T> Tensor24<T>::transpose() const noexcept
    {
        return Tensor42<T>(
            xx, yx,
            xy, yy,
            xz, yz,
            xw, yw
        );
    }
    #endif

    template <typename T>
    constexpr Vector2<T>  Tensor24<T>::w_column() const noexcept 
    {
        return Vector2<T>(xw, yw);
    }

    template <typename T>
    Tensor24<T>& Tensor24<T>::w_column(const Vector2<T>& v)
    {
        xw = v.x;
        yw = v.y;
        return *this;
    }

    template <typename T>
    Tensor24<T>& Tensor24<T>::w_column(T _xw, T _yw)
    {
        xw = _xw;
        yw = _yw;
        return *this;
    }

    template <typename T>
    constexpr Vector2<T>  Tensor24<T>::x_column() const noexcept 
    {
        return Vector2<T>(xx, yx);
    }

    template <typename T>
    Tensor24<T>& Tensor24<T>::x_column(const Vector2<T>& v)
    {
        xx = v.x;
        yx = v.y;
        return *this;
    }

    template <typename T>
    Tensor24<T>& Tensor24<T>::x_column(T _xx, T _yx)
    {
        xx = _xx;
        yx = _yx;
        return *this;
    }


    template <typename T>
    constexpr Vector4<T>  Tensor24<T>::x_row() const noexcept 
    {
        return Vector4<T>(xx, xy, xz, xw);
    }

    template <typename T>
    Tensor24<T>& Tensor24<T>::x_row(const Vector4<T>& v)
    {
        xx = v.x;
        xy = v.y;
        xz = v.z;
        xw = v.w;
        return *this;
    }

    template <typename T>
    Tensor24<T>& Tensor24<T>::x_row(T _xx, T _xy, T _xz, T _xw)
    {
        xx = _xx;
        xy = _xy;
        xz = _xz;
        xw = _xw;
        return *this;
    }


    template <typename T>
    constexpr Vector2<T>  Tensor24<T>::y_column() const noexcept 
    {
        return Vector2<T>(xy, yy);
    }


    template <typename T>
    Tensor24<T>& Tensor24<T>::y_column(const Vector2<T>& v)
    {
        xy = v.x;
        yy = v.y;
        return *this;
    }

    template <typename T>
    Tensor24<T>& Tensor24<T>::y_column(T _xy, T _yy)
    {
        xy = _xy;
        yy = _yy;
        return *this;
    }

    template <typename T>
    constexpr Vector4<T>  Tensor24<T>::y_row() const noexcept 
    {
        return Vector4<T>(yx, yy, yz, yw);
    }


    template <typename T>
    Tensor24<T>& Tensor24<T>::y_row(const Vector4<T>& v)
    {
        yx = v.x;
        yy = v.y;
        yz = v.z;
        yw = v.w;
        return *this;
    }

    template <typename T>
    Tensor24<T>& Tensor24<T>::y_row(T _yx, T _yy, T _yz, T _yw)
    {
        yx = _yx;
        yy = _yy;
        yz = _yz;
        yw = _yw;
        return *this;
    }
    
    template <typename T>
    constexpr Vector2<T>  Tensor24<T>::z_column() const noexcept 
    {
        return Vector2<T>(xz, yz);
    }


    template <typename T>
    Tensor24<T>& Tensor24<T>::z_column(const Vector2<T>& v)
    {
        xz = v.x;
        yz = v.y;
        return *this;
    }

    template <typename T>
    Tensor24<T>& Tensor24<T>::z_column(T _xz, T _yz)
    {
        xz = _xz;
        yz = _yz;
        return *this;
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Tensor24<product_t<T,U>>  operator*(T a, const Tensor24<U>& b)
    {
        return Tensor24<product_t<T,U>>(
            a*b.xx, a*b.xy, a*b.xz, a*b.xw,
            a*b.yx, a*b.yy, a*b.yz, a*b.yw
        );
    }

    template <typename T>
    AllComponents<Tensor24<T>>   all(Tensor24<T>& val)
    {
        return { val };
    }

    template <typename T>
    AllComponents<const Tensor24<T>>   all(const Tensor24<T>& val)
    {
        return { val };
    }
    
    template <typename T>
    AnyComponents<Tensor24<T>>   any(Tensor24<T>& val)
    {
        return { val };
    }

    template <typename T>
    AnyComponents<const Tensor24<T>>   any(const Tensor24<T>& val)
    {
        return { val };
    }
    
    #if 0
    template <typename T>
    ElemComponents<Tensor24<T>>   elem(Tensor24<T>& val)
    {
        return { val };
    }

    template <typename T>
    ElemComponents<const Tensor24<T>>   elem(const Tensor24<T>& val)
    {
        return { val };
    }
    #endif
    
    #ifdef YQ_MATH_TENSOR_4_2_HPP
    template <typename T>
    constexpr Tensor42<T>  transpose(const Tensor24<T>&v)
    {
        return v.transpose();
    }
    #endif

    template <typename T>
    constexpr Vector2<T>  w_column(const Tensor24<T>&ten) 
    {
        return ten.w_column();
    }

    template <typename T>
    constexpr Vector2<T>  x_column(const Tensor24<T>&ten) 
    {
        return ten.x_column();
    }

    template <typename T>
    constexpr Vector4<T>  x_row(const Tensor24<T>&ten)
    {
        return ten.x_row();
    }

    template <typename T>
    constexpr Vector2<T>  y_column(const Tensor24<T>&ten) 
    {
        return ten.y_column();
    }

    template <typename T>
    constexpr Vector4<T>  y_row(const Tensor24<T>&ten)
    {
        return ten.y_row();
    }

    template <typename T>
    constexpr Vector2<T>  z_column(const Tensor24<T>&ten) 
    {
        return ten.z_column();
    }
            
}
