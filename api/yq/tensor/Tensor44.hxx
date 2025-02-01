////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the tensor44 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <yq/tensor/Tensor44.hpp>
#include <yq/math/utility.hpp>

#include <yq/math/AllComponents.hpp>
#include <yq/math/AnyComponents.hpp>
#include <sstream>

namespace yq {

    #if defined(YQ_MATH_TENSOR_3_3_HPP) && defined(YQ_MATH_VECTOR_3_HPP)
    template <typename T>
    constexpr Tensor44<T>::Tensor44(const Tensor33<T>& t33, const Vector3<T>& wcol, const Vector3<T>& wrow, T _ww) noexcept :
        xx(t33.xx), xy(t33.yx), xz(t33.zx), xw(wcol.x),
        yx(t33.xy), yy(t33.yy), yz(t33.zy), yw(wcol.y),
        zx(t33.xz), zy(t33.yz), zz(t33.zz), zw(wcol.z),
        wx(wrow.x), wy(wrow.y), wz(wrow.z), ww(_ww)
    {
    }
    #endif
    
    #ifdef YQ_USE_GLM
    template <typename T>
        template <glm::qualifier Q>
    constexpr Tensor44<T>::Tensor44(const glm::mat<4,4,T,Q>& t) noexcept :
        xx(t[0][0]), xy(t[1][0]), xz(t[2][0]), xw(t[3][0]),
        yx(t[0][1]), yy(t[1][1]), yz(t[2][1]), yw(t[3][1]),
        zx(t[0][2]), zy(t[1][2]), zz(t[2][2]), zw(t[3][2]),
        wx(t[0][3]), wy(t[1][3]), wz(t[2][3]), ww(t[3][3])
    {
    }
    #endif

    #ifdef YQ_USE_GLM
    template <typename T>
    constexpr Tensor44<T>::operator glm::mat<4,4,T,glm::defaultp>() const noexcept 
    {
        return glm::mat<4,4,T,glm::defaultp>(
            xx, yx, zx, wx,
            xy, yy, zy, wy,
            xz, yz, zz, wz,
            xw, yw, zw, ww
        );
    }
    #endif


    template <typename T>
    constexpr Tensor44<T>  Tensor44<T>::operator+() const noexcept
    { 
        return *this; 
    }

    template <typename T>
    constexpr Tensor44<T>  Tensor44<T>::operator-() const noexcept
    {
        return Tensor44(
            -xx, -xy, -xz, -xw,
            -yx, -yy, -yz, -yw,
            -zx, -zy, -zz, -zw,
            -wx, -wy, -wz, -ww
        );
    }

    template <typename T>
    constexpr Tensor44<T>   Tensor44<T>::operator+ (const Tensor44<T> &b) const noexcept
    {
        return Tensor44<T>(
            xx+b.xx, xy+b.xy, xz+b.xz, xw+b.xw,
            yx+b.yx, yy+b.yy, yz+b.yz, yw+b.yw,
            zx+b.zx, zy+b.zy, zz+b.zz, zw+b.zw,
            wx+b.wx, wy+b.wy, wz+b.wz, ww+b.ww
        );
    }

    template <typename T>
    Tensor44<T>&   Tensor44<T>::operator+=(const Tensor44<T> &b)  noexcept
    {
        xx+=b.xx;  xy+=b.xy;  xz+=b.xz;  xw+=b.xw;
        yx+=b.yx;  yy+=b.yy;  yz+=b.yz;  yw+=b.yw;
        zx+=b.zx;  zy+=b.zy;  zz+=b.zz;  zw+=b.zw;
        wx+=b.wx;  wy+=b.wy;  wz+=b.wz;  ww+=b.ww;
        return *this;
    }


    template <typename T>
    constexpr Tensor44<T>   Tensor44<T>::operator- (const Tensor44<T> &b)  const noexcept
    {
        return Tensor44<T>(
            xx-b.xx, xy-b.xy, xz-b.xz, xw-b.xw,
            yx-b.yx, yy-b.yy, yz-b.yz, yw-b.yw,
            zx-b.zx, zy-b.zy, zz-b.zz, zw-b.zw,
            wx-b.wx, wy-b.wy, wz-b.wz, ww-b.ww
        );
    }
    

    template <typename T>
    Tensor44<T>&   Tensor44<T>::operator-=(const Tensor44<T> &b)  noexcept
    {
        xx-=b.xx;  xy-=b.xy;  xz-=b.xz;  xw-=b.xw;
        yx-=b.yx;  yy-=b.yy;  yz-=b.yz;  yw-=b.yw;
        zx-=b.zx;  zy-=b.zy;  zz-=b.zz;  zw-=b.zw;
        wx-=b.wx;  wy-=b.wy;  wz-=b.wz;  ww-=b.ww;
        return *this;
    }

    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    constexpr Tensor44<product_t<T,U>>  Tensor44<T>::operator*(U b) const noexcept
    {
        return Tensor44<product_t<T,U>>(
            xx*b, xy*b, xz*b, xw*b,
            yx*b, yy*b, yz*b, yw*b,
            zx*b, zy*b, zz*b, zw*b,
            wx*b, wy*b, wz*b, ww*b
        );
    }
    
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
    Tensor44<T>& Tensor44<T>::operator*=(U b) const noexcept
    {
        xx*=b; xy*=b; xz*=b; xw*=b;
        yx*=b; yy*=b; yz*=b; yw*=b;
        zx*=b; zy*=b; zz*=b; zw*=b;
        wx*=b; wy*=b; wz*=b; ww*=b;        
        return *this;
    }

    #ifdef YQ_MATH_POLYGON4_HPP
    template <typename T>
        template <typename U>
    Polygon4<product_t<T,U>>  Tensor44<T>::operator*(const Polygon4<U>&b) const
    {
        return Polygon4<product_t<T,U>>( *this * b.vertex );
    }
    #endif
    
    #ifdef YQ_MATH_POLYLINE4_HPP
    template <typename T>
        template <typename U>
    Polyline4<product_t<T,U>>  Tensor44<T>::operator*(const Polyline4<U>&b) const
    {
        return Polyline4<product_t<T,U>>( *this * b.vertex );
    }
    #endif

    #ifdef YQ_MATH_SEGMENT4_HPP
    template <typename T>
        template <typename U>
    constexpr Segment4<product_t<T,U>>  Tensor44<T>::operator*(const Segment4<U>&rhs) const noexcept
    {
        return Segment4<product_t<T,U>>( *this * rhs.a, *this * rhs.b );
    }
    #endif

    #ifdef YQ_MATH_TENSOR_4_1_HPP
    template <typename T>
        template <typename U>
    constexpr Tensor41<product_t<T,U>> Tensor44<T>::operator*(const Tensor41<U>& b) const noexcept
    {
        return Tensor41<product_t<T,U>>(
            xx*b.xx + xy*b.yx + xz*b.zx + xw*b.wx,

            yx*b.xx + yy*b.yx + yz*b.zx + yw*b.wx,

            zx*b.xx + zy*b.yx + zz*b.zx + zw*b.wx,

            wx*b.xx + wy*b.yx + wz*b.zx + ww*b.wx
        );
    }
    #endif
    
    #ifdef YQ_MATH_TENSOR_4_2_HPP
    template <typename T>
        template <typename U>
    constexpr Tensor42<product_t<T,U>> Tensor44<T>::operator*(const Tensor42<U>& b) const noexcept
    {
        return Tensor42<product_t<T,U>>(
            xx*b.xx + xy*b.yx + xz*b.zx + xw*b.wx,
            xx*b.xy + xy*b.yy + xz*b.zy + xw*b.wy,

            yx*b.xx + yy*b.yx + yz*b.zx + yw*b.wx,
            yx*b.xy + yy*b.yy + yz*b.zy + yw*b.wy,

            zx*b.xx + zy*b.yx + zz*b.zx + zw*b.wx,
            zx*b.xy + zy*b.yy + zz*b.zy + zw*b.wy,

            wx*b.xx + wy*b.yx + wz*b.zx + ww*b.wx,
            wx*b.xy + wy*b.yy + wz*b.zy + ww*b.wy
        );
    }
    #endif
    
    #ifdef YQ_MATH_TENSOR_4_3_HPP
    template <typename T>
        template <typename U>
    constexpr Tensor43<product_t<T,U>> Tensor44<T>::operator*(const Tensor43<U>& b) const noexcept
    {
        return Tensor43<product_t<T,U>>(
            xx*b.xx + xy*b.yx + xz*b.zx + xw*b.wx,
            xx*b.xy + xy*b.yy + xz*b.zy + xw*b.wy,
            xx*b.xz + xy*b.yz + xz*b.zz + xw*b.wz,

            yx*b.xx + yy*b.yx + yz*b.zx + yw*b.wx,
            yx*b.xy + yy*b.yy + yz*b.zy + yw*b.wy,
            yx*b.xz + yy*b.yz + yz*b.zz + yw*b.wz,

            zx*b.xx + zy*b.yx + zz*b.zx + zw*b.wx,
            zx*b.xy + zy*b.yy + zz*b.zy + zw*b.wy,
            zx*b.xz + zy*b.yz + zz*b.zz + zw*b.wz,

            wx*b.xx + wy*b.yx + wz*b.zx + ww*b.wx,
            wx*b.xy + wy*b.yy + wz*b.zy + ww*b.wy,
            wx*b.xz + wy*b.yz + wz*b.zz + ww*b.wz
        );
    }
    #endif

    template <typename T>
        template <typename U>
    constexpr Tensor44<product_t<T,U>> Tensor44<T>::operator*(const Tensor44<U>& b) const noexcept
    {
        return Tensor44<product_t<T,U>>(
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
            zx*b.xw + zy*b.yw + zz*b.zw + zw*b.ww,

            wx*b.xx + wy*b.yx + wz*b.zx + ww*b.wx,
            wx*b.xy + wy*b.yy + wz*b.zy + ww*b.wy,
            wx*b.xz + wy*b.yz + wz*b.zz + ww*b.wz,
            wx*b.xw + wy*b.yw + wz*b.zw + ww*b.ww
        );
    }
    

    template <typename T>
        template <typename U>
    requires self_multiply_v<T,U>
    Tensor44<T>& Tensor44<T>::operator*=(const Tensor44<U>& b) noexcept
    {
        *this = *this * b;
        return *this;
    }

    #ifdef YQ_MATH_TRIANGLE4_HPP
    template <typename T>
        template <typename U>
    Triangle4<product_t<T,U>> Tensor44<T>::operator*(const Triangle4<U>&rhs) const noexcept
    {
        return Triangle4<product_t<T,U>>( *this * rhs.a, *this * rhs.b, *this * rhs.c );
    }
    #endif
        
    template <typename T>
        template <typename U>
    constexpr Vector4<product_t<T,U>> Tensor44<T>::operator*(const Vector4<U>&b) const noexcept
    {
        return Vector4<product_t<T,U>>(
            xx*b.x + xy*b.y + xz*b.z + xw*b.w,
            yx*b.x + yy*b.y + yz*b.z + yw*b.w,
            zx*b.x + zy*b.y + zz*b.z + zw*b.w,
            wx*b.x + wy*b.y + wz*b.z + ww*b.w
        );
    }
    
    template <typename T>
        template <typename U>
    std::vector<Vector4<product_t<T,U>>>    Tensor44<T>::operator*(std::span<const Vector4<U>> bs) const
    {
        return transform(bs, [&](const Vector4<U>& b) -> Vector4<product_t<T,U>> {
            return *this * b;
        });
    }

    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    constexpr Tensor44<quotient_t<T,U>>  Tensor44<T>::operator/(U b) const noexcept
    {
        return Tensor44<quotient_t<T,U>>(
            xx/b, xy/b, xz/b, xw/b,
            yx/b, yy/b, yz/b, yw/b,
            zx/b, zy/b, zz/b, zw/b,
            wx/b, wy/b, wz/b, ww/b
        );
    }
    
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_divide_v<T,U>)
    Tensor44<T>&  Tensor44<T>::operator/=(U b) noexcept
    {
        xx/=b; xy/=b; xz/=b; xw/=b;
        yx/=b; yy/=b; yz/=b; yw/=b;
        zx/=b; zy/=b; zz/=b; zw/=b;
        wx/=b; wy/=b; wz/=b; ww/=b;        
        return *this;
    }


    template <typename T>
    constexpr Tensor44<T> Tensor44<T>::all_add(T b) const noexcept
    {
        return Tensor44( 
            xx+b, xy+b, xz+b, xw+b,
            yx+b, yy+b, yz+b, yw+b,
            zx+b, zy+b, zz+b, zw+b,
            wx+b, wy+b, wz+b, ww+b
         );
    }

    template <typename T>
    Tensor44<T>&    Tensor44<T>::all_decrement(T b) noexcept
    {
        xx-=b; xy-=b; xz-=b; xw-=b;
        yx-=b; yy-=b; yz-=b; yw-=b;
        zx-=b; zy-=b; zz-=b; zw-=b;
        wx-=b; wy-=b; wz-=b; ww-=b;
        return *this;
    }

    template <typename T>
    Tensor44<T>&    Tensor44<T>::all_increment(T b) noexcept
    {
        xx+=b; xy+=b; xz+=b; xw+=b;
        yx+=b; yy+=b; yz+=b; yw+=b;
        zx+=b; zy+=b; zz+=b; zw+=b;
        wx+=b; wy+=b; wz+=b; ww+=b;
        return *this;
    }
    
    template <typename T>
    constexpr Tensor44<T> Tensor44<T>::all_subtract(T b) const noexcept
    {
        return Tensor44( 
            xx-b, xy-b, xz-b, xw-b,
            yx-b, yy-b, yz-b, yw-b,
            zx-b, zy-b, zz-b, zw-b,
            wx-b, wy-b, wz-b, ww-b
         );
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Tensor44<T>::all_test(Pred pred) const noexcept
    {
        return 
            pred(xx) && pred(xy) && pred(xz) && pred(xw) &&
            pred(yx) && pred(yy) && pred(yz) && pred(yw) &&
            pred(zx) && pred(zy) && pred(zz) && pred(zw) &&
            pred(wx) && pred(wy) && pred(wz) && pred(ww)
        ;
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Tensor44<T>::all_test(const Tensor44& b, Pred pred) const noexcept
    {
        return 
            pred(xx, b.xx) && pred(xy, b.xy) && pred(xz, b.xz) && pred(xw, b.xw) &&
            pred(yx, b.yx) && pred(yy, b.yy) && pred(yz, b.yz) && pred(yw, b.yw) &&
            pred(zx, b.zx) && pred(zy, b.zy) && pred(zz, b.zz) && pred(zw, b.zw) &&
            pred(wx, b.wx) && pred(wy, b.wy) && pred(wz, b.wz) && pred(ww, b.ww)
        ;
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Tensor44<T>::all_test(T b, Pred pred) const noexcept
    {
        return 
            pred(xx, b) && pred(xy, b) && pred(xz, b) && pred(xw, b) &&
            pred(yx, b) && pred(yy, b) && pred(yz, b) && pred(yw, b) &&
            pred(zx, b) && pred(zy, b) && pred(zz, b) && pred(zw, b) &&
            pred(wx, b) && pred(wy, b) && pred(wz, b) && pred(ww, b) 
        ;
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Tensor44<T>::any_test(Pred pred) const noexcept
    {
        return 
            pred(xx) || pred(xy) || pred(xz) || pred(xw) ||
            pred(yx) || pred(yy) || pred(yz) || pred(yw) ||
            pred(zx) || pred(zy) || pred(zz) || pred(zw) ||
            pred(wx) || pred(wy) || pred(wz) || pred(ww)
        ;
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Tensor44<T>::any_test(const Tensor44& b, Pred pred) const noexcept
    {
        return 
            pred(xx, b.xx) || pred(xy, b.xy) || pred(xz, b.xz) || pred(xw, b.xw) ||
            pred(yx, b.yx) || pred(yy, b.yy) || pred(yz, b.yz) || pred(yw, b.yw) ||
            pred(zx, b.zx) || pred(zy, b.zy) || pred(zz, b.zz) || pred(zw, b.zw) ||
            pred(wx, b.wx) || pred(wy, b.wy) || pred(wz, b.wz) || pred(ww, b.ww)
        ;
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Tensor44<T>::any_test(T b, Pred pred) const noexcept
    {
        return 
            pred(xx, b) || pred(xy, b) || pred(xz, b) || pred(xw, b) ||
            pred(yx, b) || pred(yy, b) || pred(yz, b) || pred(yw, b) ||
            pred(zx, b) || pred(zy, b) || pred(zz, b) || pred(zw, b) ||
            pred(wx, b) || pred(wy, b) || pred(wz, b) || pred(ww, b) 
        ;
    }
            
    //  TODO: 4x4 determinant 

    template <typename T>
    constexpr Vector4<T>  Tensor44<T>::diagonal() const noexcept
    {
        return Vector4<T>(xx, yy, zz, ww);
    }

    template <typename T>
    Tensor44<T>&  Tensor44<T>::diagonal(const Vector4<T>& v) noexcept
    {        
        xx = v.x;
        yy = v.y;
        zz = v.z;
        ww = v.w;
        return *this;
    }

    template <typename T>
    Tensor44<T>&  Tensor44<T>::diagonal(T _xx, T _yy, T _zz, T _ww) noexcept
    {        
        xx = _xx;
        yy = _yy;
        zz = _zz;
        ww = _ww;
        return *this;
    }

    //  TODO: 4x4 inverse 
    //  TODO: 4x4 eigenvalues, eigenvectors, & eigensystem

    template <typename T>
    constexpr T     Tensor44<T>::trace() const noexcept
    {
        return xx+yy+zz+ww;
    }

    template <typename T>
    constexpr Tensor44<T> Tensor44<T>::transpose() const noexcept
    {
        return Tensor44(
            xx, yx, zx, wx,
            xy, yy, zy, wy,
            xz, yz, zz, wz,
            xw, yw, zw, ww
        );
    }

    template <typename T>
    constexpr Vector4<T>  Tensor44<T>::w_column() const noexcept
    {
        return Vector4<T>(xw, yw, zw, ww);
    }

    template <typename T>
    Tensor44<T>& Tensor44<T>::w_column(const Vector4<T>& v) noexcept
    {
        xw = v.x;
        yw = v.y;
        zw = v.z;
        ww = v.w;
        return *this;
    }

    template <typename T>
    Tensor44<T>& Tensor44<T>::w_column(T _xw, T _yw, T _zw, T _ww) noexcept
    {
        xw = _xw;
        yw = _yw;
        zw = _zw;
        ww = _ww;
        return *this;
    }

    template <typename T>
    constexpr Vector4<T>  Tensor44<T>::w_row() const noexcept
    {
        return Vector4<T>(wx, wy, wz, ww);
    }

    template <typename T>
    Tensor44<T>& Tensor44<T>::w_row(const Vector4<T>& v) noexcept
    {
        wx = v.x;
        wy = v.y;
        wz = v.z;
        ww = v.w;
        return *this;
    }

    template <typename T>
    Tensor44<T>& Tensor44<T>::w_row(T _wx, T _wy, T _wz, T _ww) noexcept
    {
        wx = _wx;
        wy = _wy;
        wz = _wz;
        ww = _ww;
        return *this;
    }

    template <typename T>
    constexpr Vector4<T>  Tensor44<T>::x_column() const noexcept
    {
        return Vector4<T>(xx, yx, zx, wx);
    }

    template <typename T>
    Tensor44<T>& Tensor44<T>::x_column(const Vector4<T>& v) noexcept
    {
        xx = v.x;
        yx = v.y;
        zx = v.z;
        wx = v.w;
        return *this;
    }

    template <typename T>
    Tensor44<T>& Tensor44<T>::x_column(T _xx, T _yx, T _zx, T _wx) noexcept
    {
        xx = _xx;
        yx = _yx;
        zx = _zx;
        wx = _wx;
        return *this;
    }
    

    template <typename T>
    constexpr Vector4<T>  Tensor44<T>::x_row() const noexcept
    {
        return Vector4<T>(xx, xy, xz, xw);
    }

    template <typename T>
    Tensor44<T>& Tensor44<T>::x_row(const Vector4<T>& v) noexcept
    {
        xx = v.x;
        xy = v.y;
        xz = v.z;
        xw = v.w;
        return *this;
    }

    template <typename T>
    Tensor44<T>& Tensor44<T>::x_row(T _xx, T _xy, T _xz, T _xw) noexcept
    {
        xx = _xx;
        xy = _xy;
        xz = _xz;
        xw = _xw;
        return *this;
    }


    template <typename T>
    constexpr Vector4<T>  Tensor44<T>::y_column() const noexcept
    {
        return Vector4<T>(xy, yy, zy, wy);
    }

    template <typename T>
    Tensor44<T>& Tensor44<T>::y_column(const Vector4<T>& v) noexcept
    {
        xy = v.x;
        yy = v.y;
        zy = v.z;
        wy = v.w;
        return *this;
    }

    template <typename T>
    Tensor44<T>& Tensor44<T>::y_column(T _xy, T _yy, T _zy, T _wy) noexcept
    {
        xy = _xy;
        yy = _yy;
        zy = _zy;
        wy = _wy;
        return *this;
    }

    template <typename T>
    constexpr Vector4<T>  Tensor44<T>::y_row() const noexcept
    {
        return Vector4<T>(yx, yy, yz, yw);
    }

    template <typename T>
    Tensor44<T>& Tensor44<T>::y_row(const Vector4<T>& v) noexcept
    {
        yx = v.x;
        yy = v.y;
        yz = v.z;
        yw = v.w;
        return *this;
    }

    template <typename T>
    Tensor44<T>& Tensor44<T>::y_row(T _yx, T _yy, T _yz, T _yw) noexcept
    {
        yx = _yx;
        yy = _yy;
        yz = _yz;
        yw = _yw;
        return *this;
    }
    
    template <typename T>
    constexpr Vector4<T>  Tensor44<T>::z_column() const noexcept
    {
        return Vector4<T>(xz, yz, zz, wz);
    }


    template <typename T>
    Tensor44<T>& Tensor44<T>::z_column(const Vector4<T>& v) noexcept
    {
        xz = v.x;
        yz = v.y;
        zz = v.z;
        wz = v.w;
        return *this;
    }

    template <typename T>
    Tensor44<T>& Tensor44<T>::z_column(T _xz, T _yz, T _zz, T _wz) noexcept
    {
        xz = _xz;
        yz = _yz;
        zz = _zz;
        wz = _wz;
        return *this;
    }

    template <typename T>
    constexpr Vector4<T>  Tensor44<T>::z_row() const noexcept
    {
        return Vector4<T>(zx, zy, zz, zw);
    }


    template <typename T>
    Tensor44<T>& Tensor44<T>::z_row(const Vector4<T>& v) noexcept
    {
        zx = v.x;
        zy = v.y;
        zz = v.z;
        zw = v.w;
        return *this;
    }

    template <typename T>
    Tensor44<T>& Tensor44<T>::z_row(T _zx, T _zy, T _zz, T _zw) noexcept
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
    requires is_arithmetic_v<T>
    constexpr Tensor44<product_t<T,U>>  operator*(T a, const Tensor44<U>& b) noexcept
    {
        return Tensor44<product_t<T,U>>(
            a*b.xx, a*b.xy, a*b.xz, a*b.xw,
            a*b.yx, a*b.yy, a*b.yz, a*b.yw,
            a*b.zx, a*b.zy, a*b.zz, a*b.zw,
            a*b.wx, a*b.wy, a*b.wz, a*b.ww
        );
    }

    template <typename T>
    AllComponents<Tensor44<T>>   all(Tensor44<T>& val)
    {
        return { val };
    }

    template <typename T>
    AllComponents<const Tensor44<T>>   all(const Tensor44<T>& val)
    {
        return { val };
    }
    
    template <typename T>
    AnyComponents<Tensor44<T>>   any(Tensor44<T>& val)
    {
        return { val };
    }

    template <typename T>
    AnyComponents<const Tensor44<T>>   any(const Tensor44<T>& val)
    {
        return { val };
    }

    template <typename T, typename U>
    requires has_nan_v<product_t<T,U>>
    constexpr Tensor44<product_t<T,U>>  comingle(const Tensor44<T>& a, const Tensor44<U>& b, const Tensor44<product_t<T,U>>& c)
    {
        return Tensor44<product_t<T,U>>(
            is_nan(c.xx) ? (a.xx*b.xx + a.xy*b.yx + a.xz*b.zx + a.xw*b.wx) : c.xx,
            is_nan(c.xy) ? (a.xx*b.xy + a.xy*b.yy + a.xz*b.zy + a.xw*b.wy) : c.xy,
            is_nan(c.xz) ? (a.xx*b.xz + a.xy*b.yz + a.xz*b.zz + a.xw*b.wz) : c.xz,
            is_nan(c.xw) ? (a.xx*b.xw + a.xy*b.yw + a.xz*b.zw + a.xw*b.ww) : c.xw,

            is_nan(c.yx) ? (a.yx*b.xx + a.yy*b.yx + a.yz*b.zx + a.yw*b.wx) : c.yx,
            is_nan(c.yy) ? (a.yx*b.xy + a.yy*b.yy + a.yz*b.zy + a.yw*b.wy) : c.yy,
            is_nan(c.yz) ? (a.yx*b.xz + a.yy*b.yz + a.yz*b.zz + a.yw*b.wz) : c.yz,
            is_nan(c.yw) ? (a.yx*b.xw + a.yy*b.yw + a.yz*b.zw + a.yw*b.ww) : c.yw,

            is_nan(c.zx) ? (a.zx*b.xx + a.zy*b.yx + a.zz*b.zx + a.zw*b.wx) : c.zx,
            is_nan(c.zy) ? (a.zx*b.xy + a.zy*b.yy + a.zz*b.zy + a.zw*b.wy) : c.zy,
            is_nan(c.zz) ? (a.zx*b.xz + a.zy*b.yz + a.zz*b.zz + a.zw*b.wz) : c.zz,
            is_nan(c.zw) ? (a.zx*b.xw + a.zy*b.yw + a.zz*b.zw + a.zw*b.ww) : c.zw,

            is_nan(c.wx) ? (a.wx*b.xx + a.wy*b.yx + a.wz*b.zx + a.ww*b.wx) : c.wx,
            is_nan(c.wy) ? (a.wx*b.xy + a.wy*b.yy + a.wz*b.zy + a.ww*b.wy) : c.wy,
            is_nan(c.wz) ? (a.wx*b.xz + a.wy*b.yz + a.wz*b.zz + a.ww*b.wz) : c.wz,
            is_nan(c.ww) ? (a.wx*b.xw + a.wy*b.yw + a.wz*b.zw + a.ww*b.ww) : c.ww
        );
    }

    //! Diagonal of given tensor
    template <typename T>
    constexpr Vector4<T>  diagonal(const Tensor44<T>&ten) noexcept
    {
        return ten.diagonal();
    }
    
    #if 0
    template <typename T>
    ElemComponents<Tensor44<T>>   elem(Tensor44<T>& val)
    {
        return { val };
    }

    template <typename T>
    ElemComponents<const Tensor44<T>>   elem(const Tensor44<T>& val)
    {
        return { val };
    }
    #endif

    //  TODO: 4x4 determinant 
    //  TODO: 4x4 inverse 
    //  TODO: 4x4 eigenvalues, eigenvectors, & eigensystem

    #ifdef YQ_USE_GLM
    template <typename T, glm::qualifier Q>
    constexpr Tensor44<T> tensor(const glm::mat<4,4,T,Q>& t) noexcept
    {
        return Tensor44<T>(t);
    }
    #endif

    template <typename T>
    constexpr T     trace(const Tensor44<T>& ten) noexcept
    {
        return ten.trace();
    }

    template <typename T>
    constexpr Tensor44<T>  transpose(const Tensor44<T>&ten) noexcept
    {
        return ten.transpose();
    }


    //! W-column of given tensor
    template <typename T>
    constexpr Vector4<T>  w_column(const Tensor44<T>&ten)  noexcept
    {
        return ten.w_column();
    }

    //! W-row of given tensor
    template <typename T>
    constexpr Vector4<T>  w_row(const Tensor44<T>&ten) noexcept
    {
        return ten.z_row();
    }

    //! X-column of given tensor
    template <typename T>
    constexpr Vector4<T>  x_column(const Tensor44<T>&ten)  noexcept
    {
        return ten.x_column();
    }

    //! X-row of given tensor
    template <typename T>
    constexpr Vector4<T>  x_row(const Tensor44<T>&ten) noexcept
    {
        return ten.x_row();
    }

    //! Y-column of given tensor
    template <typename T>
    constexpr Vector4<T>  y_column(const Tensor44<T>&ten)  noexcept
    {
        return ten.y_column();
    }

    //! Y-row of given tensor
    template <typename T>
    constexpr Vector4<T>  y_row(const Tensor44<T>&ten) noexcept
    {
        return ten.y_row();
    }

    //! Z-column of given tensor
    template <typename T>
    constexpr Vector4<T>  z_column(const Tensor44<T>&ten)  noexcept
    {
        return ten.z_column();
    }

    //! Z-row of given tensor
    template <typename T>
    constexpr Vector4<T>  z_row(const Tensor44<T>&ten) noexcept
    {
        return ten.z_row();
    }


    template <typename T>
    std::ostringstream& operator<<(std::ostringstream&oss, const Tensor44<T>&v)
    {
        oss << '[';
        oss << '[' << v.xx << ',' << v.xy << ',' << v.xz << ',' << v.xw << ']';
        oss << '[' << v.yx << ',' << v.yy << ',' << v.yz << ',' << v.yw << ']';
        oss << '[' << v.zx << ',' << v.zy << ',' << v.zz << ',' << v.zw << ']';
        oss << '[' << v.wx << ',' << v.wy << ',' << v.wz << ',' << v.ww << ']';
        oss << ']';
        return oss;
    }

}
