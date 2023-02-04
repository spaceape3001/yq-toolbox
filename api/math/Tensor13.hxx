////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the tensor13 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <math/Segment3.hpp>

#include <math/Tensor11.hpp>
#include <math/Tensor12.hpp>
#include <math/Tensor13.hpp>
#include <math/Tensor14.hpp>

#include <math/Tensor31.hpp>
#include <math/Tensor32.hpp>
#include <math/Tensor33.hpp>
#include <math/Tensor34.hpp>

#include <math/Vector1.hpp>
#include <math/Vector3.hpp>

namespace yq {
    template <typename T>
        template <glm::qualifier Q>
    constexpr Tensor13<T>::Tensor13(const glm::mat<1,3,T,Q>& t) noexcept :
        xx(t.x.x), xy(t.y.x), xz(t.z.x)
    {
    }

    template <typename T>
    constexpr Tensor13<T>::operator glm::mat<1,3,T,glm::defaultp>() const noexcept 
    {
        return glm::mat<1,3,T,glm::defaultp>(
            xx,
            xy,
            xz
        );
    }

    template <typename T>
    constexpr Tensor13<T>  Tensor13<T>::operator+() const noexcept
    { 
        return *this; 
    }

    template <typename T>
    constexpr Tensor13<T>  Tensor13<T>::operator-() const noexcept
    {
        return Tensor13(
            -xx, -xy, -xz
        );
    }



    template <typename T>
    constexpr Tensor13<T>   Tensor13<T>::operator+ (const Tensor13<T> &b) const noexcept
    {
        return Tensor13{
            xx+b.xx, xy+b.xy, xz+b.xz
        };
    }

    template <typename T>
    Tensor13<T>&   Tensor13<T>::operator+=(const Tensor13<T> &b) noexcept
    {
        xx+=b.xx;  xy+=b.xy;  xz+=b.xz;
        return *this;
    }



    template <typename T>
    constexpr Tensor13<T>   Tensor13<T>::operator- (const Tensor13<T> &b) const noexcept
    {
        return Tensor13(
            xx-b.xx, xy-b.xy, xz-b.xz
        );
    }
    

    template <typename T>
    Tensor13<T>&   Tensor13<T>::operator-=(const Tensor13<T> &b) noexcept
    {
        xx-=b.xx;  xy-=b.xy;  xz-=b.xz;
        return *this;
    }
    
    template <typename T>
        template <typename U>
    requires trait::is_arithmetic_v<U>
    constexpr Tensor13<product_t<T,U>>  Tensor13<T>::operator*(U b) const noexcept
    {
        return Tensor13<product_t<T,U>>(
            xx*b, xy*b, xz*b
        );
    }
    
    template <typename T>
        template <typename U>
    requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Tensor13<T>&  Tensor13<T>::operator*=(U b) noexcept
    {
        xx*=b; xy*=b; xz*=b;        
        return *this;
    }
    

    template <typename T>
        template <typename U>
    constexpr Tensor11<product_t<T,U>> Tensor13<T>::operator*(const Tensor31<U>& b) const noexcept
    {
        return Tensor11<product_t<T,U>>(
            xx*b.xx + xy*b.yx + xz*b.zx
        );
    }
    
    template <typename T>
        template <typename U>
    constexpr Tensor12<product_t<T,U>> Tensor13<T>::operator*(const Tensor32<U>& b) const noexcept
    {
        return Tensor12<product_t<T,U>>(
            xx*b.xx + xy*b.yx + xz*b.zx,
            xx*b.xy + xy*b.yy + xz*b.zy
        );
    }
    
    template <typename T>
        template <typename U>
    constexpr Tensor13<product_t<T,U>> Tensor13<T>::operator*(const Tensor33<U>& b) const noexcept
    {
        return Tensor13<product_t<T,U>>(
            xx*b.xx + xy*b.yx + xz*b.zx,
            xx*b.xy + xy*b.yy + xz*b.zy,
            xx*b.xz + xy*b.yz + xz*b.zz
        );
    }
    
    template <typename T>
        template <typename U>
    requires trait::self_mul_v<T,U>
    Tensor13<T>& Tensor13<T>::operator*=(const Tensor33<U>& b) noexcept
    {
        *this = *this * b;
        return *this;
    }

    template <typename T>
        template <typename U>
    constexpr Tensor14<product_t<T,U>> Tensor13<T>::operator*(const Tensor34<U>& b) const noexcept
    {
        return Tensor14<product_t<T,U>>(
            xx*b.xx + xy*b.yx + xz*b.zx,
            xx*b.xy + xy*b.yy + xz*b.zy,
            xx*b.xz + xy*b.yz + xz*b.zz,
            xx*b.xw + xy*b.yw + xz*b.zw
        );
    }
        
    template <typename T>
        template <typename U>
    constexpr Vector1<product_t<T,U>> Tensor13<T>::operator*(const Vector3<U>&b) const noexcept
    {
        return Vector1<product_t<T,U>>(
            xx*b.x + xy*b.y + xz*b.z
        );
    }

    template <typename T>
        template <typename U>
    requires trait::is_arithmetic_v<U>
    constexpr Tensor13<quotient_t<T,U>>  Tensor13<T>::operator/(U b) const noexcept
    {
        return Tensor13<quotient_t<T,U>>(
            xx/b, xy/b, xz/b
        );
    }
    
    template <typename T>
        template <typename U>
    requires (trait::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Tensor13<T>&  Tensor13<T>::operator/=(U b) noexcept
    {
        xx/=b; xy/=b; xz/=b;        
        return *this;
    }
    
    template <typename T>
    constexpr Tensor31<T> Tensor13<T>::transpose() const noexcept
    {
        return Tensor31<T>(
            xx,
            xy,
            xz
        );
    }


    template <typename T>
    constexpr Vector1<T>  Tensor13<T>::x_column() const noexcept
    {
        return Vector1<T>(xx);
    }

    template <typename T>
    Tensor13<T>& Tensor13<T>::x_column(const Vector1<T>& v)
    {
        xx = v.x;
        return *this;
    }

    template <typename T>
    Tensor13<T>& Tensor13<T>::x_column(T _xx)
    {
        xx = _xx;
        return *this;
    }

    template <typename T>
    constexpr Vector3<T>  Tensor13<T>::x_row() const noexcept
    {
        return Vector3<T>(xx, xy, xz);
    }

    template <typename T>
    Tensor13<T>& Tensor13<T>::x_row(const Vector3<T>& v)
    {
        xx = v.x;
        xy = v.y;
        xz = v.z;
        return *this;
    }

    template <typename T>
    Tensor13<T>& Tensor13<T>::x_row(T _xx, T _xy, T _xz)
    {
        xx = _xx;
        xy = _xy;
        xz = _xz;
        return *this;
    }
    
    template <typename T>
    constexpr Vector1<T>  Tensor13<T>::y_column() const noexcept
    {
        return Vector1<T>(xy);
    }

    template <typename T>
    Tensor13<T>& Tensor13<T>::y_column(const Vector1<T>& v)
    {
        xy = v.x;
        return *this;
    }

    template <typename T>
    Tensor13<T>& Tensor13<T>::y_column(T _xy)
    {
        xy = _xy;
        return *this;
    }

    template <typename T>
    constexpr Vector1<T>  Tensor13<T>::z_column() const noexcept
    {
        return Vector1<T>(xz);
    }

    template <typename T>
    Tensor13<T>& Tensor13<T>::z_column(const Vector1<T>& v)
    {
        xz = v.x;
        return *this;
    }


    template <typename T>
    Tensor13<T>& Tensor13<T>::z_column(T _xz)
    {
        xz = _xz;
        return *this;
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename T, typename U>
    requires trait::is_arithmetic_v<T>
    constexpr Tensor13<product_t<T,U>>  operator*(T a, const Tensor13<U>& b)
    {
        return {
            a*b.xx, a*b.xy, a*b.xz
        };
    }

    template <typename T>
    constexpr Tensor31<T>  transpose(const Tensor13<T>&v)
    {
        return v.transpose();
    }

    template <typename T>
    constexpr Vector1<T>  x_column(const Tensor13<T>&ten) 
    {
        return ten.x_column();
    }

    template <typename T>
    constexpr Vector1<T>  y_column(const Tensor13<T>&ten) 
    {
        return ten.y_column();
    }

    template <typename T>
    constexpr Vector1<T>  z_column(const Tensor13<T>&ten) 
    {
        return ten.z_column();
    }

    template <typename T>
    constexpr Vector3<T>  x_row(const Tensor13<T>&ten)
    {
        return ten.x_row();
    }

}
