////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once 

#define YQ_MATH_FRACTION_HPP 1

#include <yq/keywords.hpp>
#include <yq/math/gcd.hpp>
#include <yq/math/template/fraction.hpp>
#include <yq/meta/MetaBinder.hpp>
#include <yq/trait/has_one.hpp>
#include <yq/trait/has_zero.hpp>
#include <yq/typedef/fraction.hpp>
#include <compare>
#include <type_traits>

namespace log4cpp { class CategoryStream; }

namespace yq {
    class Stream;

    /*! \brief Simple fraction
    
        \tparam I   integer type
    */
    template <typename I=int>
    struct Fraction {
        static_assert(std::is_integral_v<I>, "Template parameter I must be an integer!");
    
        //! Numerator
        I   num = I{0};
        
        //! Denominator
        I   den = I{1};
        
        //! Default constructor
        consteval Fraction() noexcept : num(0), den(one_v<I>) {}
        
        //! Creates fraction from whole number
        constexpr Fraction(I n) : num(n), den(one_v<I>) {}
        
        //! Creates fraction from two parts
        constexpr Fraction(I n, I d) : num(n), den(d) {}
        
        //! Creates fraction from template fractoin
        template <int N, int D>
        consteval Fraction(const FRACTION<N,D>&) : num(N), den(D) {}
        
        //! Fraction of one
        consteval Fraction(one_k) : num(one_v<I>), den(one_v<I>) {}
        
        //! Fraction of zero
        consteval Fraction(zero_k) : num(zero_v<I>), den(one_v<I>) {}

        //! Converts to an double
        constexpr operator double() const { return (double) num / (double) den; }

        //! Affirmative operator
        constexpr Fraction  operator+() const noexcept;

        //! Negation operator
        constexpr Fraction  operator-() const noexcept;
        
        //! Addition
        constexpr Fraction  operator+(const Fraction& b) const noexcept;
        
        //! Self addition
        Fraction&           operator+=(const Fraction& b) noexcept;
        
        //! Subtraction
        constexpr Fraction  operator-(const Fraction& b) const noexcept;
        
        //! Self-subtraction
        Fraction&           operator-=(const Fraction& b) noexcept;
        
        //! Multiplication
        constexpr Fraction  operator*(const Fraction&b) const noexcept;
        
        //! Self-multiplication
        Fraction&           operator*=(const Fraction& b) noexcept;
        
        //! Division
        constexpr Fraction  operator/(const Fraction&b) const noexcept;
        
        //! Self division
        Fraction&           operator/=(const Fraction& b) noexcept;
        
        //! Powers
        constexpr Fraction  operator^(I b) const noexcept;
        
        //! Self powers
        Fraction&           operator^=(I b) noexcept;
        
        //! Comparison
        constexpr std::strong_ordering   operator<=>(const Fraction&b) const noexcept
        {
            return num*b.den <=> den*b.num;
        }
        
        //! Reduces numerator and denominator by a common divisor
        constexpr Fraction simplified() const noexcept;
        
        //! Validity test (ie, denominator is not zero)
        constexpr bool    valid() const noexcept;
        
        template <typename S>
        S&  stream(S&) const;
    };


//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Creates a fraction from a templated fraction
    */
    template <int N, int D>
    consteval Fraction<int>  fraction(const FRACTION<N,D>&)
    {
        return Fraction<int>{N,D};
    }

    YQ_ZERO_1(Fraction, { zero_v<T>, one_v<T> })

//  --------------------------------------------------------
//  BASIC/CRITICAL FUNCTIONS
    
    //! Tests for a non-zero denominator
    template <typename I>
    bool        is_valid(Fraction<I> a)
    {
        return a.valid();
    }

    //! Simplified form of fraction
    template <typename I>
    Fraction<I>  simplified(Fraction<I> a)
    {
        return a.simplified();
    }
   
    //! Raises the input by the specified power
    //! \note it's very easy to get integer overflows with this routine, at which point, 
    //! the result will be invalid.
    template <typename I>
    constexpr auto i_power(std::make_signed_t<I> base, std::make_unsigned_t<I> exp) noexcept;

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS
   
    /*! \brief Streams to the given stream */
    template <typename I>
    Stream&     operator<<(Stream& s, Fraction<I> f);
    
    /*! \brief Streams to the given logger */
    template <typename I>
    log4cpp::CategoryStream&     operator<<(log4cpp::CategoryStream& s, Fraction<I> f);
    
}

YQ_TYPE_DECLARE(yq::FractionI)
//YQ_TYPE_DECLARE(yq::Frac16)
//YQ_TYPE_DECLARE(yq::Frac32)
//YQ_TYPE_DECLARE(yq::Frac64)
