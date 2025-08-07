////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/unit/declare.hpp>

namespace yq {
    template <typename, typename> struct Polar2;
    using Polar2D               = Polar2<unit::Radian,double>;
    using Polar2M               = Polar2<unit::Radian, unit::Meter>;
    using Polar2H               = Polar2<unit::Degree,double>;
}
