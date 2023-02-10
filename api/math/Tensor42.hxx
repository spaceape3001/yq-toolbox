////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/Polygon2.hpp>
#include <math/Polygon4.hpp>
#include <math/Polyline2.hpp>
#include <math/Polyline4.hpp>

#include <math/Segment2.hpp>

#include <math/Tensor21.hpp>
#include <math/Tensor22.hpp>
#include <math/Tensor23.hpp>
#include <math/Tensor24.hpp>

#include <math/Tensor41.hpp>
#include <math/Tensor42.hpp>
#include <math/Tensor43.hpp>
#include <math/Tensor44.hpp>

#include <math/Triangle2.hpp>
#include <math/Triangle4.hpp>

#include <math/Vector2.hpp>
#include <math/Vector4.hpp>
#include <math/utility.hpp>

/* 
    This is the template IMPLEMENTATION of the tensor42 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

namespace yq {
    template <typename T>
        template <glm::qualifier Q>
    constexpr Tensor42<T>::Tensor42(const glm::mat<4,2,T,Q>& t) noexcept :
        xx(t.x.x), xy(t.y.x),
        yx(t.x.y), yy(t.y.y),
        zx(t.x.z), zy(t.y.z),
        wx(t.x.w), wy(t.y.w)
    {
    }

    template <typename T>
    constexpr Tensor42<T>::operator glm::mat<4,2,T,glm::defaultp>() const noexcept 
    {
        return glm::mat<4,2,T,glm::defaultp>(
            xx, yx, zx, wx,
            xy, yy, zy, wy
        );
    }

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
    requires trait::is_arithmetic_v<U>
    constexpr Tensor42<trait::product_t<T,U>> Tensor42<T>::operator*(U b) const noexcept
    {
        return Tensor42<trait::product_t<T,U>>(
            xx*b, xy*b,
            yx*b, yy*b,
            zx*b, zy*b,
            wx*b, wy*b
        );
    }
    
    template <typename T>
        template <typename U>
    requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Tensor42<T>&  Tensor42<T>::operator*=(U b) noexcept
    {
        xx*=b; xy*=b;
        yx*=b; yy*=b;
        zx*=b; zy*=b;
        wx*=b; wy*=b;        
        return *this;
    }

    template <typename T>
        template <typename U>
    Polygon4<trait::product_t<T,U>>  Tensor42<T>::operator*(const Polygon2<U>&b) const
    {
        return Polygon4<trait::product_t<T,U>>( *this * b.vertex );
    }
    
    template <typename T>
        template <typename U>
    Polyline4<trait::product_t<T,U>>  Tensor42<T>::operator*(const Polyline2<U>&b) const
    {
        return Polyline4<trait::product_t<T,U>>( *this * b.vertex );
    }

    template <typename T>
        template <typename U>
    constexpr Segment4<trait::product_t<T,U>>  Tensor42<T>::operator*(const Segment2<U>&rhs) const noexcept
    {
        return Segment4<trait::product_t<T,U>>( *this * rhs.a, *this * rhs.b );
    }

    template <typename T>
        template <typename U>
    constexpr Tensor41<trait::product_t<T,U>> Tensor42<T>::operator*(const Tensor21<U>& b) const noexcept
    {
        return Tensor41<trait::product_t<T,U>>(
            xx*b.xx + xy*b.yx,

            yx*b.xx + yy*b.yx,

            zx*b.xx + zy*b.yx,

            wx*b.xx + wy*b.yx
        );
    }
    
    template <typename T>
        template <typename U>
    constexpr Tensor42<trait::product_t<T,U>> Tensor42<T>::operator*(const Tensor22<U>& b) const noexcept
    {
        return Tensor42<trait::product_t<T,U>>(
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
    
    template <typename T>
        template <typename U>
    requires trait::self_mul_v<T,U>
    Tensor42<T>& Tensor42<T>::operator*=(const Tensor22<U>& b) noexcept
    {
        *this = *this * b;
        return *this;
    }

    template <typename T>
        template <typename U>
    constexpr Tensor43<trait::product_t<T,U>> Tensor42<T>::operator*(const Tensor23<U>& b) const noexcept
    {
        return Tensor43<trait::product_t<T,U>>(
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
    
    template <typename T>
        template <typename U>
    constexpr Tensor44<trait::product_t<T,U>> Tensor42<T>::operator*(const Tensor24<U>& b) const noexcept
    {
        return Tensor44<trait::product_t<T,U>>(
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
    
    template <typename T>
        template <typename U>
    Triangle4<trait::product_t<T,U>> Tensor42<T>::operator*(const Triangle2<U>&rhs) const noexcept
    {
        return Triangle4<trait::product_t<T,U>>( *this * rhs.a, *this * rhs.b, *this * rhs.c );
    }

    template <typename T>
        template <typename U>
    constexpr Vector4<trait::product_t<T,U>> Tensor42<T>::operator*(const Vector2<U>&b) const noexcept
    {
        return Vector4<trait::product_t<T,U>>(
            xx*b.x + xy*b.y,
            yx*b.x + yy*b.y,
            zx*b.x + zy*b.y,
            wx*b.x + wy*b.y
        );
    }

    template <typename T>
        template <typename U>
    std::vector<Vector4<trait::product_t<T,U>>>    Tensor42<T>::operator*(std::span<const Vector2<U>> bs) const
    {
        return transform(bs, [&](const Vector2<U>& b) -> Vector4<trait::product_t<T,U>> {
            return *this * b;
        });
    }

    template <typename T>
        template <typename U>
    requires trait::is_arithmetic_v<U>
    constexpr Tensor42<trait::quotient_t<T,U>>  Tensor42<T>::operator/(U b) const noexcept
    {
        return Tensor42<trait::quotient_t<T,U>>(
            xx/b, xy/b,
            yx/b, yy/b,
            zx/b, zy/b,
            wx/b, wy/b
        );
    }
    
    template <typename T>
        template <typename U>
    requires (trait::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Tensor42<T>&  Tensor42<T>::operator/=(U b) noexcept
    {
        xx/=b; xy/=b;
        yx/=b; yy/=b;
        zx/=b; zy/=b;
        wx/=b; wy/=b;        
        return *this;
    }




    template <typename T>
    constexpr Tensor24<T>   Tensor42<T>::transpose() const noexcept
    {
        return Tensor24<T>(
            xx, yx, zx, wx,
            xy, yy, zy, wy
        );
    }


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
    constexpr Tensor42<trait::product_t<T,U>>  operator*(T a, const Tensor42<T>& b) noexcept
    {
        return {
            a*b.xx, a*b.xy,
            a*b.yx, a*b.yy,
            a*b.zx, a*b.zy,
            a*b.wx, a*b.wy
        };
    }
    
        template <typename T>
    constexpr Tensor24<T>  transpose(const Tensor42<T>&v)
    {
        return v.transpose();
    }

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
