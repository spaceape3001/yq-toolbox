////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "TENUForce.hpp"

YQ_TYPE_IMPLEMENT(yq::TENUForce)

namespace {
    void    reg_TENUForce()
    {
        auto w = writer<TENUForce>();
        w.description("TENU Force");
        w.property(szX, &TENUForce::x);
        w.property(szY, &TENUForce::y);
        w.property(szZ, &TENUForce::z);
    }
    
    YQ_INVOKE(reg_TENUForce();)
}
