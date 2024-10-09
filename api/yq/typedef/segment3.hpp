////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {
    template <typename> struct Segment3;

    using Segment3D                 = Segment3<double>;
    using Segment3F                 = Segment3<float>;
    using Segment3I                 = Segment3<int>;
    using Segment3U                 = Segment3<unsigned>;
}
