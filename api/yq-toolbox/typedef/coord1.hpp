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

    template <typename T> using Coord1 = Coord<T,1>;
    using Coord1D = Coord1<double>;
    using Coord1F = Coord1<float>;
    using Coord1I = Coord1<int>;
    using Coord1U = Coord1<unsigned int>;
    using Coord1Z = Coord1<size_t>;
}
