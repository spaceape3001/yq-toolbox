////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "LNEDAngularVelocity.hpp"

YQ_TYPE_IMPLEMENT(yq::LNEDAngularVelocity)

namespace {
    void    reg_LNEDAngularVelocity()
    {
        auto w = writer<LNEDAngularVelocity>();
        w.description("LNED AngularVelocity");
        w.property(szX, &LNEDAngularVelocity::x);
        w.property(szY, &LNEDAngularVelocity::y);
        w.property(szZ, &LNEDAngularVelocity::z);
    }
    
    YQ_INVOKE(reg_LNEDAngularVelocity();)
}
