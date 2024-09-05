////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq-toolbox/coord/Coord6.hpp>
#include <yq-toolbox/coord/Coord.hpp>

namespace yq {
    template <typename T>
    constexpr Coord6<T> Coord6<T>::operator+() const noexcept
    {
        return *this;
    }
    
    template <typename T>
    constexpr Coord6<T> Coord6<T>::operator-() const noexcept
    {
        return { -i, -j, -k, -l, -m, -n };
    }
    
    template <typename T>
    constexpr Coord6<T> Coord6<T>::operator+(const Coord6<T>&b) const noexcept
    {
        return { i+b.i, j+b.j, k+b.k, l+b.l, m+b.m, n+b.n };
    }

    template <typename T>
    constexpr Coord6<T> Coord6<T>::operator-(const Coord6<T>&b) const noexcept
    {
        return { i-b.i, j-b.j, k-b.k, l-b.l, m-b.m, n-b.n };
    }

    template <typename T>
    Coord6<T>& Coord6<T>::operator+=(const Coord6<T>& b) noexcept
    {
        i += b.i;
        j += b.j;
        k += b.k;
        l += b.l;
        m += b.m;
        n += b.n;
        return *this;
    }

    template <typename T>
    Coord6<T>& Coord6<T>::operator-=(const Coord6<T>& b) noexcept
    {
        i -= b.i;
        j -= b.j;
        k -= b.k;
        l -= b.l;
        m -= b.m;
        n -= b.n;
        return *this;
    }

    template <typename T>
        template <typename U>
            requires is_arithmetic_v<U>
    constexpr Coord6<product_t<T,U>> Coord6<T>::operator*(U b) const noexcept
    {
        return { i*b, j*b, k*b, l*b, m*b, n*b };
    }

    template <typename T>
        template <typename U>
            requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
    Coord6<T>& Coord6<T>::operator*=(U b) noexcept
    {
        i *= b;
        j *= b;
        k *= b;
        l *= b;
        m *= b;
        n *= b;
        return *this;
    }

    template <typename T>
        template <typename U>
    constexpr Coord6<product_t<T,U>> Coord6<T>::operator*(const Coord6<U>& b) const noexcept
    {
        return { i*b.i, j*b.j, k*b.k, l*b.l, m*b.m, n*b.n };
    }
    
    template <typename T>
        template <typename U>
            requires self_multiply_v<T,U>
    Coord6<T>& Coord6<T>::operator*=(const Coord6<U>& b) noexcept
    {
        i *= b.i;
        j *= b.j;
        k *= b.k;
        l *= b.l;
        m *= b.m;
        n *= b.n;
        return *this;
    }

    template <typename T>
        template <typename U>
            requires is_arithmetic_v<U>
    constexpr Coord6<quotient_t<T,U>> Coord6<T>::operator/(U b) const noexcept
    {
        return { i/b, j/b, k/b, l/b, m/b, n/b };
    }

    template <typename T>
        template <typename U>
            requires (is_arithmetic_v<U> && self_divide_v<T,U>)
    Coord6<T>& Coord6<T>::operator/=(U b) noexcept
    {
        i /= b;
        j /= b;
        k /= b;
        l /= b;
        m /= b;
        n /= b;
        return *this;
    }

    template <typename T>
        template <typename U>
    constexpr Coord6<quotient_t<T,U>> Coord6<T>::operator/(const Coord6<U>& b) const noexcept
    {
        return { i/b.i, j/b.j, k/b.k, l/b.l, m/b.m, n/b.n };
    }

    template <typename T>
        template <typename U>
            requires self_divide_v<T,U>
    Coord6<T>& Coord6<T>::operator/=(const Coord6<U>& b) noexcept
    {
        i /= b.i;
        j /= b.j;
        k /= b.k;
        l /= b.l;
        m /= b.m;
        n /= b.n;
        return *this;
    }

    template <typename T>
        template <typename S>
    S&  Coord6<T>::stream(S&s) const
    {
        return s << "[" << i << "," << j << "," << k << "," << l << "," << m << "," << n << "]";
    }
        
    ////////////////////////////////////////////////////////////////////////////

    template <typename T, typename U>
        requires is_arithmetic_v<T>
    constexpr Coord6<product_t<T,U>> operator*(T a, const Coord6<U>&b)
    {
        return { a*b.i, a*b.j, a*b.k, a*b.l, a*b.m, a*b.n };
    }

    template <typename T>
    constexpr Coord6<T> max(const Coord6<T>&a, const Coord6<T>& b)
    {
        return { 
            max(a.i, b.i), 
            max(a.j, b.j), 
            max(a.k, b.k), 
            max(a.l, b.l), 
            max(a.m, b.m), 
            max(a.n, b.n)
        };
    }

    template <typename T>
    constexpr Coord6<T> min(const Coord6<T>&a, const Coord6<T>& b)
    {
        return { 
            min(a.i, b.i), 
            min(a.j, b.j), 
            min(a.k, b.k), 
            min(a.l, b.l), 
            min(a.m, b.m), 
            min(a.n, b.n)
        };
    }

    template <typename T>
    constexpr auto product(const Coord6<T>& a)
    {
        return a.i*a.j*a.k*a.l*a.m*a.n;
    }

    template <typename T>
    constexpr T sum(const Coord6<T>& a)
    {
        return a.i+a.j+a.k+a.l+a.m+a.n;
    }
    
    template <typename T>
    Stream& operator<<(Stream&s, const Coord6<T>& v)
    {
        return v.stream(s);
    }

    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const Coord6<T>& v)
    {
        return v.stream(s);
    }
}
