////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "BNSDRotation.hpp"

YQ_TYPE_IMPLEMENT(yq::BNSDRotation)

namespace {
    void    reg_bnsdRotation()
    {
        auto w = writer<BNSDRotation>();
        w.description("BNSD Rotation");
        w.property(szX, &BNSDRotation::x);
        w.property(szY, &BNSDRotation::y);
        w.property(szZ, &BNSDRotation::z);
    }
    
    YQ_INVOKE(reg_bnsdRotation();)
}
