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
    struct Normal2 {
        using component_type    = T;
        Vector2<T>              direction;
        
        constexpr bool operator==(const Normal2& rhs) const noexcept = default;
    };
    
    YQ_IEEE754_1(Normal2)
        
    YQ_NAN_1(Normal2, { nan_v<Vector2<T>> })
    YQ_ZERO_1(Normal2, { zero_v<Vector2<T>> })
    

    YQ_IS_NAN_1(Normal2, is_nan(v.direction))
    YQ_IS_FINITE_1(Normal2, is_finite(v.direction))
    
}

YQ_TYPE_DECLARE(yq::Normal2D)
YQ_TYPE_DECLARE(yq::Normal2F)
