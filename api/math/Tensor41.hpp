////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__TENSOR_4_1__HPP 1
#include <math/preamble.hpp>
#include <math/Vector1.hpp>
#include <math/Vector4.hpp>

namespace yq {
    /*! \brief 4x1 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor41 {
        using component_type = T;
        T xx;
        T yx;
        T zx;
        T wx;

        constexpr bool operator==(const Tensor41&) const noexcept = default;
    };

    YQ_IEEE754_1(Tensor41)
        
//  --------------------------------------------------------
//  COMPOSITION

    template <typename T>
    constexpr Tensor41<T>  columns(const Vector4<T>&x)
    {
        return {
            x.x,
            x.y,
            x.z,
            x.w
        };
    }

    template <typename T>
    constexpr Tensor41<T>  rows(const Vector1<T>&x, const Vector1<T>&y, const Vector1<T>&z, const Vector1<T>&w)
    {
        return {
            x.x,
            y.x,
            z.x,
            w.x
        };
    }
    
    YQ_IDENTITY_1(Tensor41, {
        one_v<T>,
        zero_v<T>,
        zero_v<T>,
        zero_v<T>
    })

    YQ_NAN_1(Tensor41, {
        nan_v<T>,
        nan_v<T>,
        nan_v<T>,
        nan_v<T> 
    })
    
    YQ_ZERO_1(Tensor41, {
        zero_v<T>,
        zero_v<T>,
        zero_v<T>,
        zero_v<T> 
     })
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor41, 
        is_finite(v.xx) &&
        is_finite(v.yx) &&
        is_finite(v.zx) &&
        is_finite(v.wx)
    )
    
    YQ_IS_NAN_1(Tensor41,  
        is_nan(v.xx) ||
        is_nan(v.yx) ||
        is_nan(v.zx) ||
        is_nan(v.wx)
    )

//  --------------------------------------------------------
//  GETTERS

    template <typename T>
    constexpr Vector4<T>  x_column(const Tensor41<T>&v) 
    {
        return {v.xx, v.yx, v.zx, v.wx};
    }

    template <typename T>
    constexpr Vector1<T>  x_row(const Tensor41<T>&v)
    {
        return {v.xx};
    }

    template <typename T>
    constexpr Vector1<T>  y_row(const Tensor41<T>&v)
    {
        return {v.yx};
    }

    template <typename T>
    constexpr Vector1<T>  z_row(const Tensor41<T>&v)
    {
        return {v.zx};
    }

    template <typename T>
    constexpr Vector1<T>  w_row(const Tensor41<T>&v)
    {
        return {v.wx};
    }


//  --------------------------------------------------------
//  SETTERS

    template <typename T>
    Tensor41<T>& set_x_column(Tensor41<T>&ten, const Vector1<T>& v)
    {
        ten.xx = v.x;
        ten.yx = v.y;
        ten.zx = v.z;
        ten.wx = v.w;
        return ten;
    }

    template <typename T>
    Tensor41<T>& set_x_row(Tensor41<T>&ten, const Vector4<T>& v)
    {
        ten.xx = v.x;
        return ten;
    }

    template <typename T>
    Tensor41<T>& set_y_row(Tensor41<T>&ten, const Vector4<T>& v)
    {
        ten.yx = v.x;
        return ten;
    }

    template <typename T>
    Tensor41<T>& set_z_row(Tensor41<T>&ten, const Vector4<T>& v)
    {
        ten.zx = v.x;
        return ten;
    }

    template <typename T>
    Tensor41<T>& set_w_row(Tensor41<T>&ten, const Vector4<T>& v)
    {
        ten.wx = v.x;
        return ten;
    }

//  --------------------------------------------------------
//  POSITIVE

    template <typename T>
    constexpr Tensor41<T>  operator+(const Tensor41<T>& a) 
    { 
        return a; 
    }


//  --------------------------------------------------------
//  NEGATIVE

    template <typename T>
    constexpr Tensor41<T>  operator-(const Tensor41<T>& a) 
    {
        return {
            -a.xx,
            -a.yx,
            -a.zx,
            -a.wx
        };
    }


//  --------------------------------------------------------
//  ADDITION

    template <typename T>
    constexpr Tensor41<T>   operator+ (const Tensor41<T> &a, const Tensor41<T> &b) 
    {
        return {
            a.xx+b.xx,
            a.yx+b.yx,
            a.zx+b.zx,
            a.wx+b.wx
        };
    }

    template <typename T>
    Tensor41<T>&   operator+=(Tensor41<T> &a, const Tensor41<T> &b) 
    {
        a.xx+=b.xx;
        a.yx+=b.yx;
        a.zx+=b.zx;
        a.wx+=b.wx;
        return a;
    }


//  --------------------------------------------------------
//  SUBTRACTION

    template <typename T>
    constexpr Tensor41<T>   operator- (const Tensor41<T> &a, const Tensor41<T> &b) 
    {
        return {
            a.xx-b.xx,
            a.yx-b.yx,
            a.zx-b.zx,
            a.wx-b.wx
        };
    }
    

    template <typename T>
    Tensor41<T>&   operator-=(Tensor41<T> &a, const Tensor41<T> &b) 
    {
        a.xx-=b.xx;
        a.yx-=b.yx;
        a.zx-=b.zx;
        a.wx-=b.wx;
        return a;
    }
    
//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires std::is_arithmetic_v<T>
    constexpr Tensor41<product_t<T,U>>  operator*(T a, const Tensor41<T>& b)
    {
        return {
            a*b.xx,
            a*b.yx,
            a*b.zx,
            a*b.wx
        };
    }
    
    
    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor41<product_t<T,U>>  operator*(const Tensor41<T>& a, U b)
    {
        return {
            a.xx*b,
            a.yx*b,
            a.zx*b,
            a.wx*b
        };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Tensor41<product_t<T,U>>  operator*=(const Tensor41<T>& a, U b)
    {
        a.xx*=b;
        a.yx*=b;
        a.zx*=b;
        a.wx*=b;        
        return a;
    }

        
    template <typename T, typename U>
    constexpr Vector4<product_t<T,U>> operator*(const Tensor41<T>&a, const Vector1<U>&b)
    {
        return {
            a.xx*b.x,
            a.yx*b.x,
            a.zx*b.x,
            a.wx*b.x
        };
    }

    template <typename T, typename U>
    constexpr Vector1<product_t<T,U>> operator*(const Vector4<T>&a, const Tensor41<U>&b)
    {
        return {
            a.x*b.xx + a.y*b.yx + a.z*b.zx + a.w*b.wx
        };
    }

//  --------------------------------------------------------
//  DIVISION


    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor41<quotient_t<T,U>>  operator/(const Tensor41<T>& a, U b)
    {
        return {
            a.xx/b,
            a.yx/b,
            a.zx/b,
            a.wx/b
        };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Tensor41<quotient_t<T,U>>  operator/=(const Tensor41<T>& a, U b)
    {
        a.xx/=b;
        a.yx/=b;
        a.zx/=b;
        a.wx/=b;        
        return a;
    }

//  --------------------------------------------------------
//  OTIMES PRODUCT

    template <typename T, typename U>
    constexpr Tensor41<product_t<T,U>> operator OTIMES(const Vector4<T>&a, const Vector1<U>&b)
    {
        return {
            a.x+b.x,
            a.y+b.x,
            a.z+b.x,
            a.w+b.x
        };
    }

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

}

YQ_TYPE_DECLARE(yq::Tensor41D)
YQ_TYPE_DECLARE(yq::Tensor41F)
YQ_TYPE_DECLARE(yq::Tensor41I)
YQ_TYPE_DECLARE(yq::Tensor41U)

