////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>
#include <basic/Coord1.hpp>

namespace yq {
    YQ_NAN_1(Coord1, Coord1<T>( nan_v<T> ))
    YQ_IS_NAN_1(Coord1, is_nan(v.i) )
    YQ_IS_FINITE_1(Coord1, is_finite(v.i) )
    YQ_ZERO_1(Coord1, Coord1<T>( zero_v<T> ))
}

YQ_TYPE_DECLARE(yq::Coord1D)
YQ_TYPE_DECLARE(yq::Coord1F)
YQ_TYPE_DECLARE(yq::Coord1I)
YQ_TYPE_DECLARE(yq::Coord1U)

