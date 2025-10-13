////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ECEFAngularVelocity.hpp"

YQ_TYPE_IMPLEMENT(yq::ECEFAngularVelocity)

namespace {
    void    reg_ECEFAngularVelocity()
    {
        auto w = writer<ECEFAngularVelocity>();
        w.description("ECEF AngularVelocity");
        w.property(szX, &ECEFAngularVelocity::x);
        w.property(szY, &ECEFAngularVelocity::y);
        w.property(szZ, &ECEFAngularVelocity::z);
    }
    
    YQ_INVOKE(reg_ECEFAngularVelocity();)
}
