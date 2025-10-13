////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "LENUAcceleration.hpp"

YQ_TYPE_IMPLEMENT(yq::LENUAcceleration)

namespace {
    void    reg_LENUAcceleration()
    {
        auto w = writer<LENUAcceleration>();
        w.description("LENU Acceleration");
        w.property(szX, &LENUAcceleration::x);
        w.property(szY, &LENUAcceleration::y);
        w.property(szZ, &LENUAcceleration::z);
    }
    
    YQ_INVOKE(reg_LENUAcceleration();)
}
