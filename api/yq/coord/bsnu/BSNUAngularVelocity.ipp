////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "BSNUAngularVelocity.hpp"

YQ_TYPE_IMPLEMENT(yq::BSNUAngularVelocity)

namespace {
    void    reg_BSNUAngularVelocity()
    {
        auto w = writer<BSNUAngularVelocity>();
        w.description("BSNU AngularVelocity");
        w.property(szX, &BSNUAngularVelocity::x);
        w.property(szY, &BSNUAngularVelocity::y);
        w.property(szZ, &BSNUAngularVelocity::z);
    }
    
    YQ_INVOKE(reg_BSNUAngularVelocity();)
}
