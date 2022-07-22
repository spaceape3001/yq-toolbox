////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <math/preamble.hpp>

namespace yq {
    template <typename T>
    struct AxCorners4 {
        using component_type    = T;
    
        T   llll;
        T   lllh;
        T   llhl;
        T   llhh;
        T   lhll;
        T   lhlh;
        T   lhhl;
        T   lhhh;

        T   hlll;
        T   hllh;
        T   hlhl;
        T   hlhh;
        T   hhll;
        T   hhlh;
        T   hhhl;
        T   hhhh;

        bool operator==(const AxCorners4&) const noexcept = default;
    };
}

