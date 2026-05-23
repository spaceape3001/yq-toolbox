////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "TanSurface.hpp"
#include <yq/core/Enumeration.hxx>

YQ_ENUM_IMPLEMENT(yq::TanSurface)
YQ_TYPE_IMPLEMENT(yq::TanSurface)

namespace {
    void    reg_TanSurface()
    {
        auto w = writer<TanSurface>();
        w.description("Tangent coordinate Direction");
    }
    
    YQ_INVOKE(reg_TanSurface();)
}

