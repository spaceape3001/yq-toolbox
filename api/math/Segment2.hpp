////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>
#include <math/Vector2.hpp>
#include "SegmentData.hpp"

namespace yq {
    YQ_IEEE754_1(Segment2)

    YQ_NAN_1(Segment2, { nan_v<Vector2<T>>, nan_v<Vector2<T>>});
    YQ_ZERO_1(Segment2, { zero_v<Vector2<T>>, zero_v<Vector2<T>>});

    YQ_IS_FINITE_1( Segment2, is_finite(v.a) && is_finite(v.b))
    YQ_IS_NAN_1(Segment2, is_nan(v.a) || is_nan(v.b))
}

YQ_TYPE_DECLARE(yq::Segment2D)
YQ_TYPE_DECLARE(yq::Segment2F)
YQ_TYPE_DECLARE(yq::Segment2I)
YQ_TYPE_DECLARE(yq::Segment2U)

