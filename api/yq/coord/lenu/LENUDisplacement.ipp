////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "LENUDisplacement.hpp"

YQ_TYPE_IMPLEMENT(yq::LENUDisplacement)

namespace {
    void    reg_LENUDisplacement()
    {
        auto w = writer<LENUDisplacement>();
        w.description("LENU Displacement");
        w.property(szX, &LENUDisplacement::x);
        w.property(szY, &LENUDisplacement::y);
        w.property(szZ, &LENUDisplacement::z);
    }
    
    YQ_INVOKE(reg_LENUDisplacement();)
}
