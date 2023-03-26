////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_POLAR2_HPP 1

#include <math/preamble.hpp>

namespace yq {
    template <typename A, typename L>
    struct Polar2 {
        A       angle;
        L       distance;
        
        constexpr Polar2() noexcept = default;
        constexpr Polar2(A _a, L _d) noexcept : angle(_a), distance(_d) {};
        
        constexpr bool    operator==(const Polar2&) const noexcept = default;
    };
}
