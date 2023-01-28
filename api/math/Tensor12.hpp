////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__TENSOR_1_2__HPP 1
#include <math/preamble.hpp>
#include <math/Vector1.hpp>
#include <math/Vector2.hpp>

namespace yq {

    /*! \brief 1x2 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor12 {
    
        //! Component type
        using component_type = T;
        
        T xx, xy;
        
        constexpr Tensor12() noexcept {}
        constexpr Tensor12(T _xx, T _xy) noexcept : xx(_xx), xy(_xy) {}
        constexpr Tensor12(columns_t, const Vector1<T>& x, const Vector1<T>& y) noexcept : xx(x.x), xy(y.x) {}
        consteval Tensor12(identity_t) noexcept : xx(one_v<T>), xy(zero_v<T>) {}
        constexpr Tensor12(rows_t, Vector2<T>& v) noexcept : xx(v.x), xy(v.y) {}
        constexpr Tensor12(ordered_t, T _xx, T _xy) noexcept : xx(_xx), xy(_xy) {}
        consteval Tensor12(zero_t) noexcept : xx(zero_v<T>), xy(zero_v<T>) {}
        

        //! Defaulted equality operator
        constexpr bool operator==(const Tensor12&) const noexcept = default;

        //! Positive (affirmation) operator
        constexpr Tensor12  operator+() const noexcept
        { 
            return *this; 
        }


        //! Negation
        constexpr Tensor12  operator-() const noexcept
        {
            return Tensor12(
                -xx, -xy
            );
        }


        //  --------------------------------------------------------
        //  GETTERS

            //! Gets the x-column as a vector
            constexpr Vector1<T>  x_column() const noexcept
            {
                return Vector1<T>(xx);
            }

            //! Gets the y-column as a vector
            constexpr Vector1<T>  y_column() const noexcept
            {
                return Vector1<T>(xy);
            }

            //! Gets the x-row as a vector
            constexpr Vector2<T>  x_row() const noexcept
            {
                return Vector2<T>(xx, xy);
            }

        //  --------------------------------------------------------
        //  SETTERS

            //! Sets the X-column
            Tensor12& x_column(const Vector1<T>& v)
            {
                xx = v.x;
                return *this;
            }

            //! Sets the X-column
            Tensor12& x_column(T _xx)
            {
                xx = _xx;
                return *this;
            }

            //! Sets the Y-column
            Tensor12& y_column(const Vector1<T>& v)
            {
                xy = v.x;
                return *this;
            }

            //! Sets the Y-column
            Tensor12& y_column(T _xy)
            {
                xy = _xy;
                return *this;
            }

            //! Sets the X-row
            Tensor12& x_row(const Vector2<T>& v)
            {
                xx = v.x;
                xy = v.y;
                return *this;
            }

            //! Sets the X-row
            Tensor12& x_row(T _xx, T _xy)
            {
                xx = _xx;
                xy = _xy;
                return *this;
            }

    };

    YQ_IEEE754_1(Tensor12)
        
//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Create 1x2 tensor by columns
    */
    template <typename T>
    constexpr Tensor12<T>  columns(const Vector1<T>&x, const Vector1<T>&y)
    {
        return Tensor12<T>(columns_, x, y);
    }

    /*! \brief Create 1x2 tensor by rows
    */
    template <typename T>
    constexpr Tensor12<T>  rows(const Vector2<T>&x)
    {
        return Tensor12<T>(rows_, x);
    }
    
    YQ_IDENTITY_1(Tensor12, {
        one_v<T>, zero_v<T>
    })

    YQ_NAN_1(Tensor12, {
        nan_v<T>, nan_v<T> 
    })
    
    YQ_ZERO_1(Tensor12, {
        zero_v<T>, zero_v<T> 
     })
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor12, 
        is_finite(v.xx) && is_finite(v.xy)
    )
    
    YQ_IS_NAN_1(Tensor12,  
        is_nan(v.xx) || is_nan(v.xy)
    )

//  --------------------------------------------------------
//  GETTERS

    template <typename T>
    constexpr Vector1<T>  x_column(const Tensor12<T>&ten) 
    {
        return ten.x_column();
    }

    template <typename T>
    constexpr Vector1<T>  y_column(const Tensor12<T>&ten) 
    {
        return ten.y_column();
    }

    template <typename T>
    constexpr Vector2<T>  x_row(const Tensor12<T>&ten)
    {   
        return ten.x_row();
    }

//  --------------------------------------------------------
//  ADDITION

    template <typename T>
    constexpr Tensor12<T>   operator+ (const Tensor12<T> &a, const Tensor12<T> &b) 
    {
        return Tensor12<T>(
            a.xx+b.xx, a.xy+b.xy
        );
    }

    template <typename T>
    Tensor12<T>&   operator+=(Tensor12<T> &a, const Tensor12<T> &b) 
    {
        a.xx+=b.xx;  a.xy+=b.xy;
        return a;
    }


//  --------------------------------------------------------
//  SUBTRACTION

    template <typename T>
    constexpr Tensor12<T>   operator- (const Tensor12<T> &a, const Tensor12<T> &b) 
    {
        return Tensor12<T>(
            a.xx-b.xx, a.xy-b.xy
        );
    }
    

    template <typename T>
    Tensor12<T>&   operator-=(Tensor12<T> &a, const Tensor12<T> &b) 
    {
        a.xx-=b.xx;  a.xy-=b.xy;
        return a;
    }
    
//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires std::is_arithmetic_v<T>
    constexpr Tensor12<product_t<T,U>>  operator*(T a, const Tensor12<U>& b)
    {
        return Tensor12<product_t<T,U>>(
            a*b.xx, a*b.xy
        );
    }
    
    
    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor12<product_t<T,U>>  operator*(const Tensor12<T>& a, U b)
    {
        return Tensor12<product_t<T,U>>(
            a.xx*b, a.xy*b
        );
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Tensor12<product_t<T,U>>  operator*=(const Tensor12<T>& a, U b)
    {
        a.xx*=b; a.xy*=b;        
        return a;
    }

        
    template <typename T, typename U>
    constexpr Vector1<product_t<T,U>> operator*(const Tensor12<T>&a, const Vector2<U>&b)
    {
        return Vector1<product_t<T,U>>(
            a.xx*b.x + a.xy*b.y
        );
    }

    template <typename T, typename U>
    constexpr Vector2<product_t<T,U>> operator*(const Vector1<T>&a, const Tensor12<U>&b)
    {
        return Vector2<product_t<T,U>>(
            a.x*b.xx,
            a.x*b.xy
        );
    }

//  --------------------------------------------------------
//  DIVISION


    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor12<quotient_t<T,U>>  operator/(const Tensor12<T>& a, U b)
    {
        return Tensor12<quotient_t<T,U>> (
            a.xx/b, a.xy/b
        );
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Tensor12<quotient_t<T,U>>  operator/=(const Tensor12<T>& a, U b)
    {
        a.xx/=b; a.xy/=b;        
        return a;
    }

//  --------------------------------------------------------
//  OTIMES PRODUCT

    template <typename T, typename U>
    constexpr Tensor12<product_t<T,U>> operator OTIMES(const Vector1<T>&a, const Vector2<U>&b)
    {
        return Tensor12<product_t<T,U>>(
            a.x+b.x, a.x+b.y
        );
    }

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

}

YQ_TYPE_DECLARE(yq::Tensor12D)
YQ_TYPE_DECLARE(yq::Tensor12F)
YQ_TYPE_DECLARE(yq::Tensor12I)
YQ_TYPE_DECLARE(yq::Tensor12U)

