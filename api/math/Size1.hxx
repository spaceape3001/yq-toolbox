////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the size1 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <math/Size1.hpp>
#include <math/Vector1.hpp>
#include <basic/Stream.hpp>
#include <basic/Logging.hpp>


namespace yq {

    template <typename T>
    constexpr Size1<T>::Size1(const Vector1<T>&v) noexcept : Size1(v.x) 
    {
    }
    
    template <typename T>
    constexpr Size1<T> Size1<T>::operator+() const noexcept
    {
        return *this;
    }

    template <typename T>
    constexpr Size1<T> Size1<T>::operator-() const noexcept
    {
        return Size1(-x);
    }
    
    template <typename T>
    constexpr Size1<T> Size1<T>::operator+(const Size1&b) const noexcept
    {
        return Size1(x+b.x);
    }

    template <typename T>
    Size1<T>& Size1<T>::operator+=(const Size1&b) noexcept
    {
        x += b.x;
        return *this;
    }

    template <typename T>
    constexpr Size1<T> Size1<T>::operator-(const Size1&b) const noexcept
    {
        return Size1(x-b.x);
    }

    template <typename T>
    Size1<T>& Size1<T>::operator-=(const Size1&b) noexcept
    {
        x -= b.x;
        return *this;
    }
    
    template <typename T>
    template <typename U>
    requires is_arithmetic_v<U>
    constexpr Size1<product_t<T,U>> Size1<T>::operator*(U b) const noexcept
    {
        return Size1<product_t<T,U>>( x*b );
    }
    
    template <typename T>
    template <typename U>
    requires (is_arithmetic_v<U> && self_mul_v<T,U>)
    Size1<T>& Size1<T>::operator*=(U b) noexcept
    {
        x *= b;
        return *this;
    }
    
    template <typename T>
    template <typename U>
    requires is_arithmetic_v<U>
    constexpr Size1<quotient_t<T,U>> Size1<T>::operator/(U b) const noexcept
    {
        return Size1<quotient_t<T,U>>( x/b );
    }
    
    template <typename T>
    template <typename U>
    requires (is_arithmetic_v<U> && self_div_v<T,U>)
    Size1<T>& Size1<T>::operator/=(U b) noexcept
    {
        x /= b;
        return *this;
    }


    template <typename T>
    constexpr Size1<T> Size1<T>::all_add(T b) const noexcept
    {
        return Size1( x+b );
    }
    
    template <typename T>
    constexpr Size1<T> Size1<T>::all_subtract(T b) const noexcept
    {
        return Size1( x-b );
    }

    template <typename T>
    constexpr T     Size1<T>::cmax() const noexcept
    {
        return x;
    }

    template <typename T>
    constexpr T     Size1<T>::cmin() const noexcept
    {
        return x;
    }

    template <typename T>
    constexpr bool  Size1<T>::contains(const Size1& small) const noexcept
    {
        return all(*this) >= small;
    }
    
    template <typename T>
    constexpr T   Size1<T>::cproduct() const noexcept
    {
        return x;
    }

    template <typename T>
    constexpr T             Size1<T>::csum() const noexcept
    {
        return x;
    }

    template <typename T>
    constexpr Size1<T>   Size1<T>::eabs() const noexcept
    {
        return Size1( abs(x)  );
    }

    template <typename T>
    constexpr bool  Size1<T>::eclipses(const Size1& small) const noexcept
    {
        return all(*this) >= small;
    }

    template <typename T>
        template <typename U>
    constexpr Size1<quotient_t<T,U>>  Size1<T>::ediv(const Size1<U>&b) const noexcept
    {
        return Size1<quotient_t<T,U>>(x/b.x );
    }

    template <typename T>
    constexpr Size1<T>   Size1<T>::emax(const Size1&b) const noexcept
    {
        return Size1(max(x, b.x));
    }
    
    template <typename T>
    constexpr Size1<T>   Size1<T>::emin(const Size1&b) const noexcept
    {
        return Size1(min(x, b.x));
    }

    template <typename T>
        template <typename U>
    constexpr Size1<product_t<T,U>>   Size1<T>::emul(const Size1<U>&b) const noexcept
    {
        return {x*b.x};
    }

    template <typename T>
    constexpr T         Size1<T>::length() const noexcept 
    { 
        return x; 
    }

    template <typename T>
    constexpr T         Size1<T>::width() const 
    { 
        return x; 
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename S, typename T>
    S&  as_stream(S& s, const Size1<T>& v)
    {
        return s << "[" << v.x << "]";
    }
    
    /*! \brief Streams to a stream
    */
    template <typename T>
    Stream& operator<<(Stream&s, const Size1<T>& v)
    {
        return as_stream(s, v);
    }

    /*! \brief Streams to to a logging stream
    */
    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const Size1<T>& v)
    {
        return as_stream(s, v);
    }
}
