////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "TNEDAcceleration.hpp"

YQ_TYPE_IMPLEMENT(yq::TNEDAcceleration)

namespace {
    void    reg_TNEDAcceleration()
    {
        auto w = writer<TNEDAcceleration>();
        w.description("TNED Acceleration");
        w.property(szX, &TNEDAcceleration::x);
        w.property(szY, &TNEDAcceleration::y);
        w.property(szZ, &TNEDAcceleration::z);
    }
    
    YQ_INVOKE(reg_TNEDAcceleration();)
}
