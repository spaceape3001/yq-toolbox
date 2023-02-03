////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__TENSOR_4_3__HPP 1
#include <math/preamble.hpp>
#include <math/Vector3.hpp>
#include <math/Vector4.hpp>

namespace yq {
    /*! \brief 4x3 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor43 {
        //! Component type (captures template parameter)
        using component_type = T;
        
        static constexpr const unsigned rows_count  = 4;
        static constexpr const unsigned cols_count  = 3;

        T xx, xy, xz;
        T yx, yy, yz;
        T zx, zy, zz;
        T wx, wy, wz;

        constexpr Tensor43() noexcept = default;

        constexpr Tensor43(
            T _xx, T _xy, T _xz,
            T _yx, T _yy, T _yz,
            T _zx, T _zy, T _zz,
            T _wx, T _wy, T _wz
        ) : 
            xx(_xx), xy(_xy), xz(_xz), 
            yx(_yx), yy(_yy), yz(_yz), 
            zx(_zx), zy(_zy), zz(_zz), 
            wx(_wx), wy(_wy), wz(_wz)
        {
        }
        
        constexpr Tensor43(all_t, T v) : 
            xx(v), xy(v), xz(v),
            yx(v), yy(v), yz(v),
            zx(v), zy(v), zz(v),
            wx(v), wy(v), wz(v)
        {
        }

        constexpr Tensor43(columns_t, const Vector4<T>& x, const Vector4<T>& y, const Vector4<T>& z) noexcept :
            xx(x.x), xy(y.x), xz(z.x), 
            yx(x.y), yy(y.y), yz(z.y), 
            zx(x.z), zy(y.z), zz(z.z), 
            wx(x.w), wy(y.w), wz(z.w)
        {
        }

        consteval Tensor43(identity_t) : 
            xx(one_v<T>),  xy(zero_v<T>), xz(zero_v<T>), 
            yx(zero_v<T>), yy(one_v<T>),  yz(zero_v<T>), 
            zx(zero_v<T>), zy(zero_v<T>), zz(one_v<T>),  
            wx(zero_v<T>), wy(zero_v<T>), wz(zero_v<T>) 
        {
        }

        template <typename=void> requires trait::has_nan_v<T>
        consteval Tensor43(nan_t) : Tensor43(ALL, nan_v<T>) {}

        constexpr Tensor43(rows_t, const Vector3<T>& x, const Vector3<T>& y, const Vector3<T>& z, const Vector3<T>& w) :
            xx(x.x), xy(x.y), xz(x.z),
            yx(y.x), yy(y.y), yz(y.z),
            zx(z.x), zy(z.y), zz(z.z),
            wx(w.x), wy(w.y), wz(w.z)
        {
        }

        consteval Tensor43(zero_t) : Tensor43(ALL, zero_v<T>) {}

        template <glm::qualifier Q>
        explicit constexpr Tensor43(const glm::mat<4,3,T,Q>& t) noexcept;

        //! Defaulted equality operator
        constexpr bool operator==(const Tensor43&) const noexcept = default;

        //! Conversion to GLM
        constexpr operator glm::mat<4,3,T,glm::defaultp>() const noexcept ;

        //! Positive (affirmation) operator
        constexpr Tensor43  operator+() const noexcept;

        //! Negation operator
        constexpr Tensor43  operator-() const noexcept;

        constexpr Tensor43   operator+ (const Tensor43 &b)  const noexcept;
        Tensor43&            operator+=(const Tensor43 &b)  noexcept;
        constexpr Tensor43   operator- (const Tensor43 &b)  const noexcept;
        Tensor43&            operator-=(const Tensor43 &b)  noexcept;

        template <typename U>
        requires trait::is_arithmetic_v<U>
        constexpr Tensor43<product_t<T,U>>  operator*(U b) const noexcept;
        
        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
        Tensor43&  operator*=(U b) noexcept;

        template <typename U>
        constexpr Tensor41<product_t<T,U>> operator*(const Tensor31<U>& b) const noexcept;

        template <typename U>
        constexpr Tensor42<product_t<T,U>> operator*(const Tensor32<U>& b) const noexcept;

        template <typename U>
        constexpr Tensor43<product_t<T,U>> operator*(const Tensor33<U>& b) const noexcept;

        template <typename U>
        constexpr Tensor44<product_t<T,U>> operator*(const Tensor34<U>& b) const noexcept;

        template <typename U>
        requires trait::self_mul_v<T,U>
        Tensor43& operator*=(const Tensor33<U>& b) noexcept;

        template <typename U>
        constexpr Vector4<product_t<T,U>> operator*(const Vector3<U>&b) const noexcept;

        template <typename U>
        requires trait::is_arithmetic_v<U>
        constexpr Tensor43<quotient_t<T,U>>  operator/(U b) const noexcept;

        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_div_v<T,U>)
        Tensor43&  operator/=(U b) noexcept;

        constexpr Tensor34<T>   transpose() const noexcept;


        //  --------------------------------------------------------
        //  GETTERS

            //! X-column of this tensor
            constexpr Vector4<T>  x_column() const noexcept;

            //! Y-column of this tensor
            constexpr Vector4<T>  y_column() const noexcept;

            //! Z-column of this tensor
            constexpr Vector4<T>  z_column() const noexcept;
            
            //! X-row of this tensor
            constexpr Vector3<T>  x_row() const noexcept;

            //! Y-row of this tensor
            constexpr Vector3<T>  y_row() const noexcept;

            //! Z-row of this tensor
            constexpr Vector3<T>  z_row() const noexcept;

            //! W-row of this tensor
            constexpr Vector3<T>  w_row() const noexcept;
    

        //  --------------------------------------------------------
        //  SETTERS

            //! Sets the X-column
            Tensor43& x_column(const Vector4<T>& v) noexcept;

            //! Sets the X-column
            Tensor43& x_column(T _xx, T _yx, T _zx, T _wx) noexcept;

            //! Sets the Y-column
            Tensor43& y_column(const Vector4<T>& v) noexcept;

            //! Sets the Y-column
            Tensor43& y_column(T _xy, T _yy, T _zy, T _wy) noexcept;

            //! Sets the Z-column
            Tensor43& z_column(const Vector4<T>& v) noexcept;

            //! Sets the Z-column
            Tensor43& z_column(T _xz, T _yz, T _zz, T _wz) noexcept;

            //! Sets the X-row
            Tensor43& x_row(const Vector3<T>& v) noexcept;

            //! Sets the X-row
            Tensor43& x_row(T _xx, T _xy, T _xz) noexcept;

            //! Sets the Y-row
            Tensor43& y_row(const Vector3<T>& v) noexcept;

            //! Sets the Y-row
            Tensor43& y_row(T _yx, T _yy, T _yz) noexcept;

            //! Sets the Z-row
            Tensor43& z_row(const Vector3<T>& v) noexcept;

            //! Sets the Z-row
            Tensor43& z_row(T _zx, T _zy, T _zz) noexcept;

            //! Sets the W-row
            Tensor43& w_row(const Vector3<T>& v) noexcept;

            //! Sets the W-row
            Tensor43& w_row(T _wx, T _wy, T _wz) noexcept;

    };

    YQ_IEEE754_1(Tensor43)
        
//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Creates 4x3 tensor by specifying the columns
    */
    template <typename T>
    constexpr Tensor43<T>  columns(const Vector4<T>&x, const Vector4<T>&y, const Vector4<T>&z) noexcept
    {
        return Tensor43<T>(COLUMNS, x, y, z);
    }

    /*! \brief Creates 4x3 tensor by specifying the rows
    */
    template <typename T>
    constexpr Tensor43<T>  rows(const Vector3<T>&x, const Vector3<T>&y, const Vector3<T>&z, const Vector3<T>&w) noexcept
    {
        return Tensor43<T>(ROWS, x, y, z, w);
    }
    
    YQ_IDENTITY_1(Tensor43, Tensor43<T>(IDENTITY))
    YQ_NAN_1(Tensor43, Tensor43<T>(NAN))
    YQ_ZERO_1(Tensor43, Tensor43<T>(ZERO))
    
    template <typename T>
    constexpr Tensor34<T>  transpose(const Tensor43<T>&v);

//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor43, 
        is_finite(v.xx) && is_finite(v.xy) && is_finite(v.xz) &&
        is_finite(v.yx) && is_finite(v.yy) && is_finite(v.yz) &&
        is_finite(v.zx) && is_finite(v.zy) && is_finite(v.zz) &&
        is_finite(v.wx) && is_finite(v.wy) && is_finite(v.wz)
    )
    
    YQ_IS_NAN_1(Tensor43,  
        is_nan(v.xx) || is_nan(v.xy) || is_nan(v.xz) ||
        is_nan(v.yx) || is_nan(v.yy) || is_nan(v.yz) ||
        is_nan(v.zx) || is_nan(v.zy) || is_nan(v.zz) ||
        is_nan(v.wx) || is_nan(v.wy) || is_nan(v.wz)
    )

//  --------------------------------------------------------
//  GETTERS

    //! X-column of given tensor
    template <typename T>
    constexpr Vector4<T>  x_column(const Tensor43<T>&ten)  noexcept;

    //! Y-column of given tensor
    template <typename T>
    constexpr Vector4<T>  y_column(const Tensor43<T>&ten)  noexcept;

    //! Z-column of given tensor
    template <typename T>
    constexpr Vector4<T>  z_column(const Tensor43<T>&ten)  noexcept;

    //! X-row of given tensor
    template <typename T>
    constexpr Vector3<T>  x_row(const Tensor43<T>&ten) noexcept;

    //! Y-row of given tensor
    template <typename T>
    constexpr Vector3<T>  y_row(const Tensor43<T>&ten) noexcept;

    //! Z-row of given tensor
    template <typename T>
    constexpr Vector3<T>  z_row(const Tensor43<T>&ten) noexcept;

    //! W-row of given tensor
    template <typename T>
    constexpr Vector3<T>  w_row(const Tensor43<T>&ten) noexcept;



//  --------------------------------------------------------
//  ADDITION



//  --------------------------------------------------------
//  SUBTRACTION

    
//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires trait::is_arithmetic_v<T>
    constexpr Tensor43<product_t<T,U>>  operator*(T a, const Tensor43<T>& b) noexcept;
    


//  --------------------------------------------------------
//  DIVISION



//  --------------------------------------------------------
//  OTIMES PRODUCT


//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

}

YQ_TYPE_DECLARE(yq::Tensor43D)
YQ_TYPE_DECLARE(yq::Tensor43F)
YQ_TYPE_DECLARE(yq::Tensor43I)
YQ_TYPE_DECLARE(yq::Tensor43U)

