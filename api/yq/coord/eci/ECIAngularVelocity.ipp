////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ECIAngularVelocity.hpp"

YQ_TYPE_IMPLEMENT(yq::ECIAngularVelocity)

namespace {
    void    reg_ECIAngularVelocity()
    {
        auto w = writer<ECIAngularVelocity>();
        w.description("ECI AngularVelocity");
        w.property(szX, &ECIAngularVelocity::x);
        w.property(szY, &ECIAngularVelocity::y);
        w.property(szZ, &ECIAngularVelocity::z);
    }
    
    YQ_INVOKE(reg_ECIAngularVelocity();)
}
