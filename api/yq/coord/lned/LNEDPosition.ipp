////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "LNEDPosition.hpp"

YQ_TYPE_IMPLEMENT(yq::LNEDPosition)

namespace {
    void    reg_LNEDPosition()
    {
        auto w = writer<LNEDPosition>();
        w.description("LNED Position");
        w.property(szX, &LNEDPosition::x);
        w.property(szY, &LNEDPosition::y);
        w.property(szZ, &LNEDPosition::z);
    }
    
    YQ_INVOKE(reg_LNEDPosition();)
}
