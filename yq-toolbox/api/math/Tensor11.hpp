////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__TENSOR_1_1__HPP 1
#include <math/preamble.hpp>
#include <math/Vector1.hpp>

namespace yq {
    /*! \brief 1x1 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor11 {
        using component_type = T;
        T xx;

        constexpr bool operator==(const Tensor11&) const noexcept = default;
    };

    YQ_IEEE754_1(Tensor11)
        
//  --------------------------------------------------------
//  COMPOSITION

    template <typename T>
    constexpr Tensor11<T>  columns(const Vector1<T>&x)
    {
        return {
            x.x
        };
    }

    template <typename T>
    constexpr Tensor11<T>  diagonal(const Vector1<T>&v)
    {
        return {
            v.x
        };
    }
    
    template <typename T>
    constexpr Tensor11<T>  diagonal(T x)
    {
        return {
            x
        };
    }

    template <typename T>
    constexpr Tensor11<T>  rows(const Vector1<T>&x)
    {
        return {
            x.x
        };
    }
    
    YQ_IDENTITY_1(Tensor11, {
        one_v<T>
    })

    YQ_NAN_1(Tensor11, {
        nan_v<T> 
    })
    
    YQ_ZERO_1(Tensor11, {
        zero_v<T> 
     })
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor11, 
        is_finite(v.xx)
    )
    
    YQ_IS_NAN_1(Tensor11,  
        is_nan(v.xx)
    )

    template <typename T>
    constexpr Tensor11<T>  transpose(const Tensor11<T>&v)
    {
        return {
            v.xx
        };
    }

//  --------------------------------------------------------
//  GETTERS

    template <typename T>
    constexpr Vector1<T>  diagonal(const Tensor11<T>& v)
    {
        return {v.xx};
    }

    template <typename T>
    constexpr Vector1<T>  x_column(const Tensor11<T>&v) 
    {
        return {v.xx};
    }

    template <typename T>
    constexpr Vector1<T>  x_row(const Tensor11<T>&v)
    {
        return {v.xx};
    }


//  --------------------------------------------------------
//  SETTERS

            
    template <typename T>
    Tensor11<T>&  set_diagonal(Tensor11<T>& ten, const Vector1<T>& v)
    {        ten.xx = v.x;
        return ten;
    }


    template <typename T>
    Tensor11<T>& set_x_column(Tensor11<T>&ten, const Vector1<T>& v)
    {
        ten.xx = v.x;
        return ten;
    }

    template <typename T>
    Tensor11<T>& set_x_row(Tensor11<T>&ten, const Vector1<T>& v)
    {
        ten.xx = v.x;
        return ten;
    }

//  --------------------------------------------------------
//  POSITIVE

    template <typename T>
    constexpr Tensor11<T>  operator+(const Tensor11<T>& a) 
    { 
        return a; 
    }


//  --------------------------------------------------------
//  NEGATIVE

    template <typename T>
    constexpr Tensor11<T>  operator-(const Tensor11<T>& a) 
    {
        return {
            -a.xx
        };
    }


//  --------------------------------------------------------
//  ADDITION

    template <typename T>
    constexpr Tensor11<T>   operator+ (const Tensor11<T> &a, const Tensor11<T> &b) 
    {
        return {
            a.xx+b.xx
        };
    }

    template <typename T>
    Tensor11<T>&   operator+=(Tensor11<T> &a, const Tensor11<T> &b) 
    {
        a.xx+=b.xx;
        return a;
    }


//  --------------------------------------------------------
//  SUBTRACTION

    template <typename T>
    constexpr Tensor11<T>   operator- (const Tensor11<T> &a, const Tensor11<T> &b) 
    {
        return {
            a.xx-b.xx
        };
    }
    

    template <typename T>
    Tensor11<T>&   operator-=(Tensor11<T> &a, const Tensor11<T> &b) 
    {
        a.xx-=b.xx;
        return a;
    }
    
//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires std::is_arithmetic_v<T>
    constexpr Tensor11<product_t<T,U>>  operator*(T a, const Tensor11<T>& b)
    {
        return {
            a*b.xx
        };
    }
    
    
    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor11<product_t<T,U>>  operator*(const Tensor11<T>& a, U b)
    {
        return {
            a.xx*b
        };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Tensor11<product_t<T,U>>  operator*=(const Tensor11<T>& a, U b)
    {
        a.xx*=b;        
        return a;
    }

    template <typename T, typename U>
    constexpr Tensor11<product_t<T,U>> operator*(const Tensor11<T>& a, const Tensor11<U>& b)
    {
        return {
            a.xx*b.xx
        };
    }
    
    template <typename T, typename U>
    requires trait::self_mul_v<T,U>
    Tensor11<T>& operator*=(Tensor11<T>&a, const Tensor11<U>& b)
    {
        a = a * b;
        return a;
    }

        
    template <typename T, typename U>
    constexpr Vector1<product_t<T,U>> operator*(const Tensor11<T>&a, const Vector1<U>&b)
    {
        return {
            a.xx*b.x
        };
    }

    template <typename T, typename U>
    constexpr Vector1<product_t<T,U>> operator*(const Vector1<T>&a, const Tensor11<U>&b)
    {
        return {
            a.x*b.xx
        };
    }

    template <typename T, typename U>
    requires trait::self_mul_v<T,U>
    Vector1<T>& operator*=(Vector1<T>&a, const Tensor11<U>& b)
    {
        a = a * b;
        return a;
    }

//  --------------------------------------------------------
//  DIVISION


    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor11<quotient_t<T,U>>  operator/(const Tensor11<T>& a, U b)
    {
        return {
            a.xx/b
        };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Tensor11<quotient_t<T,U>>  operator/=(const Tensor11<T>& a, U b)
    {
        a.xx/=b;        
        return a;
    }

//  --------------------------------------------------------
//  OTIMES PRODUCT

    template <typename T, typename U>
    constexpr Tensor11<product_t<T,U>> operator OTIMES(const Vector1<T>&a, const Vector1<U>&b)
    {
        return {
            a.x+b.x
        };
    }

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

    /*! \brief Trace of the 1 x 1 tensor
    
        \param[in] a    Tensor to take the trace of
    */
    template <typename T>
    constexpr T     trace(const Tensor11<T>& a)
    {
        return a.xx;
    }

}

YQ_TYPE_DECLARE(yq::Tensor11D)
YQ_TYPE_DECLARE(yq::Tensor11F)
YQ_TYPE_DECLARE(yq::Tensor11I)
YQ_TYPE_DECLARE(yq::Tensor11U)

