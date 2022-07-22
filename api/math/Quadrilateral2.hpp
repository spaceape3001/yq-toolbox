////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "QuadrilateralData.hpp"
#include <math/preamble.hpp>
#include <math/Vector2.hpp>

namespace yq {
//  --------------------------------------------------------
//  COMPOSITION

    YQ_NAN_1(Quadrilateral2, { nan_v<Vector2<T>>, nan_v<Vector2<T>>, nan_v<Vector2<T>>, nan_v<Vector2<T>> })
    YQ_ZERO_1(Quadrilateral2, { zero_v<Vector2<T>>, zero_v<Vector2<T>>, zero_v<Vector2<T>>, zero_v<Vector2<T>> })

//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_FINITE_1(Quadrilateral2, is_finite(v.a) && is_finite(v.b) && is_finite(v.c) && is_finite(v.d))
    YQ_IS_NAN_1(Quadrilateral2, is_nan(v.a) || is_nan(v.b) || is_nan(v.c) || is_nan(v.d) )

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

}

YQ_TYPE_DECLARE(yq::Quadrilateral2D)
YQ_TYPE_DECLARE(yq::Quadrilateral2F)
YQ_TYPE_DECLARE(yq::Quadrilateral2I)
YQ_TYPE_DECLARE(yq::Quadrilateral2U)

