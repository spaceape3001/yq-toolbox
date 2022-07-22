////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <math/preamble.hpp>
#include <math/Vector4.hpp>

namespace yq {

    /*! \brief Axially aligned box in 4 dimension(s).
    */
    template <typename T>
    struct AxBox4 {
        using component_t   = T;
        
        Vector4<T>  lo, hi;
        
        constexpr bool operator==(const AxBox4&) const noexcept = default;
    };
    
    YQ_IEEE754_1(AxBox4)
    
    YQ_NAN_1(AxBox4, { nan_v<Vector4<T>>, nan_v<Vector4<T>>});
    YQ_ZERO_1(AxBox4, { zero_v<Vector4<T>>, zero_v<Vector4<T>>});


    YQ_IS_FINITE_1( AxBox4, is_finite(v.lo) && is_finite(v.hi))
    YQ_IS_NAN_1(AxBox4, is_nan(v.lo) || is_nan(v.hi))

    
    
}

YQ_TYPE_DECLARE(yq::AxBox4D)
YQ_TYPE_DECLARE(yq::AxBox4F)
YQ_TYPE_DECLARE(yq::AxBox4I)
YQ_TYPE_DECLARE(yq::AxBox4U)

