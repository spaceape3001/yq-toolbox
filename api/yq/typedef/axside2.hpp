////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/unit/declare.hpp>

namespace yq {
    template <typename> struct AxSide2;

    using AxSide2D   = AxSide2<double>;
    using AxSide2F   = AxSide2<float>;
    using AxSide2I   = AxSide2<int>;
    using AxSide2U   = AxSide2<unsigned>;
    using AxSide2M   = AxSide2<unit::Meter>;
    using AxSide2CM  = AxSide2<unit::Centimeter>;
    using AxSide2MM  = AxSide2<unit::Millimeter>;
}
