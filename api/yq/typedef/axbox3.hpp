////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/unit/declare.hpp>

namespace yq {
    template <typename> struct AxBox3;

    using AxBox3D   = AxBox3<double>;
    using AxBox3F   = AxBox3<float>;
    using AxBox3I   = AxBox3<int>;
    using AxBox3U   = AxBox3<unsigned>;
    using AxBox3M   = AxBox3<unit::Meter>;
    using AxBox3CM  = AxBox3<unit::Centimeter>;
    using AxBox3MM  = AxBox3<unit::Millimeter>;
}
