////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <math/preamble.hpp>
#include <math/AxBox1.hpp>
#include <math/Vector1.hpp>
#include <math/SegmentData.hpp>

namespace yq {
    /*! \brief Data for a segment
    
        \note Can be the vertex themselves, or other data.
    */
    template <typename T>
    struct Segment1 {
    
        //! Capture the template parameter
        using component_type    = T;
        
        Vector1<T>   a, b;
        
        //! Defaulted equality operator
        constexpr bool operator==(const Segment1&) const noexcept = default;
        
        constexpr operator SegmentData<Vector1<T>>() const noexcept
        {
            return { a, b };
        }
        
        constexpr AxBox1<T>     bounds() const noexcept
        {
            return aabb(a, b);
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
        Vector1<T>  midpoint() const
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
        constexpr Vector1<T>     point(ieee754_t<T> f) const noexcept
        {
            return (one_v<ieee754_t<T>> - f) * a + f * b;
        }
    };

    YQ_IEEE754_1(Segment1)

//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Creates a segment from two points
    */
    template <typename T>
    constexpr Segment1<T> segment(const Vector1<T>& a, const Vector1<T>& b) noexcept
    {
        return { a, b };
    }

    YQ_NAN_1(Segment1, { nan_v<Vector1<T>>, nan_v<Vector1<T>>});
    YQ_ZERO_1(Segment1, { zero_v<Vector1<T>>, zero_v<Vector1<T>>});

//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_FINITE_1( Segment1, is_finite(v.a) && is_finite(v.b))
    YQ_IS_NAN_1(Segment1, is_nan(v.a) || is_nan(v.b))

    /*! \brief Creates an axially aligned bounding box from a segment
    */
    template <typename T>
    constexpr AxBox1<T>   aabb(const Segment1<T>& seg) noexcept
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

    /*! \brief Computes the length of the segment
    */
    template <typename T>
    T       length(const Segment1<T>& seg)
    {
        return seg.length();
    }
    
    /*! \brief Computes the midpoint of the segmetn
    */
    template <typename T>
    constexpr Vector1<T>     midpoint(const Segment1<T>& seg) noexcept
    {
        return seg.midpoint();
    }

    /*! \brief Computes a point along the segment based on a fractional position
    
        \param[in]  seg Segment
        \param[in]  f   Fractional point
    */
    template <typename T>
    requires has_ieee754_v<T>
    constexpr Vector1<T>     point(const Segment1<T>& seg, ieee754_t<T> f) noexcept
    {
        return seg.point(f);
    }

}
YQ_TYPE_DECLARE(yq::Segment1D)
YQ_TYPE_DECLARE(yq::Segment1F)
YQ_TYPE_DECLARE(yq::Segment1I)
YQ_TYPE_DECLARE(yq::Segment1U)

