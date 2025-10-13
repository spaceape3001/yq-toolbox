////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ECIVelocity.hpp"

YQ_TYPE_IMPLEMENT(yq::ECIVelocity)

namespace {
    void    reg_ECIVelocity()
    {
        auto w = writer<ECIVelocity>();
        w.description("ECI Velocity");
        w.property(szX, &ECIVelocity::x);
        w.property(szY, &ECIVelocity::y);
        w.property(szZ, &ECIVelocity::z);
    }
    
    YQ_INVOKE(reg_ECIVelocity();)
}
