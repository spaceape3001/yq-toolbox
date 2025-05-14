////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/unit/declare.hpp>

namespace yq {
    template <typename> struct AxSide3;

    using AxSide3D   = AxSide3<double>;
    using AxSide3F   = AxSide3<float>;
    using AxSide3I   = AxSide3<int>;
    using AxSide3U   = AxSide3<unsigned>;
    using AxSide3M   = AxSide3<unit::Meter>;
    using AxSide3CM  = AxSide3<unit::Centimeter>;
    using AxSide3MM  = AxSide3<unit::Millimeter>;
}
