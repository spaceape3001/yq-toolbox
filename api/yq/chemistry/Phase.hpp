////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/meta/MetaBinder.hpp>

namespace yq::chemistry {
    enum class Phase : uint8_t {
        Unknown = 0,
        Solid,
        Liquid,
        Gas,
        Plasma
    };
}

YQ_TYPE_DECLARE(yq::chemistry::Phase)
