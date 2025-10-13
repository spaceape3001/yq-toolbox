////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "BNSDAngularVelocity.hpp"

YQ_TYPE_IMPLEMENT(yq::BNSDAngularVelocity)

namespace {
    void    reg_bnsdAngularVelocity()
    {
        auto w = writer<BNSDAngularVelocity>();
        w.description("BNSD AngularVelocity");
        w.property(szX, &BNSDAngularVelocity::x);
        w.property(szY, &BNSDAngularVelocity::y);
        w.property(szZ, &BNSDAngularVelocity::z);
    }
    
    YQ_INVOKE(reg_bnsdAngularVelocity();)
}
