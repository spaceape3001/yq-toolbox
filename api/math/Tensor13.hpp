////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__TENSOR_1_3__HPP 1
#include <math/preamble.hpp>
#include <math/Vector1.hpp>
#include <math/Vector3.hpp>

namespace yq {
    /*! \brief 1x3 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor13 {
    
        //! Component type (captures the template parameter)
        using component_type = T;
        static constexpr const unsigned rows_count  = 1;
        static constexpr const unsigned cols_count  = 3;

        T xx, xy, xz;
        
        constexpr Tensor13() noexcept = default;

        constexpr Tensor13(
            T _xx, T _xy, T _xz
        ) : 
            xx(_xx), xy(_xy), xz(_xz)
        {
        }
        
        consteval Tensor13(all_t, T v) : 
            xx(v), xy(v), xz(v)
        {
        }

        constexpr Tensor13(columns_t, const Vector1<T>& x, const Vector1<T>& y, const Vector1<T>& z) noexcept :
            xx(x.x), xy(y.x), xz(z.x)
        {
        }


        consteval Tensor13(identity_t) : 
            xx(one_v<T>),  xy(zero_v<T>), xz(zero_v<T>)
        {
        }

        consteval Tensor13(nan_t) : Tensor13(ALL, nan_v<T>) {}

        constexpr Tensor13(rows_t, const Vector3<T>& x) :
            xx(x.x), xy(x.y), xz(x.z)
        {
        }

        consteval Tensor13(zero_t) : Tensor13(ALL, zero_v<T>) {}
        
        template <glm::qualifier Q>
        explicit constexpr Tensor13(const glm::mat<1,3,T,Q>& t) noexcept;
        
        //! Defaulted equality operator
        constexpr bool operator==(const Tensor13&) const noexcept = default;

        constexpr operator glm::mat<1,3,T,glm::defaultp>() const noexcept;

        //! Positive (affirmation) operator
        constexpr Tensor13  operator+() const noexcept;

        //! Negation operator
        constexpr Tensor13  operator-() const noexcept;

        constexpr Tensor13  operator+ (const Tensor13 &b) const noexcept;
        Tensor13&           operator+=(const Tensor13 &b) noexcept;
        constexpr Tensor13  operator- (const Tensor13 &b) const noexcept;
        Tensor13&           operator-=(const Tensor13 &b) noexcept;
        
        template <typename U>
        requires trait::is_arithmetic_v<U>
        constexpr Tensor13<product_t<T,U>>  operator*(U b) const noexcept;

        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
        Tensor13&  operator*=(U b) noexcept;

        template <typename U>
        constexpr Tensor11<product_t<T,U>> operator*(const Tensor31<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor12<product_t<T,U>> operator*(const Tensor32<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor13<product_t<T,U>> operator*(const Tensor33<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor14<product_t<T,U>> operator*(const Tensor34<U>& b) const noexcept;

        template <typename U>
        requires trait::self_mul_v<T,U>
        Tensor13& operator*=(const Tensor33<U>& b) noexcept;

        template <typename U>
        constexpr Vector1<product_t<T,U>> operator*(const Vector3<U>&b) const noexcept;

        template <typename U>
        requires trait::is_arithmetic_v<U>
        constexpr Tensor13<quotient_t<T,U>>  operator/(U b) const noexcept;

        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_div_v<T,U>)
        Tensor13&  operator/=(U b) noexcept;

        constexpr Tensor31<T> transpose() const noexcept;

        //  --------------------------------------------------------
        //  GETTERS

            constexpr Vector1<T>  x_column() const noexcept;

            constexpr Vector1<T>  y_column() const noexcept;

            constexpr Vector1<T>  z_column() const noexcept;

            constexpr Vector3<T>  x_row() const noexcept;



        //  --------------------------------------------------------
        //  SETTERS

            Tensor13& x_column(const Vector1<T>& v);

            Tensor13& x_column(T _xx);

            Tensor13& y_column(const Vector1<T>& v);

            Tensor13& y_column(T _xy);

            Tensor13& z_column(const Vector1<T>& v);


            Tensor13& z_column(T _xz);

            Tensor13& x_row(const Vector3<T>& v);

            Tensor13& x_row(T _xx, T _xy, T _xz);
    };

    YQ_IEEE754_1(Tensor13)
        
//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Create 1x3 tensor by columns
    */
    template <typename T>
    constexpr Tensor13<T>  columns(const Vector1<T>&x, const Vector1<T>&y, const Vector1<T>&z)
    {
        return Tensor13<T>(COLUMNS, x, y, z);
    }

    /*! \brief Create 1x3 tensor by rows
    */
    template <typename T>
    constexpr Tensor13<T>  rows(const Vector3<T>&x)
    {
        return Tensor13<T>(ROWS, x );
    }
    
    YQ_IDENTITY_1(Tensor13, Tensor13<T>(IDENTITY))
    YQ_NAN_1(Tensor13, Tensor13<T>(NAN))
    YQ_ZERO_1(Tensor13, Tensor13<T>(ZERO))
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor13, 
        is_finite(v.xx) && is_finite(v.xy) && is_finite(v.xz)
    )
    
    YQ_IS_NAN_1(Tensor13,  
        is_nan(v.xx) || is_nan(v.xy) || is_nan(v.xz)
    )

    template <typename T>
    constexpr Tensor31<T>  transpose(const Tensor13<T>&v);

//  --------------------------------------------------------
//  GETTERS

    template <typename T>
    constexpr Vector1<T>  x_column(const Tensor13<T>&ten);

    template <typename T>
    constexpr Vector1<T>  y_column(const Tensor13<T>&ten);

    template <typename T>
    constexpr Vector1<T>  z_column(const Tensor13<T>&ten);

    template <typename T>
    constexpr Vector3<T>  x_row(const Tensor13<T>&ten);


//  --------------------------------------------------------
//  --------------------------------------------------------

    template <typename T, typename U>
    requires trait::is_arithmetic_v<T>
    constexpr Tensor13<product_t<T,U>>  operator*(T a, const Tensor13<U>& b);
    
    
}

YQ_TYPE_DECLARE(yq::Tensor13D)
YQ_TYPE_DECLARE(yq::Tensor13F)
YQ_TYPE_DECLARE(yq::Tensor13I)
YQ_TYPE_DECLARE(yq::Tensor13U)

