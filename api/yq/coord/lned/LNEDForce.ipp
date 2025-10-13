////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "LNEDForce.hpp"

YQ_TYPE_IMPLEMENT(yq::LNEDForce)

namespace {
    void    reg_LNEDForce()
    {
        auto w = writer<LNEDForce>();
        w.description("LNED Force");
        w.property(szX, &LNEDForce::x);
        w.property(szY, &LNEDForce::y);
        w.property(szZ, &LNEDForce::z);
    }
    
    YQ_INVOKE(reg_LNEDForce();)
}
