////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once


/* 
    This is the template IMPLEMENTATION of the size2 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <math/Size2.hpp>
#include <basic/Stream.hpp>
#include <basic/Logging.hpp>

namespace yq {

    template <typename T>
    constexpr Size2<T> Size2<T>::operator+() const noexcept
    {
        return *this;
    }

    template <typename T>
    constexpr Size2<T> Size2<T>::operator-() const noexcept
    {
        return Size2(-x, -y);
    }
    
    template <typename T>
    constexpr Size2<T> Size2<T>::operator+(const Size2&b) const noexcept
    {
        return Size2(x+b.x, y+b.y);
    }

    template <typename T>
    Size2<T>& Size2<T>::operator+=(const Size2&b) noexcept
    {
        x += b.x;
        y += b.y;
        return *this;
    }

    template <typename T>
    constexpr Size2<T> Size2<T>::operator-(const Size2&b) const noexcept
    {
        return Size2(x-b.x, y-b.y);
    }

    template <typename T>
    Size2<T>& Size2<T>::operator-=(const Size2&b) noexcept
    {
        x -= b.x;
        y -= b.y;
        return *this;
    }
    
    template <typename T>
    template <typename U>
    requires is_arithmetic_v<U>
    constexpr Size2<product_t<T,U>> Size2<T>::operator*(U b) const noexcept
    {
        return Size2<product_t<T,U>>( x*b, y*b );
    }
    
    template <typename T>
    template <typename U>
    requires (is_arithmetic_v<U> && self_mul_v<T,U>)
    Size2<T>& Size2<T>::operator*=(U b) noexcept
    {
        x *= b;
        y *= b;
        return *this;
    }
    
    template <typename T>
    template <typename U>
    requires is_arithmetic_v<U>
    constexpr Size2<quotient_t<T,U>> Size2<T>::operator/(U b) const noexcept
    {
        return Size2<quotient_t<T,U>>( x/b, y/b );
    }
    
    template <typename T>
    template <typename U>
    requires (is_arithmetic_v<U> && self_div_v<T,U>)
    Size2<T>& Size2<T>::operator/=(U b) noexcept
    {
        x /= b;
        y /= b;
        return *this;
    }

    template <typename T>
    constexpr square_t<T> Size2<T>::area() const noexcept
    {
        return x*y;
    }

    template <typename T>
    bool                Size2<T>::eclipses(const Size2& b) const noexcept
    {
        return (x >= b.x) && (y >= b.y);
    }
    
    template <typename T>
    constexpr T         Size2<T>::height() const noexcept 
    { 
        return y; 
    }

    template <typename T>
    constexpr T         Size2<T>::width() const noexcept 
    { 
        return x; 
    }

    template <typename T>
    Size2<T>            Size2<T>::shrink_to_fit(const Size2& frame) const
    {
        using sq_t  = decltype(T()*T());
        
        //  --------------------------------------
        //  Check for reasons to not do the math...
    
        if(frame.eclipses(*this))           // we already fit
            return *this;
        if(frame.area() == zero_v<sq_t>)     // frame is bogus
            return *this;
        if(area() == zero_v<sq_t>)    // dims is bogus
            return *this;

        /*
            The relative "shrink" factor in each dimension
            
            fx = dims.x / frame.x
            fy = dims.y / frame.y
            
            And the greater one dictates which axis is held constant 
            while the other is shrunk by the same amount.  However
            the above would decimate precision with integer numbers,
            therefore we need to rewrite the conditional to avoid.
            
            dims.y      dims.x
            -------  > --------
            frame.y     frame.x
            
            dims.y * frame.x > dim.x * frame.y
            
            Still have the issue of integer overflow... 
            address that later if that becomes a concern.
        */
        
        if(y*frame.x > x*frame.y){
            return Size2<T>{ (x * frame.y)/y , frame.y };
        } else {
            return Size2<T>{ frame.x, (y*frame.x)/x };
        }
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    
    template <typename T, typename U>
    requires is_arithmetic_v<T,U>
    constexpr Size2<product_t<T,U>> operator*(T a, const Size2<U>& b) noexcept
    {
        return Size2<product_t<T,U>>(a*b.x, a*b.y);
    }

    template <typename T>
    constexpr auto    area(const Size2<T>& sz) noexcept
    {
        return sz.x*sz.y;
    }
    
    template <typename T>
    Size2<T>  shrink_to_fit_within(const Size2<T>& dims, const Size2<T>& frame)
    {
        return dims.shrink_to_fit(frame);
        
    }
    
    template <typename S, typename T>
    S&  as_stream(S& s, const Size2<T>& v)
    {
        return s << "[" << v.x << "x" << v.y << "]";
    }
    
    template <typename T>
    Stream& operator<<(Stream&s, const Size2<T>& v)
    {
        return as_stream(s, v);
    }

    /*! \brief Streams to to a logging stream
    */
    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const Size2<T>& v)
    {
        return as_stream(s, v);
    }
    }
