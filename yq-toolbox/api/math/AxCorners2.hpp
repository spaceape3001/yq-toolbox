////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <math/preamble.hpp>

namespace yq {
    template <typename T>
    struct AxCorners2 {
        using component_type    = T;
    
        T   ll;
        T   lh;
        T   hl;
        T   hh;
        
        bool operator==(const AxCorners2&) const noexcept = default;
    };
}

