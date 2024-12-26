////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the tensor41 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <yq/tensor/Tensor41.hpp>
#include <yq/math/utility.hpp>

#include <yq/math/AllComponents.hpp>
#include <yq/math/AnyComponents.hpp>

namespace yq {
    #ifdef YQ_USE_GLM
    template <typename T>
        template <glm::qualifier Q>
    constexpr Tensor41<T>::Tensor41(const glm::mat<4,1,T,Q>& t) noexcept :
        xx(t.x.x),
        yx(t.x.y),
        zx(t.x.z),
        wx(t.x.w)
    {
    }
    #endif

    #ifdef YQ_USE_GLM
    template <typename T>
    constexpr Tensor41<T>::operator glm::mat<4,1,T,glm::defaultp>() const noexcept 
    {
        return glm::mat<4,1,T,glm::defaultp>(
            xx, yx, zx, wx
        );
    }
    #endif

    template <typename T>
    constexpr Tensor41<T>  Tensor41<T>::operator+() const noexcept
    { 
        return *this; 
    }


    template <typename T>
    constexpr Tensor41<T>  Tensor41<T>::operator-() const noexcept
    {
        return Tensor41<T>(
            -xx,
            -yx,
            -zx,
            -wx
        );
    }


    template <typename T>
    constexpr Tensor41<T>   Tensor41<T>::operator+ (const Tensor41<T> &b) const noexcept
    {
        return Tensor41<T>(
            xx+b.xx,
            yx+b.yx,
            zx+b.zx,
            wx+b.wx
        );
    }

    template <typename T>
    Tensor41<T>&   Tensor41<T>::operator+=(const Tensor41<T> &b)  noexcept
    {
        xx+=b.xx;
        yx+=b.yx;
        zx+=b.zx;
        wx+=b.wx;
        return *this;
    }

    template <typename T>
    constexpr Tensor41<T>   Tensor41<T>::operator- (const Tensor41<T> &b)  const noexcept
    {
        return Tensor41<T>(
            xx-b.xx,
            yx-b.yx,
            zx-b.zx,
            wx-b.wx
        );
    }
    

    template <typename T>
    Tensor41<T>&   Tensor41<T>::operator-=(const Tensor41<T> &b) noexcept
    {
        xx-=b.xx;
        yx-=b.yx;
        zx-=b.zx;
        wx-=b.wx;
        return *this;
    }

    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    constexpr Tensor41<product_t<T,U>>  Tensor41<T>::operator*(U b) const noexcept
    {
        return Tensor41<product_t<T,U>>(
            xx*b,
            yx*b,
            zx*b,
            wx*b
        );
    }
    
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
    Tensor41<T>&  Tensor41<T>::operator*=(U b) noexcept
    {
        xx*=b;
        yx*=b;
        zx*=b;
        wx*=b;        
        return *this;
    }

    #if defined(YQ_MATH_SEGMENT1_HPP) && defined(YQ_MATH_SEGMENT4_HPP)
    template <typename T>
        template <typename U>
    constexpr Segment4<product_t<T,U>>  Tensor41<T>::operator*(const Segment1<U>&rhs) const noexcept
    {
        return Segment4<product_t<T,U>>( *this * rhs.a, *this * rhs.b );
    }
    #endif

    #ifdef YQ_MATH_TENSOR_1_1_HPP
    template <typename T>
        template <typename U>
    constexpr Tensor41<product_t<T,U>> Tensor41<T>::operator*(const Tensor11<U>& b) const noexcept
    {
        return Tensor41<product_t<T,U>>(
            xx*b.xx,

            yx*b.xx,

            zx*b.xx,

            wx*b.xx
        );
    }
    #endif
    
    #ifdef YQ_MATH_TENSOR_1_1_HPP
    template <typename T>
        template <typename U>
    requires self_multiply_v<T,U>
    Tensor41<T>& Tensor41<T>::operator*=(const Tensor11<U>& b) noexcept
    {
        *this = *this * b;
        return *this;
    }
    #endif

    #if defined(YQ_MATH_TENSOR_1_2_HPP) && defined(YQ_MATH_TENSOR_4_2_HPP)
    template <typename T>
        template <typename U>
    constexpr Tensor42<product_t<T,U>> Tensor41<T>::operator*(const Tensor12<U>& b) const noexcept
    {
        return Tensor42<product_t<T,U>>(
            xx*b.xx,
            xx*b.xy,

            yx*b.xx,
            yx*b.xy,

            zx*b.xx,
            zx*b.xy,

            wx*b.xx,
            wx*b.xy
        );
    }
    #endif
    
    #if defined(YQ_MATH_TENSOR_1_3_HPP) && defined(YQ_MATH_TENSOR_4_3_HPP)
    template <typename T>
        template <typename U>
    constexpr Tensor43<product_t<T,U>> Tensor41<T>::operator*(const Tensor13<U>& b) const noexcept
    {
        return Tensor43<product_t<T,U>>(
            xx*b.xx,
            xx*b.xy,
            xx*b.xz,

            yx*b.xx,
            yx*b.xy,
            yx*b.xz,

            zx*b.xx,
            zx*b.xy,
            zx*b.xz,

            wx*b.xx,
            wx*b.xy,
            wx*b.xz
        );
    }
    #endif
    
    #if defined(YQ_MATH_TENSOR_1_4_HPP) && defined(YQ_MATH_TENSOR_4_4_HPP)
    template <typename T>
        template <typename U>
    constexpr Tensor44<product_t<T,U>> Tensor41<T>::operator*(const Tensor14<U>& b) const noexcept
    {
        return Tensor44<product_t<T,U>>(
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
            zx*b.xw,

            wx*b.xx,
            wx*b.xy,
            wx*b.xz,
            wx*b.xw
        );
    }
    #endif
            
    template <typename T>
        template <typename U>
    constexpr Vector4<product_t<T,U>> Tensor41<T>::operator*(const Vector1<U>&b) const noexcept
    {
        return Vector4<product_t<T,U>>(
            xx*b.x,
            yx*b.x,
            zx*b.x,
            wx*b.x
        );
    }

    template <typename T>
        template <typename U>
    std::vector<Vector4<product_t<T,U>>>    Tensor41<T>::operator*(std::span<const Vector1<U>> bs) const
    {
        return transform(bs, [&](const Vector1<U>& b) -> Vector4<product_t<T,U>> {
            return *this * b;
        });
    }
    
    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    constexpr Tensor41<quotient_t<T,U>>  Tensor41<T>::operator/(U b) const noexcept
    {
        return Tensor41<quotient_t<T,U>>(
            xx/b,
            yx/b,
            zx/b,
            wx/b
        );
    }
    
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_divide_v<T,U>)
    Tensor41<T>&  Tensor41<T>::operator/=(U b) noexcept
    {
        xx/=b;
        yx/=b;
        zx/=b;
        wx/=b;        
        return *this;
    }


    template <typename T>
    constexpr Tensor41<T> Tensor41<T>::all_add(T b) const noexcept
    {
        return Tensor41( 
            xx+b,
            yx+b,
            zx+b,
            wx+b
         );
    }

    template <typename T>
    Tensor41<T>&    Tensor41<T>::all_decrement(T b) noexcept
    {
        xx-=b;
        yx-=b;
        zx-=b;
        wx-=b;
        return *this;
    }

    template <typename T>
    Tensor41<T>&    Tensor41<T>::all_increment(T b) noexcept
    {
        xx+=b;
        yx+=b;
        zx+=b;
        wx+=b;
        return *this;
    }
    
    template <typename T>
    constexpr Tensor41<T> Tensor41<T>::all_subtract(T b) const noexcept
    {
        return Tensor41( 
            xx-b,
            yx-b,
            zx-b,
            wx-b
         );
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Tensor41<T>::all_kest(Pred pred) const noexcept
    {
        return 
            pred(xx) && 
            pred(yx) && 
            pred(zx) && 
            pred(wx) 
        ;
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Tensor41<T>::all_kest(const Tensor41& b, Pred pred) const noexcept
    {
        return 
            pred(xx, b.xx) && 
            pred(yx, b.yx) && 
            pred(zx, b.zx) && 
            pred(wx, b.wx) 
        ;
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Tensor41<T>::all_kest(T b, Pred pred) const noexcept
    {
        return 
            pred(xx, b) && 
            pred(yx, b) && 
            pred(zx, b) && 
            pred(wx, b) 
        ;
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Tensor41<T>::any_kest(Pred pred) const noexcept
    {
        return 
            pred(xx) || 
            pred(yx) || 
            pred(zx) || 
            pred(wx) 
        ;
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Tensor41<T>::any_kest(const Tensor41& b, Pred pred) const noexcept
    {
        return 
            pred(xx, b.xx) || 
            pred(yx, b.yx) || 
            pred(zx, b.zx) || 
            pred(wx, b.wx) 
        ;
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Tensor41<T>::any_kest(T b, Pred pred) const noexcept
    {
        return 
            pred(xx, b) || 
            pred(yx, b) || 
            pred(zx, b) || 
            pred(wx, b)
        ;
    }

    #ifdef YQ_MATH_TENSOR_1_4_HPP
    template <typename T>
    constexpr Tensor14<T> Tensor41<T>::transpose() const noexcept
    {
        return Tensor14<T>(
            xx, yx, zx, wx
        );
    }
    #endif

    template <typename T>
    constexpr Vector1<T>  Tensor41<T>::w_row() const noexcept
    {
        return Vector1<T>(wx);
    }

    template <typename T>
    Tensor41<T>& Tensor41<T>::w_row(T _wx) noexcept
    {
        wx = _wx;
        return *this;
    }

    template <typename T>
    Tensor41<T>& Tensor41<T>::w_row(const Vector1<T>& v) noexcept
    {
        wx = v.x;
        return *this;
    }

    template <typename T>
    constexpr Vector4<T>  Tensor41<T>::x_column() const noexcept
    {
        return Vector4<T>(xx, yx, zx, wx);
    }

    template <typename T>
    Tensor41<T>& Tensor41<T>::x_column(const Vector4<T>& v) noexcept
    {
        xx = v.x;
        yx = v.y;
        zx = v.z;
        wx = v.w;
        return *this;
    }

    template <typename T>
    Tensor41<T>& Tensor41<T>::x_column(T _xx, T _yx, T _zx, T _wx) noexcept
    {
        xx = _xx;
        yx = _yx;
        zx = _zx;
        wx = _wx;
        return *this;
    }

    template <typename T>
    constexpr Vector1<T>  Tensor41<T>::x_row() const noexcept
    {
        return Vector4<T>(xx);
    }

    template <typename T>
    Tensor41<T>& Tensor41<T>::x_row(const Vector1<T>& v) noexcept
    {
        xx = v.x;
        return *this;
    }

    template <typename T>
    Tensor41<T>& Tensor41<T>::x_row(T _xx) noexcept
    {
        xx = _xx;
        return *this;
    }

    template <typename T>
    constexpr Vector1<T>  Tensor41<T>::y_row() const noexcept
    {
        return Vector4<T>(yx);
    }

    template <typename T>
    Tensor41<T>& Tensor41<T>::y_row(const Vector1<T>& v) noexcept
    {
        yx = v.x;
        return *this;
    }

    template <typename T>
    Tensor41<T>& Tensor41<T>::y_row(T _yx) noexcept
    {
        yx = _yx;
        return *this;
    }

    template <typename T>
    constexpr Vector1<T>  Tensor41<T>::z_row() const noexcept
    {
        return Vector4<T>(zx);
    }

    template <typename T>
    Tensor41<T>& Tensor41<T>::z_row(const Vector1<T>& v) noexcept
    {
        zx = v.x;
        return *this;
    }

    template <typename T>
    Tensor41<T>& Tensor41<T>::z_row(T _zx) noexcept
    {
        zx = _zx;
        return *this;
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            
    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Tensor41<product_t<T,U>>  operator*(T a, const Tensor41<T>& b) noexcept
    {
        return {
            a*b.xx,
            a*b.yx,
            a*b.zx,
            a*b.wx
        };
    }


    template <typename T>
    AllComponents<Tensor41<T>>   all(Tensor41<T>& val)
    {
        return { val };
    }

    template <typename T>
    AllComponents<const Tensor41<T>>   all(const Tensor41<T>& val)
    {
        return { val };
    }
    
    template <typename T>
    AnyComponents<Tensor41<T>>   any(Tensor41<T>& val)
    {
        return { val };
    }

    template <typename T>
    AnyComponents<const Tensor41<T>>   any(const Tensor41<T>& val)
    {
        return { val };
    }
    
    #if 0
    template <typename T>
    ElemComponents<Tensor41<T>>   elem(Tensor41<T>& val)
    {
        return { val };
    }

    template <typename T>
    ElemComponents<const Tensor41<T>>   elem(const Tensor41<T>& val)
    {
        return { val };
    }
    #endif

    #ifdef YQ_MATH_TENSOR_1_4_HPP
    template <typename T>
    constexpr Tensor14<T>  transpose(const Tensor41<T>&v)
    {
        return v.transpose();
    }
    #endif

}
