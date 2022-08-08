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
    */
    template <typename T>
    struct Range {
        using component_type    = T;
        T   lo, hi;
        
        //! Default comparison object
        constexpr bool    operator==(const Range&) const noexcept = default;
        
        //  see if the for() syntax will work?
        constexpr T       begin() const { return lo; }
        constexpr T       end() const { return hi; }
    };

    YQ_IEEE754_1(Range)
    
//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Constructs a range 
    
        This routine enforces lo <= hi by using the min/max functions
    */
    template <typename T>
    constexpr Range<T> range(T a, T b)
    {
        return { min(a,b), max(a,b) };
    }
    
    template <typename T>
    constexpr Range<T> range(std::initializer_list<T> them)
    {
        return { min(them), max(them) };
    }
    
    template <typename T>
    constexpr Range<T> range(const Range<T>& a)
    {
        return range(a.lo, a.hi);
    }

    YQ_NAN_1(Range, Range<T>{nan_v<T>, nan_v<T>})
    YQ_ZERO_1(Range, Range<T>{zero_v<T>, zero_v<T>})

//  --------------------------------------------------------
//  GETTERS

//  --------------------------------------------------------
//  SETTERS


//  --------------------------------------------------------
//  BASIC FUNCTIONS

    template <typename T>
    bool    is_valid(const Range<T>& a)
    {
        return a.lo <= a.hi;
    }

    YQ_IS_NAN_1(Range, is_nan(v.lo) || is_nan(v.hi))
    YQ_IS_FINITE_1(Range, is_finite(v.lo) && is_finite(v.hi))


//  --------------------------------------------------------
//  POSITIVE

    template <typename T>
    constexpr Range<T> operator+(const Range<T>& a) noexcept
    {
        return a;
    }


//  --------------------------------------------------------
//  NEGATIVE

    template <typename T>
    constexpr Range<T> operator-(const Range<T>&a) noexcept
    {
        return range( -a.hi, -a.lo );
    }

//  --------------------------------------------------------
//  NORMALIZATION


//  --------------------------------------------------------
//  ADDITION

    template <typename T>
    constexpr Range<T>  operator+(T a, const Range<T>& b) noexcept
    {
        return range( a + b.lo, a + b.hi );
    }

    template <typename T>
    constexpr Range<T>  operator+(const Range<T>&a, T b) noexcept
    {
        return range( a.lo+b, a.hi+b );
    }

    template <typename T>
    Range<T>& operator+=(Range<T>&a, T b) noexcept
    {
        a = a + b;
        return a;
    }

    template <typename T>
    constexpr Range<T>  operator+(const Range<T>&a, const Range<T>& b) noexcept
    {
        return range({ a.lo+b.lo, a.lo+b.hi, a.hi+b.lo, a.hi+b.hi });
    }

    template <typename T>
    Range<T>& operator+=(Range<T>&a, const Range<T>& b) noexcept
    {
        a = a + b;
        return a;
    }

//  --------------------------------------------------------
//  SUBTRACTION

    template <typename T>
    constexpr Range<T>  operator-(T a, const Range<T>& b)
    {
        return range( a - b.hi, a - b.lo );
    }

    template <typename T>
    constexpr Range<T>  operator-(const Range<T>&a, T b)
    {
        return range( a.lo-b, a.hi-b );
    }

    template <typename T>
    Range<T>& operator-=(Range<T>&a, T b) noexcept
    {
        a = a - b;
        return a;
    }

    template <typename T>
    constexpr Range<T>  operator-(const Range<T>&a, const Range<T>& b) noexcept
    {
        return range({ a.lo-b.lo, a.lo-b.hi, a.hi-b.lo, a.hi-b.hi });
    }

    template <typename T>
    Range<T>& operator-=(Range<T>&a, const Range<T>& b) noexcept
    {
        a = a - b;
        return a;
    }

//  --------------------------------------------------------
//  MULTIPLICATION


    template <typename T, typename U>
    requires std::is_arithmetic_v<T>
    Range<product_t<T,U>>    operator*(T a, const Range<U>& b)
    {
        return range(a*b.lo, a*b.hi);
    }

    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    Range<product_t<T,U>>    operator*(const Range<T>& a, U b)
    {
        return range(a.lo*b, b.hi*b);
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Range<T>&    operator*=(const Range<T>& a, U b)
    {
        a   = a * b;
        return a;
    }

    template <typename T, typename U>
    Range<product_t<T,U>>   operator*(const Range<T>&a, const Range<U>&b)
    {
        return range({a.lo*b.lo, a.lo*b.hi, a.hi*b.lo, a.hi*b.hi });
    }

    template <typename T, typename U>
    requires trait::self_mul_v<T,U>
    Range<T>&    operator*=(const Range<T>& a, const Range<U>& b)
    {
        a   = a * b;
        return a;
    }


//  --------------------------------------------------------
//  DIVISION

    template <typename T, typename U>
    requires std::is_arithmetic_v<T>
    Range<product_t<T,U>>    operator/(T a, const Range<U>& b)
    {
        return range(a/b.lo, a/b.hi);
    }

    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    Range<product_t<T,U>>    operator/(const Range<T>& a, U b)
    {
        return range(a.lo/b, b.hi/b);
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Range<T>&    operator/=(const Range<T>& a, U b)
    {
        a   = a / b;
        return a;
    }

    template <typename T, typename U>
    Range<product_t<T,U>>   operator/(const Range<T>&a, const Range<U>&b)
    {
        return range({a.lo/b.lo, a.lo/b.hi, a.hi/b.lo, a.hi/b.hi });
    }

    template <typename T, typename U>
    requires trait::self_mul_v<T,U>
    Range<T>&    operator/=(const Range<T>& a, const Range<U>& b)
    {
        a   = a / b;
        return a;
    }

//  --------------------------------------------------------
//  POWERS

//  --------------------------------------------------------
//  DOT PRODUCT


//  --------------------------------------------------------
//  INNER PRODUCT


//  --------------------------------------------------------
//  OUTER PRODUCT


//  --------------------------------------------------------
//  CROSS PRODUCT


///  --------------------------------------------------------
//  OTIMES PRODUCT

//  --------------------------------------------------------
//  UNIONS

    template <typename T>
    Range<T>    operator|(T a, const Range<T>& b)
    {
        return range({ a, b.lo, b.hi });
    }

    template <typename T>
    Range<T>    operator|(const Range<T>& a, std::type_identity_t<T>  b)
    {
        return range({ a.lo, a.hi, b });
    }

    template <typename T>
    Range<T>    operator|=(Range<T>& a, std::type_identity_t<T>  b)
    {
        a = range({ a.lo, a.hi, b });
        return a;
    }


//  --------------------------------------------------------
//  INTERSECTIONS


//  --------------------------------------------------------
//  PROJECTIONS

    template <typename T>
    requires std::is_floating_point_v<T>
    T   local_to_global(const Range<T>& r, T v)
    {
        return (one_v<T>-v)*r.lo + v*r.hi;
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    T   global_to_local(const Range<T>& r, T v)
    {
        return (v-r.lo)/(r.hi-r.lo);
    }


//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

    template <typename T>
    requires std::is_floating_point_v<T>
    Range<T>    center(const Range<T>& a)
    {
        return half_v<T>*(a.lo+a.hi);
    }
    
    template <typename T>
    bool        is_inside(const Range<T>& a, T b)
    {
        return (a.lo <= b) && (b <= a.hi);
    }
    
    template <typename T>
    T           span(const Range<T>& a)
    {
        return a.hi - a.lo;
    }
}