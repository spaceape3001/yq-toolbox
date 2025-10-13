////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "LNEDVector.hpp"

YQ_TYPE_IMPLEMENT(yq::LNEDVector)

namespace {
    void    reg_LNEDVector()
    {
        auto w = writer<LNEDVector>();
        w.description("LNED Vector");
        w.property(szX, &LNEDVector::x);
        w.property(szY, &LNEDVector::y);
        w.property(szZ, &LNEDVector::z);
    }
    
    YQ_INVOKE(reg_LNEDVector();)
}
