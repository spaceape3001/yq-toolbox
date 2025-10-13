////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ECIVector.hpp"

YQ_TYPE_IMPLEMENT(yq::ECIVector)

namespace {
    void    reg_ECIVector()
    {
        auto w = writer<ECIVector>();
        w.description("ECI Vector");
        w.property(szX, &ECIVector::x);
        w.property(szY, &ECIVector::y);
        w.property(szZ, &ECIVector::z);
    }
    
    YQ_INVOKE(reg_ECIVector();)
}
