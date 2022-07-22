////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__TENSOR_3_2__HPP 1
#include <math/preamble.hpp>
#include <math/Vector2.hpp>
#include <math/Vector3.hpp>

namespace yq {
    /*! \brief 3x2 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor32 {
        using component_type = T;
        T xx, xy;
        T yx, yy;
        T zx, zy;

        constexpr bool operator==(const Tensor32&) const noexcept = default;
    };

    YQ_IEEE754_1(Tensor32)
        
//  --------------------------------------------------------
//  COMPOSITION

    template <typename T>
    constexpr Tensor32<T>  columns(const Vector3<T>&x, const Vector3<T>&y)
    {
        return {
            x.x, y.x,
            x.y, y.y,
            x.z, y.z
        };
    }

    template <typename T>
    constexpr Tensor32<T>  rows(const Vector2<T>&x, const Vector2<T>&y, const Vector2<T>&z)
    {
        return {
            x.x, x.y,
            y.x, y.y,
            z.x, z.y
        };
    }
    
    YQ_IDENTITY_1(Tensor32, {
        one_v<T>, zero_v<T>,
        zero_v<T>, one_v<T>,
        zero_v<T>, zero_v<T>
    })

    YQ_NAN_1(Tensor32, {
        nan_v<T>, nan_v<T>,
        nan_v<T>, nan_v<T>,
        nan_v<T>, nan_v<T> 
    })
    
    YQ_ZERO_1(Tensor32, {
        zero_v<T>, zero_v<T>,
        zero_v<T>, zero_v<T>,
        zero_v<T>, zero_v<T> 
     })
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor32, 
        is_finite(v.xx) && is_finite(v.xy) &&
        is_finite(v.yx) && is_finite(v.yy) &&
        is_finite(v.zx) && is_finite(v.zy)
    )
    
    YQ_IS_NAN_1(Tensor32,  
        is_nan(v.xx) || is_nan(v.xy) ||
        is_nan(v.yx) || is_nan(v.yy) ||
        is_nan(v.zx) || is_nan(v.zy)
    )

//  --------------------------------------------------------
//  GETTERS

    template <typename T>
    constexpr Vector3<T>  x_column(const Tensor32<T>&v) 
    {
        return {v.xx, v.yx, v.zx};
    }

    template <typename T>
    constexpr Vector3<T>  y_column(const Tensor32<T>&v) 
    {
        return {v.xy, v.yy, v.zy};
    }

    template <typename T>
    constexpr Vector2<T>  x_row(const Tensor32<T>&v)
    {
        return {v.xx, v.xy};
    }

    template <typename T>
    constexpr Vector2<T>  y_row(const Tensor32<T>&v)
    {
        return {v.yx, v.yy};
    }

    template <typename T>
    constexpr Vector2<T>  z_row(const Tensor32<T>&v)
    {
        return {v.zx, v.zy};
    }


//  --------------------------------------------------------
//  SETTERS

    template <typename T>
    Tensor32<T>& set_x_column(Tensor32<T>&ten, const Vector2<T>& v)
    {
        ten.xx = v.x;
        ten.yx = v.y;
        ten.zx = v.z;
        return ten;
    }

    template <typename T>
    Tensor32<T>& set_y_column(Tensor32<T>&ten, const Vector2<T>& v)
    {
        ten.xy = v.x;
        ten.yy = v.y;
        ten.zy = v.z;
        return ten;
    }

    template <typename T>
    Tensor32<T>& set_x_row(Tensor32<T>&ten, const Vector3<T>& v)
    {
        ten.xx = v.x;
        ten.xy = v.y;
        return ten;
    }

    template <typename T>
    Tensor32<T>& set_y_row(Tensor32<T>&ten, const Vector3<T>& v)
    {
        ten.yx = v.x;
        ten.yy = v.y;
        return ten;
    }

    template <typename T>
    Tensor32<T>& set_z_row(Tensor32<T>&ten, const Vector3<T>& v)
    {
        ten.zx = v.x;
        ten.zy = v.y;
        return ten;
    }

//  --------------------------------------------------------
//  POSITIVE

    template <typename T>
    constexpr Tensor32<T>  operator+(const Tensor32<T>& a) 
    { 
        return a; 
    }


//  --------------------------------------------------------
//  NEGATIVE

    template <typename T>
    constexpr Tensor32<T>  operator-(const Tensor32<T>& a) 
    {
        return {
            -a.xx, -a.xy,
            -a.yx, -a.yy,
            -a.zx, -a.zy
        };
    }


//  --------------------------------------------------------
//  ADDITION

    template <typename T>
    constexpr Tensor32<T>   operator+ (const Tensor32<T> &a, const Tensor32<T> &b) 
    {
        return {
            a.xx+b.xx, a.xy+b.xy,
            a.yx+b.yx, a.yy+b.yy,
            a.zx+b.zx, a.zy+b.zy
        };
    }

    template <typename T>
    Tensor32<T>&   operator+=(Tensor32<T> &a, const Tensor32<T> &b) 
    {
        a.xx+=b.xx;  a.xy+=b.xy;
        a.yx+=b.yx;  a.yy+=b.yy;
        a.zx+=b.zx;  a.zy+=b.zy;
        return a;
    }


//  --------------------------------------------------------
//  SUBTRACTION

    template <typename T>
    constexpr Tensor32<T>   operator- (const Tensor32<T> &a, const Tensor32<T> &b) 
    {
        return {
            a.xx-b.xx, a.xy-b.xy,
            a.yx-b.yx, a.yy-b.yy,
            a.zx-b.zx, a.zy-b.zy
        };
    }
    

    template <typename T>
    Tensor32<T>&   operator-=(Tensor32<T> &a, const Tensor32<T> &b) 
    {
        a.xx-=b.xx;  a.xy-=b.xy;
        a.yx-=b.yx;  a.yy-=b.yy;
        a.zx-=b.zx;  a.zy-=b.zy;
        return a;
    }
    
//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires std::is_arithmetic_v<T>
    constexpr Tensor32<product_t<T,U>>  operator*(T a, const Tensor32<T>& b)
    {
        return {
            a*b.xx, a*b.xy,
            a*b.yx, a*b.yy,
            a*b.zx, a*b.zy
        };
    }
    
    
    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor32<product_t<T,U>>  operator*(const Tensor32<T>& a, U b)
    {
        return {
            a.xx*b, a.xy*b,
            a.yx*b, a.yy*b,
            a.zx*b, a.zy*b
        };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Tensor32<product_t<T,U>>  operator*=(const Tensor32<T>& a, U b)
    {
        a.xx*=b; a.xy*=b;
        a.yx*=b; a.yy*=b;
        a.zx*=b; a.zy*=b;        
        return a;
    }

        
    template <typename T, typename U>
    constexpr Vector3<product_t<T,U>> operator*(const Tensor32<T>&a, const Vector2<U>&b)
    {
        return {
            a.xx*b.x + a.xy*b.y,
            a.yx*b.x + a.yy*b.y,
            a.zx*b.x + a.zy*b.y
        };
    }

    template <typename T, typename U>
    constexpr Vector2<product_t<T,U>> operator*(const Vector3<T>&a, const Tensor32<U>&b)
    {
        return {
            a.x*b.xx + a.y*b.yx + a.z*b.zx,
            a.x*b.xy + a.y*b.yy + a.z*b.zy
        };
    }

//  --------------------------------------------------------
//  DIVISION


    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor32<quotient_t<T,U>>  operator/(const Tensor32<T>& a, U b)
    {
        return {
            a.xx/b, a.xy/b,
            a.yx/b, a.yy/b,
            a.zx/b, a.zy/b
        };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Tensor32<quotient_t<T,U>>  operator/=(const Tensor32<T>& a, U b)
    {
        a.xx/=b; a.xy/=b;
        a.yx/=b; a.yy/=b;
        a.zx/=b; a.zy/=b;        
        return a;
    }

//  --------------------------------------------------------
//  OTIMES PRODUCT

    template <typename T, typename U>
    constexpr Tensor32<product_t<T,U>> operator OTIMES(const Vector3<T>&a, const Vector2<U>&b)
    {
        return {
            a.x+b.x, a.x+b.y,
            a.y+b.x, a.y+b.y,
            a.z+b.x, a.z+b.y
        };
    }

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

}

YQ_TYPE_DECLARE(yq::Tensor32D)
YQ_TYPE_DECLARE(yq::Tensor32F)
YQ_TYPE_DECLARE(yq::Tensor32I)
YQ_TYPE_DECLARE(yq::Tensor32U)

