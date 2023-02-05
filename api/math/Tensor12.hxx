////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the tensor12 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <math/Segment2.hpp>

#include <math/Tensor11.hpp>
#include <math/Tensor12.hpp>
#include <math/Tensor13.hpp>
#include <math/Tensor14.hpp>

#include <math/Tensor21.hpp>
#include <math/Tensor22.hpp>
#include <math/Tensor23.hpp>
#include <math/Tensor24.hpp>

#include <math/Vector1.hpp>
#include <math/Vector2.hpp>

namespace yq {
    template <typename T>
        template <glm::qualifier Q>
    constexpr Tensor12<T>::Tensor12(const glm::mat<1,2,T,Q>& t) noexcept :
        xx(t.x.x), xy(t.y.x)
    {
    }

    template <typename T>
    constexpr Tensor12<T>::operator glm::mat<1,2,T,glm::defaultp>() const noexcept 
    {
        return glm::mat<1,2,T,glm::defaultp>(
            xx,
            xy
        );
    }

    template <typename T>
    constexpr Tensor12<T>  Tensor12<T>::operator+() const noexcept
    { 
        return *this; 
    }

    template <typename T>
    constexpr Tensor12<T>  Tensor12<T>::operator-() const noexcept
    {
        return Tensor12(
            -xx, -xy
        );
    }

    template <typename T>
    constexpr Tensor12<T>   Tensor12<T>::operator+ (const Tensor12<T> &b) const noexcept
    {
        return Tensor12<T>(
            xx+b.xx, xy+b.xy
        );
    }

    template <typename T>
    Tensor12<T>&   Tensor12<T>::operator+=(const Tensor12<T> &b) noexcept
    {
        xx+=b.xx;  xy+=b.xy;
        return *this;
    }

    template <typename T>
    constexpr Tensor12<T>   Tensor12<T>::operator- (const Tensor12<T> &b) const noexcept
    {
        return Tensor12<T>(
            xx-b.xx, xy-b.xy
        );
    }
    

    template <typename T>
    Tensor12<T>&   Tensor12<T>::operator-=(const Tensor12<T> &b) noexcept
    {
        xx-=b.xx;  xy-=b.xy;
        return *this;
    }

    template <typename T>
        template <typename U>
    requires trait::is_arithmetic_v<U>
    constexpr Tensor12<trait::product_t<T,U>>  Tensor12<T>::operator*(U b) const noexcept
    {
        return Tensor12<trait::product_t<T,U>>(
            xx*b, xy*b
        );
    }
    
    template <typename T>
        template <typename U>
    requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Tensor12<trait::product_t<T,U>>  Tensor12<T>::operator*=(U b) noexcept
    {
        xx*=b; xy*=b;        
        return *this;
    }

    template <typename T>
        template <typename U>
    constexpr Segment1<trait::product_t<T,U>>  Tensor12<T>::operator*(const Segment2<U>&rhs) const noexcept
    {
        return Segment1<trait::product_t<T,U>>( *this * rhs.a, *this * rhs.b );
    }

    template <typename T>
        template <typename U>
    constexpr Tensor11<trait::product_t<T,U>> Tensor12<T>::operator*(const Tensor21<U>& b) const noexcept
    {
        return Tensor11<trait::product_t<T,U>>(
            xx*b.xx + xy*b.yx
        );
    }
    
    template <typename T>
        template <typename U>
    constexpr Tensor12<trait::product_t<T,U>> Tensor12<T>::operator*(const Tensor22<U>& b) const noexcept
    {
        return Tensor12<trait::product_t<T,U>>(
            xx*b.xx + xy*b.yx,
            xx*b.xy + xy*b.yy
        );
    }
    
    template <typename T>
        template <typename U>
    requires trait::self_mul_v<T,U>
    Tensor12<T>& Tensor12<T>::operator*=(const Tensor22<U>& b) noexcept
    {
        *this = *this * b;
        return *this;
    }

    template <typename T>
        template <typename U>
    constexpr Tensor13<trait::product_t<T,U>> Tensor12<T>::operator*(const Tensor23<U>& b) const noexcept
    {
        return Tensor13<trait::product_t<T,U>>(
            xx*b.xx + xy*b.yx,
            xx*b.xy + xy*b.yy,
            xx*b.xz + xy*b.yz
        );
    }
    
    template <typename T>
        template <typename U>
    constexpr Tensor14<trait::product_t<T,U>> Tensor12<T>::operator*(const Tensor24<U>& b) const noexcept
    {
        return Tensor14<trait::product_t<T,U>>(
            xx*b.xx + xy*b.yx,
            xx*b.xy + xy*b.yy,
            xx*b.xz + xy*b.yz,
            xx*b.xw + xy*b.yw
        );
    }

    template <typename T>
        template <typename U>
    constexpr Vector1<trait::product_t<T,U>> Tensor12<T>::operator*(const Vector2<U>&b) const noexcept
    {
        return Vector1<trait::product_t<T,U>>(
            xx*b.x + xy*b.y
        );
    }

    template <typename T>
        template <typename U>
    requires trait::is_arithmetic_v<U>
    constexpr Tensor12<trait::quotient_t<T,U>>  Tensor12<T>::operator/(U b) const noexcept
    {
        return Tensor12<trait::quotient_t<T,U>> (
            xx/b, xy/b
        );
    }
    
    template <typename T>
        template <typename U>
    requires (trait::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Tensor12<trait::quotient_t<T,U>>  Tensor12<T>::operator/=(U b) noexcept
    {
        xx/=b; xy/=b;        
        return *this;
    }


    template <typename T>
    constexpr Tensor21<T> Tensor12<T>::transpose() const noexcept
    {
        return Tensor21<T>(
            xx,
            xy
        );
    }

    template <typename T>
    constexpr Vector1<T>  Tensor12<T>::x_column() const noexcept
    {
        return Vector1<T>(xx);
    }

    template <typename T>
    Tensor12<T>& Tensor12<T>::x_column(const Vector1<T>& v)
    {
        xx = v.x;
        return *this;
    }

    template <typename T>
    Tensor12<T>& Tensor12<T>::x_column(T _xx)
    {
        xx = _xx;
        return *this;
    }

    template <typename T>
    constexpr Vector2<T>  Tensor12<T>::x_row() const noexcept
    {
        return Vector2<T>(xx, xy);
    }

    template <typename T>
    Tensor12<T>& Tensor12<T>::x_row(const Vector2<T>& v)
    {
        xx = v.x;
        xy = v.y;
        return *this;
    }

    template <typename T>
    Tensor12<T>& Tensor12<T>::x_row(T _xx, T _xy)
    {
        xx = _xx;
        xy = _xy;
        return *this;
    }

    template <typename T>
    constexpr Vector1<T>  Tensor12<T>::y_column() const noexcept
    {
        return Vector1<T>(xy);
    }

    template <typename T>
    Tensor12<T>& Tensor12<T>::y_column(const Vector1<T>& v)
    {
        xy = v.x;
        return *this;
    }

    template <typename T>
    Tensor12<T>& Tensor12<T>::y_column(T _xy)
    {
        xy = _xy;
        return *this;
    }


    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename T, typename U>
    requires std::is_arithmetic_v<T>
    constexpr Tensor12<trait::product_t<T,U>>  operator*(T a, const Tensor12<U>& b)
    {
        return Tensor12<trait::product_t<T,U>>(
            a*b.xx, a*b.xy
        );
    }

    template <typename T>
    constexpr Tensor21<T>  transpose(const Tensor12<T>&v) noexcept
    {
        return v.transpose();
    }

    template <typename T>
    constexpr Vector1<T>  x_column(const Tensor12<T>&ten) noexcept
    {
        return ten.x_column();
    }

    template <typename T>
    constexpr Vector2<T>  x_row(const Tensor12<T>&ten) noexcept
    {   
        return ten.x_row();
    }

    template <typename T>
    constexpr Vector1<T>  y_column(const Tensor12<T>&ten) noexcept 
    {
        return ten.y_column();
    }

}
