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

    template <typename T> using Coord2 = Coord<T,2>;
    using Coord2D = Coord2<double>;
    using Coord2F = Coord2<float>;
    using Coord2I = Coord2<int>;
    using Coord2U = Coord2<unsigned int>;
    using Coord2Z = Coord2<size_t>;
}
