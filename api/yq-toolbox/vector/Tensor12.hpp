////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_TENSOR_1_2_HPP 1

#include <yq-toolbox/typedef/tensor12.hpp>

#include <yq-toolbox/keywords.hpp>
#include <yq-toolbox/trait/has_identity.hpp>
#include <yq-toolbox/trait/product.hpp>
#include <yq-toolbox/trait/quotient.hpp>
#include <yq-toolbox/trait/self_divide.hpp>
#include <yq-toolbox/trait/self_multiply.hpp>
#include <yq-toolbox/vector/Vector1.hpp>
#include <yq-toolbox/vector/Vector2.hpp>

namespace log4cpp { class CategoryStream; }

namespace yq {

    /*! \brief 1x2 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor12 {
    
        //! Component type
        using component_type = T;
        
        static constexpr const unsigned rows_count  = 1;
        static constexpr const unsigned cols_count  = 2;
        
        T xx, xy;
        
        constexpr Tensor12() noexcept {}
        constexpr Tensor12(T _xx, T _xy) noexcept : xx(_xx), xy(_xy) {}
        constexpr Tensor12(all_t, T v) : 
            xx(v), xy(v)
        {
        }
        constexpr Tensor12(columns_t, const Vector1<T>& x, const Vector1<T>& y) noexcept : xx(x.x), xy(y.x) {}
        consteval Tensor12(identity_t) noexcept : xx(one_v<T>), xy(zero_v<T>) {}
        template <typename=void> requires has_nan_v<T>
        consteval Tensor12(nan_t) noexcept : Tensor12(ALL, nan_v<T>) {}
        constexpr Tensor12(rows_t, Vector2<T>& v) noexcept : xx(v.x), xy(v.y) {}
        consteval Tensor12(zero_t) noexcept : Tensor12(ALL, zero_v<T>) {}
        
        #ifdef YQ_USE_GLM
        template <glm::qualifier Q>
        explicit constexpr Tensor12(const glm::mat<1,2,T,Q>& t) noexcept;
        #endif

        //! Defaulted equality operator
        constexpr bool operator==(const Tensor12&) const noexcept = default;

        #ifdef YQ_USE_GLM
        constexpr operator glm::mat<1,2,T,glm::defaultp>() const noexcept;
        #endif

        //! Positive (affirmation) operator
        constexpr Tensor12  operator+() const noexcept;

        //! Negation
        constexpr Tensor12  operator-() const noexcept;

        constexpr Tensor12<T>   operator+ (const Tensor12<T> &b) const noexcept;
        Tensor12<T>&            operator+=(const Tensor12<T> &b) noexcept;
        constexpr Tensor12<T>   operator- (const Tensor12<T> &b) const noexcept;
        Tensor12<T>&            operator-=(const Tensor12<T> &b) noexcept;

        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Tensor12<product_t<T,U>>  operator*(U b) const noexcept;

        template <typename U>
        requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
        Tensor12<product_t<T,U>>            operator*=(U b) noexcept;

        template <typename U>
        constexpr Segment1<product_t<T,U>>  operator*(const Segment2<U>&) const noexcept;

        template <typename U>
        constexpr Tensor11<product_t<T,U>> operator*(const Tensor21<U>& b) const noexcept;

        template <typename U>
        constexpr Tensor12<product_t<T,U>> operator*(const Tensor22<U>& b) const noexcept;

        template <typename U>
        requires self_multiply_v<T,U>
        Tensor12<T>& operator*=(const Tensor22<U>& b) noexcept;

        template <typename U>
        constexpr Tensor13<product_t<T,U>> operator*(const Tensor23<U>& b) const noexcept;

        template <typename U>
        constexpr Tensor14<product_t<T,U>> operator*(const Tensor24<U>& b) const noexcept;

        template <typename U>
        constexpr Vector1<product_t<T,U>>   operator*(const Vector2<U>&b) const noexcept;

        template <typename U>
        std::vector<Vector1<product_t<T,U>>>    operator*(std::span<const Vector2<U>> b) const;

        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Tensor12<quotient_t<T,U>>  operator/(U b) const noexcept;

        template <typename U>
        requires (is_arithmetic_v<U> && self_divide_v<T,U>)
        Tensor12<quotient_t<T,U>>               operator/=(U b) noexcept;

        constexpr Tensor21<T> transpose() const noexcept;

        //  --------------------------------------------------------
        //  GETTERS

            //! Gets the x-column as a vector
            constexpr Vector1<T>  x_column() const noexcept;

            //! Gets the y-column as a vector
            constexpr Vector1<T>  y_column() const noexcept;

            //! Gets the x-row as a vector
            constexpr Vector2<T>  x_row() const noexcept;

        //  --------------------------------------------------------
        //  SETTERS

            //! Sets the X-column
            Tensor12& x_column(const Vector1<T>& v);

            //! Sets the X-column
            Tensor12& x_column(T _xx);

            //! Sets the Y-column
            Tensor12& y_column(const Vector1<T>& v);

            //! Sets the Y-column
            Tensor12& y_column(T _xy);

            //! Sets the X-row
            Tensor12& x_row(const Vector2<T>& v);

            //! Sets the X-row
            Tensor12& x_row(T _xx, T _xy);
            
        //  --------------------------------------------------------
        //  AllComponents Adapters

            /*! Adds a value to all the elements
            */
            constexpr Tensor12 all_add(T b) const noexcept;
            
            //! Decrements all elements
            Tensor12&   all_decrement(T) noexcept;

            //! Increments all elements
            Tensor12&   all_increment(T) noexcept;

            /*! \brief Subtracts value from all elements
            */
            constexpr Tensor12 all_subtract(T b) const noexcept;
            

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
            constexpr bool all_test(const Tensor12& b, Pred pred) const noexcept;

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
            constexpr bool any_test(const Tensor12& b, Pred pred) const noexcept;
            
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

            static bool less_xx( const Tensor12& a, const Tensor12& b) { return a.xx < b.xx; }
            static bool less_xy( const Tensor12& a, const Tensor12& b) { return a.xy < b.xy; }

    };

    YQ_IEEE754_1(Tensor12)
        
//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Create 1x2 tensor by columns
    */
    template <typename T>
    constexpr Tensor12<T>  columns(const Vector1<T>&x, const Vector1<T>&y)
    {
        return Tensor12<T>(COLUMNS, x, y);
    }

    /*! \brief Create 1x2 tensor by rows
    */
    template <typename T>
    constexpr Tensor12<T>  rows(const Vector2<T>&x)
    {
        return Tensor12<T>(ROWS, x);
    }
    
    YQ_IDENTITY_1(Tensor12, Tensor12<T>(IDENTITY))
    YQ_NAN_1(Tensor12, Tensor12<T>(NAN))
    YQ_ZERO_1(Tensor12, Tensor12<T>(ZERO))
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor12, 
        is_finite(v.xx) && is_finite(v.xy)
    )
    
    YQ_IS_NAN_1(Tensor12,  
        is_nan(v.xx) || is_nan(v.xy)
    )

    //! All components adapter
    //! Use this to activate the "all" component adapters in tensor12
    template <typename T>
    AllComponents<Tensor12<T>>   all(Tensor12<T>& val);

    //! All components adapter
    //! Use this to activate the "all" component adapters in tensor12
    template <typename T>
    AllComponents<const Tensor12<T>>   all(const Tensor12<T>& val);
    
    #if 0
    template <typename T>
    ElemComponents<Tensor12<T>>   elem(Tensor12<T>& val);

    template <typename T>
    ElemComponents<const Tensor12<T>>   elem(const Tensor12<T>& val);
    #endif

    template <typename T>
    AnyComponents<Tensor12<T>>   any(Tensor12<T>& val);

    template <typename T>
    AnyComponents<const Tensor12<T>>   any(const Tensor12<T>& val);

    template <typename T>
    constexpr Tensor21<T>  transpose(const Tensor12<T>&v) noexcept;

//  --------------------------------------------------------
//  GETTERS

    template <typename T>
    constexpr Vector1<T>  x_column(const Tensor12<T>&ten) noexcept;

    template <typename T>
    constexpr Vector1<T>  y_column(const Tensor12<T>&ten) noexcept;

    template <typename T>
    constexpr Vector2<T>  x_row(const Tensor12<T>&ten) noexcept;

//  --------------------------------------------------------
//  ADDITION

//  --------------------------------------------------------
//  SUBTRACTION
    
//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires std::is_arithmetic_v<T>
    constexpr Tensor12<product_t<T,U>>  operator*(T a, const Tensor12<U>& b);
    
//  --------------------------------------------------------
//  DIVISION

//  --------------------------------------------------------
//  OTIMES PRODUCT

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

}

YQ_TYPE_DECLARE(yq::Tensor12D)
YQ_TYPE_DECLARE(yq::Tensor12F)
YQ_TYPE_DECLARE(yq::Tensor12I)
YQ_TYPE_DECLARE(yq::Tensor12U)

