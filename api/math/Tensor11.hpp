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
    
        //! Component type captures the template parameter
        using component_type = T;
        T xx;

        //! Defaulted equality operator
        constexpr bool operator==(const Tensor11&) const noexcept = default;
        
        constexpr Tensor11  operator+() const noexcept
        { 
            return *this; 
        }

        constexpr Tensor11  operator-() const noexcept
        {
            return {
                -xx
            };
        }

        constexpr Tensor11   operator+ (const Tensor11 &b) const noexcept
        {
            return {
                xx+b.xx
            };
        }

        Tensor11&   operator+=(const Tensor11 &b) 
        {
            xx+=b.xx;
            return *this;
        }

        constexpr Tensor11   operator- (const Tensor11 &b) const noexcept
        {
            return {
                xx-b.xx
            };
        }
        
        Tensor11&   operator-=(const Tensor11 &b) 
        {
            xx-=b.xx;
            return *this;
        }
    
            //! Returns the determinant
        constexpr T determinant() const noexcept
        {
            return xx;
        }

            //! Returns the trace
        constexpr T     trace() const noexcept
        {
            return xx;
        }

        //! Transpose, which is itself for a 1x1
        constexpr Tensor11 transpose() const 
        { 
            return { xx }; 
        }

        //  --------------------------------------------------------
        //  GETTERS

            //! Gets the diagonal as a vector
            constexpr Vector1<T>  diagonal() const noexcept
            {
                return {xx};
            }

            //! Gets the x-column as a vector
            constexpr Vector1<T>  x_column()  const noexcept
            {
                return {xx};
            }

            //! Gets the x-row as a vector
            constexpr Vector1<T>  x_row() const noexcept
            {
                return {xx};
            }

        //  --------------------------------------------------------
        //  SETTERS

            //! Sets the diagonal
            Tensor11&   diagonal(const Vector1<T>& v)
            {        
                xx = v.x;
                return *this;
            }

            //! Sets the diagonal
            Tensor11&   diagonal(T _xx)
            {        
                xx = _xx;
                return *this;
            }

            //! Sets the x-column
            Tensor11& x_column(const Vector1<T>& v)
            {
                xx = v.x;
                return *this;
            }

            //! Sets the x-column
            Tensor11& x_column(T _xx)
            {
                xx = _xx;
                return *this;
            }

            //! Sets the x-row
            Tensor11& x_row(const Vector1<T>& v)
            {
                xx = v.x;
                return *this;
            }

            //! Sets the x-row
            Tensor11& x_row(T _xx)
            {
                xx = _xx;
                return *this;
            }
    };

    YQ_IEEE754_1(Tensor11)
        
//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Create 1x1 tensor by columns
    */
    template <typename T>
    constexpr Tensor11<T>  columns(const Vector1<T>&x)
    {
        return {
            x.x
        };
    }

    /*! \brief Create 1x1 tensor by its diagonal
    */
    template <typename T>
    constexpr Tensor11<T>  diagonal(const Vector1<T>&v)
    {
        return {
            v.x
        };
    }
    
    /*! \brief Create 1x1 tensor by its diagonal
    */
    template <typename T>
    constexpr Tensor11<T>  diagonal(T x)
    {
        return {
            x
        };
    }

    /*! \brief Create 1x1 tensor by rows
    */
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
        return v.diagonal();
    }

    template <typename T>
    constexpr Vector1<T>  x_column(const Tensor11<T>&v) 
    {
        return v.x_column();
    }

    template <typename T>
    constexpr Vector1<T>  x_row(const Tensor11<T>&v)
    {
        return v.x_row();
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

    template <typename T>
    constexpr T determinant(const Tensor11<T>& a)
    {
        return a.determinant();
    }

    /*! \brief Trace of the 1 x 1 tensor
    
        \param[in] a    Tensor to take the trace of
    */
    template <typename T>
    constexpr T     trace(const Tensor11<T>& a)
    {
        return a.trace();
    }

}

YQ_TYPE_DECLARE(yq::Tensor11D)
YQ_TYPE_DECLARE(yq::Tensor11F)
YQ_TYPE_DECLARE(yq::Tensor11I)
YQ_TYPE_DECLARE(yq::Tensor11U)

