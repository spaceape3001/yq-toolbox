////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <math/preamble.hpp>
#include <math/Vector3.hpp>
#include "SegmentData.hpp"

namespace yq {
    YQ_IEEE754_1(Segment3)

    YQ_NAN_1(Segment3, { nan_v<Vector3<T>>, nan_v<Vector3<T>>});
    YQ_ZERO_1(Segment3, { zero_v<Vector3<T>>, zero_v<Vector3<T>>});

    YQ_IS_FINITE_1( Segment3, is_finite(v.a) && is_finite(v.b))
    YQ_IS_NAN_1(Segment3, is_nan(v.a) || is_nan(v.b))
}

YQ_TYPE_DECLARE(yq::Segment3D)
YQ_TYPE_DECLARE(yq::Segment3F)
YQ_TYPE_DECLARE(yq::Segment3I)
YQ_TYPE_DECLARE(yq::Segment3U)

