////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "BNSDAcceleration.hpp"

YQ_TYPE_IMPLEMENT(yq::BNSDAcceleration)

namespace {
    void    reg_bnsdAcceleration()
    {
        auto w = writer<BNSDAcceleration>();
        w.description("BNSD Acceleration");
        w.property(szX, &BNSDAcceleration::x);
        w.property(szY, &BNSDAcceleration::y);
        w.property(szZ, &BNSDAcceleration::z);
    }
    
    YQ_INVOKE(reg_bnsdAcceleration();)
}
