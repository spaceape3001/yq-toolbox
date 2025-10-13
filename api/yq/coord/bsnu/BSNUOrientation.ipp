////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "BSNUOrientation.hpp"

YQ_TYPE_IMPLEMENT(yq::BSNUOrientation)

namespace {
    void    reg_BSNUOrientation()
    {
        auto w = writer<BSNUOrientation>();
        w.description("BSNU Orientation");
        w.property(szW, &BSNUOrientation::w);
        w.property(szX, &BSNUOrientation::x);
        w.property(szY, &BSNUOrientation::y);
        w.property(szZ, &BSNUOrientation::z);
    }
    
    YQ_INVOKE(reg_BSNUOrientation();)
}
