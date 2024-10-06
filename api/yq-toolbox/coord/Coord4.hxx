////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq-toolbox/coord/Coord4.hpp>
#include <yq-toolbox/coord/Coord.hpp>
#include <yq-toolbox/math/AllComponents.hpp>
#include <yq-toolbox/math/AnyComponents.hpp>

namespace yq {
    template <typename T>
    constexpr Coord4<T> Coord4<T>::operator+() const noexcept
    {
        return *this;
    }
    
    template <typename T>
    constexpr Coord4<T> Coord4<T>::operator-() const noexcept
    {
        return { -i, -j, -k, -l };
    }

    template <typename T>
    constexpr Coord4<T> Coord4<T>::operator+(const Coord4<T>&b) const noexcept
    {
        return { i+b.i, j+b.j, k+b.k, l+b.l };
    }

    template <typename T>
    constexpr Coord4<T> Coord4<T>::operator-(const Coord4<T>&b) const noexcept
    {
        return { i-b.i, j-b.j, k-b.k, l-b.l };
    }

    template <typename T>
    Coord4<T>& Coord4<T>::operator+=(const Coord4<T>& b) noexcept
    {
        i += b.i;
        j += b.j;
        k += b.k;
        l += b.l;
        return *this;
    }

    template <typename T>
    Coord4<T>& Coord4<T>::operator-=(const Coord4<T>& b) noexcept
    {
        i -= b.i;
        j -= b.j;
        k -= b.k;
        l -= b.l;
        return *this;
    }

    template <typename T>
        template <typename U>
            requires is_arithmetic_v<U>
    constexpr Coord4<product_t<T,U>> Coord4<T>::operator*(U b) const noexcept
    {
        return { i*b, j*b, k*b, l*b };
    }

    template <typename T>
        template <typename U>
            requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
    Coord4<T>& Coord4<T>::operator*=(U b) noexcept
    {
        i *= b;
        j *= b;
        k *= b;
        l *= b;
        return *this;
    }

    template <typename T>
        template <typename U>
    constexpr Coord4<product_t<T,U>> Coord4<T>::operator*(const Coord4<U>& b) const noexcept
    {
        return { i*b.i, j*b.j, k*b.k, l*b.l };
    }
    
    template <typename T>
        template <typename U>
            requires self_multiply_v<T,U>
    Coord4<T>& Coord4<T>::operator*=(const Coord4<U>& b) noexcept
    {
        i *= b.i;
        j *= b.j;
        k *= b.k;
        l *= b.l;
        return *this;
    }

    template <typename T>
        template <typename U>
            requires is_arithmetic_v<U>
    constexpr Coord4<quotient_t<T,U>> Coord4<T>::operator/(U b) const noexcept
    {
        return { i/b, j/b, k/b, l/b };
    }

    template <typename T>
        template <typename U>
            requires (is_arithmetic_v<U> && self_divide_v<T,U>)
    Coord4<T>& Coord4<T>::operator/=(U b) noexcept
    {
        i /= b;
        j /= b;
        k /= b;
        l /= b;
        return *this;
    }

    template <typename T>
        template <typename U>
    constexpr Coord4<quotient_t<T,U>> Coord4<T>::operator/(const Coord4<U>& b) const noexcept
    {
        return { i/b.i, j/b.j, k/b.k, l/b.l };
    }

    template <typename T>
        template <typename U>
            requires self_divide_v<T,U>
    Coord4<T>& Coord4<T>::operator/=(const Coord4<U>& b) noexcept
    {
        i /= b.i;
        j /= b.j;
        k /= b.k;
        l /= b.l;
        return *this;
    }

    template <typename T>
    constexpr Coord4<T> Coord4<T>::all_add(T b) const noexcept
    {
        return Coord4( i+b, j+b, k+b, l+b );
    }

    template <typename T>
    Coord4<T>&    Coord4<T>::all_decrement(T b) noexcept
    {
        i -= b;
        j -= b;
        k -= b;
        l -= b;
        return *this;
    }

    template <typename T>
    Coord4<T>&    Coord4<T>::all_increment(T b) noexcept
    {
        i += b;
        j += b;
        k += b;
        l += b;
        return *this;
    }
    
    template <typename T>
    constexpr Coord4<T> Coord4<T>::all_subtract(T b) const noexcept
    {
        return Coord4( i-b, j-b, k-b, l-b );
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Coord4<T>::all_test(Pred pred) const noexcept
    {
        return pred(i) && pred(j) && pred(k) && pred(l);
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Coord4<T>::all_test(T b, Pred pred) const noexcept
    {
        return pred(i, b) && pred(j, b) && pred(k, b) && pred(l, b);
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Coord4<T>::all_test(const Coord4<T>& b, Pred pred) const noexcept
    {
        return pred(i, b.i) && pred(j, b.j) && pred(k, b.k) && pred(l, b.l);
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Coord4<T>::any_test(Pred pred) const noexcept
    {
        return pred(i) || pred(j) || pred(k) || pred(l);
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Coord4<T>::any_test(const Coord4<T>& b, Pred pred) const noexcept
    {
        return pred(i, b.i) || pred(j, b.j) || pred(k, b.k) || pred(l, b.l);
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Coord4<T>::any_test(T b, Pred pred) const noexcept
    {
        return pred(i, b) || pred(j, b) || pred(k, b) || pred(l, b);
    }
    
    template <typename T>
        template <typename S>
    S&  Coord4<T>::stream(S&s) const
    {
        return s << "[" << i << "," << j << "," << k << "," << l << "]";
    }

    ////////////////////////////////////////////////////////////////////////////

    template <typename T, typename U>
        requires is_arithmetic_v<T>
    constexpr Coord4<product_t<T,U>> operator*(T a, const Coord4<U>&b)
    {
        return { a*b.i, a*b.j, a*b.k, a*b.l };
    }

    template <typename T>
    AllComponents<Coord4<T>>   all(Coord4<T>& val)
    {
        return { val };
    }

    template <typename T>
    AllComponents<const Coord4<T>>   all(const Coord4<T>& val)
    {
        return { val };
    }
    
    template <typename T>
    AnyComponents<Coord4<T>>   any(Coord4<T>& val)
    {
        return { val };
    }
     
    template <typename T>
    AnyComponents<const Coord4<T>>   any(const Coord4<T>& val)
    {
        return { val };
    }

    template <typename T>
    constexpr Coord4<T> max(const Coord4<T>&a, const Coord4<T>& b)
    {
        return { 
            max(a.i, b.i), 
            max(a.j, b.j), 
            max(a.k, b.k), 
            max(a.l, b.l)
        };
    }

    template <typename T>
    constexpr Coord4<T> min(const Coord4<T>&a, const Coord4<T>& b)
    {
        return { 
            min(a.i, b.i), 
            min(a.j, b.j), 
            min(a.k, b.k), 
            min(a.l, b.l)
        };
    }

    template <typename T>
    constexpr auto product(const Coord4<T>& a)
    {
        return a.i*a.j*a.k*a.l;
    }

    template <typename T>
    constexpr T sum(const Coord4<T>& a)
    {
        return a.i+a.j+a.k+a.l;
    }

    template <typename T>
    Stream& operator<<(Stream&s, const Coord4<T>& v)
    {
        return v.stream(s);
    }

    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const Coord4<T>& v)
    {
        return v.stream(s);
    }
}
