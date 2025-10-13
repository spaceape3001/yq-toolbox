////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "TNEDAngularAcceleration.hpp"

YQ_TYPE_IMPLEMENT(yq::TNEDAngularAcceleration)

namespace {
    void    reg_TNEDAngularAcceleration()
    {
        auto w = writer<TNEDAngularAcceleration>();
        w.description("TNED AngularAcceleration");
        w.property(szX, &TNEDAngularAcceleration::x);
        w.property(szY, &TNEDAngularAcceleration::y);
        w.property(szZ, &TNEDAngularAcceleration::z);
    }
    
    YQ_INVOKE(reg_TNEDAngularAcceleration();)
}
