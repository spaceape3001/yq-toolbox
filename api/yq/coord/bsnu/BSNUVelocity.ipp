////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "BSNUVelocity.hpp"

YQ_TYPE_IMPLEMENT(yq::BSNUVelocity)

namespace {
    void    reg_BSNUVelocity()
    {
        auto w = writer<BSNUVelocity>();
        w.description("BSNU Velocity");
        w.property(szX, &BSNUVelocity::x);
        w.property(szY, &BSNUVelocity::y);
        w.property(szZ, &BSNUVelocity::z);
    }
    
    YQ_INVOKE(reg_BSNUVelocity();)
}
