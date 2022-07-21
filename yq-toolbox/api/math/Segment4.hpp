////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <math/preamble.hpp>
#include <math/Vector4.hpp>
#include "SegmentData.hpp"

namespace yq {

    YQ_IEEE754_1(Segment4)

    YQ_NAN_1(Segment4, { nan_v<Vector4<T>>, nan_v<Vector4<T>>});
    YQ_ZERO_1(Segment4, { zero_v<Vector4<T>>, zero_v<Vector4<T>>});

    YQ_IS_FINITE_1( Segment4, is_finite(v.a) && is_finite(v.b))
    YQ_IS_NAN_1(Segment4, is_nan(v.a) || is_nan(v.b))
    
}
YQ_TYPE_DECLARE(yq::Segment4D)
YQ_TYPE_DECLARE(yq::Segment4F)
YQ_TYPE_DECLARE(yq::Segment4I)
YQ_TYPE_DECLARE(yq::Segment4U)

