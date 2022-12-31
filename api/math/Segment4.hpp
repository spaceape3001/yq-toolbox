////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <math/preamble.hpp>
#include <math/Vector4.hpp>
#include <math/SegmentData.hpp>

namespace yq {

    template <typename T>
    struct Segment4 {
        //! Capture the template parameter
        using component_type    = T;
    
        Vector4<T>  a, b;
        
        //! Defaulted equality
        constexpr bool operator==(const Segment4&) const noexcept = default;

        constexpr operator SegmentData<Vector4<T>>() const noexcept
        {
            return { a, b };
        }

        constexpr AxBox4<T>     bounds() const noexcept
        {
            return aabb(a, b);
        }

        //! Net displacement
        constexpr Vector4<T>  delta() const noexcept
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
        Vector4<T>  midpoint() const
        {
            return midvector(a, b);
        }

        /*! \brief Computes a point along the segment based on a fractional position
        
            \param[in]  f   Fractional point
        */
        template <typename=void>
        requires has_ieee754_v<T>
        constexpr Vector4<T>     point(ieee754_t<T> f) const noexcept
        {
            return (one_v<ieee754_t<T>> - f) * a + f * b;
        }

    };
        YQ_IEEE754_1(Segment4)

//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Creates segment from two points
    */
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
    
    /*! \brief Creates axially aligned bounding box from the segment
    */
    template <typename T>
    constexpr AxBox4<T>   aabb(const Segment4<T>& seg) noexcept
    {
        return aabb(seg.a, seg.b);
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
    T       length(const Segment4<T>& seg)
    {
        return seg.length();
    }

    /*! \brief Computes the midpoint of the segmetn
    */
    template <typename T>
    constexpr Vector4<T>     midpoint(const Segment4<T>& seg) noexcept
    {
        return seg.midpoint();
    }
    
    /*! \brief Computes a point along the segment based on a fractional position
    
        \param[in]  seg Segment
        \param[in]  f   Fractional point
    */
    template <typename T>
    requires has_ieee754_v<T>
    constexpr Vector4<T>     point(const Segment4<T>& seg, ieee754_t<T> f) noexcept
    {
        return seg.point(f);
    }
}

YQ_TYPE_DECLARE(yq::Segment4D)
YQ_TYPE_DECLARE(yq::Segment4F)
YQ_TYPE_DECLARE(yq::Segment4I)
YQ_TYPE_DECLARE(yq::Segment4U)

