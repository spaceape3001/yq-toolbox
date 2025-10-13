////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "TENUVector.hpp"

YQ_TYPE_IMPLEMENT(yq::TENUVector)

namespace {
    void    reg_TENUVector()
    {
        auto w = writer<TENUVector>();
        w.description("TENU Vector");
        w.property(szX, &TENUVector::x);
        w.property(szY, &TENUVector::y);
        w.property(szZ, &TENUVector::z);
    }
    
    YQ_INVOKE(reg_TENUVector();)
}
