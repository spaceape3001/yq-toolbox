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
    
        //! Component type (captures template parameter)
        using component_type = T;
        
        T xx;
        T yx;
        T zx;

        //! Defaulted equality operator
        constexpr bool operator==(const Tensor31&) const noexcept = default;

        //! Positive (affirmation) operator
        constexpr const Tensor31&  operator+() const noexcept
        { 
            return *this; 
        }

        //! Negation
        constexpr Tensor31  operator-() const noexcept
        {
            return {
                -xx,
                -yx,
                -zx
            };
        }

        //  --------------------------------------------------------
        //  GETTERS

            //! X-column of this vector
            constexpr Vector3<T>  x_column() const noexcept
            {
                return {xx, yx, zx};
            }

            //! X-row of this vector
            constexpr Vector1<T>  x_row() const noexcept
            {
                return {xx};
            }

            //! Y-row of this vector
            constexpr Vector1<T>  y_row() const noexcept
            {
                return {yx};
            }

            //! Z-row of this vector
            constexpr Vector1<T>  z_row() const noexcept
            {
                return {zx};
            }


        //  --------------------------------------------------------
        //  SETTERS

            //! Sets the x-column
            Tensor31& x_column(const Vector3<T>& v)
            {
                xx = v.x;
                yx = v.y;
                zx = v.z;
                return *this;
            }

            //! Sets the x-column
            Tensor31& x_column(T _xx, T _yx, T _zx)
            {
                xx = _xx;
                yx = _yx;
                zx = _zx;
                return *this;
            }

            //! Sets the x-row
            Tensor31& x_row(const Vector1<T>& v)
            {
                xx = v.x;
                return *this;
            }

            //! Sets the x-row
            Tensor31& x_row(T _xx)
            {
                xx = _xx;
                return *this;
            }

            //! Sets the y-row
            Tensor31& y_row(const Vector1<T>& v)
            {
                yx = v.x;
                return *this;
            }

            //! Sets the y-row
            Tensor31& y_row(T _yx)
            {
                yx = _yx;
                return *this;
            }

            //! Sets the z-row
            Tensor31& z_row(const Vector1<T>& v)
            {
                zx = v.x;
                return *this;
            }    

            //! Sets the z-row
            Tensor31& z_row(T _zx)
            {
                zx = _zx;
                return *this;
            }    
    };

    YQ_IEEE754_1(Tensor31)
        
//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Create 3x1 tensor by columns
    */
    template <typename T>
    constexpr Tensor31<T>  columns(const Vector3<T>&x)
    {
        return {
            x.x,
            x.y,
            x.z
        };
    }

    /*! \brief Create 3x1 tensor by rows
    */
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

    //! X-column of given tensor
    template <typename T>
    constexpr Vector3<T>  x_column(const Tensor31<T>&ten) 
    {
        return ten.x_column();
    }

    //! X-row of given tensor
    template <typename T>
    constexpr Vector1<T>  x_row(const Tensor31<T>&ten)
    {
        return ten.x_row();
    }

    //! Y-row of given tensor
    template <typename T>
    constexpr Vector1<T>  y_row(const Tensor31<T>&ten)
    {
        return ten.y_row();
    }

    //! Z-row of given tensor
    template <typename T>
    constexpr Vector1<T>  z_row(const Tensor31<T>&ten)
    {
        return ten.z_row();
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


//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

}

YQ_TYPE_DECLARE(yq::Tensor31D)
YQ_TYPE_DECLARE(yq::Tensor31F)
YQ_TYPE_DECLARE(yq::Tensor31I)
YQ_TYPE_DECLARE(yq::Tensor31U)

