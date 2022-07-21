////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__TENSOR_3_1__HPP 1
#include <math/preamble.hpp>
#include <math/Vector1.hpp>
#include <math/Vector3.hpp>

namespace yq {
    /*! \brief 3x1 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor31 {
        using component_type = T;
        T xx;
        T yx;
        T zx;

        constexpr bool operator==(const Tensor31&) const noexcept = default;
    };

    YQ_IEEE754_1(Tensor31)
        
//  --------------------------------------------------------
//  COMPOSITION

    template <typename T>
    constexpr Tensor31<T>  columns(const Vector3<T>&x)
    {
        return {
            x.x,
            x.y,
            x.z
        };
    }

    template <typename T>
    constexpr Tensor31<T>  rows(const Vector1<T>&x, const Vector1<T>&y, const Vector1<T>&z)
    {
        return {
            x.x,
            y.x,
            z.x
        };
    }
    
    YQ_IDENTITY_1(Tensor31, {
        one_v<T>,
        zero_v<T>,
        zero_v<T>
    })

    YQ_NAN_1(Tensor31, {
        nan_v<T>,
        nan_v<T>,
        nan_v<T> 
    })
    
    YQ_ZERO_1(Tensor31, {
        zero_v<T>,
        zero_v<T>,
        zero_v<T> 
     })
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor31, 
        is_finite(v.xx) &&
        is_finite(v.yx) &&
        is_finite(v.zx)
    )
    
    YQ_IS_NAN_1(Tensor31,  
        is_nan(v.xx) ||
        is_nan(v.yx) ||
        is_nan(v.zx)
    )

//  --------------------------------------------------------
//  GETTERS

    template <typename T>
    constexpr Vector3<T>  x_column(const Tensor31<T>&v) 
    {
        return {v.xx, v.yx, v.zx};
    }

    template <typename T>
    constexpr Vector1<T>  x_row(const Tensor31<T>&v)
    {
        return {v.xx};
    }

    template <typename T>
    constexpr Vector1<T>  y_row(const Tensor31<T>&v)
    {
        return {v.yx};
    }

    template <typename T>
    constexpr Vector1<T>  z_row(const Tensor31<T>&v)
    {
        return {v.zx};
    }


//  --------------------------------------------------------
//  SETTERS

    template <typename T>
    Tensor31<T>& set_x_column(Tensor31<T>&ten, const Vector1<T>& v)
    {
        ten.xx = v.x;
        ten.yx = v.y;
        ten.zx = v.z;
        return ten;
    }

    template <typename T>
    Tensor31<T>& set_x_row(Tensor31<T>&ten, const Vector3<T>& v)
    {
        ten.xx = v.x;
        return ten;
    }

    template <typename T>
    Tensor31<T>& set_y_row(Tensor31<T>&ten, const Vector3<T>& v)
    {
        ten.yx = v.x;
        return ten;
    }

    template <typename T>
    Tensor31<T>& set_z_row(Tensor31<T>&ten, const Vector3<T>& v)
    {
        ten.zx = v.x;
        return ten;
    }

//  --------------------------------------------------------
//  POSITIVE

    template <typename T>
    constexpr Tensor31<T>  operator+(const Tensor31<T>& a) 
    { 
        return a; 
    }


//  --------------------------------------------------------
//  NEGATIVE

    template <typename T>
    constexpr Tensor31<T>  operator-(const Tensor31<T>& a) 
    {
        return {
            -a.xx,
            -a.yx,
            -a.zx
        };
    }


//  --------------------------------------------------------
//  ADDITION

    template <typename T>
    constexpr Tensor31<T>   operator+ (const Tensor31<T> &a, const Tensor31<T> &b) 
    {
        return {
            a.xx+b.xx,
            a.yx+b.yx,
            a.zx+b.zx
        };
    }

    template <typename T>
    Tensor31<T>&   operator+=(Tensor31<T> &a, const Tensor31<T> &b) 
    {
        a.xx+=b.xx;
        a.yx+=b.yx;
        a.zx+=b.zx;
        return a;
    }


//  --------------------------------------------------------
//  SUBTRACTION

    template <typename T>
    constexpr Tensor31<T>   operator- (const Tensor31<T> &a, const Tensor31<T> &b) 
    {
        return {
            a.xx-b.xx,
            a.yx-b.yx,
            a.zx-b.zx
        };
    }
    

    template <typename T>
    Tensor31<T>&   operator-=(Tensor31<T> &a, const Tensor31<T> &b) 
    {
        a.xx-=b.xx;
        a.yx-=b.yx;
        a.zx-=b.zx;
        return a;
    }
    
//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires std::is_arithmetic_v<T>
    constexpr Tensor31<product_t<T,U>>  operator*(T a, const Tensor31<T>& b)
    {
        return {
            a*b.xx,
            a*b.yx,
            a*b.zx
        };
    }
    
    
    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor31<product_t<T,U>>  operator*(const Tensor31<T>& a, U b)
    {
        return {
            a.xx*b,
            a.yx*b,
            a.zx*b
        };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Tensor31<product_t<T,U>>  operator*=(const Tensor31<T>& a, U b)
    {
        a.xx*=b;
        a.yx*=b;
        a.zx*=b;        
        return a;
    }

        
    template <typename T, typename U>
    constexpr Vector3<product_t<T,U>> operator*(const Tensor31<T>&a, const Vector1<U>&b)
    {
        return {
            a.xx*b.x,
            a.yx*b.x,
            a.zx*b.x
        };
    }

    template <typename T, typename U>
    constexpr Vector1<product_t<T,U>> operator*(const Vector3<T>&a, const Tensor31<U>&b)
    {
        return {
            a.x*b.xx + a.y*b.yx + a.z*b.zx
        };
    }

//  --------------------------------------------------------
//  DIVISION


    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor31<quotient_t<T,U>>  operator/(const Tensor31<T>& a, U b)
    {
        return {
            a.xx/b,
            a.yx/b,
            a.zx/b
        };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Tensor31<quotient_t<T,U>>  operator/=(const Tensor31<T>& a, U b)
    {
        a.xx/=b;
        a.yx/=b;
        a.zx/=b;        
        return a;
    }

//  --------------------------------------------------------
//  OTIMES PRODUCT

    template <typename T, typename U>
    constexpr Tensor31<product_t<T,U>> operator OTIMES(const Vector3<T>&a, const Vector1<U>&b)
    {
        return {
            a.x+b.x,
            a.y+b.x,
            a.z+b.x
        };
    }

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

}

YQ_TYPE_DECLARE(yq::Tensor31D)
YQ_TYPE_DECLARE(yq::Tensor31F)
YQ_TYPE_DECLARE(yq::Tensor31I)
YQ_TYPE_DECLARE(yq::Tensor31U)

