////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/coord/Coord6.hpp>
#include <yq/coord/Coord.hpp>
#include <yq/math/AllComponents.hpp>
#include <yq/math/AnyComponents.hpp>

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
    constexpr Coord6<T> Coord6<T>::all_add(T b) const noexcept
    {
        return Coord6( i+b, j+b, k+b, l+b, m+b, n+b );
    }

    template <typename T>
    Coord6<T>&    Coord6<T>::all_decrement(T b) noexcept
    {
        i -= b;
        j -= b;
        k -= b;
        l -= b;
        m -= b;
        n -= b;
        return *this;
    }

    template <typename T>
    Coord6<T>&    Coord6<T>::all_increment(T b) noexcept
    {
        i += b;
        j += b;
        k += b;
        l += b;
        m += b;
        n += b;
        return *this;
    }
    
    template <typename T>
    constexpr Coord6<T> Coord6<T>::all_subtract(T b) const noexcept
    {
        return Coord6( i-b, j-b, k-b, l-b, m-b, n-b );
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Coord6<T>::all_test(Pred pred) const noexcept
    {
        return pred(i) && pred(j) && pred(k) && pred(l) && pred(m) && pred(n);
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Coord6<T>::all_test(T b, Pred pred) const noexcept
    {
        return pred(i, b) && pred(j, b) && pred(k, b) && pred(l, b) && pred(m, b) && pred(n, b);
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Coord6<T>::all_test(const Coord6<T>& b, Pred pred) const noexcept
    {
        return pred(i, b.i) && pred(j, b.j) && pred(k, b.k) && pred(l, b.l) && pred(m, b.m) && pred(n, b.n);
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Coord6<T>::any_test(Pred pred) const noexcept
    {
        return pred(i) || pred(j) || pred(k) || pred(l) || pred(m) || pred(n);
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Coord6<T>::any_test(const Coord6<T>& b, Pred pred) const noexcept
    {
        return pred(i, b.i) || pred(j, b.j) || pred(k, b.k) || pred(l, b.l) || pred(m, b.m) || pred(n, b.n);
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Coord6<T>::any_test(T b, Pred pred) const noexcept
    {
        return pred(i, b) || pred(j, b) || pred(k, b) || pred(l, b) || pred(m, b) || pred(n, b);
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
    AllComponents<Coord6<T>>   all(Coord6<T>& val)
    {
        return { val };
    }

    template <typename T>
    AllComponents<const Coord6<T>>   all(const Coord6<T>& val)
    {
        return { val };
    }
    
    template <typename T>
    AnyComponents<Coord6<T>>   any(Coord6<T>& val)
    {
        return { val };
    }
     
    template <typename T>
    AnyComponents<const Coord6<T>>   any(const Coord6<T>& val)
    {
        return { val };
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
