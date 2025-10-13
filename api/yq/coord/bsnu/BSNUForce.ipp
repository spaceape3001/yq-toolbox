////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "BSNUForce.hpp"

YQ_TYPE_IMPLEMENT(yq::BSNUForce)

namespace {
    void    reg_BSNUForce()
    {
        auto w = writer<BSNUForce>();
        w.description("BSNU Force");
        w.property(szX, &BSNUForce::x);
        w.property(szY, &BSNUForce::y);
        w.property(szZ, &BSNUForce::z);
    }
    
    YQ_INVOKE(reg_BSNUForce();)
}
