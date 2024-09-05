////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq-toolbox/coord/Coord2.hpp>
#include <yq-toolbox/coord/Coord.hpp>

namespace yq {
    template <typename T>
    constexpr Coord2<T> Coord2<T>::operator+() const noexcept
    {
        return *this;
    }
    
    template <typename T>
    constexpr Coord2<T> Coord2<T>::operator-() const noexcept
    {
        return { -i, -j };
    }

    template <typename T>
    constexpr Coord2<T> Coord2<T>::operator+(const Coord2<T>&b) const noexcept
    {
        return { i+b.i, j+b.j };
    }

    template <typename T>
    constexpr Coord2<T> Coord2<T>::operator-(const Coord2<T>&b) const noexcept
    {
        return { i-b.i, j-b.j };
    }

    template <typename T>
    Coord2<T>& Coord2<T>::operator+=(const Coord2<T>& b) noexcept
    {
        i += b.i;
        j += b.j;
        return *this;
    }

    template <typename T>
    Coord2<T>& Coord2<T>::operator-=(const Coord2<T>& b) noexcept
    {
        i -= b.i;
        j -= b.j;
        return *this;
    }

    template <typename T>
        template <typename U>
            requires is_arithmetic_v<U>
    constexpr Coord2<product_t<T,U>> Coord2<T>::operator*(U b) const noexcept
    {
        return { i*b, j*b };
    }

    template <typename T>
        template <typename U>
            requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
    Coord2<T>& Coord2<T>::operator*=(U b) noexcept
    {
        i *= b;
        j *= b;
        return *this;
    }

    template <typename T>
        template <typename U>
    constexpr Coord2<product_t<T,U>> Coord2<T>::operator*(const Coord2<U>& b) const noexcept
    {
        return { i*b.i, j*b.j };
    }
    
    template <typename T>
        template <typename U>
            requires self_multiply_v<T,U>
    Coord2<T>& Coord2<T>::operator*=(const Coord2<U>& b) noexcept
    {
        i *= b.i;
        j *= b.j;
        return *this;
    }

    template <typename T>
        template <typename U>
            requires is_arithmetic_v<U>
    constexpr Coord2<quotient_t<T,U>> Coord2<T>::operator/(U b) const noexcept
    {
        return { i/b, j/b };
    }

    template <typename T>
        template <typename U>
            requires (is_arithmetic_v<U> && self_divide_v<T,U>)
    Coord2<T>& Coord2<T>::operator/=(U b) noexcept
    {
        i /= b;
        j /= b;
        return *this;
    }

    template <typename T>
        template <typename U>
    constexpr Coord2<quotient_t<T,U>> Coord2<T>::operator/(const Coord2<U>& b) const noexcept
    {
        return { i/b.i, j/b.j };
    }

    template <typename T>
        template <typename U>
            requires self_divide_v<T,U>
    Coord2<T>& Coord2<T>::operator/=(const Coord2<U>& b) noexcept
    {
        i /= b.i;
        j /= b.j;
        return *this;
    }

    template <typename T>
        template <typename S>
    S&  Coord2<T>::stream(S&s) const
    {
        return s << "[" << i << "," << j << "]";
    }

    ////////////////////////////////////////////////////////////////////////////

    template <typename T, typename U>
        requires is_arithmetic_v<T>
    constexpr Coord2<product_t<T,U>> operator*(T a, const Coord2<U>&b)
    {
        return { a*b.i, a*b.j };
    }

    template <typename T>
    constexpr Coord2<T> max(const Coord2<T>&a, const Coord2<T>& b)
    {
        return { 
            max(a.i, b.i), 
            max(a.j, b.j)
        };
    }

    template <typename T>
    constexpr Coord2<T> min(const Coord2<T>&a, const Coord2<T>& b)
    {
        return { 
            min(a.i, b.i), 
            min(a.j, b.j)
        };
    }

    template <typename T>
    constexpr auto product(const Coord2<T>& a)
    {
        return a.i*a.j;
    }

    template <typename T>
    constexpr T sum(const Coord2<T>& a)
    {
        return a.i+a.j;
    }

    template <typename T>
    Stream& operator<<(Stream&s, const Coord2<T>& v)
    {
        return v.stream(s);
    }

    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const Coord2<T>& v)
    {
        return v.stream(s);
    }
}
