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

#include <yq/shape/Size2.hpp>

#include <yq/math/AllComponents.hpp>
#include <yq/math/AnyComponents.hpp>
#include <yq/math/algorithm.hpp>

namespace yq {

    #ifdef YQ_MATH_VECTOR_2_HPP
    template <typename T>
    constexpr Size2<T>::Size2(const Vector2<T>&v) noexcept : Size2(v.x, v.y)
    {
    }
    #endif

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
    
    #ifdef YQ_MATH_RECTANGLE2_HPP
    template <typename T>
    constexpr Rectangle2<T> Size2<T>::operator+(const Rectangle2<T>&b) const noexcept
    {
        Rectangle2<T>(b.position, *this + b.size);
    }
    #endif

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

    #ifdef YQ_MATH_RECTANGLE2_HPP
    template <typename T>
    constexpr Rectangle2<T> Size2<T>::operator+(const Vector2<T>&b) const noexcept
    {
        return Rectangle2<T>(b, *this);
    }
    #endif

    #ifdef YQ_MATH_RECTANGLE2_HPP
    template <typename T>
    constexpr Rectangle2<T> Size2<T>::operator-(const Rectangle2<T>&b) const noexcept
    {
        return Rectangle2<T>(-b.position, *this - b.size);
    }
    #endif

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
    
    #ifdef YQ_MATH_RECTANGLE2_HPP
    template <typename T>
    constexpr Rectangle2<T> Size2<T>::operator-(const Vector2<T>&b) const noexcept
    {
        return Rectangle2<T>(-b, *this);
    }
    #endif

    template <typename T>
    template <typename U>
    requires is_arithmetic_v<U>
    constexpr Size2<product_t<T,U>> Size2<T>::operator*(U b) const noexcept
    {
        return Size2<product_t<T,U>>( x*b, y*b );
    }
    
    template <typename T>
    template <typename U>
    requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
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
    requires (is_arithmetic_v<U> && self_divide_v<T,U>)
    Size2<T>& Size2<T>::operator/=(U b) noexcept
    {
        x /= b;
        y /= b;
        return *this;
    }

    template <typename T>
    constexpr Size2<T> Size2<T>::all_add(T b) const noexcept
    {
        return Size2( x+b, y+b );
    }
    
    template <typename T>
    Size2<T>&    Size2<T>::all_decrement(T b) noexcept
    {
        x -= b;
        y -= b;
        return *this;
    }

    template <typename T>
    Size2<T>&    Size2<T>::all_increment(T b) noexcept
    {
        x += b;
        y += b;
        return *this;
    }

    template <typename T>
    constexpr Size2<T> Size2<T>::all_subtract(T b) const noexcept
    {
        return Size2( x-b, y-b );
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Size2<T>::all_test(Pred pred) const noexcept
    {
        return pred(x) && pred(y);
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Size2<T>::all_test(const Size2& b, Pred pred) const noexcept
    {
        return pred(x, b.x) && pred(y, b.y);
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Size2<T>::all_test(T b, Pred pred) const noexcept
    {
        return pred(x, b) && pred(y, b);
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Size2<T>::any_test(Pred pred) const noexcept
    {
        return pred(x) || pred(y);
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Size2<T>::any_test(const Size2& b, Pred pred) const noexcept
    {
        return pred(x, b.x) || pred(y, b.y);
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Size2<T>::any_test(T b, Pred pred) const noexcept
    {
        return pred(x, b) || pred(y, b);
    }

    template <typename T>
    constexpr square_t<T> Size2<T>::area() const noexcept
    {
        return x*y;
    }

    template <typename T>
    constexpr T     Size2<T>::cmax() const noexcept
    {
        return std::max({x, y});
    }

    template <typename T>
    constexpr T     Size2<T>::cmin() const noexcept
    {
        return std::min({x, y});
    }

    template <typename T>
    bool                Size2<T>::contains(const Size2& small) const noexcept
    {
        return all(*this) >= small;
    }
    
    template <typename T>
    constexpr square_t<T>   Size2<T>::cproduct() const noexcept
    {
        return x*y;
    }

    template <typename T>
    constexpr T             Size2<T>::csum() const noexcept
    {
        return x + y;
    }

    template <typename T>
    constexpr Size2<T>   Size2<T>::eabs() const noexcept
    {
        return Size2( abs(x), abs(y) );
    }

    template <typename T>
    bool                Size2<T>::eclipses(const Size2& small) const noexcept
    {
        return all(*this) >= small;
    }
    
    template <typename T>
        template <typename U>
    constexpr Size2<quotient_t<T,U>>  Size2<T>::ediv(const Size2<U>&b) const noexcept
    {
        return Size2<quotient_t<T,U>>(x/b.x, y/b.y );
    }

    template <typename T>
    constexpr Size2<T>   Size2<T>::emax(const Size2&b) const noexcept
    {
        return Size2(max(x, b.x), max(y, b.y));
    }

    template <typename T>
    constexpr Size2<T>   Size2<T>::emax(T b) const noexcept
    {
        return Size2(max(x, b), max(y, b));
    }
    
    template <typename T>
    constexpr Size2<T>   Size2<T>::emin(const Size2&b) const noexcept
    {
        return Size2(min(x, b.x), min(y, b.y));
    }

    template <typename T>
    constexpr Size2<T>   Size2<T>::emin(T b) const noexcept
    {
        return Size2(min(x, b), min(y, b));
    }

    template <typename T>
        template <typename U>
    constexpr Size2<product_t<T,U>>   Size2<T>::emul(const Size2<U>&b) const noexcept
    {
        return {x*b.x, y*b.y};
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
    requires is_arithmetic_v<T>
    constexpr Size2<product_t<T,U>> operator*(T a, const Size2<U>& b) noexcept
    {
        return Size2<product_t<T,U>>(a*b.x, a*b.y);
    }

    template <typename T>
    AllComponents<Size2<T>>   all(Size2<T>& val)
    {
        return { val };
    }

    template <typename T>
    AllComponents<const Size2<T>>   all(const Size2<T>& val)
    {
        return { val };
    }
    
    template <typename T>
    AnyComponents<Size2<T>>   any(Size2<T>& val)
    {
        return { val };
    }

    template <typename T>
    AnyComponents<const Size2<T>>   any(const Size2<T>& val)
    {
        return { val };
    }

    template <typename T>
    constexpr auto    area(const Size2<T>& sz) noexcept
    {
        return sz.x*sz.y;
    }
    
    #if 0
    template <typename T>
    ElemComponents<Size2<T>>   elem(Size2<T>& val)
    {
        return { val };
    }

    template <typename T>
    ElemComponents<const Size2<T>>   elem(const Size2<T>& val)
    {
        return { val };
    }
    #endif

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
    
    #ifdef YQ_BASIC_STREAM_HPP_
    template <typename T>
    Stream& operator<<(Stream&s, const Size2<T>& v)
    {
        return as_stream(s, v);
    }
    #endif

    #ifdef _LOG4CPP_CATEGORYSTREAM_HH
    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const Size2<T>& v)
    {
        return as_stream(s, v);
    }
    #endif
}
