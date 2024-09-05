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

#include <yq-toolbox/vector/Tensor13.hpp>
#include <yq-toolbox/math/utility.hpp>

#include <yq-toolbox/math/AllComponents.hpp>
#include <yq-toolbox/math/AnyComponents.hpp>


namespace yq {
    #ifdef YQ_USE_GLM
    template <typename T>
        template <glm::qualifier Q>
    constexpr Tensor13<T>::Tensor13(const glm::mat<1,3,T,Q>& t) noexcept :
        xx(t.x.x), xy(t.y.x), xz(t.z.x)
    {
    }
    #endif

    #ifdef YQ_USE_GLM
    template <typename T>
    constexpr Tensor13<T>::operator glm::mat<1,3,T,glm::defaultp>() const noexcept 
    {
        return glm::mat<1,3,T,glm::defaultp>(
            xx,
            xy,
            xz
        );
    }
    #endif

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
    requires is_arithmetic_v<U>
    constexpr Tensor13<product_t<T,U>>  Tensor13<T>::operator*(U b) const noexcept
    {
        return Tensor13<product_t<T,U>>(
            xx*b, xy*b, xz*b
        );
    }
    
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
    Tensor13<T>&  Tensor13<T>::operator*=(U b) noexcept
    {
        xx*=b; xy*=b; xz*=b;        
        return *this;
    }
    
    #if defined(YQ_MATH_SEGMENT1_HPP) && defined(YQ_MATH_SEGMENT3_HPP)
    template <typename T>
        template <typename U>
    constexpr Segment1<product_t<T,U>>  Tensor13<T>::operator*(const Segment3<U>&rhs) const noexcept
    {
        return Segment1<product_t<T,U>>( *this * rhs.a, *this * rhs.b );
    }
    #endif


    #if defined(YQ_MATH_TENSOR_1_1_HPP) && defined(YQ_MATH_TENSOR_3_1_HPP)
    template <typename T>
        template <typename U>
    constexpr Tensor11<product_t<T,U>> Tensor13<T>::operator*(const Tensor31<U>& b) const noexcept
    {
        return Tensor11<product_t<T,U>>(
            xx*b.xx + xy*b.yx + xz*b.zx
        );
    }
    #endif
    
    #if defined(YQ_MATH_TENSOR_1_2_HPP) && defined(YQ_MATH_TENSOR_3_2_HPP)
    template <typename T>
        template <typename U>
    constexpr Tensor12<product_t<T,U>> Tensor13<T>::operator*(const Tensor32<U>& b) const noexcept
    {
        return Tensor12<product_t<T,U>>(
            xx*b.xx + xy*b.yx + xz*b.zx,
            xx*b.xy + xy*b.yy + xz*b.zy
        );
    }
    #endif
    
    #ifdef YQ_MATH_TENSOR_3_3_HPP
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
    #endif
    
    #ifdef YQ_MATH_TENSOR_3_3_HPP
    template <typename T>
        template <typename U>
    requires self_multiply_v<T,U>
    Tensor13<T>& Tensor13<T>::operator*=(const Tensor33<U>& b) noexcept
    {
        *this = *this * b;
        return *this;
    }
    #endif

    #if defined(YQ_MATH_TENSOR_1_4_HPP) && defined(YQ_MATH_TENSOR_3_4_HPP)
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
    #endif
        
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
    std::vector<Vector1<product_t<T,U>>>    Tensor13<T>::operator*(std::span<const Vector3<U>> bs) const
    {
        return transform(bs, [&](const Vector3<U>& b) -> Vector1<product_t<T,U>> {
            return *this * b;
        });
    }

    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    constexpr Tensor13<quotient_t<T,U>>  Tensor13<T>::operator/(U b) const noexcept
    {
        return Tensor13<quotient_t<T,U>>(
            xx/b, xy/b, xz/b
        );
    }
    
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_divide_v<T,U>)
    Tensor13<T>&  Tensor13<T>::operator/=(U b) noexcept
    {
        xx/=b; xy/=b; xz/=b;        
        return *this;
    }


    template <typename T>
    constexpr Tensor13<T> Tensor13<T>::all_add(T b) const noexcept
    {
        return Tensor13( 
            xx+b, xy+b, xz+b
         );
    }

    template <typename T>
    Tensor13<T>&    Tensor13<T>::all_decrement(T b) noexcept
    {
        xx-=b; xy-=b; xz-=b;
        return *this;
    }

    template <typename T>
    Tensor13<T>&    Tensor13<T>::all_increment(T b) noexcept
    {
        xx+=b; xy+=b; xz+=b;
        return *this;
    }
    
    template <typename T>
    constexpr Tensor13<T> Tensor13<T>::all_subtract(T b) const noexcept
    {
        return Tensor13( 
            xx-b, xy-b, xz-b
         );
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Tensor13<T>::all_test(Pred pred) const noexcept
    {
        return 
            pred(xx) && pred(xy) && pred(xz)
        ;
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Tensor13<T>::all_test(const Tensor13& b, Pred pred) const noexcept
    {
        return 
            pred(xx, b.xx) && pred(xy, b.xy) && pred(xz, b.xz)
        ;
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Tensor13<T>::all_test(T b, Pred pred) const noexcept
    {
        return 
            pred(xx, b) && pred(xy, b) && pred(xz, b)
        ;
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Tensor13<T>::any_test(Pred pred) const noexcept
    {
        return 
            pred(xx) || pred(xy) || pred(xz)
        ;
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Tensor13<T>::any_test(const Tensor13& b, Pred pred) const noexcept
    {
        return 
            pred(xx, b.xx) || pred(xy, b.xy) || pred(xz, b.xz)
        ;
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Tensor13<T>::any_test(T b, Pred pred) const noexcept
    {
        return 
            pred(xx, b) || pred(xy, b) || pred(xz, b)
        ;
    }
        
    #ifdef YQ_MATH_TENSOR_3_1_HPP
    template <typename T>
    constexpr Tensor31<T> Tensor13<T>::transpose() const noexcept
    {
        return Tensor31<T>(
            xx,
            xy,
            xz
        );
    }
    #endif

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
    requires is_arithmetic_v<T>
    constexpr Tensor13<product_t<T,U>>  operator*(T a, const Tensor13<U>& b)
    {
        return {
            a*b.xx, a*b.xy, a*b.xz
        };
    }


    template <typename T>
    AllComponents<Tensor13<T>>   all(Tensor13<T>& val)
    {
        return { val };
    }

    template <typename T>
    AllComponents<const Tensor13<T>>   all(const Tensor13<T>& val)
    {
        return { val };
    }
    
    template <typename T>
    AnyComponents<Tensor13<T>>   any(Tensor13<T>& val)
    {
        return { val };
    }

    template <typename T>
    AnyComponents<const Tensor13<T>>   any(const Tensor13<T>& val)
    {
        return { val };
    }
    
    #if 0
    template <typename T>
    ElemComponents<Tensor13<T>>   elem(Tensor13<T>& val)
    {
        return { val };
    }

    template <typename T>
    ElemComponents<const Tensor13<T>>   elem(const Tensor13<T>& val)
    {
        return { val };
    }
    #endif
    
    #ifdef YQ_MATH_TENSOR_3_1_HPP
    template <typename T>
    constexpr Tensor31<T>  transpose(const Tensor13<T>&v)
    {
        return v.transpose();
    }
    #endif

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
