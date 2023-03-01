////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_SIZE1_HPP 1

#include <math/preamble.hpp>

namespace yq {

    /*! Size object to hold a simple x/y dimensions
    
        This implicitly defines a region of zero to X-/Y-.
    */
    template <typename T>
    struct Size1 {
        
        //! Capture our template argument
        using component_type    = T;
    
        //! X-size
        T   x;
        
        constexpr Size1() noexcept = default;
        constexpr Size1(T _x) noexcept : x(_x) {}
        constexpr Size1(all_t, T v) noexcept : x(v) {}
        
        template <typename=void> requires has_nan_v<T>
        consteval Size1(nan_t) : Size1(ALL, nan_v<T>) {}
        consteval Size1(zero_t) : Size1(ALL, zero_v<T>) {}
        
        explicit constexpr Size1(const Vector1<T>&) noexcept;
        
        
        //! Defaulted comparsion operator
        constexpr bool    operator==(const Size1&) const noexcept = default;
        
        template <typename U>
        requires std::is_nothrow_convertible_v<T,U>
        explicit constexpr operator Size1<U>() const noexcept
        {
            return { (U) x };
        }
        
        template <typename U>
        requires (std::is_convertible_v<T,U> && !std::is_nothrow_convertible_v<T,U>)
        explicit constexpr operator Size1<U>() const 
        {
            return { (U) x };
        }

        
        constexpr Size1 operator+() const noexcept;
        constexpr Size1 operator-() const noexcept;
        
        constexpr Size1 operator+(const Size1&) const noexcept;
        Size1& operator+=(const Size1&) noexcept;

        constexpr Size1 operator-(const Size1&) const noexcept;
        Size1& operator-=(const Size1&) noexcept;
        
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Size1<product_t<T,U>> operator*(U) const noexcept;
        
        template <typename U>
        requires (is_arithmetic_v<U> && self_mul_v<T,U>)
        Size1& operator*=(U) noexcept;
        
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Size1<quotient_t<T,U>> operator/(U) const noexcept;
        
        template <typename U>
        requires (is_arithmetic_v<U> && self_div_v<T,U>)
        Size1& operator/=(U) noexcept;
      

        //! Returns the most positive of the components
        constexpr T             cmax() const noexcept;

        //! Returns the most negative of the components
        constexpr T             cmin() const noexcept;

        //! Tests to see if the left fully encloses the right
        constexpr bool          contains(const Size1& b) const noexcept;

        //! Returns the product of all components
        constexpr T             cproduct() const noexcept;

        //! Returns the sum of all components
        constexpr T             csum() const noexcept;

        //! Absolute value of each component
        constexpr Size1         eabs() const noexcept;

        //! Tests to see if the left fully encloses the right
        constexpr bool          eclipses(const Size1& b) const noexcept;

        //! Element by element division
        template <typename U>
        constexpr Size1<quotient_t<T,U>>  ediv(const Size1<U>&b) const noexcept;

        //! Maximum applied to each component
        constexpr Size1   emax(const Size1&b) const noexcept;
        
        //! Minimum applied to each component
        constexpr Size1   emin(const Size1&b) const noexcept;

        //! Element by element multiplication
        template <typename U>
        constexpr Size1<product_t<T,U>>   emul(const Size1<U>&b) const noexcept;
        
        
        
        constexpr T         length() const noexcept;

        //! Width (X-dimension)
        constexpr T         width() const;


            //  ===================================================================================================
            //  AllComponents Adapters
            //  ===================================================================================================

        /*! Adds a value to all the elements
        */
        constexpr Size1 all_add(T b) const noexcept;
        
        //! Decrement all elements
        Size1&    all_decrement(T b) noexcept;

        //! Increment all elements
        Size1&    all_increment(T b) noexcept;

        /*! \brief Subtracts value from all elements
        */
        constexpr Size1 all_subtract(T b) const noexcept;

        /*! Tests every element
            
            This applies the given test to every component, 
            returns TRUE if all tests are true.
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool all_test(Pred pred) const noexcept;

        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if all tests are true.
            \param[in] b The other vector
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool all_test(const Size1& b, Pred pred) const noexcept;

        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if all tests are true.
            \param[in] b The other value
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool all_test(T b, Pred pred) const noexcept;

            //  ===================================================================================================
            //  AnyComponents Adapters
            //  
            //  The following all_test() are for the AllComponents Adapters, to apply the test on ALL components,
            //  returning true if all elements are successful
            //  ===================================================================================================
        
        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if any test is true.
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool any_test(Pred pred) const noexcept;
        
        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if any test is true.
            \param[in] b The other vector
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool any_test(const Size1& b, Pred pred) const noexcept;
        
        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if any test is true.
            \param[in] b The other value
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool any_test(T b, Pred pred) const noexcept;

        static bool less_x( const Size1& a, const Size1& b) 
        {
            return a.x < b.x;
        }
    };

    YQ_IEEE754_1(Size1)
    YQ_INTEGER_1(Size1)
    YQ_IS_INTEGER_1(Size1)

    YQ_NAN_1(Size1, Size1<T>(NAN))
    YQ_ZERO_1(Size1, Size1<T>(ZERO))
    
    YQ_IS_NAN_1(Size1, is_nan(v.x) )
    YQ_IS_FINITE_1(Size1, is_finite(v.x) )

    
    /*! \brief Streams the size to a stream-like object */
    template <typename S, typename T>
    S&  as_stream(S& s, const Size1<T>& v);
    
    /*! \brief Streams to a stream
    */
    template <typename T>
    Stream& operator<<(Stream&s, const Size1<T>& v);

    /*! \brief Streams to to a logging stream
    */
    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const Size1<T>& v);

    template <typename T, typename U>
    requires is_arithmetic_v<T,U>
    constexpr Size2<product_t<T,U>> operator*(T a, const Size2<U>& b) noexcept;

    template <typename T>
    constexpr T       length(const Size1<T>&) noexcept;


    template <typename T>
    AllComponents<Size1<T>>   all(const Size1<T>& val);
    
    template <typename T>
    AllComponents<const Size1<T>>   all(const Size1<T>& val);

    #if 0
    template <typename T>
    ElemComponents<Size1<T>>   elem(Size1<T>& val);

    template <typename T>
    ElemComponents<const Size1<T>>   elem(const Size1<T>& val);
    #endif

    template <typename T>
    AnyComponents<Size1<T>>   any(Size1<T>& val);

    template <typename T>
    AnyComponents<const Size1<T>>   any(const Size1<T>& val);
}

YQ_TYPE_DECLARE(yq::Size1D)
YQ_TYPE_DECLARE(yq::Size1F)
YQ_TYPE_DECLARE(yq::Size1I)
YQ_TYPE_DECLARE(yq::Size1U)
