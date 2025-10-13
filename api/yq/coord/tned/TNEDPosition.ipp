////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "TNEDPosition.hpp"

YQ_TYPE_IMPLEMENT(yq::TNEDPosition)

namespace {
    void    reg_TNEDPosition()
    {
        auto w = writer<TNEDPosition>();
        w.description("TNED Position");
        w.property(szX, &TNEDPosition::x);
        w.property(szY, &TNEDPosition::y);
        w.property(szZ, &TNEDPosition::z);
    }
    
    YQ_INVOKE(reg_TNEDPosition();)
}
