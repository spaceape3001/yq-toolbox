////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_TENSOR_1_3_HPP 1

#include <yq/typedef/tensor13.hpp>

#include <yq/keywords.hpp>
#include <yq/trait/has_identity.hpp>
#include <yq/trait/product.hpp>
#include <yq/trait/quotient.hpp>
#include <yq/trait/self_divide.hpp>
#include <yq/trait/self_multiply.hpp>
#include <yq/vector/Vector1.hpp>
#include <yq/vector/Vector3.hpp>

namespace log4cpp { class CategoryStream; }

namespace yq {
    /*! \brief 1x3 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor13 {
    
        //! Component type (captures the template parameter)
        using component_type = T;
        static constexpr const unsigned rows_count  = 1;
        static constexpr const unsigned cols_count  = 3;

        T xx, xy, xz;
        
        constexpr Tensor13() noexcept = default;

        constexpr Tensor13(
            T _xx, T _xy, T _xz
        ) : 
            xx(_xx), xy(_xy), xz(_xz)
        {
        }
        
        consteval Tensor13(all_k, T v) : 
            xx(v), xy(v), xz(v)
        {
        }

        constexpr Tensor13(columns_t, const Vector1<T>& x, const Vector1<T>& y, const Vector1<T>& z) noexcept :
            xx(x.x), xy(y.x), xz(z.x)
        {
        }


        consteval Tensor13(identity_t) : 
            xx(one_v<T>),  xy(zero_v<T>), xz(zero_v<T>)
        {
        }

        template <typename=void> requires has_nan_v<T>
        consteval Tensor13(nan_t) : Tensor13(ALL, nan_v<T>) {}

        constexpr Tensor13(rows_t, const Vector3<T>& x) :
            xx(x.x), xy(x.y), xz(x.z)
        {
        }

        consteval Tensor13(zero_k) : Tensor13(ALL, zero_v<T>) {}
        
        #ifdef YQ_USE_GLM
        template <glm::qualifier Q>
        explicit constexpr Tensor13(const glm::mat<1,3,T,Q>& t) noexcept;
        #endif
        
        //! Defaulted equality operator
        constexpr bool operator==(const Tensor13&) const noexcept = default;

        #ifdef YQ_USE_GLM
        constexpr operator glm::mat<1,3,T,glm::defaultp>() const noexcept;
        #endif

        //! Positive (affirmation) operator
        constexpr Tensor13  operator+() const noexcept;

        //! Negation operator
        constexpr Tensor13  operator-() const noexcept;

        constexpr Tensor13  operator+ (const Tensor13 &b) const noexcept;
        Tensor13&           operator+=(const Tensor13 &b) noexcept;
        constexpr Tensor13  operator- (const Tensor13 &b) const noexcept;
        Tensor13&           operator-=(const Tensor13 &b) noexcept;
        
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Tensor13<product_t<T,U>>  operator*(U b) const noexcept;

        template <typename U>
        requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
        Tensor13&  operator*=(U b) noexcept;

        template <typename U>
        constexpr Segment1<product_t<T,U>>  operator*(const Segment3<U>&) const noexcept;

        template <typename U>
        constexpr Tensor11<product_t<T,U>> operator*(const Tensor31<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor12<product_t<T,U>> operator*(const Tensor32<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor13<product_t<T,U>> operator*(const Tensor33<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor14<product_t<T,U>> operator*(const Tensor34<U>& b) const noexcept;

        template <typename U>
        requires self_multiply_v<T,U>
        Tensor13& operator*=(const Tensor33<U>& b) noexcept;

        template <typename U>
        constexpr Vector1<product_t<T,U>> operator*(const Vector3<U>&b) const noexcept;

        template <typename U>
        std::vector<Vector1<product_t<T,U>>>    operator*(std::span<const Vector3<U>> b) const;

        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Tensor13<quotient_t<T,U>>  operator/(U b) const noexcept;

        template <typename U>
        requires (is_arithmetic_v<U> && self_divide_v<T,U>)
        Tensor13&  operator/=(U b) noexcept;

        constexpr Tensor31<T> transpose() const noexcept;

        //  --------------------------------------------------------
        //  GETTERS

            constexpr Vector1<T>  x_column() const noexcept;

            constexpr Vector1<T>  y_column() const noexcept;

            constexpr Vector1<T>  z_column() const noexcept;

            constexpr Vector3<T>  x_row() const noexcept;



        //  --------------------------------------------------------
        //  SETTERS

            Tensor13& x_column(const Vector1<T>& v);

            Tensor13& x_column(T _xx);

            Tensor13& y_column(const Vector1<T>& v);

            Tensor13& y_column(T _xy);

            Tensor13& z_column(const Vector1<T>& v);


            Tensor13& z_column(T _xz);

            Tensor13& x_row(const Vector3<T>& v);

            Tensor13& x_row(T _xx, T _xy, T _xz);


        //  --------------------------------------------------------
        //  AllComponents Adapters

            /*! Adds a value to all the elements
            */
            constexpr Tensor13 all_add(T b) const noexcept;
            
            //! Decrements all elements
            Tensor13&   all_decrement(T) noexcept;

            //! Increments all elements
            Tensor13&   all_increment(T) noexcept;

            /*! \brief Subtracts value from all elements
            */
            constexpr Tensor13 all_subtract(T b) const noexcept;
            

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
            constexpr bool all_kest(const Tensor13& b, Pred pred) const noexcept;

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
            constexpr bool any_test(Pred pred) const noexcept;
            
            /*! Tests every element
                This applies the given test to every component, 
                returns TRUE if any test is true.
                \note y, z, w component tests may be skipped if the x-component test passes.
                \param[in] b The other vector
                \param[in] pred The predicate (your test)
            */
            template <typename Pred>
            constexpr bool any_test(const Tensor13& b, Pred pred) const noexcept;
            
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

            static bool less_xx( const Tensor13& a, const Tensor13& b) { return a.xx < b.xx; }
            static bool less_xy( const Tensor13& a, const Tensor13& b) { return a.xy < b.xy; }
            static bool less_xz( const Tensor13& a, const Tensor13& b) { return a.xz < b.xz; }

    };

    YQ_IEEE754_1(Tensor13)
        
//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Create 1x3 tensor by columns
    */
    template <typename T>
    constexpr Tensor13<T>  columns(const Vector1<T>&x, const Vector1<T>&y, const Vector1<T>&z)
    {
        return Tensor13<T>(COLUMNS, x, y, z);
    }

    /*! \brief Create 1x3 tensor by rows
    */
    template <typename T>
    constexpr Tensor13<T>  rows(const Vector3<T>&x)
    {
        return Tensor13<T>(ROWS, x );
    }
    
    YQ_IDENTITY_1(Tensor13, Tensor13<T>(IDENTITY))
    YQ_NAN_1(Tensor13, Tensor13<T>(NAN))
    YQ_ZERO_1(Tensor13, Tensor13<T>(ZERO))
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor13, 
        is_finite(v.xx) && is_finite(v.xy) && is_finite(v.xz)
    )
    
    YQ_IS_NAN_1(Tensor13,  
        is_nan(v.xx) || is_nan(v.xy) || is_nan(v.xz)
    )


    //! All components adapter
    //! Use this to activate the "all" component adapters in tensor13
    template <typename T>
    AllComponents<Tensor13<T>>   all(Tensor13<T>& val);

    //! All components adapter
    //! Use this to activate the "all" component adapters in tensor13
    template <typename T>
    AllComponents<const Tensor13<T>>   all(const Tensor13<T>& val);
    
    #if 0
    template <typename T>
    ElemComponents<Tensor13<T>>   elem(Tensor13<T>& val);

    template <typename T>
    ElemComponents<const Tensor13<T>>   elem(const Tensor13<T>& val);
    #endif

    template <typename T>
    AnyComponents<Tensor13<T>>   any(Tensor13<T>& val);

    template <typename T>
    AnyComponents<const Tensor13<T>>   any(const Tensor13<T>& val);
    
    template <typename T>
    constexpr Tensor31<T>  transpose(const Tensor13<T>&v);

//  --------------------------------------------------------
//  GETTERS

    template <typename T>
    constexpr Vector1<T>  x_column(const Tensor13<T>&ten);

    template <typename T>
    constexpr Vector1<T>  y_column(const Tensor13<T>&ten);

    template <typename T>
    constexpr Vector1<T>  z_column(const Tensor13<T>&ten);

    template <typename T>
    constexpr Vector3<T>  x_row(const Tensor13<T>&ten);


//  --------------------------------------------------------
//  --------------------------------------------------------

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Tensor13<product_t<T,U>>  operator*(T a, const Tensor13<U>& b);
    
    
}

YQ_TYPE_DECLARE(yq::Tensor13D)
YQ_TYPE_DECLARE(yq::Tensor13F)
YQ_TYPE_DECLARE(yq::Tensor13I)
YQ_TYPE_DECLARE(yq::Tensor13U)

