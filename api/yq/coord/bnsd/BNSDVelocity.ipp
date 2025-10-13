////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "BNSDVelocity.hpp"

YQ_TYPE_IMPLEMENT(yq::BNSDVelocity)

namespace {
    void    reg_bnsdVelocity()
    {
        auto w = writer<BNSDVelocity>();
        w.description("BNSD Velocity");
        w.property(szX, &BNSDVelocity::x);
        w.property(szY, &BNSDVelocity::y);
        w.property(szZ, &BNSDVelocity::z);
    }
    
    YQ_INVOKE(reg_bnsdVelocity();)
}
