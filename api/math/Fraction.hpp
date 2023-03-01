////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once 

#define YQ_MATH_FRACTION_HPP 1

#include <math/preamble.hpp>
#include <math/gcd.hpp>

namespace yq {

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
        
        consteval Fraction() noexcept : num(0), den(one_v<I>) {}
        constexpr Fraction(I n) : num(n), den(one_v<I>) {}
        constexpr Fraction(I n, I d) : num(n), den(d) {}
        
        template <int N, int D>
        consteval Fraction(const FRACTION<N,D>&) : num(N), den(D) {}

        //! Converts to an double
        constexpr operator double() const { return (double) num / (double) den; }

        //! Affirmative operator
        constexpr Fraction  operator+() const noexcept;

        //! Negation operator
        constexpr Fraction  operator-() const noexcept;
        
        constexpr Fraction  operator+(const Fraction& b) const noexcept;
        Fraction&           operator+=(const Fraction& b) noexcept;
        constexpr Fraction  operator-(const Fraction& b) const noexcept;
        Fraction&           operator-=(const Fraction& b) noexcept;
        constexpr Fraction  operator*(const Fraction&b) const noexcept;
        Fraction&           operator*=(const Fraction& b) noexcept;
        constexpr Fraction  operator/(const Fraction&b) const noexcept;
        Fraction&           operator/=(const Fraction& b) noexcept;
        
        constexpr Fraction  operator^(I b) const noexcept;
        Fraction&           operator^=(I b) noexcept;
        
        
        constexpr std::strong_ordering   operator<=>(const Fraction&b) const noexcept
        {
            return num*b.den <=> den*b.num;
        }
        
        //! Reduces numerator and denominator by a common divisor
        constexpr Fraction simplified() const noexcept;
        
        constexpr bool    valid() const noexcept;
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
   
    /*! \brief Streaming fraction to the given stream like object
    
        \tparam S   type of the stream
        \param[s]   Stream
        \param[f]   Fraction
    */
    template <typename S, typename I>
    S&  as_stream(S& s, Fraction<I> f);
    
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
