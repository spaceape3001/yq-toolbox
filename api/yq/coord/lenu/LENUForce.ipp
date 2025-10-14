////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once


#include "LENUForce.hpp"

YQ_TYPE_IMPLEMENT(yq::LENUForce)

namespace {
    void    reg_LENUForce()
    {
        auto w = writer<LENUForce>();
        w.description("LENU Force");
        w.property(szX, &LENUForce::x);
        w.property(szY, &LENUForce::y);
        w.property(szZ, &LENUForce::z);
    }
    
    YQ_INVOKE(reg_LENUForce();)
}
