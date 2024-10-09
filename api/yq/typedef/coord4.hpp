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

    template <typename T> using Coord4 = Coord<T,4>;
    using Coord4D = Coord4<double>;
    using Coord4F = Coord4<float>;
    using Coord4I = Coord4<int>;
    using Coord4U = Coord4<unsigned int>;
    using Coord4Z = Coord4<size_t>;
}
