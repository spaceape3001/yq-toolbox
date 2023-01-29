////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__TENSOR_3_4__HPP 1
#include <math/preamble.hpp>
#include <math/Vector3.hpp>
#include <math/Vector4.hpp>

namespace yq {
    /*! \brief 3x4 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor34 {
        //! Component type (captures template parameter)
        using component_type = T;
        
        static constexpr const unsigned rows_count  = 3;
        static constexpr const unsigned cols_count  = 4;

        T xx, xy, xz, xw;
        T yx, yy, yz, yw;
        T zx, zy, zz, zw;

        constexpr Tensor34() noexcept = default;

        constexpr Tensor34(
            T _xx, T _xy, T _xz, T _xw,
            T _yx, T _yy, T _yz, T _yw,
            T _zx, T _zy, T _zz, T _zw
        ) : 
            xx(_xx), xy(_xy), xz(_xz), xw(_xw),
            yx(_yx), yy(_yy), yz(_yz), yw(_yw),
            zx(_zx), zy(_zy), zz(_zz), zw(_zw)
        {
        }

        constexpr Tensor34(all_t, T v) : 
            xx(v), xy(v), xz(v), xw(v),
            yx(v), yy(v), yz(v), yw(v),
            zx(v), zy(v), zz(v), zw(v)
        {
        }
        
        constexpr Tensor34(columns_t, const Vector3<T>& x, const Vector3<T>& y, const Vector3<T>& z, const Vector3<T>& w) :
            xx(x.x), xy(y.x), xz(z.x), xw(w.x),
            yx(x.y), yy(y.y), yz(z.y), yw(w.y),
            zx(x.z), zy(y.z), zz(z.z), zw(w.z)
        {
        }

        consteval Tensor34(identity_t) : 
            xx(one_v<T>),  xy(zero_v<T>), xz(zero_v<T>), xw(zero_v<T>),
            yx(zero_v<T>), yy(one_v<T>),  yz(zero_v<T>), yw(zero_v<T>),
            zx(zero_v<T>), zy(zero_v<T>), zz(one_v<T>),  zw(zero_v<T>)
        {
        }

        consteval Tensor34(nan_t) : 
            xx(nan_v<T>), xy(nan_v<T>), xz(nan_v<T>), xw(nan_v<T>),
            yx(nan_v<T>), yy(nan_v<T>), yz(nan_v<T>), yw(nan_v<T>),
            zx(nan_v<T>), zy(nan_v<T>), zz(nan_v<T>), zw(nan_v<T>)
        {
        }

        constexpr Tensor34(rows_t, const Vector4<T>& x, const Vector4<T>& y, const Vector4<T>& z, const Vector4<T>& w) :
            xx(x.x), xy(x.y), xz(x.z), xw(x.w),
            yx(y.x), yy(y.y), yz(y.z), yw(y.w),
            zx(z.x), zy(z.y), zz(z.z), zw(z.w)
        {
        }

        consteval Tensor34(zero_t) : 
            xx(zero_v<T>), xy(zero_v<T>), xz(zero_v<T>), xw(zero_v<T>),
            yx(zero_v<T>), yy(zero_v<T>), yz(zero_v<T>), yw(zero_v<T>),
            zx(zero_v<T>), zy(zero_v<T>), zz(zero_v<T>), zw(zero_v<T>)
        {
        }

        template <glm::qualifier Q>
        explicit constexpr Tensor34(const glm::mat<3,4,T,Q>& t) noexcept;

        //! Defaulted equality operator
        constexpr bool operator==(const Tensor34&) const noexcept = default;

        constexpr operator glm::mat<3,4,T,glm::defaultp>() const noexcept;
        
        //! Positive (affirmation) operator
        constexpr Tensor34<T>   operator+() const noexcept;

        //! Negation operator
        constexpr Tensor34<T>   operator-() const noexcept;

        constexpr Tensor34<T>   operator+ (const Tensor34<T> &b)  const noexcept;
        Tensor34&               operator+=(const Tensor34<T> &b)  noexcept;

        constexpr Tensor34<T>   operator- (const Tensor34<T> &b)  const noexcept;
        Tensor34&               operator-=(const Tensor34<T> &b)  noexcept;

        template <typename U>
        requires trait::is_arithmetic_v<U>
        constexpr Tensor34<product_t<T,U>>  operator*(U b) const noexcept;

        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
        Tensor34&  operator*=(U b) noexcept;

        
        template <typename U>
        constexpr Tensor31<product_t<T,U>> operator*(const Tensor41<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor32<product_t<T,U>> operator*(const Tensor42<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor33<product_t<T,U>> operator*(const Tensor43<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor34<product_t<T,U>> operator*(const Tensor44<U>& b) const noexcept;

        template <typename U>
        requires trait::self_mul_v<T,U>
        Tensor34& operator*=(const Tensor44<U>& b) noexcept;

        template <typename U>
        constexpr Vector3<product_t<T,U>> operator*(const Vector4<U>&b) const noexcept;

        template <typename U>
        requires trait::is_arithmetic_v<U>
        constexpr Tensor34<quotient_t<T,U>>  operator/(U b) const noexcept;

        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_div_v<T,U>)
        Tensor34&  operator/=(U b) noexcept;

        constexpr Tensor43<T>   transpose() const noexcept;

        //  --------------------------------------------------------
        //  GETTERS

            //! X-column of this tensor
            constexpr Vector3<T>  x_column() const noexcept;

            //! Y-column of this tensor
            constexpr Vector3<T>  y_column() const noexcept;

            //! Z-column of this tensor
            constexpr Vector3<T>  z_column() const noexcept;

            //! W-column of this tensor
            constexpr Vector3<T>  w_column() const noexcept;

            //! X-row of this tensor
            constexpr Vector4<T>  x_row() const noexcept;

            //! Y-row of this tensor
            constexpr Vector4<T>  y_row() const noexcept;

            //! Z-row of this tensor
            constexpr Vector4<T>  z_row() const noexcept;


        //  --------------------------------------------------------
        //  SETTERS

            //! Sets the X-column
            Tensor34<T>& x_column(const Vector3<T>& v) noexcept;

            //! Sets the X-column
            Tensor34<T>& x_column(T _xx, T _yx, T _zx) noexcept;

            //! Sets the Y-column
            Tensor34<T>& y_column(const Vector3<T>& v) noexcept;

            //! Sets the Y-column
            Tensor34<T>& y_column(T _xy, T _yy, T _zy) noexcept;

            //! Sets the Z-column
            Tensor34<T>& z_column(const Vector3<T>& v) noexcept;

            //! Sets the Z-column
            Tensor34<T>& z_column(T _xz, T _yz, T _zz) noexcept;

            //! Sets the W-column
            Tensor34<T>& w_column(const Vector3<T>& v) noexcept;

            //! Sets the W-column
            Tensor34<T>& w_column(T _xw, T _yw, T _zw) noexcept;

            //! Sets the X-row
            Tensor34<T>& x_row(const Vector4<T>& v) noexcept;

            //! Sets the X-row
            Tensor34<T>& x_row(T _xx, T _xy, T _xz, T _xw) noexcept;

            //! Sets the Y-row
            Tensor34<T>& y_row(const Vector4<T>& v) noexcept;

            //! Sets the Y-row
            Tensor34<T>& y_row(T _yx, T _yy, T _yz, T _yw) noexcept;

            //! Sets the Z-row
            Tensor34<T>& z_row(const Vector4<T>& v) noexcept;

            //! Sets the Z-row
            Tensor34<T>& z_row(T _zx, T _zy, T _zz, T _zw) noexcept;
    };

    YQ_IEEE754_1(Tensor34)
        
//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Create 3x4 tensor by columns
    */
    template <typename T>
    constexpr Tensor34<T>  columns(const Vector3<T>&x, const Vector3<T>&y, const Vector3<T>&z, const Vector3<T>&w) noexcept
    {
        return Tensor34<T>(columns_, x, y, z, w);
    }

    /*! \brief Create 3x4 tensor by rows
    */
    template <typename T>
    constexpr Tensor34<T>  rows(const Vector4<T>&x, const Vector4<T>&y, const Vector4<T>&z) noexcept
    {
        return Tensor34<T>(rows_, x, y, z);
    }
    
    YQ_IDENTITY_1(Tensor34, Tensor34<T>(ZERO))
    YQ_NAN_1(Tensor34, Tensor34<T>(NAN))
    YQ_ZERO_1(Tensor34, Tensor34<T>(ZERO))
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor34, 
        is_finite(v.xx) && is_finite(v.xy) && is_finite(v.xz) && is_finite(v.xw) &&
        is_finite(v.yx) && is_finite(v.yy) && is_finite(v.yz) && is_finite(v.yw) &&
        is_finite(v.zx) && is_finite(v.zy) && is_finite(v.zz) && is_finite(v.zw)
    )
    
    YQ_IS_NAN_1(Tensor34,  
        is_nan(v.xx) || is_nan(v.xy) || is_nan(v.xz) || is_nan(v.xw) ||
        is_nan(v.yx) || is_nan(v.yy) || is_nan(v.yz) || is_nan(v.yw) ||
        is_nan(v.zx) || is_nan(v.zy) || is_nan(v.zz) || is_nan(v.zw)
    )

    template <typename T>
    constexpr Tensor43<T>  transpose(const Tensor34<T>&v);

//  --------------------------------------------------------
//  GETTERS

    //! X-column of given tensor
    template <typename T>
    constexpr Vector3<T>  x_column(const Tensor34<T>&ten)  noexcept;

    //! Y-column of given tensor
    template <typename T>
    constexpr Vector3<T>  y_column(const Tensor34<T>&ten) noexcept;

    //! Z-column of given tensor
    template <typename T>
    constexpr Vector3<T>  z_column(const Tensor34<T>&ten)  noexcept;

    //! W-column of given tensor
    template <typename T>
    constexpr Vector3<T>  w_column(const Tensor34<T>&ten)  noexcept;

    //! X-row of given tensor
    template <typename T>
    constexpr Vector4<T>  x_row(const Tensor34<T>&ten) noexcept;

    //! Y-row of given tensor
    template <typename T>
    constexpr Vector4<T>  y_row(const Tensor34<T>&ten) noexcept;

    //! Z-row of given tensor
    template <typename T>
    constexpr Vector4<T>  z_row(const Tensor34<T>&ten) noexcept;



//  --------------------------------------------------------
//  ADDITION



//  --------------------------------------------------------
//  SUBTRACTION

    
//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires trait::is_arithmetic_v<T>
    constexpr Tensor34<product_t<T,U>>  operator*(T a, const Tensor34<U>& b) noexcept;
    
    



//  --------------------------------------------------------
//  DIVISION

//  --------------------------------------------------------
//  OTIMES PRODUCT

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

}

YQ_TYPE_DECLARE(yq::Tensor34D)
YQ_TYPE_DECLARE(yq::Tensor34F)
YQ_TYPE_DECLARE(yq::Tensor34I)
YQ_TYPE_DECLARE(yq::Tensor34U)

