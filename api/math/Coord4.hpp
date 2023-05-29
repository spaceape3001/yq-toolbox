////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>
#include <basic/Coord4.hpp>

namespace yq {
    YQ_NAN_1(Coord4, Coord4<T>(ALL, nan_v<T>))
    YQ_IS_NAN_1(Coord4, is_nan(v.i) || is_nan(v.j) || is_nan(v.k) || is_nan(v.l))
    YQ_IS_FINITE_1(Coord4, is_finite(v.i) && is_finite(v.j) && is_finite(v.k) && is_finite(v.l))
    YQ_ZERO_1(Coord4, Coord4<T>( ZERO ))
}

YQ_TYPE_DECLARE(yq::Coord4D)
YQ_TYPE_DECLARE(yq::Coord4F)
YQ_TYPE_DECLARE(yq::Coord4I)
YQ_TYPE_DECLARE(yq::Coord4U)

