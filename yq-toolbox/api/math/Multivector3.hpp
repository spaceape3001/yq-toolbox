////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>
#include <math/Vector3.hpp>
#include <math/Bivector3.hpp>
#include <math/Trivector3.hpp>

namespace yq {
    template <typename T>
    struct Multivector3 {
        unity_t<T>      a;
        T               x, y, z;
        square_t<T>     xy, yz, zx;
        cube_t<T>       xyz;
        
        bool operator==(const Multivector3&) const = default;
    };

    YQ_IEEE754_1(Multivector3)
    YQ_NAN_1(Multivector3, Multivector3<T>{
        nan_v<unity_t<T>>, 
        nan_v<T>, nan_v<T>, nan_v<T>, 
        nan_v<square_t<T>>, nan_v<square_t<T>>, nan_v<square_t<T>>, 
        nan_v<cube_t<T>>
    })
    YQ_ZERO_1(Multivector3, Multivector3<T>{
        zero_v<unity_t<T>>, 
        zero_v<T>, zero_v<T>, zero_v<T>, 
        zero_v<square_t<T>>, zero_v<square_t<T>>, zero_v<square_t<T>>, 
        zero_v<cube_t<T>>
    })
    
    YQ_IS_NAN_1(Multivector3, 
        is_nan(v.a) || 
        is_nan(v.x) || is_nan(v.y) || is_nan(v.z) || 
        is_nan(v.xy) || is_nan(v.yz) || is_nan(v.zx) || 
        is_nan(v.xyz)
    )
    YQ_IS_FINITE_1(Multivector3, 
        is_finite(v.a) && 
        is_finite(v.x) && is_finite(v.y) && is_finite(v.z) && 
        is_finite(v.xy) && is_finite(v.yz) && is_finite(v.zx) && 
        is_finite(v.xyz)
    )
}

YQ_TYPE_DECLARE(Multivector3D)
YQ_TYPE_DECLARE(Multivector3F)
