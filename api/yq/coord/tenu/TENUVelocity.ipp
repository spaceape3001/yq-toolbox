////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "TENUVelocity.hpp"

YQ_TYPE_IMPLEMENT(yq::TENUVelocity)

namespace {
    void    reg_TENUVelocity()
    {
        auto w = writer<TENUVelocity>();
        w.description("TENU Velocity");
        w.property(szX, &TENUVelocity::x);
        w.property(szY, &TENUVelocity::y);
        w.property(szZ, &TENUVelocity::z);
    }
    
    YQ_INVOKE(reg_TENUVelocity();)
}
