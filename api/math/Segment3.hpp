////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <math/preamble.hpp>
#include <math/Vector3.hpp>
#include "SegmentData.hpp"

namespace yq {
    YQ_IEEE754_1(Segment3)

//  --------------------------------------------------------
//  COMPOSITION


    YQ_NAN_1(Segment3, { nan_v<Vector3<T>>, nan_v<Vector3<T>>});
    YQ_ZERO_1(Segment3, { zero_v<Vector3<T>>, zero_v<Vector3<T>>});

    template <typename T>
    constexpr Segment3<T> segment(const Vector3<T>& a, const Vector3<T>& b) noexcept
    {
        return { a, b };
    }

//  --------------------------------------------------------
//  GETTERS

//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_NAN_1(Segment3, is_nan(v.a) || is_nan(v.b))

    template <typename T>
    constexpr AxBox3<T>   aabb(const Segment3<T>& v) noexcept
    {
        return aabb(v.a, v.b);
    }

    template <typename T>
    constexpr bool is_finite(const Segment3<T>& v)
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
    T       length(const Segment3<T>& seg)
    {
        return length(seg.b-seg.a);
    }

    template <typename T>
    requires has_ieee754_v<T>
    constexpr Vector3<T>     midpoint(const Segment3<T>& seg) noexcept
    {
        return ieee754_t<T>(0.5)*(seg.hi+seg.lo);
    }

    template <typename T>
    requires has_ieee754_v<T>
    constexpr Vector3<T>     point(const Segment3<T>& seg, ieee754_t<T> f) noexcept
    {
        return (one_v<ieee754_t<T>> - f) * seg.a + f * seg.b;
    }
}

YQ_TYPE_DECLARE(yq::Segment3D)
YQ_TYPE_DECLARE(yq::Segment3F)
YQ_TYPE_DECLARE(yq::Segment3I)
YQ_TYPE_DECLARE(yq::Segment3U)

