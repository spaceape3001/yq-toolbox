////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the tensor11 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/


#include <yq-toolbox/vector/Tensor11.hpp>
#include <yq-toolbox/math/utility.hpp>

#include <yq-toolbox/math/AllComponents.hpp>
#include <yq-toolbox/math/AnyComponents.hpp>

namespace yq {
    #ifdef YQ_USE_GLM
    template <typename T>
        template <glm::qualifier Q>
    constexpr Tensor11<T>::Tensor11(const glm::mat<1,1,T,Q>& t) noexcept :
        xx(t.x.x)
    {
    }
    #endif

    #ifdef YQ_USE_GLM
    template <typename T>
    constexpr Tensor11<T>::operator glm::mat<1,1,T,glm::defaultp>() const noexcept 
    {
        return glm::mat<1,1,T,glm::defaultp>(
            xx
        );
    }
    #endif

    template <typename T>
    constexpr Tensor11<T>  Tensor11<T>::operator+() const noexcept
    { 
        return *this; 
    }

    template <typename T>
    constexpr Tensor11<T>  Tensor11<T>::operator-() const noexcept
    {
        return Tensor11(
            -xx
        );
    }

    template <typename T>
    constexpr Tensor11<T>   Tensor11<T>::operator+ (const Tensor11 &b) const noexcept
    {
        return Tensor11(
            xx+b.xx
        );
    }

    template <typename T>
    Tensor11<T>&   Tensor11<T>::operator+=(const Tensor11 &b) 
    {
        xx+=b.xx;
        return *this;
    }

    template <typename T>
    constexpr Tensor11<T>   Tensor11<T>::operator- (const Tensor11 &b) const noexcept
    {
        return Tensor11(
            xx-b.xx
        );
    }
    
    template <typename T>
    Tensor11<T>&   Tensor11<T>::operator-=(const Tensor11 &b) 
    {
        xx-=b.xx;
        return *this;
    }

    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    constexpr Tensor11<product_t<T,U>>  Tensor11<T>::operator*(U b) const noexcept
    {
        return Tensor11<product_t<T,U>>(
            xx*b
        );
    }
    
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
    Tensor11<product_t<T,U>>  Tensor11<T>::operator*=(U b) noexcept
    {
        xx*=b;        
        return *this;
    }

    #ifdef YQ_MATH_SEGMENT1_HPP
    template <typename T>
        template <typename U>
    constexpr Segment1<product_t<T,U>>  Tensor11<T>::operator*(const Segment1<U>&rhs) const noexcept
    {
        return Segment1<product_t<T,U>>( *this * rhs.a, *this * rhs.b );
    }
    #endif

    template <typename T>
        template <typename U>
    constexpr Tensor11<product_t<T,U>> Tensor11<T>::operator*(const Tensor11<U>& b) const noexcept
    {
        return Tensor11<product_t<T,U>>(
            xx*b.xx
        );
    }
    
    template <typename T>
        template <typename U>
    requires self_multiply_v<T,U>
    Tensor11<T>& Tensor11<T>::operator*=(const Tensor11<U>& b) const noexcept
    {
        *this = *this * b;
        return *this;
    }

    #ifdef YQ_MATH_TENSOR_1_2_HPP
    template <typename T>
        template <typename U>
    constexpr Tensor12<product_t<T,U>> Tensor11<T>::operator*(const Tensor12<U>& b) const noexcept
    {
        return Tensor12<product_t<T,U>>(
            xx*b.xx,
            xx*b.xy
        );
    }
    #endif
    
    #ifdef YQ_MATH_TENSOR_1_3_HPP
    template <typename T>
        template <typename U>
    constexpr Tensor13<product_t<T,U>> Tensor11<T>::operator*(const Tensor13<U>& b) const noexcept
    {
        return Tensor13<product_t<T,U>>(
            xx*b.xx,
            xx*b.xy,
            xx*b.xz
        );
    }
    #endif
    
    #ifdef YQ_MATH_TENSOR_1_4_HPP
    template <typename T>
        template <typename U>
    constexpr Tensor14<product_t<T,U>> Tensor11<T>::operator*(const Tensor14<U>& b) const noexcept
    {
        return Tensor14<product_t<T,U>>(
            xx*b.xx,
            xx*b.xy,
            xx*b.xz,
            xx*b.xw
        );
    }
    #endif
        
    template <typename T>
        template <typename U>
    constexpr Vector1<product_t<T,U>> Tensor11<T>::operator*(const Vector1<U>&b) const noexcept
    {
        return Vector1<product_t<T,U>>(
            xx*b.x
        );
    }

    template <typename T>
        template <typename U>
    std::vector<Vector1<product_t<T,U>>>    Tensor11<T>::operator*(std::span<const Vector1<U>> bs) const
    {
        return transform(bs, [&](const Vector1<U>& b) -> Vector1<product_t<T,U>> {
            return *this * b;
        });
    }


    template <typename T>
    constexpr Tensor11<T> Tensor11<T>::all_add(T b) const noexcept
    {
        return Tensor11( 
            xx+b
         );
    }

    template <typename T>
    Tensor11<T>&    Tensor11<T>::all_decrement(T b) noexcept
    {
        xx-=b;
        return *this;
    }

    template <typename T>
    Tensor11<T>&    Tensor11<T>::all_increment(T b) noexcept
    {
        xx+=b;
        return *this;
    }
    
    template <typename T>
    constexpr Tensor11<T> Tensor11<T>::all_subtract(T b) const noexcept
    {
        return Tensor11( 
            xx-b
         );
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Tensor11<T>::all_test(Pred pred) const noexcept
    {
        return 
            pred(xx) 
        ;
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Tensor11<T>::all_test(const Tensor11& b, Pred pred) const noexcept
    {
        return 
            pred(xx, b.xx) 
        ;
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Tensor11<T>::all_test(T b, Pred pred) const noexcept
    {
        return 
            pred(xx, b) 
        ;
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Tensor11<T>::any_test(Pred pred) const noexcept
    {
        return 
            pred(xx) 
        ;
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Tensor11<T>::any_test(const Tensor11& b, Pred pred) const noexcept
    {
        return 
            pred(xx, b.xx) 
        ;
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Tensor11<T>::any_test(T b, Pred pred) const noexcept
    {
        return 
            pred(xx, b)
        ;
    }

        //! Returns the determinant
    template <typename T>
    constexpr T Tensor11<T>::determinant() const noexcept
    {
        return xx;
    }

    //! Gets the diagonal as a vector
    template <typename T>
    constexpr Vector1<T>  Tensor11<T>::diagonal() const noexcept
    {
        return Vector1<T>(xx);
    }

    //! Sets the diagonal
    template <typename T>
    Tensor11<T>&   Tensor11<T>::diagonal(const Vector1<T>& v)
    {        
        xx = v.x;
        return *this;
    }

    template <typename T>
    Tensor11<T>&   Tensor11<T>::diagonal(T _xx)
    {        
        xx = _xx;
        return *this;
    }

        //! Returns the trace
    template <typename T>
    constexpr T     Tensor11<T>::trace() const noexcept
    {
        return xx;
    }

    //! Transpose, which is itself for a 1x1
    template <typename T>
    constexpr Tensor11<T> Tensor11<T>::transpose() const 
    { 
        return Tensor11( xx ); 
    }

    //! Gets the x-column as a vector
    template <typename T>
    constexpr Vector1<T>  Tensor11<T>::x_column()  const noexcept
    {
        return Vector1<T>(xx);
    }

    template <typename T>
    Tensor11<T>&   Tensor11<T>::x_column(const Vector1<T>& v)
    {
        xx = v.x;
        return *this;
    }

    //! Sets the x-column
    template <typename T>
    Tensor11<T>& Tensor11<T>::x_column(T _xx)
    {
        xx = _xx;
        return *this;
    }

    //! Gets the x-row as a vector
    template <typename T>
    constexpr Vector1<T>  Tensor11<T>::x_row() const noexcept
    {
        return Vector1<T>(xx);
    }

    //! Sets the x-row
    template <typename T>
    Tensor11<T>& Tensor11<T>::x_row(const Vector1<T>& v)
    {
        xx = v.x;
        return *this;
    }

    //! Sets the x-row
    template <typename T>
    Tensor11<T>& Tensor11<T>::x_row(T _xx)
    {
        xx = _xx;
        return *this;
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Tensor11<product_t<T,U>>  operator*(T a, const Tensor11<U>& b)
    {
        return Tensor11<product_t<T,U>>(
            a*b.xx
        );
    }
    
    template <typename T>
    AllComponents<Tensor11<T>>   all(Tensor11<T>& val)
    {
        return { val };
    }

    template <typename T>
    AllComponents<const Tensor11<T>>   all(const Tensor11<T>& val)
    {
        return { val };
    }
    
    template <typename T>
    AnyComponents<Tensor11<T>>   any(Tensor11<T>& val)
    {
        return { val };
    }

    template <typename T>
    AnyComponents<const Tensor11<T>>   any(const Tensor11<T>& val)
    {
        return { val };
    }
    
    template <typename T>
    constexpr Vector1<T>  diagonal(const Tensor11<T>& v)
    {
        return v.diagonal();
    }

    #if 0
    template <typename T>
    ElemComponents<Tensor11<T>>   elem(Tensor11<T>& val)
    {
        return { val };
    }

    template <typename T>
    ElemComponents<const Tensor11<T>>   elem(const Tensor11<T>& val)
    {
        return { val };
    }
    #endif
    
    template <typename T>
    constexpr Tensor11<T>  transpose(const Tensor11<T>&v)
    {
        return v.transpose();
    }


    template <typename T>
    constexpr Vector1<T>  x_column(const Tensor11<T>&v) 
    {
        return v.x_column();
    }

    template <typename T>
    constexpr Vector1<T>  x_row(const Tensor11<T>&v)
    {
        return v.x_row();
    }

}
