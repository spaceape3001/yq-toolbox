////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <yq/typedef/axside2.hpp>

namespace yq {
    template <typename T>
    struct AxSide2 {
        //! Component type (captures the argument)
        using component_type    = T;

        T   lx, hx;
        T   ly, hy;

        //! Equality operator
        constexpr bool operator==(const AxSide2&) const noexcept = default;
    };
}


