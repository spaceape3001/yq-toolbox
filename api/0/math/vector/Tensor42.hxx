////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/math/vector/Tensor42.hpp>
#include <0/math/utility.hpp>

#include <0/math/AllComponents.hpp>
#include <0/math/AnyComponents.hpp>

/* 
    This is the template IMPLEMENTATION of the tensor42 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

namespace yq {
    #ifdef YQ_USE_GLM
    template <typename T>
        template <glm::qualifier Q>
    constexpr Tensor42<T>::Tensor42(const glm::mat<4,2,T,Q>& t) noexcept :
        xx(t.x.x), xy(t.y.x),
        yx(t.x.y), yy(t.y.y),
        zx(t.x.z), zy(t.y.z),
        wx(t.x.w), wy(t.y.w)
    {
    }
    #endif

    #ifdef YQ_USE_GLM
    template <typename T>
    constexpr Tensor42<T>::operator glm::mat<4,2,T,glm::defaultp>() const noexcept 
    {
        return glm::mat<4,2,T,glm::defaultp>(
            xx, yx, zx, wx,
            xy, yy, zy, wy
        );
    }
    #endif

    template <typename T>
    constexpr Tensor42<T>  Tensor42<T>::operator+() const noexcept
    { 
        return *this; 
    }


    template <typename T>
    constexpr Tensor42<T>  Tensor42<T>::operator-() const noexcept
    {
        return Tensor42<T> (
            -xx, -xy,
            -yx, -yy,
            -zx, -zy,
            -wx, -wy
        );
    }


    template <typename T>
    constexpr Tensor42<T>   Tensor42<T>::operator+ (const Tensor42<T> &b) const noexcept
    {
        return {
            xx+b.xx, xy+b.xy,
            yx+b.yx, yy+b.yy,
            zx+b.zx, zy+b.zy,
            wx+b.wx, wy+b.wy
        };
    }

    template <typename T>
    Tensor42<T>&   Tensor42<T>::operator+=(const Tensor42<T> &b)  noexcept
    {
        xx+=b.xx;  xy+=b.xy;
        yx+=b.yx;  yy+=b.yy;
        zx+=b.zx;  zy+=b.zy;
        wx+=b.wx;  wy+=b.wy;
        return *this;
    }
    
    
    template <typename T>
    constexpr Tensor42<T>   Tensor42<T>::operator- (const Tensor42<T> &b)  const noexcept
    {
        return {
            xx-b.xx, xy-b.xy,
            yx-b.yx, yy-b.yy,
            zx-b.zx, zy-b.zy,
            wx-b.wx, wy-b.wy
        };
    }
    

    template <typename T>
    Tensor42<T>&   Tensor42<T>::operator-=(const Tensor42<T> &b)  noexcept
    {
        xx-=b.xx;  xy-=b.xy;
        yx-=b.yx;  yy-=b.yy;
        zx-=b.zx;  zy-=b.zy;
        wx-=b.wx;  wy-=b.wy;
        return *this;
    }
    
    
    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    constexpr Tensor42<product_t<T,U>> Tensor42<T>::operator*(U b) const noexcept
    {
        return Tensor42<product_t<T,U>>(
            xx*b, xy*b,
            yx*b, yy*b,
            zx*b, zy*b,
            wx*b, wy*b
        );
    }
    
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_mul_v<T,U>)
    Tensor42<T>&  Tensor42<T>::operator*=(U b) noexcept
    {
        xx*=b; xy*=b;
        yx*=b; yy*=b;
        zx*=b; zy*=b;
        wx*=b; wy*=b;        
        return *this;
    }

    #if defined(YQ_MATH_POLYGON2_HPP) && defined(YQ_MATH_POLYGON4_HPP)
    template <typename T>
        template <typename U>
    Polygon4<product_t<T,U>>  Tensor42<T>::operator*(const Polygon2<U>&b) const
    {
        return Polygon4<product_t<T,U>>( *this * b.vertex );
    }
    #endif
    
    #if defined(YQ_MATH_POLYLINE2_HPP) && defined(YQ_MATH_POLYLINE4_HPP)
    template <typename T>
        template <typename U>
    Polyline4<product_t<T,U>>  Tensor42<T>::operator*(const Polyline2<U>&b) const
    {
        return Polyline4<product_t<T,U>>( *this * b.vertex );
    }
    #endif

    #if defined(YQ_MATH_SEGMENT2_HPP) && defined(YQ_MATH_SEGMENT4_HPP)
    template <typename T>
        template <typename U>
    constexpr Segment4<product_t<T,U>>  Tensor42<T>::operator*(const Segment2<U>&rhs) const noexcept
    {
        return Segment4<product_t<T,U>>( *this * rhs.a, *this * rhs.b );
    }
    #endif

    #if defined(YQ_MATH_TENSOR_2_1_HPP) && defined(YQ_MATH_TENSOR_4_1_HPP)
    template <typename T>
        template <typename U>
    constexpr Tensor41<product_t<T,U>> Tensor42<T>::operator*(const Tensor21<U>& b) const noexcept
    {
        return Tensor41<product_t<T,U>>(
            xx*b.xx + xy*b.yx,

            yx*b.xx + yy*b.yx,

            zx*b.xx + zy*b.yx,

            wx*b.xx + wy*b.yx
        );
    }
    #endif
    
    #ifdef YQ_MATH_TENSOR_2_2_HPP
    template <typename T>
        template <typename U>
    constexpr Tensor42<product_t<T,U>> Tensor42<T>::operator*(const Tensor22<U>& b) const noexcept
    {
        return Tensor42<product_t<T,U>>(
            xx*b.xx + xy*b.yx,
            xx*b.xy + xy*b.yy,

            yx*b.xx + yy*b.yx,
            yx*b.xy + yy*b.yy,

            zx*b.xx + zy*b.yx,
            zx*b.xy + zy*b.yy,

            wx*b.xx + wy*b.yx,
            wx*b.xy + wy*b.yy
        );
    }
    #endif
    
    #ifdef YQ_MATH_TENSOR_2_2_HPP
    template <typename T>
        template <typename U>
    requires self_mul_v<T,U>
    Tensor42<T>& Tensor42<T>::operator*=(const Tensor22<U>& b) noexcept
    {
        *this = *this * b;
        return *this;
    }
    #endif

    #if defined(YQ_MATH_TENSOR_2_3_HPP) && defined(YQ_MATH_TENSOR_4_3_HPP)
    template <typename T>
        template <typename U>
    constexpr Tensor43<product_t<T,U>> Tensor42<T>::operator*(const Tensor23<U>& b) const noexcept
    {
        return Tensor43<product_t<T,U>>(
            xx*b.xx + xy*b.yx,
            xx*b.xy + xy*b.yy,
            xx*b.xz + xy*b.yz,

            yx*b.xx + yy*b.yx,
            yx*b.xy + yy*b.yy,
            yx*b.xz + yy*b.yz,

            zx*b.xx + zy*b.yx,
            zx*b.xy + zy*b.yy,
            zx*b.xz + zy*b.yz,

            wx*b.xx + wy*b.yx,
            wx*b.xy + wy*b.yy,
            wx*b.xz + wy*b.yz
        );
    }
    #endif
    
    #if defined(YQ_MATH_TENSOR_2_4_HPP) && defined(YQ_MATH_TENSOR_4_4_HPP)
    template <typename T>
        template <typename U>
    constexpr Tensor44<product_t<T,U>> Tensor42<T>::operator*(const Tensor24<U>& b) const noexcept
    {
        return Tensor44<product_t<T,U>>(
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
            zx*b.xw + zy*b.yw,

            wx*b.xx + wy*b.yx,
            wx*b.xy + wy*b.yy,
            wx*b.xz + wy*b.yz,
            wx*b.xw + wy*b.yw
        );
    } 
    #endif
    
    #if defined(YQ_MATH_TRIANGLE2_HPP) && defined(YQ_MATH_TRIANGLE4_HPP)
    template <typename T>
        template <typename U>
    Triangle4<product_t<T,U>> Tensor42<T>::operator*(const Triangle2<U>&rhs) const noexcept
    {
        return Triangle4<product_t<T,U>>( *this * rhs.a, *this * rhs.b, *this * rhs.c );
    }
    #endif

    template <typename T>
        template <typename U>
    constexpr Vector4<product_t<T,U>> Tensor42<T>::operator*(const Vector2<U>&b) const noexcept
    {
        return Vector4<product_t<T,U>>(
            xx*b.x + xy*b.y,
            yx*b.x + yy*b.y,
            zx*b.x + zy*b.y,
            wx*b.x + wy*b.y
        );
    }

    template <typename T>
        template <typename U>
    std::vector<Vector4<product_t<T,U>>>    Tensor42<T>::operator*(std::span<const Vector2<U>> bs) const
    {
        return transform(bs, [&](const Vector2<U>& b) -> Vector4<product_t<T,U>> {
            return *this * b;
        });
    }

    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    constexpr Tensor42<quotient_t<T,U>>  Tensor42<T>::operator/(U b) const noexcept
    {
        return Tensor42<quotient_t<T,U>>(
            xx/b, xy/b,
            yx/b, yy/b,
            zx/b, zy/b,
            wx/b, wy/b
        );
    }
    
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_div_v<T,U>)
    Tensor42<T>&  Tensor42<T>::operator/=(U b) noexcept
    {
        xx/=b; xy/=b;
        yx/=b; yy/=b;
        zx/=b; zy/=b;
        wx/=b; wy/=b;        
        return *this;
    }


    template <typename T>
    constexpr Tensor42<T> Tensor42<T>::all_add(T b) const noexcept
    {
        return Tensor42( 
            xx+b, xy+b,
            yx+b, yy+b,
            zx+b, zy+b,
            wx+b, wy+b
         );
    }

    template <typename T>
    Tensor42<T>&    Tensor42<T>::all_decrement(T b) noexcept
    {
        xx-=b; xy-=b;
        yx-=b; yy-=b;
        zx-=b; zy-=b;
        wx-=b; wy-=b;
        return *this;
    }

    template <typename T>
    Tensor42<T>&    Tensor42<T>::all_increment(T b) noexcept
    {
        xx+=b; xy+=b;
        yx+=b; yy+=b;
        zx+=b; zy+=b;
        wx+=b; wy+=b;
        return *this;
    }
    
    template <typename T>
    constexpr Tensor42<T> Tensor42<T>::all_subtract(T b) const noexcept
    {
        return Tensor42( 
            xx-b, xy-b,
            yx-b, yy-b,
            zx-b, zy-b,
            wx-b, wy-b
         );
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Tensor42<T>::all_test(Pred pred) const noexcept
    {
        return 
            pred(xx) && pred(xy) && 
            pred(yx) && pred(yy) && 
            pred(zx) && pred(zy) && 
            pred(wx) && pred(wy)
        ;
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Tensor42<T>::all_test(const Tensor42& b, Pred pred) const noexcept
    {
        return 
            pred(xx, b.xx) && pred(xy, b.xy) &&
            pred(yx, b.yx) && pred(yy, b.yy) &&
            pred(zx, b.zx) && pred(zy, b.zy) &&
            pred(wx, b.wx) && pred(wy, b.wy)
        ;
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Tensor42<T>::all_test(T b, Pred pred) const noexcept
    {
        return 
            pred(xx, b) && pred(xy, b) && 
            pred(yx, b) && pred(yy, b) && 
            pred(zx, b) && pred(zy, b) && 
            pred(wx, b) && pred(wy, b)
        ;
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Tensor42<T>::any_test(Pred pred) const noexcept
    {
        return 
            pred(xx) || pred(xy) || 
            pred(yx) || pred(yy) || 
            pred(zx) || pred(zy) || 
            pred(wx) || pred(wy)
        ;
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Tensor42<T>::any_test(const Tensor42& b, Pred pred) const noexcept
    {
        return 
            pred(xx, b.xx) || pred(xy, b.xy) || 
            pred(yx, b.yx) || pred(yy, b.yy) || 
            pred(zx, b.zx) || pred(zy, b.zy) || 
            pred(wx, b.wx) || pred(wy, b.wy) 
        ;
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Tensor42<T>::any_test(T b, Pred pred) const noexcept
    {
        return 
            pred(xx, b) || pred(xy, b) || 
            pred(yx, b) || pred(yy, b) || 
            pred(zx, b) || pred(zy, b) || 
            pred(wx, b) || pred(wy, b) 
        ;
    }

    #ifdef YQ_MATH_TENSOR_2_4_HPP
    template <typename T>
    constexpr Tensor24<T>   Tensor42<T>::transpose() const noexcept
    {
        return Tensor24<T>(
            xx, yx, zx, wx,
            xy, yy, zy, wy
        );
    }
    #endif

    template <typename T>
    constexpr Vector2<T>  Tensor42<T>::w_row() const noexcept
    {
        return {wx, wy};
    }

    template <typename T>
    Tensor42<T>& Tensor42<T>::w_row(const Vector2<T>& v) noexcept
    {
        wx = v.x;
        wy = v.y;
        return *this;
    }

    template <typename T>
    Tensor42<T>& Tensor42<T>::w_row(T _wx, T _wy) noexcept
    {
        wx = _wx;
        wy = _wy;
        return *this;
    }
    template <typename T>
    constexpr Vector4<T>  Tensor42<T>::x_column() const noexcept
    {
        return {xx, yx, zx, wx};
    }

    template <typename T>
    Tensor42<T>& Tensor42<T>::x_column(const Vector4<T>& v) noexcept
    {
        xx = v.x;
        yx = v.y;
        zx = v.z;
        wx = v.w;
        return *this;
    }

    template <typename T>
    Tensor42<T>& Tensor42<T>::x_column(T _xx, T _yx, T _zx, T _wx) noexcept
    {
        xx = _xx;
        yx = _yx;
        zx = _zx;
        wx = _wx;
        return *this;
    }

    template <typename T>
    constexpr Vector2<T>  Tensor42<T>::x_row() const noexcept
    {
        return {xx, xy};
    }

    template <typename T>
    Tensor42<T>& Tensor42<T>::x_row(const Vector2<T>& v) noexcept
    {
        xx = v.x;
        xy = v.y;
        return *this;
    }

    template <typename T>
    Tensor42<T>& Tensor42<T>::x_row(T _xx, T _xy) noexcept
    {
        xx = _xx;
        xy = _xy;
        return *this;
    }

    template <typename T>
    constexpr Vector4<T>  Tensor42<T>::y_column() const noexcept
    {
        return {xy, yy, zy, wy};
    }

    template <typename T>
    Tensor42<T>& Tensor42<T>::y_column(const Vector4<T>& v) noexcept
    {
        xy = v.x;
        yy = v.y;
        zy = v.z;
        wy = v.w;
        return *this;
    }

    template <typename T>
    Tensor42<T>& Tensor42<T>::y_column(T _xy, T _yy, T _zy, T _wy) noexcept
    {
        xy = _xy;
        yy = _yy;
        zy = _zy;
        wy = _wy;
        return *this;
    }


    template <typename T>
    constexpr Vector2<T>  Tensor42<T>::y_row() const noexcept
    {
        return {yx, yy};
    }


    template <typename T>
    Tensor42<T>& Tensor42<T>::y_row(const Vector2<T>& v) noexcept
    {
        yx = v.x;
        yy = v.y;
        return *this;
    }

    template <typename T>
    Tensor42<T>& Tensor42<T>::y_row(T _yx, T _yy) noexcept
    {
        yx = _yx;
        yy = _yy;
        return *this;
    }

    template <typename T>
    constexpr Vector2<T>  Tensor42<T>::z_row() const noexcept
    {
        return {zx, zy};
    }

    template <typename T>
    Tensor42<T>& Tensor42<T>::z_row(const Vector2<T>& v) noexcept
    {
        zx = v.x;
        zy = v.y;
        return *this;
    }

    template <typename T>
    Tensor42<T>& Tensor42<T>::z_row(T _zx, T _zy) noexcept
    {
        zx = _zx;
        zy = _zy;
        return *this;
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename T, typename U>
    requires std::is_arithmetic_v<T>
    constexpr Tensor42<product_t<T,U>>  operator*(T a, const Tensor42<T>& b) noexcept
    {
        return {
            a*b.xx, a*b.xy,
            a*b.yx, a*b.yy,
            a*b.zx, a*b.zy,
            a*b.wx, a*b.wy
        };
    }

    template <typename T>
    AllComponents<Tensor42<T>>   all(Tensor42<T>& val)
    {
        return { val };
    }

    template <typename T>
    AllComponents<const Tensor42<T>>   all(const Tensor42<T>& val)
    {
        return { val };
    }
    
    template <typename T>
    AnyComponents<Tensor42<T>>   any(Tensor42<T>& val)
    {
        return { val };
    }

    template <typename T>
    AnyComponents<const Tensor42<T>>   any(const Tensor42<T>& val)
    {
        return { val };
    }
    
    #if 0
    template <typename T>
    ElemComponents<Tensor42<T>>   elem(Tensor42<T>& val)
    {
        return { val };
    }

    template <typename T>
    ElemComponents<const Tensor42<T>>   elem(const Tensor42<T>& val)
    {
        return { val };
    }
    #endif
    
    #ifdef YQ_MATH_TENSOR_2_4_HPP
    template <typename T>
    constexpr Tensor24<T>  transpose(const Tensor42<T>&v)
    {
        return v.transpose();
    }
    #endif

    template <typename T>
    constexpr Vector4<T>  x_column(const Tensor42<T>&ten)  noexcept
    {
        return ten.x_column();
    }

    template <typename T>
    constexpr Vector2<T>  w_row(const Tensor42<T>&ten) noexcept
    {
        return ten.w_row();
    }

    template <typename T>
    constexpr Vector2<T>  x_row(const Tensor42<T>&ten) noexcept
    {
        return ten.x_row();
    }

    template <typename T>
    constexpr Vector4<T>  y_column(const Tensor42<T>&ten)  noexcept
    {
        return ten.y_column();
    }

    template <typename T>
    constexpr Vector2<T>  y_row(const Tensor42<T>&ten) noexcept
    {
        return ten.y_row();
    }

    template <typename T>
    constexpr Vector2<T>  z_row(const Tensor42<T>&ten) noexcept
    {
        return ten.z_row();
    }

}
