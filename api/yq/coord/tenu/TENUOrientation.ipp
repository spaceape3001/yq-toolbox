////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "TENUOrientation.hpp"

YQ_TYPE_IMPLEMENT(yq::TENUOrientation)

namespace {
    void    reg_TENUOrientation()
    {
        auto w = writer<TENUOrientation>();
        w.description("TENU Orientation");
        w.property(szW, &TENUOrientation::w);
        w.property(szX, &TENUOrientation::x);
        w.property(szY, &TENUOrientation::y);
        w.property(szZ, &TENUOrientation::z);
    }
    
    YQ_INVOKE(reg_TENUOrientation();)
}
