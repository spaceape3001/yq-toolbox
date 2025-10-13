////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "TENUAngularVelocity.hpp"

YQ_TYPE_IMPLEMENT(yq::TENUAngularVelocity)

namespace {
    void    reg_TENUAngularVelocity()
    {
        auto w = writer<TENUAngularVelocity>();
        w.description("TENU AngularVelocity");
        w.property(szX, &TENUAngularVelocity::x);
        w.property(szY, &TENUAngularVelocity::y);
        w.property(szZ, &TENUAngularVelocity::z);
    }
    
    YQ_INVOKE(reg_TENUAngularVelocity();)
}
