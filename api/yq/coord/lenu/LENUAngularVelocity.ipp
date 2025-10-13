////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "LENUAngularVelocity.hpp"

YQ_TYPE_IMPLEMENT(yq::LENUAngularVelocity)

namespace {
    void    reg_LENUAngularVelocity()
    {
        auto w = writer<LENUAngularVelocity>();
        w.description("LENU AngularVelocity");
        w.property(szX, &LENUAngularVelocity::x);
        w.property(szY, &LENUAngularVelocity::y);
        w.property(szZ, &LENUAngularVelocity::z);
    }
    
    YQ_INVOKE(reg_LENUAngularVelocity();)
}
