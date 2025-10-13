////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "BSNUAngularAcceleration.hpp"

YQ_TYPE_IMPLEMENT(yq::BSNUAngularAcceleration)

namespace {
    void    reg_BSNUAngularAcceleration()
    {
        auto w = writer<BSNUAngularAcceleration>();
        w.description("BSNU AngularAcceleration");
        w.property(szX, &BSNUAngularAcceleration::x);
        w.property(szY, &BSNUAngularAcceleration::y);
        w.property(szZ, &BSNUAngularAcceleration::z);
    }
    
    YQ_INVOKE(reg_BSNUAngularAcceleration();)
}
