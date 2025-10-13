////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "LNEDRotation.hpp"

YQ_TYPE_IMPLEMENT(yq::LNEDRotation)

namespace {
    void    reg_LNEDRotation()
    {
        auto w = writer<LNEDRotation>();
        w.description("LNED Rotation");
        w.property(szX, &LNEDRotation::x);
        w.property(szY, &LNEDRotation::y);
        w.property(szZ, &LNEDRotation::z);
    }
    
    YQ_INVOKE(reg_LNEDRotation();)
}
