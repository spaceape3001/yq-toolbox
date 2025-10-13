////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ECEFVector.hpp"

YQ_TYPE_IMPLEMENT(yq::ECEFVector)

namespace {
    void    reg_ECEFVector()
    {
        auto w = writer<ECEFVector>();
        w.description("ECEF Vector");
        w.property(szX, &ECEFVector::x);
        w.property(szY, &ECEFVector::y);
        w.property(szZ, &ECEFVector::z);
    }
    
    YQ_INVOKE(reg_ECEFVector();)
}
