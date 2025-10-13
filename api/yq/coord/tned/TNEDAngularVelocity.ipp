////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "TNEDAngularVelocity.hpp"

YQ_TYPE_IMPLEMENT(yq::TNEDAngularVelocity)

namespace {
    void    reg_TNEDAngularVelocity()
    {
        auto w = writer<TNEDAngularVelocity>();
        w.description("TNED AngularVelocity");
        w.property(szX, &TNEDAngularVelocity::x);
        w.property(szY, &TNEDAngularVelocity::y);
        w.property(szZ, &TNEDAngularVelocity::z);
    }
    
    YQ_INVOKE(reg_TNEDAngularVelocity();)
}
