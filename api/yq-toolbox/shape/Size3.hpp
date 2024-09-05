////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_SIZE3_HPP 1

#include <yq-toolbox/typedef/size3.hpp>

#include <yq-toolbox/keywords.hpp>
#include <yq-toolbox/meta/InfoBinder.hpp>
#include <yq-toolbox/trait/cube.hpp>
#include <yq-toolbox/trait/has_is_finite.hpp>
#include <yq-toolbox/trait/has_nan.hpp>
#include <yq-toolbox/trait/has_one.hpp>
#include <yq-toolbox/trait/has_zero.hpp>
#include <yq-toolbox/trait/ieee754.hpp>
#include <yq-toolbox/trait/integer.hpp>
#include <yq-toolbox/trait/is_arithmetic.hpp>
#include <yq-toolbox/trait/is_integral.hpp>
#include <yq-toolbox/trait/product.hpp>
#include <yq-toolbox/trait/quotient.hpp>
#include <yq-toolbox/trait/self_divide.hpp>
#include <yq-toolbox/trait/self_multiply.hpp>

namespace log4cpp { class CategoryStream; }

namespace yq {
    struct Stream;

    template <typename> struct AllComponents;
    template <typename> struct AnyComponents;
    template <typename> struct Size2;
    template <typename> struct Vector3;

    /*! Size object
    */
    template <typename T>
    struct Size3 {

        //! Capture our template argument
        using component_type    = T;

        //! X-size
        T   x;
        
        //! Y-size
        T   y;
        
        //! Z-size
        T   z;
        
        constexpr Size3() noexcept = default;
        constexpr Size3(T _x, T _y, T _z) noexcept : x(_x), y(_y), z(_z) {}
        constexpr Size3(all_t, T v) noexcept : x(v), y(v), z(v) {}
        consteval Size3(one_t) : Size3(ALL, one_v<T>) {}
        
        template <typename=void> requires has_nan_v<T>
        consteval Size3(nan_t) : Size3(ALL, nan_v<T>) {}
        consteval Size3(zero_t) : Size3(ALL, zero_v<T>) {}

        explicit constexpr Size3(const Vector3<T>&) noexcept;

        template <typename U>
        requires std::is_nothrow_convertible_v<T,U>
        explicit constexpr operator Size3<U>() const noexcept
        {
            return { (U) x, (U) y, (U) z };
        }
        
        template <typename U>
        requires (std::is_convertible_v<T,U> && !std::is_nothrow_convertible_v<T,U>)
        explicit constexpr operator Size3<U>() const 
        {
            return { (U) x, (U) y, (U) z };
        }

        //! Defaulted comparison operator
        constexpr bool    operator==(const Size3&) const noexcept = default;
        
        
        constexpr Size3 operator+() const noexcept;
        constexpr Size3 operator-() const noexcept;
        
        constexpr Size3 operator+(const Size3&) const noexcept;
        Size3& operator+=(const Size3&) noexcept;

        constexpr Size3 operator-(const Size3&) const noexcept;
        Size3& operator-=(const Size3&) noexcept;
        
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Size3<product_t<T,U>> operator*(U) const noexcept;
        
        template <typename U>
        requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
        Size3& operator*=(U) noexcept;
        
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Size3<quotient_t<T,U>> operator/(U) const noexcept;
        
        template <typename U>
        requires (is_arithmetic_v<U> && self_divide_v<T,U>)
        Size3& operator/=(U) noexcept;
                

        //! Returns the most positive of the components
        constexpr T             cmax() const noexcept;

        //! Returns the most negative of the components
        constexpr T             cmin() const noexcept;

        //! Detects if this object eclipses the other
        constexpr bool   contains(const Size3<T>& small) const noexcept;

        //! Returns the product of all components
        constexpr cube_t<T>    cproduct() const noexcept;

        //! Returns the sum of all components
        constexpr T             csum() const noexcept;

        //! Depth (Z-dimension)
        constexpr T   depth() const;

        //! Absolute value of each component
        constexpr Size3       eabs() const noexcept;

        //! Detects if this object eclipses the other
        constexpr bool   eclipses(const Size3<T>& small) const noexcept;

        //! Element by element division
        template <typename U>
        constexpr Size3<quotient_t<T,U>>  ediv(const Size3<U>&b) const noexcept;

        //! Maximum applied to each component
        constexpr Size3   emax(const Size3&b) const noexcept;
        
        //! Minimum applied to each component
        constexpr Size3   emin(const Size3&b) const noexcept;

        //! Element by element multiplication
        template <typename U>
        constexpr Size3<product_t<T,U>>   emul(const Size3<U>&b) const noexcept;
        

        //! Height (Y-dimension)
        constexpr T   height() const;

        //! Volume of this size
        constexpr cube_t<T> volume() const noexcept;

        //! Width (X-dimension)
        constexpr T   width() const;
        
        //! Swizzles the x/y components to a Size2
        constexpr Size2<T>  xy() const noexcept;


            //  ===================================================================================================
            //  AllComponents Adapters
            //  ===================================================================================================

        /*! Adds a value to all the elements
        */
        constexpr Size3 all_add(T b) const noexcept;
        
        //! Decrement all elements
        Size3&    all_decrement(T b) noexcept;

        //! Increment all elements
        Size3&    all_increment(T b) noexcept;

        /*! \brief Subtracts value from all elements
        */
        constexpr Size3 all_subtract(T b) const noexcept;

        /*! Tests every element
            
            This applies the given test to every component, 
            returns TRUE if all tests are true.
            \note y, z component tests may be skipped if the x-component test fails.
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool all_test(Pred pred) const noexcept;

        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if all tests are true.
            \note y, z component tests may be skipped if the x-component test fails.
            \param[in] b The other vector
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool all_test(const Size3& b, Pred pred) const noexcept;

        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if all tests are true.
            \note y, z component tests may be skipped if the x-component test fails.
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
            \note y, z component tests may be skipped if the x-component test passes.
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool any_test(Pred pred) const noexcept;
        
        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if any test is true.
            \note y, z component tests may be skipped if the x-component test passes.
            \param[in] b The other vector
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool any_test(const Size3& b, Pred pred) const noexcept;
        
        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if any test is true.
            \note y, z component tests may be skipped if the x-component test passes.
            \param[in] b The other value
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool any_test(T b, Pred pred) const noexcept;

        static bool less_x( const Size3& a, const Size3& b) 
        {
            return a.x < b.x;
        }

        static bool less_y( const Size3& a, const Size3& b) 
        {
            return a.y < b.y;
        }

        static bool less_z( const Size3& a, const Size3& b) 
        {
            return a.z < b.z;
        }

    };

    YQ_IEEE754_1(Size3)
    YQ_INTEGER_1(Size3)
    YQ_IS_INTEGER_1(Size3)

    YQ_NAN_1(Size3, Size3<T>(NAN))
    YQ_ZERO_1(Size3, Size3<T>(ZERO))
    
    YQ_IS_NAN_1(Size3, is_nan(v.x) || is_nan(v.y) || is_nan(v.z))
    YQ_IS_FINITE_1(Size3, is_finite(v.x) && is_finite(v.y) && is_finite(v.z) )
    
    //! Computes volume of the size
    template <typename T>
    constexpr cube_t<T>    volume(const Size3<T>& size) noexcept;

    template <typename S, typename T>
    S&  as_stream(S& s, const Size3<T>& v);
    
    template <typename T>
    Stream& operator<<(Stream&s, const Size3<T>& v);

    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const Size3<T>& v);

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Size3<product_t<T,U>> operator*(T a, const Size3<U>& b) noexcept;

    template <typename T>
    AllComponents<Size3<T>>   all(Size3<T>& val);
    
    template <typename T>
    AllComponents<const Size3<T>>   all(const Size3<T>& val);
    
    #if 0
    template <typename T>
    ElemComponents<Size3<T>>   elem(Size3<T>& val);

    template <typename T>
    ElemComponents<const Size3<T>>   elem(const Size3<T>& val);
    #endif

    template <typename T>
    AnyComponents<Size3<T>>   any(Size3<T>& val);

    template <typename T>
    AnyComponents<const Size3<T>>   any(const Size3<T>& val);
}

YQ_TYPE_DECLARE(yq::Size3D)
YQ_TYPE_DECLARE(yq::Size3F)
YQ_TYPE_DECLARE(yq::Size3I)
YQ_TYPE_DECLARE(yq::Size3U)
