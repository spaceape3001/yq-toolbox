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
        
        static constexpr const unsigned rows_count  = 1;
        static constexpr const unsigned cols_count  = 2;
        
        T xx, xy;
        
        constexpr Tensor12() noexcept {}
        constexpr Tensor12(T _xx, T _xy) noexcept : xx(_xx), xy(_xy) {}
        constexpr Tensor12(all_t, T v) : 
            xx(v), xy(v)
        {
        }
        constexpr Tensor12(columns_t, const Vector1<T>& x, const Vector1<T>& y) noexcept : xx(x.x), xy(y.x) {}
        consteval Tensor12(identity_t) noexcept : xx(one_v<T>), xy(zero_v<T>) {}
        template <typename=void> requires trait::has_nan_v<T>
        consteval Tensor12(nan_t) noexcept : Tensor12(ALL, nan_v<T>) {}
        constexpr Tensor12(rows_t, Vector2<T>& v) noexcept : xx(v.x), xy(v.y) {}
        consteval Tensor12(zero_t) noexcept : Tensor12(ALL, zero_v<T>) {}
        
        template <glm::qualifier Q>
        explicit constexpr Tensor12(const glm::mat<1,2,T,Q>& t) noexcept;

        //! Defaulted equality operator
        constexpr bool operator==(const Tensor12&) const noexcept = default;

        constexpr operator glm::mat<1,2,T,glm::defaultp>() const noexcept;

        //! Positive (affirmation) operator
        constexpr Tensor12  operator+() const noexcept;

        //! Negation
        constexpr Tensor12  operator-() const noexcept;

        constexpr Tensor12<T>   operator+ (const Tensor12<T> &b) const noexcept;
        Tensor12<T>&            operator+=(const Tensor12<T> &b) noexcept;
        constexpr Tensor12<T>   operator- (const Tensor12<T> &b) const noexcept;
        Tensor12<T>&            operator-=(const Tensor12<T> &b) noexcept;

        template <typename U>
        requires trait::is_arithmetic_v<U>
        constexpr Tensor12<trait::product_t<T,U>>  operator*(U b) const noexcept;

        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
        Tensor12<trait::product_t<T,U>>            operator*=(U b) noexcept;

        template <typename U>
        constexpr Segment1<trait::product_t<T,U>>  operator*(const Segment2<U>&) const noexcept;

        template <typename U>
        constexpr Tensor11<trait::product_t<T,U>> operator*(const Tensor21<U>& b) const noexcept;

        template <typename U>
        constexpr Tensor12<trait::product_t<T,U>> operator*(const Tensor22<U>& b) const noexcept;

        template <typename U>
        requires trait::self_mul_v<T,U>
        Tensor12<T>& operator*=(const Tensor22<U>& b) noexcept;

        template <typename U>
        constexpr Tensor13<trait::product_t<T,U>> operator*(const Tensor23<U>& b) const noexcept;

        template <typename U>
        constexpr Tensor14<trait::product_t<T,U>> operator*(const Tensor24<U>& b) const noexcept;

        template <typename U>
        constexpr Vector1<trait::product_t<T,U>>   operator*(const Vector2<U>&b) const noexcept;

        template <typename U>
        std::vector<Vector1<trait::product_t<T,U>>>    operator*(std::span<const Vector2<U>> b) const;

        template <typename U>
        requires trait::is_arithmetic_v<U>
        constexpr Tensor12<trait::quotient_t<T,U>>  operator/(U b) const noexcept;

        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_div_v<T,U>)
        Tensor12<trait::quotient_t<T,U>>               operator/=(U b) noexcept;

        constexpr Tensor21<T> transpose() const noexcept;

        //  --------------------------------------------------------
        //  GETTERS

            //! Gets the x-column as a vector
            constexpr Vector1<T>  x_column() const noexcept;

            //! Gets the y-column as a vector
            constexpr Vector1<T>  y_column() const noexcept;

            //! Gets the x-row as a vector
            constexpr Vector2<T>  x_row() const noexcept;

        //  --------------------------------------------------------
        //  SETTERS

            //! Sets the X-column
            Tensor12& x_column(const Vector1<T>& v);

            //! Sets the X-column
            Tensor12& x_column(T _xx);

            //! Sets the Y-column
            Tensor12& y_column(const Vector1<T>& v);

            //! Sets the Y-column
            Tensor12& y_column(T _xy);

            //! Sets the X-row
            Tensor12& x_row(const Vector2<T>& v);

            //! Sets the X-row
            Tensor12& x_row(T _xx, T _xy);
            

    };

    YQ_IEEE754_1(Tensor12)
        
//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Create 1x2 tensor by columns
    */
    template <typename T>
    constexpr Tensor12<T>  columns(const Vector1<T>&x, const Vector1<T>&y)
    {
        return Tensor12<T>(COLUMNS, x, y);
    }

    /*! \brief Create 1x2 tensor by rows
    */
    template <typename T>
    constexpr Tensor12<T>  rows(const Vector2<T>&x)
    {
        return Tensor12<T>(ROWS, x);
    }
    
    YQ_IDENTITY_1(Tensor12, Tensor12<T>(IDENTITY))
    YQ_NAN_1(Tensor12, Tensor12<T>(NAN))
    YQ_ZERO_1(Tensor12, Tensor12<T>(ZERO))
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor12, 
        is_finite(v.xx) && is_finite(v.xy)
    )
    
    YQ_IS_NAN_1(Tensor12,  
        is_nan(v.xx) || is_nan(v.xy)
    )

    template <typename T>
    constexpr Tensor21<T>  transpose(const Tensor12<T>&v) noexcept;

//  --------------------------------------------------------
//  GETTERS

    template <typename T>
    constexpr Vector1<T>  x_column(const Tensor12<T>&ten) noexcept;

    template <typename T>
    constexpr Vector1<T>  y_column(const Tensor12<T>&ten) noexcept;

    template <typename T>
    constexpr Vector2<T>  x_row(const Tensor12<T>&ten) noexcept;

//  --------------------------------------------------------
//  ADDITION

//  --------------------------------------------------------
//  SUBTRACTION
    
//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires std::is_arithmetic_v<T>
    constexpr Tensor12<trait::product_t<T,U>>  operator*(T a, const Tensor12<U>& b);
    
//  --------------------------------------------------------
//  DIVISION

//  --------------------------------------------------------
//  OTIMES PRODUCT

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

}

YQ_TYPE_DECLARE(yq::Tensor12D)
YQ_TYPE_DECLARE(yq::Tensor12F)
YQ_TYPE_DECLARE(yq::Tensor12I)
YQ_TYPE_DECLARE(yq::Tensor12U)

