////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__TENSOR_2_3__HPP 1
#include <math/preamble.hpp>
#include <math/Vector2.hpp>
#include <math/Vector3.hpp>

namespace yq {
    /*! \brief 2x3 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor23 {
    
        //! Component type (captures template parameter)
        using component_type = T;
        T xx, xy, xz;
        T yx, yy, yz;

        //! Defaulted equality operator
        constexpr bool operator==(const Tensor23&) const noexcept = default;

        //! Positive (affirmation) oeprator
        constexpr Tensor23<T>  operator+() const noexcept
        { 
            return *this; 
        }

        //! Negation
        constexpr Tensor23<T>  operator-() const noexcept
        {
            return {
                -xx, -xy, -xz,
                -yx, -yy, -yz
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


        //  --------------------------------------------------------
        //  SETTERS

            //! Sets the X-column of this tensor
            Tensor23& x_column(const Vector2<T>& v)
            {
                xx = v.x;
                yx = v.y;
                return *this;
            }

            //! Sets the X-column of this tensor
            Tensor23& x_column(T _xx, T _yx)
            {
                xx = _xx;
                yx = _yx;
                return *this;
            }


            //! Sets the Y-column of this tensor
            Tensor23& y_column(const Vector2<T>& v)
            {
                xy = v.x;
                yy = v.y;
                return *this;
            }

            //! Sets the Y-column of this tensor
            Tensor23& y_column(T _xy, T _yy)
            {
                xy = _xy;
                yy = _yy;
                return *this;
            }

            //! Sets the Z-column of this tensor
            Tensor23& z_column(const Vector2<T>& v)
            {
                xz = v.x;
                yz = v.y;
                return *this;
            }

            //! Sets the Z-column of this tensor
            Tensor23& z_column(T _xz, T _yz)
            {
                xz = _xz;
                yz = _yz;
                return *this;
            }

            //! Sets the X-row of this tensor
            Tensor23& x_row(const Vector3<T>& v)
            {
                xx = v.x;
                xy = v.y;
                xz = v.z;
                return *this;
            }

            //! Sets the X-row of this tensor
            Tensor23& x_row(T _xx, T _xy, T _xz)
            {
                xx = _xx;
                xy = _xy;
                xz = _xz;
                return *this;
            }

            //! Sets the Y-row of this tensor
            Tensor23& y_row(const Vector3<T>& v)
            {
                yx = v.x;
                yy = v.y;
                yz = v.z;
                return *this;
            }

            //! Sets the Y-row of this tensor
            Tensor23& y_row(T _yx, T _yy, T _yz)
            {
                yx = _yx;
                yy = _yy;
                yz = _yz;
                return *this;
            }
    };

    YQ_IEEE754_1(Tensor23)
        
//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Create 2x3 tensor by columns
    */
    template <typename T>
    constexpr Tensor23<T>  columns(const Vector2<T>&x, const Vector2<T>&y, const Vector2<T>&z)
    {
        return {
            x.x, y.x, z.x,
            x.y, y.y, z.y
        };
    }

    /*! \brief Create 2x3 tensor by rows
    */
    template <typename T>
    constexpr Tensor23<T>  rows(const Vector3<T>&x, const Vector3<T>&y)
    {
        return {
            x.x, x.y, x.z,
            y.x, y.y, y.z
        };
    }
    
    YQ_IDENTITY_1(Tensor23, {
        one_v<T>, zero_v<T>, zero_v<T>,
        zero_v<T>, one_v<T>, zero_v<T>
    })

    YQ_NAN_1(Tensor23, {
        nan_v<T>, nan_v<T>, nan_v<T>,
        nan_v<T>, nan_v<T>, nan_v<T> 
    })
    
    YQ_ZERO_1(Tensor23, {
        zero_v<T>, zero_v<T>, zero_v<T>,
        zero_v<T>, zero_v<T>, zero_v<T> 
     })
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor23, 
        is_finite(v.xx) && is_finite(v.xy) && is_finite(v.xz) &&
        is_finite(v.yx) && is_finite(v.yy) && is_finite(v.yz)
    )
    
    YQ_IS_NAN_1(Tensor23,  
        is_nan(v.xx) || is_nan(v.xy) || is_nan(v.xz) ||
        is_nan(v.yx) || is_nan(v.yy) || is_nan(v.yz)
    )

//  --------------------------------------------------------
//  GETTERS

    //! Gets the X-column of the provided tensor
    template <typename T>
    constexpr Vector2<T>  x_column(const Tensor23<T>&ten) 
    {
        return ten.x_column();
    }

    //! Gets the Y-column of the provided tensor
    template <typename T>
    constexpr Vector2<T>  y_column(const Tensor23<T>&ten) 
    {
        return ten.y_column();
    }

    //! Gets the Z-column of the provided tensor
    template <typename T>
    constexpr Vector2<T>  z_column(const Tensor23<T>&ten) 
    {
        return ten.z_column();
    }

    //! Gets the X-row of the provided tensor
    template <typename T>
    constexpr Vector3<T>  x_row(const Tensor23<T>&ten)
    {
        return ten.x_row();
    }

    //! Gets the Y-row of the provided tensor
    template <typename T>
    constexpr Vector3<T>  y_row(const Tensor23<T>&ten)
    {
        return ten.y_row();
    }



//  --------------------------------------------------------
//  ADDITION

    template <typename T>
    constexpr Tensor23<T>   operator+ (const Tensor23<T> &a, const Tensor23<T> &b) 
    {
        return {
            a.xx+b.xx, a.xy+b.xy, a.xz+b.xz,
            a.yx+b.yx, a.yy+b.yy, a.yz+b.yz
        };
    }

    template <typename T>
    Tensor23<T>&   operator+=(Tensor23<T> &a, const Tensor23<T> &b) 
    {
        a.xx+=b.xx;  a.xy+=b.xy;  a.xz+=b.xz;
        a.yx+=b.yx;  a.yy+=b.yy;  a.yz+=b.yz;
        return a;
    }


//  --------------------------------------------------------
//  SUBTRACTION

    template <typename T>
    constexpr Tensor23<T>   operator- (const Tensor23<T> &a, const Tensor23<T> &b) 
    {
        return {
            a.xx-b.xx, a.xy-b.xy, a.xz-b.xz,
            a.yx-b.yx, a.yy-b.yy, a.yz-b.yz
        };
    }
    

    template <typename T>
    Tensor23<T>&   operator-=(Tensor23<T> &a, const Tensor23<T> &b) 
    {
        a.xx-=b.xx;  a.xy-=b.xy;  a.xz-=b.xz;
        a.yx-=b.yx;  a.yy-=b.yy;  a.yz-=b.yz;
        return a;
    }
    
//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires std::is_arithmetic_v<T>
    constexpr Tensor23<product_t<T,U>>  operator*(T a, const Tensor23<T>& b)
    {
        return {
            a*b.xx, a*b.xy, a*b.xz,
            a*b.yx, a*b.yy, a*b.yz
        };
    }
    
    
    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor23<product_t<T,U>>  operator*(const Tensor23<T>& a, U b)
    {
        return {
            a.xx*b, a.xy*b, a.xz*b,
            a.yx*b, a.yy*b, a.yz*b
        };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Tensor23<product_t<T,U>>  operator*=(const Tensor23<T>& a, U b)
    {
        a.xx*=b; a.xy*=b; a.xz*=b;
        a.yx*=b; a.yy*=b; a.yz*=b;        
        return a;
    }

        
    template <typename T, typename U>
    constexpr Vector2<product_t<T,U>> operator*(const Tensor23<T>&a, const Vector3<U>&b)
    {
        return {
            a.xx*b.x + a.xy*b.y + a.xz*b.z,
            a.yx*b.x + a.yy*b.y + a.yz*b.z
        };
    }

    template <typename T, typename U>
    constexpr Vector3<product_t<T,U>> operator*(const Vector2<T>&a, const Tensor23<U>&b)
    {
        return {
            a.x*b.xx + a.y*b.yx,
            a.x*b.xy + a.y*b.yy,
            a.x*b.xz + a.y*b.yz
        };
    }

//  --------------------------------------------------------
//  DIVISION


    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor23<quotient_t<T,U>>  operator/(const Tensor23<T>& a, U b)
    {
        return {
            a.xx/b, a.xy/b, a.xz/b,
            a.yx/b, a.yy/b, a.yz/b
        };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Tensor23<quotient_t<T,U>>  operator/=(const Tensor23<T>& a, U b)
    {
        a.xx/=b; a.xy/=b; a.xz/=b;
        a.yx/=b; a.yy/=b; a.yz/=b;        
        return a;
    }

//  --------------------------------------------------------
//  OTIMES PRODUCT

    template <typename T, typename U>
    constexpr Tensor23<product_t<T,U>> operator OTIMES(const Vector2<T>&a, const Vector3<U>&b)
    {
        return {
            a.x+b.x, a.x+b.y, a.x+b.z,
            a.y+b.x, a.y+b.y, a.y+b.z
        };
    }

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

}

YQ_TYPE_DECLARE(yq::Tensor23D)
YQ_TYPE_DECLARE(yq::Tensor23F)
YQ_TYPE_DECLARE(yq::Tensor23I)
YQ_TYPE_DECLARE(yq::Tensor23U)

