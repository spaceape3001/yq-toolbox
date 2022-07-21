////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <math/preamble.hpp>
#include <math/Vector2.hpp>

namespace yq {

    /*! \brief Axially aligned box in 2 dimension(s).
    
        Note, lo vs hi isn't enforced, however it's expected that lo < hi, which 
        is what "is_valid" of "shape_math.hpp" will check.
    */
    template <typename T>
    struct AxBox2 {
        using component_t   = T;
        
        Vector2<T>  lo; //!< Lower bounds
        Vector2<T>  hi; //!< Upper bounds
        
        constexpr bool operator==(const AxBox2&) const noexcept = default;
    };

    YQ_IEEE754_1(AxBox2)
    
    YQ_NAN_1(AxBox2, { nan_v<Vector2<T>>, nan_v<Vector2<T>>});
    YQ_ZERO_1(AxBox2, { zero_v<Vector2<T>>, zero_v<Vector2<T>>});

    YQ_IS_FINITE_1( AxBox2, is_finite(v.lo) && is_finite(v.hi))
    YQ_IS_NAN_1(AxBox2, is_nan(v.lo) || is_nan(v.hi))
}

YQ_TYPE_DECLARE(yq::AxBox2D)
YQ_TYPE_DECLARE(yq::AxBox2F)
YQ_TYPE_DECLARE(yq::AxBox2I)
YQ_TYPE_DECLARE(yq::AxBox2U)

