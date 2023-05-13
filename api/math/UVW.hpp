////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {
    template <typename T>
    struct UVW {
        T   u;
        T   v;
        T   w;
        
        constexpr const UVW() noexcept = default;
        constexpr const UVW(const T& _u, const T& _v, const T& _w) noexcept : u(_u), v(_v), w(_w) {}
    };
}

