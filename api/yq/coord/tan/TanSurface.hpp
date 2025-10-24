////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <yq/core/Enum.hpp>
#include <yq/meta/MetaBinder.hpp>

namespace yq {
    YQ_ENUM(TanSurface, , 
        Unknown,
        xPositive,
        xNegative,
        yPositive,
        yNegative,
        zPositive,
        zNegative
    )
}

YQ_TYPE_DECLARE(yq::TanSurface)

