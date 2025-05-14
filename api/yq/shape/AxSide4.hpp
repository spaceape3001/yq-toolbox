////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <yq/typedef/axside4.hpp>

namespace yq {
    template <typename T>
    struct AxSide4 {
        //! Component type (captures the argument)
        using component_type    = T;

        T   lx, hx;
        T   ly, hy;
        T   lz, hz;
        T   lw, hw;

        //! Equality operator
        constexpr bool operator==(const AxSide4&) const noexcept = default;
    };
}


