////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>

namespace yq {

    /*! \brief A "Ranged" object with a low and a high value
    
        \note A valid range requires that lo <= hi, however, assertions
        are up to the client code to enforce this.
        
        \note ALL OPERATIONS assume the range to already be valid to minimize the 
            number of min/max comparisons.
    */
    template <typename T>
    struct Range {
        using component_type    = T;
        T   lo, hi;
        
        constexpr Range() noexcept = default;
        explicit constexpr Range(T v) : lo(v), hi(v) {}
        constexpr Range(T _lo, T _hi) noexcept : lo(_lo), hi(_hi) {}
        constexpr Range(all_t, T v) noexcept : lo(v), hi(v) {}
        consteval Range(nan_t) noexcept : Range(ALL, nan_v<T>) {}
        consteval Range(zero_t) noexcept : Range(ALL, zero_v<T>) {}
        
        constexpr Range(intersect_t, std::initializer_list<T>, std::initializer_list<T>);
        constexpr Range(intersect_t, std::span<const T>, std::span<const T>);
        constexpr Range(sort_t, T, T) noexcept;
        constexpr Range(union_t, T, T) noexcept;
        constexpr Range(union_t, std::initializer_list<T>);
        constexpr Range(union_t, std::span<const T>);
        constexpr Range(union_t, std::initializer_list<T>, std::initializer_list<T>);
        constexpr Range(union_t, std::span<const T>, std::span<const T>);
        
        //! Default comparison object
        constexpr bool      operator==(const Range&) const noexcept = default;
        
        constexpr Range<T>  operator+() const noexcept;

        constexpr Range<T>  operator-() const noexcept;
        
        constexpr Range<T>  operator+(T) const noexcept;
        Range<T>&           operator+=(T) noexcept;

        constexpr Range<T>  operator+(const Range<T>& b) const noexcept;
        Range<T>&           operator+=(const Range<T>& b) noexcept;

        constexpr Range<T>  operator-(T) const noexcept;
        Range<T>&           operator-=(T) noexcept;

        constexpr Range<T>  operator-(const Range<T>& b) const noexcept;
        Range<T>&           operator-=(const Range<T>& b) noexcept;

        template <typename U>
        requires trait::is_arithmetic_v<U>
        constexpr Range<trait::product_t<T,U>>    operator*(U b) noexcept;

        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>) 
        Range<T>&           operator*=(U b) noexcept;

        template <typename U>
        constexpr Range<trait::product_t<T,U>>   operator*(const Range<U>&b) const noexcept;
        
        template <typename U>
        requires trait::self_mul_v<T,U>
        Range<T>&    operator*=(const Range<U>& b) noexcept;

        template <typename U>
        requires trait::is_arithmetic_v<U>
        constexpr Range<trait::quotient_t<T,U>>    operator/(U b) const noexcept;

        template <typename U>
        requires (std::is_arithmetic_v<U> && trait::self_div_v<T,U>) 
        Range<T>&    operator/=(U b) noexcept;

        template <typename U>
        constexpr Range<trait::quotient_t<T,U>>   operator/(const Range<U>&b) const noexcept;

        template <typename U>
        requires trait::self_div_v<T,U>
        Range<T>&    operator/=(const Range<U>& b) noexcept;

        template <typename U>
        constexpr Range<trait::product_t<T,U>>   operator/(const Range<U>&b) const noexcept;

        constexpr Range<T>  operator|(T) const noexcept;
        Range<T>&           operator|=(T) noexcept;

        constexpr Range<T>  operator|(const Range<T>& b) const noexcept;
        Range<T>&           operator|=(const Range<T>& b) noexcept;

        constexpr Range<T>  operator&(const Range<T>& b) const noexcept;
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
        
        constexpr Range     inflate(T) const noexcept;
        
        //! Checks for validity
        constexpr bool    is_valid() const noexcept;

        /*! \brief Projects a local [0,1] coordinate to a global coordinate
            \param[in] v    The local coordinate
            \return The global coordinate
        */
        template <typename=void>
        requires trait::is_floating_point_v<T>
        constexpr T   project(T v) const noexcept;

        //! Computes the span of the range
        constexpr T     span() const noexcept;

        /*! \brief Projects a global coordinate to a local [0,1] coordinate
            \param[in] v    The global coordinate
            \return The local coordinate
        */
        template <typename=void>
        requires trait::is_floating_point_v<T>
        constexpr T   unproject(T v) const noexcept;
        
        constexpr bool    valid() const noexcept;

    };

    YQ_IEEE754_1(Range)
    
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
    requires trait::is_arithmetic_v<T>
    constexpr Range<trait::product_t<T,U>>    operator*(T a, const Range<U>& b) noexcept;

    //! Division (assumes b to be valid)
    template <typename T, typename U>
    requires trait::is_arithmetic_v<T>
    constexpr Range<trait::product_t<T,U>>    operator/(T a, const Range<U>& b) noexcept;

    //! Union (assumes b to be valid)
    template <typename T>
    constexpr Range<T>    operator|(T a, const Range<T>& b) noexcept;

    template <typename T>
    constexpr Range<T>    center(const Range<T>& a) noexcept;
    
    template <typename T>
    constexpr T           span(const Range<T>& a) noexcept;
}

YQ_TYPE_DECLARE(yq::RangeD)
YQ_TYPE_DECLARE(yq::RangeF)
YQ_TYPE_DECLARE(yq::RangeI)
YQ_TYPE_DECLARE(yq::RangeU)


