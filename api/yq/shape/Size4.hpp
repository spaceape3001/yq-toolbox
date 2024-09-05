////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_SIZE4_HPP 1



#include <yq/keywords.hpp>
#include <yq/trait/fourth.hpp>
#include <yq/trait/product.hpp>
#include <yq/trait/quotient.hpp>
#include <yq/trait/self_divide.hpp>
#include <yq/trait/self_multiply.hpp>

namespace log4cpp { class CategoryStream; }

namespace yq {

    /*! Size object
    */
    template <typename T>
    struct Size4 {

        //! Capture our template argument
        using component_type    = T;

        //! X-size
        T   x;
        
        //! Y-size
        T   y;
        
        //! Z-size
        T   z;
        
        //! W-size
        T   w;

        constexpr Size4() noexcept = default;
        constexpr Size4(T _x, T _y, T _z, T _w) noexcept : x(_x), y(_y), z(_z), w(_w) {}
        constexpr Size4(all_t, T v) noexcept : x(v), y(v), z(v), w(v) {}
        consteval Size4(one_t) : Size4(ALL, one_v<T>) {}
        
        template <typename=void> requires has_nan_v<T>
        consteval Size4(nan_t) : Size4(ALL, nan_v<T>) {}
        consteval Size4(zero_t) : Size4(ALL, zero_v<T>) {}

        explicit constexpr Size4(const Vector4<T>&) noexcept;

        //! Defaulted comparison operator
        constexpr bool    operator==(const Size4&) const noexcept = default;
        
        /*! \brief Conversion to other types sizes
        */
        template <typename U>
        requires std::is_nothrow_convertible_v<T,U>
        explicit constexpr operator Size4<U>() const noexcept
        {
            return { (U) x, (U) y, (U) z, (U) w };
        }
        
        template <typename U>
        requires (std::is_convertible_v<T,U> && !std::is_nothrow_convertible_v<T,U>)
        explicit constexpr operator Size4<U>() const 
        {
            return { (U) x, (U) y, (U) z, (U) w };
        }
        
        constexpr Size4 operator+() const noexcept;
        constexpr Size4 operator-() const noexcept;
        
        constexpr Size4 operator+(const Size4&) const noexcept;
        Size4& operator+=(const Size4&) noexcept;

        constexpr Size4 operator-(const Size4&) const noexcept;
        Size4& operator-=(const Size4&) noexcept;
        
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Size4<product_t<T,U>> operator*(U) const noexcept;
        
        template <typename U>
        requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
        Size4& operator*=(U) noexcept;
        
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Size4<quotient_t<T,U>> operator/(U) const noexcept;
        
        template <typename U>
        requires (is_arithmetic_v<U> && self_divide_v<T,U>)
        Size4& operator/=(U) noexcept;


        //! Returns the most positive of the components
        constexpr T             cmax() const noexcept;

        //! Returns the most negative of the components
        constexpr T             cmin() const noexcept;

        //! Detects if this object eclipses the other
        constexpr bool   contains(const Size4<T>& small) const noexcept;

        //! Returns the product of all components
        constexpr fourth_t<T>   cproduct() const noexcept;

        //! Returns the sum of all components
        constexpr T             csum() const noexcept;

        //! Depth (Z-dimension)
        constexpr T   depth() const;
        
                //! Duration (W-dimension)
        constexpr T   duration() const;


        //! Absolute value of each component
        constexpr Size4       eabs() const noexcept;

        //! Detects if this object eclipses the other
        constexpr bool   eclipses(const Size4<T>& small) const noexcept;

        //! Element by element division
        template <typename U>
        constexpr Size4<quotient_t<T,U>>  ediv(const Size4<U>&b) const noexcept;

        //! Maximum applied to each component
        constexpr Size4   emax(const Size4&b) const noexcept;
        
        //! Minimum applied to each component
        constexpr Size4   emin(const Size4&b) const noexcept;

        //! Element by element multiplication
        template <typename U>
        constexpr Size4<product_t<T,U>>   emul(const Size4<U>&b) const noexcept;

        //! Height (Y-dimension)
        constexpr T   height() const;

        //! Volume of this size
        constexpr fourth_t<T> hypervolume() const noexcept;


        //! Width (X-dimension)
        constexpr T   width() const;


            //  ===================================================================================================
            //  AllComponents Adapters
            //  ===================================================================================================

        /*! Adds a value to all the elements
        */
        constexpr Size4 all_add(T b) const noexcept;
        
        //! Decrement all elements
        Size4&    all_decrement(T b) noexcept;

        //! Increment all elements
        Size4&    all_increment(T b) noexcept;

        /*! \brief Subtracts value from all elements
        */
        constexpr Size4 all_subtract(T b) const noexcept;

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
        constexpr bool all_test(const Size4& b, Pred pred) const noexcept;

        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if all tests are true.
            \note y, z, w component tests may be skipped if the x-component test fails.
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
        constexpr bool any_test(const Size4& b, Pred pred) const noexcept;
        
        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if any test is true.
            \note y, z, w component tests may be skipped if the x-component test passes.
            \param[in] b The other value
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool any_test(T b, Pred pred) const noexcept;

        static bool less_x( const Size4& a, const Size4& b) 
        {
            return a.x < b.x;
        }

        static bool less_y( const Size4& a, const Size4& b) 
        {
            return a.y < b.y;
        }

        static bool less_z( const Size4& a, const Size4& b) 
        {
            return a.z < b.z;
        }

        static bool less_w( const Size4& a, const Size4& b) 
        {
            return a.w < b.w;
        }

    };

    YQ_IEEE754_1(Size4)
    YQ_INTEGER_1(Size4)
    YQ_IS_INTEGER_1(Size4)

    YQ_NAN_1(Size4, Size4<T>(NAN))
    YQ_ZERO_1(Size4, Size4<T>(ZERO))
    YQ_IS_NAN_1(Size4, is_nan(v.x) || is_nan(v.y) || is_nan(v.z) || is_nan(v.w))
    YQ_IS_FINITE_1(Size4, is_finite(v.x) && is_finite(v.y) && is_finite(v.z)&& is_finite(v.w) )
    
    //! Computes volume of the size
    template <typename T>
    constexpr auto    hypervolume(const Size4<T>& size) noexcept;

    template <typename S, typename T>
    S&  as_stream(S& s, const Size4<T>& v);
    
    template <typename T>
    Stream& operator<<(Stream&s, const Size4<T>& v);

    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const Size4<T>& v);
    
    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Size4<product_t<T,U>> operator*(T a, const Size4<U>& b) noexcept;

    template <typename T>
    AllComponents<Size4<T>>     all(Size4<T>& val);
    
    template <typename T>
    AllComponents<const Size4<T>>   all(const Size4<T>& val);

    #if 0
    template <typename T>
    ElemComponents<Size4<T>>   elem(Size4<T>& val);

    template <typename T>
    ElemComponents<const Size4<T>>   elem(const Size4<T>& val);
    #endif

    template <typename T>
    AnyComponents<Size4<T>>   any(Size4<T>& val);

    template <typename T>
    AnyComponents<const Size4<T>>   any(const Size4<T>& val);
}

YQ_TYPE_DECLARE(yq::Size4D)
YQ_TYPE_DECLARE(yq::Size4F)
YQ_TYPE_DECLARE(yq::Size4I)
YQ_TYPE_DECLARE(yq::Size4U)
