////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "BNSDVector.hpp"

YQ_TYPE_IMPLEMENT(yq::BNSDVector)

namespace {
    void    reg_bnsdVector()
    {
        auto w = writer<BNSDVector>();
        w.description("BNSD Vector");
        w.property(szX, &BNSDVector::x);
        w.property(szY, &BNSDVector::y);
        w.property(szZ, &BNSDVector::z);
    }
    
    YQ_INVOKE(reg_bnsdVector();)
}
