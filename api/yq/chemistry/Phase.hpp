////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Enum.hpp>
#include <yq/meta/MetaBinder.hpp>

namespace yq::chemistry {
    YQ_ENUM( Phase, ,
        Unknown = 0,
        Solid,
        Liquid,
        Gas,
        Plasma
    )
}

YQ_TYPE_DECLARE(yq::chemistry::Phase)
