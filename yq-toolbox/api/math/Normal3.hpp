////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>
#include <math/Vector3.hpp>

namespace yq {
    template <typename T>
    struct Normal3 {
        using component_type    = T;
        Vector3<T>              direction;
        
        constexpr bool operator==(const Normal3& rhs) const noexcept = default;
    };
    
    YQ_IEEE754_1(Normal3)
    
    YQ_NAN_1(Normal3, { nan_v<Vector3<T>> })
    YQ_ZERO_1(Normal3, { zero_v<Vector3<T>> })
    
    YQ_IS_NAN_1(Normal3, is_nan(v.direction))
    YQ_IS_FINITE_1(Normal3, is_finite(v.direction))
}

YQ_TYPE_DECLARE(yq::Normal3D)
YQ_TYPE_DECLARE(yq::Normal3F)
