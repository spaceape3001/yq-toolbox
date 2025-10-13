////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "BNSDPosition.hpp"

YQ_TYPE_IMPLEMENT(yq::BNSDPosition)

namespace {
    void    reg_bnsdposition()
    {
        auto w = writer<BNSDPosition>();
        w.description("BNSD Position");
        w.property(szX, &BNSDPosition::x);
        w.property(szY, &BNSDPosition::y);
        w.property(szZ, &BNSDPosition::z);
    }
    
    YQ_INVOKE(reg_bnsdposition();)
}
