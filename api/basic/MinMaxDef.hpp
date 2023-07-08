////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {
    template <typename T>
    struct MinMaxDef {
        using value_type    = T;
        T   min = {};
        T   max = {};
        T   def = {};
        
        constexpr bool operator==(const MinMaxDef&) const = default;
    };
}
