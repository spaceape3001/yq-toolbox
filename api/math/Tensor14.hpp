////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__TENSOR_1_4__HPP 1
#include <math/preamble.hpp>
#include <math/Vector1.hpp>
#include <math/Vector4.hpp>

namespace yq {
    /*! \brief 1x4 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor14 {
        //! Component type (captures the template parameter)
        using component_type = T;
        
        T xx, xy, xz, xw;

        //! Defaulted equality operator
        constexpr bool operator==(const Tensor14&) const noexcept = default;

        //! Positive (affirmation) operator
        constexpr Tensor14<T>  operator+() const noexcept 
        { 
            return *this; 
        }

        //! Negation operator
        constexpr Tensor14<T>  operator-() const noexcept
        {
            return {
                -xx, -xy, -xz, -xw
            };
        }


        //  --------------------------------------------------------
        //  GETTERS

            //! Gets the x-column
            constexpr Vector1<T>  x_column() const noexcept
            {
                return {xx};
            }

            //! Gets the y-column
            constexpr Vector1<T>  y_column() const noexcept
            {
                return {xy};
            }

            //! Gets the z-column
            constexpr Vector1<T>  z_column() const noexcept
            {
                return {xz};
            }

            //! Gets the w-column
            constexpr Vector1<T>  w_column() const noexcept
            {
                return {xw};
            }

            //! Gets the x-row
            constexpr Vector4<T>  x_row() const noexcept
            {
                return {xx, xy, xz, xw};
            }

        //  --------------------------------------------------------
        //  SETTERS

            //! Sets the x-column
            Tensor14<T>& x_column(const Vector1<T>& v)
            {
                xx = v.x;
                return *this;
            }

            //! Sets the x-column
            Tensor14<T>& x_column(T _xx)
            {
                xx = _xx;
                return *this;
            }

            //! Sets the y-column
            Tensor14<T>& y_column(const Vector1<T>& v)
            {
                xy = v.x;
                return *this;
            }

            //! Sets the y-column
            Tensor14<T>& y_column(T _xy)
            {
                xy = _xy;
                return *this;
            }

            //! Sets the z-column
            Tensor14<T>& z_column(const Vector1<T>& v)
            {
                xz = v.x;
                return *this;
            }

            //! Sets the z-column
            Tensor14<T>& z_column(T _xz)
            {
                xz = _xz;
                return *this;
            }

            //! Sets the w-column
            Tensor14<T>& w_column(const Vector1<T>& v)
            {
                xw = v.x;
                return *this;
            }

            //! Sets the w-column
            Tensor14<T>& w_column(T _xw)
            {
                xw = _xw;
                return *this;
            }

            //! Sets the x-row
            Tensor14<T>& x_row(const Vector4<T>& v)
            {
                xx = v.x;
                xy = v.y;
                xz = v.z;
                xw = v.w;
                return *this;
            }

            //! Sets the x-row
            Tensor14<T>& x_row(T _xx, T _xy, T _xz, T _xw)
            {
                xx = _xx;
                xy = _xy;
                xz = _xz;
                xw = _xw;
                return *this;
            }


    };

    YQ_IEEE754_1(Tensor14)
        
//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Create 1x4 tensor by columns
    */
    template <typename T>
    constexpr Tensor14<T>  columns(const Vector1<T>&x, const Vector1<T>&y, const Vector1<T>&z, const Vector1<T>&w)
    {
        return {
            x.x, y.x, z.x, w.x
        };
    }

    /*! \brief Create 1x4 tensor by columns
    */
    template <typename T>
    constexpr Tensor14<T>  rows(const Vector4<T>&x)
    {
        return {
            x.x, x.y, x.z, x.w
        };
    }
    
    YQ_IDENTITY_1(Tensor14, {
        one_v<T>, zero_v<T>, zero_v<T>, zero_v<T>
    })

    YQ_NAN_1(Tensor14, {
        nan_v<T>, nan_v<T>, nan_v<T>, nan_v<T> 
    })
    
    YQ_ZERO_1(Tensor14, {
        zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T> 
     })
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor14, 
        is_finite(v.xx) && is_finite(v.xy) && is_finite(v.xz) && is_finite(v.xw)
    )
    
    YQ_IS_NAN_1(Tensor14,  
        is_nan(v.xx) || is_nan(v.xy) || is_nan(v.xz) || is_nan(v.xw)
    )

//  --------------------------------------------------------
//  GETTERS

    template <typename T>
    constexpr Vector1<T>  x_column(const Tensor14<T>&ten) 
    {
        return ten.x_column();
    }

    template <typename T>
    constexpr Vector1<T>  y_column(const Tensor14<T>&ten) 
    {
        return ten.y_column();
    }

    template <typename T>
    constexpr Vector1<T>  z_column(const Tensor14<T>&ten) 
    {
        return ten.z_column();
    }

    template <typename T>
    constexpr Vector1<T>  w_column(const Tensor14<T>&ten) 
    {
        return ten.w_column();
    }

    template <typename T>
    constexpr Vector4<T>  x_row(const Tensor14<T>&ten)
    {
        return ten.x_row();
    }


//  --------------------------------------------------------
//  ADDITION

    template <typename T>
    constexpr Tensor14<T>   operator+ (const Tensor14<T> &a, const Tensor14<T> &b) 
    {
        return {
            a.xx+b.xx, a.xy+b.xy, a.xz+b.xz, a.xw+b.xw
        };
    }

    template <typename T>
    Tensor14<T>&   operator+=(Tensor14<T> &a, const Tensor14<T> &b) 
    {
        a.xx+=b.xx;  a.xy+=b.xy;  a.xz+=b.xz;  a.xw+=b.xw;
        return a;
    }


//  --------------------------------------------------------
//  SUBTRACTION

    template <typename T>
    constexpr Tensor14<T>   operator- (const Tensor14<T> &a, const Tensor14<T> &b) 
    {
        return {
            a.xx-b.xx, a.xy-b.xy, a.xz-b.xz, a.xw-b.xw
        };
    }
    

    template <typename T>
    Tensor14<T>&   operator-=(Tensor14<T> &a, const Tensor14<T> &b) 
    {
        a.xx-=b.xx;  a.xy-=b.xy;  a.xz-=b.xz;  a.xw-=b.xw;
        return a;
    }
    
//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires std::is_arithmetic_v<T>
    constexpr Tensor14<product_t<T,U>>  operator*(T a, const Tensor14<T>& b)
    {
        return {
            a*b.xx, a*b.xy, a*b.xz, a*b.xw
        };
    }
    
    
    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor14<product_t<T,U>>  operator*(const Tensor14<T>& a, U b)
    {
        return {
            a.xx*b, a.xy*b, a.xz*b, a.xw*b
        };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Tensor14<product_t<T,U>>  operator*=(const Tensor14<T>& a, U b)
    {
        a.xx*=b; a.xy*=b; a.xz*=b; a.xw*=b;        
        return a;
    }

        
    template <typename T, typename U>
    constexpr Vector1<product_t<T,U>> operator*(const Tensor14<T>&a, const Vector4<U>&b)
    {
        return {
            a.xx*b.x + a.xy*b.y + a.xz*b.z + a.xw*b.w
        };
    }

    template <typename T, typename U>
    constexpr Vector4<product_t<T,U>> operator*(const Vector1<T>&a, const Tensor14<U>&b)
    {
        return {
            a.x*b.xx,
            a.x*b.xy,
            a.x*b.xz,
            a.x*b.xw
        };
    }

//  --------------------------------------------------------
//  DIVISION


    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor14<quotient_t<T,U>>  operator/(const Tensor14<T>& a, U b)
    {
        return {
            a.xx/b, a.xy/b, a.xz/b, a.xw/b
        };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Tensor14<quotient_t<T,U>>  operator/=(const Tensor14<T>& a, U b)
    {
        a.xx/=b; a.xy/=b; a.xz/=b; a.xw/=b;        
        return a;
    }

//  --------------------------------------------------------
//  OTIMES PRODUCT

    template <typename T, typename U>
    constexpr Tensor14<product_t<T,U>> operator OTIMES(const Vector1<T>&a, const Vector4<U>&b)
    {
        return {
            a.x+b.x, a.x+b.y, a.x+b.z, a.x+b.w
        };
    }

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

}

YQ_TYPE_DECLARE(yq::Tensor14D)
YQ_TYPE_DECLARE(yq::Tensor14F)
YQ_TYPE_DECLARE(yq::Tensor14I)
YQ_TYPE_DECLARE(yq::Tensor14U)

