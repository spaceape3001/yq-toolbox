////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>
#include <math/Vector3.hpp>
#include "TetrahedronData.hpp"

namespace yq {

    YQ_IEEE754_1(Tetrahedron3)

    YQ_NAN_1(Tetrahedron3, { nan_v<Vector3<T>>, nan_v<Vector3<T>>, nan_v<Vector3<T>>, nan_v<Vector3<T>> })
    YQ_ZERO_1(Tetrahedron3, { zero_v<Vector3<T>>, zero_v<Vector3<T>>, zero_v<Vector3<T>>, zero_v<Vector3<T>> })


    YQ_IS_FINITE_1(Tetrahedron3, is_finite(v.a) && is_finite(v.b) && is_finite(v.c) && is_finite(v.d))
    YQ_IS_NAN_1(Tetrahedron3, is_nan(v.a) || is_nan(v.b) || is_nan(v.c) || is_nan(v.d))

}

YQ_TYPE_DECLARE(yq::Tetrahedron3D)
YQ_TYPE_DECLARE(yq::Tetrahedron3F)
YQ_TYPE_DECLARE(yq::Tetrahedron3I)
YQ_TYPE_DECLARE(yq::Tetrahedron3U)

