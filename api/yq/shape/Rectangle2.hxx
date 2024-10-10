////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the rectangle2 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <yq/shape/Rectangle2.hpp>
#include <yq/shape/AxBox2.hpp>
#include <yq/shape/AxCorners2.hpp>

namespace yq {
    template <typename T>
    constexpr Rectangle2<T>::Rectangle2(const AxBox2<T>& bx) noexcept : Rectangle2(bx.ll(GUARD), bx.size(GUARD))
    {
    }

    template <typename T>
    constexpr Rectangle2<T> Rectangle2<T>::operator+() const noexcept
    {
        return *this;
    }
    
    template <typename T>
    constexpr Rectangle2<T> Rectangle2<T>::operator-() const noexcept
    {
        return Rectangle2(-position-(Vector2<T>) size, size);
    }

    template <typename T>
    constexpr Rectangle2<T> Rectangle2<T>::operator+(const Rectangle2&b) const noexcept
    {
        Rectangle2(position+b.position, size+b.size);
    }
    
    template <typename T>
    Rectangle2<T>&          Rectangle2<T>::operator+=(const Rectangle2&b) noexcept
    {
        position += b.position;
        size += b.size;
        return *this;
    }

    template <typename T>
    constexpr Rectangle2<T> Rectangle2<T>::operator+(const Size2<T>&b) const noexcept
    {
        return Rectangle2(position, size+b);
    }
    
    template <typename T>
    Rectangle2<T>&          Rectangle2<T>::operator+=(const Size2<T>&b) noexcept
    {
        size += b;
        return *this;
    }

    template <typename T>
    constexpr Rectangle2<T> Rectangle2<T>::operator+(const Vector2<T>&b) const noexcept
    {
        return Rectangle2<T>(position+b, size);
    }
    
    template <typename T>
    Rectangle2<T>&          Rectangle2<T>::operator+=(const Vector2<T>&b) noexcept
    {
        position += b;
        return *this;
    }

    template <typename T>
    constexpr Rectangle2<T>    Rectangle2<T>::operator-(const Rectangle2&b) const noexcept
    {
        return Rectangle2( position-b.position, size-b.size);
    }
    
    template <typename T>
    Rectangle2<T>&             Rectangle2<T>::operator-=(const Rectangle2&b) noexcept
    {
        position -= b.position;
        size -= b.size;
        return *this;
    }

    template <typename T>
    constexpr Rectangle2<T> Rectangle2<T>::operator-(const Size2<T>&b) const noexcept
    {
        return Rectangle2(position, size-b);
    }
    
    template <typename T>
    Rectangle2<T>&          Rectangle2<T>::operator-=(const Size2<T>&b) noexcept
    {
        size -= b;
        return *this;
    }

    template <typename T>
    constexpr Rectangle2<T> Rectangle2<T>::operator-(const Vector2<T>&b) const noexcept
    {
        return Rectangle2(position-b, size);
    }
    
    template <typename T>
    Rectangle2<T>&          Rectangle2<T>::operator-=(const Vector2<T>&b) noexcept
    {
        position -= b;
        return *this;
    }

    template <typename T>
    template <typename U>
    requires is_arithmetic_v<U>
    constexpr Rectangle2<product_t<T,U>>  Rectangle2<T>::operator*(U b) const noexcept
    {
        if( b >= zero_v<U> ){
            return Rectangle2<product_t<T,U>>(position * b, size * b);
        } else {
            return Rectangle2<product_t<T,U>>((position + size) * b, size * b);
        }
    }
    
    template <typename T>
    template <typename U>
    requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
    Rectangle2<T>&  Rectangle2<T>::operator*=(U b) noexcept
    {
        *this = *this * b;
        return *this;
    }

    template <typename T>
    template <typename U>
    requires is_arithmetic_v<U>
    constexpr Rectangle2<quotient_t<T,U>>  Rectangle2<T>::operator/(U b) const noexcept
    {
        if( b >= zero_v<U> ){
            return Rectangle2<quotient_t<T,U>>(position / b, size / b);
        } else {
            return Rectangle2<quotient_t<T,U>>((position + size) / b, size / b);
        }
    }

    template <typename T>
    template <typename U>
    requires (is_arithmetic_v<U> && self_divide_v<T,U>)
    Rectangle2<T>&  Rectangle2<T>::operator/=(U b) noexcept
    {
        *this = *this / b;
        return *this;
    }


    template <typename T>
    constexpr AxBox2<T>   Rectangle2<T>::bounds() const noexcept
    {
        return AxBox2<T>(southwest(), northeast());
    }

    template <typename T>
    constexpr AxCorners2<Vector2<T>>  Rectangle2<T>::corners() const noexcept
    {
        return { 
            southwest(),
            northwest(),
            southeast(),
            northeast()
        };
    }

    template <typename T>
    constexpr T   Rectangle2<T>::height() const noexcept
    {
        return size.height();
    }

    template <typename T>
    constexpr Vector2<T>  Rectangle2<T>::northeast() const noexcept
    {
        return { position.x+size.x, position.y+size.y };
    }

    template <typename T>
    constexpr Vector2<T>  Rectangle2<T>::northwest() const noexcept
    {
        return { position.x, position.y+size.y };
    }

    template <typename T>
    constexpr Vector2<T>  Rectangle2<T>::southeast() const noexcept
    {
        return { position.x+size.x, position.y };
    }

    template <typename T>
    constexpr Vector2<T>  Rectangle2<T>::southwest() const noexcept
    {
        return { position.x, position.y };
    }

    template <typename T>
    constexpr T   Rectangle2<T>::width() const noexcept
    {
        return size.width();
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename T>
    constexpr AxBox2<T>   aabb(const Rectangle2<T>& rect) noexcept
    {
        return rect.bounds();
    }

    template <typename T>
    constexpr AxCorners2<Vector2<T>>  corners(const Rectangle2<T>& rect) noexcept
    {
        return rect.corners();
    }

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Rectangle2<product_t<T,U>> operator*(T a, const Rectangle2<T>&b) noexcept
    {
        if(a >= zero_v<T>){
            return Rectangle2<product_t<T,U>>(a*b.position, a*b.size);
        } else {
            return Rectangle2<product_t<T,U>>(a*(b.position+b.size), a*b.size);
        }
    }
}
