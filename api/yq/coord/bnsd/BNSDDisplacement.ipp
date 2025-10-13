////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "BNSDDisplacement.hpp"

YQ_TYPE_IMPLEMENT(yq::BNSDDisplacement)

namespace {
    void    reg_bnsdDisplacement()
    {
        auto w = writer<BNSDDisplacement>();
        w.description("BNSD Displacement");
        w.property(szX, &BNSDDisplacement::x);
        w.property(szY, &BNSDDisplacement::y);
        w.property(szZ, &BNSDDisplacement::z);
    }
    
    YQ_INVOKE(reg_bnsdDisplacement();)
}
