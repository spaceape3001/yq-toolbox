////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__TENSOR_2_2__HPP 1
#include <math/preamble.hpp>
#include <math/trig.hpp>
#include <math/Vector2.hpp>

namespace yq {
    /*! \brief 2x2 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor22 {
    
        //! Component type (captures the template parameter)
        using component_type = T;
        T xx, xy;
        T yx, yy;

        //! Defaulted equality operator
        constexpr bool operator==(const Tensor22&) const noexcept = default;

        //! Implicit conversion to GLM
        operator glm::mat<2,2,T,glm::defaultp>() const noexcept 
        {
            return {
                xx, yx,
                xy, yy
            };
        }


        //! Positive (affirmation) operator
        constexpr Tensor22  operator+() const noexcept
        { 
            return *this; 
        }


        //! Negation operator
        constexpr Tensor22  operator-() const noexcept
        {
            return {
                -xx, -xy,
                -yx, -yy
            };
        }

        //! Computes the determinant of this matrix
        constexpr square_t<T> determinant() const noexcept
        {
            return xx*yy-xy*yx;
        }

        //void        eigenvalues(zreal&,zreal&,zreal&,zreal&b) const;
        //void        eigensystem(zreal&,zvector4&,zreal&,zvector4&,zreal&,zvector4&,zreal&,zvector4&b) const;

        //! Computes the inverse of this matrix
        constexpr Tensor22<inverse_t<T>> inverse() const noexcept
        {
            auto    di = one_v<T> / determinant();
            return {
                 di * yy, -di * xy,
                -di * yx,  di * xx
            };
        }

        /*! \brief Trace of the 2 x 2 tensor
        
            \param[in] a    Tensor to take the trace of
        */
        constexpr T     trace() const noexcept
        {
            return xx+yy;
        }

        //! Transpose of this matrix
        constexpr Tensor22  transpose() const noexcept
        {
            return {
                xx, yx,
                xy, yy
            };
        }


        //  --------------------------------------------------------
        //  GETTERS

            //! Returns the diagonal
            constexpr Vector2<T>  diagonal() const noexcept
            {
                return {xx, yy};
            }

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


        //  --------------------------------------------------------
        //  SETTERS

            //! Sets the diagonal
            Tensor22<T>&  diagonal(const Vector2<T>& v)
            {        
                xx = v.x;
                yy = v.y;
                return *this;
            }

            //! Sets the diagonal
            Tensor22<T>&  diagonal(T _xx, T _yy)
            {        
                xx = _xx;
                yy = _yy;
                return *this;
            }

            //! Sets the X-column
            Tensor22<T>& x_column(const Vector2<T>& v)
            {
                xx = v.x;
                yx = v.y;
                return *this;
            }

            //! Sets the X-column
            Tensor22<T>& x_column(T _xx, T _yx)
            {
                xx = _xx;
                yx = _yx;
                return *this;
            }

            //! Sets the Y-column
            Tensor22<T>& y_column(const Vector2<T>& v)
            {
                xy = v.x;
                yy = v.y;
                return *this;
            }

            //! Sets the Y-column
            Tensor22<T>& y_column(T _xy, T _yy)
            {
                xy = _xy;
                yy = _yy;
                return *this;
            }

            //! Sets the X-row
            Tensor22<T>& x_row(const Vector2<T>& v)
            {
                xx = v.x;
                xy = v.y;
                return *this;
            }

            //! Sets the X-row
            Tensor22<T>& x_row(T _xx, T _xy)
            {
                xx = _xx;
                xy = _xy;
                return *this;
            }

            //! Sets the Y-row
            Tensor22<T>& y_row(const Vector2<T>& v)
            {
                yx = v.x;
                yy = v.y;
                return *this;
            }
    
            //! Sets the Y-row
            Tensor22<T>& y_row(T _yx, T _yy)
            {
                yx = _yx;
                yy = _yy;
                return *this;
            }
    
    };

    YQ_IEEE754_1(Tensor22)
        
//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Create 2x2 tensor by columns
    */
    template <typename T>
    constexpr Tensor22<T>  columns(const Vector2<T>&x, const Vector2<T>&y)
    {
        return {
            x.x, y.x,
            x.y, y.y
        };
    }

    /*! \brief Create 2x2 tensor by its diagonal
    */
    template <typename T>
    constexpr Tensor22<T>  diagonal(const Vector2<T>&v)
    {
        return {
            v.x, zero_v<T>,
            zero_v<T>, v.y
        };
    }
    
    /*! \brief Create 2x2 tensor by its diagonal
    */
    template <typename T>
    constexpr Tensor22<T>  diagonal(T x, std::type_identity_t<T> y)
    {
        return {
            x, zero_v<T>,
            zero_v<T>, y
        };
    }
    

    /*! \brief Create 2x2 tensor by rows
    */
    template <typename T>
    constexpr Tensor22<T>  rows(const Vector2<T>&x, const Vector2<T>&y)
    {
        return {
            x.x, x.y,
            y.x, y.y
        };
    }
    
    //! Creates a matrix that can rotate a vector by the specfied angle
    //! In the counter-clockwise direction
    template <typename T>
    constexpr Tensor22<T>   rotation2(MKS<T,dim::Angle> r)
    {
        auto c  = cos(r);
        auto s  = sin(r);
        return {
            c, -s,
            s, c
        };
    }

    template <typename T, glm::qualifier Q>
    constexpr Tensor22<T> tensor(const glm::mat<2,2,T,Q>& t)
    {
        return {
            t.x.x, t.y.x, 
            t.x.y, t.y.y
        };
    }

    YQ_IDENTITY_1(Tensor22, {
        one_v<T>, zero_v<T>,
        zero_v<T>, one_v<T>
    })

    YQ_NAN_1(Tensor22, {
        nan_v<T>, nan_v<T>,
        nan_v<T>, nan_v<T> 
    })
    
    YQ_ZERO_1(Tensor22, {
        zero_v<T>, zero_v<T>,
        zero_v<T>, zero_v<T> 
     })
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor22, 
        is_finite(v.xx) && is_finite(v.xy) &&
        is_finite(v.yx) && is_finite(v.yy)
    )
    
    YQ_IS_NAN_1(Tensor22,  
        is_nan(v.xx) || is_nan(v.xy) ||
        is_nan(v.yx) || is_nan(v.yy)
    )

    /*! \brief Transpose of a 2x2 tensor
    */
    template <typename T>
    constexpr Tensor22<T>  transpose(const Tensor22<T>& ten)
    {
        return ten.transpose();
    }

//  --------------------------------------------------------
//  GETTERS

    /*! \brief Diagonal of the given tensor
    */
    template <typename T>
    constexpr Vector2<T>  diagonal(const Tensor22<T>& ten)
    {
        return ten.diagonal();
    }

    /*! \brief X-column of the given tensor
    */
    template <typename T>
    constexpr Vector2<T>  x_column(const Tensor22<T>&ten) 
    {
        return ten.x_column();
    }

    /*! \brief Y-column of the given tensor
    */
    template <typename T>
    constexpr Vector2<T>  y_column(const Tensor22<T>&ten) 
    {
        return ten.y_column();
    }

    /*! \brief X-row of the given tensor
    */
    template <typename T>
    constexpr Vector2<T>  x_row(const Tensor22<T>&ten)
    {
        return ten.x_row();
    }

    /*! \brief Y-row of the given tensor
    */
    template <typename T>
    constexpr Vector2<T>  y_row(const Tensor22<T>&ten)
    {
        return ten.y_row();
    }


//  --------------------------------------------------------
//  ADDITION

    template <typename T>
    constexpr Tensor22<T>   operator+ (const Tensor22<T> &a, const Tensor22<T> &b) 
    {
        return {
            a.xx+b.xx, a.xy+b.xy,
            a.yx+b.yx, a.yy+b.yy
        };
    }

    template <typename T>
    Tensor22<T>&   operator+=(Tensor22<T> &a, const Tensor22<T> &b) 
    {
        a.xx+=b.xx;  a.xy+=b.xy;
        a.yx+=b.yx;  a.yy+=b.yy;
        return a;
    }


//  --------------------------------------------------------
//  SUBTRACTION

    template <typename T>
    constexpr Tensor22<T>   operator- (const Tensor22<T> &a, const Tensor22<T> &b) 
    {
        return {
            a.xx-b.xx, a.xy-b.xy,
            a.yx-b.yx, a.yy-b.yy
        };
    }
    

    template <typename T>
    Tensor22<T>&   operator-=(Tensor22<T> &a, const Tensor22<T> &b) 
    {
        a.xx-=b.xx;  a.xy-=b.xy;
        a.yx-=b.yx;  a.yy-=b.yy;
        return a;
    }
    
//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires std::is_arithmetic_v<T>
    constexpr Tensor22<product_t<T,U>>  operator*(T a, const Tensor22<T>& b)
    {
        return {
            a*b.xx, a*b.xy,
            a*b.yx, a*b.yy
        };
    }
    
    
    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor22<product_t<T,U>>  operator*(const Tensor22<T>& a, U b)
    {
        return {
            a.xx*b, a.xy*b,
            a.yx*b, a.yy*b
        };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Tensor22<product_t<T,U>>  operator*=(const Tensor22<T>& a, U b)
    {
        a.xx*=b; a.xy*=b;
        a.yx*=b; a.yy*=b;        
        return a;
    }

    template <typename T, typename U>
    constexpr Tensor22<product_t<T,U>> operator*(const Tensor22<T>& a, const Tensor22<U>& b)
    {
        return {
            a.xx*b.xx + a.xy*b.yx,
            a.xx*b.xy + a.xy*b.yy,

            a.yx*b.xx + a.yy*b.yx,
            a.yx*b.xy + a.yy*b.yy
        };
    }
    
    template <typename T, typename U>
    requires trait::self_mul_v<T,U>
    Tensor22<T>& operator*=(Tensor22<T>&a, const Tensor22<U>& b)
    {
        a = a * b;
        return a;
    }

        
    template <typename T, typename U>
    constexpr Vector2<product_t<T,U>> operator*(const Tensor22<T>&a, const Vector2<U>&b)
    {
        return {
            a.xx*b.x + a.xy*b.y,
            a.yx*b.x + a.yy*b.y
        };
    }


//  --------------------------------------------------------
//  DIVISION


    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor22<quotient_t<T,U>>  operator/(const Tensor22<T>& a, U b)
    {
        return {
            a.xx/b, a.xy/b,
            a.yx/b, a.yy/b
        };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Tensor22<quotient_t<T,U>>  operator/=(const Tensor22<T>& a, U b)
    {
        a.xx/=b; a.xy/=b;
        a.yx/=b; a.yy/=b;        
        return a;
    }

//  --------------------------------------------------------
//  OTIMES PRODUCT


//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

    //! Determinant of a 2x2 tensor
    template <typename T>
    square_t<T> determinant(const Tensor22<T>& ten)
    {
        return ten.determinant();
    }

    //void        eigenvalues(zreal&,zreal&,zreal&,zreal&b) const;
    //void        eigensystem(zreal&,zvector4&,zreal&,zvector4&,zreal&,zvector4&,zreal&,zvector4&b) const;

    //! Inverse of a 2x2 tensor
    template <typename T>
    auto inverse(const Tensor22<T>&ten)
    {
        return ten.inverse();
    }

    /*! \brief Trace of the 2 x 2 tensor
    
        \param[in] a    Tensor to take the trace of
    */
    template <typename T>
    constexpr T     trace(const Tensor22<T>& ten)
    {
        return ten.trace();
    }

}

YQ_TYPE_DECLARE(yq::Tensor22D)
YQ_TYPE_DECLARE(yq::Tensor22F)
YQ_TYPE_DECLARE(yq::Tensor22I)
YQ_TYPE_DECLARE(yq::Tensor22U)

