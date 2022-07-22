////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__TENSOR_3_4__HPP 1
#include <math/preamble.hpp>
#include <math/Vector3.hpp>
#include <math/Vector4.hpp>

namespace yq {
    /*! \brief 3x4 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor34 {
        using component_type = T;
        T xx, xy, xz, xw;
        T yx, yy, yz, yw;
        T zx, zy, zz, zw;

        constexpr bool operator==(const Tensor34&) const noexcept = default;
    };

    YQ_IEEE754_1(Tensor34)
        
//  --------------------------------------------------------
//  COMPOSITION

    template <typename T>
    constexpr Tensor34<T>  columns(const Vector3<T>&x, const Vector3<T>&y, const Vector3<T>&z, const Vector3<T>&w)
    {
        return {
            x.x, y.x, z.x, w.x,
            x.y, y.y, z.y, w.y,
            x.z, y.z, z.z, w.z
        };
    }

    template <typename T>
    constexpr Tensor34<T>  rows(const Vector4<T>&x, const Vector4<T>&y, const Vector4<T>&z)
    {
        return {
            x.x, x.y, x.z, x.w,
            y.x, y.y, y.z, y.w,
            z.x, z.y, z.z, z.w
        };
    }
    
    YQ_IDENTITY_1(Tensor34, {
        one_v<T>, zero_v<T>, zero_v<T>, zero_v<T>,
        zero_v<T>, one_v<T>, zero_v<T>, zero_v<T>,
        zero_v<T>, zero_v<T>, one_v<T>, zero_v<T>
    })

    YQ_NAN_1(Tensor34, {
        nan_v<T>, nan_v<T>, nan_v<T>, nan_v<T>,
        nan_v<T>, nan_v<T>, nan_v<T>, nan_v<T>,
        nan_v<T>, nan_v<T>, nan_v<T>, nan_v<T> 
    })
    
    YQ_ZERO_1(Tensor34, {
        zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>,
        zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>,
        zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T> 
     })
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor34, 
        is_finite(v.xx) && is_finite(v.xy) && is_finite(v.xz) && is_finite(v.xw) &&
        is_finite(v.yx) && is_finite(v.yy) && is_finite(v.yz) && is_finite(v.yw) &&
        is_finite(v.zx) && is_finite(v.zy) && is_finite(v.zz) && is_finite(v.zw)
    )
    
    YQ_IS_NAN_1(Tensor34,  
        is_nan(v.xx) || is_nan(v.xy) || is_nan(v.xz) || is_nan(v.xw) ||
        is_nan(v.yx) || is_nan(v.yy) || is_nan(v.yz) || is_nan(v.yw) ||
        is_nan(v.zx) || is_nan(v.zy) || is_nan(v.zz) || is_nan(v.zw)
    )

//  --------------------------------------------------------
//  GETTERS

    template <typename T>
    constexpr Vector3<T>  x_column(const Tensor34<T>&v) 
    {
        return {v.xx, v.yx, v.zx};
    }

    template <typename T>
    constexpr Vector3<T>  y_column(const Tensor34<T>&v) 
    {
        return {v.xy, v.yy, v.zy};
    }

    template <typename T>
    constexpr Vector3<T>  z_column(const Tensor34<T>&v) 
    {
        return {v.xz, v.yz, v.zz};
    }

    template <typename T>
    constexpr Vector3<T>  w_column(const Tensor34<T>&v) 
    {
        return {v.xw, v.yw, v.zw};
    }

    template <typename T>
    constexpr Vector4<T>  x_row(const Tensor34<T>&v)
    {
        return {v.xx, v.xy, v.xz, v.xw};
    }

    template <typename T>
    constexpr Vector4<T>  y_row(const Tensor34<T>&v)
    {
        return {v.yx, v.yy, v.yz, v.yw};
    }

    template <typename T>
    constexpr Vector4<T>  z_row(const Tensor34<T>&v)
    {
        return {v.zx, v.zy, v.zz, v.zw};
    }


//  --------------------------------------------------------
//  SETTERS

    template <typename T>
    Tensor34<T>& set_x_column(Tensor34<T>&ten, const Vector4<T>& v)
    {
        ten.xx = v.x;
        ten.yx = v.y;
        ten.zx = v.z;
        return ten;
    }

    template <typename T>
    Tensor34<T>& set_y_column(Tensor34<T>&ten, const Vector4<T>& v)
    {
        ten.xy = v.x;
        ten.yy = v.y;
        ten.zy = v.z;
        return ten;
    }

    template <typename T>
    Tensor34<T>& set_z_column(Tensor34<T>&ten, const Vector4<T>& v)
    {
        ten.xz = v.x;
        ten.yz = v.y;
        ten.zz = v.z;
        return ten;
    }

    template <typename T>
    Tensor34<T>& set_w_column(Tensor34<T>&ten, const Vector4<T>& v)
    {
        ten.xw = v.x;
        ten.yw = v.y;
        ten.zw = v.z;
        return ten;
    }

    template <typename T>
    Tensor34<T>& set_x_row(Tensor34<T>&ten, const Vector3<T>& v)
    {
        ten.xx = v.x;
        ten.xy = v.y;
        ten.xz = v.z;
        ten.xw = v.w;
        return ten;
    }

    template <typename T>
    Tensor34<T>& set_y_row(Tensor34<T>&ten, const Vector3<T>& v)
    {
        ten.yx = v.x;
        ten.yy = v.y;
        ten.yz = v.z;
        ten.yw = v.w;
        return ten;
    }

    template <typename T>
    Tensor34<T>& set_z_row(Tensor34<T>&ten, const Vector3<T>& v)
    {
        ten.zx = v.x;
        ten.zy = v.y;
        ten.zz = v.z;
        ten.zw = v.w;
        return ten;
    }

//  --------------------------------------------------------
//  POSITIVE

    template <typename T>
    constexpr Tensor34<T>  operator+(const Tensor34<T>& a) 
    { 
        return a; 
    }


//  --------------------------------------------------------
//  NEGATIVE

    template <typename T>
    constexpr Tensor34<T>  operator-(const Tensor34<T>& a) 
    {
        return {
            -a.xx, -a.xy, -a.xz, -a.xw,
            -a.yx, -a.yy, -a.yz, -a.yw,
            -a.zx, -a.zy, -a.zz, -a.zw
        };
    }


//  --------------------------------------------------------
//  ADDITION

    template <typename T>
    constexpr Tensor34<T>   operator+ (const Tensor34<T> &a, const Tensor34<T> &b) 
    {
        return {
            a.xx+b.xx, a.xy+b.xy, a.xz+b.xz, a.xw+b.xw,
            a.yx+b.yx, a.yy+b.yy, a.yz+b.yz, a.yw+b.yw,
            a.zx+b.zx, a.zy+b.zy, a.zz+b.zz, a.zw+b.zw
        };
    }

    template <typename T>
    Tensor34<T>&   operator+=(Tensor34<T> &a, const Tensor34<T> &b) 
    {
        a.xx+=b.xx;  a.xy+=b.xy;  a.xz+=b.xz;  a.xw+=b.xw;
        a.yx+=b.yx;  a.yy+=b.yy;  a.yz+=b.yz;  a.yw+=b.yw;
        a.zx+=b.zx;  a.zy+=b.zy;  a.zz+=b.zz;  a.zw+=b.zw;
        return a;
    }


//  --------------------------------------------------------
//  SUBTRACTION

    template <typename T>
    constexpr Tensor34<T>   operator- (const Tensor34<T> &a, const Tensor34<T> &b) 
    {
        return {
            a.xx-b.xx, a.xy-b.xy, a.xz-b.xz, a.xw-b.xw,
            a.yx-b.yx, a.yy-b.yy, a.yz-b.yz, a.yw-b.yw,
            a.zx-b.zx, a.zy-b.zy, a.zz-b.zz, a.zw-b.zw
        };
    }
    

    template <typename T>
    Tensor34<T>&   operator-=(Tensor34<T> &a, const Tensor34<T> &b) 
    {
        a.xx-=b.xx;  a.xy-=b.xy;  a.xz-=b.xz;  a.xw-=b.xw;
        a.yx-=b.yx;  a.yy-=b.yy;  a.yz-=b.yz;  a.yw-=b.yw;
        a.zx-=b.zx;  a.zy-=b.zy;  a.zz-=b.zz;  a.zw-=b.zw;
        return a;
    }
    
//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires std::is_arithmetic_v<T>
    constexpr Tensor34<product_t<T,U>>  operator*(T a, const Tensor34<T>& b)
    {
        return {
            a*b.xx, a*b.xy, a*b.xz, a*b.xw,
            a*b.yx, a*b.yy, a*b.yz, a*b.yw,
            a*b.zx, a*b.zy, a*b.zz, a*b.zw
        };
    }
    
    
    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor34<product_t<T,U>>  operator*(const Tensor34<T>& a, U b)
    {
        return {
            a.xx*b, a.xy*b, a.xz*b, a.xw*b,
            a.yx*b, a.yy*b, a.yz*b, a.yw*b,
            a.zx*b, a.zy*b, a.zz*b, a.zw*b
        };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Tensor34<product_t<T,U>>  operator*=(const Tensor34<T>& a, U b)
    {
        a.xx*=b; a.xy*=b; a.xz*=b; a.xw*=b;
        a.yx*=b; a.yy*=b; a.yz*=b; a.yw*=b;
        a.zx*=b; a.zy*=b; a.zz*=b; a.zw*=b;        
        return a;
    }

        
    template <typename T, typename U>
    constexpr Vector3<product_t<T,U>> operator*(const Tensor34<T>&a, const Vector4<U>&b)
    {
        return {
            a.xx*b.x + a.xy*b.y + a.xz*b.z + a.xw*b.w,
            a.yx*b.x + a.yy*b.y + a.yz*b.z + a.yw*b.w,
            a.zx*b.x + a.zy*b.y + a.zz*b.z + a.zw*b.w
        };
    }

    template <typename T, typename U>
    constexpr Vector4<product_t<T,U>> operator*(const Vector3<T>&a, const Tensor34<U>&b)
    {
        return {
            a.x*b.xx + a.y*b.yx + a.z*b.zx,
            a.x*b.xy + a.y*b.yy + a.z*b.zy,
            a.x*b.xz + a.y*b.yz + a.z*b.zz,
            a.x*b.xw + a.y*b.yw + a.z*b.zw
        };
    }

//  --------------------------------------------------------
//  DIVISION


    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor34<quotient_t<T,U>>  operator/(const Tensor34<T>& a, U b)
    {
        return {
            a.xx/b, a.xy/b, a.xz/b, a.xw/b,
            a.yx/b, a.yy/b, a.yz/b, a.yw/b,
            a.zx/b, a.zy/b, a.zz/b, a.zw/b
        };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Tensor34<quotient_t<T,U>>  operator/=(const Tensor34<T>& a, U b)
    {
        a.xx/=b; a.xy/=b; a.xz/=b; a.xw/=b;
        a.yx/=b; a.yy/=b; a.yz/=b; a.yw/=b;
        a.zx/=b; a.zy/=b; a.zz/=b; a.zw/=b;        
        return a;
    }

//  --------------------------------------------------------
//  OTIMES PRODUCT

    template <typename T, typename U>
    constexpr Tensor34<product_t<T,U>> operator OTIMES(const Vector3<T>&a, const Vector4<U>&b)
    {
        return {
            a.x+b.x, a.x+b.y, a.x+b.z, a.x+b.w,
            a.y+b.x, a.y+b.y, a.y+b.z, a.y+b.w,
            a.z+b.x, a.z+b.y, a.z+b.z, a.z+b.w
        };
    }

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

}

YQ_TYPE_DECLARE(yq::Tensor34D)
YQ_TYPE_DECLARE(yq::Tensor34F)
YQ_TYPE_DECLARE(yq::Tensor34I)
YQ_TYPE_DECLARE(yq::Tensor34U)

