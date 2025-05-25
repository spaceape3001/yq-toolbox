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

#include <yq/tensor/Tensor22.hpp>
#include <yq/math/trigonometry.hpp>
#include <yq/math/utility.hpp>

#include <yq/math/AllComponents.hpp>
#include <yq/math/AnyComponents.hpp>

namespace yq {
    template <typename T>
    template <typename>
    requires std::is_floating_point_v<T>
    Tensor22<T>::Tensor22(ccw_k, MKS<T,dim::Angle> v)
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
    Tensor22<T>::Tensor22(clockwise_k, MKS<T,dim::Angle>v) : Tensor22(CCW, -v) {}

    #ifdef YQ_MATH_SPINOR2_HPP
    template <typename T>
    Tensor22<T>::Tensor22(const Spinor2<T>& q)  : 
        xx(q.a), xy(-q.xy), // Verify the sign, might need to go on yx...
        yx(q.xy), yy(q.a)
    {
    }
    #endif

    #ifdef YQ_USE_GLM
    template <typename T>
        template <glm::qualifier Q>
    constexpr Tensor22<T>::Tensor22(const glm::mat<2,2,T,Q>& t) noexcept :
        xx(t[0][0]), xy(t[1][0]),
        yx(t[0][1]), yy(t[1][1])
    {
    }
    #endif

    #ifdef YQ_USE_GLM
    template <typename T>
    Tensor22<T>::operator glm::mat<2,2,T,glm::defaultp>() const noexcept 
    {
        return glm::mat<2,2,T,glm::defaultp>(
            xx, yx,
            xy, yy
        );
    }
    #endif


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
    requires is_arithmetic_v<U>
    constexpr Tensor22<product_t<T,U>>  Tensor22<T>::operator*(U b) const noexcept
    {
        return Tensor22<product_t<T,U>>(
            xx*b, xy*b,
            yx*b, yy*b
        );
    }
    
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
    Tensor22<T>&  Tensor22<T>::operator*=(U b) noexcept
    {
        xx*=b; xy*=b;
        yx*=b; yy*=b;        
        return *this;
    }

    #ifdef YQ_MATH_POLYGON2_HPP
    template <typename T>
        template <typename U>
    Polygon2<product_t<T,U>>  Tensor22<T>::operator*(const Polygon2<U>&b) const
    {
        return Polygon2<product_t<T,U>>( *this * b.vertex );
    }
    #endif
    
    #ifdef YQ_MATH_POLYLINE2_HPP
    template <typename T>
        template <typename U>
    Polyline2<product_t<T,U>>  Tensor22<T>::operator*(const Polyline2<U>&b) const
    {
        return Polyline2<product_t<T,U>>( *this * b.vertex );
    }
    #endif

    #ifdef YQ_MATH_QUADRILATERAL2_HPP
    template <typename T>
        template <typename U>
    Quadrilateral2<product_t<T,U>> Tensor22<T>::operator*(const Quadrilateral2<U>&rhs) const
    {
        return Quadrilateral2<product_t<T,U>>(*this * rhs.a, *this * rhs.b, *this * rhs.c, *this * rhs.d);
    }
    #endif

    #ifdef YQ_MATH_SEGMENT2_HPP
    template <typename T>
        template <typename U>
    constexpr Segment2<product_t<T,U>>  Tensor22<T>::operator*(const Segment2<U>&rhs) const noexcept
    {
        return Segment2<product_t<T,U>>( *this * rhs.a, *this * rhs.b );
    }
    #endif

    #ifdef YQ_MATH_TENSOR_2_1_HPP
    template <typename T>
        template <typename U>
    constexpr Tensor21<product_t<T,U>> Tensor22<T>::operator*(const Tensor21<U>& b) const noexcept
    {
        return {
            xx*b.xx + xy*b.yx,

            yx*b.xx + yy*b.yx
        };
    }
    #endif

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
    requires self_multiply_v<T,U>
    Tensor22<T>& Tensor22<T>::operator*=(const Tensor22<U>& b) noexcept
    {
        *this = *this * b;
        return *this;
    }
   
    #ifdef YQ_MATH_TENSOR_2_3_HPP
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
    #endif
    
    #ifdef YQ_MATH_TENSOR_2_4_HPP
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
    #endif
    
    #ifdef YQ_MATH_TRIANGLE2_HPP
    template <typename T>
        template <typename U>
    Triangle2<product_t<T,U>> Tensor22<T>::operator*(const Triangle2<U>&rhs) const noexcept
    {
        return Triangle2<product_t<T,U>>( *this * rhs.a, *this * rhs.b, *this * rhs.c );
    }
    #endif
        
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
    std::vector<Vector2<product_t<T,U>>>    Tensor22<T>::operator*(std::span<const Vector2<U>> bs) const
    {
        return transform(bs, [&](const Vector2<U>& b) -> Vector2<product_t<T,U>> {
            return *this * b;
        });
    }

    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    constexpr Tensor22<quotient_t<T,U>>  Tensor22<T>::operator/(U b) const noexcept
    {
        return Tensor22<quotient_t<T,U>>(
            xx/b, xy/b,
            yx/b, yy/b
        );
    }
    
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_divide_v<T,U>)
    Tensor22<T>&  Tensor22<T>::operator/=(U b) noexcept
    {
        xx/=b; xy/=b;
        yx/=b; yy/=b;        
        return *this;
    }


    template <typename T>
    constexpr Tensor22<T> Tensor22<T>::all_add(T b) const noexcept
    {
        return Tensor22( 
            xx+b, xy+b,
            yx+b, yy+b
         );
    }

    template <typename T>
    Tensor22<T>&    Tensor22<T>::all_decrement(T b) noexcept
    {
        xx-=b; xy-=b;
        yx-=b; yy-=b;
        return *this;
    }

    template <typename T>
    Tensor22<T>&    Tensor22<T>::all_increment(T b) noexcept
    {
        xx+=b; xy+=b;
        yx+=b; yy+=b;
        return *this;
    }
    
    template <typename T>
    constexpr Tensor22<T> Tensor22<T>::all_subtract(T b) const noexcept
    {
        return Tensor22( 
            xx-b, xy-b,
            yx-b, yy-b
         );
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Tensor22<T>::all_test(Pred pred) const noexcept
    {
        return 
            pred(xx) && pred(xy) && 
            pred(yx) && pred(yy)
        ;
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Tensor22<T>::all_test(const Tensor22& b, Pred pred) const noexcept
    {
        return 
            pred(xx, b.xx) && pred(xy, b.xy) &&
            pred(yx, b.yx) && pred(yy, b.yy)
        ;
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Tensor22<T>::all_test(T b, Pred pred) const noexcept
    {
        return 
            pred(xx, b) && pred(xy, b) && 
            pred(yx, b) && pred(yy, b)
        ;
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Tensor22<T>::any_test(Pred pred) const noexcept
    {
        return 
            pred(xx) || pred(xy) || 
            pred(yx) || pred(yy)
        ;
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Tensor22<T>::any_test(const Tensor22& b, Pred pred) const noexcept
    {
        return 
            pred(xx, b.xx) || pred(xy, b.xy) || 
            pred(yx, b.yx) || pred(yy, b.yy) 
        ;
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Tensor22<T>::any_test(T b, Pred pred) const noexcept
    {
        return 
            pred(xx, b) || pred(xy, b) || 
            pred(yx, b) || pred(yy, b) 
        ;
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
    requires is_arithmetic_v<T>
    constexpr Tensor22<product_t<T,U>>  operator*(T a, const Tensor22<T>& b)
    {
        return Tensor22<product_t<T,U>>(
            a*b.xx, a*b.xy,
            a*b.yx, a*b.yy
        );
    }

    template <typename T>
    AllComponents<Tensor22<T>>   all(Tensor22<T>& val)
    {
        return { val };
    }

    template <typename T>
    AllComponents<const Tensor22<T>>   all(const Tensor22<T>& val)
    {
        return { val };
    }
    
    template <typename T>
    AnyComponents<Tensor22<T>>   any(Tensor22<T>& val)
    {
        return { val };
    }

    template <typename T>
    AnyComponents<const Tensor22<T>>   any(const Tensor22<T>& val)
    {
        return { val };
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

    #if 0
    template <typename T>
    ElemComponents<Tensor22<T>>   elem(Tensor22<T>& val)
    {
        return { val };
    }

    template <typename T>
    ElemComponents<const Tensor22<T>>   elem(const Tensor22<T>& val)
    {
        return { val };
    }
    #endif
    
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

    #ifdef YQ_USE_GLM
    template <typename T, glm::qualifier Q>
    constexpr Tensor22<T> tensor(const glm::mat<2,2,T,Q>& t)
    {
        return Tensor22<T>(t);
    }
    #endif

    #ifdef YQ_MATH_SPINOR2_HPP
    template <typename T>
    constexpr Tensor22<T> tensor(const Spinor2<T>& t)
    {
        return Tensor22<T>(t);
    }
    #endif

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

    template <typename S, typename T>
    S&  as_stream(S& s, const Tensor22<T>& v)
    {
        return s << "[" << v.xx << "," << v.xy << ";" << v.yx << "," << v.yy << "]";
    }
    
    #ifdef YQ_BASIC_STREAM_HPP_
    template <typename T>
    Stream& operator<<(Stream&s, const Tensor22<T>& v)
    {
        return as_stream(s, v);
    }
    #endif

    #ifdef _LOG4CPP_CATEGORYSTREAM_HH
    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const Tensor22<T>& v)
    {
        return as_stream(s, v);
    }
    #endif
}
