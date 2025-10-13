////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "BSNUAcceleration.hpp"

YQ_TYPE_IMPLEMENT(yq::BSNUAcceleration)

namespace {
    void    reg_BSNUAcceleration()
    {
        auto w = writer<BSNUAcceleration>();
        w.description("BSNU Acceleration");
        w.property(szX, &BSNUAcceleration::x);
        w.property(szY, &BSNUAcceleration::y);
        w.property(szZ, &BSNUAcceleration::z);
    }
    
    YQ_INVOKE(reg_BSNUAcceleration();)
}
