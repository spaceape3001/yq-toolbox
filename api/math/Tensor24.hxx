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

#include <math/Polygon2.hpp>
#include <math/Polygon4.hpp>
#include <math/Polyline2.hpp>
#include <math/Polyline4.hpp>

#include <math/Segment4.hpp>


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

namespace yq {
    template <typename T>
        template <glm::qualifier Q>
    constexpr Tensor24<T>::Tensor24(const glm::mat<2,4,T,Q>& t) noexcept :
        xx(t.x.x), xy(t.y.x), xz(t.z.x), xw(t.w.x),
        yx(t.x.y), yy(t.y.y), yz(t.z.y), yw(t.w.y)
    {
    }

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
    requires trait::is_arithmetic_v<U>
    constexpr Tensor24<trait::product_t<T,U>>  Tensor24<T>::operator*(U b) const noexcept
    {
        return Tensor24<trait::product_t<T,U>>(
            xx*b, xy*b, xz*b, xw*b,
            yx*b, yy*b, yz*b, yw*b
        );
    }
    
    template <typename T>
        template <typename U>
    requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Tensor24<T>&  Tensor24<T>::operator*=(U b) noexcept
    {
        xx*=b; xy*=b; xz*=b; xw*=b;
        yx*=b; yy*=b; yz*=b; yw*=b;        
        return *this;
    }

    template <typename T>
        template <typename U>
    Polygon2<trait::product_t<T,U>>  Tensor24<T>::operator*(const Polygon4<U>&b) const
    {
        return Polygon2<trait::product_t<T,U>>( *this * b.vertex );
    }
    
    template <typename T>
        template <typename U>
    Polyline2<trait::product_t<T,U>>  Tensor24<T>::operator*(const Polyline4<U>&b) const
    {
        return Polyline2<trait::product_t<T,U>>( *this * b.vertex );
        
    }

    template <typename T>
        template <typename U>
    constexpr Segment2<trait::product_t<T,U>>  Tensor24<T>::operator*(const Segment4<U>&rhs) const noexcept
    {
        return Segment2<trait::product_t<T,U>>( *this * rhs.a, *this * rhs.b );
    }

    template <typename T>
        template <typename U>
    constexpr Tensor21<trait::product_t<T,U>> Tensor24<T>::operator*(const Tensor41<U>& b) const noexcept
    {
        return Tensor21<trait::product_t<T,U>>(
            xx*b.xx + xy*b.yx + xz*b.zx + xw*b.wx,

            yx*b.xx + yy*b.yx + yz*b.zx + yw*b.wx
        );
    }
    
    template <typename T>
        template <typename U>
    constexpr Tensor22<trait::product_t<T,U>> Tensor24<T>::operator*(const Tensor42<U>& b) const noexcept
    {
        return Tensor22<trait::product_t<T,U>>(
            xx*b.xx + xy*b.yx + xz*b.zx + xw*b.wx,
            xx*b.xy + xy*b.yy + xz*b.zy + xw*b.wy,

            yx*b.xx + yy*b.yx + yz*b.zx + yw*b.wx,
            yx*b.xy + yy*b.yy + yz*b.zy + yw*b.wy
        );
    }
    
    template <typename T>
        template <typename U>
    constexpr Tensor23<trait::product_t<T,U>> Tensor24<T>::operator*(const Tensor43<U>& b) const noexcept
    {
        return Tensor23<trait::product_t<T,U>>(
            xx*b.xx + xy*b.yx + xz*b.zx + xw*b.wx,
            xx*b.xy + xy*b.yy + xz*b.zy + xw*b.wy,
            xx*b.xz + xy*b.yz + xz*b.zz + xw*b.wz,

            yx*b.xx + yy*b.yx + yz*b.zx + yw*b.wx,
            yx*b.xy + yy*b.yy + yz*b.zy + yw*b.wy,
            yx*b.xz + yy*b.yz + yz*b.zz + yw*b.wz
        );
    }
    
    template <typename T>
        template <typename U>
    constexpr Tensor24<trait::product_t<T,U>> Tensor24<T>::operator*(const Tensor44<U>& b) const noexcept
    {
        return Tensor24<trait::product_t<T,U>>(
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
    
    template <typename T>
        template <typename U>
    requires trait::self_mul_v<T,U>
    Tensor24<T>& Tensor24<T>::operator*=(const Tensor44<U>& b) noexcept
    {
        *this = *this * b;
        return *this;
    }
    
    template <typename T>
        template <typename U>
    Triangle2<trait::product_t<T,U>> Tensor24<T>::operator*(const Triangle4<U>&rhs) const noexcept
    {
        return Triangle2<trait::product_t<T,U>>( *this * rhs.a, *this * rhs.b, *this * rhs.c );
    }

    template <typename T>
        template <typename U>
    constexpr Vector2<trait::product_t<T,U>> Tensor24<T>::operator*(const Vector4<U>&b) const noexcept
    {
        return Vector2<trait::product_t<T,U>>(
            xx*b.x + xy*b.y + xz*b.z + xw*b.w,
            yx*b.x + yy*b.y + yz*b.z + yw*b.w
        );
    }

    template <typename T>
        template <typename U>
    std::vector<Vector2<trait::product_t<T,U>>>    Tensor24<T>::operator*(std::span<const Vector4<U>> bs) const
    {
        return transform(bs, [&](const Vector4<U>& b) -> Vector2<trait::product_t<T,U>> {
            return *this * b;
        });
    }

    template <typename T>
        template <typename U>
    requires trait::is_arithmetic_v<U>
    constexpr Tensor24<trait::quotient_t<T,U>>  Tensor24<T>::operator/(U b) const noexcept
    {
        return Tensor24<trait::quotient_t<T,U>>(
            xx/b, xy/b, xz/b, xw/b,
            yx/b, yy/b, yz/b, yw/b
        );
    }
    
    template <typename T>
        template <typename U>
    requires (trait::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Tensor24<T>&  Tensor24<T>::operator/=(U b) noexcept
    {
        xx/=b; xy/=b; xz/=b; xw/=b;
        yx/=b; yy/=b; yz/=b; yw/=b;        
        return *this;
    }

    
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
    requires trait::is_arithmetic_v<T>
    constexpr Tensor24<trait::product_t<T,U>>  operator*(T a, const Tensor24<U>& b)
    {
        return Tensor24<trait::product_t<T,U>>(
            a*b.xx, a*b.xy, a*b.xz, a*b.xw,
            a*b.yx, a*b.yy, a*b.yz, a*b.yw
        );
    }

    template <typename T>
    constexpr Tensor42<T>  transpose(const Tensor24<T>&v)
    {
        return v.transpose();
    }

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
