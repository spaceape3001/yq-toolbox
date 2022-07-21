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
        using component_type = T;
        T xx, xy;
        T yx, yy;

        constexpr bool operator==(const Tensor22&) const noexcept = default;

        operator glm::mat<2,2,T,glm::defaultp>() const noexcept 
        {
            return {
                xx, yx,
                xy, yy
            };
        }
    };

    YQ_IEEE754_1(Tensor22)
        
//  --------------------------------------------------------
//  COMPOSITION

    template <typename T>
    constexpr Tensor22<T>  columns(const Vector2<T>&x, const Vector2<T>&y)
    {
        return {
            x.x, y.x,
            x.y, y.y
        };
    }

    template <typename T>
    constexpr Tensor22<T>  diagonal(const Vector2<T>&v)
    {
        return {
            v.x, zero_v<T>,
            zero_v<T>, v.y
        };
    }
    
    template <typename T>
    constexpr Tensor22<T>  diagonal(T x, std::type_identity_t<T> y)
    {
        return {
            x, zero_v<T>,
            zero_v<T>, y
        };
    }
    

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

    template <typename T>
    constexpr Tensor22<T>  transpose(const Tensor22<T>&v)
    {
        return {
            v.xx, v.yx,
            v.xy, v.yy
        };
    }

//  --------------------------------------------------------
//  GETTERS

    template <typename T>
    constexpr Vector2<T>  diagonal(const Tensor22<T>& v)
    {
        return {v.xx, v.yy};
    }

    template <typename T>
    constexpr Vector2<T>  x_column(const Tensor22<T>&v) 
    {
        return {v.xx, v.yx};
    }

    template <typename T>
    constexpr Vector2<T>  y_column(const Tensor22<T>&v) 
    {
        return {v.xy, v.yy};
    }

    template <typename T>
    constexpr Vector2<T>  x_row(const Tensor22<T>&v)
    {
        return {v.xx, v.xy};
    }

    template <typename T>
    constexpr Vector2<T>  y_row(const Tensor22<T>&v)
    {
        return {v.yx, v.yy};
    }


//  --------------------------------------------------------
//  SETTERS

            
    template <typename T>
    Tensor22<T>&  set_diagonal(Tensor22<T>& ten, const Vector2<T>& v)
    {        ten.xx = v.x;
        ten.yy = v.y;
        return ten;
    }


    template <typename T>
    Tensor22<T>& set_x_column(Tensor22<T>&ten, const Vector2<T>& v)
    {
        ten.xx = v.x;
        ten.yx = v.y;
        return ten;
    }

    template <typename T>
    Tensor22<T>& set_y_column(Tensor22<T>&ten, const Vector2<T>& v)
    {
        ten.xy = v.x;
        ten.yy = v.y;
        return ten;
    }

    template <typename T>
    Tensor22<T>& set_x_row(Tensor22<T>&ten, const Vector2<T>& v)
    {
        ten.xx = v.x;
        ten.xy = v.y;
        return ten;
    }

    template <typename T>
    Tensor22<T>& set_y_row(Tensor22<T>&ten, const Vector2<T>& v)
    {
        ten.yx = v.x;
        ten.yy = v.y;
        return ten;
    }

//  --------------------------------------------------------
//  POSITIVE

    template <typename T>
    constexpr Tensor22<T>  operator+(const Tensor22<T>& a) 
    { 
        return a; 
    }


//  --------------------------------------------------------
//  NEGATIVE

    template <typename T>
    constexpr Tensor22<T>  operator-(const Tensor22<T>& a) 
    {
        return {
            -a.xx, -a.xy,
            -a.yx, -a.yy
        };
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

    template <typename T, typename U>
    constexpr Vector2<product_t<T,U>> operator*(const Vector2<T>&a, const Tensor22<U>&b)
    {
        return {
            a.x*b.xx + a.y*b.yx,
            a.x*b.xy + a.y*b.yy
        };
    }

    template <typename T, typename U>
    requires trait::self_mul_v<T,U>
    Vector2<T>& operator*=(Vector2<T>&a, const Tensor22<U>& b)
    {
        a = a * b;
        return a;
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

    template <typename T, typename U>
    constexpr Tensor22<product_t<T,U>> operator OTIMES(const Vector2<T>&a, const Vector2<U>&b)
    {
        return {
            a.x+b.x, a.x+b.y,
            a.y+b.x, a.y+b.y
        };
    }

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

    /*! \brief Trace of the 2 x 2 tensor
    
        \param[in] a    Tensor to take the trace of
    */
    template <typename T>
    constexpr T     trace(const Tensor22<T>& a)
    {
        return a.xx+a.yy;
    }

}

YQ_TYPE_DECLARE(yq::Tensor22D)
YQ_TYPE_DECLARE(yq::Tensor22F)
YQ_TYPE_DECLARE(yq::Tensor22I)
YQ_TYPE_DECLARE(yq::Tensor22U)

