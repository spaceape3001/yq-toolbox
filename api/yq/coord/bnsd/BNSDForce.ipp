////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "BNSDForce.hpp"

YQ_TYPE_IMPLEMENT(yq::BNSDForce)

namespace {
    void    reg_bnsdForce()
    {
        auto w = writer<BNSDForce>();
        w.description("BNSD Force");
        w.property(szX, &BNSDForce::x);
        w.property(szY, &BNSDForce::y);
        w.property(szZ, &BNSDForce::z);
    }
    
    YQ_INVOKE(reg_bnsdForce();)
}
