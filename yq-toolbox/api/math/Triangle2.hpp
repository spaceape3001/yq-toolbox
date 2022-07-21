////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "TriangleData.hpp"
#include <math/preamble.hpp>
#include <math/Vector2.hpp>

namespace yq {

    YQ_IEEE754_1(Triangle2)

    YQ_NAN_1(Triangle2, { nan_v<Vector2<T>>, nan_v<Vector2<T>>, nan_v<Vector2<T>> })
    YQ_ZERO_1(Triangle2, { zero_v<Vector2<T>>, zero_v<Vector2<T>>, zero_v<Vector2<T>> })

    YQ_IS_FINITE_1(Triangle2, is_finite(v.a) && is_finite(v.b) && is_finite(v.c))
    YQ_IS_NAN_1(Triangle2, is_nan(v.a) || is_nan(v.b) || is_nan(v.c) )

}

YQ_TYPE_DECLARE(yq::Triangle2D)
YQ_TYPE_DECLARE(yq::Triangle2F)
YQ_TYPE_DECLARE(yq::Triangle2I)
YQ_TYPE_DECLARE(yq::Triangle2U)

