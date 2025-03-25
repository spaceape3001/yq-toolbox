////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/keywords.hpp>

namespace yq {
    template <typename T>
    struct AllLocal {
        T   all;
        T   local;
        
        constexpr T&        operator[](all_k) noexcept { return all; }
        constexpr const T&  operator[](all_k) const noexcept { return all; }
        constexpr T&        operator[](local_k) noexcept { return local; }
        constexpr const T&  operator[](local_k) const noexcept { return local; }
        constexpr T&        operator[](bool f) noexcept { return f ? all : local; }
        constexpr const T&  operator[](bool f) const noexcept { return f ? all : local; }
    };
}
