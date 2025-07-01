////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/typedef/complex.hpp>

#include <yq/meta/MetaBinder.hpp>
#include <yq/trait/has_abs.hpp>
#include <yq/trait/has_identity.hpp>
#include <yq/trait/has_is_finite.hpp>
#include <yq/trait/has_nan.hpp>
#include <yq/trait/has_one.hpp>
#include <yq/trait/has_sqrt.hpp>
#include <yq/trait/has_zero.hpp>

#include <complex>

namespace yq {
    using namespace std::complex_literals;
    
    YQ_ABS_1(std::complex, std::abs(v) )
    YQ_IDENTITY_1(std::complex, { one_v<T>, zero_v<T> })
    YQ_IS_FINITE_1(std::complex, is_finite(v.real()) && is_finite(v.imag()))
    YQ_IS_NAN_1(std::complex, is_nan(v.real()) || is_nan(v.imag()))
    YQ_NAN_1(std::complex, { nan_v<T>, nan_v<T> })
    YQ_SQRT_1(std::complex, std::sqrt(v))
    YQ_ZERO_1(std::complex, { zero_v<T>, zero_v<T> })
    
}

YQ_TYPE_DECLARE(yq::ComplexD)
YQ_TYPE_DECLARE(yq::ComplexF)
YQ_TYPE_DECLARE(yq::ComplexI)
YQ_TYPE_DECLARE(yq::ComplexU)

