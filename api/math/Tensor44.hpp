////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__TENSOR_4_4__HPP 1
#include <math/preamble.hpp>
#include <math/Vector4.hpp>

namespace yq {
    /*! \brief 4x4 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor44 {
        //! Component type
        using component_type = T;
        
        T xx, xy, xz, xw;
        T yx, yy, yz, yw;
        T zx, zy, zz, zw;
        T wx, wy, wz, ww;


        constexpr Tensor44() noexcept = default;

        constexpr Tensor44(
            T _xx, T _xy, T _xz, T _xw,
            T _yx, T _yy, T _yz, T _yw,
            T _zx, T _zy, T _zz, T _zw,
            T _wx, T _wy, T _wz, T _ww
        ) : 
            xx(_xx), xy(_xy), xz(_xz), xw(_xw),
            yx(_yx), yy(_yy), yz(_yz), yw(_yw),
            zx(_zx), zy(_zy), zz(_zz), zw(_zw),
            wx(_wx), wy(_wy), wz(_wz), ww(_ww)
        {
        }
        
        constexpr Tensor44(columns_t, const Vector4<T>& x, const Vector4<T>& y, const Vector4<T>& z, const Vector4<T>& w) :
            xx(x.x), xy(y.x), xz(z.x), xw(w.x),
            yx(x.y), yy(y.y), yz(z.y), yw(w.y),
            zx(x.z), zy(y.z), zz(z.z), zw(w.z),
            wx(x.w), wy(y.w), wz(z.w), ww(w.w)
        {
        }

        constexpr Tensor44(diagonal_t, T _xx, T _yy, T _zz, T _ww) : 
            xx(_xx),  xy(zero_v<T>), xz(zero_v<T>), xw(zero_v<T>),
            yx(zero_v<T>), yy(_yy),  yz(zero_v<T>), yw(zero_v<T>),
            zx(zero_v<T>), zy(zero_v<T>), zz(_zz),  zw(zero_v<T>),
            wx(zero_v<T>), wy(zero_v<T>), wz(zero_v<T>), ww(_ww)
        {
        }

        constexpr Tensor44(diagonal_t, const Vector4<T>& v) : 
            xx(v.x),  xy(zero_v<T>), xz(zero_v<T>), xw(zero_v<T>),
            yx(zero_v<T>), yy(v.y),  yz(zero_v<T>), yw(zero_v<T>),
            zx(zero_v<T>), zy(zero_v<T>), zz(v.z),  zw(zero_v<T>),
            wx(zero_v<T>), wy(zero_v<T>), wz(zero_v<T>), ww(v.w)
        {
        }

        consteval Tensor44(identity_t) : 
            xx(one_v<T>),  xy(zero_v<T>), xz(zero_v<T>), xw(zero_v<T>),
            yx(zero_v<T>), yy(one_v<T>),  yz(zero_v<T>), yw(zero_v<T>),
            zx(zero_v<T>), zy(zero_v<T>), zz(one_v<T>),  zw(zero_v<T>),
            wx(zero_v<T>), wy(zero_v<T>), wz(zero_v<T>), ww(one_v<T>)
        {
        }

        constexpr Tensor44(ordered_t,
            T _xx, T _xy, T _xz, T _xw,
            T _yx, T _yy, T _yz, T _yw,
            T _zx, T _zy, T _zz, T _zw,
            T _wx, T _wy, T _wz, T _ww
        ) : 
            xx(_xx), xy(_xy), xz(_xz), xw(_xw),
            yx(_yx), yy(_yy), yz(_yz), yw(_yw),
            zx(_zx), zy(_zy), zz(_zz), zw(_zw),
            wx(_wx), wy(_wy), wz(_wz), ww(_ww)
        {
        }

        constexpr Tensor44(rows_t, const Vector4<T>& x, const Vector4<T>& y, const Vector4<T>& z, const Vector4<T>& w) :
            xx(x.x), xy(x.y), xz(x.z), xw(x.w),
            yx(y.x), yy(y.y), yz(y.z), yw(y.w),
            zx(z.x), zy(z.y), zz(z.z), zw(z.w),
            wx(w.x), wy(w.y), wz(w.z), ww(w.w)
        {
        }

        consteval Tensor44(zero_t) : 
            xx(zero_v<T>), xy(zero_v<T>), xz(zero_v<T>), xw(zero_v<T>),
            yx(zero_v<T>), yy(zero_v<T>), yz(zero_v<T>), yw(zero_v<T>),
            zx(zero_v<T>), zy(zero_v<T>), zz(zero_v<T>), zw(zero_v<T>),
            wx(zero_v<T>), wy(zero_v<T>), wz(zero_v<T>), ww(zero_v<T>)
        {
        }

        //! Defaulted equality operator
        constexpr bool operator==(const Tensor44&) const noexcept = default;
        
        //! Conversion to GLM
        operator glm::mat<4,4,T,glm::defaultp>() const noexcept 
        {
            return {
                xx, yx, zx, wx,
                xy, yy, zy, wy,
                xz, yz, zz, wz,
                xw, yw, zw, ww
            };
        }


        //! Positive (affirmation) operator
        constexpr Tensor44  operator+() const noexcept
        { 
            return *this; 
        }

        //! Negation operator
        constexpr Tensor44  operator-() const noexcept
        {
            return Tensor44(
                -xx, -xy, -xz, -xw,
                -yx, -yy, -yz, -yw,
                -zx, -zy, -zz, -zw,
                -wx, -wy, -wz, -ww
            );
        }
    
        //! Takes the transpose
        constexpr Tensor44 transpose() const noexcept
        {
            return Tensor44(
                xx, yx, zx, wx,
                xy, yy, zy, wy,
                xz, yz, zz, wz,
                xw, yw, zw, ww
            );
        }


        //  TODO: 4x4 determinant 
        //  TODO: 4x4 inverse 
        //  TODO: 4x4 eigenvalues, eigenvectors, & eigensystem

        //! \brief Trace of this tensor
        constexpr T     trace() const noexcept
        {
            return xx+yy+zz+ww;
        }

        //  --------------------------------------------------------
        //  GETTERS

            //! Diagonal of this vector
            constexpr Vector4<T>  diagonal() const noexcept
            {
                return Vector4<T>(xx, yy, zz, ww);
            }

            //! X-column of this vector
            constexpr Vector4<T>  x_column() const noexcept
            {
                return Vector4<T>(xx, yx, zx, wx);
            }

            //! Y-column of this vector
            constexpr Vector4<T>  y_column() const noexcept
            {
                return Vector4<T>(xy, yy, zy, wy);
            }

            //! Z-column of this vector
            constexpr Vector4<T>  z_column() const noexcept
            {
                return Vector4<T>(xz, yz, zz, wz);
            }

            //! W-column of this vector
            constexpr Vector4<T>  w_column() const noexcept
            {
                return Vector4<T>(xw, yw, zw, ww);
            }

            //! X-row of this vector
            constexpr Vector4<T>  x_row() const noexcept
            {
                return Vector4<T>(xx, xy, xz, xw);
            }

            //! Y-row of this vector
            constexpr Vector4<T>  y_row() const noexcept
            {
                return Vector4<T>(yx, yy, yz, yw);
            }

            //! Z-row of this vector
            constexpr Vector4<T>  z_row() const noexcept
            {
                return Vector4<T>(zx, zy, zz, zw);
            }

            //! W-row of this vector
            constexpr Vector4<T>  w_row() const noexcept
            {
                return Vector4<T>(wx, wy, wz, ww);
            }


        //  --------------------------------------------------------
        //  SETTERS

            //! Sets the diagonal
            Tensor44&  diagonal(const Vector4<T>& v) noexcept
            {        
                xx = v.x;
                yy = v.y;
                zz = v.z;
                ww = v.w;
                return *this;
            }

            //! Sets the diagonal
            Tensor44&  diagonal(T _xx, T _yy, T _zz, T _ww) noexcept
            {        
                xx = _xx;
                yy = _yy;
                zz = _zz;
                ww = _ww;
                return *this;
            }

            //! Sets the X-column
            Tensor44& x_column(const Vector4<T>& v) noexcept
            {
                xx = v.x;
                yx = v.y;
                zx = v.z;
                wx = v.w;
                return *this;
            }

            //! Sets the X-column
            Tensor44& x_column(T _xx, T _yx, T _zx, T _wx) noexcept
            {
                xx = _xx;
                yx = _yx;
                zx = _zx;
                wx = _wx;
                return *this;
            }

            //! Sets the Y-column
            Tensor44& y_column(const Vector4<T>& v) noexcept
            {
                xy = v.x;
                yy = v.y;
                zy = v.z;
                wy = v.w;
                return *this;
            }

            //! Sets the Y-column
            Tensor44& y_column(T _xy, T _yy, T _zy, T _wy) noexcept
            {
                xy = _xy;
                yy = _yy;
                zy = _zy;
                wy = _wy;
                return *this;
            }

            //! Sets the Z-column
            Tensor44& z_column(const Vector4<T>& v) noexcept
            {
                xz = v.x;
                yz = v.y;
                zz = v.z;
                wz = v.w;
                return *this;
            }

            //! Sets the Z-column
            Tensor44& z_column(T _xz, T _yz, T _zz, T _wz) noexcept
            {
                xz = _xz;
                yz = _yz;
                zz = _zz;
                wz = _wz;
                return *this;
            }

            //! Sets the W-column
            Tensor44& w_column(const Vector4<T>& v) noexcept
            {
                xw = v.x;
                yw = v.y;
                zw = v.z;
                ww = v.w;
                return *this;
            }

            //! Sets the W-column
            Tensor44& w_column(T _xw, T _yw, T _zw, T _ww) noexcept
            {
                xw = _xw;
                yw = _yw;
                zw = _zw;
                ww = _ww;
                return *this;
            }

            //! Sets the X-row
            Tensor44& x_row(const Vector4<T>& v) noexcept
            {
                xx = v.x;
                xy = v.y;
                xz = v.z;
                xw = v.w;
                return *this;
            }

            //! Sets the X-row
            Tensor44& x_row(T _xx, T _xy, T _xz, T _xw) noexcept
            {
                xx = _xx;
                xy = _xy;
                xz = _xz;
                xw = _xw;
                return *this;
            }

            //! Sets the Y-row
            Tensor44& y_row(const Vector4<T>& v) noexcept
            {
                yx = v.x;
                yy = v.y;
                yz = v.z;
                yw = v.w;
                return *this;
            }

            //! Sets the Y-row
            Tensor44& y_row(T _yx, T _yy, T _yz, T _yw) noexcept
            {
                yx = _yx;
                yy = _yy;
                yz = _yz;
                yw = _yw;
                return *this;
            }

            //! Sets the Z-row
            Tensor44& z_row(const Vector4<T>& v) noexcept
            {
                zx = v.x;
                zy = v.y;
                zz = v.z;
                zw = v.w;
                return *this;
            }

            //! Sets the Z-row
            Tensor44& z_row(T _zx, T _zy, T _zz, T _zw) noexcept
            {
                zx = _zx;
                zy = _zy;
                zz = _zz;
                zw = _zw;
                return *this;
            }

            //! Sets the W-row
            Tensor44& w_row(const Vector4<T>& v) noexcept
            {
                wx = v.x;
                wy = v.y;
                wz = v.z;
                ww = v.w;
                return *this;
            }

            //! Sets the W-row
            Tensor44& w_row(T _wx, T _wy, T _wz, T _ww) noexcept
            {
                wx = _wx;
                wy = _wy;
                wz = _wz;
                ww = _ww;
                return *this;
            }
    
    };
        
    YQ_IEEE754_1(Tensor44)

//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Creates 4x4 tensor from four Vector4 column vectors
    */
    template <typename T>
    constexpr Tensor44<T>  columns(const Vector4<T>&x, const Vector4<T>&y, const Vector4<T>&z, const Vector4<T>&w) noexcept
    {
        return Tensor44<T>(columns_, x, y, z, w);
    }

    /*! \brief Creates 4x4 tensor by specifying diagonal 
    
        This assumes the rest of the components are zero.
    */
    template <typename T>
    constexpr Tensor44<T>  diagonal(const Vector4<T>&v) noexcept
    {
        return Tensor44<T>(diagonal_, v);
    }
    
    /*! \brief Creates 4x4 tensor by specifying diagonal
    
        This assumes the rest of the components are zero.
    */
    template <typename T>
    constexpr Tensor44<T>  diagonal(T x, std::type_identity_t<T> y, std::type_identity_t<T> z, std::type_identity_t<T> w) noexcept
    {
        return Tensor44<T>(diagonal_, x, y, z, w);
    }

    /*! \brief Creates 4x4 tensor by specifying the rows
    */
    template <typename T>
    constexpr Tensor44<T>  rows(const Vector4<T>&x, const Vector4<T>&y, const Vector4<T>&z, const Vector4<T>&w) noexcept
    {
        return Tensor44<T>(rows_, x, y, z, w);
    }

    /*! \brief Creates 4x4 tensor from the GLM equivalent
    */
    template <typename T, glm::qualifier Q>
    constexpr Tensor44<T> tensor(const glm::mat<4,4,T,Q>& t) noexcept
    {
        return Tensor44<T>( ordered_,
            t.x.x, t.y.x, t.z.x, t.w.x,
            t.x.y, t.y.y, t.z.y, t.w.y,
            t.x.z, t.y.z, t.z.z, t.w.z,
            t.x.w, t.y.w, t.z.w, t.w.w
        );
    }
    
    YQ_IDENTITY_1(Tensor44, {
        one_v<T>, zero_v<T>, zero_v<T>, zero_v<T>,
        zero_v<T>, one_v<T>, zero_v<T>, zero_v<T>,
        zero_v<T>, zero_v<T>, one_v<T>, zero_v<T>,
        zero_v<T>, zero_v<T>, zero_v<T>, one_v<T>
    })

    YQ_NAN_1(Tensor44, {
        nan_v<T>, nan_v<T>, nan_v<T>, nan_v<T>,
        nan_v<T>, nan_v<T>, nan_v<T>, nan_v<T>,
        nan_v<T>, nan_v<T>, nan_v<T>, nan_v<T>,
        nan_v<T>, nan_v<T>, nan_v<T>, nan_v<T> 
    })
    
    YQ_ZERO_1(Tensor44, {
        zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>,
        zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>,
        zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>,
        zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T> 
     })
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor44, 
        is_finite(v.xx) && is_finite(v.xy) && is_finite(v.xz) && is_finite(v.xw) &&
        is_finite(v.yx) && is_finite(v.yy) && is_finite(v.yz) && is_finite(v.yw) &&
        is_finite(v.zx) && is_finite(v.zy) && is_finite(v.zz) && is_finite(v.zw) &&
        is_finite(v.wx) && is_finite(v.wy) && is_finite(v.wz) && is_finite(v.ww)
    )
    
    YQ_IS_NAN_1(Tensor44,  
        is_nan(v.xx) || is_nan(v.xy) || is_nan(v.xz) || is_nan(v.xw) ||
        is_nan(v.yx) || is_nan(v.yy) || is_nan(v.yz) || is_nan(v.yw) ||
        is_nan(v.zx) || is_nan(v.zy) || is_nan(v.zz) || is_nan(v.zw) ||
        is_nan(v.wx) || is_nan(v.wy) || is_nan(v.wz) || is_nan(v.ww)
    )

    //! Transpose of given tensor
    template <typename T>
    constexpr Tensor44<T>  transpose(const Tensor44<T>&ten) noexcept
    {
        return ten.transpose();
    }

//  --------------------------------------------------------
//  GETTERS

    //! Diagonal of given tensor
    template <typename T>
    constexpr Vector4<T>  diagonal(const Tensor44<T>&ten) noexcept
    {
        return ten.diagonal();
    }

    //! X-column of given tensor
    template <typename T>
    constexpr Vector4<T>  x_column(const Tensor44<T>&ten)  noexcept
    {
        return ten.x_column();
    }

    //! Y-column of given tensor
    template <typename T>
    constexpr Vector4<T>  y_column(const Tensor44<T>&ten)  noexcept
    {
        return ten.y_column();
    }

    //! Z-column of given tensor
    template <typename T>
    constexpr Vector4<T>  z_column(const Tensor44<T>&ten)  noexcept
    {
        return ten.z_column();
    }

    //! W-column of given tensor
    template <typename T>
    constexpr Vector4<T>  w_column(const Tensor44<T>&ten)  noexcept
    {
        return ten.w_column();
    }

    //! X-row of given tensor
    template <typename T>
    constexpr Vector4<T>  x_row(const Tensor44<T>&ten) noexcept
    {
        return ten.x_row();
    }

    //! Y-row of given tensor
    template <typename T>
    constexpr Vector4<T>  y_row(const Tensor44<T>&ten) noexcept
    {
        return ten.y_row();
    }

    //! Z-row of given tensor
    template <typename T>
    constexpr Vector4<T>  z_row(const Tensor44<T>&ten) noexcept
    {
        return ten.z_row();
    }

    //! W-row of given tensor
    template <typename T>
    constexpr Vector4<T>  w_row(const Tensor44<T>&ten) noexcept
    {
        return ten.z_row();
    }


//  --------------------------------------------------------
//  ADDITION

    template <typename T>
    constexpr Tensor44<T>   operator+ (const Tensor44<T> &a, const Tensor44<T> &b)  noexcept
    {
        return Tensor44<T>(
            a.xx+b.xx, a.xy+b.xy, a.xz+b.xz, a.xw+b.xw,
            a.yx+b.yx, a.yy+b.yy, a.yz+b.yz, a.yw+b.yw,
            a.zx+b.zx, a.zy+b.zy, a.zz+b.zz, a.zw+b.zw,
            a.wx+b.wx, a.wy+b.wy, a.wz+b.wz, a.ww+b.ww
        );
    }

    template <typename T>
    Tensor44<T>&   operator+=(Tensor44<T> &a, const Tensor44<T> &b)  noexcept
    {
        a.xx+=b.xx;  a.xy+=b.xy;  a.xz+=b.xz;  a.xw+=b.xw;
        a.yx+=b.yx;  a.yy+=b.yy;  a.yz+=b.yz;  a.yw+=b.yw;
        a.zx+=b.zx;  a.zy+=b.zy;  a.zz+=b.zz;  a.zw+=b.zw;
        a.wx+=b.wx;  a.wy+=b.wy;  a.wz+=b.wz;  a.ww+=b.ww;
        return a;
    }


//  --------------------------------------------------------
//  SUBTRACTION

    template <typename T>
    constexpr Tensor44<T>   operator- (const Tensor44<T> &a, const Tensor44<T> &b)  noexcept
    {
        return Tensor44<T>(
            a.xx-b.xx, a.xy-b.xy, a.xz-b.xz, a.xw-b.xw,
            a.yx-b.yx, a.yy-b.yy, a.yz-b.yz, a.yw-b.yw,
            a.zx-b.zx, a.zy-b.zy, a.zz-b.zz, a.zw-b.zw,
            a.wx-b.wx, a.wy-b.wy, a.wz-b.wz, a.ww-b.ww
        );
    }
    

    template <typename T>
    Tensor44<T>&   operator-=(Tensor44<T> &a, const Tensor44<T> &b)  noexcept
    {
        a.xx-=b.xx;  a.xy-=b.xy;  a.xz-=b.xz;  a.xw-=b.xw;
        a.yx-=b.yx;  a.yy-=b.yy;  a.yz-=b.yz;  a.yw-=b.yw;
        a.zx-=b.zx;  a.zy-=b.zy;  a.zz-=b.zz;  a.zw-=b.zw;
        a.wx-=b.wx;  a.wy-=b.wy;  a.wz-=b.wz;  a.ww-=b.ww;
        return a;
    }
    
//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires std::is_arithmetic_v<T>
    constexpr Tensor44<product_t<T,U>>  operator*(T a, const Tensor44<U>& b) noexcept
    {
        return Tensor44<product_t<T,U>>(
            a*b.xx, a*b.xy, a*b.xz, a*b.xw,
            a*b.yx, a*b.yy, a*b.yz, a*b.yw,
            a*b.zx, a*b.zy, a*b.zz, a*b.zw,
            a*b.wx, a*b.wy, a*b.wz, a*b.ww
        );
    }
    
    
    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor44<product_t<T,U>>  operator*(const Tensor44<T>& a, U b) noexcept
    {
        return {
            a.xx*b, a.xy*b, a.xz*b, a.xw*b,
            a.yx*b, a.yy*b, a.yz*b, a.yw*b,
            a.zx*b, a.zy*b, a.zz*b, a.zw*b,
            a.wx*b, a.wy*b, a.wz*b, a.ww*b
        };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Tensor44<product_t<T,U>>  operator*=(const Tensor44<T>& a, U b) noexcept
    {
        a.xx*=b; a.xy*=b; a.xz*=b; a.xw*=b;
        a.yx*=b; a.yy*=b; a.yz*=b; a.yw*=b;
        a.zx*=b; a.zy*=b; a.zz*=b; a.zw*=b;
        a.wx*=b; a.wy*=b; a.wz*=b; a.ww*=b;        
        return a;
    }

    template <typename T, typename U>
    constexpr Tensor44<product_t<T,U>> operator*(const Tensor44<T>& a, const Tensor44<U>& b) noexcept
    {
        return Tensor44<product_t<T,U>>(
            a.xx*b.xx + a.xy*b.yx + a.xz*b.zx + a.xw*b.wx,
            a.xx*b.xy + a.xy*b.yy + a.xz*b.zy + a.xw*b.wy,
            a.xx*b.xz + a.xy*b.yz + a.xz*b.zz + a.xw*b.wz,
            a.xx*b.xw + a.xy*b.yw + a.xz*b.zw + a.xw*b.ww,

            a.yx*b.xx + a.yy*b.yx + a.yz*b.zx + a.yw*b.wx,
            a.yx*b.xy + a.yy*b.yy + a.yz*b.zy + a.yw*b.wy,
            a.yx*b.xz + a.yy*b.yz + a.yz*b.zz + a.yw*b.wz,
            a.yx*b.xw + a.yy*b.yw + a.yz*b.zw + a.yw*b.ww,

            a.zx*b.xx + a.zy*b.yx + a.zz*b.zx + a.zw*b.wx,
            a.zx*b.xy + a.zy*b.yy + a.zz*b.zy + a.zw*b.wy,
            a.zx*b.xz + a.zy*b.yz + a.zz*b.zz + a.zw*b.wz,
            a.zx*b.xw + a.zy*b.yw + a.zz*b.zw + a.zw*b.ww,

            a.wx*b.xx + a.wy*b.yx + a.wz*b.zx + a.ww*b.wx,
            a.wx*b.xy + a.wy*b.yy + a.wz*b.zy + a.ww*b.wy,
            a.wx*b.xz + a.wy*b.yz + a.wz*b.zz + a.ww*b.wz,
            a.wx*b.xw + a.wy*b.yw + a.wz*b.zw + a.ww*b.ww
        );
    }
    
    template <typename T, typename U>
    requires trait::self_mul_v<T,U>
    Tensor44<T>& operator*=(Tensor44<T>&a, const Tensor44<U>& b) noexcept
    {
        a = a * b;
        return a;
    }

        
    template <typename T, typename U>
    constexpr Vector4<product_t<T,U>> operator*(const Tensor44<T>&a, const Vector4<U>&b) noexcept
    {
        return Vector4<product_t<T,U>>(
            a.xx*b.x + a.xy*b.y + a.xz*b.z + a.xw*b.w,
            a.yx*b.x + a.yy*b.y + a.yz*b.z + a.yw*b.w,
            a.zx*b.x + a.zy*b.y + a.zz*b.z + a.zw*b.w,
            a.wx*b.x + a.wy*b.y + a.wz*b.z + a.ww*b.w
        );
    }


//  --------------------------------------------------------
//  DIVISION


    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor44<quotient_t<T,U>>  operator/(const Tensor44<T>& a, U b) noexcept
    {
        return Tensor44<quotient_t<T,U>>(
            a.xx/b, a.xy/b, a.xz/b, a.xw/b,
            a.yx/b, a.yy/b, a.yz/b, a.yw/b,
            a.zx/b, a.zy/b, a.zz/b, a.zw/b,
            a.wx/b, a.wy/b, a.wz/b, a.ww/b
        );
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Tensor44<quotient_t<T,U>>  operator/=(const Tensor44<T>& a, U b) noexcept
    {
        a.xx/=b; a.xy/=b; a.xz/=b; a.xw/=b;
        a.yx/=b; a.yy/=b; a.yz/=b; a.yw/=b;
        a.zx/=b; a.zy/=b; a.zz/=b; a.zw/=b;
        a.wx/=b; a.wy/=b; a.wz/=b; a.ww/=b;        
        return a;
    }

//  --------------------------------------------------------
//  OTIMES PRODUCT

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS


    //  TODO: 4x4 determinant 
    //  TODO: 4x4 inverse 
    //  TODO: 4x4 eigenvalues, eigenvectors, & eigensystem

    /*! \brief Trace of the given 4 x 4 tensor
    
        \param[in] a    Tensor to take the trace of
    */
    template <typename T>
    constexpr T     trace(const Tensor44<T>& ten) noexcept
    {
        return ten.trace();
    }

}

YQ_TYPE_DECLARE(yq::Tensor44D)
YQ_TYPE_DECLARE(yq::Tensor44F)
YQ_TYPE_DECLARE(yq::Tensor44I)
YQ_TYPE_DECLARE(yq::Tensor44U)

