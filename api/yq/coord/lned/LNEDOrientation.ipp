////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "LNEDOrientation.hpp"

YQ_TYPE_IMPLEMENT(yq::LNEDOrientation)

namespace {
    void    reg_LNEDOrientation()
    {
        auto w = writer<LNEDOrientation>();
        w.description("LNED Orientation");
        w.property(szW, &LNEDOrientation::w);
        w.property(szX, &LNEDOrientation::x);
        w.property(szY, &LNEDOrientation::y);
        w.property(szZ, &LNEDOrientation::z);
    }
    
    YQ_INVOKE(reg_LNEDOrientation();)
}
