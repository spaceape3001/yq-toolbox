////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/keywords.hpp>

namespace yq {
    template <typename T>
    struct UVW {
        T   u;
        T   v;
        T   w;
        
        constexpr UVW() noexcept = default;
        constexpr UVW(const T& _u, const T& _v, const T& _w) noexcept : u(_u), v(_v), w(_w) {}
        constexpr UVW(all_t, const T& _val) noexcept : u(_val), v(_val), w(_val) {}
    };
}

