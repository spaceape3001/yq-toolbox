////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once 

#include <math/preamble.hpp>
#include <math/gcd.hpp>

namespace yq {

    template <typename I=int>
    struct Fraction {
        static_assert(std::is_integral_v<I>, "Template parameter I must be an integer!");
    
        I   num = I{0};
        I   den = I{1};

        constexpr operator double() const { return (double) num / (double) den; }
    };


//  --------------------------------------------------------
//  COMPOSITION

    template <int N, int D>
    consteval Fraction<int>  fraction(const FRACTION<N,D>&)
    {
        return Fraction<int>{N,D};
    }


    YQ_ZERO_1(Fraction, { zero_v<T>, one_v<T> })

//  --------------------------------------------------------
//  BASIC/CRITICAL FUNCTIONS
    
    template <typename I>
    bool        is_valid(Fraction<I> a)
    {
        return a.den != I{0};
    }

    template <typename I>
    Fraction<I>  simplified(Fraction<I> a)
    {
        I   n   = (a.den > 0) ? a.num : -a.num;
        I   d   = (a.den > 0) ? a.den : -a.den;
        I   cf  = gcd(n, d);
        return Fraction<I>{ n, d };
    }
   
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
//  POSITIVE

    template <typename I>
    constexpr Fraction<I> operator+(Fraction<I> a)
    {
        return a;
    }
   
//  --------------------------------------------------------
//  NEGATIVE

    template <typename I>
    constexpr Fraction<I> operator-(Fraction<I> a)
    {
        return { -a.num, a.den };
    }
    
//  --------------------------------------------------------
//  NORMALIZATION

//  --------------------------------------------------------
//  ADDITION

    template <typename I>
    constexpr Fraction<I> operator+(Fraction<I> a, Fraction<I> b)
    {
        return Fraction<I>{ a.num*b.den+a.den*b.num, a.den*b.den };
    }

    template <typename I>
    Fraction<I>&  operator+=(Fraction<I>&a, Fraction<I>b)
    {
        a = a + b;
        return a;
    }
    
//  --------------------------------------------------------
//  SUBTRACTION

    template <typename I>
    constexpr Fraction<I> operator-(Fraction<I> a, Fraction<I> b)
    {
        return Fraction<I>{ a.num*b.den-a.den*b.num, a.den*b.den };
    }
    
    template <typename I>
    Fraction<I>&  operator-=(Fraction<I>&a, Fraction<I>b)
    {
        a = a - b;
        return a;
    }
    
//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename I>
    constexpr Fraction<I> operator*(Fraction<I> a, Fraction<I>b)
    {
        return Fraction<I>{ a.num*b.num, a.den*b.den };
    }

    template <typename I>
    Fraction<I>&  operator*=(Fraction<I>&a, Fraction<I>b)
    {
        a = a * b;
        return a;
    }

//  --------------------------------------------------------
//  DIVISION


    template <typename I>
    constexpr Fraction<I> operator/(Fraction<I> a, Fraction<I>b)
    {
        return Fraction<I>{ a.num*b.den, a.den*b.num };
    }

    template <typename I>
    Fraction<I>&  operator/=(Fraction<I>&a, Fraction<I>b)
    {
        a = a / b;
        return a;
    }

//  --------------------------------------------------------
//  POWERS

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

    template <typename I>
    Fraction<I>&  operator^=(Fraction<I>&a, I b)
    {
        a = a ^ b;
        return a;
    }

    template <typename I>
    constexpr std::strong_ordering   operator<=>(Fraction<I>&a, Fraction<I>b)
    {
        auto    lt  = a.num*b.den;
        auto    rt  = a.den*b.den;
        
        if(lt == rt)
            return std::strong_ordering::equal;
        return (lt < rt) ? std::strong_ordering::less : std::strong_ordering::greater;
    }
    
//  --------------------------------------------------------
//  ADVANCED FUNCTIONS
   
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
    
    template <typename I>
    Stream&     operator<<(Stream& s, Fraction<I> f)
    {
        return as_stream(s, f);
    }
   
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
