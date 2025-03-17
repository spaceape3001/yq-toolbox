////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Flags.hpp>

namespace yq::spatial {
    enum class Dim : uint8_t {
        D0  = 0,
        D1,
        D2,
        D3,
        D4,
        D5,
        D6
    };
    
    using DimFlags = Flags<Dim, uint8_t>;
}
