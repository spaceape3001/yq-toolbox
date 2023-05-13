////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {
    template <typename T>
    struct UV {
        T   u;
        T   v;

        constexpr const UV() noexcept = default;
        constexpr const UV(const T& _u, const T& _v) noexcept : u(_u), v(_v) {}
    };
}

