////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "TanSurface.hpp"

YQ_TYPE_IMPLEMENT(yq::TanSurface)

namespace {
    void    reg_TanSurface()
    {
        auto w = writer<TanSurface>();
        w.description("Tangent coordinate Direction");
    }
    
    YQ_INVOKE(reg_TanSurface();)
}

