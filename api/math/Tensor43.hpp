////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__TENSOR_4_3__HPP 1
#include <math/preamble.hpp>
#include <math/Vector3.hpp>
#include <math/Vector4.hpp>

namespace yq {
    /*! \brief 4x3 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor43 {
        //! Component type (captures template parameter)
        using component_type = T;
        
        T xx, xy, xz;
        T yx, yy, yz;
        T zx, zy, zz;
        T wx, wy, wz;

        //! Defaulted equality operator
        constexpr bool operator==(const Tensor43&) const noexcept = default;

        //! Positive (affirmation) operator
        constexpr Tensor43<T>  operator+() const noexcept
        { 
            return *this; 
        }

        //! Negation operator
        constexpr Tensor43<T>  operator-() const noexcept
        {
            return {
                -xx, -xy, -xz,
                -yx, -yy, -yz,
                -zx, -zy, -zz,
                -wx, -wy, -wz
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

            //! Z-column of this tensor
            constexpr Vector4<T>  z_column() const noexcept
            {
                return {xz, yz, zz, wz};
            }

            //! X-row of this tensor
            constexpr Vector3<T>  x_row() const noexcept
            {
                return {xx, xy, xz};
            }

            //! Y-row of this tensor
            constexpr Vector3<T>  y_row() const noexcept
            {
                return {yx, yy, yz};
            }

            //! Z-row of this tensor
            constexpr Vector3<T>  z_row() const noexcept
            {
                return {zx, zy, zz};
            }

            //! W-row of this tensor
            constexpr Vector3<T>  w_row() const noexcept
            {
                return {wx, wy, wz};
            }
    

        //  --------------------------------------------------------
        //  SETTERS

            //! Sets the X-column
            Tensor43& x_column(const Vector4<T>& v) noexcept
            {
                xx = v.x;
                yx = v.y;
                zx = v.z;
                wx = v.w;
                return *this;
            }

            //! Sets the X-column
            Tensor43& x_column(T _xx, T _yx, T _zx, T _wx) noexcept
            {
                xx = _xx;
                yx = _yx;
                zx = _zx;
                wx = _wx;
                return *this;
            }

            //! Sets the Y-column
            Tensor43& y_column(const Vector4<T>& v) noexcept
            {
                xy = v.x;
                yy = v.y;
                zy = v.z;
                wy = v.w;
                return *this;
            }

            //! Sets the Y-column
            Tensor43& y_column(T _xy, T _yy, T _zy, T _wy) noexcept
            {
                xy = _xy;
                yy = _yy;
                zy = _zy;
                wy = _wy;
                return *this;
            }

            //! Sets the Z-column
            Tensor43& z_column(const Vector4<T>& v) noexcept
            {
                xz = v.x;
                yz = v.y;
                zz = v.z;
                wz = v.w;
                return *this;
            }

            //! Sets the Z-column
            Tensor43& z_column(T _xz, T _yz, T _zz, T _wz) noexcept
            {
                xz = _xz;
                yz = _yz;
                zz = _zz;
                wz = _wz;
                return *this;
            }

            //! Sets the X-row
            Tensor43& x_row(const Vector3<T>& v) noexcept
            {
                xx = v.x;
                xy = v.y;
                xz = v.z;
                return *this;
            }

            //! Sets the X-row
            Tensor43& x_row(T _xx, T _xy, T _xz) noexcept
            {
                xx = _xx;
                xy = _xy;
                xz = _xz;
                return *this;
            }

            //! Sets the Y-row
            Tensor43& y_row(const Vector3<T>& v) noexcept
            {
                yx = v.x;
                yy = v.y;
                yz = v.z;
                return *this;
            }

            //! Sets the Y-row
            Tensor43& y_row(T _yx, T _yy, T _yz) noexcept
            {
                yx = _yx;
                yy = _yy;
                yz = _yz;
                return *this;
            }

            //! Sets the Z-row
            Tensor43& z_row(const Vector3<T>& v) noexcept
            {
                zx = v.x;
                zy = v.y;
                zz = v.z;
                return *this;
            }

            //! Sets the Z-row
            Tensor43& z_row(T _zx, T _zy, T _zz) noexcept
            {
                zx = _zx;
                zy = _zy;
                zz = _zz;
                return *this;
            }

            //! Sets the W-row
            Tensor43& w_row(const Vector3<T>& v) noexcept
            {
                wx = v.x;
                wy = v.y;
                wz = v.z;
                return *this;
            }

            //! Sets the W-row
            Tensor43& w_row(T _wx, T _wy, T _wz) noexcept
            {
                wx = _wx;
                wy = _wy;
                wz = _wz;
                return *this;
            }

    };

    YQ_IEEE754_1(Tensor43)
        
//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Creates 4x3 tensor by specifying the columns
    */
    template <typename T>
    constexpr Tensor43<T>  columns(const Vector4<T>&x, const Vector4<T>&y, const Vector4<T>&z) noexcept
    {
        return {
            x.x, y.x, z.x,
            x.y, y.y, z.y,
            x.z, y.z, z.z,
            x.w, y.w, z.w
        };
    }

    /*! \brief Creates 4x3 tensor by specifying the rows
    */
    template <typename T>
    constexpr Tensor43<T>  rows(const Vector3<T>&x, const Vector3<T>&y, const Vector3<T>&z, const Vector3<T>&w) noexcept
    {
        return {
            x.x, x.y, x.z,
            y.x, y.y, y.z,
            z.x, z.y, z.z,
            w.x, w.y, w.z
        };
    }
    
    YQ_IDENTITY_1(Tensor43, {
        one_v<T>, zero_v<T>, zero_v<T>,
        zero_v<T>, one_v<T>, zero_v<T>,
        zero_v<T>, zero_v<T>, one_v<T>,
        zero_v<T>, zero_v<T>, zero_v<T>
    })

    YQ_NAN_1(Tensor43, {
        nan_v<T>, nan_v<T>, nan_v<T>,
        nan_v<T>, nan_v<T>, nan_v<T>,
        nan_v<T>, nan_v<T>, nan_v<T>,
        nan_v<T>, nan_v<T>, nan_v<T> 
    })
    
    YQ_ZERO_1(Tensor43, {
        zero_v<T>, zero_v<T>, zero_v<T>,
        zero_v<T>, zero_v<T>, zero_v<T>,
        zero_v<T>, zero_v<T>, zero_v<T>,
        zero_v<T>, zero_v<T>, zero_v<T> 
     })
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor43, 
        is_finite(v.xx) && is_finite(v.xy) && is_finite(v.xz) &&
        is_finite(v.yx) && is_finite(v.yy) && is_finite(v.yz) &&
        is_finite(v.zx) && is_finite(v.zy) && is_finite(v.zz) &&
        is_finite(v.wx) && is_finite(v.wy) && is_finite(v.wz)
    )
    
    YQ_IS_NAN_1(Tensor43,  
        is_nan(v.xx) || is_nan(v.xy) || is_nan(v.xz) ||
        is_nan(v.yx) || is_nan(v.yy) || is_nan(v.yz) ||
        is_nan(v.zx) || is_nan(v.zy) || is_nan(v.zz) ||
        is_nan(v.wx) || is_nan(v.wy) || is_nan(v.wz)
    )

//  --------------------------------------------------------
//  GETTERS

    //! X-column of given tensor
    template <typename T>
    constexpr Vector4<T>  x_column(const Tensor43<T>&ten)  noexcept
    {
        return ten.x_column();
    }

    //! Y-column of given tensor
    template <typename T>
    constexpr Vector4<T>  y_column(const Tensor43<T>&ten)  noexcept
    {
        return ten.y_column();
    }

    //! Z-column of given tensor
    template <typename T>
    constexpr Vector4<T>  z_column(const Tensor43<T>&ten)  noexcept
    {
        return ten.z_column();
    }

    //! X-row of given tensor
    template <typename T>
    constexpr Vector3<T>  x_row(const Tensor43<T>&ten) noexcept
    {
        return ten.x_row();
    }

    //! Y-row of given tensor
    template <typename T>
    constexpr Vector3<T>  y_row(const Tensor43<T>&ten) noexcept
    {
        return ten.y_row();
    }

    //! Z-row of given tensor
    template <typename T>
    constexpr Vector3<T>  z_row(const Tensor43<T>&ten) noexcept
    {
        return ten.z_row();
    }

    //! W-row of given tensor
    template <typename T>
    constexpr Vector3<T>  w_row(const Tensor43<T>&ten) noexcept
    {
        return ten.w_row();
    }



//  --------------------------------------------------------
//  ADDITION

    template <typename T>
    constexpr Tensor43<T>   operator+ (const Tensor43<T> &a, const Tensor43<T> &b)  noexcept
    {
        return {
            a.xx+b.xx, a.xy+b.xy, a.xz+b.xz,
            a.yx+b.yx, a.yy+b.yy, a.yz+b.yz,
            a.zx+b.zx, a.zy+b.zy, a.zz+b.zz,
            a.wx+b.wx, a.wy+b.wy, a.wz+b.wz
        };
    }

    template <typename T>
    Tensor43<T>&   operator+=(Tensor43<T> &a, const Tensor43<T> &b)  noexcept
    {
        a.xx+=b.xx;  a.xy+=b.xy;  a.xz+=b.xz;
        a.yx+=b.yx;  a.yy+=b.yy;  a.yz+=b.yz;
        a.zx+=b.zx;  a.zy+=b.zy;  a.zz+=b.zz;
        a.wx+=b.wx;  a.wy+=b.wy;  a.wz+=b.wz;
        return a;
    }


//  --------------------------------------------------------
//  SUBTRACTION

    template <typename T>
    constexpr Tensor43<T>   operator- (const Tensor43<T> &a, const Tensor43<T> &b)  noexcept
    {
        return {
            a.xx-b.xx, a.xy-b.xy, a.xz-b.xz,
            a.yx-b.yx, a.yy-b.yy, a.yz-b.yz,
            a.zx-b.zx, a.zy-b.zy, a.zz-b.zz,
            a.wx-b.wx, a.wy-b.wy, a.wz-b.wz
        };
    }
    

    template <typename T>
    Tensor43<T>&   operator-=(Tensor43<T> &a, const Tensor43<T> &b)  noexcept
    {
        a.xx-=b.xx;  a.xy-=b.xy;  a.xz-=b.xz;
        a.yx-=b.yx;  a.yy-=b.yy;  a.yz-=b.yz;
        a.zx-=b.zx;  a.zy-=b.zy;  a.zz-=b.zz;
        a.wx-=b.wx;  a.wy-=b.wy;  a.wz-=b.wz;
        return a;
    }
    
//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires std::is_arithmetic_v<T>
    constexpr Tensor43<product_t<T,U>>  operator*(T a, const Tensor43<T>& b) noexcept
    {
        return {
            a*b.xx, a*b.xy, a*b.xz,
            a*b.yx, a*b.yy, a*b.yz,
            a*b.zx, a*b.zy, a*b.zz,
            a*b.wx, a*b.wy, a*b.wz
        };
    }
    
    
    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor43<product_t<T,U>>  operator*(const Tensor43<T>& a, U b) noexcept
    {
        return {
            a.xx*b, a.xy*b, a.xz*b,
            a.yx*b, a.yy*b, a.yz*b,
            a.zx*b, a.zy*b, a.zz*b,
            a.wx*b, a.wy*b, a.wz*b
        };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Tensor43<product_t<T,U>>  operator*=(const Tensor43<T>& a, U b) noexcept
    {
        a.xx*=b; a.xy*=b; a.xz*=b;
        a.yx*=b; a.yy*=b; a.yz*=b;
        a.zx*=b; a.zy*=b; a.zz*=b;
        a.wx*=b; a.wy*=b; a.wz*=b;        
        return a;
    }

        
    template <typename T, typename U>
    constexpr Vector4<product_t<T,U>> operator*(const Tensor43<T>&a, const Vector3<U>&b) noexcept
    {
        return {
            a.xx*b.x + a.xy*b.y + a.xz*b.z,
            a.yx*b.x + a.yy*b.y + a.yz*b.z,
            a.zx*b.x + a.zy*b.y + a.zz*b.z,
            a.wx*b.x + a.wy*b.y + a.wz*b.z
        };
    }


//  --------------------------------------------------------
//  DIVISION


    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor43<quotient_t<T,U>>  operator/(const Tensor43<T>& a, U b) noexcept
    {
        return {
            a.xx/b, a.xy/b, a.xz/b,
            a.yx/b, a.yy/b, a.yz/b,
            a.zx/b, a.zy/b, a.zz/b,
            a.wx/b, a.wy/b, a.wz/b
        };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Tensor43<quotient_t<T,U>>  operator/=(const Tensor43<T>& a, U b) noexcept
    {
        a.xx/=b; a.xy/=b; a.xz/=b;
        a.yx/=b; a.yy/=b; a.yz/=b;
        a.zx/=b; a.zy/=b; a.zz/=b;
        a.wx/=b; a.wy/=b; a.wz/=b;        
        return a;
    }

//  --------------------------------------------------------
//  OTIMES PRODUCT


//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

}

YQ_TYPE_DECLARE(yq::Tensor43D)
YQ_TYPE_DECLARE(yq::Tensor43F)
YQ_TYPE_DECLARE(yq::Tensor43I)
YQ_TYPE_DECLARE(yq::Tensor43U)

