////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>

namespace yq {
    template <typename T>
    struct Bivector4 {
        using component_type = T;
        square_t<T>     xy, yz, zw, wx, xz, yw;
        bool operator==(const Bivector4&) const = default;
    };
    
    YQ_IEEE754_1(Bivector4)


    constexpr Bivector4D   operator "" _xy4(unsigned long long int v)
    {
        return {(double) v, 0., 0., 0., 0., 0.};
    }

    constexpr Bivector4D   operator "" _xy4(long double v)
    {
        return {(double) v, 0., 0., 0., 0., 0.};
    }


    constexpr Bivector4D   operator "" _yz4(unsigned long long int v)
    {
        return {0., (double) v,  0., 0., 0., 0.};
    }

    constexpr Bivector4D   operator "" _yz4(long double v)
    {
        return {0., (double) v, 0., 0., 0., 0.};
    }

    constexpr Bivector4D   operator "" _zw4(unsigned long long int v)
    {
        return {0., 0., (double) v,  0., 0., 0.};
    }

    constexpr Bivector4D   operator "" _xw4(long double v)
    {
        return {0., 0., (double) v, 0., 0., 0.};
    }

    constexpr Bivector4D   operator "" _wx4(unsigned long long int v)
    {
        return {0., 0., 0., (double) v,  0., 0. };
    }

    constexpr Bivector4D   operator "" _wx4(long double v)
    {
        return {0., 0., 0., (double) v, 0., 0.};
    }

    constexpr Bivector4D   operator "" _xz4(unsigned long long int v)
    {
        return {0., 0., 0., 0., (double) v,  0. };
    }

    constexpr Bivector4D   operator "" _xz4(long double v)
    {
        return {0., 0., 0., 0., (double) v,  0.};
    }

    constexpr Bivector4D   operator "" _yw4(unsigned long long int v)
    {
        return {0., 0., 0., 0., 0., (double) v};
    }

    constexpr Bivector4D   operator "" _yw4(long double v)
    {
        return {0., 0., 0., 0., 0., (double) v};
    }
    
    YQ_NAN_1(Bivector4, Bivector4<T>{
        nan_v<square_t<T>>, nan_v<square_t<T>>, nan_v<square_t<T>>, 
        nan_v<square_t<T>>, nan_v<square_t<T>>, nan_v<square_t<T>>
    })
    YQ_ZERO_1(Bivector4, Bivector4<T>{
        zero_v<square_t<T>>, zero_v<square_t<T>>, zero_v<square_t<T>>,
        zero_v<square_t<T>>, zero_v<square_t<T>>, zero_v<square_t<T>>
    })
    
    YQ_IS_NAN_1(Bivector4, 
        is_nan(v.xy) || is_nan(v.yz) || is_nan(v.zw) || 
        is_nan(v.wx) || is_nan(v.xz) || is_nan(v.yw)
    )
    YQ_IS_FINITE_1(Bivector4, 
        is_finite(v.xy) && is_finite(v.yz) && is_finite(v.zw) && 
        is_finite(v.wx) && is_finite(v.xz) && is_finite(v.yw)
    )
}

YQ_TYPE_DECLARE(yq::Bivector4D)
YQ_TYPE_DECLARE(yq::Bivector4F)

