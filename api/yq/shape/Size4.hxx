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

#include <yq/shape/Size4.hpp>

#include <yq/math/AllComponents.hpp>
#include <yq/math/AnyComponents.hpp>

namespace yq {
    #ifdef YQ_MATH_VECTOR_4_HPP
    template <typename T>
    constexpr Size4<T>::Size4(const Vector4<T>&v) noexcept : Size4(v.x, v.y, v.z, v.w)
    {
    }
    #endif

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
    requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
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
    requires (is_arithmetic_v<U> && self_divide_v<T,U>)
    Size4<T>& Size4<T>::operator/=(U b) noexcept
    {
        x /= b;
        y /= b;
        z /= b;
        w /= b;
        return *this;
    }

    template <typename T>
    constexpr Size4<T> Size4<T>::all_add(T b) const noexcept
    {
        return Size4( x+b, y+b, z+b, w+b );
    }
    
    template <typename T>
    Size4<T>&    Size4<T>::all_decrement(T b) noexcept
    {
        x -= b;
        y -= b;
        z -= b;
        w -= b;
        return *this;
    }

    template <typename T>
    Size4<T>&    Size4<T>::all_increment(T b) noexcept
    {
        x += b;
        y += b;
        z += b;
        w += b;
        return *this;
    }

    template <typename T>
    constexpr Size4<T> Size4<T>::all_subtract(T b) const noexcept
    {
        return Size4( x-b, y-b, z-b, w-b );
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Size4<T>::all_kest(Pred pred) const noexcept
    {
        return pred(x) && pred(y) && pred(z) && pred(w);
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Size4<T>::all_kest(const Size4& b, Pred pred) const noexcept
    {
        return pred(x, b.x) && pred(y, b.y) && pred(z, b.z) && pred(w, b.w);
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Size4<T>::all_kest(T b, Pred pred) const noexcept
    {
        return pred(x, b) && pred(y, b) && pred(z, b) && pred(w, b);
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Size4<T>::any_test(Pred pred) const noexcept
    {
        return pred(x) || pred(y) || pred(z) || pred(w);
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Size4<T>::any_test(const Size4& b, Pred pred) const noexcept
    {
        return pred(x, b.x) || pred(y, b.y) || pred(z, b.z) || pred(w, b.w);
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Size4<T>::any_test(T b, Pred pred) const noexcept
    {
        return pred(x, b) || pred(y, b) || pred(z, b) || pred(w, b);
    }
        
    template <typename T>
    constexpr T     Size4<T>::cmax() const noexcept
    {
        return std::max({x, y, z, w});
    }

    template <typename T>
    constexpr T     Size4<T>::cmin() const noexcept
    {
        return std::min({x, y, z, w});
    }

    template <typename T>
    constexpr bool   Size4<T>::contains(const Size4<T>& small) const noexcept
    {
        return all(*this) >= small;
    }

    template <typename T>
    constexpr fourth_t<T>   Size4<T>::cproduct() const noexcept
    {
        return x*y*z*w;
    }

    template <typename T>
    constexpr T             Size4<T>::csum() const noexcept
    {
        return x + y + z + w;
    }

    template <typename T>
    constexpr T   Size4<T>::depth() const 
    { 
        return z; 
    }
    
    template <typename T>
    constexpr T   Size4<T>::duration() const 
    { 
        return w; 
    }

    template <typename T>
    constexpr Size4<T>   Size4<T>::eabs() const noexcept
    {
        return Size4( abs(x), abs(y), abs(z), abs(w) );
    }

    template <typename T>
    constexpr bool   Size4<T>::eclipses(const Size4<T>& small) const noexcept
    {
        return all(*this) >= small;
    }

    template <typename T>
        template <typename U>
    constexpr Size4<quotient_t<T,U>>  Size4<T>::ediv(const Size4<U>&b) const noexcept
    {
        return Size4<quotient_t<T,U>>(x/b.x, y/b.y, z/b.z, w/b.w);
    }

    template <typename T>
    constexpr Size4<T>   Size4<T>::emax(const Size4&b) const noexcept
    {
        return Size4(max(x, b.x), max(y, b.y), max(z, b.z), max(w, b.w));
    }
    
    template <typename T>
    constexpr Size4<T>   Size4<T>::emin(const Size4&b) const noexcept
    {
        return Size4(min(x, b.x), min(y, b.y), min(z, b.z), min(w, b.w));
    }

    template <typename T>
        template <typename U>
    constexpr Size4<product_t<T,U>>   Size4<T>::emul(const Size4<U>&b) const noexcept
    {
        return {x*b.x, y*b.y, z*b.z, w*b.w};
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
    
    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Size4<product_t<T,U>> operator*(T a, const Size4<U>& b) noexcept
    {
        return Size4<product_t<T,U>>(a*b.x, a*b.y, a*b.z, a*b.w );
    }

    template <typename T>
    AllComponents<Size4<T>>   all(Size4<T>& val)
    {
        return { val };
    }
    
    template <typename T>
    AllComponents<const Size4<T>>   all(const Size4<T>& val)
    {
        return { val };
    }

    #if 0
    template <typename T>
    ElemComponents<Size4<T>>   elem(Size4<T>& val)
    {
        return { val };
    }

    template <typename T>
    ElemComponents<const Size4<T>>   elem(const Size4<T>& val)
    {
        return { val };
    }
    #endif

    template <typename T>
    AnyComponents<Size4<T>>   any(Size4<T>& val)
    {
        return { val };
    }

    template <typename T>
    AnyComponents<const Size4<T>>   any(const Size4<T>& val)
    {
        return { val };
    }

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
    
    #ifdef YQ_BASIC_STREAM_HPP_
    template <typename T>
    Stream& operator<<(Stream&s, const Size4<T>& v)
    {
        return as_stream(s, v);
    }
    #endif

    #ifdef _LOG4CPP_CATEGORYSTREAM_HH
    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const Size4<T>& v)
    {
        return as_stream(s, v);
    }
    #endif
}
