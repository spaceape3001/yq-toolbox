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
        constexpr bool      operator==(const Range&) const noexcept = default;
        
        constexpr Range<T>  operator+() const noexcept
        {
            return *this;
        }

        constexpr Range<T>  operator-() const noexcept
        {
            return range( -hi, -lo );
        }

        //  see if the for() syntax will work?
        
        //! low value (for-loops)
        constexpr T       begin() const noexcept { return lo; }
        
        /*! \brief Computes the center of this range */
        constexpr Range<T>    center() const noexcept
        {
            if constexpr (std::is_floating_point_v<T>)
                return ieee754_t<T>(0.5)*(lo+hi);
            if constexpr (std::is_integral_v<T>)
                return (lo+hi) / T(2);
            return {};
        }
        
        //! Checks if value is within range
        constexpr bool        eclipses(T b) const noexcept
        {
            return (lo <= b) && (b <= hi);
        }
    
        //! Checks if provided range is entirely within this range
        constexpr bool        eclipses(const Range& b) const noexcept
        {
            return (lo <= b.lo) && (b.hi <= hi);
        }

        //! high value (for-loops)
        constexpr T       end() const noexcept { return hi; }
        
        //! Checks for validity
        constexpr bool    is_valid() const noexcept
        {
            return lo <= hi;
        }

        /*! \brief Projects a local [0,1] coordinate to a global coordinate
            \param[in] v    The local coordinate
            \return The global coordinate
        */
        template <typename=void>
        requires std::is_floating_point_v<T>
        constexpr T   project(T v) const noexcept
        {
            return (one_v<T>-v)*lo + v*hi;
        }

        //! Computes the span of the range
        constexpr T     span() const noexcept
        {
            return hi - lo;
        }

        /*! \brief Projects a global coordinate to a local [0,1] coordinate
            \param[in] v    The global coordinate
            \return The local coordinate
        */
        template <typename=void>
        requires std::is_floating_point_v<T>
        constexpr T   unproject(T v) const noexcept
        {
            return (v-lo)/(hi-lo);
        }

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
        return { min(a,b), max(a,b) };
    }
    
    template <typename T>
    constexpr Range<T> range(std::initializer_list<T> them) noexcept
    {
        return { min(them), max(them) };
    }
    
    template <typename T>
    constexpr Range<T> range(const Range<T>& a) noexcept
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
    constexpr bool    is_valid(const Range<T>& a) noexcept
    {
        return a.is_valid();
    }

    YQ_IS_NAN_1(Range, is_nan(v.lo) || is_nan(v.hi))
    YQ_IS_FINITE_1(Range, is_finite(v.lo) && is_finite(v.hi))



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
    constexpr Range<T>  operator-(T a, const Range<T>& b) noexcept
    {
        return range( a - b.hi, a - b.lo );
    }

    template <typename T>
    constexpr Range<T>  operator-(const Range<T>&a, T b) noexcept
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
    constexpr Range<product_t<T,U>>    operator*(T a, const Range<U>& b) noexcept
    {
        return range(a*b.lo, a*b.hi);
    }

    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Range<product_t<T,U>>    operator*(const Range<T>& a, U b) noexcept
    {
        return range(a.lo*b, b.hi*b);
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_mul_v<T,U>) 
    Range<T>&    operator*=(const Range<T>& a, U b) noexcept
    {
        a   = a * b;
        return a;
    }

    template <typename T, typename U>
    constexpr Range<product_t<T,U>>   operator*(const Range<T>&a, const Range<U>&b) noexcept
    {
        return range({a.lo*b.lo, a.lo*b.hi, a.hi*b.lo, a.hi*b.hi });
    }

    template <typename T, typename U>
    requires trait::self_mul_v<T,U>
    Range<T>&    operator*=(const Range<T>& a, const Range<U>& b) noexcept
    {
        a   = a * b;
        return a;
    }


//  --------------------------------------------------------
//  DIVISION

    template <typename T, typename U>
    requires std::is_arithmetic_v<T>
    constexpr Range<product_t<T,U>>    operator/(T a, const Range<U>& b) noexcept
    {
        return range(a/b.lo, a/b.hi);
    }

    template <typename T, typename U>
    requires std::is_arithmetic_v<U>
    constexpr Range<product_t<T,U>>    operator/(const Range<T>& a, U b) noexcept
    {
        return range(a.lo/b, b.hi/b);
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_mul_v<T,U>) 
    Range<T>&    operator/=(const Range<T>& a, U b) noexcept
    {
        a   = a / b;
        return a;
    }

    template <typename T, typename U>
    constexpr Range<product_t<T,U>>   operator/(const Range<T>&a, const Range<U>&b) noexcept
    {
        return range({a.lo/b.lo, a.lo/b.hi, a.hi/b.lo, a.hi/b.hi });
    }

    template <typename T, typename U>
    requires trait::self_mul_v<T,U>
    Range<T>&    operator/=(const Range<T>& a, const Range<U>& b) noexcept
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
    constexpr Range<T>    operator|(T a, const Range<T>& b) noexcept
    {
        return range({ a, b.lo, b.hi });
    }

    template <typename T>
    constexpr Range<T>    operator|(const Range<T>& a, std::type_identity_t<T>  b) noexcept
    {
        return range({ a.lo, a.hi, b });
    }

    template <typename T>
    Range<T>    operator|=(Range<T>& a, std::type_identity_t<T>  b) noexcept
    {
        a = range({ a.lo, a.hi, b });
        return a;
    }


//  --------------------------------------------------------
//  INTERSECTIONS


//  --------------------------------------------------------
//  PROJECTIONS



//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

    template <typename T>
    constexpr Range<T>    center(const Range<T>& a) noexcept
    {
        return a.center();
    }
    
    template <typename T>
    constexpr T           span(const Range<T>& a) noexcept
    {
        return a.span();
    }
}
