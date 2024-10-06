////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq-toolbox/coord/Coord1.hpp>
#include <yq-toolbox/coord/Coord.hpp>
#include <yq-toolbox/math/AllComponents.hpp>
#include <yq-toolbox/math/AnyComponents.hpp>

namespace yq {
    template <typename T>
    constexpr Coord1<T> Coord1<T>::operator-() const noexcept 
    {
        return { -i };
    }
    
    template <typename T>
    constexpr Coord1<T> Coord1<T>::operator+() const noexcept
    {
        return *this;
    }
    
    template <typename T>
    constexpr Coord1<T> Coord1<T>::operator+(const Coord1<T>& b) const noexcept
    {
        return { i+b.i };
    }

    template <typename T>
    constexpr Coord1<T> Coord1<T>::operator-(const Coord1<T>&b) const noexcept
    {
        return { i-b.i };
    }

    template <typename T>
    Coord1<T>& Coord1<T>::operator+=(const Coord1<T>& b) noexcept
    {
        i += b.i;
        return *this;
    }

    template <typename T>
    Coord1<T>& Coord1<T>::operator-=(const Coord1<T>& b) noexcept
    {
        i -= b.i;
        return *this;
    }

    template <typename T>
        template <typename U>
            requires is_arithmetic_v<U>
    constexpr Coord1<product_t<T,U>> Coord1<T>::operator*(U b) const noexcept
    {
        return { i*b };
    }

    template <typename T>
        template <typename U>
    constexpr Coord1<product_t<T,U>> Coord1<T>::operator*(const Coord1<U>& b) const noexcept
    {
        return { i*b.i };
    }
    
    template <typename T>
        template <typename U>
            requires self_multiply_v<T,U>
    Coord1<T>& Coord1<T>::operator*=(const Coord1<U>& b) noexcept
    {
        i *= b.i;
        return *this;
    }

    template <typename T>
        template <typename U>
            requires is_arithmetic_v<U>
    constexpr Coord1<quotient_t<T,U>> Coord1<T>::operator/(U b) const noexcept
    {
        return { i/b };
    }

    template <typename T>
        template <typename U>
            requires (is_arithmetic_v<U> && self_divide_v<T,U>)
    Coord1<T>& Coord1<T>::operator/=(U b) noexcept
    {
        i /= b;
        return *this;
    }

    template <typename T>
        template <typename U>
    constexpr Coord1<quotient_t<T,U>> Coord1<T>::operator/(const Coord1<U>& b) const noexcept
    {
        return { i/b.i };
    }

    template <typename T>
        template <typename U>
            requires self_divide_v<T,U>
    Coord1<T>& Coord1<T>::operator/=(const Coord1<U>& b) noexcept
    {
        i /= b.i;
        return *this;
    }

    template <typename T>
    constexpr Coord1<T> Coord1<T>::all_add(T b) const noexcept
    {
        return Coord1( i+b );
    }

    template <typename T>
    Coord1<T>&    Coord1<T>::all_decrement(T b) noexcept
    {
        i -= b;
        return *this;
    }

    template <typename T>
    Coord1<T>&    Coord1<T>::all_increment(T b) noexcept
    {
        i += b;
        return *this;
    }
    
    template <typename T>
    constexpr Coord1<T> Coord1<T>::all_subtract(T b) const noexcept
    {
        return Coord1( i-b );
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Coord1<T>::all_test(Pred pred) const noexcept
    {
        return pred(i);
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Coord1<T>::all_test(T b, Pred pred) const noexcept
    {
        return pred(i, b);
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Coord1<T>::all_test(const Coord1<T>& b, Pred pred) const noexcept
    {
        return pred(i, b.i);
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Coord1<T>::any_test(Pred pred) const noexcept
    {
        return pred(i);
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Coord1<T>::any_test(const Coord1<T>& b, Pred pred) const noexcept
    {
        return pred(i, b.i);
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Coord1<T>::any_test(T b, Pred pred) const noexcept
    {
        return pred(i, b);
    }

    template <typename T>
        template <typename S>
    S&  Coord1<T>::stream(S&s) const
    {
        return s << "[" << i << "]";
    }

    ////////////////////////////////////////////////////////////////////////////

    template <typename T, typename U>
        requires is_arithmetic_v<T>
    constexpr Coord1<product_t<T,U>> operator*(T a, const Coord1<U>&b)
    {
        return { a*b.i };
    }

    template <typename T>
    AllComponents<Coord1<T>>   all(Coord1<T>& val)
    {
        return { val };
    }

    template <typename T>
    AllComponents<const Coord1<T>>   all(const Coord1<T>& val)
    {
        return { val };
    }
    
    template <typename T>
    AnyComponents<Coord1<T>>   any(Coord1<T>& val)
    {
        return { val };
    }
     
    template <typename T>
    AnyComponents<const Coord1<T>>   any(const Coord1<T>& val)
    {
        return { val };
    }

    template <typename T>
    constexpr Coord1<T> max(const Coord1<T>&a, const Coord1<T>& b)
    {
        return { 
            max(a.i, b.i)
        };
    }

    template <typename T>
    constexpr Coord1<T> min(const Coord1<T>&a, const Coord1<T>& b)
    {
        return { 
            min(a.i, b.i)
        };
    }

    template <typename T>
    constexpr T product(const Coord1<T>& a)
    {
        return a.i;
    }

    template <typename T>
    constexpr T sum(const Coord1<T>& a)
    {
        return a.i;
    }

    template <typename T>
    Stream& operator<<(Stream&s, const Coord1<T>& v)
    {
        return v.stream(s);
    }

    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const Coord1<T>& v)
    {
        return v.stream(s);
    }
}
