////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {
    template <typename> struct AxBox3;

    using AxBox3D                   = AxBox3<double>;
    using AxBox3F                   = AxBox3<float>;
    using AxBox3I                   = AxBox3<int>;
    using AxBox3U                   = AxBox3<unsigned>;
}
