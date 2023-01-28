////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__TENSOR_2_4__HPP 1
#include <math/preamble.hpp>
#include <math/Vector2.hpp>
#include <math/Vector4.hpp>

namespace yq {
    /*! \brief 2x4 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor24 {
    
        //! Component type
        using component_type = T;

        T xx, xy, xz, xw;
        T yx, yy, yz, yw;

        constexpr Tensor24() noexcept = default;

        constexpr Tensor24(
            T _xx, T _xy, T _xz, T _xw,
            T _yx, T _yy, T _yz, T _yw
        ) : 
            xx(_xx), xy(_xy), xz(_xz), xw(_xw),
            yx(_yx), yy(_yy), yz(_yz), yw(_yw)
        {
        }
        
        constexpr Tensor24(columns_t, const Vector2<T>& x, const Vector2<T>& y, const Vector2<T>& z, const Vector2<T>& w) :
            xx(x.x), xy(y.x), xz(z.x), xw(w.x),
            yx(x.y), yy(y.y), yz(z.y), yw(w.y)
        {
        }

        consteval Tensor24(identity_t) : 
            xx(one_v<T>),  xy(zero_v<T>), xz(zero_v<T>), xw(zero_v<T>),
            yx(zero_v<T>), yy(one_v<T>),  yz(zero_v<T>), yw(zero_v<T>)
        {
        }

        constexpr Tensor24(ordered_t,
            T _xx, T _xy, T _xz, T _xw,
            T _yx, T _yy, T _yz, T _yw
        ) : 
            xx(_xx), xy(_xy), xz(_xz), xw(_xw),
            yx(_yx), yy(_yy), yz(_yz), yw(_yw)
        {
        }

        constexpr Tensor24(rows_t, const Vector4<T>& x, const Vector4<T>& y, const Vector4<T>& z, const Vector4<T>& w) :
            xx(x.x), xy(x.y), xz(x.z), xw(x.w),
            yx(y.x), yy(y.y), yz(y.z), yw(y.w)
        {
        }

        consteval Tensor24(zero_t) : 
            xx(zero_v<T>), xy(zero_v<T>), xz(zero_v<T>), xw(zero_v<T>),
            yx(zero_v<T>), yy(zero_v<T>), yz(zero_v<T>), yw(zero_v<T>)
        {
        }

        //! Defaulted equality operator
        constexpr bool operator==(const Tensor24&) const noexcept = default;

        //! Positive (affirmation) operator
        constexpr Tensor24  operator+() const noexcept
        { 
            return *this; 
        }

        //! Negation
        constexpr Tensor24  operator-() const noexcept
        {
            return {
                -xx, -xy, -xz, -xw,
                -yx, -yy, -yz, -yw
            };
        }

        //  --------------------------------------------------------
        //  GETTERS

            //! X-column of this tensor
            constexpr Vector2<T>  x_column() const noexcept 
            {
                return {xx, yx};
            }

            //! Y-column of this tensor
            constexpr Vector2<T>  y_column() const noexcept 
            {
                return {xy, yy};
            }

            //! Z-column of this tensor
            constexpr Vector2<T>  z_column() const noexcept 
            {
                return {xz, yz};
            }

            //! W-column of this tensor
            constexpr Vector2<T>  w_column() const noexcept 
            {
                return {xw, yw};
            }

            //! X-row of this tensor
            constexpr Vector4<T>  x_row() const noexcept 
            {
                return {xx, xy, xz, xw};
            }

            //! Y-row of this tensor
            constexpr Vector4<T>  y_row() const noexcept 
            {
                return {yx, yy, yz, yw};
            }


        //  --------------------------------------------------------
        //  SETTERS

            //! Sets the x-column of this tensor
            Tensor24& x_column(const Vector2<T>& v)
            {
                xx = v.x;
                yx = v.y;
                return *this;
            }

            //! Sets the x-column of this tensor
            Tensor24& x_column(T _xx, T _yx)
            {
                xx = _xx;
                yx = _yx;
                return *this;
            }

            //! Sets the y-column of this tensor
            Tensor24& y_column(const Vector2<T>& v)
            {
                xy = v.x;
                yy = v.y;
                return *this;
            }

            //! Sets the y-column of this tensor
            Tensor24& y_column(T _xy, T _yy)
            {
                xy = _xy;
                yy = _yy;
                return *this;
            }

            //! Sets the z-column of this tensor
            Tensor24& z_column(const Vector2<T>& v)
            {
                xz = v.x;
                yz = v.y;
                return *this;
            }

            //! Sets the z-column of this tensor
            Tensor24& z_column(T _xz, T _yz)
            {
                xz = _xz;
                yz = _yz;
                return *this;
            }

            //! Sets the w-column of this tensor
            Tensor24& w_column(const Vector2<T>& v)
            {
                xw = v.x;
                yw = v.y;
                return *this;
            }

            //! Sets the w-column of this tensor
            Tensor24& w_column(T _xw, T _yw)
            {
                xw = _xw;
                yw = _yw;
                return *this;
            }

            //! Sets the x-row of this tensor
            Tensor24& x_row(const Vector4<T>& v)
            {
                xx = v.x;
                xy = v.y;
                xz = v.z;
                xw = v.w;
                return *this;
            }

            //! Sets the x-row of this tensor
            Tensor24& x_row(T _xx, T _xy, T _xz, T _xw)
            {
                xx = _xx;
                xy = _xy;
                xz = _xz;
                xw = _xw;
                return *this;
            }

            //! Sets the y-row of this tensor
            Tensor24& y_row(const Vector4<T>& v)
            {
                yx = v.x;
                yy = v.y;
                yz = v.z;
                yw = v.w;
                return *this;
            }

            //! Sets the y-row of this tensor
            Tensor24& y_row(T _yx, T _yy, T _yz, T _yw)
            {
                yx = _yx;
                yy = _yy;
                yz = _yz;
                yw = _yw;
                return *this;
            }
    };

    YQ_IEEE754_1(Tensor24)
        
//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Create 2x4 tensor by columns
    */
    template <typename T>
    constexpr Tensor24<T>  columns(const Vector2<T>&x, const Vector2<T>&y, const Vector2<T>&z, const Vector2<T>&w)
    {
        return {
            x.x, y.x, z.x, w.x,
            x.y, y.y, z.y, w.y
        };
    }

    /*! \brief Create 2x4 tensor by rows
    */
    template <typename T>
    constexpr Tensor24<T>  rows(const Vector4<T>&x, const Vector4<T>&y)
    {
        return {
            x.x, x.y, x.z, x.w,
            y.x, y.y, y.z, y.w
        };
    }
    
    YQ_IDENTITY_1(Tensor24, {
        one_v<T>, zero_v<T>, zero_v<T>, zero_v<T>,
        zero_v<T>, one_v<T>, zero_v<T>, zero_v<T>
    })

    YQ_NAN_1(Tensor24, {
        nan_v<T>, nan_v<T>, nan_v<T>, nan_v<T>,
        nan_v<T>, nan_v<T>, nan_v<T>, nan_v<T> 
    })
    
    YQ_ZERO_1(Tensor24, {
        zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>,
        zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T> 
     })
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor24, 
        is_finite(v.xx) && is_finite(v.xy) && is_finite(v.xz) && is_finite(v.xw) &&
        is_finite(v.yx) && is_finite(v.yy) && is_finite(v.yz) && is_finite(v.yw)
    )
    
    YQ_IS_NAN_1(Tensor24,  
        is_nan(v.xx) || is_nan(v.xy) || is_nan(v.xz) || is_nan(v.xw) ||
        is_nan(v.yx) || is_nan(v.yy) || is_nan(v.yz) || is_nan(v.yw)
    )

//  --------------------------------------------------------
//  GETTERS

    //! Gets the x-column of the provided tensor
    template <typename T>
    constexpr Vector2<T>  x_column(const Tensor24<T>&ten) 
    {
        return ten.x_column();
    }

    //! Gets the y-column of the provided tensor
    template <typename T>
    constexpr Vector2<T>  y_column(const Tensor24<T>&ten) 
    {
        return ten.y_column();
    }

    //! Gets the z-column of the provided tensor
    template <typename T>
    constexpr Vector2<T>  z_column(const Tensor24<T>&ten) 
    {
        return ten.z_column();
    }

    //! Gets the w-column of the provided tensor
    template <typename T>
    constexpr Vector2<T>  w_column(const Tensor24<T>&ten) 
    {
        return ten.w_column();
    }

    //! Gets the x-row of the provided tensor
    template <typename T>
    constexpr Vector4<T>  x_row(const Tensor24<T>&ten)
    {
        return ten.x_row();
    }

    //! Gets the y-row of the provided tensor
    template <typename T>
    constexpr Vector4<T>  y_row(const Tensor24<T>&ten)
    {
        return ten.y_row();
    }

//  --------------------------------------------------------
//  ADDITION

    template <typename T>
    constexpr Tensor24<T>   operator+ (const Tensor24<T> &a, const Tensor24<T> &b) 
    {
        return {
            a.xx+b.xx, a.xy+b.xy, a.xz+b.xz, a.xw+b.xw,
            a.yx+b.yx, a.yy+b.yy, a.yz+b.yz, a.yw+b.yw
        };
    }

    template <typename T>
    Tensor24<T>&   operator+=(Tensor24<T> &a, const Tensor24<T> &b) 
    {
        a.xx+=b.xx;  a.xy+=b.xy;  a.xz+=b.xz;  a.xw+=b.xw;
        a.yx+=b.yx;  a.yy+=b.yy;  a.yz+=b.yz;  a.yw+=b.yw;
        return a;
    }


//  --------------------------------------------------------
//  SUBTRACTION

    template <typename T>
    constexpr Tensor24<T>   operator- (const Tensor24<T> &a, const Tensor24<T> &b) 
    {
        return {
            a.xx-b.xx, a.xy-b.xy, a.xz-b.xz, a.xw-b.xw,
            a.yx-b.yx, a.yy-b.yy, a.yz-b.yz, a.yw-b.yw
        };
    }
    

    template <typename T>
    Tensor24<T>&   operator-=(Tensor24<T> &a, const Tensor24<T> &b) 
    {
        a.xx-=b.xx;  a.xy-=b.xy;  a.xz-=b.xz;  a.xw-=b.xw;
        a.yx-=b.yx;  a.yy-=b.yy;  a.yz-=b.yz;  a.yw-=b.yw;
        return a;
    }
    
//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires std::is_arithmetic_v<T>
    constexpr Tensor24<product_t<T,U>>  operator*(T a, const Tensor24<T>& b)
    {
        return {
            a*b.xx, a*b.xy, a*b.xz, a*b.xw,
            a*b.yx, a*b.yy, a*b.yz, a*b.yw
        };
    }
    
    
    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor24<product_t<T,U>>  operator*(const Tensor24<T>& a, U b)
    {
        return {
            a.xx*b, a.xy*b, a.xz*b, a.xw*b,
            a.yx*b, a.yy*b, a.yz*b, a.yw*b
        };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Tensor24<product_t<T,U>>  operator*=(const Tensor24<T>& a, U b)
    {
        a.xx*=b; a.xy*=b; a.xz*=b; a.xw*=b;
        a.yx*=b; a.yy*=b; a.yz*=b; a.yw*=b;        
        return a;
    }

        
    template <typename T, typename U>
    constexpr Vector2<product_t<T,U>> operator*(const Tensor24<T>&a, const Vector4<U>&b)
    {
        return {
            a.xx*b.x + a.xy*b.y + a.xz*b.z + a.xw*b.w,
            a.yx*b.x + a.yy*b.y + a.yz*b.z + a.yw*b.w
        };
    }

//  --------------------------------------------------------
//  DIVISION


    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor24<quotient_t<T,U>>  operator/(const Tensor24<T>& a, U b)
    {
        return {
            a.xx/b, a.xy/b, a.xz/b, a.xw/b,
            a.yx/b, a.yy/b, a.yz/b, a.yw/b
        };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Tensor24<quotient_t<T,U>>  operator/=(const Tensor24<T>& a, U b)
    {
        a.xx/=b; a.xy/=b; a.xz/=b; a.xw/=b;
        a.yx/=b; a.yy/=b; a.yz/=b; a.yw/=b;        
        return a;
    }

//  --------------------------------------------------------
//  OTIMES PRODUCT


//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

}

YQ_TYPE_DECLARE(yq::Tensor24D)
YQ_TYPE_DECLARE(yq::Tensor24F)
YQ_TYPE_DECLARE(yq::Tensor24I)
YQ_TYPE_DECLARE(yq::Tensor24U)

