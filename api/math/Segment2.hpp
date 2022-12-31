////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>
#include <math/Vector2.hpp>
#include <math/SegmentData.hpp>

namespace yq {

    template <typename T>
    struct Segment2 {
        //! Capture the template parameter
        using component_type    = T;
    
        Vector2<T>  a, b;
        
        //! Defaulted equality
        constexpr bool operator==(const Segment2&) const noexcept = default;

        constexpr operator SegmentData<Vector2<T>>() const noexcept
        {
            return { a, b };
        }

        constexpr AxBox2<T>     bounds() const noexcept
        {
            return aabb(a, b);
        }

        //! Net displacement
        constexpr Vector2<T>  delta() const noexcept
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
        Vector2<T>  midpoint() const
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
        constexpr Vector2<T>     point(ieee754_t<T> f) const noexcept
        {
            return (one_v<ieee754_t<T>> - f) * a + f * b;
        }

    };

    YQ_IEEE754_1(Segment2)

//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Creates segment from two points
    */
    template <typename T>
    constexpr Segment2<T> segment(const Vector2<T>& a, const Vector2<T>& b) noexcept
    {
        return { a, b };
    }

    YQ_NAN_1(Segment2, { nan_v<Vector2<T>>, nan_v<Vector2<T>>});
    YQ_ZERO_1(Segment2, { zero_v<Vector2<T>>, zero_v<Vector2<T>>});

//  --------------------------------------------------------
//  GETTERS

//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_FINITE_1( Segment2, is_finite(v.a) && is_finite(v.b))
    YQ_IS_NAN_1(Segment2, is_nan(v.a) || is_nan(v.b))

    /*! \brief Creates axially aligned bounding box from the segment
    */
    template <typename T>
    constexpr AxBox2<T>   aabb(const Segment2<T>& seg) noexcept
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
    T       length(const Segment2<T>& seg)
    {
        return seg.length();
    }

    /*! \brief Computes the midpoint of the segmetn
    */
    template <typename T>
    constexpr Vector2<T>     midpoint(const Segment2<T>& seg) noexcept
    {
        return seg.midpoint();
    }

    /*! \brief Computes a point along the segment based on a fractional position
    
        \param[in]  seg Segment
        \param[in]  f   Fractional point
    */
    template <typename T>
    requires has_ieee754_v<T>
    constexpr Vector2<T>     point(const Segment2<T>& seg, ieee754_t<T> f) noexcept
    {
        return seg.point(f);
    }
}

YQ_TYPE_DECLARE(yq::Segment2D)
YQ_TYPE_DECLARE(yq::Segment2F)
YQ_TYPE_DECLARE(yq::Segment2I)
YQ_TYPE_DECLARE(yq::Segment2U)

