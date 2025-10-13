////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "TENUAngularAcceleration.hpp"

YQ_TYPE_IMPLEMENT(yq::TENUAngularAcceleration)

namespace {
    void    reg_TENUAngularAcceleration()
    {
        auto w = writer<TENUAngularAcceleration>();
        w.description("TENU AngularAcceleration");
        w.property(szX, &TENUAngularAcceleration::x);
        w.property(szY, &TENUAngularAcceleration::y);
        w.property(szZ, &TENUAngularAcceleration::z);
    }
    
    YQ_INVOKE(reg_TENUAngularAcceleration();)
}
