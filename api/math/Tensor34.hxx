////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the tensor34 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <math/Segment4.hpp>

#include <math/Tensor31.hpp>
#include <math/Tensor32.hpp>
#include <math/Tensor33.hpp>
#include <math/Tensor34.hpp>

#include <math/Tensor41.hpp>
#include <math/Tensor42.hpp>
#include <math/Tensor43.hpp>
#include <math/Tensor44.hpp>

#include <math/Triangle3.hpp>
#include <math/Triangle4.hpp>

#include <math/Vector2.hpp>
#include <math/Vector4.hpp>

namespace yq {
    template <typename T>
        template <glm::qualifier Q>
    constexpr Tensor34<T>::Tensor34(const glm::mat<3,4,T,Q>& t) noexcept :
        xx(t.x.x), xy(t.y.x), xz(t.z.x), xw(t.w.x),
        yx(t.x.y), yy(t.y.y), yz(t.z.y), yw(t.w.y),
        zx(t.x.z), zy(t.y.z), zz(t.z.z), zw(t.w.z)
    {
    }

    template <typename T>
    constexpr Tensor34<T>::operator glm::mat<3,4,T,glm::defaultp>() const noexcept 
    {
        return glm::mat<3,4,T,glm::defaultp>(
            xx, yx, zx, 
            xy, yy, zy, 
            xz, yz, zz, 
            xw, yw, zw
        );
    }

    template <typename T>
    constexpr Tensor34<T>  Tensor34<T>::operator+() const noexcept
    { 
        return *this; 
    }

    template <typename T>
    constexpr Tensor34<T>  Tensor34<T>::operator-() const noexcept
    {
        return Tensor34<T>(
            -xx, -xy, -xz, -xw,
            -yx, -yy, -yz, -yw,
            -zx, -zy, -zz, -zw
        );
    }

    template <typename T>
    constexpr Tensor34<T>   Tensor34<T>::operator+ (const Tensor34<T> &b)  const noexcept
    {
        return Tensor34<T>(
            xx+b.xx, xy+b.xy, xz+b.xz, xw+b.xw,
            yx+b.yx, yy+b.yy, yz+b.yz, yw+b.yw,
            zx+b.zx, zy+b.zy, zz+b.zz, zw+b.zw
        );
    }

    template <typename T>
    Tensor34<T>&   Tensor34<T>::operator+=(const Tensor34<T> &b)  noexcept
    {
        xx+=b.xx;  xy+=b.xy;  xz+=b.xz;  xw+=b.xw;
        yx+=b.yx;  yy+=b.yy;  yz+=b.yz;  yw+=b.yw;
        zx+=b.zx;  zy+=b.zy;  zz+=b.zz;  zw+=b.zw;
        return *this;
    }

    template <typename T>
    constexpr Tensor34<T>   Tensor34<T>::operator- (const Tensor34<T> &b)  const noexcept
    {
        return Tensor34<T>(
            xx-b.xx, xy-b.xy, xz-b.xz, xw-b.xw,
            yx-b.yx, yy-b.yy, yz-b.yz, yw-b.yw,
            zx-b.zx, zy-b.zy, zz-b.zz, zw-b.zw
        );
    }
    

    template <typename T>
    Tensor34<T>&   Tensor34<T>::operator-=(const Tensor34<T> &b)  noexcept
    {
        xx-=b.xx;  xy-=b.xy;  xz-=b.xz;  xw-=b.xw;
        yx-=b.yx;  yy-=b.yy;  yz-=b.yz;  yw-=b.yw;
        zx-=b.zx;  zy-=b.zy;  zz-=b.zz;  zw-=b.zw;
        return *this;
    }

    template <typename T>
        template <typename U>
    requires trait::is_arithmetic_v<U>
    constexpr Tensor34<trait::product_t<T,U>>  Tensor34<T>::operator*( U b) const noexcept
    {
        return Tensor34<trait::product_t<T,U>>(
            xx*b, xy*b, xz*b, xw*b,
            yx*b, yy*b, yz*b, yw*b,
            zx*b, zy*b, zz*b, zw*b
        );
    }
    
    template <typename T>
        template <typename U>
    requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Tensor34<T>&  Tensor34<T>::operator*=(U b) noexcept
    {
        xx*=b; xy*=b; xz*=b; xw*=b;
        yx*=b; yy*=b; yz*=b; yw*=b;
        zx*=b; zy*=b; zz*=b; zw*=b;        
        return *this;
    }

    template <typename T>
        template <typename U>
    constexpr Segment3<trait::product_t<T,U>>  Tensor34<T>::operator*(const Segment4<U>&rhs) const noexcept
    {
        return Segment3<trait::product_t<T,U>>( *this * rhs.a, *this * rhs.b );
    }
        
    
    template <typename T>
        template <typename U>
    constexpr Tensor31<trait::product_t<T,U>> Tensor34<T>::operator*(const Tensor41<U>& b) const noexcept
    {
        return Tensor31<trait::product_t<T,U>>(
            xx*b.xx + xy*b.yx + xz*b.zx + xw*b.wx,

            yx*b.xx + yy*b.yx + yz*b.zx + yw*b.wx,

            zx*b.xx + zy*b.yx + zz*b.zx + zw*b.wx
        );
    }
    
    template <typename T>
        template <typename U>
    constexpr Tensor32<trait::product_t<T,U>> Tensor34<T>::operator*(const Tensor42<U>& b) const noexcept
    {
        return Tensor32<trait::product_t<T,U>>(
            xx*b.xx + xy*b.yx + xz*b.zx + xw*b.wx,
            xx*b.xy + xy*b.yy + xz*b.zy + xw*b.wy,

            yx*b.xx + yy*b.yx + yz*b.zx + yw*b.wx,
            yx*b.xy + yy*b.yy + yz*b.zy + yw*b.wy,

            zx*b.xx + zy*b.yx + zz*b.zx + zw*b.wx,
            zx*b.xy + zy*b.yy + zz*b.zy + zw*b.wy
        );
    }
    
    template <typename T>
        template <typename U>
    constexpr Tensor33<trait::product_t<T,U>> Tensor34<T>::operator*(const Tensor43<U>& b) const noexcept
    {
        return Tensor32<trait::product_t<T,U>>(
            xx*b.xx + xy*b.yx + xz*b.zx + xw*b.wx,
            xx*b.xy + xy*b.yy + xz*b.zy + xw*b.wy,
            xx*b.xz + xy*b.yz + xz*b.zz + xw*b.wz,

            yx*b.xx + yy*b.yx + yz*b.zx + yw*b.wx,
            yx*b.xy + yy*b.yy + yz*b.zy + yw*b.wy,
            yx*b.xz + yy*b.yz + yz*b.zz + yw*b.wz,

            zx*b.xx + zy*b.yx + zz*b.zx + zw*b.wx,
            zx*b.xy + zy*b.yy + zz*b.zy + zw*b.wy,
            zx*b.xz + zy*b.yz + zz*b.zz + zw*b.wz
        );
    }
    
    template <typename T>
        template <typename U>
    constexpr Tensor34<trait::product_t<T,U>> Tensor34<T>::operator*(const Tensor44<U>& b) const noexcept
    {
        return Tensor34<trait::product_t<T,U>>(
            xx*b.xx + xy*b.yx + xz*b.zx + xw*b.wx,
            xx*b.xy + xy*b.yy + xz*b.zy + xw*b.wy,
            xx*b.xz + xy*b.yz + xz*b.zz + xw*b.wz,
            xx*b.xw + xy*b.yw + xz*b.zw + xw*b.ww,

            yx*b.xx + yy*b.yx + yz*b.zx + yw*b.wx,
            yx*b.xy + yy*b.yy + yz*b.zy + yw*b.wy,
            yx*b.xz + yy*b.yz + yz*b.zz + yw*b.wz,
            yx*b.xw + yy*b.yw + yz*b.zw + yw*b.ww,

            zx*b.xx + zy*b.yx + zz*b.zx + zw*b.wx,
            zx*b.xy + zy*b.yy + zz*b.zy + zw*b.wy,
            zx*b.xz + zy*b.yz + zz*b.zz + zw*b.wz,
            zx*b.xw + zy*b.yw + zz*b.zw + zw*b.ww
        );
    }
    
    template <typename T>
        template <typename U>
    requires trait::self_mul_v<T,U>
    Tensor34<T>& Tensor34<T>::operator*=(const Tensor44<U>& b) noexcept
    {
        *this = *this * b;
        return *this;
    }
    
    template <typename T>
        template <typename U>
    Triangle3<trait::product_t<T,U>> Tensor34<T>::operator*(const Triangle4<U>&rhs) const noexcept
    {
        return Triangle3<trait::product_t<T,U>>( *this * rhs.a, *this * rhs.b, *this * rhs.c );
    }

    template <typename T>
        template <typename U>
    constexpr Vector3<trait::product_t<T,U>> Tensor34<T>::operator*(const Vector4<U>&b) const noexcept
    {
        return Vector3<trait::product_t<T,U>>(
            xx*b.x + xy*b.y + xz*b.z + xw*b.w,
            yx*b.x + yy*b.y + yz*b.z + yw*b.w,
            zx*b.x + zy*b.y + zz*b.z + zw*b.w
        );
    }
    
    template <typename T>
        template <typename U>
    requires trait::is_arithmetic_v<U>
    constexpr Tensor34<trait::quotient_t<T,U>>  Tensor34<T>::operator/(U b) const noexcept
    {
        return Tensor34<trait::quotient_t<T,U>>(
            xx/b, xy/b, xz/b, xw/b,
            yx/b, yy/b, yz/b, yw/b,
            zx/b, zy/b, zz/b, zw/b
        );
    }

    template <typename T>
        template <typename U>
    requires (trait::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Tensor34<T>&  Tensor34<T>::operator/=(U b) noexcept
    {
        xx/=b; xy/=b; xz/=b; xw/=b;
        yx/=b; yy/=b; yz/=b; yw/=b;
        zx/=b; zy/=b; zz/=b; zw/=b;        
        return *this;
    }
    
    template <typename T>
    constexpr Tensor43<T>   Tensor34<T>::transpose() const noexcept
    {
        return Tensor43<T>(
            xx, yx, zx,
            xy, yy, zy,
            xz, yz, zz,
            xw, yw, zw
        );
    }

    template <typename T>
    constexpr Vector3<T>  Tensor34<T>::w_column() const noexcept
    {
        return Vector3<T>(xw, yw, zw);
    }

    template <typename T>
    Tensor34<T>& Tensor34<T>::w_column(const Vector3<T>& v) noexcept
    {
        xw = v.x;
        yw = v.y;
        zw = v.z;
        return *this;
    }

    template <typename T>
    Tensor34<T>& Tensor34<T>::w_column(T _xw, T _yw, T _zw) noexcept
    {
        xw = _xw;
        yw = _yw;
        zw = _zw;
        return *this;
    }

    template <typename T>
    constexpr Vector3<T>  Tensor34<T>::x_column() const noexcept
    {
        return Vector3<T>(xx, yx, zx);
    }

    template <typename T>
    Tensor34<T>& Tensor34<T>::x_column(const Vector3<T>& v) noexcept
    {
        xx = v.x;
        yx = v.y;
        zx = v.z;
        return *this;
    }

    template <typename T>
    Tensor34<T>& Tensor34<T>::x_column(T _xx, T _yx, T _zx) noexcept
    {
        xx = _xx;
        yx = _yx;
        zx = _zx;
        return *this;
    }

    template <typename T>
    constexpr Vector4<T>  Tensor34<T>::x_row() const noexcept
    {
        return Vector4<T>(xx, xy, xz, xw);
    }

    template <typename T>
    Tensor34<T>& Tensor34<T>::x_row(const Vector4<T>& v) noexcept
    {
        xx = v.x;
        xy = v.y;
        xz = v.z;
        xw = v.w;
        return *this;
    }

    template <typename T>
    Tensor34<T>& Tensor34<T>::x_row(T _xx, T _xy, T _xz, T _xw) noexcept
    {
        xx = _xx;
        xy = _xy;
        xz = _xz;
        xw = _xw;
        return *this;
    }
    
    template <typename T>
    constexpr Vector3<T>  Tensor34<T>::y_column() const noexcept
    {
        return Vector3<T>(xy, yy, zy);
    }


    template <typename T>
    Tensor34<T>& Tensor34<T>::y_column(const Vector3<T>& v) noexcept
    {
        xy = v.x;
        yy = v.y;
        zy = v.z;
        return *this;
    }

    template <typename T>
    Tensor34<T>& Tensor34<T>::y_column(T _xy, T _yy, T _zy) noexcept
    {
        xy = _xy;
        yy = _yy;
        zy = _zy;
        return *this;
    }

    template <typename T>
    constexpr Vector4<T>  Tensor34<T>::y_row() const noexcept
    {
        return Vector4<T>(yx, yy, yz, yw);
    }

    template <typename T>
    Tensor34<T>& Tensor34<T>::y_row(const Vector4<T>& v) noexcept
    {
        yx = v.x;
        yy = v.y;
        yz = v.z;
        yw = v.w;
        return *this;
    }

    template <typename T>
    Tensor34<T>& Tensor34<T>::y_row(T _yx, T _yy, T _yz, T _yw) noexcept
    {
        yx = _yx;
        yy = _yy;
        yz = _yz;
        yw = _yw;
        return *this;
    }


    template <typename T>
    constexpr Vector3<T>  Tensor34<T>::z_column() const noexcept
    {
        return Vector3<T>(xz, yz, zz);
    }

    template <typename T>
    Tensor34<T>& Tensor34<T>::z_column(const Vector3<T>& v) noexcept
    {
        xz = v.x;
        yz = v.y;
        zz = v.z;
        return *this;
    }

    template <typename T>
    Tensor34<T>& Tensor34<T>::z_column(T _xz, T _yz, T _zz) noexcept
    {
        xz = _xz;
        yz = _yz;
        zz = _zz;
        return *this;
    }

    template <typename T>
    constexpr Vector4<T>  Tensor34<T>::z_row() const noexcept
    {
        return Vector4<T>(zx, zy, zz, zw);
    }


    template <typename T>
    Tensor34<T>& Tensor34<T>::z_row(const Vector4<T>& v) noexcept
    {
        zx = v.x;
        zy = v.y;
        zz = v.z;
        zw = v.w;
        return *this;
    }

    template <typename T>
    Tensor34<T>& Tensor34<T>::z_row(T _zx, T _zy, T _zz, T _zw) noexcept
    {
        zx = _zx;
        zy = _zy;
        zz = _zz;
        zw = _zw;
        return *this;
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename T, typename U>
    requires trait::is_arithmetic_v<T>
    constexpr Tensor34<trait::product_t<T,U>>  operator*(T a, const Tensor34<U>& b) noexcept
    {
        return Tensor34<trait::product_t<T,U>>(
            a*b.xx, a*b.xy, a*b.xz, a*b.xw,
            a*b.yx, a*b.yy, a*b.yz, a*b.yw,
            a*b.zx, a*b.zy, a*b.zz, a*b.zw
        );
    }

    template <typename T>
    constexpr Tensor43<T>  transpose(const Tensor34<T>&v)
    {
        return v.transpose();
    }

    //! W-column of given tensor
    template <typename T>
    constexpr Vector3<T>  w_column(const Tensor34<T>&ten)  noexcept
    {
        return ten.w_column();
    }

    //! X-column of given tensor
    template <typename T>
    constexpr Vector3<T>  x_column(const Tensor34<T>&ten)  noexcept
    {
        return ten.x_column();
    }

    //! X-row of given tensor
    template <typename T>
    constexpr Vector4<T>  x_row(const Tensor34<T>&ten) noexcept
    {
        return ten.x_row();
    }

    //! Y-column of given tensor
    template <typename T>
    constexpr Vector3<T>  y_column(const Tensor34<T>&ten) noexcept
    {
        return ten.y_column();
    }

    //! Y-row of given tensor
    template <typename T>
    constexpr Vector4<T>  y_row(const Tensor34<T>&ten) noexcept
    {
        return ten.y_row();
    }

    //! Z-column of given tensor
    template <typename T>
    constexpr Vector3<T>  z_column(const Tensor34<T>&ten)  noexcept
    {
        return ten.z_column();
    }

    //! Z-row of given tensor
    template <typename T>
    constexpr Vector4<T>  z_row(const Tensor34<T>&ten) noexcept
    {
        return ten.z_row();
    }
}
