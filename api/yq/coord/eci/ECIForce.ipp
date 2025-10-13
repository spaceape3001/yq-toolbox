////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ECIForce.hpp"

YQ_TYPE_IMPLEMENT(yq::ECIForce)

namespace {
    void    reg_ECIForce()
    {
        auto w = writer<ECIForce>();
        w.description("ECI Force");
        w.property(szX, &ECIForce::x);
        w.property(szY, &ECIForce::y);
        w.property(szZ, &ECIForce::z);
    }
    
    YQ_INVOKE(reg_ECIForce();)
}
