////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <math/preamble.hpp>
#include <math/AxBox1.hpp>
#include <math/Vector1.hpp>
#include "SegmentData.hpp"

namespace yq {
    YQ_IEEE754_1(Segment1)


//  --------------------------------------------------------
//  COMPOSITION

    template <typename T>
    constexpr Segment1<T> segment(const Vector1<T>& a, const Vector1<T>& b) noexcept
    {
        return { a, b };
    }

    YQ_NAN_1(Segment1, { nan_v<Vector1<T>>, nan_v<Vector1<T>>});
    YQ_ZERO_1(Segment1, { zero_v<Vector1<T>>, zero_v<Vector1<T>>});

//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_NAN_1(Segment1, is_nan(v.a) || is_nan(v.b))

    template <typename T>
    constexpr AxBox1<T>   aabb(const Segment1<T>& v) noexcept
    {
        return aabb(v.a, v.b);
    }

    template <typename T>
    constexpr bool is_finite(const Segment1<T>& v)
    {
        return is_finite(v.a) && is_finite(v.b);
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
    T       length(const Segment1<T>& seg)
    {
        return length(seg.b-seg.a);
    }
    
    template <typename T>
    requires has_ieee754_v<T>
    constexpr Vector1<T>     midpoint(const Segment1<T>& seg) noexcept
    {
        return ieee754_t<T>(0.5)*(seg.hi+seg.lo);
    }

    template <typename T>
    requires has_ieee754_v<T>
    constexpr Vector1<T>     point(const Segment1<T>& seg, ieee754_t<T> f) noexcept
    {
        return (one_v<ieee754_t<T>> - f) * seg.a + f * seg.b;
    }

}
YQ_TYPE_DECLARE(yq::Segment1D)
YQ_TYPE_DECLARE(yq::Segment1F)
YQ_TYPE_DECLARE(yq::Segment1I)
YQ_TYPE_DECLARE(yq::Segment1U)

