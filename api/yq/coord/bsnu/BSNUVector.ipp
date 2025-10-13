////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "BSNUVector.hpp"

YQ_TYPE_IMPLEMENT(yq::BSNUVector)

namespace {
    void    reg_BSNUVector()
    {
        auto w = writer<BSNUVector>();
        w.description("BSNU Vector");
        w.property(szX, &BSNUVector::x);
        w.property(szY, &BSNUVector::y);
        w.property(szZ, &BSNUVector::z);
    }
    
    YQ_INVOKE(reg_BSNUVector();)
}
