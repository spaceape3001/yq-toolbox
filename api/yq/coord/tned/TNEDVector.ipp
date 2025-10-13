////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "TNEDVector.hpp"

YQ_TYPE_IMPLEMENT(yq::TNEDVector)

namespace {
    void    reg_TNEDVector()
    {
        auto w = writer<TNEDVector>();
        w.description("TNED Vector");
        w.property(szX, &TNEDVector::x);
        w.property(szY, &TNEDVector::y);
        w.property(szZ, &TNEDVector::z);
    }
    
    YQ_INVOKE(reg_TNEDVector();)
}
