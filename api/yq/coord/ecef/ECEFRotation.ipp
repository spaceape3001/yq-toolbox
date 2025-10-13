////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ECEFRotation.hpp"

YQ_TYPE_IMPLEMENT(yq::ECEFRotation)

namespace {
    void    reg_ECEFRotation()
    {
        auto w = writer<ECEFRotation>();
        w.description("ECEF Rotation");
        w.property(szX, &ECEFRotation::x);
        w.property(szY, &ECEFRotation::y);
        w.property(szZ, &ECEFRotation::z);
    }
    
    YQ_INVOKE(reg_ECEFRotation();)
}
