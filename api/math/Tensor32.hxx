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

#include <math/Segment2.hpp>

#include <math/Tensor21.hpp>
#include <math/Tensor22.hpp>
#include <math/Tensor23.hpp>
#include <math/Tensor24.hpp>

#include <math/Tensor31.hpp>
#include <math/Tensor32.hpp>
#include <math/Tensor33.hpp>
#include <math/Tensor34.hpp>

#include <math/Triangle2.hpp>
#include <math/Triangle3.hpp>

#include <math/Vector2.hpp>
#include <math/Vector3.hpp>

namespace yq {
    template <typename T>
        template <glm::qualifier Q>
    constexpr Tensor32<T>::Tensor32(const glm::mat<3,2,T,Q>& t) noexcept :
        xx(t.x.x), xy(t.y.x),
        yx(t.x.y), yy(t.y.y),
        zx(t.x.z), zy(t.y.z)
    {
    }

    template <typename T>
    constexpr Tensor32<T>::operator glm::mat<3,2,T,glm::defaultp>() const noexcept 
    {
        return glm::mat<3,2,T,glm::defaultp>(
            xx, yx, zx, 
            xy, yy, zy
        );
    }


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
    requires trait::is_arithmetic_v<U>
    constexpr Tensor32<trait::product_t<T,U>>  Tensor32<T>::operator*(U b) const noexcept
    {
        return Tensor32<trait::product_t<T,U>>(
            xx*b, xy*b,
            yx*b, yy*b,
            zx*b, zy*b
        );
    }
    
    template <typename T>
        template <typename U>
    requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Tensor32<T>&  Tensor32<T>::operator*=(U b) noexcept
    {
        xx*=b; xy*=b;
        yx*=b; yy*=b;
        zx*=b; zy*=b;        
        return *this;
    }

    template <typename T>
        template <typename U>
    constexpr Segment3<trait::product_t<T,U>>  Tensor32<T>::operator*(const Segment2<U>&rhs) const noexcept
    {
        return Segment3<trait::product_t<T,U>>( *this * rhs.a, *this * rhs.b );
    }

    template <typename T>
        template <typename U>
    constexpr Tensor31<trait::product_t<T,U>> Tensor32<T>::operator*(const Tensor21<U>& b) const noexcept
    {
        return Tensor31<trait::product_t<T,U>>(
            xx*b.xx + xy*b.yx,

            yx*b.xx + yy*b.yx,

            zx*b.xx + zy*b.yx
        );
    }
    
    template <typename T>
        template <typename U>
    constexpr Tensor32<trait::product_t<T,U>> Tensor32<T>::operator*(const Tensor22<U>& b) const noexcept
    {
        return Tensor32<trait::product_t<T,U>>(
            xx*b.xx + xy*b.yx,
            xx*b.xy + xy*b.yy,

            yx*b.xx + yy*b.yx,
            yx*b.xy + yy*b.yy,

            zx*b.xx + zy*b.yx,
            zx*b.xy + zy*b.yy
        );
    }
    
    template <typename T>
        template <typename U>
    requires trait::self_mul_v<T,U>
    Tensor32<T>& Tensor32<T>::operator*=(const Tensor22<U>& b) noexcept
    {
        *this = *this * b;
        return *this;
    }

    template <typename T>
        template <typename U>
    constexpr Tensor33<trait::product_t<T,U>> Tensor32<T>::operator*(const Tensor23<U>& b) const noexcept
    {
        return Tensor33<trait::product_t<T,U>>(
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
    
    template <typename T>
        template <typename U>
    constexpr Tensor34<trait::product_t<T,U>> Tensor32<T>::operator*(const Tensor24<U>& b) const noexcept
    {
        return Tensor34<trait::product_t<T,U>>(
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

    template <typename T>
        template <typename U>
    Triangle3<trait::product_t<T,U>> Tensor32<T>::operator*(const Triangle2<U>&rhs) const noexcept
    {
        return Triangle3<trait::product_t<T,U>>( *this * rhs.a, *this * rhs.b, *this * rhs.c );
    }
        
    template <typename T>
        template <typename U>
    constexpr Vector3<trait::product_t<T,U>> Tensor32<T>::operator*(const Vector2<U>&b) const noexcept
    {
        return Vector3<trait::product_t<T,U>>(
            xx*b.x + xy*b.y,
            yx*b.x + yy*b.y,
            zx*b.x + zy*b.y
        );
    }

    template <typename T>
        template <typename U>
    requires trait::is_arithmetic_v<U>
    constexpr Tensor32<trait::quotient_t<T,U>>  Tensor32<T>::operator/(U b) const noexcept
    {
        return Tensor32<trait::quotient_t<T,U>>(
            xx/b, xy/b,
            yx/b, yy/b,
            zx/b, zy/b
        );
    }
    
    template <typename T>
        template <typename U>
    requires (trait::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Tensor32<T>&  Tensor32<T>::operator/=(U b) noexcept
    {
        xx/=b; xy/=b;
        yx/=b; yy/=b;
        zx/=b; zy/=b;        
        return *this;
    }

    template <typename T>
    constexpr Tensor23<T> Tensor32<T>::transpose() const noexcept
    {
        return Tensor23<T>(
            xx, yx, zx,
            xy, yy, zy
        );
    }

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
    requires trait::is_arithmetic_v<T>
    constexpr Tensor32<trait::product_t<T,U>>  operator*(T a, const Tensor32<U>& b)
    {
        return Tensor32<trait::product_t<T,U>>(
            a*b.xx, a*b.xy,
            a*b.yx, a*b.yy,
            a*b.zx, a*b.zy
        );
    }

    template <typename T>
    constexpr Tensor23<T>  transpose(const Tensor32<T>&v)
    {
        return v.transpose();
    }
    
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
