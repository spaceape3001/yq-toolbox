////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_BIVECTOR2_HPP 1

#include <yq/typedef/bivector2.hpp>

#include <yq-toolbox/keywords.hpp>
#include <yq-toolbox/meta/InfoBinder.hpp>
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

namespace log4cpp { class CategoryStream; }

namespace yq {
    template <typename> struct Multivector2;
    template <typename> struct Vector2;

    /*! \brief 2D Bivector
    
        Two dimensional bivector
    */
    template <typename T>
    struct Bivector2 {
    
        //! Component type
        using component_type = T;
        
        //! The value... since it's a unit area, square of T
        T               xy;
        
        //! Default constructor
        constexpr Bivector2() noexcept = default;
        
        //! Component wise constructor 
        constexpr Bivector2(T _xy) noexcept : xy(_xy) {}
        
        //! Constructs all components to the same value
        constexpr Bivector2(all_t, T v) noexcept : xy(v) {}
        
        //! Constructs with NaN in all components
        consteval Bivector2(nan_t) noexcept : Bivector2(ALL, nan_v<T>) {}

        //! Constructs with ONE in all components
        consteval Bivector2(one_t) noexcept : Bivector2(ALL, one_v<T>) {}
        
        //! Constructs with a single (possibly) non-zero value in the XY component
        constexpr Bivector2(xy_t, T v) noexcept : xy(v) {}
        
        //! Constructs a unit bivector in the XY component
        consteval Bivector2(xy_t) noexcept : Bivector2(XY, one_v<T>) {}
        
        //! Constructs a zero bivector
        consteval Bivector2(zero_t) noexcept : Bivector2(ALL, zero_v<T>) {}
        
        //! Converts to another bivector of compatible type
        template <typename U>
        requires std::is_nothrow_convertible_v<T,U>
        explicit constexpr operator Bivector2<U>() const noexcept
        {
            return { (U) xy };
        }
        
        //! Converts to another bivector of compatible type
        template <typename U>
        requires (std::is_convertible_v<T,U> && !std::is_nothrow_convertible_v<T,U>)
        explicit constexpr operator Bivector2<U>() const 
        {
            return { (U) xy };
        }
        
        //! Defaulted comparison operator
        constexpr auto operator<=>(const Bivector2&) const noexcept = default;
        
        /*! \brief Affirmation (positive) operator
        
            \note Here to complement the negation operator
        */
        constexpr Bivector2 operator+() const noexcept;

        /*! \brief Negation operator of a bivector
        */
        constexpr Bivector2 operator-() const noexcept;
        
        //! Adds a bivector with a scalar
        constexpr Multivector2<T> operator+(T b) const noexcept;
        
        //! Adds two bivectors together
        constexpr Bivector2<T> operator+(const Bivector2<T>& b) const noexcept;
        
        //! Self-incrementing this bivector
        Bivector2<T>& operator+=(const Bivector2<T>& b) noexcept;
        
        //! Adds a bivector with a multivector
        constexpr Multivector2<T> operator+(const Multivector2<T>& b) const noexcept;
        
        //! Adds a bivector with a vector
        constexpr Multivector2<T> operator+(const Vector2<T>& b) const noexcept;

        //! Subtracts a scalar from this bivector
        constexpr Multivector2<T> operator-(T b) const noexcept;
        
        //! Subtracts two bivectors
        constexpr Bivector2<T> operator-( const Bivector2<T>& b) const noexcept;
        
        //! Self-decrementing this bivector
        Bivector2<T>& operator-=(const Bivector2<T>& b) noexcept;
        
        //! Subtracts a multivector from this bivector
        constexpr Multivector2<T> operator-(const Multivector2<T>& b) const noexcept;

        //! Subtracts a vector from this bivector
        constexpr Multivector2<T> operator-(const Vector2<T>& b) const noexcept;

        //! Multiplies a bivector by the given factor, returns the result
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Bivector2<product_t<T,U>> operator*(U b) const noexcept;

        //! Self-multiplies this bivector by the given factor
        template <typename U>
        requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
        Bivector2<T>& operator*=(U b) noexcept;

        //! Divides a bivector by the given divisor, returns the result
        template <typename U>
        requires is_arithmetic_v<T>
        constexpr Bivector2<quotient_t<T,U>> operator/(U b) const noexcept;

        //! Self-divides this bivector by the given factor
        template <typename U>
        requires (is_arithmetic_v<U> && self_divide_v<T,U>)
        Bivector2<T>& operator/=(U b) noexcept;
    };

    YQ_IEEE754_1(Bivector2)
    YQ_INTEGER_1(Bivector2)
    YQ_IS_INTEGER_1(Bivector2)

//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Literal constructor
    */
    constexpr Bivector2D  operator "" _xy2(unsigned long long int v) noexcept
    {
        return Bivector2D(XY, (double) v);
    }

    /*! \brief Literal constructor
    */
    constexpr Bivector2D  operator "" _xy2(long double v) noexcept
    {
        return Bivector2D(XY, (double) v);
    }

    
    YQ_NAN_1(Bivector2, Bivector2<T>(NAN))
    YQ_ZERO_1(Bivector2, Bivector2<T>(ZERO))
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_NAN_1(Bivector2, is_nan(v.xy))
    YQ_IS_FINITE_1(Bivector2, is_finite(v.xy))


//  --------------------------------------------------------
//  --------------------------------------------------------

    //! Adds a value with a bivector (same type)
    template <typename T>
    constexpr Multivector2<T> operator+(T a, const Bivector2<T>& b) noexcept;

    //! Subtracts a bivector from a value (same type)
    template <typename T>
    constexpr Multivector2<T> operator-(T a, const Bivector2<T>& b) noexcept;

    /*! \brief Scaling multiplication operator
    
        \note currently limited to floating points due to uncertainty 
    */
    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Bivector2<product_t<T,U>> operator*(T a, const Bivector2<U>& b) noexcept;


}

YQ_TYPE_DECLARE(yq::Bivector2D)
YQ_TYPE_DECLARE(yq::Bivector2F)

