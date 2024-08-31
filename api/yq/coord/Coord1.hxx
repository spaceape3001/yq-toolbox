////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/coord/Coord1.hpp>
#include <yq/coord/Coord.hpp>

namespace yq {
    template <typename T>
    constexpr Coord1<T> Coord1<T>::operator-() const noexcept 
    {
        return { -i };
    }
    
    template <typename T>
    constexpr Coord1<T>   Coord1<T>::operator+() const noexcept
    {
        return *this;
    }
    
    template <typename T>
    constexpr Coord1<T>   Coord1<T>::operator+(const Coord& b) const noexcept
    {
        return { i + b.i };
    }
}
