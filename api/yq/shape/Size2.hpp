////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_SIZE2_HPP 1

#include <yq/typedef/size2.hpp>

#include <yq/keywords.hpp>
#include <yq/meta/InfoBinder.hpp>
#include <yq/trait/has_is_finite.hpp>
#include <yq/trait/has_nan.hpp>
#include <yq/trait/has_one.hpp>
#include <yq/trait/has_zero.hpp>
#include <yq/trait/ieee754.hpp>
#include <yq/trait/integer.hpp>
#include <yq/trait/is_arithmetic.hpp>
#include <yq/trait/is_integral.hpp>
#include <yq/trait/product.hpp>
#include <yq/trait/quotient.hpp>
#include <yq/trait/self_divide.hpp>
#include <yq/trait/self_multiply.hpp>
#include <yq/trait/square.hpp>

namespace log4cpp { class CategoryStream; }

namespace yq {
    struct Stream;
    
    template <typename> struct AllComponents;
    template <typename> struct AnyComponents;
    template <typename> struct Rectangle2;
    template <typename> struct Vector2;

    /*! Size object to hold a simple x/y dimensions
    
        This implicitly defines a region of zero to X-/Y-.
    */
    template <typename T>
    struct Size2 {
        
        //! Capture our template argument
        using component_type    = T;
    
        //! X-size
        T   x;
        
        //! Y-size
        T   y;

        constexpr Size2() noexcept = default;
        constexpr Size2(T _x, T _y) noexcept : x(_x), y(_y) {}
        constexpr Size2(all_k, T v) noexcept : x(v), y(v) {}
        
        template <typename=void> requires has_nan_v<T>
        consteval Size2(nan_k) : Size2(ALL, nan_v<T>) {}
        consteval Size2(zero_k) : Size2(ALL, zero_v<T>) {}
        consteval Size2(one_k) : Size2(ALL, one_v<T>) {}
        
        explicit constexpr Size2(const Vector2<T>&) noexcept;
        
        #ifdef QSIZE_H
        template <typename=void> requires (std::is_same_v<T,int>)
        Size2(const QSize& Q) : Size2(Q.width(), Q.height()) {}
        
        template <typename=void> requires (std::is_floating_point_v<T>)
        explicit Size2(const QSize& Q) : Size2((T) Q.width(), (T) Q.height()){}
        #endif

        template <typename U>
        requires std::is_nothrow_convertible_v<T,U>
        explicit constexpr operator Size2<U>() const noexcept
        {
            return { (U) x, (U) y };
        }
        
        template <typename U>
        requires (std::is_convertible_v<T,U> && !std::is_nothrow_convertible_v<T,U>)
        explicit constexpr operator Size2<U>() const 
        {
            return { (U) x, (U) y };
        }

        #ifdef QSIZE_H
        template <typename=void> requires (std::is_same_v<T,int>)
        explicit operator QSize() const { return QSize(x,y); }
        
        template <typename=void> requires (std::is_floating_point_v<T>)
        explicit operator QSizeF() const { return QSizeF((qreal) x, (qreal) y); }
        #endif


        //! Defaulted comparsion operator
        constexpr bool    operator==(const Size2&) const noexcept = default;
        
        
        constexpr Size2 operator+() const noexcept;
        constexpr Size2 operator-() const noexcept;
        
        constexpr Rectangle2<T> operator+(const Rectangle2<T>&) const noexcept;
        constexpr Size2 operator+(const Size2&) const noexcept;
        Size2& operator+=(const Size2&) noexcept;
        constexpr Rectangle2<T> operator+(const Vector2<T>&) const noexcept;

        constexpr Rectangle2<T> operator-(const Rectangle2<T>&) const noexcept;

        constexpr Size2 operator-(const Size2&) const noexcept;
        Size2& operator-=(const Size2&) noexcept;
        
        constexpr Rectangle2<T> operator-(const Vector2<T>&) const noexcept;
        
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Size2<product_t<T,U>> operator*(U) const noexcept;
        
        template <typename U>
        requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
        Size2& operator*=(U) noexcept;
        
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Size2<quotient_t<T,U>> operator/(U) const noexcept;
        
        template <typename U>
        requires (is_arithmetic_v<U> && self_divide_v<T,U>)
        Size2& operator/=(U) noexcept;
      
        //! Returns the area
        constexpr square_t<T> area() const noexcept;

        //! An explicit cast when its "ambiguous"
        template <typename U>
        constexpr Size2<U>  cast() const
        {
            return { (U) x, (U) y };
        }

        //! Returns the most positive of the components
        constexpr T             cmax() const noexcept;

        //! Returns the most negative of the components
        constexpr T             cmin() const noexcept;

        //! Tests to see if the left fully encloses the right
        bool                contains(const Size2& b) const noexcept;

        //! Returns the product of all components
        constexpr square_t<T>   cproduct() const noexcept;

        //! Returns the sum of all components
        constexpr T             csum() const noexcept;

        //! Absolute value of each component
        constexpr Size2       eabs() const noexcept;

        //! Tests to see if the left fully encloses the right
        bool                eclipses(const Size2& b) const noexcept;

        //! Element by element division
        template <typename U>
        constexpr Size2<quotient_t<T,U>>  ediv(const Size2<U>&b) const noexcept;

        //! Maximum applied to each component
        constexpr Size2     emax(const Size2&b) const noexcept;
        
        constexpr Size2     emax(T) const noexcept;

        //! Minimum applied to each component
        constexpr Size2     emin(const Size2&b) const noexcept;

        constexpr Size2   emin(T) const noexcept;

        //! Element by element multiplication
        template <typename U>
        constexpr Size2<product_t<T,U>>   emul(const Size2<U>&b) const noexcept;
        
        
        //! Height (Y-dimension)
        constexpr T         height() const noexcept;

        //! Width (X-dimension)
        constexpr T         width() const noexcept;

        /*! \brief Shrinks to fit the given frame

            This shrinks a size to fit the given frame (no spillage), preserving aspect ratio.

            \param[in]  frame   Desired frame
        */
        Size2               shrink_to_fit(const Size2& frame) const;


            //  ===================================================================================================
            //  AllComponents Adapters
            //  ===================================================================================================

        /*! Adds a value to all the elements
        */
        constexpr Size2 all_add(T b) const noexcept;
        
        //! Decrement all elements
        Size2&    all_decrement(T b) noexcept;

        //! Increment all elements
        Size2&    all_increment(T b) noexcept;

        /*! \brief Subtracts value from all elements
        */
        constexpr Size2 all_subtract(T b) const noexcept;

        /*! Tests every element
            
            This applies the given test to every component, 
            returns TRUE if all tests are true.
            \note y component test may be skipped if the x-component test fails.
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool all_test(Pred pred) const noexcept;

        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if all tests are true.
            \note y component test may be skipped if the x-component test fails.
            \param[in] b The other vector
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool all_test(const Size2& b, Pred pred) const noexcept;

        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if all tests are true.
            \note y component test may be skipped if the x-component test fails.
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
            \note y component test may be skipped if the x-component test passes.
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool any_test(Pred pred) const noexcept;
        
        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if any test is true.
            \note y component test may be skipped if the x-component test passes.
            \param[in] b The other vector
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool any_test(const Size2& b, Pred pred) const noexcept;
        
        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if any test is true.
            \note y component test may be skipped if the x-component test passes.
            \param[in] b The other value
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool any_test(T b, Pred pred) const noexcept;

        static bool less_x( const Size2& a, const Size2& b) 
        {
            return a.x < b.x;
        }

        static bool less_y( const Size2& a, const Size2& b) 
        {
            return a.y < b.y;
        }

    };

    YQ_IEEE754_1(Size2)
    YQ_INTEGER_1(Size2)
    YQ_IS_INTEGER_1(Size2)
    
    YQ_NAN_1(Size2, Size2<T>(NAN))
    YQ_ZERO_1(Size2, Size2<T>(ZERO))

    YQ_IS_NAN_1(Size2, is_nan(v.x) || is_nan(v.y) )
    YQ_IS_FINITE_1(Size2, is_finite(v.x) && is_finite(v.y) )
    
    
    /*! \brief Computes the area of this size
    */
    template <typename T>
    constexpr auto    area(const Size2<T>& sz) noexcept;
    
    /*! \brief Shrinks a size to fit the frame
        
        This shrinks a size to fit the given frame (no spillage), preserving aspect ratio.
        
        \param[in]  dims    Size being shrunk
        \param[in]  frame   Desired frame
    */
    template <typename T>
    Size2<T>  shrink_to_fit_within(const Size2<T>& dims, const Size2<T>& frame);
    
    /*! \brief Streams the size to a stream-like object */
    template <typename S, typename T>
    S&  as_stream(S& s, const Size2<T>& v);
    
    /*! \brief Streams to a stream
    */
    template <typename T>
    Stream& operator<<(Stream&s, const Size2<T>& v);

    /*! \brief Streams to to a logging stream
    */
    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const Size2<T>& v);

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Size2<product_t<T,U>> operator*(T a, const Size2<U>& b) noexcept;

    template <typename T>
    AllComponents<Size2<T>>   all(Size2<T>& val);

    template <typename T>
    AllComponents<const Size2<T>>   all(const Size2<T>& val);
    
    #if 0
    template <typename T>
    ElemComponents<Size2<T>>   elem(Size2<T>& val);

    template <typename T>
    ElemComponents<const Size2<T>>   elem(const Size2<T>& val);
    #endif

    template <typename T>
    AnyComponents<Size2<T>>   any(Size2<T>& val);

    template <typename T>
    AnyComponents<const Size2<T>>   any(const Size2<T>& val);
    
    Size2I  iround(const Size2D&);
}

YQ_TYPE_DECLARE(yq::Size2D)
YQ_TYPE_DECLARE(yq::Size2F)
YQ_TYPE_DECLARE(yq::Size2I)
YQ_TYPE_DECLARE(yq::Size2U)
