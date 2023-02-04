////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the tensor33 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <math/Segment3.hpp>

#include <math/Tensor31.hpp>
#include <math/Tensor32.hpp>
#include <math/Tensor33.hpp>
#include <math/Tensor34.hpp>

#include <math/Vector3.hpp>

#include <math/Quaternion3.hpp>

#include <math/trig.hpp>
#include <math/Units.hpp>

namespace yq {
    template <typename T>
    template <typename>
    requires std::is_floating_point_v<T>
    Tensor33<T>::Tensor33(const Quaternion3<T>&q) : 
        Tensor33(COLUMNS,  q * Vector3<T>(X), q * Vector3<T>(Y), q * Vector3<T>(Z) )
    {
    }

    template <typename T>
    template <typename>
    requires std::is_floating_point_v<T>
    Tensor33<T>::Tensor33(hpr_t, MKS<T,dim::Angle> hdg, MKS<T,dim::Angle> pitch, MKS<T,dim::Angle> roll)
    {
        auto ch = cos(hdg);
        auto sh = sin(hdg);

        auto cp = cos(pitch);
        auto sp = sin(pitch);

        auto cr = cos(roll);
        auto sr = sin(roll);
        
        xx  = ch*cp;
        xy  = sh*cp;
        xz  = -sp;
        
        yx  = ch*sp*sr-sh*cr;
        yy  = sh*sp*sr+ch*cr;
        yz  = cp*sr;
        
        zx  = ch*sp*cr+sh*sr;
        zy  = sh*sp*cr-ch*sr;
        zz  = cp*cr;
    }


    template <typename T>
    template <typename>
    requires std::is_floating_point_v<T>
    Tensor33<T>::Tensor33(ccw_t, x_t, MKS<T,dim::Angle>v) : Tensor33(IDENTITY)
    {
        auto c  = cos(v);
        auto s  = sin(v);
        
        yy  = c;
        yz  = -s,
        
        zy  = s;
        zz  = c;
    }
    
    
    template <typename T>
    template <typename>
    requires std::is_floating_point_v<T>
    Tensor33<T>::Tensor33(clockwise_t, x_t, MKS<T,dim::Angle>v) : Tensor33(CCW, X, -v) {}

    template <typename T>
    template <typename>
    requires std::is_floating_point_v<T>
    Tensor33<T>::Tensor33(ccw_t, y_t, MKS<T,dim::Angle>v) : Tensor33(IDENTITY)
    {
        auto c  = cos(v);
        auto s  = sin(v);
        
        xx  = c;
        xz  = -s;
        zx  = s;
        zz  = c;
    }
    

    template <typename T>
    template <typename>
    requires std::is_floating_point_v<T>
    Tensor33<T>::Tensor33(clockwise_t, y_t, MKS<T,dim::Angle>v) : Tensor33(CCW, Y, -v) {}

    template <typename T>
    template <typename>
    requires std::is_floating_point_v<T>
    Tensor33<T>::Tensor33(ccw_t, z_t, MKS<T,dim::Angle>v) : Tensor33(IDENTITY)
    {
        auto c  = cos(v);
        auto s  = sin(v);
        
        yy  = c;
        yz  = -s;
        zy  = s;
        zz  = c;
    }

    template <typename T>
    template <typename>
    requires std::is_floating_point_v<T>
    Tensor33<T>::Tensor33(clockwise_t, z_t, MKS<T,dim::Angle>v) : Tensor33(CCW, Z, -v) {}

    template <typename T>
        template <glm::qualifier Q>
    constexpr Tensor33<T>::Tensor33(const glm::mat<3,3,T,Q>& t) noexcept :
        xx(t.x.x), xy(t.y.x), xz(t.z.x),
        yx(t.x.y), yy(t.y.y), yz(t.z.y),
        zx(t.x.z), zy(t.y.z), zz(t.z.z)
    {
    }

    template <typename T>
    constexpr Tensor33<T>::operator glm::mat<3,3,T,glm::defaultp>() const noexcept 
    {
        return glm::mat<3,3,T,glm::defaultp>(
            xx, yx, zx, 
            xy, yy, zy, 
            xz, yz, zz
        );
    }

    template <typename T>
    constexpr Tensor33<T>  Tensor33<T>::operator+() const noexcept
    { 
        return *this; 
    }

    template <typename T>
    constexpr Tensor33<T>  Tensor33<T>::operator-() const noexcept
    {
        return Tensor33(
            -xx, -xy, -xz,
            -yx, -yy, -yz,
            -zx, -zy, -zz
        );
    }


    template <typename T>
    constexpr Tensor33<T>   Tensor33<T>::operator+ (const Tensor33<T> &b) const noexcept
    {
        return Tensor33(
            xx+b.xx, xy+b.xy, xz+b.xz,
            yx+b.yx, yy+b.yy, yz+b.yz,
            zx+b.zx, zy+b.zy, zz+b.zz
        );
    }

    template <typename T>
    Tensor33<T>&   Tensor33<T>::operator+=(const Tensor33<T> &b) noexcept
    {
        xx+=b.xx;  xy+=b.xy;  xz+=b.xz;
        yx+=b.yx;  yy+=b.yy;  yz+=b.yz;
        zx+=b.zx;  zy+=b.zy;  zz+=b.zz;
        return *this;
    }


    template <typename T>
    constexpr Tensor33<T>   Tensor33<T>::operator- (const Tensor33<T> &b) const noexcept
    {
        return Tensor33(
            xx-b.xx, xy-b.xy, xz-b.xz,
            yx-b.yx, yy-b.yy, yz-b.yz,
            zx-b.zx, zy-b.zy, zz-b.zz
        );
    }
    

    template <typename T>
    Tensor33<T>&   Tensor33<T>::operator-=(const Tensor33<T> &b) noexcept
    {
        xx-=b.xx;  xy-=b.xy;  xz-=b.xz;
        yx-=b.yx;  yy-=b.yy;  yz-=b.yz;
        zx-=b.zx;  zy-=b.zy;  zz-=b.zz;
        return *this;
    }


    template <typename T>
        template <typename U>
    requires trait::is_arithmetic_v<U>
    constexpr Tensor33<product_t<T,U>>  Tensor33<T>::operator*(U b) const noexcept
    {
        return Tensor33<product_t<T,U>>(
            xx*b, xy*b, xz*b,
            yx*b, yy*b, yz*b,
            zx*b, zy*b, zz*b
        );
    }
    
    template <typename T>
        template <typename U>
    requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Tensor33<T>&  Tensor33<T>::operator*=(U b) noexcept
    {
        xx*=b; xy*=b; xz*=b;
        yx*=b; yy*=b; yz*=b;
        zx*=b; zy*=b; zz*=b;        
        return *this;
    }

    template <typename T>
        template <typename U>
    constexpr Segment3<product_t<T,U>>  Tensor33<T>::operator*(const Segment3<U>&rhs) const noexcept
    {
        return Segment3<product_t<T,U>>( *this * rhs.a, *this * rhs.b );
    }

    template <typename T>
        template <typename U>
    constexpr Tensor31<product_t<T,U>> Tensor33<T>::operator*(const Tensor31<U>& b) const noexcept
    {
        return Tensor31<product_t<T,U>>(
            xx*b.xx + xy*b.yx + xz*b.zx,

            yx*b.xx + yy*b.yx + yz*b.zx,

            zx*b.xx + zy*b.yx + zz*b.zx
        );
    }
    
    template <typename T>
        template <typename U>
    constexpr Tensor32<product_t<T,U>> Tensor33<T>::operator*(const Tensor32<U>& b) const noexcept
    {
        return Tensor32<product_t<T,U>>(
            xx*b.xx + xy*b.yx + xz*b.zx,
            xx*b.xy + xy*b.yy + xz*b.zy,

            yx*b.xx + yy*b.yx + yz*b.zx,
            yx*b.xy + yy*b.yy + yz*b.zy,

            zx*b.xx + zy*b.yx + zz*b.zx,
            zx*b.xy + zy*b.yy + zz*b.zy
        );
    }

    template <typename T>
        template <typename U>
    constexpr Tensor33<product_t<T,U>> Tensor33<T>::operator*(const Tensor33<U>& b) const noexcept
    {
        return Tensor33<product_t<T,U>>(
            xx*b.xx + xy*b.yx + xz*b.zx,
            xx*b.xy + xy*b.yy + xz*b.zy,
            xx*b.xz + xy*b.yz + xz*b.zz,

            yx*b.xx + yy*b.yx + yz*b.zx,
            yx*b.xy + yy*b.yy + yz*b.zy,
            yx*b.xz + yy*b.yz + yz*b.zz,

            zx*b.xx + zy*b.yx + zz*b.zx,
            zx*b.xy + zy*b.yy + zz*b.zy,
            zx*b.xz + zy*b.yz + zz*b.zz
        );
    }
    
    template <typename T>
        template <typename U>
    requires trait::self_mul_v<T,U>
    Tensor33<T>& Tensor33<T>::operator*=(const Tensor33<U>& b) noexcept
    {
        *this = *this * b;
        return *this;
    }

    template <typename T>
        template <typename U>
    constexpr Tensor34<product_t<T,U>> Tensor33<T>::operator*(const Tensor34<U>& b) const noexcept
    {
        return Tensor34<product_t<T,U>>(
            xx*b.xx + xy*b.yx + xz*b.zx,
            xx*b.xy + xy*b.yy + xz*b.zy,
            xx*b.xz + xy*b.yz + xz*b.zz,
            xx*b.xw + xy*b.yw + xz*b.zw,

            yx*b.xx + yy*b.yx + yz*b.zx,
            yx*b.xy + yy*b.yy + yz*b.zy,
            yx*b.xz + yy*b.yz + yz*b.zz,
            yx*b.xw + yy*b.yw + yz*b.zw,

            zx*b.xx + zy*b.yx + zz*b.zx,
            zx*b.xy + zy*b.yy + zz*b.zy,
            zx*b.xz + zy*b.yz + zz*b.zz,
            zx*b.xw + zy*b.yw + zz*b.zw
        );
    }
        
    template <typename T>
        template <typename U>
    constexpr Vector3<product_t<T,U>> Tensor33<T>::operator*(const Vector3<U>&b) const noexcept
    {
        return Vector3<product_t<T,U>>(
            xx*b.x + xy*b.y + xz*b.z,
            yx*b.x + yy*b.y + yz*b.z,
            zx*b.x + zy*b.y + zz*b.z
        );
    }


    template <typename T>
        template <typename U>
    requires trait::is_arithmetic_v<U>
    constexpr Tensor33<quotient_t<T,U>>  Tensor33<T>::operator/(U b) const noexcept
    {
        return Tensor33<quotient_t<T,U>>(
            xx/b, xy/b, xz/b,
            yx/b, yy/b, yz/b,
            zx/b, zy/b, zz/b
        );
    }
    
    template <typename T>
        template <typename U>
    requires (trait::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Tensor33<T>&  Tensor33<T>::operator/=(U b) noexcept
    {
        xx/=b; xy/=b; xz/=b;
        yx/=b; yy/=b; yz/=b;
        zx/=b; zy/=b; zz/=b;        
        return *this;
    }

    template <typename T>
    constexpr cube_t<T> Tensor33<T>::determinant() const noexcept
    {
        return xx*(yy*zz-yz*zy)+xy*(zx*xz-yx*zz)+xz*(yx*zy-zx*yy);
    }
 
    //  TODO: 3x3 eigenvalues, eigenvectors, & eigensystem
    

    template <typename T>
    constexpr Vector3<T>  Tensor33<T>::diagonal() const noexcept
    {
        return Vector3<T>(xx, yy, zz);
    }

    template <typename T>
    Tensor33<T>&  Tensor33<T>::diagonal(const Vector3<T>& v)
    {
        xx = v.x;
        yy = v.y;
        zz = v.z;
        return *this;
    }


    template <typename T>
    Tensor33<T>&  Tensor33<T>::diagonal(T _xx, T _yy, T _zz)
    {
        xx = _xx;
        yy = _yy;
        zz = _zz;
        return *this;
    }
        
    template <typename T>
    constexpr Tensor33<inverse_t<T>> Tensor33<T>::inverse() const noexcept
    {
        auto    di = one_v<T> / determinant();
        return Tensor33<inverse_t<T>>(
            di*(yy*zz-zy*yz), di*(xz*zy-zz*xy), di*(xy*yz-yy*xz),
            di*(yz*zx-zz*yx), di*(xx*zz-xz*zx), di*(xz*yx-yz*xx),
            di*(yx*zy-zx*yy), di*(xy*zx-zy*xx), di*(xx*yy-yx*xy)
        );
    }
    
    template <typename T>
    constexpr T     Tensor33<T>::trace() const noexcept
    {
        return xx+yy+zz;
    }

    template <typename T>
    constexpr Tensor33<T>  Tensor33<T>::transpose() const noexcept
    {
        return Tensor33(
            xx, yx, zx,
            xy, yy, zy,
            xz, yz, zz
        );
    }


    template <typename T>
    constexpr Vector3<T>  Tensor33<T>::x_column() const noexcept
    {
        return Vector3<T>(xx, yx, zx);
    }


    template <typename T>
    Tensor33<T>& Tensor33<T>::x_column(const Vector3<T>& v)
    {
        xx = v.x;
        yx = v.y;
        zx = v.z;
        return *this;
    }

    template <typename T>
    Tensor33<T>& Tensor33<T>::x_column(T _xx, T _yx, T _zx)
    {
        xx = _xx;
        yx = _yx;
        zx = _zx;
        return *this;
    }

    template <typename T>
    constexpr Vector3<T>  Tensor33<T>::x_row() const noexcept
    {
        return Vector3<T>(xx, xy, xz);
    }

    template <typename T>
    Tensor33<T>& Tensor33<T>::x_row(const Vector3<T>& v)
    {
        xx = v.x;
        xy = v.y;
        xz = v.z;
        return *this;
    }

    template <typename T>
    Tensor33<T>& Tensor33<T>::x_row(T _xx, T _xy, T _xz)
    {
        xx = _xx;
        xy = _xy;
        xz = _xz;
        return *this;
    }

    template <typename T>
    constexpr Vector3<T>  Tensor33<T>::y_column() const noexcept
    {
        return Vector3<T>(xy, yy, zy);
    }

    template <typename T>
    Tensor33<T>& Tensor33<T>::y_column(const Vector3<T>& v)
    {
        xy = v.x;
        yy = v.y;
        zy = v.z;
        return *this;
    }

    template <typename T>
    Tensor33<T>& Tensor33<T>::y_column(T _xy, T _yy, T _zy)
    {
        xy = _xy;
        yy = _yy;
        zy = _zy;
        return *this;
    }

    template <typename T>
    constexpr Vector3<T>  Tensor33<T>::y_row() const noexcept
    {
        return Vector3<T>(yx, yy, yz);
    }

    template <typename T>
    Tensor33<T>& Tensor33<T>::y_row(const Vector3<T>& v)
    {
        yx = v.x;
        yy = v.y;
        yz = v.z;
        return *this;
    }

    template <typename T>
    Tensor33<T>& Tensor33<T>::y_row(T _yx, T _yy, T _yz)
    {
        yx = _yx;
        yy = _yy;
        yz = _yz;
        return *this;
    }

    template <typename T>
    constexpr Vector3<T>  Tensor33<T>::z_column() const noexcept
    {
        return Vector3<T>(xz, yz, zz);
    }


    template <typename T>
    Tensor33<T>& Tensor33<T>::z_column(const Vector3<T>& v)
    {
        xz = v.x;
        yz = v.y;
        zz = v.z;
        return *this;
    }

    template <typename T>
    Tensor33<T>& Tensor33<T>::z_column(T _xz, T _yz, T _zz)
    {
        xz = _xz;
        yz = _yz;
        zz = _zz;
        return *this;
    }


    template <typename T>
    constexpr Vector3<T>  Tensor33<T>::z_row() const noexcept
    {
        return Vector3<T>(zx, zy, zz);
    }


    template <typename T>
    Tensor33<T>& Tensor33<T>::z_row(const Vector3<T>& v)
    {
        zx = v.x;
        zy = v.y;
        zz = v.z;
        return *this;
    }

    template <typename T>
    Tensor33<T>& Tensor33<T>::z_row(T _zx, T _zy, T _zz)
    {
        zx = _zx;
        zy = _zy;
        zz = _zz;
        return *this;
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename T, typename U>
    requires trait::is_arithmetic_v<T>
    constexpr Tensor33<product_t<T,U>>  operator*(T a, const Tensor33<U>& b)
    {
        return {
            a*b.xx, a*b.xy, a*b.xz,
            a*b.yx, a*b.yy, a*b.yz,
            a*b.zx, a*b.zy, a*b.zz
        };
    }

    template <typename T>
    cube_t<T> determinant(const Tensor33<T>& ten)
    {
        return ten.determinant();
    }

    template <typename T>
    constexpr Vector3<T>  diagonal(const Tensor33<T>&ten)
    {
        return ten.diagonal();
    }

    template <typename T>
    Tensor33<T> hpr33(MKS<T,dim::Angle> hdg, MKS<T,dim::Angle> pitch, MKS<T,dim::Angle> roll)
    {
        return Tensor33<T>(HPR, hdg, pitch, roll);
    }

    template <typename T>
    Tensor33<inverse_t<T>> inverse(const Tensor33<T>&ten)
    {
        return ten.inverse();
    }

    template <typename T>
    constexpr Tensor33<T>   rotation3X(MKS<T,dim::Angle> r)
    {
        return Tensor33<T>(CCW, X, r);
    }

    template <typename T>
    constexpr Tensor33<T>   rotation3Y(MKS<T,dim::Angle> r)
    {
        return Tensor33<T>(CCW, Y, r);
    }

    template <typename T>
    constexpr Tensor33<T>   rotation3Z(MKS<T,dim::Angle> r)
    {
        return Tensor33<T>(CCW, Z, r);
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    Tensor33<T>     tensor(const Quaternion3<T>& q)
    {
        return Tensor33<T>(q);
    }

    template <typename T, glm::qualifier Q>
    constexpr Tensor33<T> tensor(const glm::mat<3,3,T,Q>& t)
    {
        return Tensor33<T>(t);
    }
    
    template <typename T>
    constexpr T     trace(const Tensor33<T>& ten)
    {
        return ten.trace();
    }

    template <typename T>
    constexpr Tensor33<T>  transpose(const Tensor33<T>&ten)
    {
        return ten.transpose();
    }

    template <typename T>
    constexpr Vector3<T>  x_column(const Tensor33<T>&ten) 
    {
        return ten.x_column();
    }

    //! Y-column of provided tensor
    template <typename T>
    constexpr Vector3<T>  y_column(const Tensor33<T>&ten) 
    {
        return ten.y_column();
    }

    //! Z-column of provided tensor
    template <typename T>
    constexpr Vector3<T>  z_column(const Tensor33<T>&ten) 
    {
        return ten.z_column();
    }

    //! X-row of provided tensor
    template <typename T>
    constexpr Vector3<T>  x_row(const Tensor33<T>&ten)
    {
        return ten.x_row();
    }

    //! Y-row of provided tensor
    template <typename T>
    constexpr Vector3<T>  y_row(const Tensor33<T>&ten)
    {
        return ten.y_row();
    }

    //! Z-row of provided tensor
    template <typename T>
    constexpr Vector3<T>  z_row(const Tensor33<T>&ten)
    {
        return ten.z_row();
    }
}
