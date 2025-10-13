////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "TNEDRotation.hpp"

YQ_TYPE_IMPLEMENT(yq::TNEDRotation)

namespace {
    void    reg_TNEDRotation()
    {
        auto w = writer<TNEDRotation>();
        w.description("TNED Rotation");
        w.property(szX, &TNEDRotation::x);
        w.property(szY, &TNEDRotation::y);
        w.property(szZ, &TNEDRotation::z);
    }
    
    YQ_INVOKE(reg_TNEDRotation();)
}
