////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "TNEDOrientation.hpp"

YQ_TYPE_IMPLEMENT(yq::TNEDOrientation)

namespace {
    void    reg_TNEDOrientation()
    {
        auto w = writer<TNEDOrientation>();
        w.description("TNED Orientation");
        w.property(szW, &TNEDOrientation::w);
        w.property(szX, &TNEDOrientation::x);
        w.property(szY, &TNEDOrientation::y);
        w.property(szZ, &TNEDOrientation::z);
    }
    
    YQ_INVOKE(reg_TNEDOrientation();)
}
