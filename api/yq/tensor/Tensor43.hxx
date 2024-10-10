////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the tensor43 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <yq-toolbox/tensor/Tensor43.hpp>
#include <yq-toolbox/math/utility.hpp>

#include <yq-toolbox/math/AllComponents.hpp>
#include <yq-toolbox/math/AnyComponents.hpp>


namespace yq {
    #ifdef YQ_USE_GLM
    template <typename T>
        template <glm::qualifier Q>
    constexpr Tensor43<T>::Tensor43(const glm::mat<4,3,T,Q>& t) noexcept :
        xx(t.x.x), xy(t.y.x), xz(t.z.x),
        yx(t.x.y), yy(t.y.y), yz(t.z.y),
        zx(t.x.z), zy(t.y.z), zz(t.z.z),
        wx(t.x.w), wy(t.y.w), wz(t.z.w)
    {
    }
    #endif

    #ifdef YQ_USE_GLM
    template <typename T>
    constexpr Tensor43<T>::operator glm::mat<4,3,T,glm::defaultp>() const noexcept 
    {
        return glm::mat<4,3,T,glm::defaultp>(
            xx, yx, zx, wx,
            xy, yy, zy, wy,
            xz, yz, zz, wz
        );
    }
    #endif

    template <typename T>
    constexpr Tensor43<T>  Tensor43<T>::operator+() const noexcept
    { 
        return *this; 
    }

    template <typename T>
    constexpr Tensor43<T>  Tensor43<T>::operator-() const noexcept
    {
        return Tensor43<T>(
            -xx, -xy, -xz,
            -yx, -yy, -yz,
            -zx, -zy, -zz,
            -wx, -wy, -wz
        );
    }

    template <typename T>
    constexpr Tensor43<T>   Tensor43<T>::operator+ (const Tensor43<T> &b)  const noexcept
    {
        return Tensor43<T>(
            xx+b.xx, xy+b.xy, xz+b.xz,
            yx+b.yx, yy+b.yy, yz+b.yz,
            zx+b.zx, zy+b.zy, zz+b.zz,
            wx+b.wx, wy+b.wy, wz+b.wz
        );
    }

    template <typename T>
    Tensor43<T>&   Tensor43<T>::operator+=(const Tensor43<T> &b)  noexcept
    {
        xx+=b.xx;  xy+=b.xy;  xz+=b.xz;
        yx+=b.yx;  yy+=b.yy;  yz+=b.yz;
        zx+=b.zx;  zy+=b.zy;  zz+=b.zz;
        wx+=b.wx;  wy+=b.wy;  wz+=b.wz;
        return *this;
    }

    template <typename T>
    constexpr Tensor43<T>   Tensor43<T>::operator- (const Tensor43<T> &b)  const noexcept
    {
        return Tensor43<T>(
            xx-b.xx, xy-b.xy, xz-b.xz,
            yx-b.yx, yy-b.yy, yz-b.yz,
            zx-b.zx, zy-b.zy, zz-b.zz,
            wx-b.wx, wy-b.wy, wz-b.wz
        );
    }
    

    template <typename T>
    Tensor43<T>&   Tensor43<T>::operator-=(const Tensor43<T> &b)  noexcept
    {
        xx-=b.xx;  xy-=b.xy;  xz-=b.xz;
        yx-=b.yx;  yy-=b.yy;  yz-=b.yz;
        zx-=b.zx;  zy-=b.zy;  zz-=b.zz;
        wx-=b.wx;  wy-=b.wy;  wz-=b.wz;
        return *this;
    }

    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    constexpr Tensor43<product_t<T,U>>  Tensor43<T>::operator*(U b) const noexcept
    {
        return Tensor43<product_t<T,U>>(
            xx*b, xy*b, xz*b,
            yx*b, yy*b, yz*b,
            zx*b, zy*b, zz*b,
            wx*b, wy*b, wz*b
        );
    }
    
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
    Tensor43<T>&  Tensor43<T>::operator*=(U b) noexcept
    {
        xx*=b; xy*=b; xz*=b;
        yx*=b; yy*=b; yz*=b;
        zx*=b; zy*=b; zz*=b;
        wx*=b; wy*=b; wz*=b;        
        return *this;
    }

    #if defined(YQ_MATH_POLYGON3_HPP) && defined(YQ_MATH_POLYGON4_HPP)
    template <typename T>
        template <typename U>
    Polygon4<product_t<T,U>>  Tensor43<T>::operator*(const Polygon3<U>&b) const
    {
        return Polygon4<product_t<T,U>>( *this * b.vertex );
    }
    #endif
    
    #if defined(YQ_MATH_POLYLINE3_HPP) && defined(YQ_MATH_POLYLINE4_HPP)
    template <typename T>
        template <typename U>
    Polyline4<product_t<T,U>>  Tensor43<T>::operator*(const Polyline3<U>&b) const
    {
        return Polyline4<product_t<T,U>>( *this * b.vertex );
    }
    #endif

    #if defined(YQ_MATH_SEGMENT3_HPP) && defined(YQ_MATH_SEGMENT4_HPP)
    template <typename T>
        template <typename U>
    constexpr Segment4<product_t<T,U>>  Tensor43<T>::operator*(const Segment3<U>&rhs) const noexcept
    {
        return Segment4<product_t<T,U>>( *this * rhs.a, *this * rhs.b );
    }
    #endif

    #if defined(YQ_MATH_TENSOR_3_1_HPP) && defined(YQ_MATH_TENSOR_4_1_HPP)
    template <typename T>
        template <typename U>
    constexpr Tensor41<product_t<T,U>> Tensor43<T>::operator*(const Tensor31<U>& b) const noexcept
    {
        return Tensor41<product_t<T,U>>(
            xx*b.xx + xy*b.yx + xz*b.zx,

            yx*b.xx + yy*b.yx + yz*b.zx,

            zx*b.xx + zy*b.yx + zz*b.zx,

            wx*b.xx + wy*b.yx + wz*b.zx
        );
    }
    #endif
    
    #if defined(YQ_MATH_TENSOR_3_2_HPP) && defined(YQ_MATH_TENSOR_4_2_HPP)
    template <typename T>
        template <typename U>
    constexpr Tensor42<product_t<T,U>> Tensor43<T>::operator*(const Tensor32<U>& b) const noexcept
    {
        return Tensor42<product_t<T,U>>(
            xx*b.xx + xy*b.yx + xz*b.zx,
            xx*b.xy + xy*b.yy + xz*b.zy,

            yx*b.xx + yy*b.yx + yz*b.zx,
            yx*b.xy + yy*b.yy + yz*b.zy,

            zx*b.xx + zy*b.yx + zz*b.zx,
            zx*b.xy + zy*b.yy + zz*b.zy,

            wx*b.xx + wy*b.yx + wz*b.zx,
            wx*b.xy + wy*b.yy + wz*b.zy
        );
    }
    #endif
    
    #ifdef YQ_MATH_TENSOR_4_4_HPP
    template <typename T>
        template <typename U>
    constexpr Tensor43<product_t<T,U>> Tensor43<T>::operator*(const Tensor33<U>& b) const noexcept
    {
        return Tensor43<product_t<T,U>>(
            xx*b.xx + xy*b.yx + xz*b.zx,
            xx*b.xy + xy*b.yy + xz*b.zy,
            xx*b.xz + xy*b.yz + xz*b.zz,

            yx*b.xx + yy*b.yx + yz*b.zx,
            yx*b.xy + yy*b.yy + yz*b.zy,
            yx*b.xz + yy*b.yz + yz*b.zz,

            zx*b.xx + zy*b.yx + zz*b.zx,
            zx*b.xy + zy*b.yy + zz*b.zy,
            zx*b.xz + zy*b.yz + zz*b.zz,

            wx*b.xx + wy*b.yx + wz*b.zx,
            wx*b.xy + wy*b.yy + wz*b.zy,
            wx*b.xz + wy*b.yz + wz*b.zz
        );
    }
    #endif
    
    #ifdef YQ_MATH_TENSOR_4_4_HPP
    template <typename T>
        template <typename U>
    requires self_multiply_v<T,U>
    Tensor43<T>& Tensor43<T>::operator*=(const Tensor33<U>& b) noexcept
    {
        *this = *this * b;
        return *this;
    }
    #endif

    #if defined(YQ_MATH_TENSOR_3_4_HPP) && defined(YQ_MATH_TENSOR_4_4_HPP)
    template <typename T>
        template <typename U>
    constexpr Tensor44<product_t<T,U>> Tensor43<T>::operator*(const Tensor34<U>& b) const noexcept
    {
        return Tensor44<product_t<T,U>>(
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
            zx*b.xw + zy*b.yw + zz*b.zw,

            wx*b.xx + wy*b.yx + wz*b.zx,
            wx*b.xy + wy*b.yy + wz*b.zy,
            wx*b.xz + wy*b.yz + wz*b.zz,
            wx*b.xw + wy*b.yw + wz*b.zw
        );
    }
    #endif
    
    #if defined(YQ_MATH_TRIANGLE3_HPP) && defined(YQ_MATH_TRIANGLE4_HPP)
    template <typename T>
        template <typename U>
    Triangle4<product_t<T,U>> Tensor43<T>::operator*(const Triangle3<U>&rhs) const noexcept
    {
        return Triangle4<product_t<T,U>>( *this * rhs.a, *this * rhs.b, *this * rhs.c );
    }
    #endif

    template <typename T>
        template <typename U>
    constexpr Vector4<product_t<T,U>> Tensor43<T>::operator*(const Vector3<U>&b) const noexcept
    {
        return Vector4<product_t<T,U>>(
            xx*b.x + xy*b.y + xz*b.z,
            yx*b.x + yy*b.y + yz*b.z,
            zx*b.x + zy*b.y + zz*b.z,
            wx*b.x + wy*b.y + wz*b.z
        );
    }

    template <typename T>
        template <typename U>
    std::vector<Vector4<product_t<T,U>>>    Tensor43<T>::operator*(std::span<const Vector3<U>> bs) const
    {
        return transform(bs, [&](const Vector3<U>& b) -> Vector4<product_t<T,U>> {
            return *this * b;
        });
    }

    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    constexpr Tensor43<quotient_t<T,U>>  Tensor43<T>::operator/(U b) const noexcept
    {
        return Tensor43<quotient_t<T,U>>(
            xx/b, xy/b, xz/b,
            yx/b, yy/b, yz/b,
            zx/b, zy/b, zz/b,
            wx/b, wy/b, wz/b
        );
    }
    
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_divide_v<T,U>)
    Tensor43<T>&  Tensor43<T>::operator/=(U b) noexcept
    {
        xx/=b; xy/=b; xz/=b;
        yx/=b; yy/=b; yz/=b;
        zx/=b; zy/=b; zz/=b;
        wx/=b; wy/=b; wz/=b;        
        return *this;
    }


    template <typename T>
    constexpr Tensor43<T> Tensor43<T>::all_add(T b) const noexcept
    {
        return Tensor43( 
            xx+b, xy+b, xz+b,
            yx+b, yy+b, yz+b,
            zx+b, zy+b, zz+b,
            wx+b, wy+b, wz+b
         );
    }

    template <typename T>
    Tensor43<T>&    Tensor43<T>::all_decrement(T b) noexcept
    {
        xx-=b; xy-=b; xz-=b;
        yx-=b; yy-=b; yz-=b;
        zx-=b; zy-=b; zz-=b;
        wx-=b; wy-=b; wz-=b;
        return *this;
    }

    template <typename T>
    Tensor43<T>&    Tensor43<T>::all_increment(T b) noexcept
    {
        xx+=b; xy+=b; xz+=b;
        yx+=b; yy+=b; yz+=b;
        zx+=b; zy+=b; zz+=b;
        wx+=b; wy+=b; wz+=b;
        return *this;
    }
    
    template <typename T>
    constexpr Tensor43<T> Tensor43<T>::all_subtract(T b) const noexcept
    {
        return Tensor43( 
            xx-b, xy-b, xz-b,
            yx-b, yy-b, yz-b,
            zx-b, zy-b, zz-b,
            wx-b, wy-b, wz-b
         );
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Tensor43<T>::all_test(Pred pred) const noexcept
    {
        return 
            pred(xx) && pred(xy) && pred(xz) && 
            pred(yx) && pred(yy) && pred(yz) && 
            pred(zx) && pred(zy) && pred(zz) && 
            pred(wx) && pred(wy) && pred(wz) 
        ;
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Tensor43<T>::all_test(const Tensor43& b, Pred pred) const noexcept
    {
        return 
            pred(xx, b.xx) && pred(xy, b.xy) && pred(xz, b.xz) && 
            pred(yx, b.yx) && pred(yy, b.yy) && pred(yz, b.yz) && 
            pred(zx, b.zx) && pred(zy, b.zy) && pred(zz, b.zz) && 
            pred(wx, b.wx) && pred(wy, b.wy) && pred(wz, b.wz)
        ;
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Tensor43<T>::all_test(T b, Pred pred) const noexcept
    {
        return 
            pred(xx, b) && pred(xy, b) && pred(xz, b) && 
            pred(yx, b) && pred(yy, b) && pred(yz, b) && 
            pred(zx, b) && pred(zy, b) && pred(zz, b) && 
            pred(wx, b) && pred(wy, b) && pred(wz, b) 
        ;
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Tensor43<T>::any_test(Pred pred) const noexcept
    {
        return 
            pred(xx) || pred(xy) || pred(xz) || 
            pred(yx) || pred(yy) || pred(yz) || 
            pred(zx) || pred(zy) || pred(zz) || 
            pred(wx) || pred(wy) || pred(wz)
        ;
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Tensor43<T>::any_test(const Tensor43& b, Pred pred) const noexcept
    {
        return 
            pred(xx, b.xx) || pred(xy, b.xy) || pred(xz, b.xz) ||
            pred(yx, b.yx) || pred(yy, b.yy) || pred(yz, b.yz) ||
            pred(zx, b.zx) || pred(zy, b.zy) || pred(zz, b.zz) ||
            pred(wx, b.wx) || pred(wy, b.wy) || pred(wz, b.wz)
        ;
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Tensor43<T>::any_test(T b, Pred pred) const noexcept
    {
        return 
            pred(xx, b) || pred(xy, b) || pred(xz, b) || 
            pred(yx, b) || pred(yy, b) || pred(yz, b) || 
            pred(zx, b) || pred(zy, b) || pred(zz, b) || 
            pred(wx, b) || pred(wy, b) || pred(wz, b)
        ;
    }
     
    #ifdef YQ_MATH_TENSOR_3_4_HPP
    template <typename T>
    constexpr Tensor34<T>   Tensor43<T>::transpose() const noexcept
    {
        return Tensor34<T>(
            xx, yx, zx, wx,
            xy, yy, zy, wy,
            xz, yz, zz, wz
        );
    }
    #endif

    template <typename T>
    constexpr Vector3<T>  Tensor43<T>::w_row() const noexcept
    {
        return Vector3<T>(wx, wy, wz);
    }

    template <typename T>
    Tensor43<T>& Tensor43<T>::w_row(const Vector3<T>& v) noexcept
    {
        wx = v.x;
        wy = v.y;
        wz = v.z;
        return *this;
    }

    template <typename T>
    Tensor43<T>& Tensor43<T>::w_row(T _wx, T _wy, T _wz) noexcept
    {
        wx = _wx;
        wy = _wy;
        wz = _wz;
        return *this;
    }


    template <typename T>
    constexpr Vector4<T>  Tensor43<T>::x_column() const noexcept
    {
        return Vector4<T>(xx, yx, zx, wx);
    }


    template <typename T>
    Tensor43<T>& Tensor43<T>::x_column(const Vector4<T>& v) noexcept
    {
        xx = v.x;
        yx = v.y;
        zx = v.z;
        wx = v.w;
        return *this;
    }

    template <typename T>
    Tensor43<T>& Tensor43<T>::x_column(T _xx, T _yx, T _zx, T _wx) noexcept
    {
        xx = _xx;
        yx = _yx;
        zx = _zx;
        wx = _wx;
        return *this;
    }

    template <typename T>
    constexpr Vector3<T>  Tensor43<T>::x_row() const noexcept
    {
        return Vector3<T>(xx, xy, xz);
    }

    template <typename T>
    Tensor43<T>& Tensor43<T>::x_row(const Vector3<T>& v) noexcept
    {
        xx = v.x;
        xy = v.y;
        xz = v.z;
        return *this;
    }

    template <typename T>
    Tensor43<T>& Tensor43<T>::x_row(T _xx, T _xy, T _xz) noexcept
    {
        xx = _xx;
        xy = _xy;
        xz = _xz;
        return *this;
    }

    template <typename T>
    constexpr Vector4<T>  Tensor43<T>::y_column() const noexcept
    {
        return Vector4<T>(xy, yy, zy, wy);
    }

    template <typename T>
    Tensor43<T>& Tensor43<T>::y_column(const Vector4<T>& v) noexcept
    {
        xy = v.x;
        yy = v.y;
        zy = v.z;
        wy = v.w;
        return *this;
    }

    template <typename T>
    Tensor43<T>& Tensor43<T>::y_column(T _xy, T _yy, T _zy, T _wy) noexcept
    {
        xy = _xy;
        yy = _yy;
        zy = _zy;
        wy = _wy;
        return *this;
    }

    template <typename T>
    constexpr Vector3<T>  Tensor43<T>::y_row() const noexcept
    {
        return Vector3<T>(yx, yy, yz);
    }

    template <typename T>
    Tensor43<T>& Tensor43<T>::y_row(const Vector3<T>& v) noexcept
    {
        yx = v.x;
        yy = v.y;
        yz = v.z;
        return *this;
    }

    template <typename T>
    Tensor43<T>& Tensor43<T>::y_row(T _yx, T _yy, T _yz) noexcept
    {
        yx = _yx;
        yy = _yy;
        yz = _yz;
        return *this;
    }

    template <typename T>
    constexpr Vector4<T>  Tensor43<T>::z_column() const noexcept
    {
        return Vector4<T>(xz, yz, zz, wz);
    }


    template <typename T>
    Tensor43<T>& Tensor43<T>::z_column(const Vector4<T>& v) noexcept
    {
        xz = v.x;
        yz = v.y;
        zz = v.z;
        wz = v.w;
        return *this;
    }

    template <typename T>
    Tensor43<T>& Tensor43<T>::z_column(T _xz, T _yz, T _zz, T _wz) noexcept
    {
        xz = _xz;
        yz = _yz;
        zz = _zz;
        wz = _wz;
        return *this;
    }

    template <typename T>
    constexpr Vector3<T>  Tensor43<T>::z_row() const noexcept
    {
        return Vector3<T>(zx, zy, zz);
    }

    template <typename T>
    Tensor43<T>& Tensor43<T>::z_row(const Vector3<T>& v) noexcept
    {
        zx = v.x;
        zy = v.y;
        zz = v.z;
        return *this;
    }
    template <typename T>
    Tensor43<T>& Tensor43<T>::z_row(T _zx, T _zy, T _zz) noexcept
    {
        zx = _zx;
        zy = _zy;
        zz = _zz;
        return *this;
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Tensor43<product_t<T,U>>  operator*(T a, const Tensor43<T>& b) noexcept
    {
        return Tensor43<product_t<T,U>>(
            a*b.xx, a*b.xy, a*b.xz,
            a*b.yx, a*b.yy, a*b.yz,
            a*b.zx, a*b.zy, a*b.zz,
            a*b.wx, a*b.wy, a*b.wz
        );
    }

    template <typename T>
    AllComponents<Tensor43<T>>   all(Tensor43<T>& val)
    {
        return { val };
    }

    template <typename T>
    AllComponents<const Tensor43<T>>   all(const Tensor43<T>& val)
    {
        return { val };
    }
    
    template <typename T>
    AnyComponents<Tensor43<T>>   any(Tensor43<T>& val)
    {
        return { val };
    }

    template <typename T>
    AnyComponents<const Tensor43<T>>   any(const Tensor43<T>& val)
    {
        return { val };
    }
    
    #if 0
    template <typename T>
    ElemComponents<Tensor43<T>>   elem(Tensor43<T>& val)
    {
        return { val };
    }

    template <typename T>
    ElemComponents<const Tensor43<T>>   elem(const Tensor43<T>& val)
    {
        return { val };
    }
    #endif
    
    #ifdef YQ_MATH_TENSOR_3_4_HPP
    template <typename T>
    constexpr Tensor34<T>  transpose(const Tensor43<T>&v)
    {
        return v.transpose();
    }
    #endif

    //! W-row of given tensor
    template <typename T>
    constexpr Vector3<T>  w_row(const Tensor43<T>&ten) noexcept
    {
        return ten.w_row();
    }

    template <typename T>
    constexpr Vector4<T>  x_column(const Tensor43<T>&ten)  noexcept
    {
        return ten.x_column();
    }

    //! X-row of given tensor
    template <typename T>
    constexpr Vector3<T>  x_row(const Tensor43<T>&ten) noexcept
    {
        return ten.x_row();
    }

    //! Y-column of given tensor
    template <typename T>
    constexpr Vector4<T>  y_column(const Tensor43<T>&ten)  noexcept
    {
        return ten.y_column();
    }

    //! Y-row of given tensor
    template <typename T>
    constexpr Vector3<T>  y_row(const Tensor43<T>&ten) noexcept
    {
        return ten.y_row();
    }

    //! Z-column of given tensor
    template <typename T>
    constexpr Vector4<T>  z_column(const Tensor43<T>&ten)  noexcept
    {
        return ten.z_column();
    }


    //! Z-row of given tensor
    template <typename T>
    constexpr Vector3<T>  z_row(const Tensor43<T>&ten) noexcept
    {
        return ten.z_row();
    }



}
