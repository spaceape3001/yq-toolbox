////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/unit/declare.hpp>

namespace yq {
    template <typename, typename> struct Cylindrical3;

    using Cylindrical3D         = Cylindrical3<unit::Radian,double>;
    using Cylindrical3M         = Cylindrical3<unit::Radian,unit::Meter>;
}
