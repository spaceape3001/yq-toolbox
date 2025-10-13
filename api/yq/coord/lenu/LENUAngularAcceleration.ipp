////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "LENUAngularAcceleration.hpp"

YQ_TYPE_IMPLEMENT(yq::LENUAngularAcceleration)

namespace {
    void    reg_LENUAngularAcceleration()
    {
        auto w = writer<LENUAngularAcceleration>();
        w.description("LENU AngularAcceleration");
        w.property(szX, &LENUAngularAcceleration::x);
        w.property(szY, &LENUAngularAcceleration::y);
        w.property(szZ, &LENUAngularAcceleration::z);
    }
    
    YQ_INVOKE(reg_LENUAngularAcceleration();)
}
