////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__TENSOR_3_1__HPP 1
#include <math/preamble.hpp>
#include <math/Vector1.hpp>
#include <math/Vector3.hpp>

namespace yq {
    /*! \brief 3x1 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor31 {
    
        //! Component type (captures template parameter)
        using component_type = T;

        static constexpr const unsigned rows_count  = 3;
        static constexpr const unsigned cols_count  = 1;
        
        T xx;
        T yx;
        T zx;

        constexpr Tensor31() noexcept = default;

        constexpr Tensor31(
            T _xx, 
            T _yx, 
            T _zx
        ) : 
            xx(_xx),
            yx(_yx),
            zx(_zx)
        {
        }
        
        constexpr Tensor31(all_t, T v) : 
            xx(v), 
            yx(v), 
            zx(v)
        {
        }

        constexpr Tensor31(columns_t, const Vector3<T>& x) noexcept :
            xx(x.x),
            yx(x.y),
            zx(x.z)
        {
        }

        consteval Tensor31(identity_t) : 
            xx(one_v<T>),  
            yx(zero_v<T>), 
            zx(zero_v<T>)
        {
        }

        template <typename=void> requires trait::has_nan_v<T>
        consteval Tensor31(nan_t) : Tensor31(ALL, nan_v<T>) {}

        constexpr Tensor31(rows_t, const Vector1<T>& x, const Vector1<T>& y, const Vector1<T>& z) :
            xx(x.x), 
            yx(y.x), 
            zx(z.x)
        {
        }

        consteval Tensor31(zero_t) : Tensor31(ALL, zero_v<T>) {} 
        
        template <glm::qualifier Q>
        explicit constexpr Tensor31(const glm::mat<3,1,T,Q>& t) noexcept;
        
        //! Defaulted equality operator
        constexpr bool operator==(const Tensor31&) const noexcept = default;

        //! Conversion to GLM
        constexpr operator glm::mat<3,1,T,glm::defaultp>() const noexcept;

        //! Positive (affirmation) operator
        constexpr const Tensor31&  operator+() const noexcept;

        //! Negation
        constexpr Tensor31  operator-() const noexcept;
        
        constexpr Tensor31<T>   operator+ (const Tensor31<T> &b) const noexcept;
        Tensor31<T>&            operator+=(const Tensor31<T> &b) noexcept;
        constexpr Tensor31<T>   operator- (const Tensor31<T> &b) const noexcept;
        Tensor31<T>&            operator-=(const Tensor31<T> &b) noexcept;
        
        template <typename U>
        requires trait::is_arithmetic_v<U>
        constexpr Tensor31<product_t<T,U>>  operator*(U b) const noexcept;

        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
        Tensor31<T>&  operator*=(U b) noexcept;

        template <typename U>
        constexpr Segment3<product_t<T,U>>  operator*(const Segment1<U>&) const noexcept;

        template <typename U>
        constexpr Tensor31<product_t<T,U>> operator*(const Tensor11<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor32<product_t<T,U>> operator*(const Tensor12<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor33<product_t<T,U>> operator*(const Tensor13<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor34<product_t<T,U>> operator*(const Tensor14<U>& b) const noexcept;

        template <typename U>
        requires trait::self_mul_v<T,U>
        Tensor31<T>& operator*=(const Tensor11<U>& b) noexcept;

        template <typename U>
        constexpr Vector3<product_t<T,U>> operator*(const Vector1<U>&b) const noexcept;
        
        template <typename U>
        requires trait::is_arithmetic_v<U>
        constexpr Tensor31<quotient_t<T,U>>  operator/(U b) const noexcept;
        
        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_div_v<T,U>)
        Tensor31<T>&  operator/=(U b) noexcept;

        constexpr Tensor13<T> transpose() const noexcept;

        //  --------------------------------------------------------
        //  GETTERS

            //! X-column of this vector
            constexpr Vector3<T>  x_column() const noexcept;

            //! X-row of this vector
            constexpr Vector1<T>  x_row() const noexcept;

            //! Y-row of this vector
            constexpr Vector1<T>  y_row() const noexcept;

            //! Z-row of this vector
            constexpr Vector1<T>  z_row() const noexcept;


        //  --------------------------------------------------------
        //  SETTERS

            //! Sets the x-column
            Tensor31& x_column(const Vector3<T>& v);

            //! Sets the x-column
            Tensor31& x_column(T _xx, T _yx, T _zx);

            //! Sets the x-row
            Tensor31& x_row(const Vector1<T>& v);

            //! Sets the x-row
            Tensor31& x_row(T _xx);

            //! Sets the y-row
            Tensor31& y_row(const Vector1<T>& v);

            //! Sets the y-row
            Tensor31& y_row(T _yx);

            //! Sets the z-row
            Tensor31& z_row(const Vector1<T>& v);

            //! Sets the z-row
            Tensor31& z_row(T _zx);
    };

    YQ_IEEE754_1(Tensor31)
        
//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Create 3x1 tensor by columns
    */
    template <typename T>
    constexpr Tensor31<T>  columns(const Vector3<T>&x)
    {
        return Tensor31<T>(ROWS, x);
    }

    /*! \brief Create 3x1 tensor by rows
    */
    template <typename T>
    constexpr Tensor31<T>  rows(const Vector1<T>&x, const Vector1<T>&y, const Vector1<T>&z)
    {
        return Tensor31<T>(ROWS, x, y, z);
    }
    
    YQ_IDENTITY_1(Tensor31, Tensor31<T>(IDENTITY))

    YQ_NAN_1(Tensor31, Tensor31<T>(NAN))
    
    YQ_ZERO_1(Tensor31, Tensor31<T>(ZERO))
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor31, 
        is_finite(v.xx) &&
        is_finite(v.yx) &&
        is_finite(v.zx)
    )
    
    YQ_IS_NAN_1(Tensor31,  
        is_nan(v.xx) ||
        is_nan(v.yx) ||
        is_nan(v.zx)
    )
    
    template <typename T>
    constexpr Tensor13<T>  transpose(const Tensor31<T>&v);

//  --------------------------------------------------------
//  GETTERS

    //! X-column of given tensor
    template <typename T>
    constexpr Vector3<T>  x_column(const Tensor31<T>&ten);

    //! X-row of given tensor
    template <typename T>
    constexpr Vector1<T>  x_row(const Tensor31<T>&ten);

    //! Y-row of given tensor
    template <typename T>
    constexpr Vector1<T>  y_row(const Tensor31<T>&ten);

    //! Z-row of given tensor
    template <typename T>
    constexpr Vector1<T>  z_row(const Tensor31<T>&ten);

//  --------------------------------------------------------
//  ADDITION

//  --------------------------------------------------------
//  SUBTRACTION
    
//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires trait::is_arithmetic_v<T>
    constexpr Tensor31<product_t<T,U>>  operator*(T a, const Tensor31<U>& b);
    
//  --------------------------------------------------------
//  DIVISION

//  --------------------------------------------------------
//  OTIMES PRODUCT

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

}

YQ_TYPE_DECLARE(yq::Tensor31D)
YQ_TYPE_DECLARE(yq::Tensor31F)
YQ_TYPE_DECLARE(yq::Tensor31I)
YQ_TYPE_DECLARE(yq::Tensor31U)

