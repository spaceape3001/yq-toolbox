////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__TENSOR_2_3__HPP 1
#include <math/preamble.hpp>
#include <math/Vector2.hpp>
#include <math/Vector3.hpp>

namespace yq {
    /*! \brief 2x3 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor23 {
    
        //! Component type (captures template parameter)
        using component_type = T;
        T xx, xy, xz;
        T yx, yy, yz;


        constexpr Tensor23() noexcept = default;

        constexpr Tensor23(
            T _xx, T _xy, T _xz,
            T _yx, T _yy, T _yz
        ) : 
            xx(_xx), xy(_xy), xz(_xz), 
            yx(_yx), yy(_yy), yz(_yz)
        {
        }
        
        constexpr Tensor23(columns_t, const Vector2<T>& x, const Vector2<T>& y, const Vector2<T>& z) noexcept :
            xx(x.x), xy(y.x), xz(z.x), 
            yx(x.y), yy(y.y), yz(z.y)
        {
        }


        consteval Tensor23(identity_t) : 
            xx(one_v<T>),  xy(zero_v<T>), xz(zero_v<T>), 
            yx(zero_v<T>), yy(one_v<T>),  yz(zero_v<T>)
        {
        }

        consteval Tensor23(nan_t) : 
            xx(nan_v<T>), xy(nan_v<T>), xz(nan_v<T>), 
            yx(nan_v<T>), yy(nan_v<T>), yz(nan_v<T>)
        {
        }

        constexpr Tensor23(rows_t, const Vector3<T>& x, const Vector3<T>& y) :
            xx(x.x), xy(x.y), xz(x.z),
            yx(y.x), yy(y.y), yz(y.z)
        {
        }

        consteval Tensor23(zero_t) : 
            xx(zero_v<T>), xy(zero_v<T>), xz(zero_v<T>), 
            yx(zero_v<T>), yy(zero_v<T>), yz(zero_v<T>)
        {
        }
        
        template <glm::qualifier Q>
        explicit constexpr Tensor23(const glm::mat<2,3,T,Q>& t) noexcept;
        
        //! Defaulted equality operator
        constexpr bool operator==(const Tensor23&) const noexcept = default;

        //! Creates a GLM matrix
        constexpr operator glm::mat<2,3,T,glm::defaultp>() const noexcept;

        //! Positive (affirmation) oeprator
        constexpr Tensor23      operator+() const noexcept;

        //! Negation
        constexpr Tensor23      operator-() const noexcept;
        
        constexpr Tensor23      operator+ (const Tensor23 &b) const noexcept;
        Tensor23&               operator+=(const Tensor23 &b) noexcept;
        constexpr Tensor23      operator- (const Tensor23 &b) const noexcept;
        Tensor23&               operator-=(const Tensor23 &b) noexcept;

        template <typename U>
        requires trait::is_arithmetic_v<U>
        constexpr Tensor23<product_t<T,U>>  operator*(U b) const noexcept;
        
        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
        Tensor23&  operator*=(U b) noexcept;

        template <typename U>
        constexpr Tensor21<product_t<T,U>> operator*(const Tensor31<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor22<product_t<T,U>> operator*(const Tensor32<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor23<product_t<T,U>> operator*(const Tensor33<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor24<product_t<T,U>> operator*(const Tensor34<U>& b) const noexcept;

        template <typename U>
        requires trait::self_mul_v<T,U>
        Tensor23& operator*=(const Tensor33<U>& b) noexcept;

        template <typename U>
        constexpr Vector2<product_t<T,U>> operator*(const Vector3<U>&b) const noexcept;
        
        template <typename U>
        requires trait::is_arithmetic_v<U>
        constexpr Tensor23<quotient_t<T,U>>  operator/(U b) const noexcept;

        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_div_v<T,U>)
        Tensor23&  operator/=(U b) noexcept;

        constexpr Tensor32<T> transpose() const noexcept;


        //  --------------------------------------------------------
        //  GETTERS

            //! X-column of this tensor
            constexpr Vector2<T>  x_column() const noexcept;

            //! Y-column of this tensor
            constexpr Vector2<T>  y_column() const noexcept;

            //! Z-column of this tensor
            constexpr Vector2<T>  z_column() const noexcept;

            //! X-row of this tensor
            constexpr Vector3<T>  x_row() const noexcept;

            //! Y-row of this tensor
            constexpr Vector3<T>  y_row() const noexcept;


        //  --------------------------------------------------------
        //  SETTERS

            //! Sets the X-column of this tensor
            Tensor23& x_column(const Vector2<T>& v);

            //! Sets the X-column of this tensor
            Tensor23& x_column(T _xx, T _yx);

            //! Sets the Y-column of this tensor
            Tensor23& y_column(const Vector2<T>& v);

            //! Sets the Y-column of this tensor
            Tensor23& y_column(T _xy, T _yy);

            //! Sets the Z-column of this tensor
            Tensor23& z_column(const Vector2<T>& v);

            //! Sets the Z-column of this tensor
            Tensor23& z_column(T _xz, T _yz);

            //! Sets the X-row of this tensor
            Tensor23& x_row(const Vector3<T>& v);

            //! Sets the X-row of this tensor
            Tensor23& x_row(T _xx, T _xy, T _xz);

            //! Sets the Y-row of this tensor
            Tensor23& y_row(const Vector3<T>& v);

            //! Sets the Y-row of this tensor
            Tensor23& y_row(T _yx, T _yy, T _yz);
    };

    YQ_IEEE754_1(Tensor23)
        
//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Create 2x3 tensor by columns
    */
    template <typename T>
    constexpr Tensor23<T>  columns(const Vector2<T>&x, const Vector2<T>&y, const Vector2<T>&z)
    {
        return Tensor23<T>(COLUMNS, x, y, z);
    }

    /*! \brief Create 2x3 tensor by rows
    */
    template <typename T>
    constexpr Tensor23<T>  rows(const Vector3<T>&x, const Vector3<T>&y)
    {
        return Tensor23<T>(ROWS, x, y);
    }
    
    YQ_IDENTITY_1(Tensor23, Tensor23<T>(IDENTITY))
    YQ_NAN_1(Tensor23, Tensor23<T>(NAN))
    YQ_ZERO_1(Tensor23, Tensor23<T>(ZERO))
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor23, 
        is_finite(v.xx) && is_finite(v.xy) && is_finite(v.xz) &&
        is_finite(v.yx) && is_finite(v.yy) && is_finite(v.yz)
    )
    
    YQ_IS_NAN_1(Tensor23,  
        is_nan(v.xx) || is_nan(v.xy) || is_nan(v.xz) ||
        is_nan(v.yx) || is_nan(v.yy) || is_nan(v.yz)
    )

    template <typename T>
    constexpr Tensor32<T>  transpose(const Tensor23<T>&v);

//  --------------------------------------------------------
//  GETTERS

    //! Gets the X-column of the provided tensor
    template <typename T>
    constexpr Vector2<T>  x_column(const Tensor23<T>&ten);

    //! Gets the Y-column of the provided tensor
    template <typename T>
    constexpr Vector2<T>  y_column(const Tensor23<T>&ten);

    //! Gets the Z-column of the provided tensor
    template <typename T>
    constexpr Vector2<T>  z_column(const Tensor23<T>&ten);

    //! Gets the X-row of the provided tensor
    template <typename T>
    constexpr Vector3<T>  x_row(const Tensor23<T>&ten);

    //! Gets the Y-row of the provided tensor
    template <typename T>
    constexpr Vector3<T>  y_row(const Tensor23<T>&ten);



//  --------------------------------------------------------
//  ADDITION

//  --------------------------------------------------------
//  SUBTRACTION

//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires trait::is_arithmetic_v<T>
    constexpr Tensor23<product_t<T,U>>  operator*(T a, const Tensor23<U>& b);
    

//  --------------------------------------------------------
//  DIVISION



//  --------------------------------------------------------
//  OTIMES PRODUCT


//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

}

YQ_TYPE_DECLARE(yq::Tensor23D)
YQ_TYPE_DECLARE(yq::Tensor23F)
YQ_TYPE_DECLARE(yq::Tensor23I)
YQ_TYPE_DECLARE(yq::Tensor23U)

