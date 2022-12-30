////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once 

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

        //! Converts to an double
        constexpr operator double() const { return (double) num / (double) den; }

        //! Affirmative operator
        constexpr Fraction operator+() const noexcept
        {
            return *this;
        }

        //! Negation operator
        constexpr Fraction operator-() noexcept
        {
            return { -num, den };
        }
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
        return a.den != I{0};
    }

    //! Reduces numerator and denominator by a common divisor
    template <typename I>
    Fraction<I>  simplified(Fraction<I> a)
    {
        I   n   = (a.den > 0) ? a.num : -a.num;
        I   d   = (a.den > 0) ? a.den : -a.den;
        I   cf  = gcd(n, d);
        return Fraction<I>{ n, d };
    }
   
    //! Raises the input by the specified power
    //! \note it's very easy to get integer overflows with this routine, at which point, 
    //! the result will be invalid.
    template <typename I>
    constexpr auto i_power(std::make_signed_t<I> base, std::make_unsigned_t<I> exp)
    {
        std::make_signed_t<I>   result{1};
        for(; exp; exp >>= 1){
            if(exp & 1)
                result *= base;
            base *= base;
        }
        return result;
    }

//  --------------------------------------------------------
//  ADDITION

    /*! \brief Adds two fractions
    */
    template <typename I>
    constexpr Fraction<I> operator+(Fraction<I> a, Fraction<I> b) noexcept
    {
        return Fraction<I>{ a.num*b.den+a.den*b.num, a.den*b.den };
    }

    /*! \brief Self-addition operator
    
        Adds the right term into the left fraction
    */
    template <typename I>
    Fraction<I>&  operator+=(Fraction<I>&a, Fraction<I>b)
    {
        a = a + b;
        return a;
    }
    
//  --------------------------------------------------------
//  SUBTRACTION

    /*! \brief Subtracts two fractions
    */
    template <typename I>
    constexpr Fraction<I> operator-(Fraction<I> a, Fraction<I> b) noexcept
    {
        return Fraction<I>{ a.num*b.den-a.den*b.num, a.den*b.den };
    }
    
    /*! \brief Self-subtraction operator
    
        Subtracts the right term from th e left fraction
    */
    template <typename I>
    Fraction<I>&  operator-=(Fraction<I>&a, Fraction<I>b)
    {
        a = a - b;
        return a;
    }
    
//  --------------------------------------------------------
//  MULTIPLICATION

    /*! \brief Multiplies two fractions
    */
    template <typename I>
    constexpr Fraction<I> operator*(Fraction<I> a, Fraction<I>b) noexcept
    {
        return Fraction<I>{ a.num*b.num, a.den*b.den };
    }

    /*! \brief Self-multiplication operator
        
        Multiplies the left term by the right.
    */
    template <typename I>
    Fraction<I>&  operator*=(Fraction<I>&a, Fraction<I>b)
    {
        a = a * b;
        return a;
    }

//  --------------------------------------------------------
//  DIVISION

    /*! \brief Divides two fractions
    */
    template <typename I>
    constexpr Fraction<I> operator/(Fraction<I> a, Fraction<I>b) noexcept
    {
        return Fraction<I>{ a.num*b.den, a.den*b.num };
    }

    /*! \brief Self-division operator
        
        Divides the left term by the right
    */
    template <typename I>
    Fraction<I>&  operator/=(Fraction<I>&a, Fraction<I>b)
    {
        a = a / b;
        return a;
    }

//  --------------------------------------------------------
//  POWERS

    /*! \brief Raises the left fraction to the right power */
    template <typename I>
    constexpr Fraction<I> operator^(Fraction<I>a, std::type_identity_t<I> b)
    {
        I     n   = 1;
        I     d   = 1;
        
        if(b < 0){
            n   = i_power<I>(a.den, -b);
            d   = i_power<I>(a.num, -b);
        } else {
            n   = i_power<I>(a.num, b);
            d   = i_power<I>(a.den, b);
        }
        return Fraction<I>{n,d};
    }

    /*! \brief Self-power operator
    
        Raises the left term to the right power
    */
    template <typename I>
    Fraction<I>&  operator^=(Fraction<I>&a, I b)
    {
        a = a ^ b;
        return a;
    }

    /*! \brief Comparison operator
    
        This compares the two fractions for equality.
        
        \note this will show that (1/2) == (2/4)
    */
    template <typename I>
    constexpr std::strong_ordering   operator<=>(const Fraction<I>&a, const Fraction<I>&b) noexcept
    {
        return a.num*b.den <=> a.den*b.num;
    }
    
//  --------------------------------------------------------
//  ADVANCED FUNCTIONS
   
    /*! \brief Streaming fraction to the given stream like object
    
        \tparam S   type of the stream
        \param[s]   Stream
        \param[f]   Fraction
    */
    template <typename S, typename I>
    S&  as_stream(S& s, Fraction<I> f)
    {
        switch(f.den){
        case I{0}:
            s << f.num << "/ZERO";
            break;
        case I{1}:
            s << f.num;
            break;
        default:
            s << f.num << '/' << f.den;
            break;
        }
        return s;
    }
    
    /*! \brief Streams to the given stream */
    template <typename I>
    Stream&     operator<<(Stream& s, Fraction<I> f)
    {
        return as_stream(s, f);
    }
   
    /*! \brief Streams to the given logger */
    template <typename I>
    log4cpp::CategoryStream&     operator<<(log4cpp::CategoryStream& s, Fraction<I> f)
    {
        return as_stream(s, f);
    }
    
    
    
}

YQ_TYPE_DECLARE(yq::FractionI)
//YQ_TYPE_DECLARE(yq::Frac16)
//YQ_TYPE_DECLARE(yq::Frac32)
//YQ_TYPE_DECLARE(yq::Frac64)
