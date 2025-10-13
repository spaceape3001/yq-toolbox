////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "TNEDVelocity.hpp"

YQ_TYPE_IMPLEMENT(yq::TNEDVelocity)

namespace {
    void    reg_TNEDVelocity()
    {
        auto w = writer<TNEDVelocity>();
        w.description("TNED Velocity");
        w.property(szX, &TNEDVelocity::x);
        w.property(szY, &TNEDVelocity::y);
        w.property(szZ, &TNEDVelocity::z);
    }
    
    YQ_INVOKE(reg_TNEDVelocity();)
}
