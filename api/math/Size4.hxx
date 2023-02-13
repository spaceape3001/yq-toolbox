////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the size4 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <math/Size4.hpp>
#include <basic/Stream.hpp>
#include <basic/Logging.hpp>

namespace yq {
    template <typename T>
    constexpr Size4<T> Size4<T>::operator+() const noexcept
    {
        return *this;
    }

    template <typename T>
    constexpr Size4<T> Size4<T>::operator-() const noexcept
    {
        return Size4(-x, -y, -z, -w);
    }
    
    template <typename T>
    constexpr Size4<T> Size4<T>::operator+(const Size4&b) const noexcept
    {
        return Size4(x+b.x, y+b.y, z+b.z, w+b.w);
    }

    template <typename T>
    Size4<T>& Size4<T>::operator+=(const Size4&b) noexcept
    {
        x += b.x;
        y += b.y;
        z += b.z;
        w += b.w;
        return *this;
    }

    template <typename T>
    constexpr Size4<T> Size4<T>::operator-(const Size4&b) const noexcept
    {
        return Size4(x-b.x, y-b.y, z-b.z, w-b.w);
    }

    template <typename T>
    Size4<T>& Size4<T>::operator-=(const Size4&b) noexcept
    {
        x -= b.x;
        y -= b.y;
        z -= b.z;
        w -= b.w;
        return *this;
    }
    
    template <typename T>
    template <typename U>
    requires is_arithmetic_v<U>
    constexpr Size4<product_t<T,U>> Size4<T>::operator*(U b) const noexcept
    {
        return Size4<product_t<T,U>>( x*b, y*b, z*b, w*b );
    }
    
    template <typename T>
    template <typename U>
    requires (is_arithmetic_v<U> && self_mul_v<T,U>)
    Size4<T>& Size4<T>::operator*=(U b) noexcept
    {
        x *= b;
        y *= b;
        z *= b;
        w *= b;
        return *this;
    }
    
    template <typename T>
    template <typename U>
    requires is_arithmetic_v<U>
    constexpr Size4<quotient_t<T,U>> Size4<T>::operator/(U b) const noexcept
    {
        return Size4<quotient_t<T,U>>( x/b, y/b, z/b, w/b );
    }
    
    template <typename T>
    template <typename U>
    requires (is_arithmetic_v<U> && self_div_v<T,U>)
    Size4<T>& Size4<T>::operator/=(U b) noexcept
    {
        x /= b;
        y /= b;
        z /= b;
        w /= b;
        return *this;
    }

    template <typename T>
    constexpr T   Size4<T>::duration() const 
    { 
        return w; 
    }

    template <typename T>
    constexpr T   Size4<T>::depth() const 
    { 
        return z; 
    }
    
    template <typename T>
    constexpr bool   Size4<T>::eclipses(const Size4<T>& small) const noexcept
    {
        return (x >= small.x) && (y >= small.y) && (z >= small.z );
    }

    template <typename T>
    constexpr T   Size4<T>::height() const 
    { 
        return y; 
    }

    template <typename T>
    constexpr fourth_t<T> Size4<T>::hypervolume() const noexcept
    {
        return x*y*z*w;
    }

    template <typename T>
    constexpr T   Size4<T>::width() const 
    { 
        return x; 
    }
    
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    
    //! Computes volume of the size
    template <typename T>
    constexpr auto    hypervolume(const Size4<T>& size) noexcept
    {
        return size.hypervolume();
    }

    template <typename S, typename T>
    S&  as_stream(S& s, const Size4<T>& v)
    {
        return s << "[" << v.x << "x" << v.y << "x" << v.z << "x" << v.w << "]";
    }
    
    template <typename T>
    Stream& operator<<(Stream&s, const Size4<T>& v)
    {
        return as_stream(s, v);
    }

    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const Size4<T>& v)
    {
        return as_stream(s, v);
    }
}
