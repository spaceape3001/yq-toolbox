////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__TENSOR_1_2__HPP 1
#include <math/preamble.hpp>
#include <math/Vector1.hpp>
#include <math/Vector2.hpp>

namespace yq {

    /*! \brief 1x2 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor12 {
        using component_type = T;
        T xx, xy;

        constexpr bool operator==(const Tensor12&) const noexcept = default;
    };

    YQ_IEEE754_1(Tensor12)
        
//  --------------------------------------------------------
//  COMPOSITION

    template <typename T>
    constexpr Tensor12<T>  columns(const Vector1<T>&x, const Vector1<T>&y)
    {
        return {
            x.x, y.x
        };
    }

    template <typename T>
    constexpr Tensor12<T>  rows(const Vector2<T>&x)
    {
        return {
            x.x, x.y
        };
    }
    
    YQ_IDENTITY_1(Tensor12, {
        one_v<T>, zero_v<T>
    })

    YQ_NAN_1(Tensor12, {
        nan_v<T>, nan_v<T> 
    })
    
    YQ_ZERO_1(Tensor12, {
        zero_v<T>, zero_v<T> 
     })
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor12, 
        is_finite(v.xx) && is_finite(v.xy)
    )
    
    YQ_IS_NAN_1(Tensor12,  
        is_nan(v.xx) || is_nan(v.xy)
    )

//  --------------------------------------------------------
//  GETTERS

    template <typename T>
    constexpr Vector1<T>  x_column(const Tensor12<T>&v) 
    {
        return {v.xx};
    }

    template <typename T>
    constexpr Vector1<T>  y_column(const Tensor12<T>&v) 
    {
        return {v.xy};
    }

    template <typename T>
    constexpr Vector2<T>  x_row(const Tensor12<T>&v)
    {
        return {v.xx, v.xy};
    }


//  --------------------------------------------------------
//  SETTERS

    template <typename T>
    Tensor12<T>& set_x_column(Tensor12<T>&ten, const Vector2<T>& v)
    {
        ten.xx = v.x;
        return ten;
    }

    template <typename T>
    Tensor12<T>& set_y_column(Tensor12<T>&ten, const Vector2<T>& v)
    {
        ten.xy = v.x;
        return ten;
    }

    template <typename T>
    Tensor12<T>& set_x_row(Tensor12<T>&ten, const Vector1<T>& v)
    {
        ten.xx = v.x;
        ten.xy = v.y;
        return ten;
    }

//  --------------------------------------------------------
//  POSITIVE

    template <typename T>
    constexpr Tensor12<T>  operator+(const Tensor12<T>& a) 
    { 
        return a; 
    }


//  --------------------------------------------------------
//  NEGATIVE

    template <typename T>
    constexpr Tensor12<T>  operator-(const Tensor12<T>& a) 
    {
        return {
            -a.xx, -a.xy
        };
    }


//  --------------------------------------------------------
//  ADDITION

    template <typename T>
    constexpr Tensor12<T>   operator+ (const Tensor12<T> &a, const Tensor12<T> &b) 
    {
        return {
            a.xx+b.xx, a.xy+b.xy
        };
    }

    template <typename T>
    Tensor12<T>&   operator+=(Tensor12<T> &a, const Tensor12<T> &b) 
    {
        a.xx+=b.xx;  a.xy+=b.xy;
        return a;
    }


//  --------------------------------------------------------
//  SUBTRACTION

    template <typename T>
    constexpr Tensor12<T>   operator- (const Tensor12<T> &a, const Tensor12<T> &b) 
    {
        return {
            a.xx-b.xx, a.xy-b.xy
        };
    }
    

    template <typename T>
    Tensor12<T>&   operator-=(Tensor12<T> &a, const Tensor12<T> &b) 
    {
        a.xx-=b.xx;  a.xy-=b.xy;
        return a;
    }
    
//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires std::is_arithmetic_v<T>
    constexpr Tensor12<product_t<T,U>>  operator*(T a, const Tensor12<T>& b)
    {
        return {
            a*b.xx, a*b.xy
        };
    }
    
    
    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor12<product_t<T,U>>  operator*(const Tensor12<T>& a, U b)
    {
        return {
            a.xx*b, a.xy*b
        };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Tensor12<product_t<T,U>>  operator*=(const Tensor12<T>& a, U b)
    {
        a.xx*=b; a.xy*=b;        
        return a;
    }

        
    template <typename T, typename U>
    constexpr Vector1<product_t<T,U>> operator*(const Tensor12<T>&a, const Vector2<U>&b)
    {
        return {
            a.xx*b.x + a.xy*b.y
        };
    }

    template <typename T, typename U>
    constexpr Vector2<product_t<T,U>> operator*(const Vector1<T>&a, const Tensor12<U>&b)
    {
        return {
            a.x*b.xx,
            a.x*b.xy
        };
    }

//  --------------------------------------------------------
//  DIVISION


    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor12<quotient_t<T,U>>  operator/(const Tensor12<T>& a, U b)
    {
        return {
            a.xx/b, a.xy/b
        };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Tensor12<quotient_t<T,U>>  operator/=(const Tensor12<T>& a, U b)
    {
        a.xx/=b; a.xy/=b;        
        return a;
    }

//  --------------------------------------------------------
//  OTIMES PRODUCT

    template <typename T, typename U>
    constexpr Tensor12<product_t<T,U>> operator OTIMES(const Vector1<T>&a, const Vector2<U>&b)
    {
        return {
            a.x+b.x, a.x+b.y
        };
    }

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

}

YQ_TYPE_DECLARE(yq::Tensor12D)
YQ_TYPE_DECLARE(yq::Tensor12F)
YQ_TYPE_DECLARE(yq::Tensor12I)
YQ_TYPE_DECLARE(yq::Tensor12U)

