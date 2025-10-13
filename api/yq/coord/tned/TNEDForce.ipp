////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "TNEDForce.hpp"

YQ_TYPE_IMPLEMENT(yq::TNEDForce)

namespace {
    void    reg_TNEDForce()
    {
        auto w = writer<TNEDForce>();
        w.description("TNED Force");
        w.property(szX, &TNEDForce::x);
        w.property(szY, &TNEDForce::y);
        w.property(szZ, &TNEDForce::z);
    }
    
    YQ_INVOKE(reg_TNEDForce();)
}
