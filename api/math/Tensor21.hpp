////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__TENSOR_2_1__HPP 1
#include <math/preamble.hpp>
#include <math/Vector1.hpp>
#include <math/Vector2.hpp>

namespace yq {
    /*! \brief 2x1 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor21 {
    
        //! Component type (captures template parameter)
        using component_type = T;
        T xx;
        T yx;


        constexpr Tensor21() noexcept = default;

        constexpr Tensor21(
            T _xx, 
            T _yx
        ) : 
            xx(_xx),
            yx(_yx)
        {
        }
        
        consteval Tensor21(all_t, T v) : 
            xx(v), 
            yx(v)
        {
        }

        constexpr Tensor21(columns_t, const Vector2<T>& x) noexcept :
            xx(x.x),
            yx(x.y)
        {
        }

        consteval Tensor21(identity_t) : 
            xx(one_v<T>),  
            yx(zero_v<T>)
        {
        }

        consteval Tensor21(nan_t) : Tensor21(ALL, nan_v<T>) {}

        constexpr Tensor21(rows_t, const Vector1<T>& x, const Vector1<T>& y) :
            xx(x.x), 
            yx(y.x)
        {
        }

        consteval Tensor21(zero_t) : Tensor21(ALL, zero_v<T>) {} 
        
        template <glm::qualifier Q>
        explicit constexpr Tensor21(const glm::mat<2,1,T,Q>& t) noexcept;
        
        
        //! Defaulted equality operator
        constexpr bool operator==(const Tensor21&) const noexcept = default;

        //! Positive (affirmation) operator
        constexpr Tensor21  operator+() const noexcept
        { 
            return *this; 
        }

        //! Negation operator
        constexpr Tensor21  operator-() const noexcept
        {
            return {
                -xx,
                -yx
            };
        }

        //  --------------------------------------------------------
        //  GETTERS

            constexpr Vector2<T>  x_column() const noexcept
            {
                return {xx, yx};
            }

            constexpr Vector1<T>  x_row() const noexcept
            {
                return {xx};
            }

            constexpr Vector1<T>  y_row() const noexcept
            {
                return {yx};
            }

        //  --------------------------------------------------------
        //  SETTERS

            Tensor21& x_column(const Vector2<T>& v)
            {
                xx = v.x;
                yx = v.y;
                return *this;
            }

            Tensor21& x_column(T _xx, T _yx)
            {
                xx = _xx;
                yx = _yx;
                return *this;
            }

            Tensor21& x_row(const Vector1<T>& v)
            {
                xx = v.x;
                return *this;
            }

            Tensor21& x_row(T _xx)
            {
                xx = _xx;
                return *this;
            }

            Tensor21& y_row(const Vector1<T>& v)
            {
                yx = v.x;
                return *this;
            }

            Tensor21& y_row(T _yx)
            {
                yx = _yx;
                return *this;
            }


    };

    YQ_IEEE754_1(Tensor21)
        
//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Create 2x1 tensor by columns
    */
    template <typename T>
    constexpr Tensor21<T>  columns(const Vector2<T>&x)
    {
        return {
            x.x,
            x.y
        };
    }

    /*! \brief Create 2x1 tensor by rows
    */
    template <typename T>
    constexpr Tensor21<T>  rows(const Vector1<T>&x, const Vector1<T>&y)
    {
        return {
            x.x,
            y.x
        };
    }
    
    YQ_IDENTITY_1(Tensor21, {
        one_v<T>,
        zero_v<T>
    })

    YQ_NAN_1(Tensor21, {
        nan_v<T>,
        nan_v<T> 
    })
    
    YQ_ZERO_1(Tensor21, {
        zero_v<T>,
        zero_v<T> 
     })
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor21, 
        is_finite(v.xx) &&
        is_finite(v.yx)
    )
    
    YQ_IS_NAN_1(Tensor21,  
        is_nan(v.xx) ||
        is_nan(v.yx)
    )

//  --------------------------------------------------------
//  GETTERS

    template <typename T>
    constexpr Vector2<T>  x_column(const Tensor21<T>&ten) 
    {
        return ten.x_column();
    }

    template <typename T>
    constexpr Vector1<T>  x_row(const Tensor21<T>&ten)
    {
        return ten.x_row();
    }

    template <typename T>
    constexpr Vector1<T>  y_row(const Tensor21<T>&ten)
    {
        return ten.y_row();
    }



//  --------------------------------------------------------
//  ADDITION

    template <typename T>
    constexpr Tensor21<T>   operator+ (const Tensor21<T> &a, const Tensor21<T> &b) 
    {
        return {
            a.xx+b.xx,
            a.yx+b.yx
        };
    }

    template <typename T>
    Tensor21<T>&   operator+=(Tensor21<T> &a, const Tensor21<T> &b) 
    {
        a.xx+=b.xx;
        a.yx+=b.yx;
        return a;
    }


//  --------------------------------------------------------
//  SUBTRACTION

    template <typename T>
    constexpr Tensor21<T>   operator- (const Tensor21<T> &a, const Tensor21<T> &b) 
    {
        return {
            a.xx-b.xx,
            a.yx-b.yx
        };
    }
    

    template <typename T>
    Tensor21<T>&   operator-=(Tensor21<T> &a, const Tensor21<T> &b) 
    {
        a.xx-=b.xx;
        a.yx-=b.yx;
        return a;
    }
    
//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires std::is_arithmetic_v<T>
    constexpr Tensor21<product_t<T,U>>  operator*(T a, const Tensor21<T>& b)
    {
        return {
            a*b.xx,
            a*b.yx
        };
    }
    
    
    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor21<product_t<T,U>>  operator*(const Tensor21<T>& a, U b)
    {
        return {
            a.xx*b,
            a.yx*b
        };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Tensor21<product_t<T,U>>  operator*=(const Tensor21<T>& a, U b)
    {
        a.xx*=b;
        a.yx*=b;        
        return a;
    }

        
    template <typename T, typename U>
    constexpr Vector2<product_t<T,U>> operator*(const Tensor21<T>&a, const Vector1<U>&b)
    {
        return {
            a.xx*b.x,
            a.yx*b.x
        };
    }

//  --------------------------------------------------------
//  DIVISION


    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor21<quotient_t<T,U>>  operator/(const Tensor21<T>& a, U b)
    {
        return {
            a.xx/b,
            a.yx/b
        };
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Tensor21<quotient_t<T,U>>  operator/=(const Tensor21<T>& a, U b)
    {
        a.xx/=b;
        a.yx/=b;        
        return a;
    }

//  --------------------------------------------------------
//  OTIMES PRODUCT

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

}

YQ_TYPE_DECLARE(yq::Tensor21D)
YQ_TYPE_DECLARE(yq::Tensor21F)
YQ_TYPE_DECLARE(yq::Tensor21I)
YQ_TYPE_DECLARE(yq::Tensor21U)

