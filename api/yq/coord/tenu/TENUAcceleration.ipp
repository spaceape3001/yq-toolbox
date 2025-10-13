////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "TENUAcceleration.hpp"

YQ_TYPE_IMPLEMENT(yq::TENUAcceleration)

namespace {
    void    reg_TENUAcceleration()
    {
        auto w = writer<TENUAcceleration>();
        w.description("TENU Acceleration");
        w.property(szX, &TENUAcceleration::x);
        w.property(szY, &TENUAcceleration::y);
        w.property(szZ, &TENUAcceleration::z);
    }
    
    YQ_INVOKE(reg_TENUAcceleration();)
}
