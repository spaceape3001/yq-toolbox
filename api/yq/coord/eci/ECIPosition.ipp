////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ECIPosition.hpp"

YQ_TYPE_IMPLEMENT(yq::ECIPosition)

namespace {
    void    reg_ECIPosition()
    {
        auto w = writer<ECIPosition>();
        w.description("ECI Position");
        w.property(szX, &ECIPosition::x);
        w.property(szY, &ECIPosition::y);
        w.property(szZ, &ECIPosition::z);
    }
    
    YQ_INVOKE(reg_ECIPosition();)
}
