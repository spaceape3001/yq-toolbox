////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/units.hpp>
#include <yq/vector/Vector2.hpp>
#include <yq/vector/Spinor2.hpp>

namespace yq::physics {
    //! Kinematic state in an inertial coordinate frame
    //! \note This is *NOT* bound to any specific coordinate system, that's
    //! kept separately
    struct KState20 {
        Meter2D     pos                 = ZERO;
        Spinor2D    ori                 = IDENTITY;
    };
}
