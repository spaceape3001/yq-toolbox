////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the tensor21 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <0/math/vector/Tensor21.hpp>
#include <0/math/utility.hpp>

#include <yq/math/AllComponents.hpp>
#include <yq/math/AnyComponents.hpp>

namespace yq {
    #ifdef YQ_USE_GLM
    template <typename T>
        template <glm::qualifier Q>
    constexpr Tensor21<T>::Tensor21(const glm::mat<2,1,T,Q>& t) noexcept :
        xx(t.x.x),
        yx(t.x.y)
    {
    }
    #endif

    #ifdef YQ_USE_GLM
    template <typename T>
    constexpr Tensor21<T>::operator glm::mat<2,1,T,glm::defaultp>() const noexcept 
    {
        return glm::mat<2,1,T,glm::defaultp>(
            xx, yx
        );
    }
    #endif

    template <typename T>
    constexpr Tensor21<T>  Tensor21<T>::operator+() const noexcept
    { 
        return *this; 
    }

    template <typename T>
    constexpr Tensor21<T>  Tensor21<T>::operator-() const noexcept
    {
        return Tensor21(
            -xx,
            -yx
        );
    }
    

    template <typename T>
    constexpr Tensor21<T>  Tensor21<T>::operator+ (const Tensor21<T> &b) const noexcept
    {
        return Tensor21(
            xx+b.xx,
            yx+b.yx
        );
    }

    template <typename T>
    Tensor21<T>&   Tensor21<T>::operator+=(const Tensor21<T> &b) noexcept
    {
        xx+=b.xx;
        yx+=b.yx;
        return *this;
    }

    template <typename T>
    constexpr Tensor21<T>   Tensor21<T>::operator- (const Tensor21<T> &b) const noexcept
    {
        return Tensor21(
            xx-b.xx,
            yx-b.yx
        );
    }
    

    template <typename T>
    Tensor21<T>&   Tensor21<T>::operator-=(const Tensor21<T> &b) noexcept 
    {
        xx-=b.xx;
        yx-=b.yx;
        return *this;
    }    
    
    
    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    constexpr Tensor21<product_t<T,U>>  Tensor21<T>::operator*(U b) const noexcept
    {
        return Tensor21<product_t<T,U>>(
            xx*b,
            yx*b
        );
    }
    
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_mul_v<T,U>) 
    Tensor21<T>&  Tensor21<T>::operator*=(U b) noexcept
    {
        xx*=b;
        yx*=b;        
        return *this;
    }
    
    #if defined(YQ_MATH_SEGMENT1_HPP) && defined(YQ_MATH_SEGMENT2_HPP)
    template <typename T>
        template <typename U>
    constexpr Segment2<product_t<T,U>>  Tensor21<T>::operator*(const Segment1<U>&rhs) const noexcept
    {
        return Segment2<product_t<T,U>>( *this * rhs.a, *this * rhs.b );
    }
    #endif

    #ifdef YQ_MATH_TENSOR_1_1_HPP
    template <typename T>
        template <typename U>
    constexpr Tensor21<product_t<T,U>> Tensor21<T>::operator*(const Tensor11<U>& b) const noexcept
    {
        return Tensor21<product_t<T,U>>(
            xx*b.xx,

            yx*b.xx
        );
    }
    #endif
    
    #ifdef YQ_MATH_TENSOR_1_1_HPP
    template <typename T>
        template <typename U>
    requires self_mul_v<T,U>
    Tensor21<T>& Tensor21<T>::operator*=(const Tensor11<U>& b) noexcept
    {
        *this = *this * b;
        return *this;
    }
    #endif

    #if defined(YQ_MATH_TENSOR_1_2_HPP) && defined(YQ_MATH_TENSOR_2_2_HPP)
    template <typename T>
        template <typename U>
    constexpr Tensor22<product_t<T,U>> Tensor21<T>::operator*(const Tensor12<U>& b) const noexcept
    {
        return Tensor22<product_t<T,U>>(
            xx*b.xx,
            xx*b.xy,

            yx*b.xx,
            yx*b.xy
        );
    }
    #endif
    
    #if defined(YQ_MATH_TENSOR_1_3_HPP) && defined(YQ_MATH_TENSOR_2_3_HPP)
    template <typename T>
        template <typename U>
    constexpr Tensor23<product_t<T,U>> Tensor21<T>::operator*(const Tensor13<U>& b) const noexcept
    {
        return Tensor23<product_t<T,U>>(
            xx*b.xx,
            xx*b.xy,
            xx*b.xz,

            yx*b.xx,
            yx*b.xy,
            yx*b.xz
        );
    }
    #endif
    
    #if defined(YQ_MATH_TENSOR_1_4_HPP) && defined(YQ_MATH_TENSOR_2_4_HPP)
    template <typename T>
        template <typename U>
    constexpr Tensor24<product_t<T,U>> Tensor21<T>::operator*(const Tensor14<U>& b) const noexcept
    {
        return Tensor24<product_t<T,U>>(
            xx*b.xx,
            xx*b.xy,
            xx*b.xz,
            xx*b.xw,

            yx*b.xx,
            yx*b.xy,
            yx*b.xz,
            yx*b.xw
        );
    }
    #endif
            
    template <typename T>
        template <typename U>
    constexpr Vector2<product_t<T,U>> Tensor21<T>::operator*(const Vector1<U>&b) const noexcept
    {
        return Vector2<product_t<T,U>>(
            xx*b.x,
            yx*b.x
        );
    }

    template <typename T>
        template <typename U>
    std::vector<Vector2<product_t<T,U>>>    Tensor21<T>::operator*(std::span<const Vector1<U>> bs) const
    {
        return transform(bs, [&](const Vector1<U>& b) -> Vector2<product_t<T,U>> {
            return *this * b;
        });
    }


    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    constexpr Tensor21<quotient_t<T,U>>  Tensor21<T>::operator/(U b) const noexcept
    {
        return Tensor21<quotient_t<T,U>>(
            xx/b,
            yx/b
        );
    }
    
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_div_v<T,U>) 
    Tensor21<T>&  Tensor21<T>::operator/=(U b) noexcept
    {
        xx/=b;
        yx/=b;        
        return *this;
    }    
    

    template <typename T>
    constexpr Tensor21<T> Tensor21<T>::all_add(T b) const noexcept
    {
        return Tensor21( 
            xx+b,
            yx+b
         );
    }

    template <typename T>
    Tensor21<T>&    Tensor21<T>::all_decrement(T b) noexcept
    {
        xx-=b;
        yx-=b;
        return *this;
    }

    template <typename T>
    Tensor21<T>&    Tensor21<T>::all_increment(T b) noexcept
    {
        xx+=b;
        yx+=b;
        return *this;
    }
    
    template <typename T>
    constexpr Tensor21<T> Tensor21<T>::all_subtract(T b) const noexcept
    {
        return Tensor21( 
            xx-b,
            yx-b
         );
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Tensor21<T>::all_test(Pred pred) const noexcept
    {
        return 
            pred(xx) && 
            pred(yx) 
        ;
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Tensor21<T>::all_test(const Tensor21& b, Pred pred) const noexcept
    {
        return 
            pred(xx, b.xx) && 
            pred(yx, b.yx) 
        ;
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Tensor21<T>::all_test(T b, Pred pred) const noexcept
    {
        return 
            pred(xx, b) && 
            pred(yx, b) 
        ;
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Tensor21<T>::any_test(Pred pred) const noexcept
    {
        return 
            pred(xx) || 
            pred(yx) 
        ;
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Tensor21<T>::any_test(const Tensor21& b, Pred pred) const noexcept
    {
        return 
            pred(xx, b.xx) || 
            pred(yx, b.yx) 
        ;
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Tensor21<T>::any_test(T b, Pred pred) const noexcept
    {
        return 
            pred(xx, b) || 
            pred(yx, b)
        ;
    }
     
    #ifdef YQ_MATH_TENSOR_1_2_HPP
    template <typename T>
    constexpr Tensor12<T> Tensor21<T>::transpose() const noexcept
    {
        return Tensor12<T>(
            xx, yx
        );
    }
    #endif

    template <typename T>
    constexpr Vector2<T>  Tensor21<T>::x_column() const noexcept
    {
        return Vector2<T>(xx, yx);
    }

    template <typename T>
    Tensor21<T>& Tensor21<T>::x_column(const Vector2<T>& v)
    {
        xx = v.x;
        yx = v.y;
        return *this;
    }

    template <typename T>
    Tensor21<T>& Tensor21<T>::x_column(T _xx, T _yx)
    {
        xx = _xx;
        yx = _yx;
        return *this;
    }

    template <typename T>
    constexpr Vector1<T>  Tensor21<T>::x_row() const noexcept
    {
        return Vector1<T>(xx);
    }

    template <typename T>
    Tensor21<T>& Tensor21<T>::x_row(const Vector1<T>& v)
    {
        xx = v.x;
        return *this;
    }

    template <typename T>
    Tensor21<T>& Tensor21<T>::x_row(T _xx)
    {
        xx = _xx;
        return *this;
    }

    template <typename T>
    constexpr Vector1<T>  Tensor21<T>::y_row() const noexcept
    {
        return Vector1<T>(yx);
    }

    template <typename T>
    Tensor21<T>& Tensor21<T>::y_row(const Vector1<T>& v)
    {
        yx = v.x;
        return *this;
    }

    template <typename T>
    Tensor21<T>& Tensor21<T>::y_row(T _yx)
    {
        yx = _yx;
        return *this;
    }
    
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Tensor21<product_t<T,U>>  operator*(T a, const Tensor21<U>& b)
    {
        return Tensor21<product_t<T,U>>(
            a*b.xx,
            a*b.yx
        );
    }

    template <typename T>
    AllComponents<Tensor21<T>>   all(Tensor21<T>& val)
    {
        return { val };
    }

    template <typename T>
    AllComponents<const Tensor21<T>>   all(const Tensor21<T>& val)
    {
        return { val };
    }
    
    template <typename T>
    AnyComponents<Tensor21<T>>   any(Tensor21<T>& val)
    {
        return { val };
    }

    template <typename T>
    AnyComponents<const Tensor21<T>>   any(const Tensor21<T>& val)
    {
        return { val };
    }
    
    #if 0
    template <typename T>
    ElemComponents<Tensor21<T>>   elem(Tensor21<T>& val)
    {
        return { val };
    }

    template <typename T>
    ElemComponents<const Tensor21<T>>   elem(const Tensor21<T>& val)
    {
        return { val };
    }
    #endif

    #ifdef YQ_MATH_TENSOR_1_2_HPP
    template <typename T>
    constexpr Tensor12<T>  transpose(const Tensor21<T>&v)
    {
        return v.transpose();
    }
    #endif


    template <typename T>
    constexpr Vector2<T>  x_column(const Tensor21<T>&ten) 
    {
        return ten.x_column();
    }

    template <typename T>
    constexpr Vector1<T>  x_row(const Tensor21<T>&ten)
    {
        return ten.x_row();
    }

    template <typename T>
    constexpr Vector1<T>  y_row(const Tensor21<T>&ten)
    {
        return ten.y_row();
    }


}
