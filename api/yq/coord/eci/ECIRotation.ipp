////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ECIRotation.hpp"

YQ_TYPE_IMPLEMENT(yq::ECIRotation)

namespace {
    void    reg_ECIRotation()
    {
        auto w = writer<ECIRotation>();
        w.description("ECI Rotation");
        w.property(szX, &ECIRotation::x);
        w.property(szY, &ECIRotation::y);
        w.property(szZ, &ECIRotation::z);
    }
    
    YQ_INVOKE(reg_ECIRotation();)
}
