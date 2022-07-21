////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__TENSOR_4_3__HPP 1
#include <math/preamble.hpp>
#include <math/Vector3.hpp>
#include <math/Vector4.hpp>

namespace yq {
    /*! \brief 4x3 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor43 {
        using component_type = T;
        T xx, xy, xz;
        T yx, yy, yz;
        T zx, zy, zz;
        T wx, wy, wz;

        constexpr bool operator==(const Tensor43&) const noexcept = default;
    };

    YQ_IEEE754_1(Tensor43)
        
//  --------------------------------------------------------
//  COMPOSITION

    template <typename T>
    constexpr Tensor43<T>  columns(const Vector4<T>&x, const Vector4<T>&y, const Vector4<T>&z)
    {
        return {
            x.x, y.x, z.x,
            x.y, y.y, z.y,
            x.z, y.z, z.z,
            x.w, y.w, z.w
        };
    }

    template <typename T>
    constexpr Tensor43<T>  rows(const Vector3<T>&x, const Vector3<T>&y, const Vector3<T>&z, const Vector3<T>&w)
    {
        return {
            x.x, x.y, x.z,
            y.x, y.y, y.z,
            z.x, z.y, z.z,
            w.x, w.y, w.z
        };
    }
    
    YQ_IDENTITY_1(Tensor43, {
        one_v<T>, zero_v<T>, zero_v<T>,
        zero_v<T>, one_v<T>, zero_v<T>,
        zero_v<T>, zero_v<T>, one_v<T>,
        zero_v<T>, zero_v<T>, zero_v<T>
    })

    YQ_NAN_1(Tensor43, {
        nan_v<T>, nan_v<T>, nan_v<T>,
        nan_v<T>, nan_v<T>, nan_v<T>,
        nan_v<T>, nan_v<T>, nan_v<T>,
        nan_v<T>, nan_v<T>, nan_v<T> 
    })
    
    YQ_ZERO_1(Tensor43, {
        zero_v<T>, zero_v<T>, zero_v<T>,
        zero_v<T>, zero_v<T>, zero_v<T>,
        zero_v<T>, zero_v<T>, zero_v<T>,
        zero_v<T>, zero_v<T>, zero_v<T> 
     })
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor43, 
        is_finite(v.xx) && is_finite(v.xy) && is_finite(v.xz) &&
        is_finite(v.yx) && is_finite(v.yy) && is_finite(v.yz) &&
        is_finite(v.zx) && is_finite(v.zy) && is_finite(v.zz) &&
        is_finite(v.wx) && is_finite(v.wy) && is_finite(v.wz)
    )
    
    YQ_IS_NAN_1(Tensor43,  
        is_nan(v.xx) || is_nan(v.xy) || is_nan(v.xz) ||
        is_nan(v.yx) || is_nan(v.yy) || is_nan(v.yz) ||
        is_nan(v.zx) || is_nan(v.zy) || is_nan(v.zz) ||
        is_nan(v.wx) || is_nan(v.wy) || is_nan(v.wz)
    )

//  --------------------------------------------------------
//  GETTERS

    template <typename T>
    constexpr Vector4<T>  x_column(const Tensor43<T>&v) 
    {
        return {v.xx, v.yx, v.zx, v.wx};
    }

    template <typename T>
    constexpr Vector4<T>  y_column(const Tensor43<T>&v) 
    {
        return {v.xy, v.yy, v.zy, v.wy};
    }

    template <typename T>
    constexpr Vector4<T>  z_column(const Tensor43<T>&v) 
    {
        return {v.xz, v.yz, v.zz, v.wz};
    }

    template <typename T>
    constexpr Vector3<T>  x_row(const Tensor43<T>&v)
    {
        return {v.xx, v.xy, v.xz};
    }

    template <typename T>
    constexpr Vector3<T>  y_row(const Tensor43<T>&v)
    {
        return {v.yx, v.yy, v.yz};
    }

    template <typename T>
    constexpr Vector3<T>  z_row(const Tensor43<T>&v)
    {
        return {v.zx, v.zy, v.zz};
    }

    template <typename T>
    constexpr Vector3<T>  w_row(const Tensor43<T>&v)
    {
        return {v.wx, v.wy, v.wz};
    }


//  --------------------------------------------------------
//  SETTERS

    template <typename T>
    Tensor43<T>& set_x_column(Tensor43<T>&ten, const Vector3<T>& v)
    {
        ten.xx = v.x;
        ten.yx = v.y;
        ten.zx = v.z;
        ten.wx = v.w;
        return ten;
    }

    template <typename T>
    Tensor43<T>& set_y_column(Tensor43<T>&ten, const Vector3<T>& v)
    {
        ten.xy = v.x;
        ten.yy = v.y;
        ten.zy = v.z;
        ten.wy = v.w;
        return ten;
    }

    template <typename T>
    Tensor43<T>& set_z_column(Tensor43<T>&ten, const Vector3<T>& v)
    {
        ten.xz = v.x;
        ten.yz = v.y;
        ten.zz = v.z;
        ten.wz = v.w;
        return ten;
    }

    template <typename T>
    Tensor43<T>& set_x_row(Tensor43<T>&ten, const Vector4<T>& v)
    {
        ten.xx = v.x;
        ten.xy = v.y;
        ten.xz = v.z;
        return ten;
    }

    template <typename T>
    Tensor43<T>& set_y_row(Tensor43<T>&ten, const Vector4<T>& v)
    {
        ten.yx = v.x;
        ten.yy = v.y;
        ten.yz = v.z;
        return ten;
    }

    template <typename T>
    Tensor43<T>& set_z_row(Tensor43<T>&ten, const Vector4<T>& v)
    {
        ten.zx = v.x;
        ten.zy = v.y;
        ten.zz = v.z;
        return ten;
    }

    template <typename T>
    Tensor43<T>& set_w_row(Tensor43<T>&ten, const Vector4<T>& v)
    {
        ten.wx = v.x;
        ten.wy = v.y;
        ten.wz = v.z;
        return ten;
    }

//  --------------------------------------------------------
//  POSITIVE

    template <typename T>
    constexpr Tensor43<T>  operator+(const Tensor43<T>& a) 
    { 
        return a; 
    }


//  --------------------------------------------------------
//  NEGATIVE

    template <typename T>
    constexpr Tensor43<T>  operator-(const Tensor43<T>& a) 
    {
        return {
            -a.xx, -a.xy, -a.xz,
            -a.yx, -a.yy, -a.yz,
            -a.zx, -a.zy, -a.zz,
            -a.wx, -a.wy, -a.wz
        };
    }


//  --------------------------------------------------------
//  ADDITION

    template <typename T>
    constexpr Tensor43<T>   operator+ (const Tensor43<T> &a, const Tensor43<T> &b) 
    {
        return {
            a.xx+b.xx, a.xy+b.xy, a.xz+b.xz,
            a.yx+b.yx, a.yy+b.yy, a.yz+b.yz,
            a.zx+b.zx, a.zy+b.zy, a.zz+b.zz,
            a.wx+b.wx, a.wy+b.wy, a.wz+b.wz
        };
    }

    template <typename T>
    Tensor43<T>&   operator+=(Tensor43<T> &a, const Tensor43<T> &b) 
    {
        a.xx+=b.xx;  a.xy+=b.xy;  a.xz+=b.xz;
        a.yx+=b.yx;  a.yy+=b.yy;  a.yz+=b.yz;
        a.zx+=b.zx;  a.zy+=b.zy;  a.zz+=b.zz;
        a.wx+=b.wx;  a.wy+=b.wy;  a.wz+=b.wz;
        return a;
    }


//  --------------------------------------------------------
//  SUBTRACTION

    template <typename T>
    constexpr Tensor43<T>   operator- (const Tensor43<T> &a, const Tensor43<T> &b) 
    {
        return {
            a.xx-b.xx, a.xy-b.xy, a.xz-b.xz,
            a.yx-b.yx, a.yy-b.yy, a.yz-b.yz,
            a.zx-b.zx, a.zy-b.zy, a.zz-b.zz,
            a.wx-b.wx, a.wy-b.wy, a.wz-b.wz
        };
    }
    

    template <typename T>
    Tensor43<T>&   operator-=(Tensor43<T> &a, const Tensor43<T> &b) 
    {
        a.xx-=b.xx;  a.xy-=b.xy;  a.xz-=b.xz;
        a.yx-=b.yx;  a.yy-=b.yy;  a.yz-=b.yz;
        a.zx-=b.zx;  a.zy-=b.zy;  a.zz-=b.zz;
        a.wx-=b.wx;  a.wy-=b.wy;  a.wz-=b.wz;
        return a;
    }
    
//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires std::is_arithmetic_v<T>
    constexpr Tensor43<product_t<T,U>>  operator*(T a, const Tensor43<T>& b)
    {
        return {
            a*b.xx, a*b.xy, a*b.xz,
            a*b.yx, a*b.yy, a*b.yz,
            a*b.zx, a*b.zy, a*b.zz,
            a*b.wx, a*b.wy, a*b.wz
        };
    }
    
    
    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor43<product_t<T,U>>  operator*(const Tensor43<T>& a, U b)
    {
        return {
            a.xx*b, a.xy*b, a.xz*b,
            a.yx*b, a.yy*b, a.yz*b,
            a.zx*b, a.zy*b, a.zz*b,
            a.wx*b, a.wy*b, a.wz*b
        };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Tensor43<product_t<T,U>>  operator*=(const Tensor43<T>& a, U b)
    {
        a.xx*=b; a.xy*=b; a.xz*=b;
        a.yx*=b; a.yy*=b; a.yz*=b;
        a.zx*=b; a.zy*=b; a.zz*=b;
        a.wx*=b; a.wy*=b; a.wz*=b;        
        return a;
    }

        
    template <typename T, typename U>
    constexpr Vector4<product_t<T,U>> operator*(const Tensor43<T>&a, const Vector3<U>&b)
    {
        return {
            a.xx*b.x + a.xy*b.y + a.xz*b.z,
            a.yx*b.x + a.yy*b.y + a.yz*b.z,
            a.zx*b.x + a.zy*b.y + a.zz*b.z,
            a.wx*b.x + a.wy*b.y + a.wz*b.z
        };
    }

    template <typename T, typename U>
    constexpr Vector3<product_t<T,U>> operator*(const Vector4<T>&a, const Tensor43<U>&b)
    {
        return {
            a.x*b.xx + a.y*b.yx + a.z*b.zx + a.w*b.wx,
            a.x*b.xy + a.y*b.yy + a.z*b.zy + a.w*b.wy,
            a.x*b.xz + a.y*b.yz + a.z*b.zz + a.w*b.wz
        };
    }

//  --------------------------------------------------------
//  DIVISION


    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor43<quotient_t<T,U>>  operator/(const Tensor43<T>& a, U b)
    {
        return {
            a.xx/b, a.xy/b, a.xz/b,
            a.yx/b, a.yy/b, a.yz/b,
            a.zx/b, a.zy/b, a.zz/b,
            a.wx/b, a.wy/b, a.wz/b
        };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Tensor43<quotient_t<T,U>>  operator/=(const Tensor43<T>& a, U b)
    {
        a.xx/=b; a.xy/=b; a.xz/=b;
        a.yx/=b; a.yy/=b; a.yz/=b;
        a.zx/=b; a.zy/=b; a.zz/=b;
        a.wx/=b; a.wy/=b; a.wz/=b;        
        return a;
    }

//  --------------------------------------------------------
//  OTIMES PRODUCT

    template <typename T, typename U>
    constexpr Tensor43<product_t<T,U>> operator OTIMES(const Vector4<T>&a, const Vector3<U>&b)
    {
        return {
            a.x+b.x, a.x+b.y, a.x+b.z,
            a.y+b.x, a.y+b.y, a.y+b.z,
            a.z+b.x, a.z+b.y, a.z+b.z,
            a.w+b.x, a.w+b.y, a.w+b.z
        };
    }

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

}

YQ_TYPE_DECLARE(yq::Tensor43D)
YQ_TYPE_DECLARE(yq::Tensor43F)
YQ_TYPE_DECLARE(yq::Tensor43I)
YQ_TYPE_DECLARE(yq::Tensor43U)

