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

        static constexpr const unsigned rows_count  = 2;
        static constexpr const unsigned cols_count  = 1;

        constexpr Tensor21() noexcept = default;

        constexpr Tensor21(
            T _xx, 
            T _yx
        ) : 
            xx(_xx),
            yx(_yx)
        {
        }
        
        constexpr Tensor21(all_t, T v) : 
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

        template <typename=void> requires trait::has_nan_v<T>
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

        constexpr operator glm::mat<2,1,T,glm::defaultp>() const noexcept ;

        //! Positive (affirmation) operator
        constexpr Tensor21  operator+() const noexcept;

        //! Negation operator
        constexpr Tensor21  operator-() const noexcept;

        constexpr Tensor21   operator+ (const Tensor21 &b) const noexcept;
        Tensor21&            operator+=(const Tensor21 &b) noexcept;
        constexpr Tensor21   operator- (const Tensor21 &b) const noexcept;
        Tensor21&            operator-=(const Tensor21 &b) noexcept;
        
        template <typename U>
        requires trait::is_arithmetic_v<U>
        constexpr Tensor21<product_t<T,U>>  operator*(U b) const noexcept;

        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>) 
        Tensor21&  operator*=(U b) noexcept;

        template <typename U>
        constexpr Tensor21<product_t<T,U>> operator*(const Tensor11<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor22<product_t<T,U>> operator*(const Tensor12<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor23<product_t<T,U>> operator*(const Tensor13<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor24<product_t<T,U>> operator*(const Tensor14<U>& b) const noexcept;

        template <typename U>
        requires trait::self_mul_v<T,U>
        Tensor21<T>& operator*=(const Tensor11<U>& b) noexcept;

        template <typename U>
        constexpr Vector2<product_t<T,U>> operator*(const Vector1<U>&b) const noexcept;

        template <typename U>
        requires trait::is_arithmetic_v<U>
        constexpr Tensor21<quotient_t<T,U>>  operator/(U b) const noexcept;

        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_div_v<T,U>) 
        Tensor21<T>&  operator/=(U b) noexcept;

        constexpr Tensor12<T> transpose() const noexcept;


        //  --------------------------------------------------------
        //  GETTERS

            constexpr Vector2<T>  x_column() const noexcept;
            constexpr Vector1<T>  x_row() const noexcept;
            constexpr Vector1<T>  y_row() const noexcept;
        //  --------------------------------------------------------
        //  SETTERS

            Tensor21& x_column(const Vector2<T>& v);

            Tensor21& x_column(T _xx, T _yx);

            Tensor21& x_row(const Vector1<T>& v);

            Tensor21& x_row(T _xx);

            Tensor21& y_row(const Vector1<T>& v);

            Tensor21& y_row(T _yx);

    };

    YQ_IEEE754_1(Tensor21)
        
//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Create 2x1 tensor by columns
    */
    template <typename T>
    constexpr Tensor21<T>  columns(const Vector2<T>&x)
    {
        return Tensor21<T>(COLUMNS, x);
    }

    /*! \brief Create 2x1 tensor by rows
    */
    template <typename T>
    constexpr Tensor21<T>  rows(const Vector1<T>&x, const Vector1<T>&y)
    {
        return Tensor21<T>(ROWS, x, y);
    }
    
    YQ_IDENTITY_1(Tensor21, Tensor21<T>(IDENTITY))
    YQ_NAN_1(Tensor21, Tensor21<T>(NAN))
    YQ_ZERO_1(Tensor21, Tensor21<T>(ZERO))
    
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

    template <typename T>
    constexpr Tensor12<T>  transpose(const Tensor21<T>&v);

//  --------------------------------------------------------
//  GETTERS

    template <typename T>
    constexpr Vector2<T>  x_column(const Tensor21<T>&ten);

    template <typename T>
    constexpr Vector1<T>  x_row(const Tensor21<T>&ten);

    template <typename T>
    constexpr Vector1<T>  y_row(const Tensor21<T>&ten);


//  --------------------------------------------------------
//  --------------------------------------------------------

    template <typename T, typename U>
    requires trait::is_arithmetic_v<T>
    constexpr Tensor21<product_t<T,U>>  operator*(T a, const Tensor21<U>& b);
    
}

YQ_TYPE_DECLARE(yq::Tensor21D)
YQ_TYPE_DECLARE(yq::Tensor21F)
YQ_TYPE_DECLARE(yq::Tensor21I)
YQ_TYPE_DECLARE(yq::Tensor21U)

