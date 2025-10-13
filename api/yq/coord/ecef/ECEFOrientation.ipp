////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ECEFOrientation.hpp"

YQ_TYPE_IMPLEMENT(yq::ECEFOrientation)

namespace {
    void    reg_ECEFOrientation()
    {
        auto w = writer<ECEFOrientation>();
        w.description("ECEF Orientation");
        w.property(szW, &ECEFOrientation::w);
        w.property(szX, &ECEFOrientation::x);
        w.property(szY, &ECEFOrientation::y);
        w.property(szZ, &ECEFOrientation::z);
    }
    
    YQ_INVOKE(reg_ECEFOrientation();)
}
