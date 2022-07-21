////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <math/preamble.hpp>
#include <math/Vector1.hpp>
#include "SegmentData.hpp"

namespace yq {
    YQ_IEEE754_1(Segment1)

    YQ_NAN_1(Segment1, { nan_v<Vector1<T>>, nan_v<Vector1<T>>});
    YQ_ZERO_1(Segment1, { zero_v<Vector1<T>>, zero_v<Vector1<T>>});

    YQ_IS_FINITE_1( Segment1, is_finite(v.a) && is_finite(v.b))
    YQ_IS_NAN_1(Segment1, is_nan(v.a) || is_nan(v.b))
}
YQ_TYPE_DECLARE(yq::Segment1D)
YQ_TYPE_DECLARE(yq::Segment1F)
YQ_TYPE_DECLARE(yq::Segment1I)
YQ_TYPE_DECLARE(yq::Segment1U)

