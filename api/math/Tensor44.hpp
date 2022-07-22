////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__TENSOR_4_4__HPP 1
#include <math/preamble.hpp>
#include <math/Vector4.hpp>

namespace yq {
    /*! \brief 4x4 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor44 {
        using component_type = T;
        T xx, xy, xz, xw;
        T yx, yy, yz, yw;
        T zx, zy, zz, zw;
        T wx, wy, wz, ww;

        constexpr bool operator==(const Tensor44&) const noexcept = default;
        
        operator glm::mat<4,4,T,glm::defaultp>() const noexcept 
        {
            return {
                xx, yx, zx, wx,
                xy, yy, zy, wy,
                xz, yz, zz, wz,
                xw, yw, zw, ww
            };
        }
    };
        
    YQ_IEEE754_1(Tensor44)

//  --------------------------------------------------------
//  COMPOSITION

    template <typename T>
    constexpr Tensor44<T>  columns(const Vector4<T>&x, const Vector4<T>&y, const Vector4<T>&z, const Vector4<T>&w)
    {
        return {
            x.x, y.x, z.x, w.x,
            x.y, y.y, z.y, w.y,
            x.z, y.z, z.z, w.z,
            x.w, y.w, z.w, w.w
        };
    }

    template <typename T>
    constexpr Tensor44<T>  diagonal(const Vector4<T>&v)
    {
        return {
            v.x, zero_v<T>, zero_v<T>, zero_v<T>,
            zero_v<T>, v.y, zero_v<T>, zero_v<T>,
            zero_v<T>, zero_v<T>, v.z, zero_v<T>,
            zero_v<T>, zero_v<T>, zero_v<T>, v.w
        };
    }
    
    template <typename T>
    constexpr Tensor44<T>  diagonal(T x, std::type_identity_t<T> y, std::type_identity_t<T> z, std::type_identity_t<T> w)
    {
        return {
            x, zero_v<T>, zero_v<T>, zero_v<T>,
            zero_v<T>, y, zero_v<T>, zero_v<T>,
            zero_v<T>, zero_v<T>, z, zero_v<T>,
            zero_v<T>, zero_v<T>, zero_v<T>, w
        };
    }

    template <typename T>
    constexpr Tensor44<T>  rows(const Vector4<T>&x, const Vector4<T>&y, const Vector4<T>&z, const Vector4<T>&w)
    {
        return {
            x.x, x.y, x.z, x.w,
            y.x, y.y, y.z, y.w,
            z.x, z.y, z.z, z.w,
            w.x, w.y, w.z, w.w
        };
    }

    template <typename T, glm::qualifier Q>
    constexpr Tensor44<T> tensor(const glm::mat<4,4,T,Q>& t)
    {
        return {
            t.x.x, t.y.x, t.z.x, t.w.x,
            t.x.y, t.y.y, t.z.y, t.w.y,
            t.x.z, t.y.z, t.z.z, t.w.z,
            t.x.w, t.y.w, t.z.w, t.w.w
        };
    }
    
    YQ_IDENTITY_1(Tensor44, {
        one_v<T>, zero_v<T>, zero_v<T>, zero_v<T>,
        zero_v<T>, one_v<T>, zero_v<T>, zero_v<T>,
        zero_v<T>, zero_v<T>, one_v<T>, zero_v<T>,
        zero_v<T>, zero_v<T>, zero_v<T>, one_v<T>
    })

    YQ_NAN_1(Tensor44, {
        nan_v<T>, nan_v<T>, nan_v<T>, nan_v<T>,
        nan_v<T>, nan_v<T>, nan_v<T>, nan_v<T>,
        nan_v<T>, nan_v<T>, nan_v<T>, nan_v<T>,
        nan_v<T>, nan_v<T>, nan_v<T>, nan_v<T> 
    })
    
    YQ_ZERO_1(Tensor44, {
        zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>,
        zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>,
        zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>,
        zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T> 
     })
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor44, 
        is_finite(v.xx) && is_finite(v.xy) && is_finite(v.xz) && is_finite(v.xw) &&
        is_finite(v.yx) && is_finite(v.yy) && is_finite(v.yz) && is_finite(v.yw) &&
        is_finite(v.zx) && is_finite(v.zy) && is_finite(v.zz) && is_finite(v.zw) &&
        is_finite(v.wx) && is_finite(v.wy) && is_finite(v.wz) && is_finite(v.ww)
    )
    
    YQ_IS_NAN_1(Tensor44,  
        is_nan(v.xx) || is_nan(v.xy) || is_nan(v.xz) || is_nan(v.xw) ||
        is_nan(v.yx) || is_nan(v.yy) || is_nan(v.yz) || is_nan(v.yw) ||
        is_nan(v.zx) || is_nan(v.zy) || is_nan(v.zz) || is_nan(v.zw) ||
        is_nan(v.wx) || is_nan(v.wy) || is_nan(v.wz) || is_nan(v.ww)
    )

    template <typename T>
    constexpr Tensor44<T>  transpose(const Tensor44<T>&v)
    {
        return {
            v.xx, v.yx, v.zx, v.wx,
            v.xy, v.yy, v.zy, v.wy,
            v.xz, v.yz, v.zz, v.wz,
            v.xw, v.yw, v.zw, v.ww
        };
    }

//  --------------------------------------------------------
//  GETTERS

    template <typename T>
    constexpr Vector4<T>  diagonal(const Tensor44<T>& v)
    {
        return {v.xx, v.yy, v.zz, v.ww};
    }

    template <typename T>
    constexpr Vector4<T>  x_column(const Tensor44<T>&v) 
    {
        return {v.xx, v.yx, v.zx, v.wx};
    }

    template <typename T>
    constexpr Vector4<T>  y_column(const Tensor44<T>&v) 
    {
        return {v.xy, v.yy, v.zy, v.wy};
    }

    template <typename T>
    constexpr Vector4<T>  z_column(const Tensor44<T>&v) 
    {
        return {v.xz, v.yz, v.zz, v.wz};
    }

    template <typename T>
    constexpr Vector4<T>  w_column(const Tensor44<T>&v) 
    {
        return {v.xw, v.yw, v.zw, v.ww};
    }

    template <typename T>
    constexpr Vector4<T>  x_row(const Tensor44<T>&v)
    {
        return {v.xx, v.xy, v.xz, v.xw};
    }

    template <typename T>
    constexpr Vector4<T>  y_row(const Tensor44<T>&v)
    {
        return {v.yx, v.yy, v.yz, v.yw};
    }

    template <typename T>
    constexpr Vector4<T>  z_row(const Tensor44<T>&v)
    {
        return {v.zx, v.zy, v.zz, v.zw};
    }

    template <typename T>
    constexpr Vector4<T>  w_row(const Tensor44<T>&v)
    {
        return {v.wx, v.wy, v.wz, v.ww};
    }


//  --------------------------------------------------------
//  SETTERS

            
    template <typename T>
    Tensor44<T>&  set_diagonal(Tensor44<T>& ten, const Vector4<T>& v)
    {        ten.xx = v.x;
        ten.yy = v.y;
        ten.zz = v.z;
        ten.ww = v.w;
        return ten;
    }


    template <typename T>
    Tensor44<T>& set_x_column(Tensor44<T>&ten, const Vector4<T>& v)
    {
        ten.xx = v.x;
        ten.yx = v.y;
        ten.zx = v.z;
        ten.wx = v.w;
        return ten;
    }

    template <typename T>
    Tensor44<T>& set_y_column(Tensor44<T>&ten, const Vector4<T>& v)
    {
        ten.xy = v.x;
        ten.yy = v.y;
        ten.zy = v.z;
        ten.wy = v.w;
        return ten;
    }

    template <typename T>
    Tensor44<T>& set_z_column(Tensor44<T>&ten, const Vector4<T>& v)
    {
        ten.xz = v.x;
        ten.yz = v.y;
        ten.zz = v.z;
        ten.wz = v.w;
        return ten;
    }

    template <typename T>
    Tensor44<T>& set_w_column(Tensor44<T>&ten, const Vector4<T>& v)
    {
        ten.xw = v.x;
        ten.yw = v.y;
        ten.zw = v.z;
        ten.ww = v.w;
        return ten;
    }

    template <typename T>
    Tensor44<T>& set_x_row(Tensor44<T>&ten, const Vector4<T>& v)
    {
        ten.xx = v.x;
        ten.xy = v.y;
        ten.xz = v.z;
        ten.xw = v.w;
        return ten;
    }

    template <typename T>
    Tensor44<T>& set_y_row(Tensor44<T>&ten, const Vector4<T>& v)
    {
        ten.yx = v.x;
        ten.yy = v.y;
        ten.yz = v.z;
        ten.yw = v.w;
        return ten;
    }

    template <typename T>
    Tensor44<T>& set_z_row(Tensor44<T>&ten, const Vector4<T>& v)
    {
        ten.zx = v.x;
        ten.zy = v.y;
        ten.zz = v.z;
        ten.zw = v.w;
        return ten;
    }

    template <typename T>
    Tensor44<T>& set_w_row(Tensor44<T>&ten, const Vector4<T>& v)
    {
        ten.wx = v.x;
        ten.wy = v.y;
        ten.wz = v.z;
        ten.ww = v.w;
        return ten;
    }

//  --------------------------------------------------------
//  POSITIVE

    template <typename T>
    constexpr Tensor44<T>  operator+(const Tensor44<T>& a) 
    { 
        return a; 
    }


//  --------------------------------------------------------
//  NEGATIVE

    template <typename T>
    constexpr Tensor44<T>  operator-(const Tensor44<T>& a) 
    {
        return {
            -a.xx, -a.xy, -a.xz, -a.xw,
            -a.yx, -a.yy, -a.yz, -a.yw,
            -a.zx, -a.zy, -a.zz, -a.zw,
            -a.wx, -a.wy, -a.wz, -a.ww
        };
    }


//  --------------------------------------------------------
//  ADDITION

    template <typename T>
    constexpr Tensor44<T>   operator+ (const Tensor44<T> &a, const Tensor44<T> &b) 
    {
        return {
            a.xx+b.xx, a.xy+b.xy, a.xz+b.xz, a.xw+b.xw,
            a.yx+b.yx, a.yy+b.yy, a.yz+b.yz, a.yw+b.yw,
            a.zx+b.zx, a.zy+b.zy, a.zz+b.zz, a.zw+b.zw,
            a.wx+b.wx, a.wy+b.wy, a.wz+b.wz, a.ww+b.ww
        };
    }

    template <typename T>
    Tensor44<T>&   operator+=(Tensor44<T> &a, const Tensor44<T> &b) 
    {
        a.xx+=b.xx;  a.xy+=b.xy;  a.xz+=b.xz;  a.xw+=b.xw;
        a.yx+=b.yx;  a.yy+=b.yy;  a.yz+=b.yz;  a.yw+=b.yw;
        a.zx+=b.zx;  a.zy+=b.zy;  a.zz+=b.zz;  a.zw+=b.zw;
        a.wx+=b.wx;  a.wy+=b.wy;  a.wz+=b.wz;  a.ww+=b.ww;
        return a;
    }


//  --------------------------------------------------------
//  SUBTRACTION

    template <typename T>
    constexpr Tensor44<T>   operator- (const Tensor44<T> &a, const Tensor44<T> &b) 
    {
        return {
            a.xx-b.xx, a.xy-b.xy, a.xz-b.xz, a.xw-b.xw,
            a.yx-b.yx, a.yy-b.yy, a.yz-b.yz, a.yw-b.yw,
            a.zx-b.zx, a.zy-b.zy, a.zz-b.zz, a.zw-b.zw,
            a.wx-b.wx, a.wy-b.wy, a.wz-b.wz, a.ww-b.ww
        };
    }
    

    template <typename T>
    Tensor44<T>&   operator-=(Tensor44<T> &a, const Tensor44<T> &b) 
    {
        a.xx-=b.xx;  a.xy-=b.xy;  a.xz-=b.xz;  a.xw-=b.xw;
        a.yx-=b.yx;  a.yy-=b.yy;  a.yz-=b.yz;  a.yw-=b.yw;
        a.zx-=b.zx;  a.zy-=b.zy;  a.zz-=b.zz;  a.zw-=b.zw;
        a.wx-=b.wx;  a.wy-=b.wy;  a.wz-=b.wz;  a.ww-=b.ww;
        return a;
    }
    
//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires std::is_arithmetic_v<T>
    constexpr Tensor44<product_t<T,U>>  operator*(T a, const Tensor44<T>& b)
    {
        return {
            a*b.xx, a*b.xy, a*b.xz, a*b.xw,
            a*b.yx, a*b.yy, a*b.yz, a*b.yw,
            a*b.zx, a*b.zy, a*b.zz, a*b.zw,
            a*b.wx, a*b.wy, a*b.wz, a*b.ww
        };
    }
    
    
    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor44<product_t<T,U>>  operator*(const Tensor44<T>& a, U b)
    {
        return {
            a.xx*b, a.xy*b, a.xz*b, a.xw*b,
            a.yx*b, a.yy*b, a.yz*b, a.yw*b,
            a.zx*b, a.zy*b, a.zz*b, a.zw*b,
            a.wx*b, a.wy*b, a.wz*b, a.ww*b
        };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Tensor44<product_t<T,U>>  operator*=(const Tensor44<T>& a, U b)
    {
        a.xx*=b; a.xy*=b; a.xz*=b; a.xw*=b;
        a.yx*=b; a.yy*=b; a.yz*=b; a.yw*=b;
        a.zx*=b; a.zy*=b; a.zz*=b; a.zw*=b;
        a.wx*=b; a.wy*=b; a.wz*=b; a.ww*=b;        
        return a;
    }

    template <typename T, typename U>
    constexpr Tensor44<product_t<T,U>> operator*(const Tensor44<T>& a, const Tensor44<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx + a.xz*b.zx + a.xw*b.wx,
            a.xx*b.xy + a.xy*b.yy + a.xz*b.zy + a.xw*b.wy,
            a.xx*b.xz + a.xy*b.yz + a.xz*b.zz + a.xw*b.wz,
            a.xx*b.xw + a.xy*b.yw + a.xz*b.zw + a.xw*b.ww,

            a.yx*b.xx + a.yy*b.yx + a.yz*b.zx + a.yw*b.wx,
            a.yx*b.xy + a.yy*b.yy + a.yz*b.zy + a.yw*b.wy,
            a.yx*b.xz + a.yy*b.yz + a.yz*b.zz + a.yw*b.wz,
            a.yx*b.xw + a.yy*b.yw + a.yz*b.zw + a.yw*b.ww,

            a.zx*b.xx + a.zy*b.yx + a.zz*b.zx + a.zw*b.wx,
            a.zx*b.xy + a.zy*b.yy + a.zz*b.zy + a.zw*b.wy,
            a.zx*b.xz + a.zy*b.yz + a.zz*b.zz + a.zw*b.wz,
            a.zx*b.xw + a.zy*b.yw + a.zz*b.zw + a.zw*b.ww,

            a.wx*b.xx + a.wy*b.yx + a.wz*b.zx + a.ww*b.wx,
            a.wx*b.xy + a.wy*b.yy + a.wz*b.zy + a.ww*b.wy,
            a.wx*b.xz + a.wy*b.yz + a.wz*b.zz + a.ww*b.wz,
            a.wx*b.xw + a.wy*b.yw + a.wz*b.zw + a.ww*b.ww
        };
    }
    
    template <typename T, typename U>
    requires trait::self_mul_v<T,U>
    Tensor44<T>& operator*=(Tensor44<T>&a, const Tensor44<U>& b)
    {
        a = a * b;
        return a;
    }

        
    template <typename T, typename U>
    constexpr Vector4<product_t<T,U>> operator*(const Tensor44<T>&a, const Vector4<U>&b)
    {
        return {
            a.xx*b.x + a.xy*b.y + a.xz*b.z + a.xw*b.w,
            a.yx*b.x + a.yy*b.y + a.yz*b.z + a.yw*b.w,
            a.zx*b.x + a.zy*b.y + a.zz*b.z + a.zw*b.w,
            a.wx*b.x + a.wy*b.y + a.wz*b.z + a.ww*b.w
        };
    }

    template <typename T, typename U>
    constexpr Vector4<product_t<T,U>> operator*(const Vector4<T>&a, const Tensor44<U>&b)
    {
        return {
            a.x*b.xx + a.y*b.yx + a.z*b.zx + a.w*b.wx,
            a.x*b.xy + a.y*b.yy + a.z*b.zy + a.w*b.wy,
            a.x*b.xz + a.y*b.yz + a.z*b.zz + a.w*b.wz,
            a.x*b.xw + a.y*b.yw + a.z*b.zw + a.w*b.ww
        };
    }

    template <typename T, typename U>
    requires trait::self_mul_v<T,U>
    Vector4<T>& operator*=(Vector4<T>&a, const Tensor44<U>& b)
    {
        a = a * b;
        return a;
    }

//  --------------------------------------------------------
//  DIVISION


    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor44<quotient_t<T,U>>  operator/(const Tensor44<T>& a, U b)
    {
        return {
            a.xx/b, a.xy/b, a.xz/b, a.xw/b,
            a.yx/b, a.yy/b, a.yz/b, a.yw/b,
            a.zx/b, a.zy/b, a.zz/b, a.zw/b,
            a.wx/b, a.wy/b, a.wz/b, a.ww/b
        };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Tensor44<quotient_t<T,U>>  operator/=(const Tensor44<T>& a, U b)
    {
        a.xx/=b; a.xy/=b; a.xz/=b; a.xw/=b;
        a.yx/=b; a.yy/=b; a.yz/=b; a.yw/=b;
        a.zx/=b; a.zy/=b; a.zz/=b; a.zw/=b;
        a.wx/=b; a.wy/=b; a.wz/=b; a.ww/=b;        
        return a;
    }

//  --------------------------------------------------------
//  OTIMES PRODUCT

    template <typename T, typename U>
    constexpr Tensor44<product_t<T,U>> operator OTIMES(const Vector4<T>&a, const Vector4<U>&b)
    {
        return {
            a.x+b.x, a.x+b.y, a.x+b.z, a.x+b.w,
            a.y+b.x, a.y+b.y, a.y+b.z, a.y+b.w,
            a.z+b.x, a.z+b.y, a.z+b.z, a.z+b.w,
            a.w+b.x, a.w+b.y, a.w+b.z, a.w+b.w
        };
    }

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

    /*! \brief Trace of the 4 x 4 tensor
    
        \param[in] a    Tensor to take the trace of
    */
    template <typename T>
    constexpr T     trace(const Tensor44<T>& a)
    {
        return a.xx+a.yy+a.zz+a.ww;
    }

}

YQ_TYPE_DECLARE(yq::Tensor44D)
YQ_TYPE_DECLARE(yq::Tensor44F)
YQ_TYPE_DECLARE(yq::Tensor44I)
YQ_TYPE_DECLARE(yq::Tensor44U)

