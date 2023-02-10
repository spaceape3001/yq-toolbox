////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the tensor31 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <math/Segment1.hpp>

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
    constexpr Tensor31<T>::Tensor31(const glm::mat<3,1,T,Q>& t) noexcept :
        xx(t.x.x),
        yx(t.x.y),
        zx(t.x.z)
    {
    }

    template <typename T>
    constexpr Tensor31<T>::operator glm::mat<3,1,T,glm::defaultp>() const noexcept 
    {
        return glm::mat<3,1,T,glm::defaultp>(
            xx, yx, zx
        );
    }

    template <typename T>
    constexpr const Tensor31<T>&  Tensor31<T>::operator+() const noexcept
    { 
        return *this; 
    }

    template <typename T>
    constexpr Tensor31<T>  Tensor31<T>::operator-() const noexcept
    {
        return Tensor31(
            -xx,
            -yx,
            -zx
        );
    }

    template <typename T>
    constexpr Tensor31<T>   Tensor31<T>::operator+ (const Tensor31<T> &b) const noexcept
    {
        return Tensor31(
            xx+b.xx,
            yx+b.yx,
            zx+b.zx
        );
    }

    template <typename T>
    Tensor31<T>&   Tensor31<T>::operator+=(const Tensor31<T> &b) noexcept
    {
        xx+=b.xx;
        yx+=b.yx;
        zx+=b.zx;
        return *this;
    }

    template <typename T>
    constexpr Tensor31<T>   Tensor31<T>::operator- (const Tensor31<T> &b) const noexcept
    {
        return Tensor31(
            xx-b.xx,
            yx-b.yx,
            zx-b.zx
        );
    }
    

    template <typename T>
    Tensor31<T>&   Tensor31<T>::operator-=(const Tensor31<T> &b) noexcept
    {
        xx-=b.xx;
        yx-=b.yx;
        zx-=b.zx;
        return *this;
    }

    template <typename T>
        template <typename U>
    requires trait::is_arithmetic_v<U>
    constexpr Tensor31<trait::product_t<T,U>>  Tensor31<T>::operator*(U b) const noexcept
    {
        return Tensor31<trait::product_t<T,U>>(
            xx*b,
            yx*b,
            zx*b
        );
    }
    
    template <typename T>
        template <typename U>
    requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Tensor31<T>&  Tensor31<T>::operator*=(U b) noexcept
    {
        xx*=b;
        yx*=b;
        zx*=b;        
        return *this;
    }

    template <typename T>
        template <typename U>
    constexpr Segment3<trait::product_t<T,U>>  Tensor31<T>::operator*(const Segment1<U>&rhs) const noexcept
    {
        return Segment3<trait::product_t<T,U>>( *this * rhs.a, *this * rhs.b );
    }

    template <typename T>
        template <typename U>
    constexpr Tensor31<trait::product_t<T,U>> Tensor31<T>::operator*(const Tensor11<U>& b) const noexcept
    {
        return Tensor31<trait::product_t<T,U>>(
            xx*b.xx,

            yx*b.xx,

            zx*b.xx
        );
    }
    
    template <typename T>
        template <typename U>
    requires trait::self_mul_v<T,U>
    Tensor31<T>& Tensor31<T>::operator*=(const Tensor11<U>& b) noexcept
    {
        *this = *this * b;
        return *this;
    }

    template <typename T>
        template <typename U>
    constexpr Tensor32<trait::product_t<T,U>> Tensor31<T>::operator*(const Tensor12<U>& b) const noexcept
    {
        return Tensor32<trait::product_t<T,U>>(
            xx*b.xx,
            xx*b.xy,

            yx*b.xx,
            yx*b.xy,

            zx*b.xx,
            zx*b.xy
        );
    }
    
    template <typename T>
        template <typename U>
    constexpr Tensor33<trait::product_t<T,U>> Tensor31<T>::operator*(const Tensor13<U>& b) const noexcept
    {
        return Tensor33<trait::product_t<T,U>>(
            xx*b.xx,
            xx*b.xy,
            xx*b.xz,

            yx*b.xx,
            yx*b.xy,
            yx*b.xz,

            zx*b.xx,
            zx*b.xy,
            zx*b.xz
        );
    }
    
    template <typename T>
        template <typename U>
    constexpr Tensor34<trait::product_t<T,U>> Tensor31<T>::operator*(const Tensor14<U>& b) const noexcept
    {
        return Tensor34<trait::product_t<T,U>>(
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
            zx*b.xw
        );
    }
            
    template <typename T>
        template <typename U>
    constexpr Vector3<trait::product_t<T,U>> Tensor31<T>::operator*(const Vector1<U>&b) const noexcept
    {
        return Vector3<trait::product_t<T,U>>(
            xx*b.x,
            yx*b.x,
            zx*b.x
        );
    }

    template <typename T>
        template <typename U>
    std::vector<Vector3<trait::product_t<T,U>>>    Tensor31<T>::operator*(std::span<const Vector1<U>> bs) const
    {
        std::vector<Vector3<trait::product_t<T,U>>>    ret;
        ret.reserve(bs.size());
        for(const Vector1<U>& v : bs)
            ret.push_back(*this * v);
        return ret;
    }

    template <typename T>
        template <typename U>
    requires trait::is_arithmetic_v<U>
    constexpr Tensor31<trait::quotient_t<T,U>>  Tensor31<T>::operator/(U b) const noexcept
    {
        return Tensor31<trait::quotient_t<T,U>>(
            xx/b,
            yx/b,
            zx/b
        );
    }
    
    template <typename T>
        template <typename U>
    requires (trait::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Tensor31<T>&  Tensor31<T>::operator/=(U b) noexcept
    {
        xx/=b;
        yx/=b;
        zx/=b;        
        return *this;
    }
    
    template <typename T>
    constexpr Tensor13<T> Tensor31<T>::transpose() const noexcept
    {
        return Tensor13<T>(
            xx, yx,zx
        );
    }

    template <typename T>
    constexpr Vector3<T>  Tensor31<T>::x_column() const noexcept
    {
        return Vector3<T>(xx, yx, zx);
    }

    template <typename T>
    Tensor31<T>& Tensor31<T>::x_column(const Vector3<T>& v)
    {
        xx = v.x;
        yx = v.y;
        zx = v.z;
        return *this;
    }

    template <typename T>
    Tensor31<T>& Tensor31<T>::x_column(T _xx, T _yx, T _zx)
    {
        xx = _xx;
        yx = _yx;
        zx = _zx;
        return *this;
    }

    template <typename T>
    constexpr Vector1<T>  Tensor31<T>::x_row() const noexcept
    {
        return Vector1<T>(xx);
    }


    template <typename T>
    Tensor31<T>& Tensor31<T>::x_row(const Vector1<T>& v)
    {
        xx = v.x;
        return *this;
    }

    template <typename T>
    Tensor31<T>& Tensor31<T>::x_row(T _xx)
    {
        xx = _xx;
        return *this;
    }

    template <typename T>
    constexpr Vector1<T>  Tensor31<T>::y_row() const noexcept
    {
        return Vector1<T>(yx);
    }

    template <typename T>
    Tensor31<T>& Tensor31<T>::y_row(const Vector1<T>& v)
    {
        yx = v.x;
        return *this;
    }

    template <typename T>
    Tensor31<T>& Tensor31<T>::y_row(T _yx)
    {
        yx = _yx;
        return *this;
    }

    template <typename T>
    constexpr Vector1<T>  Tensor31<T>::z_row() const noexcept
    {
        return Vector1<T>(zx);
    }

    template <typename T>
    Tensor31<T>& Tensor31<T>::z_row(const Vector1<T>& v)
    {
        zx = v.x;
        return *this;
    }    

    template <typename T>
    Tensor31<T>& Tensor31<T>::z_row(T _zx)
    {
        zx = _zx;
        return *this;
    }    
            
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename T, typename U>
    requires trait::is_arithmetic_v<T>
    constexpr Tensor31<trait::product_t<T,U>>  operator*(T a, const Tensor31<U>& b)
    {
        return Tensor31<trait::product_t<T,U>>(
            a*b.xx,
            a*b.yx,
            a*b.zx
        );
    }

    template <typename T>
    constexpr Tensor13<T>  transpose(const Tensor31<T>&v)
    {
        return v.transpose();
    }

    //! X-column of given tensor
    template <typename T>
    constexpr Vector3<T>  x_column(const Tensor31<T>&ten) 
    {
        return ten.x_column();
    }

    //! X-row of given tensor
    template <typename T>
    constexpr Vector1<T>  x_row(const Tensor31<T>&ten)
    {
        return ten.x_row();
    }

    //! Y-row of given tensor
    template <typename T>
    constexpr Vector1<T>  y_row(const Tensor31<T>&ten)
    {
        return ten.y_row();
    }

    //! Z-row of given tensor
    template <typename T>
    constexpr Vector1<T>  z_row(const Tensor31<T>&ten)
    {
        return ten.z_row();
    }

}
