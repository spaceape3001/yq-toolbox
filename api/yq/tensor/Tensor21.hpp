////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_TENSOR_2_1_HPP 1

#include <yq/typedef/tensor21.hpp>

#include <yq/keywords.hpp>
#include <yq/trait/has_identity.hpp>
#include <yq/trait/product.hpp>
#include <yq/trait/quotient.hpp>
#include <yq/trait/self_divide.hpp>
#include <yq/trait/self_multiply.hpp>
#include <yq/vector/Vector1.hpp>
#include <yq/vector/Vector2.hpp>

namespace log4cpp { class CategoryStream; }

namespace yq {
    /*! \brief 2x1 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor21 {
    
        //! Component type (captures template parameter)
        using component_type = T;
        T xx;
        T yx;

        static constexpr const unsigned rows_count  = 2;
        static constexpr const unsigned cols_count  = 1;

        constexpr Tensor21() noexcept = default;

        constexpr Tensor21(
            T _xx, 
            T _yx
        ) : 
            xx(_xx),
            yx(_yx)
        {
        }
        
        constexpr Tensor21(all_k, T v) : 
            xx(v), 
            yx(v)
        {
        }

        constexpr Tensor21(columns_t, const Vector2<T>& x) noexcept :
            xx(x.x),
            yx(x.y)
        {
        }

        consteval Tensor21(identity_k) : 
            xx(one_v<T>),  
            yx(zero_v<T>)
        {
        }

        template <typename=void> requires has_nan_v<T>
        consteval Tensor21(nan_t) : Tensor21(ALL, nan_v<T>) {}

        constexpr Tensor21(rows_t, const Vector1<T>& x, const Vector1<T>& y) :
            xx(x.x), 
            yx(y.x)
        {
        }

        consteval Tensor21(zero_k) : Tensor21(ALL, zero_v<T>) {} 
        
        #ifdef YQ_USE_GLM
        template <glm::qualifier Q>
        explicit constexpr Tensor21(const glm::mat<2,1,T,Q>& t) noexcept;
        #endif
        
        
        //! Defaulted equality operator
        constexpr bool operator==(const Tensor21&) const noexcept = default;

        #ifdef YQ_USE_GLM
        constexpr operator glm::mat<2,1,T,glm::defaultp>() const noexcept ;
        #endif

        //! Positive (affirmation) operator
        constexpr Tensor21  operator+() const noexcept;

        //! Negation operator
        constexpr Tensor21  operator-() const noexcept;

        constexpr Tensor21   operator+ (const Tensor21 &b) const noexcept;
        Tensor21&            operator+=(const Tensor21 &b) noexcept;
        constexpr Tensor21   operator- (const Tensor21 &b) const noexcept;
        Tensor21&            operator-=(const Tensor21 &b) noexcept;
        
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Tensor21<product_t<T,U>>  operator*(U b) const noexcept;

        template <typename U>
        requires (is_arithmetic_v<U> && self_multiply_v<T,U>) 
        Tensor21&  operator*=(U b) noexcept;

        template <typename U>
        constexpr Segment2<product_t<T,U>>  operator*(const Segment1<U>&) const noexcept;

        template <typename U>
        constexpr Tensor21<product_t<T,U>> operator*(const Tensor11<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor22<product_t<T,U>> operator*(const Tensor12<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor23<product_t<T,U>> operator*(const Tensor13<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor24<product_t<T,U>> operator*(const Tensor14<U>& b) const noexcept;

        template <typename U>
        requires self_multiply_v<T,U>
        Tensor21<T>& operator*=(const Tensor11<U>& b) noexcept;

        template <typename U>
        constexpr Vector2<product_t<T,U>> operator*(const Vector1<U>&b) const noexcept;

        template <typename U>
        std::vector<Vector2<product_t<T,U>>>    operator*(std::span<const Vector1<U>> b) const;

        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Tensor21<quotient_t<T,U>>  operator/(U b) const noexcept;

        template <typename U>
        requires (is_arithmetic_v<U> && self_divide_v<T,U>) 
        Tensor21<T>&  operator/=(U b) noexcept;

        constexpr Tensor12<T> transpose() const noexcept;


        //  --------------------------------------------------------
        //  GETTERS

            constexpr Vector2<T>  x_column() const noexcept;
            constexpr Vector1<T>  x_row() const noexcept;
            constexpr Vector1<T>  y_row() const noexcept;
        //  --------------------------------------------------------
        //  SETTERS

            Tensor21& x_column(const Vector2<T>& v);

            Tensor21& x_column(T _xx, T _yx);

            Tensor21& x_row(const Vector1<T>& v);

            Tensor21& x_row(T _xx);

            Tensor21& y_row(const Vector1<T>& v);

            Tensor21& y_row(T _yx);


        //  --------------------------------------------------------
        //  AllComponents Adapters

            /*! Adds a value to all the elements
            */
            constexpr Tensor21 all_add(T b) const noexcept;
            
            //! Decrements all elements
            Tensor21&   all_decrement(T) noexcept;

            //! Increments all elements
            Tensor21&   all_increment(T) noexcept;

            /*! \brief Subtracts value from all elements
            */
            constexpr Tensor21 all_subtract(T b) const noexcept;
            

            /*! Tests every element
                
                This applies the given test to every component, 
                returns TRUE if all tests are true.
                \note y, z, w component tests may be skipped if the x-component test fails.
                \param[in] pred The predicate (your test)
            */
            template <typename Pred>
            constexpr bool all_kest(Pred pred) const noexcept;

            /*! Tests every element
                This applies the given test to every component, 
                returns TRUE if all tests are true.
                \note y, z, w component tests may be skipped if the x-component test fails.
                \param[in] b The other vector
                \param[in] pred The predicate (your test)
            */
            template <typename Pred>
            constexpr bool all_kest(const Tensor21& b, Pred pred) const noexcept;

            /*! Tests every element
                This applies the given test to every component, 
                returns TRUE if all tests are true.
                \note y, z, w component tests may be skipped if the x-component test fails.
                \param[in] b The other value
                \param[in] pred The predicate (your test)
            */
            template <typename Pred>
            constexpr bool all_kest(T b, Pred pred) const noexcept;

        //  --------------------------------------------------------
        //  AnyComponents Adapters
            
            /*! Tests every element
                This applies the given test to every component, 
                returns TRUE if any test is true.
                \note y, z, w component tests may be skipped if the x-component test passes.
                \param[in] pred The predicate (your test)
            */
            template <typename Pred>
            constexpr bool any_kest(Pred pred) const noexcept;
            
            /*! Tests every element
                This applies the given test to every component, 
                returns TRUE if any test is true.
                \note y, z, w component tests may be skipped if the x-component test passes.
                \param[in] b The other vector
                \param[in] pred The predicate (your test)
            */
            template <typename Pred>
            constexpr bool any_kest(const Tensor21& b, Pred pred) const noexcept;
            
            /*! Tests every element
                This applies the given test to every component, 
                returns TRUE if any test is true.
                \note y, z, w component tests may be skipped if the x-component test passes.
                \param[in] b The other value
                \param[in] pred The predicate (your test)
            */
            template <typename Pred>
            constexpr bool any_kest(T b, Pred pred) const noexcept;

        //  --------------------------------------------------------
        //  COMPARISONS

            static bool less_xx( const Tensor21& a, const Tensor21& b) { return a.xx < b.xx; }

            static bool less_yx( const Tensor21& a, const Tensor21& b) { return a.yx < b.yx; }
    };

    YQ_IEEE754_1(Tensor21)
        
//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Create 2x1 tensor by columns
    */
    template <typename T>
    constexpr Tensor21<T>  columns(const Vector2<T>&x)
    {
        return Tensor21<T>(COLUMNS, x);
    }

    /*! \brief Create 2x1 tensor by rows
    */
    template <typename T>
    constexpr Tensor21<T>  rows(const Vector1<T>&x, const Vector1<T>&y)
    {
        return Tensor21<T>(ROWS, x, y);
    }
    
    YQ_IDENTITY_1(Tensor21, Tensor21<T>(IDENTITY))
    YQ_NAN_1(Tensor21, Tensor21<T>(NAN))
    YQ_ZERO_1(Tensor21, Tensor21<T>(ZERO))
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor21, 
        is_finite(v.xx) &&
        is_finite(v.yx)
    )
    
    YQ_IS_NAN_1(Tensor21,  
        is_nan(v.xx) ||
        is_nan(v.yx)
    )

    //! All components adapter
    //! Use this to activate the "all" component adapters in tensor21
    template <typename T>
    AllComponents<Tensor21<T>>   all(Tensor21<T>& val);

    //! All components adapter
    //! Use this to activate the "all" component adapters in tensor21
    template <typename T>
    AllComponents<const Tensor21<T>>   all(const Tensor21<T>& val);
    
    #if 0
    template <typename T>
    ElemComponents<Tensor21<T>>   elem(Tensor21<T>& val);

    template <typename T>
    ElemComponents<const Tensor21<T>>   elem(const Tensor21<T>& val);
    #endif

    template <typename T>
    AnyComponents<Tensor21<T>>   any(Tensor21<T>& val);

    template <typename T>
    AnyComponents<const Tensor21<T>>   any(const Tensor21<T>& val);

    template <typename T>
    constexpr Tensor12<T>  transpose(const Tensor21<T>&v);

//  --------------------------------------------------------
//  GETTERS

    template <typename T>
    constexpr Vector2<T>  x_column(const Tensor21<T>&ten);

    template <typename T>
    constexpr Vector1<T>  x_row(const Tensor21<T>&ten);

    template <typename T>
    constexpr Vector1<T>  y_row(const Tensor21<T>&ten);


//  --------------------------------------------------------
//  --------------------------------------------------------

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Tensor21<product_t<T,U>>  operator*(T a, const Tensor21<U>& b);
    
}

YQ_TYPE_DECLARE(yq::Tensor21D)
YQ_TYPE_DECLARE(yq::Tensor21F)
YQ_TYPE_DECLARE(yq::Tensor21I)
YQ_TYPE_DECLARE(yq::Tensor21U)

