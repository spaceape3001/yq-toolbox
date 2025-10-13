////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "LENUVelocity.hpp"

YQ_TYPE_IMPLEMENT(yq::LENUVelocity)

namespace {
    void    reg_LENUVelocity()
    {
        auto w = writer<LENUVelocity>();
        w.description("LENU Velocity");
        w.property(szX, &LENUVelocity::x);
        w.property(szY, &LENUVelocity::y);
        w.property(szZ, &LENUVelocity::z);
    }
    
    YQ_INVOKE(reg_LENUVelocity();)
}
