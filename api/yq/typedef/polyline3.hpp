////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {
    template <typename> struct Polyline3;

    using Polyline3D                = Polyline3<double>;
    using Polyline3F                = Polyline3<float>;
    using Polyline3I                = Polyline3<int>;
    using Polyline3U                = Polyline3<unsigned>;
}
