////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/unit/declare.hpp>

namespace yq {
    template <typename A, typename L>   struct Geodetic3;
        
    using Geodetic3RM   = Geodetic3<unit::Radian, unit::Meter>;
    using Geodetic3RF   = Geodetic3<unit::Radian, unit::Foot>;
    using Geodetic3DM   = Geodetic3<unit::Degree, unit::Meter>;
    using Geodetic3DF   = Geodetic3<unit::Degree, unit::Foot>;
}
