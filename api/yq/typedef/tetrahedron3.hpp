////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {
    template <typename> struct Tetrahedron3;

    using Tetrahedron3D             = Tetrahedron3<double>;
    using Tetrahedron3F             = Tetrahedron3<float>;
    using Tetrahedron3I             = Tetrahedron3<int>;
    using Tetrahedron3U             = Tetrahedron3<unsigned>;
}
