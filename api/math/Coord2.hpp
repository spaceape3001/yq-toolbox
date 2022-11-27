////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>
#include <basic/Coord2.hpp>

namespace yq {
    YQ_NAN_1(Coord2, Coord2<T>{ nan_v<T>, nan_v<T> })
    YQ_IS_NAN_1(Coord2, is_nan(v.i) || is_nan(v.j) )
    YQ_IS_FINITE_1(Coord2, is_finite(v.i) && is_finite(v.j) )
    YQ_ZERO_1(Coord2, Coord2<T>{ zero_v<T>, zero_v<T> })
}

YQ_TYPE_DECLARE(yq::Coord2D)
YQ_TYPE_DECLARE(yq::Coord2F)
YQ_TYPE_DECLARE(yq::Coord2I)
YQ_TYPE_DECLARE(yq::Coord2U)

