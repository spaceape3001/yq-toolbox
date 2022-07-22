////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>
#include <math/Vector4.hpp>
#include <math/Bivector4.hpp>
#include <math/Trivector4.hpp>
#include <math/Quadvector4.hpp>

namespace yq {
    template <typename T>
    struct Multivector4 {
        unity_t<T>      a;
        T               x, y, z, w;
        square_t<T>     xy, yz, zw, wx, xz, yw;
        cube_t<T>       xyz, yzw, zwx, wxy;
        fourth_t<T>     xyzw;
        
        bool operator==(const Multivector4&) const = default;
    };

    YQ_IEEE754_1(Multivector4)
    YQ_NAN_1(Multivector4, Multivector4<T>{
        nan_v<unity_t<T>>, 
        nan_v<T>, nan_v<T>, nan_v<T>, nan_v<T>, 
        nan_v<square_t<T>>, nan_v<square_t<T>>, nan_v<square_t<T>>, nan_v<square_t<T>>, nan_v<square_t<T>>, nan_v<square_t<T>>, 
        nan_v<cube_t<T>>, nan_v<cube_t<T>>, nan_v<cube_t<T>>, nan_v<cube_t<T>>,
        nan_v<fourth_t<T>>
    })
    YQ_ZERO_1(Multivector4, Multivector4<T>{
        zero_v<unity_t<T>>, 
        zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
        zero_v<square_t<T>>, zero_v<square_t<T>>, zero_v<square_t<T>>, zero_v<square_t<T>>, zero_v<square_t<T>>, zero_v<square_t<T>>, 
        zero_v<cube_t<T>>, zero_v<cube_t<T>>, zero_v<cube_t<T>>, zero_v<cube_t<T>>,
        zero_v<fourth_t<T>>
    })
    
    YQ_IS_NAN_1(Multivector4, 
        is_nan(v.a) || 
        is_nan(v.x) || is_nan(v.y) || is_nan(v.z) || is_nan(v.w) ||
        is_nan(v.xy) || is_nan(v.yz) || is_nan(v.zw) || is_nan(v.wx) || is_nan(v.xz) || is_nan(v.yw) ||
        is_nan(v.xyz) || is_nan(v.yzw) || is_nan(v.zwx) || is_nan(v.wxy) ||
        is_nan(v.xyzw)
    )
    YQ_IS_FINITE_1(Multivector4, 
        is_finite(v.a) && 
        is_finite(v.x) && is_finite(v.y) && is_finite(v.z) && is_finite(v.w) &&
        is_finite(v.xy) && is_finite(v.yz) && is_finite(v.zw) && is_finite(v.wx) && is_finite(v.xz) && is_finite(v.yw) &&
        is_finite(v.xyz) && is_finite(v.yzw) && is_finite(v.zwx) && is_finite(v.wxy) &&
        is_finite(v.xyzw)
    )
}

YQ_TYPE_DECLARE(Multivector4D)
YQ_TYPE_DECLARE(Multivector4F)

