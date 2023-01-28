////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__TENSOR_4_2__HPP 1
#include <math/preamble.hpp>
#include <math/Vector2.hpp>
#include <math/Vector4.hpp>

namespace yq {
    /*! \brief 4x2 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor42 {
        //! Component type (captures template parameter)
        using component_type = T;
        
        T xx, xy;
        T yx, yy;
        T zx, zy;
        T wx, wy;

        //! Defaulted equality operator
        constexpr bool operator==(const Tensor42&) const noexcept = default;


        //! Positive (affirmation) operator
        constexpr Tensor42<T>  operator+() const noexcept
        { 
            return *this; 
        }


        //! Negation operator
        constexpr Tensor42<T>  operator-() const noexcept
        {
            return {
                -xx, -xy,
                -yx, -yy,
                -zx, -zy,
                -wx, -wy
            };
        }

        //  --------------------------------------------------------
        //  GETTERS

            //! X-column of this tensor
            constexpr Vector4<T>  x_column() const noexcept
            {
                return {xx, yx, zx, wx};
            }

            //! Y-column of this tensor
            constexpr Vector4<T>  y_column() const noexcept
            {
                return {xy, yy, zy, wy};
            }

            //! X-row of this tensor
            constexpr Vector2<T>  x_row() const noexcept
            {
                return {xx, xy};
            }

            //! Y-row of this tensor
            constexpr Vector2<T>  y_row() const noexcept
            {
                return {yx, yy};
            }

            //! Z-row of this tensor
            constexpr Vector2<T>  z_row() const noexcept
            {
                return {zx, zy};
            }

            //! W-row of this tensor
            constexpr Vector2<T>  w_row() const noexcept
            {
                return {wx, wy};
            }


        //  --------------------------------------------------------
        //  SETTERS

            //! Sets x-column
            Tensor42& x_column(const Vector4<T>& v) noexcept
            {
                xx = v.x;
                yx = v.y;
                zx = v.z;
                wx = v.w;
                return *this;
            }

            //! Sets x-column
            Tensor42& x_column(T _xx, T _yx, T _zx, T _wx) noexcept
            {
                xx = _xx;
                yx = _yx;
                zx = _zx;
                wx = _wx;
                return *this;
            }

            //! Sets y-column
            Tensor42& y_column(const Vector4<T>& v) noexcept
            {
                xy = v.x;
                yy = v.y;
                zy = v.z;
                wy = v.w;
                return *this;
            }

            //! Sets y-column
            Tensor42& y_column(T _xy, T _yy, T _zy, T _wy) noexcept
            {
                xy = _xy;
                yy = _yy;
                zy = _zy;
                wy = _wy;
                return *this;
            }

            //! Sets x-row
            Tensor42& x_row(const Vector2<T>& v) noexcept
            {
                xx = v.x;
                xy = v.y;
                return *this;
            }

            //! Sets x-row
            Tensor42& x_row(T _xx, T _xy) noexcept
            {
                xx = _xx;
                xy = _xy;
                return *this;
            }

            //! Sets y-row
            Tensor42& y_row(const Vector2<T>& v) noexcept
            {
                yx = v.x;
                yy = v.y;
                return *this;
            }

            //! Sets y-row
            Tensor42& y_row(T _yx, T _yy) noexcept
            {
                yx = _yx;
                yy = _yy;
                return *this;
            }

            //! Sets z-row
            Tensor42& z_row(const Vector2<T>& v) noexcept
            {
                zx = v.x;
                zy = v.y;
                return *this;
            }

            //! Sets z-row
            Tensor42& z_row(T _zx, T _zy) noexcept
            {
                zx = _zx;
                zy = _zy;
                return *this;
            }

            //! Sets z-row
            Tensor42& w_row(const Vector2<T>& v) noexcept
            {
                wx = v.x;
                wy = v.y;
                return *this;
            }

            //! Sets z-row
            Tensor42& w_row(T _wx, T _wy) noexcept
            {
                wx = _wx;
                wy = _wy;
                return *this;
            }
    };

    YQ_IEEE754_1(Tensor42)
        
//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Create 4x2 tensor by columns
    */
    template <typename T>
    constexpr Tensor42<T>  columns(const Vector4<T>&x, const Vector4<T>&y) noexcept
    {
        return {
            x.x, y.x,
            x.y, y.y,
            x.z, y.z,
            x.w, y.w
        };
    }

    /*! \brief Create 4x2 tensor by rows
    */
    template <typename T>
    constexpr Tensor42<T>  rows(const Vector2<T>&x, const Vector2<T>&y, const Vector2<T>&z, const Vector2<T>&w) noexcept
    {
        return {
            x.x, x.y,
            y.x, y.y,
            z.x, z.y,
            w.x, w.y
        };
    }
    
    YQ_IDENTITY_1(Tensor42, {
        one_v<T>, zero_v<T>,
        zero_v<T>, one_v<T>,
        zero_v<T>, zero_v<T>,
        zero_v<T>, zero_v<T>
    })

    YQ_NAN_1(Tensor42, {
        nan_v<T>, nan_v<T>,
        nan_v<T>, nan_v<T>,
        nan_v<T>, nan_v<T>,
        nan_v<T>, nan_v<T> 
    })
    
    YQ_ZERO_1(Tensor42, {
        zero_v<T>, zero_v<T>,
        zero_v<T>, zero_v<T>,
        zero_v<T>, zero_v<T>,
        zero_v<T>, zero_v<T> 
     })
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor42, 
        is_finite(v.xx) && is_finite(v.xy) &&
        is_finite(v.yx) && is_finite(v.yy) &&
        is_finite(v.zx) && is_finite(v.zy) &&
        is_finite(v.wx) && is_finite(v.wy)
    )
    
    YQ_IS_NAN_1(Tensor42,  
        is_nan(v.xx) || is_nan(v.xy) ||
        is_nan(v.yx) || is_nan(v.yy) ||
        is_nan(v.zx) || is_nan(v.zy) ||
        is_nan(v.wx) || is_nan(v.wy)
    )


//  --------------------------------------------------------
//  GETTERS

    //! X-column of given tensor
    template <typename T>
    constexpr Vector4<T>  x_column(const Tensor42<T>&ten)  noexcept
    {
        return ten.x_column();
    }

    //! Y-column of given tensor
    template <typename T>
    constexpr Vector4<T>  y_column(const Tensor42<T>&ten)  noexcept
    {
        return ten.y_column();
    }

    //! X-row of given tensor
    template <typename T>
    constexpr Vector2<T>  x_row(const Tensor42<T>&ten) noexcept
    {
        return ten.x_row();
    }

    //! Y-row of given tensor
    template <typename T>
    constexpr Vector2<T>  y_row(const Tensor42<T>&ten) noexcept
    {
        return ten.y_row();
    }

    //! Z-row of given tensor
    template <typename T>
    constexpr Vector2<T>  z_row(const Tensor42<T>&ten) noexcept
    {
        return ten.z_row();
    }

    //! W-row of given tensor
    template <typename T>
    constexpr Vector2<T>  w_row(const Tensor42<T>&ten) noexcept
    {
        return ten.w_row();
    }



//  --------------------------------------------------------
//  ADDITION

    template <typename T>
    constexpr Tensor42<T>   operator+ (const Tensor42<T> &a, const Tensor42<T> &b)  noexcept
    {
        return {
            a.xx+b.xx, a.xy+b.xy,
            a.yx+b.yx, a.yy+b.yy,
            a.zx+b.zx, a.zy+b.zy,
            a.wx+b.wx, a.wy+b.wy
        };
    }

    template <typename T>
    Tensor42<T>&   operator+=(Tensor42<T> &a, const Tensor42<T> &b)  noexcept
    {
        a.xx+=b.xx;  a.xy+=b.xy;
        a.yx+=b.yx;  a.yy+=b.yy;
        a.zx+=b.zx;  a.zy+=b.zy;
        a.wx+=b.wx;  a.wy+=b.wy;
        return a;
    }


//  --------------------------------------------------------
//  SUBTRACTION

    template <typename T>
    constexpr Tensor42<T>   operator- (const Tensor42<T> &a, const Tensor42<T> &b)  noexcept
    {
        return {
            a.xx-b.xx, a.xy-b.xy,
            a.yx-b.yx, a.yy-b.yy,
            a.zx-b.zx, a.zy-b.zy,
            a.wx-b.wx, a.wy-b.wy
        };
    }
    

    template <typename T>
    Tensor42<T>&   operator-=(Tensor42<T> &a, const Tensor42<T> &b)  noexcept
    {
        a.xx-=b.xx;  a.xy-=b.xy;
        a.yx-=b.yx;  a.yy-=b.yy;
        a.zx-=b.zx;  a.zy-=b.zy;
        a.wx-=b.wx;  a.wy-=b.wy;
        return a;
    }
    
//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires std::is_arithmetic_v<T>
    constexpr Tensor42<product_t<T,U>>  operator*(T a, const Tensor42<T>& b) noexcept
    {
        return {
            a*b.xx, a*b.xy,
            a*b.yx, a*b.yy,
            a*b.zx, a*b.zy,
            a*b.wx, a*b.wy
        };
    }
    
    
    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor42<product_t<T,U>>  operator*(const Tensor42<T>& a, U b) noexcept
    {
        return {
            a.xx*b, a.xy*b,
            a.yx*b, a.yy*b,
            a.zx*b, a.zy*b,
            a.wx*b, a.wy*b
        };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Tensor42<product_t<T,U>>  operator*=(const Tensor42<T>& a, U b) noexcept
    {
        a.xx*=b; a.xy*=b;
        a.yx*=b; a.yy*=b;
        a.zx*=b; a.zy*=b;
        a.wx*=b; a.wy*=b;        
        return a;
    }

        
    template <typename T, typename U>
    constexpr Vector4<product_t<T,U>> operator*(const Tensor42<T>&a, const Vector2<U>&b) noexcept
    {
        return {
            a.xx*b.x + a.xy*b.y,
            a.yx*b.x + a.yy*b.y,
            a.zx*b.x + a.zy*b.y,
            a.wx*b.x + a.wy*b.y
        };
    }


//  --------------------------------------------------------
//  DIVISION


    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor42<quotient_t<T,U>>  operator/(const Tensor42<T>& a, U b) noexcept
    {
        return {
            a.xx/b, a.xy/b,
            a.yx/b, a.yy/b,
            a.zx/b, a.zy/b,
            a.wx/b, a.wy/b
        };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Tensor42<quotient_t<T,U>>  operator/=(const Tensor42<T>& a, U b) noexcept
    {
        a.xx/=b; a.xy/=b;
        a.yx/=b; a.yy/=b;
        a.zx/=b; a.zy/=b;
        a.wx/=b; a.wy/=b;        
        return a;
    }

//  --------------------------------------------------------
//  OTIMES PRODUCT


//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

}

YQ_TYPE_DECLARE(yq::Tensor42D)
YQ_TYPE_DECLARE(yq::Tensor42F)
YQ_TYPE_DECLARE(yq::Tensor42I)
YQ_TYPE_DECLARE(yq::Tensor42U)

