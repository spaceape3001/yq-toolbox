////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__TENSOR_4_4__HPP 1
#include <math/preamble.hpp>
#include <math/Vector4.hpp>

namespace yq {
    /*! \brief 4x4 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor44 {
        //! Component type
        using component_type = T;
        
        T xx, xy, xz, xw;
        T yx, yy, yz, yw;
        T zx, zy, zz, zw;
        T wx, wy, wz, ww;


        constexpr Tensor44() noexcept = default;

        constexpr Tensor44(
            T _xx, T _xy, T _xz, T _xw,
            T _yx, T _yy, T _yz, T _yw,
            T _zx, T _zy, T _zz, T _zw,
            T _wx, T _wy, T _wz, T _ww
        ) : 
            xx(_xx), xy(_xy), xz(_xz), xw(_xw),
            yx(_yx), yy(_yy), yz(_yz), yw(_yw),
            zx(_zx), zy(_zy), zz(_zz), zw(_zw),
            wx(_wx), wy(_wy), wz(_wz), ww(_ww)
        {
        }
        
        consteval Tensor44(all_t, T v) : 
            xx(v), xy(v), xz(v), xw(v),
            yx(v), yy(v), yz(v), yw(v),
            zx(v), zy(v), zz(v), zw(v),
            wx(v), wy(v), wz(v), ww(v)
        {
        }

        constexpr Tensor44(columns_t, const Vector4<T>& x, const Vector4<T>& y, const Vector4<T>& z, const Vector4<T>& w) :
            xx(x.x), xy(y.x), xz(z.x), xw(w.x),
            yx(x.y), yy(y.y), yz(z.y), yw(w.y),
            zx(x.z), zy(y.z), zz(z.z), zw(w.z),
            wx(x.w), wy(y.w), wz(z.w), ww(w.w)
        {
        }

        constexpr Tensor44(diagonal_t, T _xx, T _yy, T _zz, T _ww) : 
            xx(_xx),  xy(zero_v<T>), xz(zero_v<T>), xw(zero_v<T>),
            yx(zero_v<T>), yy(_yy),  yz(zero_v<T>), yw(zero_v<T>),
            zx(zero_v<T>), zy(zero_v<T>), zz(_zz),  zw(zero_v<T>),
            wx(zero_v<T>), wy(zero_v<T>), wz(zero_v<T>), ww(_ww)
        {
        }

        constexpr Tensor44(diagonal_t, const Vector4<T>& v) : 
            xx(v.x),  xy(zero_v<T>), xz(zero_v<T>), xw(zero_v<T>),
            yx(zero_v<T>), yy(v.y),  yz(zero_v<T>), yw(zero_v<T>),
            zx(zero_v<T>), zy(zero_v<T>), zz(v.z),  zw(zero_v<T>),
            wx(zero_v<T>), wy(zero_v<T>), wz(zero_v<T>), ww(v.w)
        {
        }

        consteval Tensor44(identity_t) : 
            xx(one_v<T>),  xy(zero_v<T>), xz(zero_v<T>), xw(zero_v<T>),
            yx(zero_v<T>), yy(one_v<T>),  yz(zero_v<T>), yw(zero_v<T>),
            zx(zero_v<T>), zy(zero_v<T>), zz(one_v<T>),  zw(zero_v<T>),
            wx(zero_v<T>), wy(zero_v<T>), wz(zero_v<T>), ww(one_v<T>)
        {
        }

        consteval Tensor44(nan_t) : Tensor44(ALL, nan_v<T>){}

        constexpr Tensor44(rows_t, const Vector4<T>& x, const Vector4<T>& y, const Vector4<T>& z, const Vector4<T>& w) :
            xx(x.x), xy(x.y), xz(x.z), xw(x.w),
            yx(y.x), yy(y.y), yz(y.z), yw(y.w),
            zx(z.x), zy(z.y), zz(z.z), zw(z.w),
            wx(w.x), wy(w.y), wz(w.z), ww(w.w)
        {
        }

        consteval Tensor44(zero_t) :Tensor44(ALL, zero_v<T>){} 

        template <glm::qualifier Q>
        explicit constexpr Tensor44(const glm::mat<4,4,T,Q>& t) noexcept;

        //! Defaulted equality operator
        constexpr bool operator==(const Tensor44&) const noexcept = default;
        
        //! Conversion to GLM
        constexpr operator glm::mat<4,4,T,glm::defaultp>() const noexcept ;


        //! Positive (affirmation) operator
        constexpr Tensor44      operator+() const noexcept;

        //! Negation operator
        constexpr Tensor44      operator-() const noexcept;
        
        constexpr Tensor44<T>   operator+ (const Tensor44<T> &b) const noexcept;
        Tensor44<T>&            operator+=(const Tensor44<T> &b)  noexcept;
        constexpr Tensor44<T>   operator- (const Tensor44<T> &b)  const noexcept;
        Tensor44<T>&            operator-=(const Tensor44<T> &b)  noexcept;
    
        template <typename U>
        requires trait::is_arithmetic_v<U>
        constexpr Tensor44<product_t<T,U>>  operator*(U b) const noexcept;
    
        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
        Tensor44&  operator*=(U b) const noexcept;

        template <typename U>
        constexpr Tensor41<product_t<T,U>> operator*(const Tensor41<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor42<product_t<T,U>> operator*(const Tensor42<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor43<product_t<T,U>> operator*(const Tensor43<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor44<product_t<T,U>> operator*(const Tensor44<U>& b) const noexcept;

        template <typename U>
        constexpr Vector4<product_t<T,U>> operator*(const Vector4<U>&b) const noexcept;

        template <typename U>
        requires trait::self_mul_v<T,U>
        Tensor44& operator*=(const Tensor44<U>& b) noexcept;

        template <typename U>
        requires trait::is_arithmetic_v<U>
        constexpr Tensor44<quotient_t<T,U>>  operator/(U b) const noexcept;

        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_div_v<T,U>)
        Tensor44&  operator/=(U b) noexcept;


        //! Takes the transpose
        constexpr Tensor44 transpose() const noexcept;


        //  TODO: 4x4 determinant 
        //  TODO: 4x4 inverse 
        //  TODO: 4x4 eigenvalues, eigenvectors, & eigensystem

        //! \brief Trace of this tensor
        constexpr T     trace() const noexcept;

        //  --------------------------------------------------------
        //  GETTERS

            //! Diagonal of this vector
            constexpr Vector4<T>  diagonal() const noexcept;

            //! X-column of this vector
            constexpr Vector4<T>  x_column() const noexcept;

            //! Y-column of this vector
            constexpr Vector4<T>  y_column() const noexcept;

            //! Z-column of this vector
            constexpr Vector4<T>  z_column() const noexcept;

            //! W-column of this vector
            constexpr Vector4<T>  w_column() const noexcept;

            //! X-row of this vector
            constexpr Vector4<T>  x_row() const noexcept;

            //! Y-row of this vector
            constexpr Vector4<T>  y_row() const noexcept;

            //! Z-row of this vector
            constexpr Vector4<T>  z_row() const noexcept;

            //! W-row of this vector
            constexpr Vector4<T>  w_row() const noexcept;


        //  --------------------------------------------------------
        //  SETTERS

            //! Sets the diagonal
            Tensor44&  diagonal(const Vector4<T>& v) noexcept;

            //! Sets the diagonal
            Tensor44&  diagonal(T _xx, T _yy, T _zz, T _ww) noexcept;

            //! Sets the X-column
            Tensor44& x_column(const Vector4<T>& v) noexcept;

            //! Sets the X-column
            Tensor44& x_column(T _xx, T _yx, T _zx, T _wx) noexcept;

            //! Sets the Y-column
            Tensor44& y_column(const Vector4<T>& v) noexcept;

            //! Sets the Y-column
            Tensor44& y_column(T _xy, T _yy, T _zy, T _wy) noexcept;

            //! Sets the Z-column
            Tensor44& z_column(const Vector4<T>& v) noexcept;

            //! Sets the Z-column
            Tensor44& z_column(T _xz, T _yz, T _zz, T _wz) noexcept;

            //! Sets the W-column
            Tensor44& w_column(const Vector4<T>& v) noexcept;

            //! Sets the W-column
            Tensor44& w_column(T _xw, T _yw, T _zw, T _ww) noexcept;

            //! Sets the X-row
            Tensor44& x_row(const Vector4<T>& v) noexcept;

            //! Sets the X-row
            Tensor44& x_row(T _xx, T _xy, T _xz, T _xw) noexcept;

            //! Sets the Y-row
            Tensor44& y_row(const Vector4<T>& v) noexcept;

            //! Sets the Y-row
            Tensor44& y_row(T _yx, T _yy, T _yz, T _yw) noexcept;

            //! Sets the Z-row
            Tensor44& z_row(const Vector4<T>& v) noexcept;

            //! Sets the Z-row
            Tensor44& z_row(T _zx, T _zy, T _zz, T _zw) noexcept;

            //! Sets the W-row
            Tensor44& w_row(const Vector4<T>& v) noexcept;

            //! Sets the W-row
            Tensor44& w_row(T _wx, T _wy, T _wz, T _ww) noexcept;
    
    };
        
    YQ_IEEE754_1(Tensor44)

//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Creates 4x4 tensor from four Vector4 column vectors
    */
    template <typename T>
    constexpr Tensor44<T>  columns(const Vector4<T>&x, const Vector4<T>&y, const Vector4<T>&z, const Vector4<T>&w) noexcept
    {
        return Tensor44<T>(COLUMNS, x, y, z, w);
    }

    /*! \brief Creates 4x4 tensor by specifying diagonal 
    
        This assumes the rest of the components are zero.
    */
    template <typename T>
    constexpr Tensor44<T>  diagonal(const Vector4<T>&v) noexcept
    {
        return Tensor44<T>(DIAGONAL, v);
    }
    
    /*! \brief Creates 4x4 tensor by specifying diagonal
    
        This assumes the rest of the components are zero.
    */
    template <typename T>
    constexpr Tensor44<T>  diagonal(T x, std::type_identity_t<T> y, std::type_identity_t<T> z, std::type_identity_t<T> w) noexcept
    {
        return Tensor44<T>(DIAGONAL, x, y, z, w);
    }

    /*! \brief Creates 4x4 tensor by specifying the rows
    */
    template <typename T>
    constexpr Tensor44<T>  rows(const Vector4<T>&x, const Vector4<T>&y, const Vector4<T>&z, const Vector4<T>&w) noexcept
    {
        return Tensor44<T>(ROWS, x, y, z, w);
    }

    /*! \brief Creates 4x4 tensor from the GLM equivalent
    */
    template <typename T, glm::qualifier Q>
    constexpr Tensor44<T> tensor(const glm::mat<4,4,T,Q>& t) noexcept;
    
    YQ_IDENTITY_1(Tensor44, Tensor44<T>(IDENTITY))
    YQ_NAN_1(Tensor44, Tensor44<T>(NAN))
    YQ_ZERO_1(Tensor44, Tensor44<T>(ZERO))
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor44, 
        is_finite(v.xx) && is_finite(v.xy) && is_finite(v.xz) && is_finite(v.xw) &&
        is_finite(v.yx) && is_finite(v.yy) && is_finite(v.yz) && is_finite(v.yw) &&
        is_finite(v.zx) && is_finite(v.zy) && is_finite(v.zz) && is_finite(v.zw) &&
        is_finite(v.wx) && is_finite(v.wy) && is_finite(v.wz) && is_finite(v.ww)
    )
    
    YQ_IS_NAN_1(Tensor44,  
        is_nan(v.xx) || is_nan(v.xy) || is_nan(v.xz) || is_nan(v.xw) ||
        is_nan(v.yx) || is_nan(v.yy) || is_nan(v.yz) || is_nan(v.yw) ||
        is_nan(v.zx) || is_nan(v.zy) || is_nan(v.zz) || is_nan(v.zw) ||
        is_nan(v.wx) || is_nan(v.wy) || is_nan(v.wz) || is_nan(v.ww)
    )

    //! Transpose of given tensor
    template <typename T>
    constexpr Tensor44<T>  transpose(const Tensor44<T>&ten) noexcept;

//  --------------------------------------------------------
//  GETTERS

    //! Diagonal of given tensor
    template <typename T>
    constexpr Vector4<T>  diagonal(const Tensor44<T>&ten) noexcept;

    //! X-column of given tensor
    template <typename T>
    constexpr Vector4<T>  x_column(const Tensor44<T>&ten)  noexcept;

    //! Y-column of given tensor
    template <typename T>
    constexpr Vector4<T>  y_column(const Tensor44<T>&ten)  noexcept;

    //! Z-column of given tensor
    template <typename T>
    constexpr Vector4<T>  z_column(const Tensor44<T>&ten)  noexcept;

    //! W-column of given tensor
    template <typename T>
    constexpr Vector4<T>  w_column(const Tensor44<T>&ten)  noexcept;

    //! X-row of given tensor
    template <typename T>
    constexpr Vector4<T>  x_row(const Tensor44<T>&ten) noexcept;

    //! Y-row of given tensor
    template <typename T>
    constexpr Vector4<T>  y_row(const Tensor44<T>&ten) noexcept;

    //! Z-row of given tensor
    template <typename T>
    constexpr Vector4<T>  z_row(const Tensor44<T>&ten) noexcept;

    //! W-row of given tensor
    template <typename T>
    constexpr Vector4<T>  w_row(const Tensor44<T>&ten) noexcept;


//  --------------------------------------------------------
//  ADDITION


//  --------------------------------------------------------
//  SUBTRACTION

    
//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires trait::is_arithmetic_v<T>
    constexpr Tensor44<product_t<T,U>>  operator*(T a, const Tensor44<U>& b) noexcept;
    


//  --------------------------------------------------------
//  DIVISION



//  --------------------------------------------------------
//  OTIMES PRODUCT

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS


    //  TODO: 4x4 determinant 
    //  TODO: 4x4 inverse 
    //  TODO: 4x4 eigenvalues, eigenvectors, & eigensystem

    /*! \brief Trace of the given 4 x 4 tensor
    
        \param[in] a    Tensor to take the trace of
    */
    template <typename T>
    constexpr T     trace(const Tensor44<T>& ten) noexcept;

}

YQ_TYPE_DECLARE(yq::Tensor44D)
YQ_TYPE_DECLARE(yq::Tensor44F)
YQ_TYPE_DECLARE(yq::Tensor44I)
YQ_TYPE_DECLARE(yq::Tensor44U)

