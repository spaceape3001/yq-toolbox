////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "LNEDVelocity.hpp"

YQ_TYPE_IMPLEMENT(yq::LNEDVelocity)

namespace {
    void    reg_LNEDVelocity()
    {
        auto w = writer<LNEDVelocity>();
        w.description("LNED Velocity");
        w.property(szX, &LNEDVelocity::x);
        w.property(szY, &LNEDVelocity::y);
        w.property(szZ, &LNEDVelocity::z);
    }
    
    YQ_INVOKE(reg_LNEDVelocity();)
}
