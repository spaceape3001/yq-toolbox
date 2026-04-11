////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/units.hpp>
#include <yq/vector/Quaternion3.hpp>
#include <yq/vector/Vector3.hpp>

namespace yq::physics {
    struct KState30 {
        Meter3D         pos                 = ZERO;
        Quaternion3D    ori                 = IDENTITY;
    };
}
