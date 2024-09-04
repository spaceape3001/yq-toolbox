////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstddef>
#include <cstdint>

namespace yq {
    template <typename T, uint8_t N> struct Coord;

    template <typename T> using Coord5 = Coord<T,5>;
    using Coord5D = Coord5<double>;
    using Coord5F = Coord5<float>;
    using Coord5I = Coord5<int>;
    using Coord5U = Coord5<unsigned int>;
    using Coord5Z = Coord5<size_t>;
}
