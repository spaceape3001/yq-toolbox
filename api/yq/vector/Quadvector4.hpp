////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_QUADVECTOR4_HPP 1

#include <yq/typedef/quadvector4.hpp>

#include <yq/keywords.hpp>
#include <yq/meta/MetaBinder.hpp>
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
    template <typename> struct Bivector4;
    template <typename> struct Multivector4;
    template <typename> struct Trivector4;
    template <typename> struct Vector4;


    /*! \brief Four dimensional quadvector
    
        Quadvector for four dimensions.  (ie a measure of hypervolume)
    */
    template <typename T>
    struct Quadvector4 {

        //! Component type
        using component_type = T;

        //! XYZW Component
        T     xyzw;

        //! Default constructor
        constexpr Quadvector4() noexcept = default;
        
        //! Initializing componentwise constructor
        constexpr Quadvector4(T _xyzw) noexcept : xyzw(_xyzw) {}
        
        //! Constructs ALL components to same value
        constexpr Quadvector4(all_k, T v) noexcept : xyzw(v) {}

        //! Constructs to NaN in the components
        template <typename=void> requires has_nan_v<T>
        consteval Quadvector4(nan_k) noexcept : Quadvector4(ALL, nan_v<T>) {}
        
        //! Constructs with all components ONE
        consteval Quadvector4(one_k) noexcept : Quadvector4(ALL, one_v<T>) {}
        
        //! Constructs with the XYZW component set to the specified value
        //! \note This is done for consistency to the other structs.
        constexpr Quadvector4(xyzw_k, T v) noexcept : xyzw(v) {}
        
        //! Constructs to a unit quadvector in the XYZW component
        consteval Quadvector4(xyzw_k) noexcept : Quadvector4(XYZW, one_v<T>) {}
        
        //! Constructs with all components zero
        consteval Quadvector4(zero_k) noexcept : Quadvector4(ALL, zero_v<T>) {}

        //! Converts this quadvector to another of compatible type
        template <typename U>
        requires std::is_nothrow_convertible_v<T,U>
        explicit constexpr operator Quadvector4<U>() const noexcept
        {
            return { (U) xyzw };
        }
        
        //! Converts this quadvector to another of compatible type
        template <typename U>
        requires (std::is_convertible_v<T,U> && !std::is_nothrow_convertible_v<T,U>)
        explicit constexpr operator Quadvector4<U>() const 
        {
            return { (U) xyzw };
        }

        //! Defaulted comparison operator
        constexpr auto operator<=>(const Quadvector4&) const noexcept = default;

        //! Positive/Affirmation operator
        constexpr Quadvector4       operator+() const noexcept;
        
        //! Negation operator
        constexpr Quadvector4       operator-() const noexcept;

        //! Adds scalar to quadvector, returns multivector result
        constexpr Multivector4<T>   operator+(T b) const noexcept;
        
        //! Adds bivector to quadvector, returns multivector result
        constexpr Multivector4<T>   operator+(const Bivector4<T>& b) const noexcept;
        
        //! Adds multivector to quadvector, returns multivector result
        constexpr Multivector4<T>   operator+(const Multivector4<T>& b) const noexcept;
        
        //! Adds two quadvectors, returns the quadvector result
        constexpr Quadvector4       operator+(const Quadvector4& b) const noexcept;
        
        //! Self-adds another quadvector to this one, returns a reference to self
        Quadvector4&                operator+=(const Quadvector4& b) noexcept;
        
        //! Adds trivector to quadvector, returns multivector result
        constexpr Multivector4<T>   operator+(const Trivector4<T>& b) const noexcept;
        
        //! Adds vector to quadvector, returns multivector result
        constexpr Multivector4<T>   operator+(const Vector4<T>& b) const noexcept;

        //! Subtracts scalar from quadvector, returns multivector result
        constexpr Multivector4<T>   operator-(T b) const noexcept;
        
        //! Subtracts bivector from quadvector, returns multivector result
        constexpr Multivector4<T>   operator-(const Bivector4<T>& b) const noexcept;
        
        //! Subtracts multivector from quadvector, returns multivector result
        constexpr Multivector4<T>   operator-(const Multivector4<T>& b) const noexcept;
        
        //! Subtracts two quadvectors, returns quadvector result
        constexpr Quadvector4       operator-(const Quadvector4& b) const noexcept;
        
        //! Self-subtracts right quadvector from left, returns reference to self
        Quadvector4&                operator-=(const Quadvector4& b) noexcept;
        
        //! Subtracts trivector from quadvector, returns multivector result
        constexpr Multivector4<T>   operator-(const Trivector4<T>& b) const noexcept;
        
        //! Subtracts vector from quadvector, returns multivector result
        constexpr Multivector4<T>   operator-(const Vector4<T>& b) const noexcept;

        //! Multiplies quadvector by scalar, returns quadvector result
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Quadvector4<product_t<T,U>> operator*(U b) const noexcept;

        //! Self-multiplies this quadvector by the given scalar, returns reference to this quadvector
        template <typename U>
        requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
        Quadvector4& operator*=(U b) noexcept;

        //! Divides this quadvector by the given scalar, returns quadvector result
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Quadvector4<quotient_t<T,U>> operator/(U b) const noexcept;

        //! Self-divides this quadvector by the given scalar, returns reference to this quadvector
        template <typename U>
        requires (is_arithmetic_v<U> && self_divide_v<T,U>)
        Quadvector4& operator/=(U b) noexcept;
    };

    YQ_IEEE754_1(Quadvector4)
    YQ_INTEGER_1(Quadvector4)
    YQ_IS_INTEGER_1(Quadvector4)

//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Literal constructor
    */
    constexpr Quadvector4D   operator ""_xyzw4(unsigned long long int v) noexcept
    {
        return Quadvector4D(XYZW, (double) v);
    }

    /*! \brief Literal constructor
    */
    constexpr Quadvector4D   operator ""_xyzw4(long double v) noexcept
    {
        return Quadvector4D(XYZW, (double) v);
    }

    YQ_NAN_1(Quadvector4, Quadvector4<T>(NAN))
    YQ_ZERO_1(Quadvector4, Quadvector4<T>(ZERO))

//  --------------------------------------------------------
//  GETTERS

//  --------------------------------------------------------
//  BASIC FUNCTIONS
    
    YQ_IS_NAN_1(Quadvector4, is_nan(v.xyzw))
    YQ_IS_FINITE_1(Quadvector4, is_finite(v.xyzw))


//  --------------------------------------------------------
//  --------------------------------------------------------

    //! Adds scalar with quadvector, returns multivector result
    template <typename T>
    constexpr Multivector4<T> operator+(T a, const Quadvector4<T>& b) noexcept;
    
    //! Subtracts quadvector from scalar, returns multivector result
    template <typename T>
    constexpr Multivector4<T> operator-(T a, const Quadvector4<T>& b) noexcept;

    //! Multiplies quadvector with scalar, returns quadvector result
    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Quadvector4<product_t<T,U>> operator*(T a, const Quadvector4<U>& b) noexcept;

}

YQ_TYPE_DECLARE(yq::Quadvector4D)
YQ_TYPE_DECLARE(yq::Quadvector4F)

