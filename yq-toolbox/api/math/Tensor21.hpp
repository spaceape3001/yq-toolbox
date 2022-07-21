////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__TENSOR_2_1__HPP 1
#include <math/preamble.hpp>
#include <math/Vector1.hpp>
#include <math/Vector2.hpp>

namespace yq {
    /*! \brief 2x1 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor21 {
        using component_type = T;
        T xx;
        T yx;

        constexpr bool operator==(const Tensor21&) const noexcept = default;
    };

    YQ_IEEE754_1(Tensor21)
        
//  --------------------------------------------------------
//  COMPOSITION

    template <typename T>
    constexpr Tensor21<T>  columns(const Vector2<T>&x)
    {
        return {
            x.x,
            x.y
        };
    }

    template <typename T>
    constexpr Tensor21<T>  rows(const Vector1<T>&x, const Vector1<T>&y)
    {
        return {
            x.x,
            y.x
        };
    }
    
    YQ_IDENTITY_1(Tensor21, {
        one_v<T>,
        zero_v<T>
    })

    YQ_NAN_1(Tensor21, {
        nan_v<T>,
        nan_v<T> 
    })
    
    YQ_ZERO_1(Tensor21, {
        zero_v<T>,
        zero_v<T> 
     })
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor21, 
        is_finite(v.xx) &&
        is_finite(v.yx)
    )
    
    YQ_IS_NAN_1(Tensor21,  
        is_nan(v.xx) ||
        is_nan(v.yx)
    )

//  --------------------------------------------------------
//  GETTERS

    template <typename T>
    constexpr Vector2<T>  x_column(const Tensor21<T>&v) 
    {
        return {v.xx, v.yx};
    }

    template <typename T>
    constexpr Vector1<T>  x_row(const Tensor21<T>&v)
    {
        return {v.xx};
    }

    template <typename T>
    constexpr Vector1<T>  y_row(const Tensor21<T>&v)
    {
        return {v.yx};
    }


//  --------------------------------------------------------
//  SETTERS

    template <typename T>
    Tensor21<T>& set_x_column(Tensor21<T>&ten, const Vector1<T>& v)
    {
        ten.xx = v.x;
        ten.yx = v.y;
        return ten;
    }

    template <typename T>
    Tensor21<T>& set_x_row(Tensor21<T>&ten, const Vector2<T>& v)
    {
        ten.xx = v.x;
        return ten;
    }

    template <typename T>
    Tensor21<T>& set_y_row(Tensor21<T>&ten, const Vector2<T>& v)
    {
        ten.yx = v.x;
        return ten;
    }

//  --------------------------------------------------------
//  POSITIVE

    template <typename T>
    constexpr Tensor21<T>  operator+(const Tensor21<T>& a) 
    { 
        return a; 
    }


//  --------------------------------------------------------
//  NEGATIVE

    template <typename T>
    constexpr Tensor21<T>  operator-(const Tensor21<T>& a) 
    {
        return {
            -a.xx,
            -a.yx
        };
    }


//  --------------------------------------------------------
//  ADDITION

    template <typename T>
    constexpr Tensor21<T>   operator+ (const Tensor21<T> &a, const Tensor21<T> &b) 
    {
        return {
            a.xx+b.xx,
            a.yx+b.yx
        };
    }

    template <typename T>
    Tensor21<T>&   operator+=(Tensor21<T> &a, const Tensor21<T> &b) 
    {
        a.xx+=b.xx;
        a.yx+=b.yx;
        return a;
    }


//  --------------------------------------------------------
//  SUBTRACTION

    template <typename T>
    constexpr Tensor21<T>   operator- (const Tensor21<T> &a, const Tensor21<T> &b) 
    {
        return {
            a.xx-b.xx,
            a.yx-b.yx
        };
    }
    

    template <typename T>
    Tensor21<T>&   operator-=(Tensor21<T> &a, const Tensor21<T> &b) 
    {
        a.xx-=b.xx;
        a.yx-=b.yx;
        return a;
    }
    
//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires std::is_arithmetic_v<T>
    constexpr Tensor21<product_t<T,U>>  operator*(T a, const Tensor21<T>& b)
    {
        return {
            a*b.xx,
            a*b.yx
        };
    }
    
    
    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor21<product_t<T,U>>  operator*(const Tensor21<T>& a, U b)
    {
        return {
            a.xx*b,
            a.yx*b
        };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Tensor21<product_t<T,U>>  operator*=(const Tensor21<T>& a, U b)
    {
        a.xx*=b;
        a.yx*=b;        
        return a;
    }

        
    template <typename T, typename U>
    constexpr Vector2<product_t<T,U>> operator*(const Tensor21<T>&a, const Vector1<U>&b)
    {
        return {
            a.xx*b.x,
            a.yx*b.x
        };
    }

    template <typename T, typename U>
    constexpr Vector1<product_t<T,U>> operator*(const Vector2<T>&a, const Tensor21<U>&b)
    {
        return {
            a.x*b.xx + a.y*b.yx
        };
    }

//  --------------------------------------------------------
//  DIVISION


    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor21<quotient_t<T,U>>  operator/(const Tensor21<T>& a, U b)
    {
        return {
            a.xx/b,
            a.yx/b
        };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Tensor21<quotient_t<T,U>>  operator/=(const Tensor21<T>& a, U b)
    {
        a.xx/=b;
        a.yx/=b;        
        return a;
    }

//  --------------------------------------------------------
//  OTIMES PRODUCT

    template <typename T, typename U>
    constexpr Tensor21<product_t<T,U>> operator OTIMES(const Vector2<T>&a, const Vector1<U>&b)
    {
        return {
            a.x+b.x,
            a.y+b.x
        };
    }

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

}

YQ_TYPE_DECLARE(yq::Tensor21D)
YQ_TYPE_DECLARE(yq::Tensor21F)
YQ_TYPE_DECLARE(yq::Tensor21I)
YQ_TYPE_DECLARE(yq::Tensor21U)

