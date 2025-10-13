////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ECIDisplacement.hpp"

YQ_TYPE_IMPLEMENT(yq::ECIDisplacement)

namespace {
    void    reg_ECIDisplacement()
    {
        auto w = writer<ECIDisplacement>();
        w.description("ECI Displacement");
        w.property(szX, &ECIDisplacement::x);
        w.property(szY, &ECIDisplacement::y);
        w.property(szZ, &ECIDisplacement::z);
    }
    
    YQ_INVOKE(reg_ECIDisplacement();)
}
