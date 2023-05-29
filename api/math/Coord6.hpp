////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>
#include <basic/Coord6.hpp>

namespace yq {
    YQ_NAN_1(Coord6, Coord6<T>(ALL, nan_v<T>))
    YQ_IS_NAN_1(Coord6, is_nan(v.i) || is_nan(v.j) || is_nan(v.k) || is_nan(v.l) || is_nan(v.m) || is_nan(v.n))
    YQ_IS_FINITE_1(Coord6, is_finite(v.i) && is_finite(v.j) && is_finite(v.k) && is_finite(v.l) && is_finite(v.m) && is_finite(v.n))
    YQ_ZERO_1(Coord6, Coord6<T>( ZERO ))
}

YQ_TYPE_DECLARE(yq::Coord6D)
YQ_TYPE_DECLARE(yq::Coord6F)
YQ_TYPE_DECLARE(yq::Coord6I)
YQ_TYPE_DECLARE(yq::Coord6U)

