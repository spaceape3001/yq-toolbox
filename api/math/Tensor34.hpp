////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__TENSOR_3_4__HPP 1
#include <math/preamble.hpp>
#include <math/Vector3.hpp>
#include <math/Vector4.hpp>

namespace yq {
    /*! \brief 3x4 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor34 {
        //! Component type (captures template parameter)
        using component_type = T;
        
        T xx, xy, xz, xw;
        T yx, yy, yz, yw;
        T zx, zy, zz, zw;

        constexpr Tensor34() noexcept = default;

        constexpr Tensor34(
            T _xx, T _xy, T _xz, T _xw,
            T _yx, T _yy, T _yz, T _yw,
            T _zx, T _zy, T _zz, T _zw
        ) : 
            xx(_xx), xy(_xy), xz(_xz), xw(_xw),
            yx(_yx), yy(_yy), yz(_yz), yw(_yw),
            zx(_zx), zy(_zy), zz(_zz), zw(_zw)
        {
        }
        
        constexpr Tensor34(columns_t, const Vector3<T>& x, const Vector3<T>& y, const Vector3<T>& z, const Vector3<T>& w) :
            xx(x.x), xy(y.x), xz(z.x), xw(w.x),
            yx(x.y), yy(y.y), yz(z.y), yw(w.y),
            zx(x.z), zy(y.z), zz(z.z), zw(w.z)
        {
        }

        consteval Tensor34(identity_t) : 
            xx(one_v<T>),  xy(zero_v<T>), xz(zero_v<T>), xw(zero_v<T>),
            yx(zero_v<T>), yy(one_v<T>),  yz(zero_v<T>), yw(zero_v<T>),
            zx(zero_v<T>), zy(zero_v<T>), zz(one_v<T>),  zw(zero_v<T>)
        {
        }

        constexpr Tensor34(ordered_t,
            T _xx, T _xy, T _xz, T _xw,
            T _yx, T _yy, T _yz, T _yw,
            T _zx, T _zy, T _zz, T _zw
        ) : 
            xx(_xx), xy(_xy), xz(_xz), xw(_xw),
            yx(_yx), yy(_yy), yz(_yz), yw(_yw),
            zx(_zx), zy(_zy), zz(_zz), zw(_zw)
        {
        }

        constexpr Tensor34(rows_t, const Vector4<T>& x, const Vector4<T>& y, const Vector4<T>& z, const Vector4<T>& w) :
            xx(x.x), xy(x.y), xz(x.z), xw(x.w),
            yx(y.x), yy(y.y), yz(y.z), yw(y.w),
            zx(z.x), zy(z.y), zz(z.z), zw(z.w)
        {
        }

        consteval Tensor34(zero_t) : 
            xx(zero_v<T>), xy(zero_v<T>), xz(zero_v<T>), xw(zero_v<T>),
            yx(zero_v<T>), yy(zero_v<T>), yz(zero_v<T>), yw(zero_v<T>),
            zx(zero_v<T>), zy(zero_v<T>), zz(zero_v<T>), zw(zero_v<T>)
        {
        }

        //! Defaulted equality operator
        constexpr bool operator==(const Tensor34&) const noexcept = default;

        //! Positive (affirmation) operator
        constexpr Tensor34<T>  operator+() const noexcept
        { 
            return *this; 
        }

        //! Negation operator
        constexpr Tensor34<T>  operator-() const noexcept
        {
            return Tensor34<T>(
                -xx, -xy, -xz, -xw,
                -yx, -yy, -yz, -yw,
                -zx, -zy, -zz, -zw
            );
        }

        //  --------------------------------------------------------
        //  GETTERS

            //! X-column of this tensor
            constexpr Vector3<T>  x_column() const noexcept
            {
                return Vector3<T>(xx, yx, zx);
            }

            //! Y-column of this tensor
            constexpr Vector3<T>  y_column() const noexcept
            {
                return Vector3<T>(xy, yy, zy);
            }

            //! Z-column of this tensor
            constexpr Vector3<T>  z_column() const noexcept
            {
                return Vector3<T>(xz, yz, zz);
            }

            //! W-column of this tensor
            constexpr Vector3<T>  w_column() const noexcept
            {
                return Vector3<T>(xw, yw, zw);
            }

            //! X-row of this tensor
            constexpr Vector4<T>  x_row() const noexcept
            {
                return Vector4<T>(xx, xy, xz, xw);
            }

            //! Y-row of this tensor
            constexpr Vector4<T>  y_row() const noexcept
            {
                return Vector4<T>(yx, yy, yz, yw);
            }

            //! Z-row of this tensor
            constexpr Vector4<T>  z_row() const noexcept
            {
                return Vector4<T>(zx, zy, zz, zw);
            }


        //  --------------------------------------------------------
        //  SETTERS

            //! Sets the X-column
            Tensor34<T>& x_column(const Vector4<T>& v) noexcept
            {
                xx = v.x;
                yx = v.y;
                zx = v.z;
                return *this;
            }

            //! Sets the X-column
            Tensor34<T>& x_column(T _xx, T _yx, T _zx) noexcept
            {
                xx = _xx;
                yx = _yx;
                zx = _zx;
                return *this;
            }

            //! Sets the Y-column
            Tensor34<T>& y_column(const Vector4<T>& v) noexcept
            {
                xy = v.x;
                yy = v.y;
                zy = v.z;
                return *this;
            }

            //! Sets the Y-column
            Tensor34<T>& y_column(T _xy, T _yy, T _zy) noexcept
            {
                xy = _xy;
                yy = _yy;
                zy = _zy;
                return *this;
            }

            //! Sets the Z-column
            Tensor34<T>& z_column(const Vector4<T>& v) noexcept
            {
                xz = v.x;
                yz = v.y;
                zz = v.z;
                return *this;
            }

            //! Sets the Z-column
            Tensor34<T>& z_column(T _xz, T _yz, T _zz) noexcept
            {
                xz = _xz;
                yz = _yz;
                zz = _zz;
                return *this;
            }

            //! Sets the W-column
            Tensor34<T>& w_column(const Vector4<T>& v) noexcept
            {
                xw = v.x;
                yw = v.y;
                zw = v.z;
                return *this;
            }

            //! Sets the W-column
            Tensor34<T>& w_column(T _xw, T _yw, T _zw) noexcept
            {
                xw = _xw;
                yw = _yw;
                zw = _zw;
                return *this;
            }

            //! Sets the X-row
            Tensor34<T>& x_row(const Vector3<T>& v) noexcept
            {
                xx = v.x;
                xy = v.y;
                xz = v.z;
                xw = v.w;
                return *this;
            }

            //! Sets the X-row
            Tensor34<T>& x_row(T _xx, T _xy, T _xz, T _xw) noexcept
            {
                xx = _xx;
                xy = _xy;
                xz = _xz;
                xw = _xw;
                return *this;
            }

            //! Sets the Y-row
            Tensor34<T>& y_row(const Vector3<T>& v) noexcept
            {
                yx = v.x;
                yy = v.y;
                yz = v.z;
                yw = v.w;
                return *this;
            }

            //! Sets the Y-row
            Tensor34<T>& y_row(T _yx, T _yy, T _yz, T _yw) noexcept
            {
                yx = _yx;
                yy = _yy;
                yz = _yz;
                yw = _yw;
                return *this;
            }

            //! Sets the Z-row
            Tensor34<T>& z_row(const Vector3<T>& v) noexcept
            {
                zx = v.x;
                zy = v.y;
                zz = v.z;
                zw = v.w;
                return *this;
            }

            //! Sets the Z-row
            Tensor34<T>& z_row(T _zx, T _zy, T _zz, T _zw) noexcept
            {
                zx = _zx;
                zy = _zy;
                zz = _zz;
                zw = _zw;
                return *this;
            }
    };

    YQ_IEEE754_1(Tensor34)
        
//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Create 3x4 tensor by columns
    */
    template <typename T>
    constexpr Tensor34<T>  columns(const Vector3<T>&x, const Vector3<T>&y, const Vector3<T>&z, const Vector3<T>&w) noexcept
    {
        return Tensor34<T>(columns_, x, y, z, w);
    }

    /*! \brief Create 3x4 tensor by rows
    */
    template <typename T>
    constexpr Tensor34<T>  rows(const Vector4<T>&x, const Vector4<T>&y, const Vector4<T>&z) noexcept
    {
        return Tensor34<T>(rows_, x, y, z);
    }
    
    YQ_IDENTITY_1(Tensor34, {
        one_v<T>, zero_v<T>, zero_v<T>, zero_v<T>,
        zero_v<T>, one_v<T>, zero_v<T>, zero_v<T>,
        zero_v<T>, zero_v<T>, one_v<T>, zero_v<T>
    })

    YQ_NAN_1(Tensor34, {
        nan_v<T>, nan_v<T>, nan_v<T>, nan_v<T>,
        nan_v<T>, nan_v<T>, nan_v<T>, nan_v<T>,
        nan_v<T>, nan_v<T>, nan_v<T>, nan_v<T> 
    })
    
    YQ_ZERO_1(Tensor34, {
        zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>,
        zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>,
        zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T> 
     })
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor34, 
        is_finite(v.xx) && is_finite(v.xy) && is_finite(v.xz) && is_finite(v.xw) &&
        is_finite(v.yx) && is_finite(v.yy) && is_finite(v.yz) && is_finite(v.yw) &&
        is_finite(v.zx) && is_finite(v.zy) && is_finite(v.zz) && is_finite(v.zw)
    )
    
    YQ_IS_NAN_1(Tensor34,  
        is_nan(v.xx) || is_nan(v.xy) || is_nan(v.xz) || is_nan(v.xw) ||
        is_nan(v.yx) || is_nan(v.yy) || is_nan(v.yz) || is_nan(v.yw) ||
        is_nan(v.zx) || is_nan(v.zy) || is_nan(v.zz) || is_nan(v.zw)
    )

//  --------------------------------------------------------
//  GETTERS

    //! X-column of given tensor
    template <typename T>
    constexpr Vector3<T>  x_column(const Tensor34<T>&ten)  noexcept
    {
        return ten.x_column();
    }

    //! Y-column of given tensor
    template <typename T>
    constexpr Vector3<T>  y_column(const Tensor34<T>&ten) noexcept
    {
        return ten.y_column();
    }

    //! Z-column of given tensor
    template <typename T>
    constexpr Vector3<T>  z_column(const Tensor34<T>&ten)  noexcept
    {
        return ten.z_column();
    }

    //! W-column of given tensor
    template <typename T>
    constexpr Vector3<T>  w_column(const Tensor34<T>&ten)  noexcept
    {
        return ten.w_column();
    }

    //! X-row of given tensor
    template <typename T>
    constexpr Vector4<T>  x_row(const Tensor34<T>&ten) noexcept
    {
        return ten.x_row();
    }

    //! Y-row of given tensor
    template <typename T>
    constexpr Vector4<T>  y_row(const Tensor34<T>&ten) noexcept
    {
        return ten.y_row();
    }

    //! Z-row of given tensor
    template <typename T>
    constexpr Vector4<T>  z_row(const Tensor34<T>&ten) noexcept
    {
        return ten.z_row();
    }



//  --------------------------------------------------------
//  ADDITION

    template <typename T>
    constexpr Tensor34<T>   operator+ (const Tensor34<T> &a, const Tensor34<T> &b)  noexcept
    {
        return Tensor34<T>(
            a.xx+b.xx, a.xy+b.xy, a.xz+b.xz, a.xw+b.xw,
            a.yx+b.yx, a.yy+b.yy, a.yz+b.yz, a.yw+b.yw,
            a.zx+b.zx, a.zy+b.zy, a.zz+b.zz, a.zw+b.zw
        );
    }

    template <typename T>
    Tensor34<T>&   operator+=(Tensor34<T> &a, const Tensor34<T> &b)  noexcept
    {
        a.xx+=b.xx;  a.xy+=b.xy;  a.xz+=b.xz;  a.xw+=b.xw;
        a.yx+=b.yx;  a.yy+=b.yy;  a.yz+=b.yz;  a.yw+=b.yw;
        a.zx+=b.zx;  a.zy+=b.zy;  a.zz+=b.zz;  a.zw+=b.zw;
        return a;
    }


//  --------------------------------------------------------
//  SUBTRACTION

    template <typename T>
    constexpr Tensor34<T>   operator- (const Tensor34<T> &a, const Tensor34<T> &b)  noexcept
    {
        return Tensor34<T>(
            a.xx-b.xx, a.xy-b.xy, a.xz-b.xz, a.xw-b.xw,
            a.yx-b.yx, a.yy-b.yy, a.yz-b.yz, a.yw-b.yw,
            a.zx-b.zx, a.zy-b.zy, a.zz-b.zz, a.zw-b.zw
        );
    }
    

    template <typename T>
    Tensor34<T>&   operator-=(Tensor34<T> &a, const Tensor34<T> &b)  noexcept
    {
        a.xx-=b.xx;  a.xy-=b.xy;  a.xz-=b.xz;  a.xw-=b.xw;
        a.yx-=b.yx;  a.yy-=b.yy;  a.yz-=b.yz;  a.yw-=b.yw;
        a.zx-=b.zx;  a.zy-=b.zy;  a.zz-=b.zz;  a.zw-=b.zw;
        return a;
    }
    
//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires std::is_arithmetic_v<T>
    constexpr Tensor34<product_t<T,U>>  operator*(T a, const Tensor34<U>& b) noexcept
    {
        return Tensor34<product_t<T,U>>(
            a*b.xx, a*b.xy, a*b.xz, a*b.xw,
            a*b.yx, a*b.yy, a*b.yz, a*b.yw,
            a*b.zx, a*b.zy, a*b.zz, a*b.zw
        );
    }
    
    
    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor34<product_t<T,U>>  operator*(const Tensor34<T>& a, U b) noexcept
    {
        return Tensor34<product_t<T,U>>(
            a.xx*b, a.xy*b, a.xz*b, a.xw*b,
            a.yx*b, a.yy*b, a.yz*b, a.yw*b,
            a.zx*b, a.zy*b, a.zz*b, a.zw*b
        );
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Tensor34<product_t<T,U>>  operator*=(const Tensor34<T>& a, U b) noexcept
    {
        a.xx*=b; a.xy*=b; a.xz*=b; a.xw*=b;
        a.yx*=b; a.yy*=b; a.yz*=b; a.yw*=b;
        a.zx*=b; a.zy*=b; a.zz*=b; a.zw*=b;        
        return a;
    }

        
    template <typename T, typename U>
    constexpr Vector3<product_t<T,U>> operator*(const Tensor34<T>&a, const Vector4<U>&b) noexcept
    {
        return Vector3<product_t<T,U>>(
            a.xx*b.x + a.xy*b.y + a.xz*b.z + a.xw*b.w,
            a.yx*b.x + a.yy*b.y + a.yz*b.z + a.yw*b.w,
            a.zx*b.x + a.zy*b.y + a.zz*b.z + a.zw*b.w
        );
    }

    template <typename T, typename U>
    constexpr Vector4<product_t<T,U>> operator*(const Vector3<T>&a, const Tensor34<U>&b) noexcept
    {
        return Vector4<product_t<T,U>>(
            a.x*b.xx + a.y*b.yx + a.z*b.zx,
            a.x*b.xy + a.y*b.yy + a.z*b.zy,
            a.x*b.xz + a.y*b.yz + a.z*b.zz,
            a.x*b.xw + a.y*b.yw + a.z*b.zw
        );
    }

//  --------------------------------------------------------
//  DIVISION


    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor34<quotient_t<T,U>>  operator/(const Tensor34<T>& a, U b) noexcept
    {
        return Tensor34<quotient_t<T,U>>(
            a.xx/b, a.xy/b, a.xz/b, a.xw/b,
            a.yx/b, a.yy/b, a.yz/b, a.yw/b,
            a.zx/b, a.zy/b, a.zz/b, a.zw/b
        );
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Tensor34<quotient_t<T,U>>  operator/=(const Tensor34<T>& a, U b) noexcept
    {
        a.xx/=b; a.xy/=b; a.xz/=b; a.xw/=b;
        a.yx/=b; a.yy/=b; a.yz/=b; a.yw/=b;
        a.zx/=b; a.zy/=b; a.zz/=b; a.zw/=b;        
        return a;
    }

//  --------------------------------------------------------
//  OTIMES PRODUCT

    template <typename T, typename U>
    constexpr Tensor34<product_t<T,U>> operator OTIMES(const Vector3<T>&a, const Vector4<U>&b) noexcept
    {
        return Tensor34<product_t<T,U>>(
            a.x+b.x, a.x+b.y, a.x+b.z, a.x+b.w,
            a.y+b.x, a.y+b.y, a.y+b.z, a.y+b.w,
            a.z+b.x, a.z+b.y, a.z+b.z, a.z+b.w
        );
    }

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

}

YQ_TYPE_DECLARE(yq::Tensor34D)
YQ_TYPE_DECLARE(yq::Tensor34F)
YQ_TYPE_DECLARE(yq::Tensor34I)
YQ_TYPE_DECLARE(yq::Tensor34U)

