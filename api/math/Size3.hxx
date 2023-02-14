////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the size3 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <math/Size2.hpp>
#include <math/Size3.hpp>
#include <basic/Stream.hpp>
#include <basic/Logging.hpp>

namespace yq {
    template <typename T>
    constexpr Size3<T> Size3<T>::operator+() const noexcept
    {
        return *this;
    }

    template <typename T>
    constexpr Size3<T> Size3<T>::operator-() const noexcept
    {
        return Size3(-x, -y, -z );
    }
    
    template <typename T>
    constexpr Size3<T> Size3<T>::operator+(const Size3&b) const noexcept
    {
        return Size3(x+b.x, y+b.y, z+b.z );
    }

    template <typename T>
    Size3<T>& Size3<T>::operator+=(const Size3&b) noexcept
    {
        x += b.x;
        y += b.y;
        z += b.z;
        return *this;
    }

    template <typename T>
    constexpr Size3<T> Size3<T>::operator-(const Size3&b) const noexcept
    {
        return Size3(x-b.x, y-b.y, z-b.z);
    }

    template <typename T>
    Size3<T>& Size3<T>::operator-=(const Size3&b) noexcept
    {
        x -= b.x;
        y -= b.y;
        z -= b.z;
        return *this;
    }
    
    template <typename T>
    template <typename U>
    requires is_arithmetic_v<U>
    constexpr Size3<product_t<T,U>> Size3<T>::operator*(U b) const noexcept
    {
        return Size3<product_t<T,U>>( x*b, y*b, z*b );
    }
    
    template <typename T>
    template <typename U>
    requires (is_arithmetic_v<U> && self_mul_v<T,U>)
    Size3<T>& Size3<T>::operator*=(U b) noexcept
    {
        x *= b;
        y *= b;
        z *= b;
        return *this;
    }
    
    template <typename T>
    template <typename U>
    requires is_arithmetic_v<U>
    constexpr Size3<quotient_t<T,U>> Size3<T>::operator/(U b) const noexcept
    {
        return Size3<quotient_t<T,U>>( x/b, y/b, z/b );
    }
    
    template <typename T>
    template <typename U>
    requires (is_arithmetic_v<U> && self_div_v<T,U>)
    Size3<T>& Size3<T>::operator/=(U b) noexcept
    {
        x /= b;
        y /= b;
        z /= b;
        return *this;
    }


    template <typename T>
    constexpr T   Size3<T>::depth() const 
    { 
        return z; 
    }
    
    template <typename T>
    constexpr bool   Size3<T>::eclipses(const Size3<T>& small) const noexcept
    {
        return (x >= small.x) && (y >= small.y) && (z >= small.z );
    }

    template <typename T>
    constexpr T   Size3<T>::height() const 
    { 
        return y; 
    }

    template <typename T>
    constexpr cube_t<T> Size3<T>::volume() const noexcept
    {
        return x*y*z;
    }

    template <typename T>
    constexpr T   Size3<T>::width() const 
    { 
        return x; 
    }
    
    template <typename T>
    constexpr Size2<T>  Size3<T>::xy() const noexcept 
    { 
        return { x, y }; 
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    
    template <typename T, typename U>
    requires is_arithmetic_v<T,U>
    constexpr Size3<product_t<T,U>> operator*(T a, const Size3<U>& b) noexcept
    {
        return Size3<product_t<T,U>>(a*b.x, a*b.y, a*b.z);
    }

    //! Computes volume of the size
    template <typename T>
    constexpr auto    volume(const Size3<T>& size) noexcept
    {
        return size.volume();
    }

    template <typename S, typename T>
    S&  as_stream(S& s, const Size3<T>& v)
    {
        return s << "[" << v.x << "x" << v.y << "x" << v.z << "]";
    }
    
    template <typename T>
    Stream& operator<<(Stream&s, const Size3<T>& v)
    {
        return as_stream(s, v);
    }

    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const Size3<T>& v)
    {
        return as_stream(s, v);
    }
}
