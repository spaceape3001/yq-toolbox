////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <yq/typedef/axside1.hpp>

namespace yq {
    template <typename T>
    struct AxSide1 {
        //! Component type (captures the argument)
        using component_type    = T;

        T   lx, hx;

        //! Equality operator
        constexpr bool operator==(const AxSide1&) const noexcept = default;
    };
}


