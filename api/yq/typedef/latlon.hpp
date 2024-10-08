////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq-toolbox/unit/declare.hpp>

namespace yq {
    template <typename> struct LatLon;
    using LL                    = LatLon<unit::Radian>;
}
