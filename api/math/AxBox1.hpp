////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <math/preamble.hpp>
#include <math/Vector1.hpp>

namespace yq {

    /*! \brief Axially aligned box in 1 dimension(s).
    */
    template <typename T>
    struct AxBox1 {
        using component_t   = T;
        
        Vector1<T>  lo, hi;
        
        constexpr bool operator==(const AxBox1&) const noexcept = default;
    };
    
    YQ_IEEE754_1(AxBox1)
    
    YQ_NAN_1(AxBox1, { nan_v<Vector1<T>>, nan_v<Vector1<T>>});
    YQ_ZERO_1(AxBox1, { zero_v<Vector1<T>>, zero_v<Vector1<T>>});


    YQ_IS_FINITE_1( AxBox1, is_finite(v.lo) && is_finite(v.hi))
    YQ_IS_NAN_1(AxBox1, is_nan(v.lo) || is_nan(v.hi))
}

YQ_TYPE_DECLARE(yq::AxBox1D)
YQ_TYPE_DECLARE(yq::AxBox1F)
YQ_TYPE_DECLARE(yq::AxBox1I)
YQ_TYPE_DECLARE(yq::AxBox1U)

