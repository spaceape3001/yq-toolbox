////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_RANGE_HPP 1

#include <yq-toolbox/keywords.hpp>
#include <yq-toolbox/meta/InfoBinder.hpp>
#include <yq/trait/has_is_finite.hpp>
#include <yq/trait/has_nan.hpp>
#include <yq/trait/has_zero.hpp>
#include <yq/trait/ieee754.hpp>
#include <yq/trait/integer.hpp>
#include <yq/trait/is_arithmetic.hpp>
#include <yq/trait/is_floating_point.hpp>
#include <yq/trait/is_integral.hpp>
#include <yq/trait/product.hpp>
#include <yq/trait/quotient.hpp>
#include <yq/trait/self_divide.hpp>
#include <yq/trait/self_multiply.hpp>
#include <yq/typedef/range.hpp>

#include <initializer_list>
#include <span>

namespace yq {
    struct Side;


    /*! \brief A "Ranged" object with a low and a high value
    
        \note A valid range requires that lo <= hi, however, assertions
        are up to the client code to enforce this.
        
        \note ALL OPERATIONS assume the range to already be valid to minimize the 
            number of min/max comparisons.
    */
    template <typename T>
    struct Range {
    
        //! Component Type
        using component_type    = T;
        
        //! Low value
        T   lo;
        
        //! High value
        T   hi;
        
        //! Default constructor
        constexpr Range() noexcept = default;
        
        //! Initializing both low & high from one  value
        explicit constexpr Range(T v) : lo(v), hi(v) {}
        
        //! Initializing constructor by component
        constexpr Range(T _lo, T _hi) noexcept : lo(_lo), hi(_hi) {}
        
        //! Initialize all components to same value
        constexpr Range(all_t, T v) noexcept : lo(v), hi(v) {}
        
        //! Initialize with nan
        consteval Range(nan_t) noexcept : Range(ALL, nan_v<T>) {}
        
        //! Initialize with zero
        consteval Range(zero_t) noexcept : Range(ALL, zero_v<T>) {}
        
        //! Construct by intersection of two value lists
        constexpr Range(intersect_t, std::initializer_list<T>, std::initializer_list<T>);

        //! Construct by intersection of two value lists
        constexpr Range(intersect_t, std::span<const T>, std::span<const T>);
        
        //! Construct by sorting the two arguments
        constexpr Range(sort_t, T, T) noexcept;
        
        //! Construct by the union of the two arguments
        constexpr Range(union_t, T, T) noexcept;
        
        //! Construct by the union of the listed values
        constexpr Range(union_t, std::initializer_list<T>vs);

        //! Construct by the union of the listed values
        constexpr Range(union_t, std::span<const T>vs);

        //! Construct by the union of the listed values for lo & high
        constexpr Range(union_t, std::initializer_list<T>ls, std::initializer_list<T>hs);

        //! Construct by the union of the listed values for lo & high
        constexpr Range(union_t, std::span<const T>ls, std::span<const T>hs);
        
        //! Default comparison object
        constexpr bool      operator==(const Range&) const noexcept = default;
        
        //! Affirmation operator
        constexpr Range<T>  operator+() const noexcept;

        //! Negation operator
        constexpr Range<T>  operator-() const noexcept;
        
        //! Adds value to range
        constexpr Range<T>  operator+(T) const noexcept;
        
        //! Increments range by value
        Range<T>&           operator+=(T) noexcept;

        //! Adds two ranges together
        constexpr Range<T>  operator+(const Range<T>& b) const noexcept;
        
        //! Increments the left range with the right
        Range<T>&           operator+=(const Range<T>& b) noexcept;

        //! Subtracts a value from a range
        constexpr Range<T>  operator-(T) const noexcept;
        
        //! Self-subtraction operator (range & value)
        Range<T>&           operator-=(T) noexcept;

        //! Subtracts two ranges
        constexpr Range<T>  operator-(const Range<T>& b) const noexcept;
        
        //! Self-subtraction operator (range & range)
        Range<T>&           operator-=(const Range<T>& b) noexcept;

        //! Multiplies range with value
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Range<product_t<T,U>>    operator*(U b) const noexcept;

        //! Self-multiplication with value
        template <typename U>
        requires (is_arithmetic_v<U> && self_multiply_v<T,U>) 
        Range<T>&           operator*=(U b) noexcept;

        //! Multiples range with range
        template <typename U>
        constexpr Range<product_t<T,U>>   operator*(const Range<U>&b) const noexcept;
        
        //! Self-multiplication with range
        template <typename U>
        requires self_multiply_v<T,U>
        Range<T>&    operator*=(const Range<U>& b) noexcept;

        //! Division of range with value
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Range<quotient_t<T,U>>    operator/(U b) const noexcept;

        //! Self-Division of range with value
        template <typename U>
        requires (std::is_arithmetic_v<U> && self_divide_v<T,U>) 
        Range<T>&    operator/=(U b) noexcept;

        //! Divdes one range by another
        template <typename U>
        constexpr Range<quotient_t<T,U>>   operator/(const Range<U>&b) const noexcept;

        //! Self-division of one range with another
        template <typename U>
        requires self_divide_v<T,U>
        Range<T>&    operator/=(const Range<U>& b) noexcept;

        //! Unions range with value
        constexpr Range<T>  operator|(T) const noexcept;
        
        //! Unions into this range with value
        Range<T>&           operator|=(T) noexcept;

        //! Unions two ranges (both assumed to be valid)
        constexpr Range<T>  operator|(const Range<T>& b) const noexcept;
        
        //! Self-unions right range into left (both assumed to be valid)
        Range<T>&           operator|=(const Range<T>& b) noexcept;

        //! Intersects of two ranges (both assumed to be valid)
        constexpr Range<T>  operator&(const Range<T>& b) const noexcept;
        
        //! Self-intersects right range into left (both assumed to be valid)
        Range<T>&           operator&=(const Range<T>& b) noexcept;

        //  see if the for() syntax will work?
        
        //! low value (for-loops)
        constexpr T         begin() const noexcept { return lo; }
        
        /*! \brief Computes the center of this range */
        constexpr Range<T>  center() const noexcept;

        //! Classify this value in the range
        constexpr Side     classify(T) const noexcept;
        
        //! Checks if value is within range
        constexpr bool        eclipses(T b) const noexcept;
    
        //! Checks if provided range is entirely within this range
        constexpr bool        eclipses(const Range& b) const noexcept;

        //! high value (for-loops)
        constexpr T       end() const noexcept { return hi; }
        
        //! Returns a fixed range (if feasible)
        constexpr Range     fixed() const noexcept;
        
        //! Inflates range by given amount
        constexpr Range     inflate(T) const noexcept;
        
        //! Checks for validity
        constexpr bool    is_valid() const noexcept;

        /*! \brief Projects a local [0,1] coordinate to a global coordinate
            \param[in] v    The local coordinate
            \return The global coordinate
        */
        template <typename=void>
        requires is_floating_point_v<T>
        constexpr T   project(T v) const noexcept;

        //! Computes the span of the range
        constexpr T     span() const noexcept;

        /*! \brief Projects a global coordinate to a local [0,1] coordinate
            \param[in] v    The global coordinate
            \return The local coordinate
        */
        template <typename=void>
        requires is_floating_point_v<T>
        constexpr T   unproject(T v) const noexcept;
        
        //! Tests for validity (same as is_valid() )
        constexpr bool    valid() const noexcept;

    };

    YQ_IEEE754_1(Range)
    YQ_INTEGER_1(Range)
    YQ_IS_INTEGER_1(Range)
    
//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Constructs a range 
    
        This routine enforces lo <= hi by using the min/max functions
    */
    template <typename T>
    constexpr Range<T> range(T a, T b) noexcept
    {
        return Range<T>(SORT, a, b);
    }
    
    /*! \brief Constructs a range
    
        This routine returns a range made from the given elements.
    */
    template <typename T>
    constexpr Range<T> range(std::initializer_list<T> them) noexcept
    {
        return Range<T>(UNION, them);
    }

    YQ_NAN_1(Range, Range<T>(NAN))
    YQ_ZERO_1(Range, Range<T>(ZERO))

//  --------------------------------------------------------
//  --------------------------------------------------------

    YQ_IS_NAN_1(Range, is_nan(v.lo) || is_nan(v.hi))
    YQ_IS_FINITE_1(Range, is_finite(v.lo) && is_finite(v.hi))

    //! Classify this value in the range
    template <typename T>
    constexpr Side     _classify(T, T lo, T hi) noexcept;

    //! Computes the delta in the gap b
    template <typename T>
    constexpr T         _gap(T v, T lo, T hi) noexcept;

    //! Checks to see if the given range is valid (lo <= hi)
    template <typename T>
    constexpr bool    is_valid(const Range<T>& a) noexcept
    {
        return a.is_valid();
    }

    //! Addition (assumes b is valid)
    template <typename T>
    constexpr Range<T>  operator+(T a, const Range<T>& b) noexcept;
    

    //! Subtraction (assumes b to be valid)
    template <typename T>
    constexpr Range<T>  operator-(T a, const Range<T>& b) noexcept;

    //! Multiplication (assumes b to be valid)
    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Range<product_t<T,U>>    operator*(T a, const Range<U>& b) noexcept;

    //! Division (assumes b to be valid)
    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Range<product_t<T,U>>    operator/(T a, const Range<U>& b) noexcept;

    //! Union (assumes b to be valid)
    template <typename T>
    constexpr Range<T>    operator|(T a, const Range<T>& b) noexcept;

    //! Center of range
    template <typename T>
    constexpr Range<T>    center(const Range<T>& a) noexcept;
    
    //! Span of range
    template <typename T>
    constexpr T           span(const Range<T>& a) noexcept;
}

YQ_TYPE_DECLARE(yq::RangeD)
YQ_TYPE_DECLARE(yq::RangeF)
YQ_TYPE_DECLARE(yq::RangeI)
YQ_TYPE_DECLARE(yq::RangeU)


