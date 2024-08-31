////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/coord/Coord2.hpp>
#include <yq/coord/Coord.hpp>

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
}
