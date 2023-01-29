////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__TENSOR_1_4__HPP 1
#include <math/preamble.hpp>
#include <math/Vector1.hpp>
#include <math/Vector4.hpp>

namespace yq {
    /*! \brief 1x4 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor14 {
        //! Component type (captures the template parameter)
        using component_type = T;
        static constexpr const unsigned rows_count  = 1;
        static constexpr const unsigned cols_count  = 4;
        
        T xx, xy, xz, xw;


        constexpr Tensor14() noexcept = default;

        constexpr Tensor14(
            T _xx, T _xy, T _xz, T _xw
        ) : 
            xx(_xx), xy(_xy), xz(_xz), xw(_xw)
        {
        }
        
        consteval Tensor14(all_t, T v) : 
            xx(v), xy(v), xz(v), xw(v)
        {
        }

        constexpr Tensor14(columns_t, const Vector1<T>& x, const Vector1<T>& y, const Vector1<T>& z, const Vector1<T>& w) :
            xx(x.x), xy(y.x), xz(z.x), xw(w.x)
        {
        }

        consteval Tensor14(identity_t) : 
            xx(one_v<T>),  xy(zero_v<T>), xz(zero_v<T>), xw(zero_v<T>)
        {
        }

        consteval Tensor14(nan_t) : Tensor14(ALL, nan_v<T>) {}

        constexpr Tensor14(rows_t, const Vector4<T>& x, const Vector4<T>& y, const Vector4<T>& z, const Vector4<T>& w) :
            xx(x.x), xy(x.y), xz(x.z), xw(x.w)
        {
        }

        consteval Tensor14(zero_t) : Tensor14(ALL, zero_v<T>) {}

        template <glm::qualifier Q>
        explicit constexpr Tensor14(const glm::mat<1,4,T,Q>& t) noexcept;

        //! Defaulted equality operator
        constexpr bool operator==(const Tensor14&) const noexcept = default;

        constexpr operator glm::mat<1,4,T,glm::defaultp>() const noexcept;

        //! Positive (affirmation) operator
        constexpr Tensor14  operator+() const noexcept;

        //! Negation operator
        constexpr Tensor14  operator-() const noexcept;
        
        constexpr Tensor14   operator+ (const Tensor14 &b) const noexcept;
        Tensor14&            operator+=(const Tensor14 &b) noexcept;
        constexpr Tensor14   operator- (const Tensor14 &b) const noexcept;
        Tensor14&            operator-=(const Tensor14 &b) noexcept;
        
        template <typename U>
        requires trait::is_arithmetic_v<U>
        constexpr Tensor14<product_t<T,U>>  operator*(U b) const noexcept;
        
        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
        Tensor14&  operator*=(U b) noexcept;

        template <typename U>
        constexpr Tensor11<product_t<T,U>> operator*(const Tensor41<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor12<product_t<T,U>> operator*(const Tensor42<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor13<product_t<T,U>> operator*(const Tensor43<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor14<product_t<T,U>> operator*(const Tensor44<U>& b) const noexcept;

        template <typename U>
        requires trait::self_mul_v<T,U>
        Tensor14<T>& operator*=(const Tensor44<U>& b) noexcept;

        template <typename U>
        constexpr Vector1<product_t<T,U>> operator*(const Vector4<U>&b) const noexcept;

        template <typename U>
        requires trait::is_arithmetic_v<U>
        constexpr Tensor14<quotient_t<T,U>>  operator/(U b) const noexcept;
        
        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_div_v<T,U>)
        Tensor14<T>&  operator/=(U b) noexcept;

        constexpr Tensor41<T>   transpose() const noexcept;


        //  --------------------------------------------------------
        //  GETTERS

            //! Gets the x-column
            constexpr Vector1<T>  x_column() const noexcept;
            
            //! Gets the y-column
            constexpr Vector1<T>  y_column() const noexcept;
            
            //! Gets the z-column
            constexpr Vector1<T>  z_column() const noexcept;

            //! Gets the w-column
            constexpr Vector1<T>  w_column() const noexcept;

            //! Gets the x-row
            constexpr Vector4<T>  x_row() const noexcept;
            
        //  --------------------------------------------------------
        //  SETTERS

            //! Sets the x-column
            Tensor14& x_column(const Vector1<T>& v);

            //! Sets the x-column
            Tensor14& x_column(T _xx);

            //! Sets the y-column
            Tensor14& y_column(const Vector1<T>& v);

            //! Sets the y-column
            Tensor14& y_column(T _xy);

            //! Sets the z-column
            Tensor14& z_column(const Vector1<T>& v);

            //! Sets the z-column
            Tensor14& z_column(T _xz);
            
            //! Sets the w-column
            Tensor14& w_column(const Vector1<T>& v);

            //! Sets the w-column
            Tensor14& w_column(T _xw);

            //! Sets the x-row
            Tensor14& x_row(const Vector4<T>& v);

            //! Sets the x-row
            Tensor14& x_row(T _xx, T _xy, T _xz, T _xw);


    };

    YQ_IEEE754_1(Tensor14)
        
//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Create 1x4 tensor by columns
    */
    template <typename T>
    constexpr Tensor14<T>  columns(const Vector1<T>&x, const Vector1<T>&y, const Vector1<T>&z, const Vector1<T>&w)
    {
        return Tensor14<T>(COLUMNS, x, y, z, w);
    }

    /*! \brief Create 1x4 tensor by columns
    */
    template <typename T>
    constexpr Tensor14<T>  rows(const Vector4<T>&x)
    {
        return Tensor14<T>(ROWS, x);
    }
    
    YQ_IDENTITY_1(Tensor14, Tensor14<T>(IDENTITY))
    YQ_NAN_1(Tensor14, Tensor14<T>(NAN))
    YQ_ZERO_1(Tensor14, Tensor14<T>(ZERO))
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor14, 
        is_finite(v.xx) && is_finite(v.xy) && is_finite(v.xz) && is_finite(v.xw)
    )
    
    YQ_IS_NAN_1(Tensor14,  
        is_nan(v.xx) || is_nan(v.xy) || is_nan(v.xz) || is_nan(v.xw)
    )

    template <typename T>
    constexpr Tensor41<T>  transpose(const Tensor14<T>&v);

//  --------------------------------------------------------
//  GETTERS

    template <typename T>
    constexpr Vector1<T>  x_column(const Tensor14<T>&ten);

    template <typename T>
    constexpr Vector1<T>  y_column(const Tensor14<T>&ten);

    template <typename T>
    constexpr Vector1<T>  z_column(const Tensor14<T>&ten);

    template <typename T>
    constexpr Vector1<T>  w_column(const Tensor14<T>&ten);

    template <typename T>
    constexpr Vector4<T>  x_row(const Tensor14<T>&ten);

//  --------------------------------------------------------
//  --------------------------------------------------------

    template <typename T, typename U>
    requires trait::is_arithmetic_v<T>
    constexpr Tensor14<product_t<T,U>>  operator*(T a, const Tensor14<U>& b);
    

}

YQ_TYPE_DECLARE(yq::Tensor14D)
YQ_TYPE_DECLARE(yq::Tensor14F)
YQ_TYPE_DECLARE(yq::Tensor14I)
YQ_TYPE_DECLARE(yq::Tensor14U)

