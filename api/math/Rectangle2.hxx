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

#include <math/Rectangle2.hpp>
#include <math/AxBox2.hpp>
#include <math/AxCorners2.hpp>

namespace yq {
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
}
