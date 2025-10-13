////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ECEFVelocity.hpp"

YQ_TYPE_IMPLEMENT(yq::ECEFVelocity)

namespace {
    void    reg_ECEFVelocity()
    {
        auto w = writer<ECEFVelocity>();
        w.description("ECEF Velocity");
        w.property(szX, &ECEFVelocity::x);
        w.property(szY, &ECEFVelocity::y);
        w.property(szZ, &ECEFVelocity::z);
    }
    
    YQ_INVOKE(reg_ECEFVelocity();)
}
