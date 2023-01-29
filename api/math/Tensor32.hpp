////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__TENSOR_3_2__HPP 1
#include <math/preamble.hpp>
#include <math/Vector2.hpp>
#include <math/Vector3.hpp>

namespace yq {
    /*! \brief 3x2 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor32 {
    
        //! Component type (captures the template parameter)
        using component_type = T;
        
        T xx, xy;
        T yx, yy;
        T zx, zy;

        constexpr Tensor32() noexcept = default;

        constexpr Tensor32(
            T _xx, T _xy, 
            T _yx, T _yy, 
            T _zx, T _zy
        ) : 
            xx(_xx), xy(_xy),
            yx(_yx), yy(_yy),
            zx(_zx), zy(_zy)
        {
        }
        
        constexpr Tensor32(columns_t, const Vector3<T>& x, const Vector3<T>& y) noexcept :
            xx(x.x), xy(y.x), 
            yx(x.y), yy(y.y), 
            zx(x.z), zy(y.z)
        {
        }

        consteval Tensor32(identity_t) : 
            xx(one_v<T>),  xy(zero_v<T>), 
            yx(zero_v<T>), yy(one_v<T>),  
            zx(zero_v<T>), zy(zero_v<T>)
        {
        }

        consteval Tensor32(nan_t) : 
            xx(nan_v<T>), xy(nan_v<T>), 
            yx(nan_v<T>), yy(nan_v<T>), 
            zx(nan_v<T>), zy(nan_v<T>)
        {
        }

        constexpr Tensor32(rows_t, const Vector2<T>& x, const Vector2<T>& y, const Vector2<T>& z) :
            xx(x.x), xy(x.y), 
            yx(y.x), yy(y.y), 
            zx(z.x), zy(z.y)
        {
        }

        consteval Tensor32(zero_t) : 
            xx(zero_v<T>), xy(zero_v<T>), 
            yx(zero_v<T>), yy(zero_v<T>), 
            zx(zero_v<T>), zy(zero_v<T>)
        {
        }

        template <glm::qualifier Q>
        explicit constexpr Tensor32(const glm::mat<3,2,T,Q>& t) noexcept;

        //! Default equality operator
        constexpr bool operator==(const Tensor32&) const noexcept = default;

        //! Conversion to GLM
        constexpr operator glm::mat<3,2,T,glm::defaultp>() const noexcept;

        //! Positive (affirmation) operator
        constexpr Tensor32  operator+() const noexcept;

        //! Negation operator
        constexpr Tensor32  operator-() const noexcept;
        
        constexpr Tensor32   operator+ (const Tensor32 &b) const noexcept;
        Tensor32&            operator+=(const Tensor32 &b) noexcept;
        constexpr Tensor32   operator- (const Tensor32 &b) const noexcept;
        Tensor32&            operator-=(const Tensor32 &b) noexcept;

        template <typename U>
        requires trait::is_arithmetic_v<U>
        constexpr Tensor32<product_t<T,U>>  operator*(U b) const noexcept;
        
        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
        Tensor32<product_t<T,U>>  operator*=(U b) noexcept;

        template <typename U>
        constexpr Tensor31<product_t<T,U>> operator*(const Tensor21<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor32<product_t<T,U>> operator*(const Tensor22<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor33<product_t<T,U>> operator*(const Tensor23<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor34<product_t<T,U>> operator*(const Tensor24<U>& b) const noexcept;

        template <typename U>
        requires trait::self_mul_v<T,U>
        Tensor32<T>& operator*=(const Tensor22<U>& b) noexcept;

        template <typename U>
        constexpr Vector3<product_t<T,U>> operator*(const Vector2<U>&b) const noexcept;

        template <typename U>
        requires trait::is_arithmetic_v<U>
        constexpr Tensor32<quotient_t<T,U>>  operator/(U b) const noexcept;

        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_div_v<T,U>)
        Tensor32<quotient_t<T,U>>  operator/=(U b) noexcept;

        constexpr Tensor23<T> transpose() const noexcept;
    
        //  --------------------------------------------------------
        //  GETTERS

            //! X-column of this tensor
            constexpr Vector3<T>  x_column() const noexcept;

            //! Y-column of this tensor
            constexpr Vector3<T>  y_column() const noexcept;

            //! X-row of this tensor
            constexpr Vector2<T>  x_row() const noexcept;

            //! Y-row of this tensor
            constexpr Vector2<T>  y_row() const noexcept;

            //! Z-row of this tensor
            constexpr Vector2<T>  z_row() const noexcept;

        //  --------------------------------------------------------
        //  SETTERS

            //! Set x-column
            Tensor32& x_column(const Vector3<T>& v);

            //! Set x-column
            Tensor32& x_column(T _xx, T _yx, T _zx);

            //! Set y-column
            Tensor32& y_column(const Vector3<T>& v);

            //! Set y-column
            Tensor32& y_column(T _xy, T _yy, T _zy);

            //! Set x-row
            Tensor32& x_row(const Vector2<T>& v);

            //! Set x-row
            Tensor32& x_row(T _xx, T _xy);

            //! Set y-row
            Tensor32& y_row(const Vector2<T>& v);

            //! Set y-row
            Tensor32& y_row(T _yx, T _yy);

            //! Set z-row
            Tensor32& z_row(const Vector2<T>& v);

            //! Set z-row
            Tensor32& z_row(T _zx, T _zy);


    };

    YQ_IEEE754_1(Tensor32)
        
//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Create 3x2 tensor by columns
    */
    template <typename T>
    constexpr Tensor32<T>  columns(const Vector3<T>&x, const Vector3<T>&y)
    {
        return Tensor32<T>(COLUMNS, x, y);
    }

    /*! \brief Create 3x2 tensor by rows
    */
    template <typename T>
    constexpr Tensor32<T>  rows(const Vector2<T>&x, const Vector2<T>&y, const Vector2<T>&z)
    {
        return Tensor32<T>(ROWS, x, y, z);
    }
    
    YQ_IDENTITY_1(Tensor32, Tensor32<T>(IDENTITY))
    YQ_NAN_1(Tensor32, Tensor32<T>(NAN))
    YQ_ZERO_1(Tensor32, Tensor32<T>(ZERO))
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor32, 
        is_finite(v.xx) && is_finite(v.xy) &&
        is_finite(v.yx) && is_finite(v.yy) &&
        is_finite(v.zx) && is_finite(v.zy)
    )
    
    YQ_IS_NAN_1(Tensor32,  
        is_nan(v.xx) || is_nan(v.xy) ||
        is_nan(v.yx) || is_nan(v.yy) ||
        is_nan(v.zx) || is_nan(v.zy)
    )

    template <typename T>
    constexpr Tensor23<T>  transpose(const Tensor32<T>&v);
    
//  --------------------------------------------------------
//  GETTERS

    template <typename T>
    constexpr Vector3<T>  x_column(const Tensor32<T>&ten);

    template <typename T>
    constexpr Vector3<T>  y_column(const Tensor32<T>&ten);

    template <typename T>
    constexpr Vector2<T>  x_row(const Tensor32<T>&ten);
    
    template <typename T>
    constexpr Vector2<T>  y_row(const Tensor32<T>&ten);

    template <typename T>
    constexpr Vector2<T>  z_row(const Tensor32<T>&ten);

//  --------------------------------------------------------
//  ADDITION

//  --------------------------------------------------------
//  SUBTRACTION
    
//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires trait::is_arithmetic_v<T>
    constexpr Tensor32<product_t<T,U>>  operator*(T a, const Tensor32<U>& b);
    
//  --------------------------------------------------------
//  DIVISION

//  --------------------------------------------------------
//  OTIMES PRODUCT

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

}

YQ_TYPE_DECLARE(yq::Tensor32D)
YQ_TYPE_DECLARE(yq::Tensor32F)
YQ_TYPE_DECLARE(yq::Tensor32I)
YQ_TYPE_DECLARE(yq::Tensor32U)

