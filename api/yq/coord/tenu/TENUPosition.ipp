////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "TENUPosition.hpp"

YQ_TYPE_IMPLEMENT(yq::TENUPosition)

namespace {
    void    reg_TENUPosition()
    {
        auto w = writer<TENUPosition>();
        w.description("TENU Position");
        w.property(szX, &TENUPosition::x);
        w.property(szY, &TENUPosition::y);
        w.property(szZ, &TENUPosition::z);
    }
    
    YQ_INVOKE(reg_TENUPosition();)
}
