////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__TENSOR_2_4__HPP 1
#include <math/preamble.hpp>
#include <math/Vector2.hpp>
#include <math/Vector4.hpp>

namespace yq {
    /*! \brief 2x4 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor24 {
    
        //! Component type
        using component_type = T;

        static constexpr const unsigned rows_count  = 2;
        static constexpr const unsigned cols_count  = 4;

        T xx, xy, xz, xw;
        T yx, yy, yz, yw;

        constexpr Tensor24() noexcept = default;

        constexpr Tensor24(
            T _xx, T _xy, T _xz, T _xw,
            T _yx, T _yy, T _yz, T _yw
        ) : 
            xx(_xx), xy(_xy), xz(_xz), xw(_xw),
            yx(_yx), yy(_yy), yz(_yz), yw(_yw)
        {
        }
        
        constexpr Tensor24(all_t, T v) : 
            xx(v), xy(v), xz(v), xw(v),
            yx(v), yy(v), yz(v), yw(v)
        {
        }

        constexpr Tensor24(columns_t, const Vector2<T>& x, const Vector2<T>& y, const Vector2<T>& z, const Vector2<T>& w) :
            xx(x.x), xy(y.x), xz(z.x), xw(w.x),
            yx(x.y), yy(y.y), yz(z.y), yw(w.y)
        {
        }

        consteval Tensor24(identity_t) : 
            xx(one_v<T>),  xy(zero_v<T>), xz(zero_v<T>), xw(zero_v<T>),
            yx(zero_v<T>), yy(one_v<T>),  yz(zero_v<T>), yw(zero_v<T>)
        {
        }

        template <typename=void> requires trait::has_nan_v<T>
        consteval Tensor24(nan_t) : Tensor24(ALL, nan_v<T>) {}

        constexpr Tensor24(rows_t, const Vector4<T>& x, const Vector4<T>& y, const Vector4<T>& z, const Vector4<T>& w) :
            xx(x.x), xy(x.y), xz(x.z), xw(x.w),
            yx(y.x), yy(y.y), yz(y.z), yw(y.w)
        {
        }

        consteval Tensor24(zero_t) : Tensor24(ALL, zero_v<T>) {}

        template <glm::qualifier Q>
        explicit constexpr Tensor24(const glm::mat<2,4,T,Q>& t) noexcept;

        //! Defaulted equality operator
        constexpr bool operator==(const Tensor24&) const noexcept = default;

        constexpr operator glm::mat<2,4,T,glm::defaultp>() const noexcept;

        //! Positive (affirmation) operator
        constexpr Tensor24      operator+() const noexcept;

        //! Negation
        constexpr Tensor24      operator-() const noexcept;
        
        constexpr Tensor24      operator+ (const Tensor24 &b) const noexcept;
        Tensor24&               operator+=(const Tensor24 &b) noexcept;
        constexpr Tensor24      operator- (const Tensor24 &b) const noexcept;
        Tensor24&               operator-=(const Tensor24 &b) noexcept;

        template <typename U>
        requires trait::is_arithmetic_v<U>
        constexpr Tensor24<trait::product_t<T,U>>  operator*(U b) const noexcept;

        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
        Tensor24<T>&  operator*=(U b) noexcept;

        template <typename U>
        Polygon2<trait::product_t<T,U>>  operator*(const Polygon4<U>&) const;
        template <typename U>
        Polyline2<trait::product_t<T,U>>  operator*(const Polyline4<U>&) const;

        template <typename U>
        constexpr Segment2<trait::product_t<T,U>>  operator*(const Segment4<U>&) const noexcept;

        template <typename U>
        constexpr Tensor21<trait::product_t<T,U>> operator*(const Tensor41<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor22<trait::product_t<T,U>> operator*(const Tensor42<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor23<trait::product_t<T,U>> operator*(const Tensor43<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor24<trait::product_t<T,U>> operator*(const Tensor44<U>& b) const noexcept;

        template <typename U>
        Triangle2<trait::product_t<T,U>> operator*(const Triangle4<U>&) const noexcept;

        template <typename U>
        constexpr Vector2<trait::product_t<T,U>> operator*(const Vector4<U>&b) const noexcept;

        template <typename U>
        std::vector<Vector2<trait::product_t<T,U>>>    operator*(std::span<const Vector4<U>> b) const;

        template <typename U>
        requires trait::self_mul_v<T,U>
        Tensor24<T>& operator*=(const Tensor44<U>& b) noexcept;

        template <typename U>
        requires trait::is_arithmetic_v<U>
        constexpr Tensor24<trait::quotient_t<T,U>>  operator/(U b) const noexcept;
        
        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_div_v<T,U>)
        Tensor24<T>&  operator/=(U b) noexcept;
        
        constexpr Tensor42<T> transpose() const noexcept;

        //  --------------------------------------------------------
        //  GETTERS

            //! X-column of this tensor
            constexpr Vector2<T>  x_column() const noexcept;

            //! Y-column of this tensor
            constexpr Vector2<T>  y_column() const noexcept;

            //! Z-column of this tensor
            constexpr Vector2<T>  z_column() const noexcept;

            //! W-column of this tensor
            constexpr Vector2<T>  w_column() const noexcept;

            //! X-row of this tensor
            constexpr Vector4<T>  x_row() const noexcept;

            //! Y-row of this tensor
            constexpr Vector4<T>  y_row() const noexcept;


        //  --------------------------------------------------------
        //  SETTERS

            //! Sets the x-column of this tensor
            Tensor24& x_column(const Vector2<T>& v);

            //! Sets the x-column of this tensor
            Tensor24& x_column(T _xx, T _yx);

            //! Sets the y-column of this tensor
            Tensor24& y_column(const Vector2<T>& v);

            //! Sets the y-column of this tensor
            Tensor24& y_column(T _xy, T _yy);

            //! Sets the z-column of this tensor
            Tensor24& z_column(const Vector2<T>& v);

            //! Sets the z-column of this tensor
            Tensor24& z_column(T _xz, T _yz);

            //! Sets the w-column of this tensor
            Tensor24& w_column(const Vector2<T>& v);

            //! Sets the w-column of this tensor
            Tensor24& w_column(T _xw, T _yw);

            //! Sets the x-row of this tensor
            Tensor24& x_row(const Vector4<T>& v);

            //! Sets the x-row of this tensor
            Tensor24& x_row(T _xx, T _xy, T _xz, T _xw);

            //! Sets the y-row of this tensor
            Tensor24& y_row(const Vector4<T>& v);

            //! Sets the y-row of this tensor
            Tensor24& y_row(T _yx, T _yy, T _yz, T _yw);
    };

    YQ_IEEE754_1(Tensor24)
        
//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Create 2x4 tensor by columns
    */
    template <typename T>
    constexpr Tensor24<T>  columns(const Vector2<T>&x, const Vector2<T>&y, const Vector2<T>&z, const Vector2<T>&w)
    {
        return Tensor24<T>(COLUMNS, x, y, z, w);
    }

    /*! \brief Create 2x4 tensor by rows
    */
    template <typename T>
    constexpr Tensor24<T>  rows(const Vector4<T>&x, const Vector4<T>&y)
    {
        return Tensor24<T>(ROWS, x, y );
    }
    
    YQ_IDENTITY_1(Tensor24, Tensor24<T>(IDENTITY))
    YQ_NAN_1(Tensor24,Tensor24<T>(NAN))
    YQ_ZERO_1(Tensor24, Tensor24<T>(ZERO))
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor24, 
        is_finite(v.xx) && is_finite(v.xy) && is_finite(v.xz) && is_finite(v.xw) &&
        is_finite(v.yx) && is_finite(v.yy) && is_finite(v.yz) && is_finite(v.yw)
    )
    
    YQ_IS_NAN_1(Tensor24,  
        is_nan(v.xx) || is_nan(v.xy) || is_nan(v.xz) || is_nan(v.xw) ||
        is_nan(v.yx) || is_nan(v.yy) || is_nan(v.yz) || is_nan(v.yw)
    )

    template <typename T>
    constexpr Tensor42<T>  transpose(const Tensor24<T>&v);

//  --------------------------------------------------------
//  GETTERS

    //! Gets the x-column of the provided tensor
    template <typename T>
    constexpr Vector2<T>  x_column(const Tensor24<T>&ten);

    //! Gets the y-column of the provided tensor
    template <typename T>
    constexpr Vector2<T>  y_column(const Tensor24<T>&ten);

    //! Gets the z-column of the provided tensor
    template <typename T>
    constexpr Vector2<T>  z_column(const Tensor24<T>&ten);

    //! Gets the w-column of the provided tensor
    template <typename T>
    constexpr Vector2<T>  w_column(const Tensor24<T>&ten);

    //! Gets the x-row of the provided tensor
    template <typename T>
    constexpr Vector4<T>  x_row(const Tensor24<T>&ten);

    //! Gets the y-row of the provided tensor
    template <typename T>
    constexpr Vector4<T>  y_row(const Tensor24<T>&ten);

//  --------------------------------------------------------
//  --------------------------------------------------------

    template <typename T, typename U>
    requires trait::is_arithmetic_v<T>
    constexpr Tensor24<trait::product_t<T,U>>  operator*(T a, const Tensor24<U>& b);


}

YQ_TYPE_DECLARE(yq::Tensor24D)
YQ_TYPE_DECLARE(yq::Tensor24F)
YQ_TYPE_DECLARE(yq::Tensor24I)
YQ_TYPE_DECLARE(yq::Tensor24U)

