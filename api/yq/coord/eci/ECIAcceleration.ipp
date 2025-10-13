////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ECIAcceleration.hpp"

YQ_TYPE_IMPLEMENT(yq::ECIAcceleration)

namespace {
    void    reg_ECIAcceleration()
    {
        auto w = writer<ECIAcceleration>();
        w.description("ECI Acceleration");
        w.property(szX, &ECIAcceleration::x);
        w.property(szY, &ECIAcceleration::y);
        w.property(szZ, &ECIAcceleration::z);
    }
    
    YQ_INVOKE(reg_ECIAcceleration();)
}
