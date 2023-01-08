////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__TENSOR_1_3__HPP 1
#include <math/preamble.hpp>
#include <math/Vector1.hpp>
#include <math/Vector3.hpp>

namespace yq {
    /*! \brief 1x3 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor13 {
    
        //! Component type (captures the template parameter)
        using component_type = T;
        T xx, xy, xz;

        //! Defaulted equality operator
        constexpr bool operator==(const Tensor13&) const noexcept = default;

        //! Positive (affirmation) operator
        constexpr Tensor13  operator+() const noexcept
        { 
            return *this; 
        }

        //! Negation operator
        constexpr Tensor13  operator-() const noexcept
        {
            return {
                -xx, -xy, -xz
            };
        }

        //  --------------------------------------------------------
        //  GETTERS

            constexpr Vector1<T>  x_column() const noexcept
            {
                return {xx};
            }

            constexpr Vector1<T>  y_column() const noexcept
            {
                return {xy};
            }

            constexpr Vector1<T>  z_column() const noexcept
            {
                return {xz};
            }

            constexpr Vector3<T>  x_row() const noexcept
            {
                return {xx, xy, xz};
            }



        //  --------------------------------------------------------
        //  SETTERS

            Tensor13& x_column(const Vector1<T>& v)
            {
                xx = v.x;
                return *this;
            }

            Tensor13& x_column(T _xx)
            {
                xx = _xx;
                return *this;
            }

            Tensor13& y_column(const Vector1<T>& v)
            {
                xy = v.x;
                return *this;
            }

            Tensor13& y_column(T _xy)
            {
                xy = _xy;
                return *this;
            }

            Tensor13& z_column(const Vector1<T>& v)
            {
                xz = v.x;
                return *this;
            }


            Tensor13& z_column(T _xz)
            {
                xz = _xz;
                return *this;
            }

            Tensor13& x_row(const Vector3<T>& v)
            {
                xx = v.x;
                xy = v.y;
                xz = v.z;
                return *this;
            }

            Tensor13& x_row(T _xx, T _xy, T _xz)
            {
                xx = _xx;
                xy = _xy;
                xz = _xz;
                return *this;
            }
    };

    YQ_IEEE754_1(Tensor13)
        
//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Create 1x3 tensor by columns
    */
    template <typename T>
    constexpr Tensor13<T>  columns(const Vector1<T>&x, const Vector1<T>&y, const Vector1<T>&z)
    {
        return {
            x.x, y.x, z.x
        };
    }

    /*! \brief Create 1x3 tensor by rows
    */
    template <typename T>
    constexpr Tensor13<T>  rows(const Vector3<T>&x)
    {
        return {
            x.x, x.y, x.z
        };
    }
    
    YQ_IDENTITY_1(Tensor13, {
        one_v<T>, zero_v<T>, zero_v<T>
    })

    YQ_NAN_1(Tensor13, {
        nan_v<T>, nan_v<T>, nan_v<T> 
    })
    
    YQ_ZERO_1(Tensor13, {
        zero_v<T>, zero_v<T>, zero_v<T> 
     })
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor13, 
        is_finite(v.xx) && is_finite(v.xy) && is_finite(v.xz)
    )
    
    YQ_IS_NAN_1(Tensor13,  
        is_nan(v.xx) || is_nan(v.xy) || is_nan(v.xz)
    )

//  --------------------------------------------------------
//  GETTERS

    template <typename T>
    constexpr Vector1<T>  x_column(const Tensor13<T>&ten) 
    {
        return ten.x_column();
    }

    template <typename T>
    constexpr Vector1<T>  y_column(const Tensor13<T>&ten) 
    {
        return ten.y_column();
    }

    template <typename T>
    constexpr Vector1<T>  z_column(const Tensor13<T>&ten) 
    {
        return ten.z_column();
    }

    template <typename T>
    constexpr Vector3<T>  x_row(const Tensor13<T>&ten)
    {
        return ten.x_row();
    }



//  --------------------------------------------------------
//  ADDITION

    template <typename T>
    constexpr Tensor13<T>   operator+ (const Tensor13<T> &a, const Tensor13<T> &b) 
    {
        return {
            a.xx+b.xx, a.xy+b.xy, a.xz+b.xz
        };
    }

    template <typename T>
    Tensor13<T>&   operator+=(Tensor13<T> &a, const Tensor13<T> &b) 
    {
        a.xx+=b.xx;  a.xy+=b.xy;  a.xz+=b.xz;
        return a;
    }


//  --------------------------------------------------------
//  SUBTRACTION

    template <typename T>
    constexpr Tensor13<T>   operator- (const Tensor13<T> &a, const Tensor13<T> &b) 
    {
        return {
            a.xx-b.xx, a.xy-b.xy, a.xz-b.xz
        };
    }
    

    template <typename T>
    Tensor13<T>&   operator-=(Tensor13<T> &a, const Tensor13<T> &b) 
    {
        a.xx-=b.xx;  a.xy-=b.xy;  a.xz-=b.xz;
        return a;
    }
    
//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires std::is_arithmetic_v<T>
    constexpr Tensor13<product_t<T,U>>  operator*(T a, const Tensor13<T>& b)
    {
        return {
            a*b.xx, a*b.xy, a*b.xz
        };
    }
    
    
    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor13<product_t<T,U>>  operator*(const Tensor13<T>& a, U b)
    {
        return {
            a.xx*b, a.xy*b, a.xz*b
        };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Tensor13<product_t<T,U>>  operator*=(const Tensor13<T>& a, U b)
    {
        a.xx*=b; a.xy*=b; a.xz*=b;        
        return a;
    }

        
    template <typename T, typename U>
    constexpr Vector1<product_t<T,U>> operator*(const Tensor13<T>&a, const Vector3<U>&b)
    {
        return {
            a.xx*b.x + a.xy*b.y + a.xz*b.z
        };
    }

    template <typename T, typename U>
    constexpr Vector3<product_t<T,U>> operator*(const Vector1<T>&a, const Tensor13<U>&b)
    {
        return {
            a.x*b.xx,
            a.x*b.xy,
            a.x*b.xz
        };
    }

//  --------------------------------------------------------
//  DIVISION


    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor13<quotient_t<T,U>>  operator/(const Tensor13<T>& a, U b)
    {
        return {
            a.xx/b, a.xy/b, a.xz/b
        };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Tensor13<quotient_t<T,U>>  operator/=(const Tensor13<T>& a, U b)
    {
        a.xx/=b; a.xy/=b; a.xz/=b;        
        return a;
    }

//  --------------------------------------------------------
//  OTIMES PRODUCT

    template <typename T, typename U>
    constexpr Tensor13<product_t<T,U>> operator OTIMES(const Vector1<T>&a, const Vector3<U>&b)
    {
        return {
            a.x+b.x, a.x+b.y, a.x+b.z
        };
    }

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

}

YQ_TYPE_DECLARE(yq::Tensor13D)
YQ_TYPE_DECLARE(yq::Tensor13F)
YQ_TYPE_DECLARE(yq::Tensor13I)
YQ_TYPE_DECLARE(yq::Tensor13U)

