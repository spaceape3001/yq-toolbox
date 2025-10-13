////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ECEFDisplacement.hpp"

YQ_TYPE_IMPLEMENT(yq::ECEFDisplacement)

namespace {
    void    reg_ECEFDisplacement()
    {
        auto w = writer<ECEFDisplacement>();
        w.description("ECEF Displacement");
        w.property(szX, &ECEFDisplacement::x);
        w.property(szY, &ECEFDisplacement::y);
        w.property(szZ, &ECEFDisplacement::z);
    }
    
    YQ_INVOKE(reg_ECEFDisplacement();)
}
