////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/coord/Coord3.hpp>
#include <yq/coord/Coord.hpp>

namespace yq {
    template <typename T>
    constexpr Coord3<T> Coord3<T>::operator+() const noexcept
    {
        return *this;
    }
    
    template <typename T>
    constexpr Coord3<T> Coord3<T>::operator-() const noexcept
    {
        return { -i, -j, -k };
    }
}
