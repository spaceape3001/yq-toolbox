////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <yq/meta/MetaBinder.hpp>

namespace yq {
    enum class TanSurface {
        Unknown,
        xPositive,
        xNegative,
        yPositive,
        yNegative,
        zPositive,
        zNegative
    };
}

YQ_TYPE_DECLARE(yq::TanSurface)

