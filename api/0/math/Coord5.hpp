////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/math/preamble.hpp>
#include <yq/coord/Coord5.hpp>

namespace yq {
    YQ_NAN_1(Coord5, Coord5<T>(ALL, nan_v<T>))
    YQ_IS_NAN_1(Coord5, is_nan(v.i) || is_nan(v.j) || is_nan(v.k) || is_nan(v.l) || is_nan(v.m))
    YQ_IS_FINITE_1(Coord5, is_finite(v.i) && is_finite(v.j) && is_finite(v.k) && is_finite(v.l) && is_finite(v.m))
    YQ_ZERO_1(Coord5, Coord5<T>( ZERO ))
}
