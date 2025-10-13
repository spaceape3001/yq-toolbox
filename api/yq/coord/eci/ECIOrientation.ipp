////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ECIOrientation.hpp"

YQ_TYPE_IMPLEMENT(yq::ECIOrientation)

namespace {
    void    reg_ECIOrientation()
    {
        auto w = writer<ECIOrientation>();
        w.description("ECI Orientation");
        w.property(szW, &ECIOrientation::w);
        w.property(szX, &ECIOrientation::x);
        w.property(szY, &ECIOrientation::y);
        w.property(szZ, &ECIOrientation::z);
    }
    
    YQ_INVOKE(reg_ECIOrientation();)
}
