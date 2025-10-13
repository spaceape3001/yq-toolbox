////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ECIAngularAcceleration.hpp"

YQ_TYPE_IMPLEMENT(yq::ECIAngularAcceleration)

namespace {
    void    reg_ECIAngularAcceleration()
    {
        auto w = writer<ECIAngularAcceleration>();
        w.description("ECI AngularAcceleration");
        w.property(szX, &ECIAngularAcceleration::x);
        w.property(szY, &ECIAngularAcceleration::y);
        w.property(szZ, &ECIAngularAcceleration::z);
    }
    
    YQ_INVOKE(reg_ECIAngularAcceleration();)
}
