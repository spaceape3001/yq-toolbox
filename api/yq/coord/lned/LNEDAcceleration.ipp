////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "LNEDAcceleration.hpp"

YQ_TYPE_IMPLEMENT(yq::LNEDAcceleration)

namespace {
    void    reg_LNEDAcceleration()
    {
        auto w = writer<LNEDAcceleration>();
        w.description("LNED Acceleration");
        w.property(szX, &LNEDAcceleration::x);
        w.property(szY, &LNEDAcceleration::y);
        w.property(szZ, &LNEDAcceleration::z);
    }
    
    YQ_INVOKE(reg_LNEDAcceleration();)
}
