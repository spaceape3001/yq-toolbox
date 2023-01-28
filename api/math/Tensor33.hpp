////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__TENSOR_3_3__HPP 1
#include <math/preamble.hpp>
#include <math/trig.hpp>
#include <math/Vector3.hpp>

namespace yq {
    /*! \brief 3x3 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor33 {
    
        //! Component type (captures the template parameter)
        using component_type = T;
        
        T xx, xy, xz;
        T yx, yy, yz;
        T zx, zy, zz;

        //! Default equality operator
        constexpr bool operator==(const Tensor33&) const noexcept = default;

        //! Creates a GLM matrix
        operator glm::mat<3,3,T,glm::defaultp>() const noexcept 
        {
            return {
                xx, yx, zx,
                xy, yy, zy,
                xz, yz, zz
            };
        }

        //! Positive (affirmation) operator
        constexpr Tensor33  operator+() const noexcept
        { 
            return *this; 
        }

        //! Negation operator
        constexpr Tensor33  operator-() const noexcept
        {
            return {
                -xx, -xy, -xz,
                -yx, -yy, -yz,
                -zx, -zy, -zz
            };
        }

        //! Determinant of this matrix
        constexpr cube_t<T> determinant() const noexcept
        {
            return xx*(yy*zz-yz*zy)+xy*(zx*xz-yx*zz)+xz*(yx*zy-zx*yy);
        }
     
        //  TODO: 3x3 eigenvalues, eigenvectors, & eigensystem
        
        
        //! Inverse of this matrix
        constexpr Tensor33<inverse_t<T>> inverse() const noexcept
        {
            auto    di = one_v<T> / determinant();
            return {
                di*(yy*zz-zy*yz), di*(xz*zy-zz*xy), di*(xy*yz-yy*xz),
                di*(yz*zx-zz*yx), di*(xx*zz-xz*zx), di*(xz*yx-yz*xx),
                di*(yx*zy-zx*yy), di*(xy*zx-zy*xx), di*(xx*yy-yx*xy)
            };
        }
        
        /*! \brief Trace of this tensor
        */
        constexpr T     trace() const noexcept
        {
            return xx+yy+zz;
        }
    
        //! Transpose of this vector
        constexpr Tensor33  transpose() const noexcept
        {
            return {
                xx, yx, zx,
                xy, yy, zy,
                xz, yz, zz
            };
        }

        //  --------------------------------------------------------
        //  GETTERS

            //! The diagonal of this tensor
            constexpr Vector3<T>  diagonal() const noexcept
            {
                return {xx, yy, zz};
            }

            //! X-column of this tensor
            constexpr Vector3<T>  x_column() const noexcept
            {
                return {xx, yx, zx};
            }

            //! Y-column of this tensor
            constexpr Vector3<T>  y_column() const noexcept
            {
                return {xy, yy, zy};
            }

            //! Z-column of this tensor
            constexpr Vector3<T>  z_column() const noexcept
            {
                return {xz, yz, zz};
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



        //  --------------------------------------------------------
        //  SETTERS

            //! Sets the diagonal
            Tensor33&  diagonal(const Vector3<T>& v)
            {
                xx = v.x;
                yy = v.y;
                zz = v.z;
                return *this;
            }

            //! Sets the diagonal
            Tensor33&  diagonal(T _xx, T _yy, T _zz)
            {
                xx = _xx;
                yy = _yy;
                zz = _zz;
                return *this;
            }

            //! Sets the x-column
            Tensor33& x_column(const Vector3<T>& v)
            {
                xx = v.x;
                yx = v.y;
                zx = v.z;
                return *this;
            }

            //! Sets the x-column
            Tensor33& x_column(T _xx, T _yx, T _zx)
            {
                xx = _xx;
                yx = _yx;
                zx = _zx;
                return *this;
            }

            //! Sets the y-column
            Tensor33& y_column(const Vector3<T>& v)
            {
                xy = v.x;
                yy = v.y;
                zy = v.z;
                return *this;
            }

            //! Sets the y-column
            Tensor33& y_column(T _xy, T _yy, T _zy)
            {
                xy = _xy;
                yy = _yy;
                zy = _zy;
                return *this;
            }

            //! Sets the z-column
            Tensor33& z_column(const Vector3<T>& v)
            {
                xz = v.x;
                yz = v.y;
                zz = v.z;
                return *this;
            }

            //! Sets the z-column
            Tensor33& z_column(T _xz, T _yz, T _zz)
            {
                xz = _xz;
                yz = _yz;
                zz = _zz;
                return *this;
            }

            //! Sets the x-row
            Tensor33& x_row(const Vector3<T>& v)
            {
                xx = v.x;
                xy = v.y;
                xz = v.z;
                return *this;
            }

            //! Sets the x-row
            Tensor33& x_row(T _xx, T _xy, T _xz)
            {
                xx = _xx;
                xy = _xy;
                xz = _xz;
                return *this;
            }

            //! Sets the y-row
            Tensor33& y_row(const Vector3<T>& v)
            {
                yx = v.x;
                yy = v.y;
                yz = v.z;
                return *this;
            }

            //! Sets the y-row
            Tensor33& y_row(T _yx, T _yy, T _yz)
            {
                yx = _yx;
                yy = _yy;
                yz = _yz;
                return *this;
            }

            //! Sets the z-row
            Tensor33& z_row(const Vector3<T>& v)
            {
                zx = v.x;
                zy = v.y;
                zz = v.z;
                return *this;
            }
    
            //! Sets the z-row
            Tensor33& z_row(T _zx, T _zy, T _zz)
            {
                zx = _zx;
                zy = _zy;
                zz = _zz;
                return *this;
            }
    };

    YQ_IEEE754_1(Tensor33)
        
//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Create 3x3 tensor by columns
    */
    template <typename T>
    constexpr Tensor33<T>  columns(const Vector3<T>&x, const Vector3<T>&y, const Vector3<T>&z)
    {
        return {
            x.x, y.x, z.x,
            x.y, y.y, z.y,
            x.z, y.z, z.z
        };
    }

    /*! \brief Create 3x3 tensor by its diagonal
    */
    template <typename T>
    constexpr Tensor33<T>  diagonal(const Vector3<T>&v)
    {
        return {
            v.x, zero_v<T>, zero_v<T>,
            zero_v<T>, v.y, zero_v<T>,
            zero_v<T>, zero_v<T>, v.z
        };
    }
    
    /*! \brief Create 3x3 tensor by its diagonal
    */
    template <typename T>
    constexpr Tensor33<T>  diagonal(T x, std::type_identity_t<T> y, std::type_identity_t<T> z)
    {
        return {
            x, zero_v<T>, zero_v<T>,
            zero_v<T>, y, zero_v<T>,
            zero_v<T>, zero_v<T>, z
        };
    }

    /*! \brief Create 3x3 tensor by heading-pitch-roll
    
        A traditional rotation matrix in flight sims and other similar ventures, this creates a 3x3
        matrix by specifying it's "heading-pitch-roll".
        
        \param[in] hdg      Yaw or Heading (ie rotation around "Z")
        \param[in] pitch    Pitch up (ie rotation around "Y")
        \param[in] roll     Roll (ie rotation around "X")

        \return 3x3 rotation matrix
    */
    template <typename T>
    Tensor33<T> hpr33(MKS<T,dim::Angle> hdg, MKS<T,dim::Angle> pitch, MKS<T,dim::Angle> roll)
    {
        auto ch = cos(hdg);
        auto sh = sin(hdg);

        auto cp = cos(pitch);
        auto sp = sin(pitch);

        auto cr = cos(roll);
        auto sr = sin(roll);
        
        return {
            ch*cp, sh*cp, -sp,
            ch*sp*sr-sh*cr, sh*sp*sr+ch*cr, cp*sr,
            ch*sp*cr+sh*sr, sh*sp*cr-ch*sr, cp*cr
        };
    }

    //! Creates a matrix that can rotate a vector by the specfied angle
    //! In the counter-clockwise direction
    template <typename T>
    constexpr Tensor33<T>   rotation3X(MKS<T,dim::Angle> r)
    {
        auto c  = cos(r);
        auto s  = sin(r);
        return {
            1., 0., 0.,
            0., c, -s,
            0., s, c
        };
    }

    //! Creates a matrix that can rotate a vector by the specfied angle
    //! In the counter-clockwise direction
    template <typename T>
    constexpr Tensor33<T>   rotation3Y(MKS<T,dim::Angle> r)
    {
        auto c  = cos(r);
        auto s  = sin(r);
        return {
            c, 0., -s,
            0., 1., 0.,
            s, 0., c
        };
    }


    //! Creates a matrix that can rotate a vector by the specfied angle
    //! In the counter-clockwise direction
    template <typename T>
    constexpr Tensor33<T>   rotation3Z(MKS<T,dim::Angle> r)
    {
        auto c  = cos(r);
        auto s  = sin(r);
        return {
            1., 0., 0.,
            0., c, -s,
            0., s, c
        };
    }


    /*! \brief Create 3x3 tensor by rows
    */
    template <typename T>
    constexpr Tensor33<T>  rows(const Vector3<T>&x, const Vector3<T>&y, const Vector3<T>&z)
    {
        return {
            x.x, x.y, x.z,
            y.x, y.y, y.z,
            z.x, z.y, z.z
        };
    }

    /*! \brief Create 3x3 tensor from GLM
    */
    template <typename T, glm::qualifier Q>
    constexpr Tensor33<T> tensor(const glm::mat<3,3,T,Q>& t)
    {
        return {
            t.x.x, t.y.x, t.z.x, 
            t.x.y, t.y.y, t.z.y, 
            t.x.z, t.y.z, t.z.z
        };
    }
    
    
    YQ_IDENTITY_1(Tensor33, {
        one_v<T>, zero_v<T>, zero_v<T>,
        zero_v<T>, one_v<T>, zero_v<T>,
        zero_v<T>, zero_v<T>, one_v<T>
    })

    YQ_NAN_1(Tensor33, {
        nan_v<T>, nan_v<T>, nan_v<T>,
        nan_v<T>, nan_v<T>, nan_v<T>,
        nan_v<T>, nan_v<T>, nan_v<T> 
    })
    
    YQ_ZERO_1(Tensor33, {
        zero_v<T>, zero_v<T>, zero_v<T>,
        zero_v<T>, zero_v<T>, zero_v<T>,
        zero_v<T>, zero_v<T>, zero_v<T> 
     })
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor33, 
        is_finite(v.xx) && is_finite(v.xy) && is_finite(v.xz) &&
        is_finite(v.yx) && is_finite(v.yy) && is_finite(v.yz) &&
        is_finite(v.zx) && is_finite(v.zy) && is_finite(v.zz)
    )
    
    YQ_IS_NAN_1(Tensor33,  
        is_nan(v.xx) || is_nan(v.xy) || is_nan(v.xz) ||
        is_nan(v.yx) || is_nan(v.yy) || is_nan(v.yz) ||
        is_nan(v.zx) || is_nan(v.zy) || is_nan(v.zz)
    )

    //! Transpose of the provided tensor
    template <typename T>
    constexpr Tensor33<T>  transpose(const Tensor33<T>&ten)
    {
        return ten.transpose();
    }

//  --------------------------------------------------------
//  GETTERS

    //! Diagonal of provided tensor
    template <typename T>
    constexpr Vector3<T>  diagonal(const Tensor33<T>&ten)
    {
        return ten.diagonal();
    }

    //! X-column of provided tensor
    template <typename T>
    constexpr Vector3<T>  x_column(const Tensor33<T>&ten) 
    {
        return ten.x_column();
    }

    //! Y-column of provided tensor
    template <typename T>
    constexpr Vector3<T>  y_column(const Tensor33<T>&ten) 
    {
        return ten.y_column();
    }

    //! Z-column of provided tensor
    template <typename T>
    constexpr Vector3<T>  z_column(const Tensor33<T>&ten) 
    {
        return ten.z_column();
    }

    //! X-row of provided tensor
    template <typename T>
    constexpr Vector3<T>  x_row(const Tensor33<T>&ten)
    {
        return ten.x_row();
    }

    //! Y-row of provided tensor
    template <typename T>
    constexpr Vector3<T>  y_row(const Tensor33<T>&ten)
    {
        return ten.y_row();
    }

    //! Z-row of provided tensor
    template <typename T>
    constexpr Vector3<T>  z_row(const Tensor33<T>&ten)
    {
        return ten.z_row();
    }



//  --------------------------------------------------------
//  ADDITION

    template <typename T>
    constexpr Tensor33<T>   operator+ (const Tensor33<T> &a, const Tensor33<T> &b) 
    {
        return {
            a.xx+b.xx, a.xy+b.xy, a.xz+b.xz,
            a.yx+b.yx, a.yy+b.yy, a.yz+b.yz,
            a.zx+b.zx, a.zy+b.zy, a.zz+b.zz
        };
    }

    template <typename T>
    Tensor33<T>&   operator+=(Tensor33<T> &a, const Tensor33<T> &b) 
    {
        a.xx+=b.xx;  a.xy+=b.xy;  a.xz+=b.xz;
        a.yx+=b.yx;  a.yy+=b.yy;  a.yz+=b.yz;
        a.zx+=b.zx;  a.zy+=b.zy;  a.zz+=b.zz;
        return a;
    }


//  --------------------------------------------------------
//  SUBTRACTION

    template <typename T>
    constexpr Tensor33<T>   operator- (const Tensor33<T> &a, const Tensor33<T> &b) 
    {
        return {
            a.xx-b.xx, a.xy-b.xy, a.xz-b.xz,
            a.yx-b.yx, a.yy-b.yy, a.yz-b.yz,
            a.zx-b.zx, a.zy-b.zy, a.zz-b.zz
        };
    }
    

    template <typename T>
    Tensor33<T>&   operator-=(Tensor33<T> &a, const Tensor33<T> &b) 
    {
        a.xx-=b.xx;  a.xy-=b.xy;  a.xz-=b.xz;
        a.yx-=b.yx;  a.yy-=b.yy;  a.yz-=b.yz;
        a.zx-=b.zx;  a.zy-=b.zy;  a.zz-=b.zz;
        return a;
    }
    
//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires std::is_arithmetic_v<T>
    constexpr Tensor33<product_t<T,U>>  operator*(T a, const Tensor33<T>& b)
    {
        return {
            a*b.xx, a*b.xy, a*b.xz,
            a*b.yx, a*b.yy, a*b.yz,
            a*b.zx, a*b.zy, a*b.zz
        };
    }
    
    
    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor33<product_t<T,U>>  operator*(const Tensor33<T>& a, U b)
    {
        return {
            a.xx*b, a.xy*b, a.xz*b,
            a.yx*b, a.yy*b, a.yz*b,
            a.zx*b, a.zy*b, a.zz*b
        };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Tensor33<product_t<T,U>>  operator*=(const Tensor33<T>& a, U b)
    {
        a.xx*=b; a.xy*=b; a.xz*=b;
        a.yx*=b; a.yy*=b; a.yz*=b;
        a.zx*=b; a.zy*=b; a.zz*=b;        
        return a;
    }

    template <typename T, typename U>
    constexpr Tensor33<product_t<T,U>> operator*(const Tensor33<T>& a, const Tensor33<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx + a.xz*b.zx,
            a.xx*b.xy + a.xy*b.yy + a.xz*b.zy,
            a.xx*b.xz + a.xy*b.yz + a.xz*b.zz,

            a.yx*b.xx + a.yy*b.yx + a.yz*b.zx,
            a.yx*b.xy + a.yy*b.yy + a.yz*b.zy,
            a.yx*b.xz + a.yy*b.yz + a.yz*b.zz,

            a.zx*b.xx + a.zy*b.yx + a.zz*b.zx,
            a.zx*b.xy + a.zy*b.yy + a.zz*b.zy,
            a.zx*b.xz + a.zy*b.yz + a.zz*b.zz
        };
    }
    
    template <typename T, typename U>
    requires trait::self_mul_v<T,U>
    Tensor33<T>& operator*=(Tensor33<T>&a, const Tensor33<U>& b)
    {
        a = a * b;
        return a;
    }

        
    template <typename T, typename U>
    constexpr Vector3<product_t<T,U>> operator*(const Tensor33<T>&a, const Vector3<U>&b)
    {
        return {
            a.xx*b.x + a.xy*b.y + a.xz*b.z,
            a.yx*b.x + a.yy*b.y + a.yz*b.z,
            a.zx*b.x + a.zy*b.y + a.zz*b.z
        };
    }


//  --------------------------------------------------------
//  DIVISION


    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor33<quotient_t<T,U>>  operator/(const Tensor33<T>& a, U b)
    {
        return {
            a.xx/b, a.xy/b, a.xz/b,
            a.yx/b, a.yy/b, a.yz/b,
            a.zx/b, a.zy/b, a.zz/b
        };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Tensor33<quotient_t<T,U>>  operator/=(const Tensor33<T>& a, U b)
    {
        a.xx/=b; a.xy/=b; a.xz/=b;
        a.yx/=b; a.yy/=b; a.yz/=b;
        a.zx/=b; a.zy/=b; a.zz/=b;        
        return a;
    }

//  --------------------------------------------------------
//  OTIMES PRODUCT

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

    //! Determinant of the given tensor
    template <typename T>
    cube_t<T> determinant(const Tensor33<T>& ten)
    {
        return ten.determinant();
    }
 
    //  TODO: 3x3 eigenvalues, eigenvectors, & eigensystem
    
    
    //! Inverse of the given tensor
    template <typename T>
    Tensor33<inverse_t<T>> inverse(const Tensor33<T>&ten)
    {
        return ten.inverse();
    }
    
    /*! \brief Trace of the 3 x 3 tensor
    
        \param[in] a    Tensor to take the trace of
    */
    template <typename T>
    constexpr T     trace(const Tensor33<T>& ten)
    {
        return ten.trace();
    }
}

YQ_TYPE_DECLARE(yq::Tensor33D)
YQ_TYPE_DECLARE(yq::Tensor33F)
YQ_TYPE_DECLARE(yq::Tensor33I)
YQ_TYPE_DECLARE(yq::Tensor33U)

