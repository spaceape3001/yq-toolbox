////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_MULTIVECTOR1_HPP 1


#include <yq/typedef/multivector1.hpp>

#include <yq/vector/Vector1.hpp>

#include <yq/keywords.hpp>
#include <yq/trait/product.hpp>
#include <yq/trait/quotient.hpp>
#include <yq/trait/self_divide.hpp>
#include <yq/trait/self_multiply.hpp>
#include <yq/trait/unity.hpp>

namespace log4cpp { class CategoryStream; }


namespace yq {

    /*! \brief One dimensional multivector
    */
    template <typename T>
    struct Multivector1 {
        
        //! Captures the template parameter
        using component_type    = T;
    
        //! Scalar
        unity_t<T>  a;
        
        //! X
        T           x;

        //! Default constructor
        constexpr Multivector1() noexcept = default;
        
        //! Componentwise constructor
        constexpr Multivector1(T _a, T _x) noexcept : a(_a), x(_x) {}
        
        //! Constructs by values (scalar & vector)
        constexpr Multivector1(T _a, const Vector1<T>& v) noexcept : a(_a), x(v.x) {}
        
        //! Constructs all components to same value
        constexpr Multivector1(all_t, T v) noexcept : a(v), x(v) {}
        
        //! Constructs to all NaN
        template <typename=void> requires has_nan_v<T>
        consteval Multivector1(nan_t) noexcept : Multivector1(ALL, nan_v<T>) {}
        
        //! Constructs to all ones
        consteval Multivector1(one_t) noexcept : Multivector1(ALL, one_v<T>) {}
        
        //! Constructs to all zeros
        consteval Multivector1(zero_t) noexcept : Multivector1(ALL, zero_v<T>) {}
        
        //! Casting operator, to another multivector type of compatible type
        template <typename U>
        requires std::is_nothrow_convertible_v<T,U>
        explicit constexpr operator Multivector1<U>() const noexcept
        {
            return {
                (U) a,
                (U) x
            };
        }
        
        //! Casting operator, to another multivector type of compatible type
        template <typename U>
        requires (std::is_convertible_v<T,U> && !std::is_nothrow_convertible_v<T,U>)
        explicit constexpr operator Multivector1<U>() const 
        {
            return {
                (U) a,
                (U) x
            };
        }

        //! Defaulted equality
        constexpr bool operator==(const Multivector1&) const noexcept = default;

        //! Positive operator
        constexpr Multivector1 operator+() const noexcept;
        
        //! Negation operator
        constexpr Multivector1 operator-() const noexcept;
        
        //! Adds scalar to multivector, returns result
        constexpr Multivector1 operator+(T  b) const noexcept;
        
        //! Self-adds scalar to THIS multivector, returns reference
        Multivector1& operator+=(T  b) noexcept;
        
        //! Adds multivector to multivector, returns result
        constexpr Multivector1 operator+(const Multivector1&  b) const noexcept;
        
        //! Self-adds multivector to THIS multivector, returns reference
        Multivector1& operator+=(const Multivector1& b) noexcept;
        
        //! Adds vector to multivector, returns result
        constexpr Multivector1 operator+(const Vector1<T>&  b) const noexcept;
        
        //! Self-adds vector to THIS multivector, returns reference
        Multivector1& operator+=(const Vector1<T>& b) noexcept;
        
        //! Subtracts scalar from the multivector, returns result
        constexpr Multivector1 operator-(T  b) const noexcept;
        
        //! Self-subtracts scalar from THIS multivector, returns result
        Multivector1& operator-=(T  b) noexcept;
        
        //! Subtracts multivector from multivector, returns result
        constexpr Multivector1 operator-(const Multivector1&  b) const noexcept;
        
        //! Self-subtracts multivector from THIS multivector, returns reference
        Multivector1& operator-=(const Multivector1& b) noexcept;
        
        //! Subtracts vector from multivector, returns result
        constexpr Multivector1 operator-(const Vector1<T>&  b) const noexcept;
        Multivector1& operator-=(const Vector1<T>& b) noexcept;
        
        //! Multiplies the multivector by the given scalar, returns the result
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Multivector1<product_t<T,U>> operator*(U b) const noexcept;
        
        //! Self-multiplies THIS multivector with scalar, returns reference
        template <typename U>
        requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
        Multivector1& operator*=(U b) noexcept;

        //! Multiplies the multivector with another multivector, returns the result
        template <typename U>
        constexpr Multivector1<product_t<T,U>> operator*(const Multivector1<U>& b) const noexcept;

        //! Self-multiplies THIS multivector with another multivector, returns reference
        template <typename U>
        requires self_multiply_v<T,U>
        Multivector1<T>& operator*=(const Multivector1<U>& b) noexcept;
        
        //! Multiplies the multivector with a vector, returns the result
        template <typename U>
        constexpr Multivector1<product_t<T,U>> operator*(const Vector1<U>& b) const noexcept;
        
        //! Self-multiplies this multivector with a vector, returns the result
        template <typename U>
        requires self_multiply_v<T,U>
        Multivector1<T>& operator*=(const Vector1<U>& b) noexcept;

        //! Inner product with another multivector, returns the result
        template <typename U>
        constexpr product_t<T,U>   operator INNER(const Multivector1<U>&b)  const noexcept;

        //! Inner product with a vector, returns the result
        template <typename U>
        constexpr product_t<T,U>   operator INNER(const Vector1<U>&b) const noexcept;

        //! Divides multivector by scalar, returns the result
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Multivector1<quotient_t<T,U>> operator/(U b) const noexcept;

        //! Self-divides this multivector by scalar, returns the result
        template <typename U>
        requires (is_arithmetic_v<U> && self_divide_v<T,U>)
        Multivector1<T>& operator/=(U b) noexcept;

        constexpr Vector1<T>  vector() const noexcept;
    };

    YQ_IEEE754_1(Multivector1)
    YQ_INTEGER_1(Multivector1)
    YQ_IS_INTEGER_1(Multivector1)

//  --------------------------------------------------------
//  COMPOSITION

    YQ_NAN_1(Multivector1, Multivector1<T>(NAN))
    YQ_ZERO_1(Multivector1, Multivector1<T>(ZERO))
    
//  --------------------------------------------------------
//  GETTERS

    //! Extracts the vector part
    template <typename T>
    constexpr Vector1<T> vector(const Multivector1<T>& a) noexcept;

//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_NAN_1(Multivector1, is_nan(v.a) || is_nan(v.x) )
    YQ_IS_FINITE_1(Multivector1, is_finite(v.a) && is_finite(v.x))

//  --------------------------------------------------------
//  --------------------------------------------------------
    
    //! Adds left scalar with right multivector
    template <typename T>
    constexpr Multivector1<T> operator+(T a, const Multivector1<T>& b) noexcept;

    template <typename T>
    constexpr Multivector1<T> operator-(T a, const Multivector1<T>& b) noexcept;

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Multivector1<product_t<T,U>> operator*(T a, const Multivector1<U>&b) noexcept;


}

YQ_TYPE_DECLARE(Multivector1D)
YQ_TYPE_DECLARE(Multivector1F)
