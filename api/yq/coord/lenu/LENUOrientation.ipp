////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "LENUOrientation.hpp"

YQ_TYPE_IMPLEMENT(yq::LENUOrientation)

namespace {
    void    reg_LENUOrientation()
    {
        auto w = writer<LENUOrientation>();
        w.description("LENU Orientation");
        w.property(szW, &LENUOrientation::w);
        w.property(szX, &LENUOrientation::x);
        w.property(szY, &LENUOrientation::y);
        w.property(szZ, &LENUOrientation::z);
    }
    
    YQ_INVOKE(reg_LENUOrientation();)
}
