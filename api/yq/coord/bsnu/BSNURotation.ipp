////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "BSNURotation.hpp"

YQ_TYPE_IMPLEMENT(yq::BSNURotation)

namespace {
    void    reg_BSNURotation()
    {
        auto w = writer<BSNURotation>();
        w.description("BSNU Rotation");
        w.property(szX, &BSNURotation::x);
        w.property(szY, &BSNURotation::y);
        w.property(szZ, &BSNURotation::z);
    }
    
    YQ_INVOKE(reg_BSNURotation();)
}
