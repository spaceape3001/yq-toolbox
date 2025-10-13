////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "BNSDAngularAcceleration.hpp"

YQ_TYPE_IMPLEMENT(yq::BNSDAngularAcceleration)

namespace {
    void    reg_bnsdAngularAcceleration()
    {
        auto w = writer<BNSDAngularAcceleration>();
        w.description("BNSD AngularAcceleration");
        w.property(szX, &BNSDAngularAcceleration::x);
        w.property(szY, &BNSDAngularAcceleration::y);
        w.property(szZ, &BNSDAngularAcceleration::z);
    }
    
    YQ_INVOKE(reg_bnsdAngularAcceleration();)
}
