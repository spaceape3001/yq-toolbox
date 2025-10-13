////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "LNEDDisplacement.hpp"

YQ_TYPE_IMPLEMENT(yq::LNEDDisplacement)

namespace {
    void    reg_LNEDDisplacement()
    {
        auto w = writer<LNEDDisplacement>();
        w.description("LNED Displacement");
        w.property(szX, &LNEDDisplacement::x);
        w.property(szY, &LNEDDisplacement::y);
        w.property(szZ, &LNEDDisplacement::z);
    }
    
    YQ_INVOKE(reg_LNEDDisplacement();)
}
