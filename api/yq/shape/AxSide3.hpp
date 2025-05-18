////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <yq/typedef/axside3.hpp>

namespace yq {
    template <typename T>
    struct AxSide3 {
        //! Component type (captures the argument)
        using component_type    = T;

        T   lx, hx;
        T   ly, hy;
        T   lz, hz;

        //! Equality operator
        constexpr bool operator==(const AxSide3&) const noexcept = default;
    };
}


