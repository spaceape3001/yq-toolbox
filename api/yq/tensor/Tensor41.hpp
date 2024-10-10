////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_TENSOR_4_1_HPP 1

#include <yq/typedef/tensor41.hpp>

#include <yq-toolbox/keywords.hpp>
#include <yq/trait/has_identity.hpp>
#include <yq/trait/product.hpp>
#include <yq/trait/quotient.hpp>
#include <yq/trait/self_divide.hpp>
#include <yq/trait/self_multiply.hpp>
#include <yq-toolbox/vector/Vector1.hpp>
#include <yq-toolbox/vector/Vector4.hpp>

namespace log4cpp { class CategoryStream; }

namespace yq {
    /*! \brief 4x1 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor41 {
    
        //! Component type
        using component_type = T;

        static constexpr const unsigned rows_count  = 4;
        static constexpr const unsigned cols_count  = 1;
        
        T xx;
        T yx;
        T zx;
        T wx;


        constexpr Tensor41() noexcept = default;

        constexpr Tensor41(
            T _xx, 
            T _yx, 
            T _zx, 
            T _wx
        ) : 
            xx(_xx),
            yx(_yx),
            zx(_zx),
            wx(_wx)
        {
        }
        
        constexpr Tensor41(all_t, T v) : 
            xx(v), 
            yx(v), 
            zx(v), 
            wx(v)
        {
        }

        constexpr Tensor41(columns_t, const Vector4<T>& x) noexcept :
            xx(x.x),
            yx(x.y),
            zx(x.z),
            wx(x.w)
        {
        }

        consteval Tensor41(identity_t) : 
            xx(one_v<T>),  
            yx(zero_v<T>), 
            zx(zero_v<T>), 
            wx(zero_v<T>)
        {
        }

        template <typename=void> requires has_nan_v<T>
        consteval Tensor41(nan_t) : Tensor41(ALL, nan_v<T>) {}

        constexpr Tensor41(rows_t, const Vector1<T>& x, const Vector1<T>& y, const Vector1<T>& z, const Vector1<T>& w) :
            xx(x.x), 
            yx(y.x), 
            zx(z.x),
            wx(w.x)
        {
        }

        consteval Tensor41(zero_t) : Tensor41(ALL, zero_v<T>) {}
        
        #ifdef YQ_USE_GLM
        template <glm::qualifier Q>
        explicit constexpr Tensor41(const glm::mat<4,1,T,Q>& t) noexcept;
        #endif

        //! Defaulted equality operator
        constexpr bool operator==(const Tensor41&) const noexcept = default;

        #ifdef YQ_USE_GLM
        //! Conversion to GLM
        constexpr operator glm::mat<4,1,T,glm::defaultp>() const noexcept ;
        #endif

        //! Positive (affirmation) operator
        constexpr Tensor41<T>  operator+() const noexcept;
        //! Negation operator
        constexpr Tensor41<T>  operator-() const noexcept;

        constexpr Tensor41<T>   operator+ (const Tensor41<T> &b) const noexcept;
        Tensor41<T>&            operator+=(const Tensor41<T> &b)  noexcept;
        constexpr Tensor41<T>   operator- (const Tensor41<T> &b) const noexcept;
        Tensor41<T>&            operator-=(const Tensor41<T> &b)  noexcept;
        
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Tensor41<product_t<T,U>>  operator*(U b) const noexcept;
        template <typename U>
        requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
        Tensor41&   operator*=(U b) noexcept;

        template <typename U>
        constexpr Segment4<product_t<T,U>>  operator*(const Segment1<U>&) const noexcept;

        template <typename U>
        constexpr Tensor41<product_t<T,U>> operator*(const Tensor11<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor42<product_t<T,U>> operator*(const Tensor12<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor43<product_t<T,U>> operator*(const Tensor13<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor44<product_t<T,U>> operator*(const Tensor14<U>& b) const noexcept;

        template <typename U>
        requires self_multiply_v<T,U>
        Tensor41& operator*=(const Tensor11<U>& b) noexcept;

        template <typename U>
        constexpr Vector4<product_t<T,U>> operator*(const Vector1<U>&b) const noexcept;

        template <typename U>
        std::vector<Vector4<product_t<T,U>>>    operator*(std::span<const Vector1<U>> b) const;

        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Tensor41<quotient_t<T,U>>  operator/(U b) const noexcept;
        
        template <typename U>
        requires (is_arithmetic_v<U> && self_divide_v<T,U>)
        Tensor41&  operator/=(U b) noexcept;

        constexpr Tensor14<T> transpose() const noexcept;


        //  --------------------------------------------------------
        //  GETTERS

            //! X column of this tensor
            constexpr Vector4<T>  x_column() const noexcept;

            //! X row of this tensor
            constexpr Vector1<T>  x_row() const noexcept;

            //! Y row of this tensor
            constexpr Vector1<T>  y_row() const noexcept;

            //! Z row of this tensor
            constexpr Vector1<T>  z_row() const noexcept;

            //! W row of this tensor
            constexpr Vector1<T>  w_row() const noexcept;


        //  --------------------------------------------------------
        //  SETTERS

            //! Sets the X-column
            Tensor41& x_column(const Vector4<T>& v) noexcept;

            //! Sets the X-column
            Tensor41& x_column(T _xx, T _yx, T _zx, T _wx) noexcept;

            //! Sets the X-row
            Tensor41& x_row(const Vector1<T>& v) noexcept;

            //! Sets the X-row
            Tensor41& x_row(T _xx) noexcept;

            //! Sets the Y-row
            Tensor41& y_row(const Vector1<T>& v) noexcept;

            //! Sets the Y-row
            Tensor41& y_row(T _yx) noexcept;

            //! Sets the Z-row
            Tensor41& z_row(const Vector1<T>& v) noexcept;

            //! Sets the Z-row
            Tensor41& z_row(T _zx) noexcept;

            //! Sets the W-row
            Tensor41& w_row(const Vector1<T>& v) noexcept;

            //! Sets the W-row
            Tensor41& w_row(T _wx) noexcept;



        //  --------------------------------------------------------
        //  AllComponents Adapters

            /*! Adds a value to all the elements
            */
            constexpr Tensor41 all_add(T b) const noexcept;
            
            //! Decrements all elements
            Tensor41&   all_decrement(T) noexcept;

            //! Increments all elements
            Tensor41&   all_increment(T) noexcept;

            /*! \brief Subtracts value from all elements
            */
            constexpr Tensor41 all_subtract(T b) const noexcept;
            

            /*! Tests every element
                
                This applies the given test to every component, 
                returns TRUE if all tests are true.
                \note y, z, w component tests may be skipped if the x-component test fails.
                \param[in] pred The predicate (your test)
            */
            template <typename Pred>
            constexpr bool all_test(Pred pred) const noexcept;

            /*! Tests every element
                This applies the given test to every component, 
                returns TRUE if all tests are true.
                \note y, z, w component tests may be skipped if the x-component test fails.
                \param[in] b The other vector
                \param[in] pred The predicate (your test)
            */
            template <typename Pred>
            constexpr bool all_test(const Tensor41& b, Pred pred) const noexcept;

            /*! Tests every element
                This applies the given test to every component, 
                returns TRUE if all tests are true.
                \note y, z, w component tests may be skipped if the x-component test fails.
                \param[in] b The other value
                \param[in] pred The predicate (your test)
            */
            template <typename Pred>
            constexpr bool all_test(T b, Pred pred) const noexcept;

        //  --------------------------------------------------------
        //  AnyComponents Adapters
            
            /*! Tests every element
                This applies the given test to every component, 
                returns TRUE if any test is true.
                \note y, z, w component tests may be skipped if the x-component test passes.
                \param[in] pred The predicate (your test)
            */
            template <typename Pred>
            constexpr bool any_test(Pred pred) const noexcept;
            
            /*! Tests every element
                This applies the given test to every component, 
                returns TRUE if any test is true.
                \note y, z, w component tests may be skipped if the x-component test passes.
                \param[in] b The other vector
                \param[in] pred The predicate (your test)
            */
            template <typename Pred>
            constexpr bool any_test(const Tensor41& b, Pred pred) const noexcept;
            
            /*! Tests every element
                This applies the given test to every component, 
                returns TRUE if any test is true.
                \note y, z, w component tests may be skipped if the x-component test passes.
                \param[in] b The other value
                \param[in] pred The predicate (your test)
            */
            template <typename Pred>
            constexpr bool any_test(T b, Pred pred) const noexcept;

        //  --------------------------------------------------------
        //  COMPARISONS

            static bool less_xx( const Tensor41& a, const Tensor41& b) { return a.xx < b.xx; }

            static bool less_yx( const Tensor41& a, const Tensor41& b) { return a.yx < b.yx; }

            static bool less_zx( const Tensor41& a, const Tensor41& b) { return a.zx < b.zx; }

            static bool less_wx( const Tensor41& a, const Tensor41& b) { return a.x < b.x; }

    };

    YQ_IEEE754_1(Tensor41)
        
//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Create 4x1 tensor by columns
    */
    template <typename T>
    constexpr Tensor41<T>  columns(const Vector4<T>&x) noexcept
    {
        return Tensor41<T>(COLUMNS, x);
    }

    /*! \brief Create 4x1 tensor by rows
    */
    template <typename T>
    constexpr Tensor41<T>  rows(const Vector1<T>&x, const Vector1<T>&y, const Vector1<T>&z, const Vector1<T>&w) noexcept
    {
        return Tensor41<T>(ROWS, x, y, z, w);
    }
    
    YQ_IDENTITY_1(Tensor41, Tensor41<T>(IDENTITY))
    YQ_NAN_1(Tensor41, Tensor41<T>(NAN))
    YQ_ZERO_1(Tensor41, Tensor41<T>(ZERO))

    //! All components adapter
    //! Use this to activate the "all" component adapters in tensor41
    template <typename T>
    AllComponents<Tensor41<T>>   all(Tensor41<T>& val);

    //! All components adapter
    //! Use this to activate the "all" component adapters in tensor41
    template <typename T>
    AllComponents<const Tensor41<T>>   all(const Tensor41<T>& val);
    
    #if 0
    template <typename T>
    ElemComponents<Tensor41<T>>   elem(Tensor41<T>& val);

    template <typename T>
    ElemComponents<const Tensor41<T>>   elem(const Tensor41<T>& val);
    #endif

    template <typename T>
    AnyComponents<Tensor41<T>>   any(Tensor41<T>& val);

    template <typename T>
    AnyComponents<const Tensor41<T>>   any(const Tensor41<T>& val);

    template <typename T>
    constexpr Tensor14<T>  transpose(const Tensor41<T>&v);
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor41, 
        is_finite(v.xx) &&
        is_finite(v.yx) &&
        is_finite(v.zx) &&
        is_finite(v.wx)
    )
    
    YQ_IS_NAN_1(Tensor41,  
        is_nan(v.xx) ||
        is_nan(v.yx) ||
        is_nan(v.zx) ||
        is_nan(v.wx)
    )

//  --------------------------------------------------------
//  GETTERS

    //! X-column of given tensor
    template <typename T>
    constexpr Vector4<T>  x_column(const Tensor41<T>&ten)  noexcept
    {
        return ten.x_column();
    }

    //! X-row of given tensor
    template <typename T>
    constexpr Vector1<T>  x_row(const Tensor41<T>&ten)  noexcept
    {
        return ten.x_row();
    }

    //! Y-row of given tensor
    template <typename T>
    constexpr Vector1<T>  y_row(const Tensor41<T>&ten) noexcept
    {
        return ten.y_row();
    }

    //! Z-row of given tensor
    template <typename T>
    constexpr Vector1<T>  z_row(const Tensor41<T>&ten) noexcept
    {
        return ten.z_row();
    }

    //! W-row of given tensor
    template <typename T>
    constexpr Vector1<T>  w_row(const Tensor41<T>&ten) noexcept
    {
        return ten.w_row();
    }



//  --------------------------------------------------------
//  ADDITION



//  --------------------------------------------------------
//  SUBTRACTION

    
//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Tensor41<product_t<T,U>>  operator*(T a, const Tensor41<T>& b) noexcept;
    
    

//  --------------------------------------------------------
//  DIVISION


//  --------------------------------------------------------
//  OTIMES PRODUCT


//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

}

YQ_TYPE_DECLARE(yq::Tensor41D)
YQ_TYPE_DECLARE(yq::Tensor41F)
YQ_TYPE_DECLARE(yq::Tensor41I)
YQ_TYPE_DECLARE(yq::Tensor41U)

