////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "TNEDDisplacement.hpp"

YQ_TYPE_IMPLEMENT(yq::TNEDDisplacement)

namespace {
    void    reg_TNEDDisplacement()
    {
        auto w = writer<TNEDDisplacement>();
        w.description("TNED Displacement");
        w.property(szX, &TNEDDisplacement::x);
        w.property(szY, &TNEDDisplacement::y);
        w.property(szZ, &TNEDDisplacement::z);
    }
    
    YQ_INVOKE(reg_TNEDDisplacement();)
}
