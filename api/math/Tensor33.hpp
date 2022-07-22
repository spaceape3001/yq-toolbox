////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__TENSOR_3_3__HPP 1
#include <math/preamble.hpp>
#include <math/trig.hpp>
#include <math/Vector3.hpp>

namespace yq {
    /*! \brief 3x3 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor33 {
        using component_type = T;
        T xx, xy, xz;
        T yx, yy, yz;
        T zx, zy, zz;

        constexpr bool operator==(const Tensor33&) const noexcept = default;

        operator glm::mat<3,3,T,glm::defaultp>() const noexcept 
        {
            return {
                xx, yx, zx,
                xy, yy, zy,
                xz, yz, zz
            };
        }
    };

    YQ_IEEE754_1(Tensor33)
        
//  --------------------------------------------------------
//  COMPOSITION

    template <typename T>
    constexpr Tensor33<T>  columns(const Vector3<T>&x, const Vector3<T>&y, const Vector3<T>&z)
    {
        return {
            x.x, y.x, z.x,
            x.y, y.y, z.y,
            x.z, y.z, z.z
        };
    }

    template <typename T>
    constexpr Tensor33<T>  diagonal(const Vector3<T>&v)
    {
        return {
            v.x, zero_v<T>, zero_v<T>,
            zero_v<T>, v.y, zero_v<T>,
            zero_v<T>, zero_v<T>, v.z
        };
    }
    
    template <typename T>
    constexpr Tensor33<T>  diagonal(T x, std::type_identity_t<T> y, std::type_identity_t<T> z)
    {
        return {
            x, zero_v<T>, zero_v<T>,
            zero_v<T>, y, zero_v<T>,
            zero_v<T>, zero_v<T>, z
        };
    }

    template <typename T>
    Tensor33<T> hpr33(MKS<T,dim::Angle> hdg, MKS<T,dim::Angle> pitch, MKS<T,dim::Angle> roll)
    {
        auto ch = cos(hdg);
        auto sh = sin(hdg);

        auto cp = cos(pitch);
        auto sp = sin(pitch);

        auto cr = cos(roll);
        auto sr = sin(roll);
        
        return {
            ch*cp, sh*cp, -sp,
            ch*sp*sr-sh*cr, sh*sp*sr+ch*cr, cp*sr,
            ch*sp*cr+sh*sr, sh*sp*cr-ch*sr, cp*cr
        };
    }

    //! Creates a matrix that can rotate a vector by the specfied angle
    //! In the counter-clockwise direction
    template <typename T>
    constexpr Tensor33<T>   rotation3X(MKS<T,dim::Angle> r)
    {
        auto c  = cos(r);
        auto s  = sin(r);
        return {
            1., 0., 0.,
            0., c, -s,
            0., s, c
        };
    }

    //! Creates a matrix that can rotate a vector by the specfied angle
    //! In the counter-clockwise direction
    template <typename T>
    constexpr Tensor33<T>   rotation3Y(MKS<T,dim::Angle> r)
    {
        auto c  = cos(r);
        auto s  = sin(r);
        return {
            c, 0., -s,
            0., 1., 0.,
            s, 0., c
        };
    }


    //! Creates a matrix that can rotate a vector by the specfied angle
    //! In the counter-clockwise direction
    template <typename T>
    constexpr Tensor33<T>   rotation3Z(MKS<T,dim::Angle> r)
    {
        auto c  = cos(r);
        auto s  = sin(r);
        return {
            1., 0., 0.,
            0., c, -s,
            0., s, c
        };
    }


    template <typename T>
    constexpr Tensor33<T>  rows(const Vector3<T>&x, const Vector3<T>&y, const Vector3<T>&z)
    {
        return {
            x.x, x.y, x.z,
            y.x, y.y, y.z,
            z.x, z.y, z.z
        };
    }

    template <typename T, glm::qualifier Q>
    constexpr Tensor33<T> tensor(const glm::mat<3,3,T,Q>& t)
    {
        return {
            t.x.x, t.y.x, t.z.x, 
            t.x.y, t.y.y, t.z.y, 
            t.x.z, t.y.z, t.z.z
        };
    }
    
    
    YQ_IDENTITY_1(Tensor33, {
        one_v<T>, zero_v<T>, zero_v<T>,
        zero_v<T>, one_v<T>, zero_v<T>,
        zero_v<T>, zero_v<T>, one_v<T>
    })

    YQ_NAN_1(Tensor33, {
        nan_v<T>, nan_v<T>, nan_v<T>,
        nan_v<T>, nan_v<T>, nan_v<T>,
        nan_v<T>, nan_v<T>, nan_v<T> 
    })
    
    YQ_ZERO_1(Tensor33, {
        zero_v<T>, zero_v<T>, zero_v<T>,
        zero_v<T>, zero_v<T>, zero_v<T>,
        zero_v<T>, zero_v<T>, zero_v<T> 
     })
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor33, 
        is_finite(v.xx) && is_finite(v.xy) && is_finite(v.xz) &&
        is_finite(v.yx) && is_finite(v.yy) && is_finite(v.yz) &&
        is_finite(v.zx) && is_finite(v.zy) && is_finite(v.zz)
    )
    
    YQ_IS_NAN_1(Tensor33,  
        is_nan(v.xx) || is_nan(v.xy) || is_nan(v.xz) ||
        is_nan(v.yx) || is_nan(v.yy) || is_nan(v.yz) ||
        is_nan(v.zx) || is_nan(v.zy) || is_nan(v.zz)
    )

    template <typename T>
    constexpr Tensor33<T>  transpose(const Tensor33<T>&v)
    {
        return {
            v.xx, v.yx, v.zx,
            v.xy, v.yy, v.zy,
            v.xz, v.yz, v.zz
        };
    }

//  --------------------------------------------------------
//  GETTERS

    template <typename T>
    constexpr Vector3<T>  diagonal(const Tensor33<T>& v)
    {
        return {v.xx, v.yy, v.zz};
    }

    template <typename T>
    constexpr Vector3<T>  x_column(const Tensor33<T>&v) 
    {
        return {v.xx, v.yx, v.zx};
    }

    template <typename T>
    constexpr Vector3<T>  y_column(const Tensor33<T>&v) 
    {
        return {v.xy, v.yy, v.zy};
    }

    template <typename T>
    constexpr Vector3<T>  z_column(const Tensor33<T>&v) 
    {
        return {v.xz, v.yz, v.zz};
    }

    template <typename T>
    constexpr Vector3<T>  x_row(const Tensor33<T>&v)
    {
        return {v.xx, v.xy, v.xz};
    }

    template <typename T>
    constexpr Vector3<T>  y_row(const Tensor33<T>&v)
    {
        return {v.yx, v.yy, v.yz};
    }

    template <typename T>
    constexpr Vector3<T>  z_row(const Tensor33<T>&v)
    {
        return {v.zx, v.zy, v.zz};
    }


//  --------------------------------------------------------
//  SETTERS

            
    template <typename T>
    Tensor33<T>&  set_diagonal(Tensor33<T>& ten, const Vector3<T>& v)
    {        ten.xx = v.x;
        ten.yy = v.y;
        ten.zz = v.z;
        return ten;
    }


    template <typename T>
    Tensor33<T>& set_x_column(Tensor33<T>&ten, const Vector3<T>& v)
    {
        ten.xx = v.x;
        ten.yx = v.y;
        ten.zx = v.z;
        return ten;
    }

    template <typename T>
    Tensor33<T>& set_y_column(Tensor33<T>&ten, const Vector3<T>& v)
    {
        ten.xy = v.x;
        ten.yy = v.y;
        ten.zy = v.z;
        return ten;
    }

    template <typename T>
    Tensor33<T>& set_z_column(Tensor33<T>&ten, const Vector3<T>& v)
    {
        ten.xz = v.x;
        ten.yz = v.y;
        ten.zz = v.z;
        return ten;
    }

    template <typename T>
    Tensor33<T>& set_x_row(Tensor33<T>&ten, const Vector3<T>& v)
    {
        ten.xx = v.x;
        ten.xy = v.y;
        ten.xz = v.z;
        return ten;
    }

    template <typename T>
    Tensor33<T>& set_y_row(Tensor33<T>&ten, const Vector3<T>& v)
    {
        ten.yx = v.x;
        ten.yy = v.y;
        ten.yz = v.z;
        return ten;
    }

    template <typename T>
    Tensor33<T>& set_z_row(Tensor33<T>&ten, const Vector3<T>& v)
    {
        ten.zx = v.x;
        ten.zy = v.y;
        ten.zz = v.z;
        return ten;
    }

//  --------------------------------------------------------
//  POSITIVE

    template <typename T>
    constexpr Tensor33<T>  operator+(const Tensor33<T>& a) 
    { 
        return a; 
    }


//  --------------------------------------------------------
//  NEGATIVE

    template <typename T>
    constexpr Tensor33<T>  operator-(const Tensor33<T>& a) 
    {
        return {
            -a.xx, -a.xy, -a.xz,
            -a.yx, -a.yy, -a.yz,
            -a.zx, -a.zy, -a.zz
        };
    }


//  --------------------------------------------------------
//  ADDITION

    template <typename T>
    constexpr Tensor33<T>   operator+ (const Tensor33<T> &a, const Tensor33<T> &b) 
    {
        return {
            a.xx+b.xx, a.xy+b.xy, a.xz+b.xz,
            a.yx+b.yx, a.yy+b.yy, a.yz+b.yz,
            a.zx+b.zx, a.zy+b.zy, a.zz+b.zz
        };
    }

    template <typename T>
    Tensor33<T>&   operator+=(Tensor33<T> &a, const Tensor33<T> &b) 
    {
        a.xx+=b.xx;  a.xy+=b.xy;  a.xz+=b.xz;
        a.yx+=b.yx;  a.yy+=b.yy;  a.yz+=b.yz;
        a.zx+=b.zx;  a.zy+=b.zy;  a.zz+=b.zz;
        return a;
    }


//  --------------------------------------------------------
//  SUBTRACTION

    template <typename T>
    constexpr Tensor33<T>   operator- (const Tensor33<T> &a, const Tensor33<T> &b) 
    {
        return {
            a.xx-b.xx, a.xy-b.xy, a.xz-b.xz,
            a.yx-b.yx, a.yy-b.yy, a.yz-b.yz,
            a.zx-b.zx, a.zy-b.zy, a.zz-b.zz
        };
    }
    

    template <typename T>
    Tensor33<T>&   operator-=(Tensor33<T> &a, const Tensor33<T> &b) 
    {
        a.xx-=b.xx;  a.xy-=b.xy;  a.xz-=b.xz;
        a.yx-=b.yx;  a.yy-=b.yy;  a.yz-=b.yz;
        a.zx-=b.zx;  a.zy-=b.zy;  a.zz-=b.zz;
        return a;
    }
    
//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires std::is_arithmetic_v<T>
    constexpr Tensor33<product_t<T,U>>  operator*(T a, const Tensor33<T>& b)
    {
        return {
            a*b.xx, a*b.xy, a*b.xz,
            a*b.yx, a*b.yy, a*b.yz,
            a*b.zx, a*b.zy, a*b.zz
        };
    }
    
    
    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor33<product_t<T,U>>  operator*(const Tensor33<T>& a, U b)
    {
        return {
            a.xx*b, a.xy*b, a.xz*b,
            a.yx*b, a.yy*b, a.yz*b,
            a.zx*b, a.zy*b, a.zz*b
        };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Tensor33<product_t<T,U>>  operator*=(const Tensor33<T>& a, U b)
    {
        a.xx*=b; a.xy*=b; a.xz*=b;
        a.yx*=b; a.yy*=b; a.yz*=b;
        a.zx*=b; a.zy*=b; a.zz*=b;        
        return a;
    }

    template <typename T, typename U>
    constexpr Tensor33<product_t<T,U>> operator*(const Tensor33<T>& a, const Tensor33<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx + a.xz*b.zx,
            a.xx*b.xy + a.xy*b.yy + a.xz*b.zy,
            a.xx*b.xz + a.xy*b.yz + a.xz*b.zz,

            a.yx*b.xx + a.yy*b.yx + a.yz*b.zx,
            a.yx*b.xy + a.yy*b.yy + a.yz*b.zy,
            a.yx*b.xz + a.yy*b.yz + a.yz*b.zz,

            a.zx*b.xx + a.zy*b.yx + a.zz*b.zx,
            a.zx*b.xy + a.zy*b.yy + a.zz*b.zy,
            a.zx*b.xz + a.zy*b.yz + a.zz*b.zz
        };
    }
    
    template <typename T, typename U>
    requires trait::self_mul_v<T,U>
    Tensor33<T>& operator*=(Tensor33<T>&a, const Tensor33<U>& b)
    {
        a = a * b;
        return a;
    }

        
    template <typename T, typename U>
    constexpr Vector3<product_t<T,U>> operator*(const Tensor33<T>&a, const Vector3<U>&b)
    {
        return {
            a.xx*b.x + a.xy*b.y + a.xz*b.z,
            a.yx*b.x + a.yy*b.y + a.yz*b.z,
            a.zx*b.x + a.zy*b.y + a.zz*b.z
        };
    }

    template <typename T, typename U>
    constexpr Vector3<product_t<T,U>> operator*(const Vector3<T>&a, const Tensor33<U>&b)
    {
        return {
            a.x*b.xx + a.y*b.yx + a.z*b.zx,
            a.x*b.xy + a.y*b.yy + a.z*b.zy,
            a.x*b.xz + a.y*b.yz + a.z*b.zz
        };
    }

    template <typename T, typename U>
    requires trait::self_mul_v<T,U>
    Vector3<T>& operator*=(Vector3<T>&a, const Tensor33<U>& b)
    {
        a = a * b;
        return a;
    }

//  --------------------------------------------------------
//  DIVISION


    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor33<quotient_t<T,U>>  operator/(const Tensor33<T>& a, U b)
    {
        return {
            a.xx/b, a.xy/b, a.xz/b,
            a.yx/b, a.yy/b, a.yz/b,
            a.zx/b, a.zy/b, a.zz/b
        };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Tensor33<quotient_t<T,U>>  operator/=(const Tensor33<T>& a, U b)
    {
        a.xx/=b; a.xy/=b; a.xz/=b;
        a.yx/=b; a.yy/=b; a.yz/=b;
        a.zx/=b; a.zy/=b; a.zz/=b;        
        return a;
    }

//  --------------------------------------------------------
//  OTIMES PRODUCT

    template <typename T, typename U>
    constexpr Tensor33<product_t<T,U>> operator OTIMES(const Vector3<T>&a, const Vector3<U>&b)
    {
        return {
            a.x+b.x, a.x+b.y, a.x+b.z,
            a.y+b.x, a.y+b.y, a.y+b.z,
            a.z+b.x, a.z+b.y, a.z+b.z
        };
    }

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

    /*! \brief Trace of the 3 x 3 tensor
    
        \param[in] a    Tensor to take the trace of
    */
    template <typename T>
    constexpr T     trace(const Tensor33<T>& a)
    {
        return a.xx+a.yy+a.zz;
    }

}

YQ_TYPE_DECLARE(yq::Tensor33D)
YQ_TYPE_DECLARE(yq::Tensor33F)
YQ_TYPE_DECLARE(yq::Tensor33I)
YQ_TYPE_DECLARE(yq::Tensor33U)

