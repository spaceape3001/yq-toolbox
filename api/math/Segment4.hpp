////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <math/preamble.hpp>
#include <math/Vector4.hpp>
#include "SegmentData.hpp"

namespace yq {

    YQ_IEEE754_1(Segment4)

//  --------------------------------------------------------
//  COMPOSITION

    template <typename T>
    constexpr Segment4<T> segment(const Vector4<T>& a, const Vector4<T>& b) noexcept
    {
        return { a, b };
    }

    YQ_NAN_1(Segment4, { nan_v<Vector4<T>>, nan_v<Vector4<T>>});
    YQ_ZERO_1(Segment4, { zero_v<Vector4<T>>, zero_v<Vector4<T>>});

//  --------------------------------------------------------
//  GETTERS

//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_FINITE_1( Segment4, is_finite(v.a) && is_finite(v.b))
    YQ_IS_NAN_1(Segment4, is_nan(v.a) || is_nan(v.b))
    
    template <typename T>
    constexpr AxBox4<T>   aabb(const Segment4<T>& a) noexcept
    {
        return aabb(a.lo, a.hi);
    }

//  --------------------------------------------------------
//  POSITIVE


//  --------------------------------------------------------
//  NEGATIVE


//  --------------------------------------------------------
//  NORMALIZATION


//  --------------------------------------------------------
//  ADDITION


//  --------------------------------------------------------
//  SUBTRACTION


//  --------------------------------------------------------
//  MULTIPLICATION


//  --------------------------------------------------------
//  DIVISION

//  --------------------------------------------------------
//  POWERS

//  --------------------------------------------------------
//  DOT PRODUCT


//  --------------------------------------------------------
//  INNER PRODUCT


//  --------------------------------------------------------
//  OUTER PRODUCT


//  --------------------------------------------------------
//  CROSS PRODUCT


///  --------------------------------------------------------
//  OTIMES PRODUCT

//  --------------------------------------------------------
//  UNIONS

//  --------------------------------------------------------
//  INTERSECTIONS


//  --------------------------------------------------------
//  PROJECTIONS

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

    template <typename T>
    T       length(const Segment4<T>& seg)
    {
        return length(seg.b-seg.a);
    }

    template <typename T>
    requires has_ieee754_v<T>
    constexpr Vector4<T>     midpoint(const Segment4<T>& seg) noexcept
    {
        return ieee754_t<T>(0.5)*(seg.hi+seg.lo);
    }
    
    template <typename T>
    requires has_ieee754_v<T>
    constexpr Vector4<T>     point(const Segment4<T>& seg, ieee754_t<T> f) noexcept
    {
        return (one_v<ieee754_t<T>> - f) * seg.a + f * seg.b;
    }
}

YQ_TYPE_DECLARE(yq::Segment4D)
YQ_TYPE_DECLARE(yq::Segment4F)
YQ_TYPE_DECLARE(yq::Segment4I)
YQ_TYPE_DECLARE(yq::Segment4U)

