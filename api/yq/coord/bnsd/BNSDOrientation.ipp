////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "BNSDOrientation.hpp"

YQ_TYPE_IMPLEMENT(yq::BNSDOrientation)

namespace {
    void    reg_bnsdOrientation()
    {
        auto w = writer<BNSDOrientation>();
        w.description("BNSD Orientation");
        w.property(szW, &BNSDOrientation::w);
        w.property(szX, &BNSDOrientation::x);
        w.property(szY, &BNSDOrientation::y);
        w.property(szZ, &BNSDOrientation::z);
    }
    
    YQ_INVOKE(reg_bnsdOrientation();)
}
