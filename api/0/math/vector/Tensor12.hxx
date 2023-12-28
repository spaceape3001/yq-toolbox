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

#include <0/math/vector/Tensor12.hpp>
#include <0/math/utility.hpp>
#include <0/math/AllComponents.hpp>
#include <0/math/AnyComponents.hpp>


namespace yq {
    #ifdef YQ_USE_GLM
    template <typename T>
        template <glm::qualifier Q>
    constexpr Tensor12<T>::Tensor12(const glm::mat<1,2,T,Q>& t) noexcept :
        xx(t.x.x), xy(t.y.x)
    {
    }
    #endif

    #ifdef YQ_USE_GLM
    template <typename T>
    constexpr Tensor12<T>::operator glm::mat<1,2,T,glm::defaultp>() const noexcept 
    {
        return glm::mat<1,2,T,glm::defaultp>(
            xx,
            xy
        );
    }
    #endif

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
    requires is_arithmetic_v<U>
    constexpr Tensor12<product_t<T,U>>  Tensor12<T>::operator*(U b) const noexcept
    {
        return Tensor12<product_t<T,U>>(
            xx*b, xy*b
        );
    }
    
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_mul_v<T,U>)
    Tensor12<product_t<T,U>>  Tensor12<T>::operator*=(U b) noexcept
    {
        xx*=b; xy*=b;        
        return *this;
    }

    #if defined(YQ_MATH_SEGMENT1_HPP) && defined(YQ_MATH_SEGMENT2_HPP)
    template <typename T>
        template <typename U>
    constexpr Segment1<product_t<T,U>>  Tensor12<T>::operator*(const Segment2<U>&rhs) const noexcept
    {
        return Segment1<product_t<T,U>>( *this * rhs.a, *this * rhs.b );
    }
    #endif

    #if defined(YQ_MATH_TENSOR_1_1_HPP) && defined(YQ_MATH_TENSOR_2_1_HPP)
    template <typename T>
        template <typename U>
    constexpr Tensor11<product_t<T,U>> Tensor12<T>::operator*(const Tensor21<U>& b) const noexcept
    {
        return Tensor11<product_t<T,U>>(
            xx*b.xx + xy*b.yx
        );
    }
    #endif
    
    #ifdef YQ_MATH_TENSOR_2_2_HPP
    template <typename T>
        template <typename U>
    constexpr Tensor12<product_t<T,U>> Tensor12<T>::operator*(const Tensor22<U>& b) const noexcept
    {
        return Tensor12<product_t<T,U>>(
            xx*b.xx + xy*b.yx,
            xx*b.xy + xy*b.yy
        );
    }
    #endif
    
    #ifdef YQ_MATH_TENSOR_2_2_HPP
    template <typename T>
        template <typename U>
    requires self_mul_v<T,U>
    Tensor12<T>& Tensor12<T>::operator*=(const Tensor22<U>& b) noexcept
    {
        *this = *this * b;
        return *this;
    }
    #endif

    #if defined(YQ_MATH_TENSOR_1_3_HPP) && defined(YQ_MATH_TENSOR_2_3_HPP)
    template <typename T>
        template <typename U>
    constexpr Tensor13<product_t<T,U>> Tensor12<T>::operator*(const Tensor23<U>& b) const noexcept
    {
        return Tensor13<product_t<T,U>>(
            xx*b.xx + xy*b.yx,
            xx*b.xy + xy*b.yy,
            xx*b.xz + xy*b.yz
        );
    }
    #endif
    
    #if defined(YQ_MATH_TENSOR_1_4_HPP) && defined(YQ_MATH_TENSOR_2_4_HPP)
    template <typename T>
        template <typename U>
    constexpr Tensor14<product_t<T,U>> Tensor12<T>::operator*(const Tensor24<U>& b) const noexcept
    {
        return Tensor14<product_t<T,U>>(
            xx*b.xx + xy*b.yx,
            xx*b.xy + xy*b.yy,
            xx*b.xz + xy*b.yz,
            xx*b.xw + xy*b.yw
        );
    }
    #endif

    template <typename T>
        template <typename U>
    constexpr Vector1<product_t<T,U>> Tensor12<T>::operator*(const Vector2<U>&b) const noexcept
    {
        return Vector1<product_t<T,U>>(
            xx*b.x + xy*b.y
        );
    }

    template <typename T>
        template <typename U>
    std::vector<Vector1<product_t<T,U>>>    Tensor12<T>::operator*(std::span<const Vector2<U>> bs) const
    {
        return transform(bs, [&](const Vector2<U>& b) -> Vector1<product_t<T,U>> {
            return *this * b;
        });
    }

    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    constexpr Tensor12<quotient_t<T,U>>  Tensor12<T>::operator/(U b) const noexcept
    {
        return Tensor12<quotient_t<T,U>> (
            xx/b, xy/b
        );
    }
    
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_div_v<T,U>)
    Tensor12<quotient_t<T,U>>  Tensor12<T>::operator/=(U b) noexcept
    {
        xx/=b; xy/=b;        
        return *this;
    }

    template <typename T>
    constexpr Tensor12<T> Tensor12<T>::all_add(T b) const noexcept
    {
        return Tensor12( 
            xx+b, xy+b
         );
    }

    template <typename T>
    Tensor12<T>&    Tensor12<T>::all_decrement(T b) noexcept
    {
        xx-=b; xy-=b;
        return *this;
    }

    template <typename T>
    Tensor12<T>&    Tensor12<T>::all_increment(T b) noexcept
    {
        xx+=b; xy+=b;
        return *this;
    }
    
    template <typename T>
    constexpr Tensor12<T> Tensor12<T>::all_subtract(T b) const noexcept
    {
        return Tensor12( 
            xx-b, xy-b
         );
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Tensor12<T>::all_test(Pred pred) const noexcept
    {
        return 
            pred(xx) && pred(xy)
        ;
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Tensor12<T>::all_test(const Tensor12& b, Pred pred) const noexcept
    {
        return 
            pred(xx, b.xx) && pred(xy, b.xy)
        ;
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Tensor12<T>::all_test(T b, Pred pred) const noexcept
    {
        return 
            pred(xx, b) && pred(xy, b)
        ;
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Tensor12<T>::any_test(Pred pred) const noexcept
    {
        return 
            pred(xx) || pred(xy)
        ;
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Tensor12<T>::any_test(const Tensor12& b, Pred pred) const noexcept
    {
        return 
            pred(xx, b.xx) || pred(xy, b.xy) 
        ;
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Tensor12<T>::any_test(T b, Pred pred) const noexcept
    {
        return 
            pred(xx, b) || pred(xy, b) 
        ;
    }


    #ifdef YQ_MATH_TENSOR_2_1_HPP
    template <typename T>
    constexpr Tensor21<T> Tensor12<T>::transpose() const noexcept
    {
        return Tensor21<T>(
            xx,
            xy
        );
    }
    #endif

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
    constexpr Tensor12<product_t<T,U>>  operator*(T a, const Tensor12<U>& b)
    {
        return Tensor12<product_t<T,U>>(
            a*b.xx, a*b.xy
        );
    }

    template <typename T>
    AllComponents<Tensor12<T>>   all(Tensor12<T>& val)
    {
        return { val };
    }

    template <typename T>
    AllComponents<const Tensor12<T>>   all(const Tensor12<T>& val)
    {
        return { val };
    }
    
    template <typename T>
    AnyComponents<Tensor12<T>>   any(Tensor12<T>& val)
    {
        return { val };
    }

    template <typename T>
    AnyComponents<const Tensor12<T>>   any(const Tensor12<T>& val)
    {
        return { val };
    }

    #if 0
    template <typename T>
    ElemComponents<Tensor12<T>>   elem(Tensor12<T>& val)
    {
        return { val };
    }

    template <typename T>
    ElemComponents<const Tensor12<T>>   elem(const Tensor12<T>& val)
    {
        return { val };
    }
    #endif

    #ifdef YQ_MATH_TENSOR_2_1_HPP
    template <typename T>
    constexpr Tensor21<T>  transpose(const Tensor12<T>&v) noexcept
    {
        return v.transpose();
    }
    #endif

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
