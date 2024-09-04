////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the tensor23 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <0/math/vector/Tensor23.hpp>
#include <yq/math/utility.hpp>

#include <yq/math/AllComponents.hpp>
#include <yq/math/AnyComponents.hpp>

namespace yq {
    #ifdef YQ_USE_GLM
    template <typename T>
        template <glm::qualifier Q>
    constexpr Tensor23<T>::Tensor23(const glm::mat<2,3,T,Q>& t) noexcept :
        xx(t.x.x), xy(t.y.x), xz(t.z.x),
        yx(t.x.y), yy(t.y.y), yz(t.z.y)
    {
    }
    #endif

    #ifdef YQ_USE_GLM
    template <typename T>
    constexpr Tensor23<T>::operator glm::mat<2,3,T,glm::defaultp>() const noexcept 
    {
        return glm::mat<2,3,T,glm::defaultp>(
            xx, yx, 
            xy, yy, 
            xz, yz
        );
    }
    #endif

    template <typename T>
    constexpr Tensor23<T>  Tensor23<T>::operator+() const noexcept
    { 
        return *this; 
    }

    template <typename T>
    constexpr Tensor23<T>  Tensor23<T>::operator-() const noexcept
    {
        return Tensor23(
            -xx, -xy, -xz,
            -yx, -yy, -yz
        );
    }
    

    template <typename T>
    constexpr Tensor23<T>   Tensor23<T>::operator+ (const Tensor23<T> &b) const noexcept
    {
        return Tensor23(
            xx+b.xx, xy+b.xy, xz+b.xz,
            yx+b.yx, yy+b.yy, yz+b.yz
        );
    }

    template <typename T>
    Tensor23<T>&   Tensor23<T>::operator+=(const Tensor23<T> &b)  noexcept
    {
        xx+=b.xx;  xy+=b.xy;  xz+=b.xz;
        yx+=b.yx;  yy+=b.yy;  yz+=b.yz;
        return *this;
    }


    template <typename T>
    constexpr Tensor23<T>   Tensor23<T>::operator- (const Tensor23<T> &b) const noexcept
    {
        return Tensor23(
            xx-b.xx, xy-b.xy, xz-b.xz,
            yx-b.yx, yy-b.yy, yz-b.yz
        );
    }
    

    template <typename T>
    Tensor23<T>&   Tensor23<T>::operator-=(const Tensor23<T> &b) noexcept
    {
        xx-=b.xx;  xy-=b.xy;  xz-=b.xz;
        yx-=b.yx;  yy-=b.yy;  yz-=b.yz;
        return *this;
    }
        
    
    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    constexpr Tensor23<product_t<T,U>>  Tensor23<T>::operator*(U b) const noexcept
    {
        return Tensor23<product_t<T,U>>(
            xx*b, xy*b, xz*b,
            yx*b, yy*b, yz*b
        );
    }
    
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
    Tensor23<T>&  Tensor23<T>::operator*=(U b) noexcept
    {
        xx*=b; xy*=b; xz*=b;
        yx*=b; yy*=b; yz*=b;        
        return *this;
    }

    #if defined(YQ_MATH_POLYGON2_HPP) && defined(YQ_MATH_POLYGON3_HPP)
    template <typename T>
        template <typename U>
    Polygon2<product_t<T,U>>  Tensor23<T>::operator*(const Polygon3<U>&b) const
    {
        return Polygon2<product_t<T,U>>( *this * b.vertex );
    }
    #endif
    
    #if defined(YQ_MATH_POLYLINE2_HPP) && defined(YQ_MATH_POLYLINE3_HPP)
    template <typename T>
        template <typename U>
    Polyline2<product_t<T,U>>  Tensor23<T>::operator*(const Polyline3<U>&b) const
    {
        return Polyline2<product_t<T,U>>( *this * b.vertex );
    }
    #endif

    #if defined(YQ_MATH_SEGMENT2_HPP) && defined(YQ_MATH_SEGMENT3_HPP)
    template <typename T>
        template <typename U>
    constexpr Segment2<product_t<T,U>>  Tensor23<T>::operator*(const Segment3<U>&rhs) const noexcept
    {
        return Segment2<product_t<T,U>>( *this * rhs.a, *this * rhs.b );
    }
    #endif

    #if defined(YQ_MATH_TENSOR_2_1_HPP) && defined(YQ_MATH_TENSOR_3_1_HPP)
    template <typename T>
        template <typename U>
    constexpr Tensor21<product_t<T,U>> Tensor23<T>::operator*(const Tensor31<U>& b) const noexcept
    {
        return Tensor21<product_t<T,U>>(
            xx*b.xx + xy*b.yx + xz*b.zx,

            yx*b.xx + yy*b.yx + yz*b.zx
        );
    }
    #endif
    
    #if defined(YQ_MATH_TENSOR_2_2_HPP) && defined(YQ_MATH_TENSOR_3_2_HPP)
    template <typename T>
        template <typename U>
    constexpr Tensor22<product_t<T,U>> Tensor23<T>::operator*(const Tensor32<U>& b) const noexcept
    {
        return Tensor22<product_t<T,U>>(
            xx*b.xx + xy*b.yx + xz*b.zx,
            xx*b.xy + xy*b.yy + xz*b.zy,

            yx*b.xx + yy*b.yx + yz*b.zx,
            yx*b.xy + yy*b.yy + yz*b.zy
        );
    }
    #endif
    
    #ifdef YQ_MATH_TENSOR_3_3_HPP
    template <typename T>
        template <typename U>
    constexpr Tensor23<product_t<T,U>> Tensor23<T>::operator*(const Tensor33<U>& b) const noexcept
    {
        return Tensor23<product_t<T,U>>(
            xx*b.xx + xy*b.yx + xz*b.zx,
            xx*b.xy + xy*b.yy + xz*b.zy,
            xx*b.xz + xy*b.yz + xz*b.zz,

            yx*b.xx + yy*b.yx + yz*b.zx,
            yx*b.xy + yy*b.yy + yz*b.zy,
            yx*b.xz + yy*b.yz + yz*b.zz
        );
    }
    #endif
    
    #ifdef YQ_MATH_TENSOR_3_3_HPP
    template <typename T>
        template <typename U>
    requires self_multiply_v<T,U>
    Tensor23<T>& Tensor23<T>::operator*=(const Tensor33<U>& b) noexcept
    {
        *this = *this * b;
        return *this;
    }
    #endif

    #if defined(YQ_MATH_TENSOR_2_4_HPP) && defined(YQ_MATH_TENSOR_3_4_HPP)
    template <typename T>
        template <typename U>
    constexpr Tensor24<product_t<T,U>> Tensor23<T>::operator*(const Tensor34<U>& b) const noexcept
    {
        return Tensor24<product_t<T,U>>(
            xx*b.xx + xy*b.yx + xz*b.zx,
            xx*b.xy + xy*b.yy + xz*b.zy,
            xx*b.xz + xy*b.yz + xz*b.zz,
            xx*b.xw + xy*b.yw + xz*b.zw,

            yx*b.xx + yy*b.yx + yz*b.zx,
            yx*b.xy + yy*b.yy + yz*b.zy,
            yx*b.xz + yy*b.yz + yz*b.zz,
            yx*b.xw + yy*b.yw + yz*b.zw
        );
    }
    #endif
        
    #if defined(YQ_MATH_TRIANGLE2_HPP) && defined(YQ_MATH_TRIANGLE3_HPP)
    template <typename T>
        template <typename U>
    Triangle2<product_t<T,U>> Tensor23<T>::operator*(const Triangle3<U>&rhs) const noexcept
    {
        return Triangle2<product_t<T,U>>( *this * rhs.a, *this * rhs.b, *this * rhs.c );
    }
    #endif

    template <typename T>
        template <typename U>
    constexpr Vector2<product_t<T,U>> Tensor23<T>::operator*(const Vector3<U>&b) const noexcept
    {
        return Vector2<product_t<T,U>>(
            xx*b.x + xy*b.y + xz*b.z,
            yx*b.x + yy*b.y + yz*b.z
        );
    }

    template <typename T>
        template <typename U>
    std::vector<Vector2<product_t<T,U>>>    Tensor23<T>::operator*(std::span<const Vector3<U>> bs) const
    {
        return transform(bs, [&](const Vector3<U>& b) -> Vector2<product_t<T,U>> {
            return *this * b;
        });
    }
    
    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    constexpr Tensor23<quotient_t<T,U>>  Tensor23<T>::operator/(U b) const noexcept
    {
        return Tensor23<quotient_t<T,U>>(
            xx/b, xy/b, xz/b,
            yx/b, yy/b, yz/b
        );
    }
    
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_divide_v<T,U>)
    Tensor23<T>&  Tensor23<T>::operator/=(U b) noexcept
    {
        xx/=b; xy/=b; xz/=b;
        yx/=b; yy/=b; yz/=b;        
        return *this;
    }
    

    template <typename T>
    constexpr Tensor23<T> Tensor23<T>::all_add(T b) const noexcept
    {
        return Tensor23( 
            xx+b, xy+b, xz+b,
            yx+b, yy+b, yz+b
         );
    }

    template <typename T>
    Tensor23<T>&    Tensor23<T>::all_decrement(T b) noexcept
    {
        xx-=b; xy-=b; xz-=b;
        yx-=b; yy-=b; yz-=b;
        return *this;
    }

    template <typename T>
    Tensor23<T>&    Tensor23<T>::all_increment(T b) noexcept
    {
        xx+=b; xy+=b; xz+=b;
        yx+=b; yy+=b; yz+=b;
        return *this;
    }
    
    template <typename T>
    constexpr Tensor23<T> Tensor23<T>::all_subtract(T b) const noexcept
    {
        return Tensor23( 
            xx-b, xy-b, xz-b,
            yx-b, yy-b, yz-b
         );
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Tensor23<T>::all_test(Pred pred) const noexcept
    {
        return 
            pred(xx) && pred(xy) && pred(xz) && 
            pred(yx) && pred(yy) && pred(yz) 
        ;
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Tensor23<T>::all_test(const Tensor23& b, Pred pred) const noexcept
    {
        return 
            pred(xx, b.xx) && pred(xy, b.xy) && pred(xz, b.xz) && 
            pred(yx, b.yx) && pred(yy, b.yy) && pred(yz, b.yz)
        ;
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Tensor23<T>::all_test(T b, Pred pred) const noexcept
    {
        return 
            pred(xx, b) && pred(xy, b) && pred(xz, b) && 
            pred(yx, b) && pred(yy, b) && pred(yz, b)
        ;
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Tensor23<T>::any_test(Pred pred) const noexcept
    {
        return 
            pred(xx) || pred(xy) || pred(xz) || 
            pred(yx) || pred(yy) || pred(yz)
        ;
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Tensor23<T>::any_test(const Tensor23& b, Pred pred) const noexcept
    {
        return 
            pred(xx, b.xx) || pred(xy, b.xy) || pred(xz, b.xz) ||
            pred(yx, b.yx) || pred(yy, b.yy) || pred(yz, b.yz)
        ;
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Tensor23<T>::any_test(T b, Pred pred) const noexcept
    {
        return 
            pred(xx, b) || pred(xy, b) || pred(xz, b) || 
            pred(yx, b) || pred(yy, b) || pred(yz, b)
        ;
    }
            
    #ifdef YQ_MATH_TENSOR_3_2_HPP
    template <typename T>
    constexpr Tensor32<T> Tensor23<T>::transpose() const noexcept
    {
        return Tensor32<T>(
            xx, yx,
            xy, yy,
            xz, yz
        );
    }
    #endif


    template <typename T>
    constexpr Vector2<T>  Tensor23<T>::x_column() const noexcept
    {
        return Vector2<T>(xx, yx);
    }

    template <typename T>
    Tensor23<T>& Tensor23<T>::x_column(const Vector2<T>& v)
    {
        xx = v.x;
        yx = v.y;
        return *this;
    }

    template <typename T>
    Tensor23<T>& Tensor23<T>::x_column(T _xx, T _yx)
    {
        xx = _xx;
        yx = _yx;
        return *this;
    }

    template <typename T>
    constexpr Vector3<T>  Tensor23<T>::x_row() const noexcept
    {
        return Vector3<T>(xx, xy, xz);
    }

    template <typename T>
    Tensor23<T>& Tensor23<T>::x_row(const Vector3<T>& v)
    {
        xx = v.x;
        xy = v.y;
        xz = v.z;
        return *this;
    }

    template <typename T>
    Tensor23<T>& Tensor23<T>::x_row(T _xx, T _xy, T _xz)
    {
        xx = _xx;
        xy = _xy;
        xz = _xz;
        return *this;
    }

    template <typename T>
    constexpr Vector2<T>  Tensor23<T>::y_column() const noexcept
    {
        return Vector2<T>(xy, yy);
    }

    template <typename T>
    Tensor23<T>& Tensor23<T>::y_column(const Vector2<T>& v)
    {
        xy = v.x;
        yy = v.y;
        return *this;
    }

    template <typename T>
    Tensor23<T>& Tensor23<T>::y_column(T _xy, T _yy)
    {
        xy = _xy;
        yy = _yy;
        return *this;
    }

    template <typename T>
    constexpr Vector3<T>  Tensor23<T>::y_row() const noexcept
    {
        return Vector3<T>(yx, yy, yz);
    }


    template <typename T>
    Tensor23<T>& Tensor23<T>::y_row(const Vector3<T>& v)
    {
        yx = v.x;
        yy = v.y;
        yz = v.z;
        return *this;
    }

    template <typename T>
    Tensor23<T>& Tensor23<T>::y_row(T _yx, T _yy, T _yz)
    {
        yx = _yx;
        yy = _yy;
        yz = _yz;
        return *this;
    }
            
    template <typename T>
    constexpr Vector2<T>  Tensor23<T>::z_column() const noexcept
    {
        return Vector2<T>(xz, yz);
    }

    template <typename T>
    Tensor23<T>& Tensor23<T>::z_column(const Vector2<T>& v)
    {
        xz = v.x;
        yz = v.y;
        return *this;
    }

    template <typename T>
    Tensor23<T>& Tensor23<T>::z_column(T _xz, T _yz)
    {
        xz = _xz;
        yz = _yz;
        return *this;
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Tensor23<product_t<T,U>>  operator*(T a, const Tensor23<U>& b)
    {
        return {
            a*b.xx, a*b.xy, a*b.xz,
            a*b.yx, a*b.yy, a*b.yz
        };
    }


    template <typename T>
    AllComponents<Tensor23<T>>   all(Tensor23<T>& val)
    {
        return { val };
    }

    template <typename T>
    AllComponents<const Tensor23<T>>   all(const Tensor23<T>& val)
    {
        return { val };
    }
    
    template <typename T>
    AnyComponents<Tensor23<T>>   any(Tensor23<T>& val)
    {
        return { val };
    }

    template <typename T>
    AnyComponents<const Tensor23<T>>   any(const Tensor23<T>& val)
    {
        return { val };
    }
    
    #if 0
    template <typename T>
    ElemComponents<Tensor23<T>>   elem(Tensor23<T>& val)
    {
        return { val };
    }

    template <typename T>
    ElemComponents<const Tensor23<T>>   elem(const Tensor23<T>& val)
    {
        return { val };
    }
    #endif
    
    #ifdef YQ_MATH_TENSOR_3_2_HPP
    template <typename T>
    constexpr Tensor32<T>  transpose(const Tensor23<T>&v)
    {
        return v.transpose();
    }
    #endif

    //! Gets the X-column of the provided tensor
    template <typename T>
    constexpr Vector2<T>  x_column(const Tensor23<T>&ten) 
    {
        return ten.x_column();
    }


    //! Gets the X-row of the provided tensor
    template <typename T>
    constexpr Vector3<T>  x_row(const Tensor23<T>&ten)
    {
        return ten.x_row();
    }

    //! Gets the Y-column of the provided tensor
    template <typename T>
    constexpr Vector2<T>  y_column(const Tensor23<T>&ten) 
    {
        return ten.y_column();
    }

    //! Gets the Y-row of the provided tensor
    template <typename T>
    constexpr Vector3<T>  y_row(const Tensor23<T>&ten)
    {
        return ten.y_row();
    }

    //! Gets the Z-column of the provided tensor
    template <typename T>
    constexpr Vector2<T>  z_column(const Tensor23<T>&ten) 
    {
        return ten.z_column();
    }



}
