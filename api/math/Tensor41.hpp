////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__TENSOR_4_1__HPP 1
#include <math/preamble.hpp>
#include <math/Vector1.hpp>
#include <math/Vector4.hpp>

namespace yq {
    /*! \brief 4x1 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor41 {
    
        //! Component type
        using component_type = T;

        static constexpr const unsigned rows_count  = 4;
        static constexpr const unsigned cols_count  = 1;
        
        T xx;
        T yx;
        T zx;
        T wx;


        constexpr Tensor41() noexcept = default;

        constexpr Tensor41(
            T _xx, 
            T _yx, 
            T _zx, 
            T _wx
        ) : 
            xx(_xx),
            yx(_yx),
            zx(_zx),
            wx(_wx)
        {
        }
        
        constexpr Tensor41(all_t, T v) : 
            xx(v), 
            yx(v), 
            zx(v), 
            wx(v)
        {
        }

        constexpr Tensor41(columns_t, const Vector4<T>& x) noexcept :
            xx(x.x),
            yx(x.y),
            zx(x.z),
            wx(x.w)
        {
        }

        consteval Tensor41(identity_t) : 
            xx(one_v<T>),  
            yx(zero_v<T>), 
            zx(zero_v<T>), 
            wx(zero_v<T>)
        {
        }

        template <typename=void> requires trait::has_nan_v<T>
        consteval Tensor41(nan_t) : Tensor41(ALL, nan_v<T>) {}

        constexpr Tensor41(rows_t, const Vector1<T>& x, const Vector1<T>& y, const Vector1<T>& z, const Vector1<T>& w) :
            xx(x.x), 
            yx(y.x), 
            zx(z.x),
            wx(w.x)
        {
        }

        consteval Tensor41(zero_t) : Tensor41(ALL, zero_v<T>) {}
        
        template <glm::qualifier Q>
        explicit constexpr Tensor41(const glm::mat<4,1,T,Q>& t) noexcept;

        //! Defaulted equality operator
        constexpr bool operator==(const Tensor41&) const noexcept = default;

        //! Conversion to GLM
        constexpr operator glm::mat<4,1,T,glm::defaultp>() const noexcept ;

        //! Positive (affirmation) operator
        constexpr Tensor41<T>  operator+() const noexcept;
        //! Negation operator
        constexpr Tensor41<T>  operator-() const noexcept;

        constexpr Tensor41<T>   operator+ (const Tensor41<T> &b) const noexcept;
        Tensor41<T>&            operator+=(const Tensor41<T> &b)  noexcept;
        constexpr Tensor41<T>   operator- (const Tensor41<T> &b) const noexcept;
        Tensor41<T>&            operator-=(const Tensor41<T> &b)  noexcept;
        
        template <typename U>
        requires trait::is_arithmetic_v<U>
        constexpr Tensor41<trait::product_t<T,U>>  operator*(U b) const noexcept;
        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
        Tensor41&   operator*=(U b) noexcept;

        template <typename U>
        constexpr Segment4<trait::product_t<T,U>>  operator*(const Segment1<U>&) const noexcept;

        template <typename U>
        constexpr Tensor41<trait::product_t<T,U>> operator*(const Tensor11<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor42<trait::product_t<T,U>> operator*(const Tensor12<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor43<trait::product_t<T,U>> operator*(const Tensor13<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor44<trait::product_t<T,U>> operator*(const Tensor14<U>& b) const noexcept;

        template <typename U>
        requires trait::self_mul_v<T,U>
        Tensor41& operator*=(const Tensor11<U>& b) noexcept;

        template <typename U>
        constexpr Vector4<trait::product_t<T,U>> operator*(const Vector1<U>&b) const noexcept;

        template <typename U>
        std::vector<Vector4<trait::product_t<T,U>>>    operator*(std::span<const Vector1<U>> b) const;

        template <typename U>
        requires trait::is_arithmetic_v<U>
        constexpr Tensor41<trait::quotient_t<T,U>>  operator/(U b) const noexcept;
        
        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_div_v<T,U>)
        Tensor41&  operator/=(U b) noexcept;

        constexpr Tensor14<T> transpose() const noexcept;


        //  --------------------------------------------------------
        //  GETTERS

            //! X column of this tensor
            constexpr Vector4<T>  x_column() const noexcept;

            //! X row of this tensor
            constexpr Vector1<T>  x_row() const noexcept;

            //! Y row of this tensor
            constexpr Vector1<T>  y_row() const noexcept;

            //! Z row of this tensor
            constexpr Vector1<T>  z_row() const noexcept;

            //! W row of this tensor
            constexpr Vector1<T>  w_row() const noexcept;


        //  --------------------------------------------------------
        //  SETTERS

            //! Sets the X-column
            Tensor41& x_column(const Vector4<T>& v) noexcept;

            //! Sets the X-column
            Tensor41& x_column(T _xx, T _yx, T _zx, T _wx) noexcept;

            //! Sets the X-row
            Tensor41& x_row(const Vector1<T>& v) noexcept;

            //! Sets the X-row
            Tensor41& x_row(T _xx) noexcept;

            //! Sets the Y-row
            Tensor41& y_row(const Vector1<T>& v) noexcept;

            //! Sets the Y-row
            Tensor41& y_row(T _yx) noexcept;

            //! Sets the Z-row
            Tensor41& z_row(const Vector1<T>& v) noexcept;

            //! Sets the Z-row
            Tensor41& z_row(T _zx) noexcept;

            //! Sets the W-row
            Tensor41& w_row(const Vector1<T>& v) noexcept;

            //! Sets the W-row
            Tensor41& w_row(T _wx) noexcept;
    };

    YQ_IEEE754_1(Tensor41)
        
//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Create 4x1 tensor by columns
    */
    template <typename T>
    constexpr Tensor41<T>  columns(const Vector4<T>&x) noexcept
    {
        return Tensor41<T>(COLUMNS, x);
    }

    /*! \brief Create 4x1 tensor by rows
    */
    template <typename T>
    constexpr Tensor41<T>  rows(const Vector1<T>&x, const Vector1<T>&y, const Vector1<T>&z, const Vector1<T>&w) noexcept
    {
        return Tensor41<T>(ROWS, x, y, z, w);
    }
    
    YQ_IDENTITY_1(Tensor41, Tensor41<T>(IDENTITY))
    YQ_NAN_1(Tensor41, Tensor41<T>(NAN))
    YQ_ZERO_1(Tensor41, Tensor41<T>(ZERO))

    template <typename T>
    constexpr Tensor14<T>  transpose(const Tensor41<T>&v);
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor41, 
        is_finite(v.xx) &&
        is_finite(v.yx) &&
        is_finite(v.zx) &&
        is_finite(v.wx)
    )
    
    YQ_IS_NAN_1(Tensor41,  
        is_nan(v.xx) ||
        is_nan(v.yx) ||
        is_nan(v.zx) ||
        is_nan(v.wx)
    )

//  --------------------------------------------------------
//  GETTERS

    //! X-column of given tensor
    template <typename T>
    constexpr Vector4<T>  x_column(const Tensor41<T>&ten)  noexcept
    {
        return ten.x_column();
    }

    //! X-row of given tensor
    template <typename T>
    constexpr Vector1<T>  x_row(const Tensor41<T>&ten)  noexcept
    {
        return ten.x_row();
    }

    //! Y-row of given tensor
    template <typename T>
    constexpr Vector1<T>  y_row(const Tensor41<T>&ten) noexcept
    {
        return ten.y_row();
    }

    //! Z-row of given tensor
    template <typename T>
    constexpr Vector1<T>  z_row(const Tensor41<T>&ten) noexcept
    {
        return ten.z_row();
    }

    //! W-row of given tensor
    template <typename T>
    constexpr Vector1<T>  w_row(const Tensor41<T>&ten) noexcept
    {
        return ten.w_row();
    }



//  --------------------------------------------------------
//  ADDITION



//  --------------------------------------------------------
//  SUBTRACTION

    
//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires trait::is_arithmetic_v<T>
    constexpr Tensor41<trait::product_t<T,U>>  operator*(T a, const Tensor41<T>& b) noexcept;
    
    

//  --------------------------------------------------------
//  DIVISION


//  --------------------------------------------------------
//  OTIMES PRODUCT


//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

}

YQ_TYPE_DECLARE(yq::Tensor41D)
YQ_TYPE_DECLARE(yq::Tensor41F)
YQ_TYPE_DECLARE(yq::Tensor41I)
YQ_TYPE_DECLARE(yq::Tensor41U)

