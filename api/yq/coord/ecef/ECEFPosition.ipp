////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ECEFPosition.hpp"

YQ_TYPE_IMPLEMENT(yq::ECEFPosition)

namespace {
    void    reg_ECEFPosition()
    {
        auto w = writer<ECEFPosition>();
        w.description("ECEF Position");
        w.property(szX, &ECEFPosition::x);
        w.property(szY, &ECEFPosition::y);
        w.property(szZ, &ECEFPosition::z);
    }
    
    YQ_INVOKE(reg_ECEFPosition();)
}
