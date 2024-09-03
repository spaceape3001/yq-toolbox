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

    template <typename T> using Coord6 = Coord<T,6>;
    using Coord6D   = Coord6<double>;
    using Coord6F   = Coord6<float>;
    using Coord6I   = Coord6<int>;
    using Coord6U   = Coord6<unsigned int>;
    using Coord6Z   = Coord6<size_t>;
}
