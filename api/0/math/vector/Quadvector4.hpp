////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_QUADVECTOR4_HPP 1

#include <0/math/preamble.hpp>

namespace yq {

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
        explicit constexpr Quadvector4(T _xyzw) noexcept : xyzw(_xyzw) {}
        
        constexpr Quadvector4(all_t, T v) noexcept : xyzw(v) {}
        template <typename=void> requires has_nan_v<T>
        consteval Quadvector4(nan_t) noexcept : Quadvector4(ALL, nan_v<T>) {}
        consteval Quadvector4(one_t) noexcept : Quadvector4(ALL, one_v<T>) {}
        constexpr Quadvector4(xyzw_t, T v) noexcept : xyzw(v) {}
        consteval Quadvector4(xyzw_t) noexcept : Quadvector4(XYZW, one_v<T>) {}
        consteval Quadvector4(zero_t) noexcept : Quadvector4(ALL, zero_v<T>) {}

        template <typename U>
        requires std::is_nothrow_convertible_v<T,U>
        explicit constexpr operator Quadvector4<U>() const noexcept
        {
            return { (U) xyzw };
        }
        
        template <typename U>
        requires (std::is_convertible_v<T,U> && !std::is_nothrow_convertible_v<T,U>)
        explicit constexpr operator Quadvector4<U>() const 
        {
            return { (U) xyzw };
        }

        //! Defaulted comparison operator
        constexpr auto operator<=>(const Quadvector4&) const noexcept = default;

        constexpr Quadvector4       operator+() const noexcept;
        constexpr Quadvector4       operator-() const noexcept;

        constexpr Multivector4<T>   operator+(T b) const noexcept;
        constexpr Multivector4<T>   operator+(const Bivector4<T>& b) const noexcept;
        constexpr Multivector4<T>   operator+(const Multivector4<T>& b) const noexcept;
        constexpr Quadvector4       operator+(const Quadvector4& b) const noexcept;
        Quadvector4&                operator+=(const Quadvector4& b) noexcept;
        constexpr Multivector4<T>   operator+(const Trivector4<T>& b) const noexcept;
        constexpr Multivector4<T>   operator+(const Vector4<T>& b) const noexcept;

        constexpr Multivector4<T>   operator-(T b) const noexcept;
        constexpr Multivector4<T>   operator-(const Bivector4<T>& b) const noexcept;
        constexpr Multivector4<T>   operator-(const Multivector4<T>& b) const noexcept;
        constexpr Quadvector4       operator-(const Quadvector4& b) const noexcept;
        Quadvector4&                operator-=(const Quadvector4& b) noexcept;
        constexpr Multivector4<T>   operator-(const Trivector4<T>& b) const noexcept;
        constexpr Multivector4<T>   operator-(const Vector4<T>& b) const noexcept;

        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Quadvector4<product_t<T,U>> operator*(U b) const noexcept;

        template <typename U>
        requires (is_arithmetic_v<U> && self_mul_v<T,U>)
        Quadvector4& operator*=(U b) noexcept;

        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Quadvector4<quotient_t<T,U>> operator/(U b) const noexcept;

        template <typename U>
        requires (is_arithmetic_v<U> && self_div_v<T,U>)
        Quadvector4& operator/=(U b) noexcept;
    };

    YQ_IEEE754_1(Quadvector4)
    YQ_INTEGER_1(Quadvector4)
    YQ_IS_INTEGER_1(Quadvector4)

//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Literal constructor
    */
    constexpr Quadvector4D   operator "" _xyzw4(unsigned long long int v) noexcept
    {
        return Quadvector4D(XYZW, (double) v);
    }

    /*! \brief Literal constructor
    */
    constexpr Quadvector4D   operator "" _xyzw4(long double v) noexcept
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

    template <typename T>
    constexpr Multivector4<T> operator+(T a, const Quadvector4<T>& b) noexcept;
    template <typename T>
    constexpr Multivector4<T> operator-(T a, const Quadvector4<T>& b) noexcept;

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Quadvector4<product_t<T,U>> operator*(T a, const Quadvector4<U>& b) noexcept;

}

YQ_TYPE_DECLARE(yq::Quadvector4D)
YQ_TYPE_DECLARE(yq::Quadvector4F)

