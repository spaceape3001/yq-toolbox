////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {
    template <typename> struct Polygon3;

    using Polygon3D = Polygon3<double>;
    using Polygon3F = Polygon3<float>;
    using Polygon3I = Polygon3<int>;
    using Polygon3U = Polygon3<unsigned>;
}
