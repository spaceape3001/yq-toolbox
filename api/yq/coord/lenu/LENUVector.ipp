////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "LENUVector.hpp"

YQ_TYPE_IMPLEMENT(yq::LENUVector)

namespace {
    void    reg_LENUVector()
    {
        auto w = writer<LENUVector>();
        w.description("LENU Vector");
        w.property(szX, &LENUVector::x);
        w.property(szY, &LENUVector::y);
        w.property(szZ, &LENUVector::z);
    }
    
    YQ_INVOKE(reg_LENUVector();)
}
