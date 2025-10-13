////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ECEFAngularAcceleration.hpp"

YQ_TYPE_IMPLEMENT(yq::ECEFAngularAcceleration)

namespace {
    void    reg_ECEFAngularAcceleration()
    {
        auto w = writer<ECEFAngularAcceleration>();
        w.description("ECEF AngularAcceleration");
        w.property(szX, &ECEFAngularAcceleration::x);
        w.property(szY, &ECEFAngularAcceleration::y);
        w.property(szZ, &ECEFAngularAcceleration::z);
    }
    
    YQ_INVOKE(reg_ECEFAngularAcceleration();)
}
