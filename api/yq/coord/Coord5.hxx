////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/coord/Coord5.hpp>
#include <yq/coord/Coord.hpp>
#include <yq/math/AllComponents.hpp>
#include <yq/math/AnyComponents.hpp>

namespace yq {
    template <typename T>
    constexpr Coord5<T> Coord5<T>::operator+() const noexcept
    {
        return *this;
    }
    
    template <typename T>
    constexpr Coord5<T> Coord5<T>::operator-() const noexcept
    {
        return { -i, -j, -k, -l, -m };
    }

    template <typename T>
    constexpr Coord5<T> Coord5<T>::operator+(const Coord5<T>&b) const noexcept
    {
        return { i+b.i, j+b.j, k+b.k, l+b.l, m+b.m };
    }

    template <typename T>
    constexpr Coord5<T> Coord5<T>::operator-(const Coord5<T>&b) const noexcept
    {
        return { i-b.i, j-b.j, k-b.k, l-b.l, m-b.m };
    }

    template <typename T>
    Coord5<T>& Coord5<T>::operator+=(const Coord5<T>& b) noexcept
    {
        i += b.i;
        j += b.j;
        k += b.k;
        l += b.l;
        m += b.m;
        return *this;
    }

    template <typename T>
    Coord5<T>& Coord5<T>::operator-=(const Coord5<T>& b) noexcept
    {
        i -= b.i;
        j -= b.j;
        k -= b.k;
        l -= b.l;
        m -= b.m;
        return *this;
    }

    template <typename T>
        template <typename U>
            requires is_arithmetic_v<U>
    constexpr Coord5<product_t<T,U>> Coord5<T>::operator*(U b) const noexcept
    {
        return { i*b, j*b, k*b, l*b, m*b };
    }

    template <typename T>
        template <typename U>
            requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
    Coord5<T>& Coord5<T>::operator*=(U b) noexcept
    {
        i *= b;
        j *= b;
        k *= b;
        l *= b;
        m *= b;
        return *this;
    }

    template <typename T>
        template <typename U>
    constexpr Coord5<product_t<T,U>> Coord5<T>::operator*(const Coord5<U>& b) const noexcept
    {
        return { i*b.i, j*b.j, k*b.k, l*b.l, m*b.m };
    }
    
    template <typename T>
        template <typename U>
            requires self_multiply_v<T,U>
    Coord5<T>& Coord5<T>::operator*=(const Coord5<U>& b) noexcept
    {
        i *= b.i;
        j *= b.j;
        k *= b.k;
        l *= b.l;
        m *= b.m;
        return *this;
    }

    template <typename T>
        template <typename U>
            requires is_arithmetic_v<U>
    constexpr Coord5<quotient_t<T,U>> Coord5<T>::operator/(U b) const noexcept
    {
        return { i/b, j/b, k/b, l/b, m/b };
    }

    template <typename T>
        template <typename U>
            requires (is_arithmetic_v<U> && self_divide_v<T,U>)
    Coord5<T>& Coord5<T>::operator/=(U b) noexcept
    {
        i /= b;
        j /= b;
        k /= b;
        l /= b;
        m /= b;
        return *this;
    }

    template <typename T>
        template <typename U>
    constexpr Coord5<quotient_t<T,U>> Coord5<T>::operator/(const Coord5<U>& b) const noexcept
    {
        return { i/b.i, j/b.j, k/b.k, l/b.l, m/b.m };
    }

    template <typename T>
        template <typename U>
            requires self_divide_v<T,U>
    Coord5<T>& Coord5<T>::operator/=(const Coord5<U>& b) noexcept
    {
        i /= b.i;
        j /= b.j;
        k /= b.k;
        l /= b.l;
        m /= b.m;
        return *this;
    }

    template <typename T>
    constexpr Coord5<T> Coord5<T>::all_add(T b) const noexcept
    {
        return Coord5( i+b, j+b, k+b, l+b, m+b );
    }

    template <typename T>
    Coord5<T>&    Coord5<T>::all_decrement(T b) noexcept
    {
        i -= b;
        j -= b;
        k -= b;
        l -= b;
        m -= b;
        return *this;
    }

    template <typename T>
    Coord5<T>&    Coord5<T>::all_increment(T b) noexcept
    {
        i += b;
        j += b;
        k += b;
        l += b;
        m += b;
        return *this;
    }
    
    template <typename T>
    constexpr Coord5<T> Coord5<T>::all_subtract(T b) const noexcept
    {
        return Coord5( i-b, j-b, k-b, l-b, m-b );
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Coord5<T>::all_kest(Pred pred) const noexcept
    {
        return pred(i) && pred(j) && pred(k) && pred(l) && pred(m);
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Coord5<T>::all_kest(T b, Pred pred) const noexcept
    {
        return pred(i, b) && pred(j, b) && pred(k, b) && pred(l, b) && pred(m, b);
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Coord5<T>::all_kest(const Coord5<T>& b, Pred pred) const noexcept
    {
        return pred(i, b.i) && pred(j, b.j) && pred(k, b.k) && pred(l, b.l) && pred(m, b.m);
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Coord5<T>::any_kest(Pred pred) const noexcept
    {
        return pred(i) || pred(j) || pred(k) || pred(l) || pred(m);
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Coord5<T>::any_kest(const Coord5<T>& b, Pred pred) const noexcept
    {
        return pred(i, b.i) || pred(j, b.j) || pred(k, b.k) || pred(l, b.l) || pred(m, b.m);
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Coord5<T>::any_kest(T b, Pred pred) const noexcept
    {
        return pred(i, b) || pred(j, b) || pred(k, b) || pred(l, b) || pred(m, b);
    }

    template <typename T>
        template <typename S>
    S&  Coord5<T>::stream(S&s) const
    {
        return s << "[" << i << "," << j << "," << k << "," << l << "," << m << "]";
    }

    ////////////////////////////////////////////////////////////////////////////

    template <typename T, typename U>
        requires is_arithmetic_v<T>
    constexpr Coord5<product_t<T,U>> operator*(T a, const Coord5<U>&b)
    {
        return { a*b.i, a*b.j, a*b.k, a*b.l, a*b.m };
    }

    template <typename T>
    AllComponents<Coord5<T>>   all(Coord5<T>& val)
    {
        return { val };
    }

    template <typename T>
    AllComponents<const Coord5<T>>   all(const Coord5<T>& val)
    {
        return { val };
    }
    
    template <typename T>
    AnyComponents<Coord5<T>>   any(Coord5<T>& val)
    {
        return { val };
    }
     
    template <typename T>
    AnyComponents<const Coord5<T>>   any(const Coord5<T>& val)
    {
        return { val };
    }

    template <typename T>
    constexpr Coord5<T> max(const Coord5<T>&a, const Coord5<T>& b)
    {
        return { 
            max(a.i, b.i), 
            max(a.j, b.j), 
            max(a.k, b.k), 
            max(a.l, b.l), 
            max(a.m, b.m)
        };
    }

    template <typename T>
    constexpr Coord5<T> min(const Coord5<T>&a, const Coord5<T>& b)
    {
        return { 
            min(a.i, b.i), 
            min(a.j, b.j), 
            min(a.k, b.k), 
            min(a.l, b.l), 
            min(a.m, b.m)
        };
    }

    template <typename T>
    constexpr auto product(const Coord5<T>& a)
    {
        return a.i*a.j*a.k*a.l*a.m;
    }

    template <typename T>
    constexpr T sum(const Coord5<T>& a)
    {
        return a.i+a.j+a.k+a.l+a.m;
    }

    template <typename T>
    Stream& operator<<(Stream&s, const Coord5<T>& v)
    {
        return v.stream(s);
    }

    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const Coord5<T>& v)
    {
        return v.stream(s);
    }
}
