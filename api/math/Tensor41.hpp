////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__TENSOR_4_1__HPP 1
#include <math/preamble.hpp>
#include <math/Vector1.hpp>
#include <math/Vector4.hpp>

namespace yq {
    /*! \brief 4x1 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor41 {
    
        //! Component type
        using component_type = T;
        
        T xx;
        T yx;
        T zx;
        T wx;

        //! Defaulted equality operator
        constexpr bool operator==(const Tensor41&) const noexcept = default;


        //  --------------------------------------------------------
        //  POSITIVE

            //! Positive (affirmation) operator
            constexpr Tensor41<T>  operator+() const noexcept
            { 
                return *this; 
            }


        //  --------------------------------------------------------
        //  NEGATIVE

            //! Negation operator
            constexpr Tensor41<T>  operator-() const noexcept
            {
                return {
                    -xx,
                    -yx,
                    -zx,
                    -wx
                };
            }

        //  --------------------------------------------------------
        //  GETTERS

            //! X column of this tensor
            constexpr Vector4<T>  x_column() const noexcept
            {
                return {xx, yx, zx, wx};
            }

            //! X row of this tensor
            constexpr Vector1<T>  x_row() const noexcept
            {
                return {xx};
            }

            //! Y row of this tensor
            constexpr Vector1<T>  y_row() const noexcept
            {
                return {yx};
            }

            //! Z row of this tensor
            constexpr Vector1<T>  z_row() const noexcept
            {
                return {zx};
            }

            //! W row of this tensor
            constexpr Vector1<T>  w_row() const noexcept
            {
                return {wx};
            }


        //  --------------------------------------------------------
        //  SETTERS

            //! Sets the X-column
            Tensor41& x_column(const Vector4<T>& v) noexcept
            {
                xx = v.x;
                yx = v.y;
                zx = v.z;
                wx = v.w;
                return *this;
            }

            //! Sets the X-column
            Tensor41& x_column(T _xx, T _yx, T _zx, T _wx) noexcept
            {
                xx = _xx;
                yx = _yx;
                zx = _zx;
                wx = _wx;
                return *this;
            }

            //! Sets the X-row
            Tensor41& x_row(const Vector1<T>& v) noexcept
            {
                xx = v.x;
                return *this;
            }

            //! Sets the X-row
            Tensor41& x_row(T _xx) noexcept
            {
                xx = _xx;
                return *this;
            }

            //! Sets the Y-row
            Tensor41& y_row(const Vector1<T>& v) noexcept
            {
                yx = v.x;
                return *this;
            }

            //! Sets the Y-row
            Tensor41& y_row(T _yx) noexcept
            {
                yx = _yx;
                return *this;
            }

            //! Sets the Z-row
            Tensor41& z_row(const Vector1<T>& v) noexcept
            {
                zx = v.x;
                return *this;
            }

            //! Sets the Z-row
            Tensor41& z_row(T _zx) noexcept
            {
                zx = _zx;
                return *this;
            }

            //! Sets the W-row
            Tensor41& w_row(const Vector1<T>& v) noexcept
            {
                wx = v.x;
                return *this;
            }

            //! Sets the W-row
            Tensor41& w_row(T _wx) noexcept
            {
                wx = _wx;
                return *this;
            }
    };

    YQ_IEEE754_1(Tensor41)
        
//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Create 4x1 tensor by columns
    */
    template <typename T>
    constexpr Tensor41<T>  columns(const Vector4<T>&x) noexcept
    {
        return {
            x.x,
            x.y,
            x.z,
            x.w
        };
    }

    /*! \brief Create 4x1 tensor by rows
    */
    template <typename T>
    constexpr Tensor41<T>  rows(const Vector1<T>&x, const Vector1<T>&y, const Vector1<T>&z, const Vector1<T>&w) noexcept
    {
        return {
            x.x,
            y.x,
            z.x,
            w.x
        };
    }
    
    YQ_IDENTITY_1(Tensor41, {
        one_v<T>,
        zero_v<T>,
        zero_v<T>,
        zero_v<T>
    })

    YQ_NAN_1(Tensor41, {
        nan_v<T>,
        nan_v<T>,
        nan_v<T>,
        nan_v<T> 
    })
    
    YQ_ZERO_1(Tensor41, {
        zero_v<T>,
        zero_v<T>,
        zero_v<T>,
        zero_v<T> 
     })
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor41, 
        is_finite(v.xx) &&
        is_finite(v.yx) &&
        is_finite(v.zx) &&
        is_finite(v.wx)
    )
    
    YQ_IS_NAN_1(Tensor41,  
        is_nan(v.xx) ||
        is_nan(v.yx) ||
        is_nan(v.zx) ||
        is_nan(v.wx)
    )

//  --------------------------------------------------------
//  GETTERS

    //! X-column of given tensor
    template <typename T>
    constexpr Vector4<T>  x_column(const Tensor41<T>&ten)  noexcept
    {
        return ten.x_column();
    }

    //! X-row of given tensor
    template <typename T>
    constexpr Vector1<T>  x_row(const Tensor41<T>&ten)  noexcept
    {
        return ten.x_row();
    }

    //! Y-row of given tensor
    template <typename T>
    constexpr Vector1<T>  y_row(const Tensor41<T>&ten) noexcept
    {
        return ten.y_row();
    }

    //! Z-row of given tensor
    template <typename T>
    constexpr Vector1<T>  z_row(const Tensor41<T>&ten) noexcept
    {
        return ten.z_row();
    }

    //! W-row of given tensor
    template <typename T>
    constexpr Vector1<T>  w_row(const Tensor41<T>&ten) noexcept
    {
        return ten.w_row();
    }



//  --------------------------------------------------------
//  ADDITION

    template <typename T>
    constexpr Tensor41<T>   operator+ (const Tensor41<T> &a, const Tensor41<T> &b)  noexcept
    {
        return {
            a.xx+b.xx,
            a.yx+b.yx,
            a.zx+b.zx,
            a.wx+b.wx
        };
    }

    template <typename T>
    Tensor41<T>&   operator+=(Tensor41<T> &a, const Tensor41<T> &b)  noexcept
    {
        a.xx+=b.xx;
        a.yx+=b.yx;
        a.zx+=b.zx;
        a.wx+=b.wx;
        return a;
    }


//  --------------------------------------------------------
//  SUBTRACTION

    template <typename T>
    constexpr Tensor41<T>   operator- (const Tensor41<T> &a, const Tensor41<T> &b)  noexcept
    {
        return {
            a.xx-b.xx,
            a.yx-b.yx,
            a.zx-b.zx,
            a.wx-b.wx
        };
    }
    

    template <typename T>
    Tensor41<T>&   operator-=(Tensor41<T> &a, const Tensor41<T> &b) noexcept
    {
        a.xx-=b.xx;
        a.yx-=b.yx;
        a.zx-=b.zx;
        a.wx-=b.wx;
        return a;
    }
    
//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires std::is_arithmetic_v<T>
    constexpr Tensor41<product_t<T,U>>  operator*(T a, const Tensor41<T>& b) noexcept
    {
        return {
            a*b.xx,
            a*b.yx,
            a*b.zx,
            a*b.wx
        };
    }
    
    
    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor41<product_t<T,U>>  operator*(const Tensor41<T>& a, U b) noexcept
    {
        return {
            a.xx*b,
            a.yx*b,
            a.zx*b,
            a.wx*b
        };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Tensor41<product_t<T,U>>  operator*=(const Tensor41<T>& a, U b) noexcept
    {
        a.xx*=b;
        a.yx*=b;
        a.zx*=b;
        a.wx*=b;        
        return a;
    }

        
    template <typename T, typename U>
    constexpr Vector4<product_t<T,U>> operator*(const Tensor41<T>&a, const Vector1<U>&b) noexcept
    {
        return {
            a.xx*b.x,
            a.yx*b.x,
            a.zx*b.x,
            a.wx*b.x
        };
    }

//  --------------------------------------------------------
//  DIVISION


    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor41<quotient_t<T,U>>  operator/(const Tensor41<T>& a, U b) noexcept
    {
        return {
            a.xx/b,
            a.yx/b,
            a.zx/b,
            a.wx/b
        };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Tensor41<quotient_t<T,U>>  operator/=(const Tensor41<T>& a, U b) noexcept
    {
        a.xx/=b;
        a.yx/=b;
        a.zx/=b;
        a.wx/=b;        
        return a;
    }

//  --------------------------------------------------------
//  OTIMES PRODUCT


//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

}

YQ_TYPE_DECLARE(yq::Tensor41D)
YQ_TYPE_DECLARE(yq::Tensor41F)
YQ_TYPE_DECLARE(yq::Tensor41I)
YQ_TYPE_DECLARE(yq::Tensor41U)

