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

    template <typename T>
    struct Segment3 {
        //! Capture the template parameter
        using component_type    = T;
    
        Vector3<T>  a, b;
        
        //! Defaulted equality
        constexpr bool operator==(const Segment3&) const noexcept = default;

        constexpr operator SegmentData<Vector3<T>>() const noexcept
        {
            return { a, b };
        }

        //! Net displacement
        constexpr Vector1<T>  delta() const noexcept
        {
            return b - a;
        }
        
        //! Length of the segment
        T   length() const 
        { 
            return delta().length(); 
        }

        //! Square of the length
        constexpr square_t<T> length²() const noexcept
        {
            return delta().length²();
        }
        
        //! Segment mid-point
        Vector3<T>  midpoint() const
        {
            if constexpr (has_ieee754_v<T>)
                return ieee754_t<T>(0.5)*(a+b);
            else if constexpr (std::is_integral_v<T>)
                return (a+b) / T(2);
            else
                return {};
        }

        /*! \brief Computes a point along the segment based on a fractional position
        
            \param[in]  f   Fractional point
        */
        template <typename=void>
        requires has_ieee754_v<T>
        constexpr Vector3<T>     point(ieee754_t<T> f) const noexcept
        {
            return (one_v<ieee754_t<T>> - f) * a + f * b;
        }

    };

    YQ_IEEE754_1(Segment3)

//  --------------------------------------------------------
//  COMPOSITION


    YQ_NAN_1(Segment3, { nan_v<Vector3<T>>, nan_v<Vector3<T>>});
    YQ_ZERO_1(Segment3, { zero_v<Vector3<T>>, zero_v<Vector3<T>>});

    /*! \brief Creates segment from two points
    */
    template <typename T>
    constexpr Segment3<T> segment(const Vector3<T>& a, const Vector3<T>& b) noexcept
    {
        return { a, b };
    }

//  --------------------------------------------------------
//  GETTERS

//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_FINITE_1( Segment3, is_finite(v.a) && is_finite(v.b))
    YQ_IS_NAN_1(Segment3, is_nan(v.a) || is_nan(v.b))

    /*! \brief Creates axially aligned bounding box from the segment
    */
    template <typename T>
    constexpr AxBox3<T>   aabb(const Segment3<T>& a) noexcept
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

    /*! \brief Computes the length of the segmetn
    */
    template <typename T>
    T       length(const Segment3<T>& seg)
    {
        return seg.length();
    }

    /*! \brief Computes the midpoint of the segmetn
    */
    template <typename T>
    constexpr Vector3<T>     midpoint(const Segment3<T>& seg) noexcept
    {
        return seg.midpoint();
    }

    /*! \brief Computes a point along the segment based on a fractional position
    
        \param[in]  seg Segment
        \param[in]  f   Fractional point
    */
    template <typename T>
    requires has_ieee754_v<T>
    constexpr Vector3<T>     point(const Segment3<T>& seg, ieee754_t<T> f) noexcept
    {
        return seg.point(f);
    }
}

YQ_TYPE_DECLARE(yq::Segment3D)
YQ_TYPE_DECLARE(yq::Segment3F)
YQ_TYPE_DECLARE(yq::Segment3I)
YQ_TYPE_DECLARE(yq::Segment3U)

