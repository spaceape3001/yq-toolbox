////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__TENSOR_2_3__HPP 1
#include <math/preamble.hpp>
#include <math/Vector2.hpp>
#include <math/Vector3.hpp>

namespace yq {
    /*! \brief 2x3 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor23 {
        using component_type = T;
        T xx, xy, xz;
        T yx, yy, yz;

        constexpr bool operator==(const Tensor23&) const noexcept = default;
    };

    YQ_IEEE754_1(Tensor23)
        
//  --------------------------------------------------------
//  COMPOSITION

    template <typename T>
    constexpr Tensor23<T>  columns(const Vector2<T>&x, const Vector2<T>&y, const Vector2<T>&z)
    {
        return {
            x.x, y.x, z.x,
            x.y, y.y, z.y
        };
    }

    template <typename T>
    constexpr Tensor23<T>  rows(const Vector3<T>&x, const Vector3<T>&y)
    {
        return {
            x.x, x.y, x.z,
            y.x, y.y, y.z
        };
    }
    
    YQ_IDENTITY_1(Tensor23, {
        one_v<T>, zero_v<T>, zero_v<T>,
        zero_v<T>, one_v<T>, zero_v<T>
    })

    YQ_NAN_1(Tensor23, {
        nan_v<T>, nan_v<T>, nan_v<T>,
        nan_v<T>, nan_v<T>, nan_v<T> 
    })
    
    YQ_ZERO_1(Tensor23, {
        zero_v<T>, zero_v<T>, zero_v<T>,
        zero_v<T>, zero_v<T>, zero_v<T> 
     })
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor23, 
        is_finite(v.xx) && is_finite(v.xy) && is_finite(v.xz) &&
        is_finite(v.yx) && is_finite(v.yy) && is_finite(v.yz)
    )
    
    YQ_IS_NAN_1(Tensor23,  
        is_nan(v.xx) || is_nan(v.xy) || is_nan(v.xz) ||
        is_nan(v.yx) || is_nan(v.yy) || is_nan(v.yz)
    )

//  --------------------------------------------------------
//  GETTERS

    template <typename T>
    constexpr Vector2<T>  x_column(const Tensor23<T>&v) 
    {
        return {v.xx, v.yx};
    }

    template <typename T>
    constexpr Vector2<T>  y_column(const Tensor23<T>&v) 
    {
        return {v.xy, v.yy};
    }

    template <typename T>
    constexpr Vector2<T>  z_column(const Tensor23<T>&v) 
    {
        return {v.xz, v.yz};
    }

    template <typename T>
    constexpr Vector3<T>  x_row(const Tensor23<T>&v)
    {
        return {v.xx, v.xy, v.xz};
    }

    template <typename T>
    constexpr Vector3<T>  y_row(const Tensor23<T>&v)
    {
        return {v.yx, v.yy, v.yz};
    }


//  --------------------------------------------------------
//  SETTERS

    template <typename T>
    Tensor23<T>& set_x_column(Tensor23<T>&ten, const Vector3<T>& v)
    {
        ten.xx = v.x;
        ten.yx = v.y;
        return ten;
    }

    template <typename T>
    Tensor23<T>& set_y_column(Tensor23<T>&ten, const Vector3<T>& v)
    {
        ten.xy = v.x;
        ten.yy = v.y;
        return ten;
    }

    template <typename T>
    Tensor23<T>& set_z_column(Tensor23<T>&ten, const Vector3<T>& v)
    {
        ten.xz = v.x;
        ten.yz = v.y;
        return ten;
    }

    template <typename T>
    Tensor23<T>& set_x_row(Tensor23<T>&ten, const Vector2<T>& v)
    {
        ten.xx = v.x;
        ten.xy = v.y;
        ten.xz = v.z;
        return ten;
    }

    template <typename T>
    Tensor23<T>& set_y_row(Tensor23<T>&ten, const Vector2<T>& v)
    {
        ten.yx = v.x;
        ten.yy = v.y;
        ten.yz = v.z;
        return ten;
    }

//  --------------------------------------------------------
//  POSITIVE

    template <typename T>
    constexpr Tensor23<T>  operator+(const Tensor23<T>& a) 
    { 
        return a; 
    }


//  --------------------------------------------------------
//  NEGATIVE

    template <typename T>
    constexpr Tensor23<T>  operator-(const Tensor23<T>& a) 
    {
        return {
            -a.xx, -a.xy, -a.xz,
            -a.yx, -a.yy, -a.yz
        };
    }


//  --------------------------------------------------------
//  ADDITION

    template <typename T>
    constexpr Tensor23<T>   operator+ (const Tensor23<T> &a, const Tensor23<T> &b) 
    {
        return {
            a.xx+b.xx, a.xy+b.xy, a.xz+b.xz,
            a.yx+b.yx, a.yy+b.yy, a.yz+b.yz
        };
    }

    template <typename T>
    Tensor23<T>&   operator+=(Tensor23<T> &a, const Tensor23<T> &b) 
    {
        a.xx+=b.xx;  a.xy+=b.xy;  a.xz+=b.xz;
        a.yx+=b.yx;  a.yy+=b.yy;  a.yz+=b.yz;
        return a;
    }


//  --------------------------------------------------------
//  SUBTRACTION

    template <typename T>
    constexpr Tensor23<T>   operator- (const Tensor23<T> &a, const Tensor23<T> &b) 
    {
        return {
            a.xx-b.xx, a.xy-b.xy, a.xz-b.xz,
            a.yx-b.yx, a.yy-b.yy, a.yz-b.yz
        };
    }
    

    template <typename T>
    Tensor23<T>&   operator-=(Tensor23<T> &a, const Tensor23<T> &b) 
    {
        a.xx-=b.xx;  a.xy-=b.xy;  a.xz-=b.xz;
        a.yx-=b.yx;  a.yy-=b.yy;  a.yz-=b.yz;
        return a;
    }
    
//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires std::is_arithmetic_v<T>
    constexpr Tensor23<product_t<T,U>>  operator*(T a, const Tensor23<T>& b)
    {
        return {
            a*b.xx, a*b.xy, a*b.xz,
            a*b.yx, a*b.yy, a*b.yz
        };
    }
    
    
    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor23<product_t<T,U>>  operator*(const Tensor23<T>& a, U b)
    {
        return {
            a.xx*b, a.xy*b, a.xz*b,
            a.yx*b, a.yy*b, a.yz*b
        };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Tensor23<product_t<T,U>>  operator*=(const Tensor23<T>& a, U b)
    {
        a.xx*=b; a.xy*=b; a.xz*=b;
        a.yx*=b; a.yy*=b; a.yz*=b;        
        return a;
    }

        
    template <typename T, typename U>
    constexpr Vector2<product_t<T,U>> operator*(const Tensor23<T>&a, const Vector3<U>&b)
    {
        return {
            a.xx*b.x + a.xy*b.y + a.xz*b.z,
            a.yx*b.x + a.yy*b.y + a.yz*b.z
        };
    }

    template <typename T, typename U>
    constexpr Vector3<product_t<T,U>> operator*(const Vector2<T>&a, const Tensor23<U>&b)
    {
        return {
            a.x*b.xx + a.y*b.yx,
            a.x*b.xy + a.y*b.yy,
            a.x*b.xz + a.y*b.yz
        };
    }

//  --------------------------------------------------------
//  DIVISION


    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor23<quotient_t<T,U>>  operator/(const Tensor23<T>& a, U b)
    {
        return {
            a.xx/b, a.xy/b, a.xz/b,
            a.yx/b, a.yy/b, a.yz/b
        };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Tensor23<quotient_t<T,U>>  operator/=(const Tensor23<T>& a, U b)
    {
        a.xx/=b; a.xy/=b; a.xz/=b;
        a.yx/=b; a.yy/=b; a.yz/=b;        
        return a;
    }

//  --------------------------------------------------------
//  OTIMES PRODUCT

    template <typename T, typename U>
    constexpr Tensor23<product_t<T,U>> operator OTIMES(const Vector2<T>&a, const Vector3<U>&b)
    {
        return {
            a.x+b.x, a.x+b.y, a.x+b.z,
            a.y+b.x, a.y+b.y, a.y+b.z
        };
    }

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

}

YQ_TYPE_DECLARE(yq::Tensor23D)
YQ_TYPE_DECLARE(yq::Tensor23F)
YQ_TYPE_DECLARE(yq::Tensor23I)
YQ_TYPE_DECLARE(yq::Tensor23U)

