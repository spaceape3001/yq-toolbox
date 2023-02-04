////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once


/* 
    This is the template IMPLEMENTATION of the tensor22 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <math/Segment2.hpp>

#include <math/Tensor21.hpp>
#include <math/Tensor22.hpp>
#include <math/Tensor23.hpp>
#include <math/Tensor24.hpp>

#include <math/Vector2.hpp>

#include <math/trig.hpp>

namespace yq {
    template <typename T>
    template <typename>
    requires std::is_floating_point_v<T>
    Tensor22<T>::Tensor22(ccw_t, MKS<T,dim::Angle> v)
    {
        auto c  = cos(v);
        auto s  = sin(v);
        xx = yy = c;
        xy  = -s;
        yx  = s;
    }

    template <typename T>
    template <typename>
    requires std::is_floating_point_v<T>
    Tensor22<T>::Tensor22(clockwise_t, MKS<T,dim::Angle>v) : Tensor22(CCW, -v) {}

    template <typename T>
        template <glm::qualifier Q>
    constexpr Tensor22<T>::Tensor22(const glm::mat<2,2,T,Q>& t) noexcept :
        xx(t.x.x), xy(t.y.x),
        yx(t.x.y), yy(t.y.y)
    {
    }

    template <typename T>
    Tensor22<T>::operator glm::mat<2,2,T,glm::defaultp>() const noexcept 
    {
        return glm::mat<2,2,T,glm::defaultp>(
            xx, yx,
            xy, yy
        );
    }


    template <typename T>
    constexpr Tensor22<T>  Tensor22<T>::operator+() const noexcept
    { 
        return *this; 
    }


    template <typename T>
    constexpr Tensor22<T>  Tensor22<T>::operator-() const noexcept
    {
        return Tensor22(
            -xx, -xy,
            -yx, -yy
        );
    }
    
    template <typename T>
    constexpr Tensor22<T>  Tensor22<T>::operator+ (const Tensor22<T> &b) const noexcept
    {
        return {
            xx+b.xx, xy+b.xy,
            yx+b.yx, yy+b.yy
        };
    }

    template <typename T>
    Tensor22<T>&   Tensor22<T>::operator+=(const Tensor22<T> &b) 
    {
        xx+=b.xx;  xy+=b.xy;
        yx+=b.yx;  yy+=b.yy;
        return *this;
    }

    
    template <typename T>
    constexpr Tensor22<T>   Tensor22<T>::operator- (const Tensor22<T> &b)  const noexcept
    {
        return Tensor22(
            xx-b.xx, xy-b.xy,
            yx-b.yx, yy-b.yy
        );
    }
    

    template <typename T>
    Tensor22<T>&   Tensor22<T>::operator-=(const Tensor22<T> &b) 
    {
        xx-=b.xx;  xy-=b.xy;
        yx-=b.yx;  yy-=b.yy;
        return *this;
    }

    template <typename T>
        template <typename U>
    requires trait::is_arithmetic_v<U>
    constexpr Tensor22<product_t<T,U>>  Tensor22<T>::operator*(U b) const noexcept
    {
        return Tensor22<product_t<T,U>>(
            xx*b, xy*b,
            yx*b, yy*b
        );
    }
    
    template <typename T>
        template <typename U>
    requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Tensor22<T>&  Tensor22<T>::operator*=(U b) noexcept
    {
        xx*=b; xy*=b;
        yx*=b; yy*=b;        
        return *this;
    }

    template <typename T>
        template <typename U>
    constexpr Segment2<product_t<T,U>>  Tensor22<T>::operator*(const Segment2<U>&rhs) const noexcept
    {
        return Segment2<product_t<T,U>>( *this * rhs.a, *this * rhs.b );
    }

    template <typename T>
        template <typename U>
    constexpr Tensor21<product_t<T,U>> Tensor22<T>::operator*(const Tensor21<U>& b) const noexcept
    {
        return {
            xx*b.xx + xy*b.yx,

            yx*b.xx + yy*b.yx
        };
    }

    template <typename T>
        template <typename U>
    constexpr Tensor22<product_t<T,U>> Tensor22<T>::operator*(const Tensor22<U>& b) const noexcept
    {
        return Tensor22<product_t<T,U>>(
            xx*b.xx + xy*b.yx,
            xx*b.xy + xy*b.yy,

            yx*b.xx + yy*b.yx,
            yx*b.xy + yy*b.yy
        );
    }
    
    template <typename T>
        template <typename U>
    requires trait::self_mul_v<T,U>
    Tensor22<T>& Tensor22<T>::operator*=(const Tensor22<U>& b) noexcept
    {
        *this = *this * b;
        return *this;
    }
   
    template <typename T>
        template <typename U>
    constexpr Tensor23<product_t<T,U>> Tensor22<T>::operator*(const Tensor23<U>& b) const noexcept
    {
        return Tensor23<product_t<T,U>>(
            xx*b.xx + xy*b.yx,
            xx*b.xy + xy*b.yy,
            xx*b.xz + xy*b.yz,

            yx*b.xx + yy*b.yx,
            yx*b.xy + yy*b.yy,
            yx*b.xz + yy*b.yz
        );
    }
    
    template <typename T>
        template <typename U>
    constexpr Tensor24<product_t<T,U>> Tensor22<T>::operator*(const Tensor24<U>& b) const noexcept
    {
        return Tensor24<product_t<T,U>>(
            xx*b.xx + xy*b.yx,
            xx*b.xy + xy*b.yy,
            xx*b.xz + xy*b.yz,
            xx*b.xw + xy*b.yw,

            yx*b.xx + yy*b.yx,
            yx*b.xy + yy*b.yy,
            yx*b.xz + yy*b.yz,
            yx*b.xw + yy*b.yw
        );
    }
        
    template <typename T>
        template <typename U>
    constexpr Vector2<product_t<T,U>> Tensor22<T>::operator*(const Vector2<U>&b) const noexcept
    {
        return Vector2<product_t<T,U>>(
            xx*b.x + xy*b.y,
            yx*b.x + yy*b.y
        );
    }

    template <typename T>
        template <typename U>
    requires trait::is_arithmetic_v<U>
    constexpr Tensor22<quotient_t<T,U>>  Tensor22<T>::operator/(U b) const noexcept
    {
        return Tensor22<quotient_t<T,U>>(
            xx/b, xy/b,
            yx/b, yy/b
        );
    }
    
    template <typename T>
        template <typename U>
    requires (trait::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Tensor22<T>&  Tensor22<T>::operator/=(U b) noexcept
    {
        xx/=b; xy/=b;
        yx/=b; yy/=b;        
        return *this;
    }


    template <typename T>
    constexpr square_t<T> Tensor22<T>::determinant() const noexcept
    {
        return xx*yy-xy*yx;
    }


    template <typename T>
    constexpr Vector2<T>  Tensor22<T>::diagonal() const noexcept
    {
        return Vector2<T>(xx, yy);
    }

    template <typename T>
    Tensor22<T>&  Tensor22<T>::diagonal(const Vector2<T>& v)
    {        
        xx = v.x;
        yy = v.y;
        return *this;    
    }

    template <typename T>
    Tensor22<T>&  Tensor22<T>::diagonal(T _xx, T _yy)
    {        
        xx = _xx;
        yy = _yy;
        return *this;
    }
    
    //void        eigenvalues(zreal&,zreal&,zreal&,zreal&b) const;
    //void        eigensystem(zreal&,zvector4&,zreal&,zvector4&,zreal&,zvector4&,zreal&,zvector4&b) const;

    template <typename T>
    constexpr Tensor22<inverse_t<T>> Tensor22<T>::inverse() const noexcept
    {
        auto    di = one_v<T> / determinant();
        return Tensor22<inverse_t<T>>(
             di * yy, -di * xy,
            -di * yx,  di * xx
        );
    }

    template <typename T>
    constexpr T     Tensor22<T>::trace() const noexcept
    {
        return xx+yy;
    }

    template <typename T>
    constexpr Tensor22<T>  Tensor22<T>::transpose() const noexcept
    {
        return Tensor22(
            xx, yx,
            xy, yy
        );
    }
    
    template <typename T>
    constexpr Vector2<T>  Tensor22<T>::x_column() const noexcept
    {
        return Vector2<T>(xx, yx);
    }

    template <typename T>
    Tensor22<T>& Tensor22<T>::x_column(const Vector2<T>& v)
    {
        xx = v.x;
        yx = v.y;
        return *this;
    }

    template <typename T>
    Tensor22<T>& Tensor22<T>::x_column(T _xx, T _yx)
    {
        xx = _xx;
        yx = _yx;
        return *this;
    }
    
    template <typename T>
    constexpr Vector2<T>  Tensor22<T>::x_row() const noexcept
    {
        return Vector2<T>(xx, xy);
    }

    template <typename T>
    Tensor22<T>& Tensor22<T>::x_row(const Vector2<T>& v)
    {
        xx = v.x;
        xy = v.y;
        return *this;
    }

    template <typename T>
    Tensor22<T>& Tensor22<T>::x_row(T _xx, T _xy)
    {
        xx = _xx;
        xy = _xy;
        return *this;
    }

    template <typename T>
    constexpr Vector2<T>  Tensor22<T>::y_column() const noexcept
    {
        return Vector2<T>(xy, yy);
    }

    template <typename T>
    Tensor22<T>& Tensor22<T>::y_column(const Vector2<T>& v)
    {
        xy = v.x;
        yy = v.y;
        return *this;
    }

    template <typename T>
    Tensor22<T>& Tensor22<T>::y_column(T _xy, T _yy)
    {
        xy = _xy;
        yy = _yy;
        return *this;
    }

    template <typename T>
    constexpr Vector2<T>  Tensor22<T>::y_row() const noexcept
    {
        return Vector2<T>(yx, yy);
    }

    template <typename T>
    Tensor22<T>& Tensor22<T>::y_row(const Vector2<T>& v)
    {
        yx = v.x;
        yy = v.y;
        return *this;
    }

    template <typename T>
    Tensor22<T>& Tensor22<T>::y_row(T _yx, T _yy)
    {
        yx = _yx;
        yy = _yy;
        return *this;
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename T, typename U>
    requires trait::is_arithmetic_v<T>
    constexpr Tensor22<product_t<T,U>>  operator*(T a, const Tensor22<T>& b)
    {
        return Tensor22<product_t<T,U>>(
            a*b.xx, a*b.xy,
            a*b.yx, a*b.yy
        );
    }

    template <typename T>
    square_t<T> determinant(const Tensor22<T>& ten)
    {
        return ten.determinant();
    }

    template <typename T>
    constexpr Vector2<T>  diagonal(const Tensor22<T>& ten)
    {
        return ten.diagonal();
    }

    template <typename T>
    Tensor22<inverse_t<T>> inverse(const Tensor22<T>&ten)
    {
        return ten.inverse();
    }

    template <typename T>
    constexpr Tensor22<T>   rotation2(MKS<T,dim::Angle> r)
    {
        return Tensor22<T>(CCW, r);
    }

    template <typename T, glm::qualifier Q>
    constexpr Tensor22<T> tensor(const glm::mat<2,2,T,Q>& t)
    {
        return Tensor22<T>(t);
    }

    template <typename T>
    constexpr T     trace(const Tensor22<T>& ten)
    {
        return ten.trace();
    }

    template <typename T>
    constexpr Tensor22<T>  transpose(const Tensor22<T>& ten)
    {
        return ten.transpose();
    }

    template <typename T>
    constexpr Vector2<T>  x_column(const Tensor22<T>&ten) 
    {
        return ten.x_column();
    }

    template <typename T>
    constexpr Vector2<T>  y_column(const Tensor22<T>&ten) 
    {
        return ten.y_column();
    }

    template <typename T>
    constexpr Vector2<T>  x_row(const Tensor22<T>&ten)
    {
        return ten.x_row();
    }

    template <typename T>
    constexpr Vector2<T>  y_row(const Tensor22<T>&ten)
    {
        return ten.y_row();
    }
}
