////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "LNEDAngularAcceleration.hpp"

YQ_TYPE_IMPLEMENT(yq::LNEDAngularAcceleration)

namespace {
    void    reg_LNEDAngularAcceleration()
    {
        auto w = writer<LNEDAngularAcceleration>();
        w.description("LNED AngularAcceleration");
        w.property(szX, &LNEDAngularAcceleration::x);
        w.property(szY, &LNEDAngularAcceleration::y);
        w.property(szZ, &LNEDAngularAcceleration::z);
    }
    
    YQ_INVOKE(reg_LNEDAngularAcceleration();)
}
