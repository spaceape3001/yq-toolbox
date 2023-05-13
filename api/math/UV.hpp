////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/keywords.hpp>

namespace yq {
    template <typename T>
    struct UV {
        T   u;
        T   v;

        constexpr UV() noexcept = default;
        constexpr UV(const T& _u, const T& _v) noexcept : u(_u), v(_v) {}
        constexpr UV(all_t, const T& _val) noexcept : u(_val), v(_val) {}
    };
}

