////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__TENSOR_1_1__HPP 1
#include <math/preamble.hpp>
#include <math/Vector1.hpp>

namespace yq {
    /*! \brief 1x1 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor11 {
    
        //! Component type captures the template parameter
        using component_type = T;
        static constexpr const unsigned rows_count  = 1;
        static constexpr const unsigned cols_count  = 1;

        T xx;
        
        constexpr Tensor11() noexcept = default;
        constexpr Tensor11(T _xx) noexcept : xx(_xx) {}
        constexpr Tensor11(all_t, T v) : xx(v) {}
        constexpr Tensor11(columns_t, const Vector1<T>& x) noexcept : xx(x.x) {}
        constexpr Tensor11(diagonal_t, T _xx) noexcept : xx(_xx) {}
        constexpr Tensor11(diagonal_t, const Vector1<T>& v) noexcept : xx(v.x) {}
        constexpr Tensor11(identity_t) noexcept : xx( one_v<T> ) {}
        constexpr Tensor11(nan_t) noexcept : Tensor11(ALL, nan_v<T> ) {}
        constexpr Tensor11(rows_t,    const Vector1<T>& x) noexcept : xx(x.x) {}
        constexpr Tensor11(zero_t) noexcept : Tensor11(ALL, zero_v<T> ) {}
        
        template <glm::qualifier Q>
        explicit constexpr Tensor11(const glm::mat<1,1,T,Q>& t) noexcept;

        //! Defaulted equality operator
        constexpr bool operator==(const Tensor11&) const noexcept = default;
        
        constexpr operator glm::mat<1,1,T,glm::defaultp>() const noexcept;

        constexpr Tensor11      operator+() const noexcept;
        constexpr Tensor11      operator-() const noexcept;
        constexpr Tensor11      operator+ (const Tensor11 &b) const noexcept;
        Tensor11&               operator+=(const Tensor11 &b);
        constexpr Tensor11      operator- (const Tensor11 &b) const noexcept;
        Tensor11&               operator-=(const Tensor11 &b);
    
        template <typename U>
        requires trait::is_arithmetic_v<U>
        constexpr Tensor11<product_t<T,U>>  operator*(U b) const noexcept;

        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
        Tensor11<product_t<T,U>>  operator*=(U b) noexcept;

        template <typename U>
        constexpr Tensor11<product_t<T,U>> operator*(const Tensor11<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor12<product_t<T,U>> operator*(const Tensor12<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor13<product_t<T,U>> operator*(const Tensor13<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor14<product_t<T,U>> operator*(const Tensor14<U>& b) const noexcept;

        template <typename U>
        requires trait::self_mul_v<T,U>
        Tensor11<T>& operator*=(const Tensor11<U>& b) const noexcept;


        template <typename U>
        constexpr Vector1<product_t<T,U>> operator*(const Vector1<U>&b) const noexcept;

            //! Returns the determinant
        constexpr T determinant() const noexcept;

            //! Returns the trace
        constexpr T     trace() const noexcept;

        //! Transpose, which is itself for a 1x1
        constexpr Tensor11 transpose() const ;

        //  --------------------------------------------------------
        //  GETTERS

            //! Gets the diagonal as a vector
            constexpr Vector1<T>  diagonal() const noexcept;

            //! Gets the x-column as a vector
            constexpr Vector1<T>  x_column()  const noexcept;

            //! Gets the x-row as a vector
            constexpr Vector1<T>  x_row() const noexcept;

        //  --------------------------------------------------------
        //  SETTERS

            //! Sets the diagonal
            Tensor11&   diagonal(const Vector1<T>& v);

            //! Sets the diagonal
            Tensor11&   diagonal(T _xx);

            //! Sets the x-column
            Tensor11&   x_column(const Vector1<T>& v);

            //! Sets the x-column
            Tensor11& x_column(T _xx);

            //! Sets the x-row
            Tensor11& x_row(const Vector1<T>& v);

            //! Sets the x-row
            Tensor11& x_row(T _xx);
    };

    YQ_IEEE754_1(Tensor11)
        
//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Create 1x1 tensor by columns
    */
    template <typename T>
    constexpr Tensor11<T>  columns(const Vector1<T>&x)
    {
        return Tensor11<T>(COLUMNS, x);
    }

    /*! \brief Create 1x1 tensor by its diagonal
    */
    template <typename T>
    constexpr Tensor11<T>  diagonal(const Vector1<T>&v)
    {
        return Tensor11<T>(DIAGONAL, v);
    }
    
    /*! \brief Create 1x1 tensor by its diagonal
    */
    template <typename T>
    constexpr Tensor11<T>  diagonal(T x)
    {
        return Tensor11<T>(DIAGONAL, x);
    }

    /*! \brief Create 1x1 tensor by rows
    */
    template <typename T>
    constexpr Tensor11<T>  rows(const Vector1<T>&x)
    {
        return Tensor11<T>(ROWS, x);
    }
    
    YQ_IDENTITY_1(Tensor11, Tensor11(IDENTITY))
    YQ_NAN_1(Tensor11, Tensor11(NAN))
    YQ_ZERO_1(Tensor11, Tensor11(ZERO))
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor11, 
        is_finite(v.xx)
    )
    
    YQ_IS_NAN_1(Tensor11,  
        is_nan(v.xx)
    )

    template <typename T>
    constexpr Tensor11<T>  transpose(const Tensor11<T>&v);

//  --------------------------------------------------------
//  GETTERS

    template <typename T>
    constexpr Vector1<T>  diagonal(const Tensor11<T>& v);

    template <typename T>
    constexpr Vector1<T>  x_column(const Tensor11<T>&v) ;

    template <typename T>
    constexpr Vector1<T>  x_row(const Tensor11<T>&v);


    
//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires std::is_arithmetic_v<T>
    constexpr Tensor11<product_t<T,U>>  operator*(T a, const Tensor11<U>& b);
    
    

//  --------------------------------------------------------
//  DIVISION


    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Tensor11<quotient_t<T,U>>  operator/(const Tensor11<T>& a, U b)
    {
        return Tensor11<quotient_t<T,U>>(
            a.xx/b
        );
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Tensor11<quotient_t<T,U>>  operator/=(const Tensor11<T>& a, U b)
    {
        a.xx/=b;        
        return a;
    }

//  --------------------------------------------------------
//  OTIMES PRODUCT


//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

    template <typename T>
    constexpr T determinant(const Tensor11<T>& a)
    {
        return a.determinant();
    }

    /*! \brief Trace of the 1 x 1 tensor
    
        \param[in] a    Tensor to take the trace of
    */
    template <typename T>
    constexpr T     trace(const Tensor11<T>& a)
    {
        return a.trace();
    }

}

YQ_TYPE_DECLARE(yq::Tensor11D)
YQ_TYPE_DECLARE(yq::Tensor11F)
YQ_TYPE_DECLARE(yq::Tensor11I)
YQ_TYPE_DECLARE(yq::Tensor11U)

