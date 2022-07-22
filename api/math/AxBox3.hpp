////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <math/preamble.hpp>
#include <math/Vector3.hpp>

namespace yq {

    /*! \brief Axially aligned box in 3 dimension(s).
    */
    template <typename T>
    struct AxBox3 {
        using component_t   = T;
        
        Vector3<T>  lo, hi;
        
        constexpr bool operator==(const AxBox3&) const noexcept = default;
    };

    YQ_IEEE754_1(AxBox3)
    
    YQ_NAN_1(AxBox3, { nan_v<Vector3<T>>, nan_v<Vector3<T>>});
    YQ_ZERO_1(AxBox3, { zero_v<Vector3<T>>, zero_v<Vector3<T>>});


    YQ_IS_FINITE_1( AxBox3, is_finite(v.lo) && is_finite(v.hi))
    YQ_IS_NAN_1(AxBox3, is_nan(v.lo) || is_nan(v.hi))
}

YQ_TYPE_DECLARE(yq::AxBox3D)
YQ_TYPE_DECLARE(yq::AxBox3F)
YQ_TYPE_DECLARE(yq::AxBox3I)
YQ_TYPE_DECLARE(yq::AxBox3U)

