////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Fraction.hpp"
#include <yq/basic/Logging.hpp>
#include <yq/io/StreamOps.hpp>

/* 
    This is the template IMPLEMENTATION of the fraction code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

namespace yq {
    template <typename I>
    constexpr Fraction<I> Fraction<I>::operator+() const noexcept
    {
        return *this;
    }

    template <typename I>
    constexpr Fraction<I> Fraction<I>::operator-() const noexcept
    {
        return { -num, den };
    }


    template <typename I>
    constexpr Fraction<I> Fraction<I>::operator+(const Fraction<I>& b) const noexcept
    {
        return Fraction<I>{ num*b.den+den*b.num, den*b.den };
    }

    template <typename I>
    Fraction<I>&  Fraction<I>::operator+=(const Fraction<I>& b) noexcept
    {
        *this = *this + b;
        return *this;
    }
    
    template <typename I>
    constexpr Fraction<I> Fraction<I>::operator-(const Fraction<I>& b) const noexcept
    {
        return Fraction<I>{ num*b.den-den*b.num, den*b.den };
    }
    
    template <typename I>
    Fraction<I>&  Fraction<I>::operator-=(const Fraction<I>& b) noexcept
    {
        *this = *this - b;
        return *this;
    }
    
    template <typename I>
    constexpr Fraction<I> Fraction<I>::operator*(const Fraction<I>&b) const noexcept
    {
        return Fraction<I>{ num*b.num, den*b.den };
    }

    template <typename I>
    Fraction<I>&  Fraction<I>::operator*=(const Fraction& b) noexcept
    {
        *this = *this * b;
        return *this;
    }

    template <typename I>
    constexpr Fraction<I> Fraction<I>::operator/(const Fraction<I>&b) const noexcept
    {
        return Fraction<I>{ num*b.den, den*b.num };
    }

    template <typename I>
    Fraction<I>&  Fraction<I>::operator/=(const Fraction& b) noexcept
    {
        *this = *this / b;
        return *this;
    }

    template <typename I>
    constexpr Fraction<I> Fraction<I>::operator^(I b) const noexcept
    {
        I     n   = 1;
        I     d   = 1;
        
        if(b < 0){
            n   = i_power<I>(den, -b);
            d   = i_power<I>(num, -b);
        } else {
            n   = i_power<I>(num, b);
            d   = i_power<I>(den, b);
        }
        return Fraction<I>{n,d};
    }

    template <typename I>
    Fraction<I>&  Fraction<I>::operator^=(I b) noexcept
    {
        *this = *this ^ b;
        return *this;
    }
    
    template <typename I>
    constexpr Fraction<I> Fraction<I>::simplified() const noexcept
    {
        I   n   = (den > 0) ? num : -num;
        I   d   = (den > 0) ? den : -den;
        I   cf  = gcd(n, d);
        return Fraction(n/cf, d/cf);
    }

    template <typename I>
    constexpr bool    Fraction<I>::valid() const noexcept
    {
        return den != zero_v<I>;
    }
    
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename I>
    constexpr auto i_power(std::make_signed_t<I> base, std::make_unsigned_t<I> exp) noexcept
    {
        std::make_signed_t<I>   result{1};
        for(; exp; exp >>= 1){
            if(exp & 1)
                result *= base;
            base *= base;
        }
        return result;
    }

    template <typename I>
        template <typename S>
    S&  Fraction<I>::stream(S& s) const
    {
        switch(den){
        case I{0}:
            s << num << "/ZERO";
            break;
        case I{1}:
            s << num;
            break;
        default:
            s << num << '/' << den;
            break;
        }
        return s;
    }
    
    /*! \brief Streams to the given stream */
    template <typename I>
    Stream&     operator<<(Stream& s, Fraction<I> f)
    {
        return f.stream(s);
    }
   
    /*! \brief Streams to the given logger */
    template <typename I>
    log4cpp::CategoryStream&     operator<<(log4cpp::CategoryStream& s, Fraction<I> f)
    {
        return f.stream(s);
    }
    
}
