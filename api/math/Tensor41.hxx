////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the tensor41 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include "Tensor11.hpp"
#include "Tensor12.hpp"
#include "Tensor13.hpp"
#include "Tensor14.hpp"

#include "Tensor41.hpp"
#include "Tensor42.hpp"
#include "Tensor43.hpp"
#include "Tensor44.hpp"

#include "Vector1.hpp"
#include "Vector4.hpp"

namespace yq {
    template <typename T>
        template <glm::qualifier Q>
    constexpr Tensor41<T>::Tensor41(const glm::mat<4,1,T,Q>& t) noexcept :
        xx(t.x.x),
        yx(t.x.y),
        zx(t.x.z),
        wx(t.x.w)
    {
    }

    template <typename T>
    constexpr Tensor41<T>::operator glm::mat<4,1,T,glm::defaultp>() const noexcept 
    {
        return glm::mat<4,1,T,glm::defaultp>(
            xx, yx, zx, wx
        );
    }

    template <typename T>
    constexpr Tensor41<T>  Tensor41<T>::operator+() const noexcept
    { 
        return *this; 
    }


    template <typename T>
    constexpr Tensor41<T>  Tensor41<T>::operator-() const noexcept
    {
        return Tensor41<T>(
            -xx,
            -yx,
            -zx,
            -wx
        );
    }


    template <typename T>
    constexpr Tensor41<T>   Tensor41<T>::operator+ (const Tensor41<T> &b) const noexcept
    {
        return Tensor41<T>(
            xx+b.xx,
            yx+b.yx,
            zx+b.zx,
            wx+b.wx
        );
    }

    template <typename T>
    Tensor41<T>&   Tensor41<T>::operator+=(const Tensor41<T> &b)  noexcept
    {
        xx+=b.xx;
        yx+=b.yx;
        zx+=b.zx;
        wx+=b.wx;
        return *this;
    }

    template <typename T>
    constexpr Tensor41<T>   Tensor41<T>::operator- (const Tensor41<T> &b)  const noexcept
    {
        return Tensor41<T>(
            xx-b.xx,
            yx-b.yx,
            zx-b.zx,
            wx-b.wx
        );
    }
    

    template <typename T>
    Tensor41<T>&   Tensor41<T>::operator-=(const Tensor41<T> &b) noexcept
    {
        xx-=b.xx;
        yx-=b.yx;
        zx-=b.zx;
        wx-=b.wx;
        return *this;
    }

    template <typename T>
        template <typename U>
    requires trait::is_arithmetic_v<U>
    constexpr Tensor41<product_t<T,U>>  Tensor41<T>::operator*(U b) const noexcept
    {
        return Tensor41<product_t<T,U>>(
            xx*b,
            yx*b,
            zx*b,
            wx*b
        );
    }
    
    template <typename T>
        template <typename U>
    requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Tensor41<T>&  Tensor41<T>::operator*=(U b) noexcept
    {
        xx*=b;
        yx*=b;
        zx*=b;
        wx*=b;        
        return *this;
    }


    template <typename T>
        template <typename U>
    constexpr Tensor41<product_t<T,U>> Tensor41<T>::operator*(const Tensor11<U>& b) const noexcept
    {
        return Tensor41<product_t<T,U>>(
            xx*b.xx,

            yx*b.xx,

            zx*b.xx,

            wx*b.xx
        );
    }
    
    template <typename T>
        template <typename U>
    requires trait::self_mul_v<T,U>
    Tensor41<T>& Tensor41<T>::operator*=(const Tensor11<U>& b) noexcept
    {
        *this = *this * b;
        return *this;
    }

    template <typename T>
        template <typename U>
    constexpr Tensor42<product_t<T,U>> Tensor41<T>::operator*(const Tensor12<U>& b) const noexcept
    {
        return Tensor42<product_t<T,U>>(
            xx*b.xx,
            xx*b.xy,

            yx*b.xx,
            yx*b.xy,

            zx*b.xx,
            zx*b.xy,

            wx*b.xx,
            wx*b.xy
        );
    }
    
    template <typename T>
        template <typename U>
    constexpr Tensor43<product_t<T,U>> Tensor41<T>::operator*(const Tensor13<U>& b) const noexcept
    {
        return Tensor43<product_t<T,U>>(
            xx*b.xx,
            xx*b.xy,
            xx*b.xz,

            yx*b.xx,
            yx*b.xy,
            yx*b.xz,

            zx*b.xx,
            zx*b.xy,
            zx*b.xz,

            wx*b.xx,
            wx*b.xy,
            wx*b.xz
        );
    }
    
    template <typename T>
        template <typename U>
    constexpr Tensor44<product_t<T,U>> Tensor41<T>::operator*(const Tensor14<U>& b) const noexcept
    {
        return Tensor44<product_t<T,U>>(
            xx*b.xx,
            xx*b.xy,
            xx*b.xz,
            xx*b.xw,

            yx*b.xx,
            yx*b.xy,
            yx*b.xz,
            yx*b.xw,

            zx*b.xx,
            zx*b.xy,
            zx*b.xz,
            zx*b.xw,

            wx*b.xx,
            wx*b.xy,
            wx*b.xz,
            wx*b.xw
        );
    }
            
    template <typename T>
        template <typename U>
    constexpr Vector4<product_t<T,U>> Tensor41<T>::operator*(const Vector1<U>&b) const noexcept
    {
        return Vector4<product_t<T,U>>(
            xx*b.x,
            yx*b.x,
            zx*b.x,
            wx*b.x
        );
    }
    
    template <typename T>
        template <typename U>
    requires trait::is_arithmetic_v<U>
    constexpr Tensor41<quotient_t<T,U>>  Tensor41<T>::operator/(U b) const noexcept
    {
        return Tensor41<quotient_t<T,U>>(
            xx/b,
            yx/b,
            zx/b,
            wx/b
        );
    }
    
    template <typename T>
        template <typename U>
    requires (trait::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Tensor41<T>&  Tensor41<T>::operator/=(U b) noexcept
    {
        xx/=b;
        yx/=b;
        zx/=b;
        wx/=b;        
        return *this;
    }


    template <typename T>
    constexpr Tensor14<T> Tensor41<T>::transpose() const noexcept
    {
        return Tensor14<T>(
            xx, yx, zx, wx
        );
    }
    

    template <typename T>
    constexpr Vector1<T>  Tensor41<T>::w_row() const noexcept
    {
        return Vector1<T>(wx);
    }

    template <typename T>
    Tensor41<T>& Tensor41<T>::w_row(T _wx) noexcept
    {
        wx = _wx;
        return *this;
    }

    template <typename T>
    Tensor41<T>& Tensor41<T>::w_row(const Vector1<T>& v) noexcept
    {
        wx = v.x;
        return *this;
    }

    template <typename T>
    constexpr Vector4<T>  Tensor41<T>::x_column() const noexcept
    {
        return Vector4<T>(xx, yx, zx, wx);
    }

    template <typename T>
    Tensor41<T>& Tensor41<T>::x_column(const Vector4<T>& v) noexcept
    {
        xx = v.x;
        yx = v.y;
        zx = v.z;
        wx = v.w;
        return *this;
    }

    template <typename T>
    Tensor41<T>& Tensor41<T>::x_column(T _xx, T _yx, T _zx, T _wx) noexcept
    {
        xx = _xx;
        yx = _yx;
        zx = _zx;
        wx = _wx;
        return *this;
    }

    template <typename T>
    constexpr Vector1<T>  Tensor41<T>::x_row() const noexcept
    {
        return Vector4<T>(xx);
    }

    template <typename T>
    Tensor41<T>& Tensor41<T>::x_row(const Vector1<T>& v) noexcept
    {
        xx = v.x;
        return *this;
    }

    template <typename T>
    Tensor41<T>& Tensor41<T>::x_row(T _xx) noexcept
    {
        xx = _xx;
        return *this;
    }

    template <typename T>
    constexpr Vector1<T>  Tensor41<T>::y_row() const noexcept
    {
        return Vector4<T>(yx);
    }

    template <typename T>
    Tensor41<T>& Tensor41<T>::y_row(const Vector1<T>& v) noexcept
    {
        yx = v.x;
        return *this;
    }

    template <typename T>
    Tensor41<T>& Tensor41<T>::y_row(T _yx) noexcept
    {
        yx = _yx;
        return *this;
    }

    template <typename T>
    constexpr Vector1<T>  Tensor41<T>::z_row() const noexcept
    {
        return Vector4<T>(zx);
    }

    template <typename T>
    Tensor41<T>& Tensor41<T>::z_row(const Vector1<T>& v) noexcept
    {
        zx = v.x;
        return *this;
    }

    template <typename T>
    Tensor41<T>& Tensor41<T>::z_row(T _zx) noexcept
    {
        zx = _zx;
        return *this;
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            
    template <typename T, typename U>
    requires trait::is_arithmetic_v<T>
    constexpr Tensor41<product_t<T,U>>  operator*(T a, const Tensor41<T>& b) noexcept
    {
        return {
            a*b.xx,
            a*b.yx,
            a*b.zx,
            a*b.wx
        };
    }

    template <typename T>
    constexpr Tensor14<T>  transpose(const Tensor41<T>&v)
    {
        return v.transpose();
    }

}
