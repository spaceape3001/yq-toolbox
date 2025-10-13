////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ECEFAcceleration.hpp"

YQ_TYPE_IMPLEMENT(yq::ECEFAcceleration)

namespace {
    void    reg_ECEFAcceleration()
    {
        auto w = writer<ECEFAcceleration>();
        w.description("ECEF Acceleration");
        w.property(szX, &ECEFAcceleration::x);
        w.property(szY, &ECEFAcceleration::y);
        w.property(szZ, &ECEFAcceleration::z);
    }
    
    YQ_INVOKE(reg_ECEFAcceleration();)
}
