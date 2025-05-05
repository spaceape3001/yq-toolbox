////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/unit/declare.hpp>

namespace yq {
    template <typename> struct AxBox2;

    using AxBox2D   = AxBox2<double>;
    using AxBox2F   = AxBox2<float>;
    using AxBox2I   = AxBox2<int>;
    using AxBox2U   = AxBox2<unsigned>;
    using AxBox2M   = AxBox2<unit::Meter>;
    using AxBox2CM  = AxBox2<unit::Centimeter>;
    using AxBox2MM  = AxBox2<unit::Millimeter>;
}
