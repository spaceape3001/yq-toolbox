////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>
#include <math/Vector2.hpp>

namespace yq {
    template <typename T>
    struct Circle2 {
        using component_t   = T;

        Vector2<T>  point;
        T           radius;
        
        constexpr bool operator==(const Circle2&) const noexcept = default;
    };

    YQ_IEEE754_1(Circle2)


    YQ_NAN_1(Circle2, { nan_v<Vector2<T>>, nan_v<T> })
    YQ_ZERO_1(Circle2, { zero_v<Vector2<T>>, zero_v<T> })

    
    YQ_IS_FINITE_1(Circle2, is_finite(v.point) && is_finite(v.radius))
    YQ_IS_NAN_1(Circle2, is_nan(v.point) || is_nan(v.radius))

}

YQ_TYPE_DECLARE(yq::Circle2D)
YQ_TYPE_DECLARE(yq::Circle2F)
YQ_TYPE_DECLARE(yq::Circle2I)
YQ_TYPE_DECLARE(yq::Circle2U)

