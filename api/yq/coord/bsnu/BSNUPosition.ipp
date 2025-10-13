////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "BSNUPosition.hpp"

YQ_TYPE_IMPLEMENT(yq::BSNUPosition)

namespace {
    void    reg_BSNUPosition()
    {
        auto w = writer<BSNUPosition>();
        w.description("BSNU Position");
        w.property(szX, &BSNUPosition::x);
        w.property(szY, &BSNUPosition::y);
        w.property(szZ, &BSNUPosition::z);
    }
    
    YQ_INVOKE(reg_BSNUPosition();)
}
