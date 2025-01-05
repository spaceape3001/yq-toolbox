////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the tensor14 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <yq/tensor/Tensor14.hpp>
#include <yq/math/utility.hpp>

#include <yq/math/AllComponents.hpp>
#include <yq/math/AnyComponents.hpp>

namespace yq {
    #ifdef YQ_USE_GLM
    template <typename T>
        template <glm::qualifier Q>
    constexpr Tensor14<T>::Tensor14(const glm::mat<1,4,T,Q>& t) noexcept :
        xx(t[0][0]), xy(t[1][0]), xz(t[2][0]), xw(t[3][0])
    {
    }
    #endif

    #ifdef YQ_USE_GLM
    template <typename T>
    constexpr Tensor14<T>::operator glm::mat<1,4,T,glm::defaultp>() const noexcept 
    {
        return glm::mat<1,4,T,glm::defaultp>(
            xx,
            xy,
            xz,
            xw
        );
    }
    #endif

    template <typename T>
    constexpr Tensor14<T>  Tensor14<T>::operator+() const noexcept 
    { 
        return *this; 
    }

    template <typename T>
    constexpr Tensor14<T>  Tensor14<T>::operator-() const noexcept
    {
        return Tensor14(
            -xx, -xy, -xz, -xw
        );
    }
    

    template <typename T>
    constexpr Tensor14<T>   Tensor14<T>::operator+ (const Tensor14<T> &b) const noexcept
    {
        return Tensor14(
            xx+b.xx, xy+b.xy, xz+b.xz, xw+b.xw
        );
    }

    template <typename T>
    Tensor14<T>&   Tensor14<T>::operator+=(const Tensor14<T> &b) noexcept
    {
        xx+=b.xx;  xy+=b.xy;  xz+=b.xz;  xw+=b.xw;
        return *this;
    }



    template <typename T>
    constexpr Tensor14<T>   Tensor14<T>::operator- (const Tensor14<T> &b) const noexcept
    {
        return Tensor14(
            xx-b.xx, xy-b.xy, xz-b.xz, xw-b.xw
        );
    }
    

    template <typename T>
    Tensor14<T>&   Tensor14<T>::operator-=(const Tensor14<T> &b) noexcept
    {
        xx-=b.xx;  xy-=b.xy;  xz-=b.xz;  xw-=b.xw;
        return *this;
    }
    
    
    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    constexpr Tensor14<product_t<T,U>>  Tensor14<T>::operator*(U b) const noexcept
    {
        return Tensor14<product_t<T,U>>(
            xx*b, xy*b, xz*b, xw*b
        );
    }
    
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
    Tensor14<T>&  Tensor14<T>::operator*=(U b) noexcept
    {
        xx*=b; xy*=b; xz*=b; xw*=b;        
        return *this;
    }

    #if defined(YQ_MATH_SEGMENT1_HPP) && defined(YQ_MATH_SEGMENT4_HPP)
    template <typename T>
        template <typename U>
    constexpr Segment1<product_t<T,U>>  Tensor14<T>::operator*(const Segment4<U>&rhs) const noexcept
    {
        return Segment1<product_t<T,U>>( *this * rhs.a, *this * rhs.b );
    }
    #endif
    
    #if defined(YQ_MATH_TENSOR_1_1_HPP) && defined(YQ_MATH_TENSOR_4_1_HPP)
    template <typename T>
        template <typename U>
    constexpr Tensor11<product_t<T,U>> Tensor14<T>::operator*(const Tensor41<U>& b) const noexcept
    {
        return Tensor11<product_t<T,U>>(
            xx*b.xx + xy*b.yx + xz*b.zx + xw*b.wx
        );
    }
    #endif
    
    #if defined(YQ_MATH_TENSOR_1_2_HPP) && defined(YQ_MATH_TENSOR_4_2_HPP)
    template <typename T>
        template <typename U>
    constexpr Tensor12<product_t<T,U>> Tensor14<T>::operator*(const Tensor42<U>& b) const noexcept
    {
        return Tensor12<product_t<T,U>>(
            xx*b.xx + xy*b.yx + xz*b.zx + xw*b.wx,
            xx*b.xy + xy*b.yy + xz*b.zy + xw*b.wy
        );
    }
    #endif
    
    #if defined(YQ_MATH_TENSOR_1_3_HPP) && defined(YQ_MATH_TENSOR_4_3_HPP)
    template <typename T>
        template <typename U>
    constexpr Tensor13<product_t<T,U>> Tensor14<T>::operator*(const Tensor43<U>& b) const noexcept
    {
        return Tensor13<product_t<T,U>>(
            xx*b.xx + xy*b.yx + xz*b.zx + xw*b.wx,
            xx*b.xy + xy*b.yy + xz*b.zy + xw*b.wy,
            xx*b.xz + xy*b.yz + xz*b.zz + xw*b.wz
        );
    }
    #endif
    
    #ifdef YQ_MATH_TENSOR_4_4_HPP
    template <typename T>
        template <typename U>
    constexpr Tensor14<product_t<T,U>> Tensor14<T>::operator*(const Tensor44<U>& b) const noexcept
    {
        return Tensor14<product_t<T,U>>(
            xx*b.xx + xy*b.yx + xz*b.zx + xw*b.wx,
            xx*b.xy + xy*b.yy + xz*b.zy + xw*b.wy,
            xx*b.xz + xy*b.yz + xz*b.zz + xw*b.wz,
            xx*b.xw + xy*b.yw + xz*b.zw + xw*b.ww
        );
    }
    #endif
    
    #ifdef YQ_MATH_TENSOR_4_4_HPP
    template <typename T>
        template <typename U>
    requires self_multiply_v<T,U>
    Tensor14<T>& Tensor14<T>::operator*=(const Tensor44<U>& b) noexcept
    {
        *this = *this * b;
        return *this;
    }
    #endif
            
    template <typename T>
        template <typename U>
    constexpr Vector1<product_t<T,U>> Tensor14<T>::operator*(const Vector4<U>&b) const noexcept
    {
        return Vector1<product_t<T,U>>(
            xx*b.x + xy*b.y + xz*b.z + xw*b.w
        );
    }

    template <typename T>
        template <typename U>
    std::vector<Vector1<product_t<T,U>>>    Tensor14<T>::operator*(std::span<const Vector4<U>> bs) const
    {
        return transform(bs, [&](const Vector4<U>& b) -> Vector1<product_t<T,U>> {
            return *this * b;
        });
    }

    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    constexpr Tensor14<quotient_t<T,U>>  Tensor14<T>::operator/(U b) const noexcept
    {
        return Tensor14<quotient_t<T,U>>(
            xx/b, xy/b, xz/b, xw/b
        );
    }
    
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_divide_v<T,U>)
    Tensor14<T>&  Tensor14<T>::operator/=(U b) noexcept
    {
        xx/=b; xy/=b; xz/=b; xw/=b;        
        return *this;
    }    

    template <typename T>
    constexpr Tensor14<T> Tensor14<T>::all_add(T b) const noexcept
    {
        return Tensor14( 
            xx+b, xy+b, xz+b, xw+b
         );
    }

    template <typename T>
    Tensor14<T>&    Tensor14<T>::all_decrement(T b) noexcept
    {
        xx-=b; xy-=b; xz-=b; xw-=b;
        return *this;
    }

    template <typename T>
    Tensor14<T>&    Tensor14<T>::all_increment(T b) noexcept
    {
        xx+=b; xy+=b; xz+=b; xw+=b;
        return *this;
    }
    
    template <typename T>
    constexpr Tensor14<T> Tensor14<T>::all_subtract(T b) const noexcept
    {
        return Tensor14( 
            xx-b, xy-b, xz-b, xw-b
         );
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Tensor14<T>::all_test(Pred pred) const noexcept
    {
        return 
            pred(xx) && pred(xy) && pred(xz) && pred(xw)
        ;
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Tensor14<T>::all_test(const Tensor14& b, Pred pred) const noexcept
    {
        return 
            pred(xx, b.xx) && pred(xy, b.xy) && pred(xz, b.xz) && pred(xw, b.xw)
        ;
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Tensor14<T>::all_test(T b, Pred pred) const noexcept
    {
        return 
            pred(xx, b) && pred(xy, b) && pred(xz, b) && pred(xw, b) 
        ;
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Tensor14<T>::any_test(Pred pred) const noexcept
    {
        return 
            pred(xx) || pred(xy) || pred(xz) || pred(xw)
        ;
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Tensor14<T>::any_test(const Tensor14& b, Pred pred) const noexcept
    {
        return 
            pred(xx, b.xx) || pred(xy, b.xy) || pred(xz, b.xz) || pred(xw, b.xw)
        ;
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Tensor14<T>::any_test(T b, Pred pred) const noexcept
    {
        return 
            pred(xx, b) || pred(xy, b) || pred(xz, b) || pred(xw, b) 
        ;
    }

    #ifdef YQ_MATH_TENSOR_4_1_HPP
    template <typename T>
    constexpr Tensor41<T>   Tensor14<T>::transpose() const noexcept
    {
        return Tensor41<T>(
            xx,
            xy,
            xz,
            xw
        );
    }
    #endif

    template <typename T>
    constexpr Vector1<T>  Tensor14<T>::w_column() const noexcept
    {
        return Vector1<T>(xw);
    }

    template <typename T>
    Tensor14<T>& Tensor14<T>::w_column(const Vector1<T>& v)
    {
        xw = v.x;
        return *this;
    }

    template <typename T>
    Tensor14<T>& Tensor14<T>::w_column(T _xw)
    {
        xw = _xw;
        return *this;
    }

    template <typename T>
    constexpr Vector1<T>  Tensor14<T>::x_column() const noexcept
    {
        return Vector1<T>(xx);
    }

    template <typename T>
    Tensor14<T>& Tensor14<T>::x_column(const Vector1<T>& v)
    {
        xx = v.x;
        return *this;
    }

    template <typename T>
    Tensor14<T>& Tensor14<T>::x_column(T _xx)
    {
        xx = _xx;
        return *this;
    }

    template <typename T>
    constexpr Vector4<T>  Tensor14<T>::x_row() const noexcept
    {
        return Vector4<T>(xx, xy, xz, xw);
    }


    template <typename T>
    Tensor14<T>& Tensor14<T>::x_row(const Vector4<T>& v)
    {
        xx = v.x;
        xy = v.y;
        xz = v.z;
        xw = v.w;
        return *this;
    }

    template <typename T>
    Tensor14<T>& Tensor14<T>::x_row(T _xx, T _xy, T _xz, T _xw)
    {
        xx = _xx;
        xy = _xy;
        xz = _xz;
        xw = _xw;
        return *this;
    }
    
    template <typename T>
    constexpr Vector1<T>  Tensor14<T>::y_column() const noexcept
    {
        return Vector1<T>(xy);
    }

    template <typename T>
    Tensor14<T>& Tensor14<T>::y_column(const Vector1<T>& v)
    {
        xy = v.x;
        return *this;
    }

    template <typename T>
    Tensor14<T>& Tensor14<T>::y_column(T _xy)
    {
        xy = _xy;
        return *this;
    }

    template <typename T>
    constexpr Vector1<T>  Tensor14<T>::z_column() const noexcept
    {
        return Vector1<T>(xz);
    }


    template <typename T>
    Tensor14<T>& Tensor14<T>::z_column(const Vector1<T>& v)
    {
        xz = v.x;
        return *this;
    }

    template <typename T>
    Tensor14<T>& Tensor14<T>::z_column(T _xz)
    {
        xz = _xz;
        return *this;
    }



    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Tensor14<product_t<T,U>>  operator*(T a, const Tensor14<U>& b)
    {
        return Tensor14<product_t<T,U>>(
            a*b.xx, a*b.xy, a*b.xz, a*b.xw
        );
    }

    template <typename T>
    AllComponents<Tensor14<T>>   all(Tensor14<T>& val)
    {
        return { val };
    }

    template <typename T>
    AllComponents<const Tensor14<T>>   all(const Tensor14<T>& val)
    {
        return { val };
    }
    
    template <typename T>
    AnyComponents<Tensor14<T>>   any(Tensor14<T>& val)
    {
        return { val };
    }

    template <typename T>
    AnyComponents<const Tensor14<T>>   any(const Tensor14<T>& val)
    {
        return { val };
    }
    
    #if 0
    template <typename T>
    ElemComponents<Tensor14<T>>   elem(Tensor14<T>& val)
    {
        return { val };
    }

    template <typename T>
    ElemComponents<const Tensor14<T>>   elem(const Tensor14<T>& val)
    {
        return { val };
    }
    #endif
    
    #ifdef YQ_MATH_TENSOR_4_1_HPP
    template <typename T>
    constexpr Tensor41<T>  transpose(const Tensor14<T>&v)
    {
        return v.transpose();
    }
    #endif
    

    template <typename T>
    constexpr Vector1<T>  w_column(const Tensor14<T>&ten) 
    {
        return ten.w_column();
    }

    template <typename T>
    constexpr Vector1<T>  x_column(const Tensor14<T>&ten) 
    {
        return ten.x_column();
    }

    template <typename T>
    constexpr Vector4<T>  x_row(const Tensor14<T>&ten)
    {
        return ten.x_row();
    }

    template <typename T>
    constexpr Vector1<T>  y_column(const Tensor14<T>&ten) 
    {
        return ten.y_column();
    }

    template <typename T>
    constexpr Vector1<T>  z_column(const Tensor14<T>&ten) 
    {
        return ten.z_column();
    }

}
