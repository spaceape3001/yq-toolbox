////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <array>
#include <span>

namespace yq {
    template <typename T, size_t N>
    constexpr std::span<const T> span(const std::array<T, N>& data) noexcept
    {
        return std::span<const T>(data.data(), N);
    }
}
