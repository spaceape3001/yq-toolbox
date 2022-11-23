#pragma once

#include <complex>
#include <math/preamble.hpp>

namespace yq {
    using namespace std::complex_literals;
    
    //YQ_ABS_1(std::complex, std::abs(v) )
    YQ_IDENTITY_1(std::complex, { one_v<T>, zero_v<T> })
    
    template <typename T>
    constexpr bool    is_finite(const std::complex<T>& v)
    {
        return is_finite(v.real()) && is_finite(v.imag());
    }
    
    YQ_IS_NAN_1(std::complex, is_nan(v.real()) || is_nan(v.imag()))
    YQ_NAN_1(std::complex, { nan_v<T>, nan_v<T> })
    //YQ_SQRT_1(std::complex, std::sqrt(v))
    YQ_ZERO_1(std::complex, { zero_v<T>, zero_v<T> })
    
}

YQ_TYPE_DECLARE(yq::ComplexD)
YQ_TYPE_DECLARE(yq::ComplexF)
YQ_TYPE_DECLARE(yq::ComplexI)
YQ_TYPE_DECLARE(yq::ComplexU)

