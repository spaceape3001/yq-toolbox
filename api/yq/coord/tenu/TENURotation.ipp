////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "TENURotation.hpp"

YQ_TYPE_IMPLEMENT(yq::TENURotation)

namespace {
    void    reg_TENURotation()
    {
        auto w = writer<TENURotation>();
        w.description("TENU Rotation");
        w.property(szX, &TENURotation::x);
        w.property(szY, &TENURotation::y);
        w.property(szZ, &TENURotation::z);
    }
    
    YQ_INVOKE(reg_TENURotation();)
}
