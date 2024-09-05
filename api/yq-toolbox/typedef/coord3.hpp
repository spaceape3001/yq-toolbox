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

    template <typename T> using Coord3 = Coord<T,3>;
    using Coord3D = Coord3<double>;
    using Coord3F = Coord3<float>;
    using Coord3I = Coord3<int>;
    using Coord3U = Coord3<unsigned int>;
    using Coord3Z = Coord3<size_t>;
}
