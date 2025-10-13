////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "TENUDisplacement.hpp"

YQ_TYPE_IMPLEMENT(yq::TENUDisplacement)

namespace {
    void    reg_TENUDisplacement()
    {
        auto w = writer<TENUDisplacement>();
        w.description("TENU Displacement");
        w.property(szX, &TENUDisplacement::x);
        w.property(szY, &TENUDisplacement::y);
        w.property(szZ, &TENUDisplacement::z);
    }
    
    YQ_INVOKE(reg_TENUDisplacement();)
}
