////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__TENSOR_2_2__HPP 1
#include <math/preamble.hpp>
#include <math/Vector2.hpp>

namespace yq {
    /*! \brief 2x2 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor22 {
    
        //! Component type (captures the template parameter)
        using component_type = T;

        static constexpr const unsigned rows_count  = 2;
        static constexpr const unsigned cols_count  = 2;

        T xx, xy;
        T yx, yy;

        constexpr Tensor22() noexcept = default;

        constexpr Tensor22(
            T _xx, T _xy, 
            T _yx, T _yy
        ) : 
            xx(_xx), xy(_xy),
            yx(_yx), yy(_yy)
        {
        }

        constexpr Tensor22(all_t, T v) : 
            xx(v), xy(v),
            yx(v), yy(v)
        {
        }
        
        constexpr Tensor22(columns_t, const Vector2<T>& x, const Vector2<T>& y) noexcept :
            xx(x.x), xy(y.x), 
            yx(x.y), yy(y.y)
        {
        }

        constexpr Tensor22(diagonal_t, T _xx, T _yy) : 
            xx(_xx),  xy(zero_v<T>), 
            yx(zero_v<T>), yy(_yy)
        {
        }

        constexpr Tensor22(diagonal_t, const Vector2<T>& v) : 
            xx(v.x),  xy(zero_v<T>), 
            yx(zero_v<T>), yy(v.y)
        {
        }

        consteval Tensor22(identity_t) : 
            xx(one_v<T>),  xy(zero_v<T>), 
            yx(zero_v<T>), yy(one_v<T>)
        {
        }

        template <typename=void> requires has_nan_v<T>
        consteval Tensor22(nan_t) : Tensor22(ALL, nan_v<T>) {}

        constexpr Tensor22(rows_t, const Vector2<T>& x, const Vector2<T>& y) :
            xx(x.x), xy(x.y), 
            yx(y.x), yy(y.y)
        {
        }

        consteval Tensor22(zero_t) : Tensor22(ALL, zero_v<T>) {}
        
        template <typename=void>
        requires std::is_floating_point_v<T>
        Tensor22(ccw_t, MKS<T,dim::Angle>);

        template <typename=void>
        requires std::is_floating_point_v<T>
        Tensor22(clockwise_t, MKS<T,dim::Angle>);

        template <glm::qualifier Q>
        explicit constexpr Tensor22(const glm::mat<2,2,T,Q>& t) noexcept;
        
        //! Defaulted equality operator
        constexpr bool operator==(const Tensor22&) const noexcept = default;

        //! Implicit conversion to GLM
        explicit operator glm::mat<2,2,T,glm::defaultp>() const noexcept;


        //! Positive (affirmation) operator
        constexpr Tensor22  operator+() const noexcept;

        //! Negation operator
        constexpr Tensor22  operator-() const noexcept;
        
        constexpr Tensor22   operator+ (const Tensor22 &b) const noexcept;
        Tensor22&            operator+=(const Tensor22 &b);
        constexpr Tensor22   operator- (const Tensor22 &b) const noexcept;
        Tensor22&            operator-=(const Tensor22 &b);

        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Tensor22<product_t<T,U>>  operator*(U b) const noexcept;
        
        template <typename U>
        requires (is_arithmetic_v<U> && self_mul_v<T,U>)
        Tensor22&  operator*=(U b) noexcept;
        
        template <typename U>
        Polygon2<product_t<T,U>>  operator*(const Polygon2<U>&) const;
        template <typename U>
        Polyline2<product_t<T,U>>  operator*(const Polyline2<U>&) const;

        template <typename U>
        constexpr Segment2<product_t<T,U>>  operator*(const Segment2<U>&) const noexcept;

        template <typename U>
        constexpr Tensor21<product_t<T,U>> operator*(const Tensor21<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor22<product_t<T,U>> operator*(const Tensor22<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor23<product_t<T,U>> operator*(const Tensor23<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor24<product_t<T,U>> operator*(const Tensor24<U>& b) const noexcept;

        template <typename U>
        requires self_mul_v<T,U>
        Tensor22& operator*=(const Tensor22<U>& b) noexcept;
        
        template <typename U>
        Triangle2<product_t<T,U>> operator*(const Triangle2<U>&) const noexcept;

        template <typename U>
        constexpr Vector2<product_t<T,U>> operator*(const Vector2<U>&b) const noexcept;

        template <typename U>
        std::vector<Vector2<product_t<T,U>>>    operator*(std::span<const Vector2<U>> b) const;

        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Tensor22<quotient_t<T,U>>  operator/(U b) const noexcept;

        template <typename U>
        requires (is_arithmetic_v<U> && self_div_v<T,U>)
        Tensor22&  operator/=(U b) noexcept;

        //! Computes the determinant of this matrix
        constexpr square_t<T> determinant() const noexcept;

        //void        eigenvalues(zreal&,zreal&,zreal&,zreal&b) const;
        //void        eigensystem(zreal&,zvector4&,zreal&,zvector4&,zreal&,zvector4&,zreal&,zvector4&b) const;

        //! Computes the inverse of this matrix
        constexpr Tensor22<inverse_t<T>> inverse() const noexcept;

        /*! \brief Trace of the 2 x 2 tensor
        
            \param[in] a    Tensor to take the trace of
        */
        constexpr T     trace() const noexcept;

        //! Transpose of this matrix
        constexpr Tensor22  transpose() const noexcept;


        //  --------------------------------------------------------
        //  GETTERS

            //! Returns the diagonal
            constexpr Vector2<T>  diagonal() const noexcept;

            //! X-column of this tensor
            constexpr Vector2<T>  x_column() const noexcept;

            //! Y-column of this tensor
            constexpr Vector2<T>  y_column() const noexcept;

            //! X-row of this tensor
            constexpr Vector2<T>  x_row() const noexcept;

            //! Y-row of this tensor
            constexpr Vector2<T>  y_row() const noexcept;


        //  --------------------------------------------------------
        //  SETTERS

            //! Sets the diagonal
            Tensor22&  diagonal(const Vector2<T>& v);

            //! Sets the diagonal
            Tensor22&  diagonal(T _xx, T _yy);

            //! Sets the X-column
            Tensor22& x_column(const Vector2<T>& v);

            //! Sets the X-column
            Tensor22& x_column(T _xx, T _yx);

            //! Sets the Y-column
            Tensor22& y_column(const Vector2<T>& v);

            //! Sets the Y-column
            Tensor22& y_column(T _xy, T _yy);

            //! Sets the X-row
            Tensor22& x_row(const Vector2<T>& v);

            //! Sets the X-row
            Tensor22& x_row(T _xx, T _xy);

            //! Sets the Y-row
            Tensor22& y_row(const Vector2<T>& v);
    
            //! Sets the Y-row
            Tensor22& y_row(T _yx, T _yy);
    
    };

    YQ_IEEE754_1(Tensor22)
        
//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Create 2x2 tensor by columns
    */
    template <typename T>
    constexpr Tensor22<T>  columns(const Vector2<T>&x, const Vector2<T>&y)
    {
        return Tensor22<T>(COLUMNS, x, y);
    }

    /*! \brief Create 2x2 tensor by its diagonal
    */
    template <typename T>
    constexpr Tensor22<T>  diagonal(const Vector2<T>&v)
    {
        return Tensor22<T>(DIAGONAL, v);
    }
    
    /*! \brief Create 2x2 tensor by its diagonal
    */
    template <typename T>
    constexpr Tensor22<T>  diagonal(T x, std::type_identity_t<T> y)
    {
        return Tensor22<T>(DIAGONAL, x, y);
    }
    

    /*! \brief Create 2x2 tensor by rows
    */
    template <typename T>
    constexpr Tensor22<T>  rows(const Vector2<T>&x, const Vector2<T>&y)
    {
        return Tensor22<T>(ROWS, x, y);
    }
    
    //! Creates a matrix that can rotate a vector by the specfied angle
    //! In the counter-clockwise direction
    template <typename T>
    constexpr Tensor22<T>   rotation2(MKS<T,dim::Angle> r);

    template <typename T, glm::qualifier Q>
    constexpr Tensor22<T> tensor(const glm::mat<2,2,T,Q>& t);

    YQ_IDENTITY_1(Tensor22, Tensor22<T>(IDENTITY))
    YQ_NAN_1(Tensor22, Tensor22<T>(NAN))
    
    YQ_ZERO_1(Tensor22, Tensor22<T>(ZERO))
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor22, 
        is_finite(v.xx) && is_finite(v.xy) &&
        is_finite(v.yx) && is_finite(v.yy)
    )
    
    YQ_IS_NAN_1(Tensor22,  
        is_nan(v.xx) || is_nan(v.xy) ||
        is_nan(v.yx) || is_nan(v.yy)
    )

    /*! \brief Transpose of a 2x2 tensor
    */
    template <typename T>
    constexpr Tensor22<T>  transpose(const Tensor22<T>& ten);

//  --------------------------------------------------------
//  GETTERS

    /*! \brief Diagonal of the given tensor
    */
    template <typename T>
    constexpr Vector2<T>  diagonal(const Tensor22<T>& ten);

    /*! \brief X-column of the given tensor
    */
    template <typename T>
    constexpr Vector2<T>  x_column(const Tensor22<T>&ten);

    /*! \brief Y-column of the given tensor
    */
    template <typename T>
    constexpr Vector2<T>  y_column(const Tensor22<T>&ten);

    /*! \brief X-row of the given tensor
    */
    template <typename T>
    constexpr Vector2<T>  x_row(const Tensor22<T>&ten);

    /*! \brief Y-row of the given tensor
    */
    template <typename T>
    constexpr Vector2<T>  y_row(const Tensor22<T>&ten);


//  --------------------------------------------------------
//  --------------------------------------------------------

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Tensor22<product_t<T,U>>  operator*(T a, const Tensor22<T>& b);
    

    //! Determinant of a 2x2 tensor
    template <typename T>
    square_t<T> determinant(const Tensor22<T>& ten);

    //void        eigenvalues(zreal&,zreal&,zreal&,zreal&b) const;
    //void        eigensystem(zreal&,zvector4&,zreal&,zvector4&,zreal&,zvector4&,zreal&,zvector4&b) const;

    //! Inverse of a 2x2 tensor
    template <typename T>
    Tensor22<inverse_t<T>> inverse(const Tensor22<T>&ten);

    /*! \brief Trace of the 2 x 2 tensor
    
        \param[in] a    Tensor to take the trace of
    */
    template <typename T>
    constexpr T     trace(const Tensor22<T>& ten);

}

YQ_TYPE_DECLARE(yq::Tensor22D)
YQ_TYPE_DECLARE(yq::Tensor22F)
YQ_TYPE_DECLARE(yq::Tensor22I)
YQ_TYPE_DECLARE(yq::Tensor22U)

