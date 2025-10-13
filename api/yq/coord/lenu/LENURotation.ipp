////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "LENURotation.hpp"

YQ_TYPE_IMPLEMENT(yq::LENURotation)

namespace {
    void    reg_LENURotation()
    {
        auto w = writer<LENURotation>();
        w.description("LENU Rotation");
        w.property(szX, &LENURotation::x);
        w.property(szY, &LENURotation::y);
        w.property(szZ, &LENURotation::z);
    }
    
    YQ_INVOKE(reg_LENURotation();)
}
