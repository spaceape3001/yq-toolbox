////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/math/preamble.hpp>
#include <yq/coord/Coord2.hpp>

namespace yq {
    YQ_NAN_1(Coord2, Coord2<T>( nan_v<T>, nan_v<T> ))
    YQ_IS_NAN_1(Coord2, is_nan(v.i) || is_nan(v.j) )
    YQ_IS_FINITE_1(Coord2, is_finite(v.i) && is_finite(v.j) )
    YQ_ZERO_1(Coord2, Coord2<T>( zero_v<T>, zero_v<T> ))
}
