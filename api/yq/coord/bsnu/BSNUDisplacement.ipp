////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "BSNUDisplacement.hpp"

YQ_TYPE_IMPLEMENT(yq::BSNUDisplacement)

namespace {
    void    reg_BSNUDisplacement()
    {
        auto w = writer<BSNUDisplacement>();
        w.description("BSNU Displacement");
        w.property(szX, &BSNUDisplacement::x);
        w.property(szY, &BSNUDisplacement::y);
        w.property(szZ, &BSNUDisplacement::z);
    }
    
    YQ_INVOKE(reg_BSNUDisplacement();)
}
