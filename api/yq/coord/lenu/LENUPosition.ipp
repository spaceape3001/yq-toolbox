////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "LENUPosition.hpp"

YQ_TYPE_IMPLEMENT(yq::LENUPosition)

namespace {
    void    reg_LENUPosition()
    {
        auto w = writer<LENUPosition>();
        w.description("LENU Position");
        w.property(szX, &LENUPosition::x);
        w.property(szY, &LENUPosition::y);
        w.property(szZ, &LENUPosition::z);
    }
    
    YQ_INVOKE(reg_LENUPosition();)
}
