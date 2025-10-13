////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ECEFForce.hpp"

YQ_TYPE_IMPLEMENT(yq::ECEFForce)

namespace {
    void    reg_ECEFForce()
    {
        auto w = writer<ECEFForce>();
        w.description("ECEF Force");
        w.property(szX, &ECEFForce::x);
        w.property(szY, &ECEFForce::y);
        w.property(szZ, &ECEFForce::z);
    }
    
    YQ_INVOKE(reg_ECEFForce();)
}
