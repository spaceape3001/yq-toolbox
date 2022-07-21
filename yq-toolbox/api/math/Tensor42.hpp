////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__TENSOR_4_2__HPP 1
#include <math/preamble.hpp>
#include <math/Vector2.hpp>
#include <math/Vector4.hpp>

namespace yq {
    /*! \brief 4x2 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor42 {
        using component_type = T;
        T xx, xy;
        T yx, yy;
        T zx, zy;
        T wx, wy;

        constexpr bool operator==(const Tensor42&) const noexcept = default;
    };

    YQ_IEEE754_1(Tensor42)
        
//  --------------------------------------------------------
//  COMPOSITION

    template <typename T>
    constexpr Tensor42<T>  columns(const Vector4<T>&x, const Vector4<T>&y)
    {
        return {
            x.x, y.x,
            x.y, y.y,
            x.z, y.z,
            x.w, y.w
        };
    }

    template <typename T>
    constexpr Tensor42<T>  rows(const Vector2<T>&x, const Vector2<T>&y, const Vector2<T>&z, const Vector2<T>&w)
    {
        return {
            x.x, x.y,
            y.x, y.y,
            z.x, z.y,
            w.x, w.y
        };
    }
    
    YQ_IDENTITY_1(Tensor42, {
        one_v<T>, zero_v<T>,
        zero_v<T>, one_v<T>,
        zero_v<T>, zero_v<T>,
        zero_v<T>, zero_v<T>
    })

    YQ_NAN_1(Tensor42, {
        nan_v<T>, nan_v<T>,
        nan_v<T>, nan_v<T>,
        nan_v<T>, nan_v<T>,
        nan_v<T>, nan_v<T> 
    })
    
    YQ_ZERO_1(Tensor42, {
        zero_v<T>, zero_v<T>,
        zero_v<T>, zero_v<T>,
        zero_v<T>, zero_v<T>,
        zero_v<T>, zero_v<T> 
     })
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor42, 
        is_finite(v.xx) && is_finite(v.xy) &&
        is_finite(v.yx) && is_finite(v.yy) &&
        is_finite(v.zx) && is_finite(v.zy) &&
        is_finite(v.wx) && is_finite(v.wy)
    )
    
    YQ_IS_NAN_1(Tensor42,  
        is_nan(v.xx) || is_nan(v.xy) ||
        is_nan(v.yx) || is_nan(v.yy) ||
        is_nan(v.zx) || is_nan(v.zy) ||
        is_nan(v.wx) || is_nan(v.wy)
    )

//  --------------------------------------------------------
//  GETTERS

    template <typename T>
    constexpr Vector4<T>  x_column(const Tensor42<T>&v) 
    {
        return {v.xx, v.yx, v.zx, v.wx};
    }

    template <typename T>
    constexpr Vector4<T>  y_column(const Tensor42<T>&v) 
    {
        return {v.xy, v.yy, v.zy, v.wy};
    }

    template <typename T>
    constexpr Vector2<T>  x_row(const Tensor42<T>&v)
    {
        return {v.xx, v.xy};
    }

    template <typename T>
    constexpr Vector2<T>  y_row(const Tensor42<T>&v)
    {
        return {v.yx, v.yy};
    }

    template <typename T>
    constexpr Vector2<T>  z_row(const Tensor42<T>&v)
    {
        return {v.zx, v.zy};
    }

    template <typename T>
    constexpr Vector2<T>  w_row(const Tensor42<T>&v)
    {
        return {v.wx, v.wy};
    }


//  --------------------------------------------------------
//  SETTERS

    template <typename T>
    Tensor42<T>& set_x_column(Tensor42<T>&ten, const Vector2<T>& v)
    {
        ten.xx = v.x;
        ten.yx = v.y;
        ten.zx = v.z;
        ten.wx = v.w;
        return ten;
    }

    template <typename T>
    Tensor42<T>& set_y_column(Tensor42<T>&ten, const Vector2<T>& v)
    {
        ten.xy = v.x;
        ten.yy = v.y;
        ten.zy = v.z;
        ten.wy = v.w;
        return ten;
    }

    template <typename T>
    Tensor42<T>& set_x_row(Tensor42<T>&ten, const Vector4<T>& v)
    {
        ten.xx = v.x;
        ten.xy = v.y;
        return ten;
    }

    template <typename T>
    Tensor42<T>& set_y_row(Tensor42<T>&ten, const Vector4<T>& v)
    {
        ten.yx = v.x;
        ten.yy = v.y;
        return ten;
    }

    template <typename T>
    Tensor42<T>& set_z_row(Tensor42<T>&ten, const Vector4<T>& v)
    {
        ten.zx = v.x;
        ten.zy = v.y;
        return ten;
    }

    template <typename T>
    Tensor42<T>& set_w_row(Tensor42<T>&ten, const Vector4<T>& v)
    {
        ten.wx = v.x;
        ten.wy = v.y;
        return ten;
    }

//  --------------------------------------------------------
//  POSITIVE

    template <typename T>
    constexpr Tensor42<T>  operator+(const Tensor42<T>& a) 
    { 
        return a; 
    }


//  --------------------------------------------------------
//  NEGATIVE

    template <typename T>
    constexpr Tensor42<T>  operator-(const Tensor42<T>& a) 
    {
        return {
            -a.xx, -a.xy,
            -a.yx, -a.yy,
            -a.zx, -a.zy,
            -a.wx, -a.wy
        };
    }


//  --------------------------------------------------------
//  ADDITION

    template <typename T>
    constexpr Tensor42<T>   operator+ (const Tensor42<T> &a, const Tensor42<T> &b) 
    {
        return {
            a.xx+b.xx, a.xy+b.xy,
            a.yx+b.yx, a.yy+b.yy,
            a.zx+b.zx, a.zy+b.zy,
            a.wx+b.wx, a.wy+b.wy
        };
    }

    template <typename T>
    Tensor42<T>&   operator+=(Tensor42<T> &a, const Tensor42<T> &b) 
    {
        a.xx+=b.xx;  a.xy+=b.xy;
        a.yx+=b.yx;  a.yy+=b.yy;
        a.zx+=b.zx;  a.zy+=b.zy;
        a.wx+=b.wx;  a.wy+=b.wy;
        return a;
    }


//  --------------------------------------------------------
//  SUBTRACTION

    template <typename T>
    constexpr Tensor42<T>   operator- (const Tensor42<T> &a, const Tensor42<T> &b) 
    {
        return {
            a.xx-b.xx, a.xy-b.xy,
            a.yx-b.yx, a.yy-b.yy,
            a.zx-b.zx, a.zy-b.zy,
            a.wx-b.wx, a.wy-b.wy
        };
    }
    

    template <typename T>
    Tensor42<T>&   operator-=(Tensor42<T> &a, const Tensor42<T> &b) 
    {
        a.xx-=b.xx;  a.xy-=b.xy;
        a.yx-=b.yx;  a.yy-=b.yy;
        a.zx-=b.zx;  a.zy-=b.zy;
        a.wx-=b.wx;  a.wy-=b.wy;
        return a;
    }
    
//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires std::is_arithmetic_v<T>
    constexpr Tensor42<product_t<T,U>>  operator*(T a, const Tensor42<T>& b)
    {
        return {
            a*b.xx, a*b.xy,
            a*b.yx, a*b.yy,
            a*b.zx, a*b.zy,
            a*b.wx, a*b.wy
        };
    }
    
    
    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor42<product_t<T,U>>  operator*(const Tensor42<T>& a, U b)
    {
        return {
            a.xx*b, a.xy*b,
            a.yx*b, a.yy*b,
            a.zx*b, a.zy*b,
            a.wx*b, a.wy*b
        };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Tensor42<product_t<T,U>>  operator*=(const Tensor42<T>& a, U b)
    {
        a.xx*=b; a.xy*=b;
        a.yx*=b; a.yy*=b;
        a.zx*=b; a.zy*=b;
        a.wx*=b; a.wy*=b;        
        return a;
    }

        
    template <typename T, typename U>
    constexpr Vector4<product_t<T,U>> operator*(const Tensor42<T>&a, const Vector2<U>&b)
    {
        return {
            a.xx*b.x + a.xy*b.y,
            a.yx*b.x + a.yy*b.y,
            a.zx*b.x + a.zy*b.y,
            a.wx*b.x + a.wy*b.y
        };
    }

    template <typename T, typename U>
    constexpr Vector2<product_t<T,U>> operator*(const Vector4<T>&a, const Tensor42<U>&b)
    {
        return {
            a.x*b.xx + a.y*b.yx + a.z*b.zx + a.w*b.wx,
            a.x*b.xy + a.y*b.yy + a.z*b.zy + a.w*b.wy
        };
    }

//  --------------------------------------------------------
//  DIVISION


    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor42<quotient_t<T,U>>  operator/(const Tensor42<T>& a, U b)
    {
        return {
            a.xx/b, a.xy/b,
            a.yx/b, a.yy/b,
            a.zx/b, a.zy/b,
            a.wx/b, a.wy/b
        };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Tensor42<quotient_t<T,U>>  operator/=(const Tensor42<T>& a, U b)
    {
        a.xx/=b; a.xy/=b;
        a.yx/=b; a.yy/=b;
        a.zx/=b; a.zy/=b;
        a.wx/=b; a.wy/=b;        
        return a;
    }

//  --------------------------------------------------------
//  OTIMES PRODUCT

    template <typename T, typename U>
    constexpr Tensor42<product_t<T,U>> operator OTIMES(const Vector4<T>&a, const Vector2<U>&b)
    {
        return {
            a.x+b.x, a.x+b.y,
            a.y+b.x, a.y+b.y,
            a.z+b.x, a.z+b.y,
            a.w+b.x, a.w+b.y
        };
    }

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

}

YQ_TYPE_DECLARE(yq::Tensor42D)
YQ_TYPE_DECLARE(yq::Tensor42F)
YQ_TYPE_DECLARE(yq::Tensor42I)
YQ_TYPE_DECLARE(yq::Tensor42U)

