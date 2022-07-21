////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__TENSOR_2_4__HPP 1
#include <math/preamble.hpp>
#include <math/Vector2.hpp>
#include <math/Vector4.hpp>

namespace yq {
    /*! \brief 2x4 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor24 {
        using component_type = T;
        T xx, xy, xz, xw;
        T yx, yy, yz, yw;

        constexpr bool operator==(const Tensor24&) const noexcept = default;
    };

    YQ_IEEE754_1(Tensor24)
        
//  --------------------------------------------------------
//  COMPOSITION

    template <typename T>
    constexpr Tensor24<T>  columns(const Vector2<T>&x, const Vector2<T>&y, const Vector2<T>&z, const Vector2<T>&w)
    {
        return {
            x.x, y.x, z.x, w.x,
            x.y, y.y, z.y, w.y
        };
    }

    template <typename T>
    constexpr Tensor24<T>  rows(const Vector4<T>&x, const Vector4<T>&y)
    {
        return {
            x.x, x.y, x.z, x.w,
            y.x, y.y, y.z, y.w
        };
    }
    
    YQ_IDENTITY_1(Tensor24, {
        one_v<T>, zero_v<T>, zero_v<T>, zero_v<T>,
        zero_v<T>, one_v<T>, zero_v<T>, zero_v<T>
    })

    YQ_NAN_1(Tensor24, {
        nan_v<T>, nan_v<T>, nan_v<T>, nan_v<T>,
        nan_v<T>, nan_v<T>, nan_v<T>, nan_v<T> 
    })
    
    YQ_ZERO_1(Tensor24, {
        zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>,
        zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T> 
     })
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor24, 
        is_finite(v.xx) && is_finite(v.xy) && is_finite(v.xz) && is_finite(v.xw) &&
        is_finite(v.yx) && is_finite(v.yy) && is_finite(v.yz) && is_finite(v.yw)
    )
    
    YQ_IS_NAN_1(Tensor24,  
        is_nan(v.xx) || is_nan(v.xy) || is_nan(v.xz) || is_nan(v.xw) ||
        is_nan(v.yx) || is_nan(v.yy) || is_nan(v.yz) || is_nan(v.yw)
    )

//  --------------------------------------------------------
//  GETTERS

    template <typename T>
    constexpr Vector2<T>  x_column(const Tensor24<T>&v) 
    {
        return {v.xx, v.yx};
    }

    template <typename T>
    constexpr Vector2<T>  y_column(const Tensor24<T>&v) 
    {
        return {v.xy, v.yy};
    }

    template <typename T>
    constexpr Vector2<T>  z_column(const Tensor24<T>&v) 
    {
        return {v.xz, v.yz};
    }

    template <typename T>
    constexpr Vector2<T>  w_column(const Tensor24<T>&v) 
    {
        return {v.xw, v.yw};
    }

    template <typename T>
    constexpr Vector4<T>  x_row(const Tensor24<T>&v)
    {
        return {v.xx, v.xy, v.xz, v.xw};
    }

    template <typename T>
    constexpr Vector4<T>  y_row(const Tensor24<T>&v)
    {
        return {v.yx, v.yy, v.yz, v.yw};
    }


//  --------------------------------------------------------
//  SETTERS

    template <typename T>
    Tensor24<T>& set_x_column(Tensor24<T>&ten, const Vector4<T>& v)
    {
        ten.xx = v.x;
        ten.yx = v.y;
        return ten;
    }

    template <typename T>
    Tensor24<T>& set_y_column(Tensor24<T>&ten, const Vector4<T>& v)
    {
        ten.xy = v.x;
        ten.yy = v.y;
        return ten;
    }

    template <typename T>
    Tensor24<T>& set_z_column(Tensor24<T>&ten, const Vector4<T>& v)
    {
        ten.xz = v.x;
        ten.yz = v.y;
        return ten;
    }

    template <typename T>
    Tensor24<T>& set_w_column(Tensor24<T>&ten, const Vector4<T>& v)
    {
        ten.xw = v.x;
        ten.yw = v.y;
        return ten;
    }

    template <typename T>
    Tensor24<T>& set_x_row(Tensor24<T>&ten, const Vector2<T>& v)
    {
        ten.xx = v.x;
        ten.xy = v.y;
        ten.xz = v.z;
        ten.xw = v.w;
        return ten;
    }

    template <typename T>
    Tensor24<T>& set_y_row(Tensor24<T>&ten, const Vector2<T>& v)
    {
        ten.yx = v.x;
        ten.yy = v.y;
        ten.yz = v.z;
        ten.yw = v.w;
        return ten;
    }

//  --------------------------------------------------------
//  POSITIVE

    template <typename T>
    constexpr Tensor24<T>  operator+(const Tensor24<T>& a) 
    { 
        return a; 
    }


//  --------------------------------------------------------
//  NEGATIVE

    template <typename T>
    constexpr Tensor24<T>  operator-(const Tensor24<T>& a) 
    {
        return {
            -a.xx, -a.xy, -a.xz, -a.xw,
            -a.yx, -a.yy, -a.yz, -a.yw
        };
    }


//  --------------------------------------------------------
//  ADDITION

    template <typename T>
    constexpr Tensor24<T>   operator+ (const Tensor24<T> &a, const Tensor24<T> &b) 
    {
        return {
            a.xx+b.xx, a.xy+b.xy, a.xz+b.xz, a.xw+b.xw,
            a.yx+b.yx, a.yy+b.yy, a.yz+b.yz, a.yw+b.yw
        };
    }

    template <typename T>
    Tensor24<T>&   operator+=(Tensor24<T> &a, const Tensor24<T> &b) 
    {
        a.xx+=b.xx;  a.xy+=b.xy;  a.xz+=b.xz;  a.xw+=b.xw;
        a.yx+=b.yx;  a.yy+=b.yy;  a.yz+=b.yz;  a.yw+=b.yw;
        return a;
    }


//  --------------------------------------------------------
//  SUBTRACTION

    template <typename T>
    constexpr Tensor24<T>   operator- (const Tensor24<T> &a, const Tensor24<T> &b) 
    {
        return {
            a.xx-b.xx, a.xy-b.xy, a.xz-b.xz, a.xw-b.xw,
            a.yx-b.yx, a.yy-b.yy, a.yz-b.yz, a.yw-b.yw
        };
    }
    

    template <typename T>
    Tensor24<T>&   operator-=(Tensor24<T> &a, const Tensor24<T> &b) 
    {
        a.xx-=b.xx;  a.xy-=b.xy;  a.xz-=b.xz;  a.xw-=b.xw;
        a.yx-=b.yx;  a.yy-=b.yy;  a.yz-=b.yz;  a.yw-=b.yw;
        return a;
    }
    
//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires std::is_arithmetic_v<T>
    constexpr Tensor24<product_t<T,U>>  operator*(T a, const Tensor24<T>& b)
    {
        return {
            a*b.xx, a*b.xy, a*b.xz, a*b.xw,
            a*b.yx, a*b.yy, a*b.yz, a*b.yw
        };
    }
    
    
    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor24<product_t<T,U>>  operator*(const Tensor24<T>& a, U b)
    {
        return {
            a.xx*b, a.xy*b, a.xz*b, a.xw*b,
            a.yx*b, a.yy*b, a.yz*b, a.yw*b
        };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Tensor24<product_t<T,U>>  operator*=(const Tensor24<T>& a, U b)
    {
        a.xx*=b; a.xy*=b; a.xz*=b; a.xw*=b;
        a.yx*=b; a.yy*=b; a.yz*=b; a.yw*=b;        
        return a;
    }

        
    template <typename T, typename U>
    constexpr Vector2<product_t<T,U>> operator*(const Tensor24<T>&a, const Vector4<U>&b)
    {
        return {
            a.xx*b.x + a.xy*b.y + a.xz*b.z + a.xw*b.w,
            a.yx*b.x + a.yy*b.y + a.yz*b.z + a.yw*b.w
        };
    }

    template <typename T, typename U>
    constexpr Vector4<product_t<T,U>> operator*(const Vector2<T>&a, const Tensor24<U>&b)
    {
        return {
            a.x*b.xx + a.y*b.yx,
            a.x*b.xy + a.y*b.yy,
            a.x*b.xz + a.y*b.yz,
            a.x*b.xw + a.y*b.yw
        };
    }

//  --------------------------------------------------------
//  DIVISION


    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor24<quotient_t<T,U>>  operator/(const Tensor24<T>& a, U b)
    {
        return {
            a.xx/b, a.xy/b, a.xz/b, a.xw/b,
            a.yx/b, a.yy/b, a.yz/b, a.yw/b
        };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Tensor24<quotient_t<T,U>>  operator/=(const Tensor24<T>& a, U b)
    {
        a.xx/=b; a.xy/=b; a.xz/=b; a.xw/=b;
        a.yx/=b; a.yy/=b; a.yz/=b; a.yw/=b;        
        return a;
    }

//  --------------------------------------------------------
//  OTIMES PRODUCT

    template <typename T, typename U>
    constexpr Tensor24<product_t<T,U>> operator OTIMES(const Vector2<T>&a, const Vector4<U>&b)
    {
        return {
            a.x+b.x, a.x+b.y, a.x+b.z, a.x+b.w,
            a.y+b.x, a.y+b.y, a.y+b.z, a.y+b.w
        };
    }

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

}

YQ_TYPE_DECLARE(yq::Tensor24D)
YQ_TYPE_DECLARE(yq::Tensor24F)
YQ_TYPE_DECLARE(yq::Tensor24I)
YQ_TYPE_DECLARE(yq::Tensor24U)

