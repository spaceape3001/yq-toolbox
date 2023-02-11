////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>
#include <math/Vector2.hpp>

namespace yq {

    template <typename T>
    struct Segment2 {
        //! Capture the template parameter
        using component_type    = T;
    
        Vector2<T>  a, b;
        
        constexpr Segment2() noexcept = default;
        constexpr Segment2(const Vector2<T>& _a, const Vector2<T>& _b) : a(_a), b(_b) {}
        template <typename=void> requires has_nan_v<T>
        constexpr Segment2(nan_t) : Segment2( Vector2<T>(NAN), Vector2<T>(NAN)) {}
        constexpr Segment2(zero_t) : Segment2( Vector2<T>(ZERO), Vector2<T>(ZERO)) {}

        template <typename U>
        requires std::is_nothrow_convertible_v<T,U>
        explicit constexpr operator Segment2<U>() const noexcept
        {
            return { (Vector2<U>) a, (Vector2<U>) b };
        }
        
        template <typename U>
        requires (std::is_convertible_v<T,U> && !std::is_nothrow_convertible_v<T,U>)
        explicit constexpr operator Segment2<U>() const 
        {
            return { (Vector2<U>) a, (Vector2<U>) b };
        }

        //! Defaulted equality
        constexpr bool operator==(const Segment2&) const noexcept = default;

        constexpr operator SegmentData<Vector2<T>>() const noexcept;

        constexpr Segment2      operator+() const noexcept;
        constexpr Segment2      operator-() const noexcept;
        
        
        Segment2                operator+(const Vector2<T>&) const noexcept;
        Segment2                operator-(const Vector2<T>&) const noexcept;
        
        Segment2&               operator+=(const Vector2<T>&) noexcept;
        Segment2&               operator-=(const Vector2<T>&) noexcept;
        
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Segment2<product_t<T,U>>    operator*(U) const noexcept;
        
        template <typename U>
        requires (is_arithmetic_v<U> && self_mul_v<T,U>)
        Segment2<T>&                operator*=(U)  noexcept;
        

        template <typename U>
        Segment1<product_t<T,U>>    operator*(const Tensor21<U>&) const noexcept;

        template <typename U>
        Segment2<product_t<T,U>>    operator*(const Tensor22<U>&) const noexcept;

        template <typename U>
        Segment3<product_t<T,U>>    operator*(const Tensor23<U>&) const noexcept;

        template <typename U>
        Segment4<product_t<T,U>>    operator*(const Tensor24<U>&) const noexcept;
        
        template <typename U>
        requires self_mul_v<T,U>
        Segment2&                   operator*=(const Tensor22<U>&) noexcept;
        
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Segment2<quotient_t<T,U>>   operator/(U) const noexcept;
        
        template <typename U>
        requires (is_arithmetic_v<U> && self_div_v<T,U>)
        Segment2<T>&                operator/=(U)  noexcept;

        constexpr AxBox2<T>     bounds() const noexcept;

        //! Net displacement
        constexpr Vector2<T>  delta() const noexcept;
        
        //! Length of the segment
        T   length() const;

        //! Square of the length
        constexpr square_t<T> length²() const noexcept;
        
        //! Segment mid-point
        constexpr Vector2<T>  midpoint() const noexcept;

        /*! \brief Computes a point along the segment based on a fractional position
        
            \param[in]  f   Fractional point
        */
        template <typename=void>
        requires has_ieee754_v<T>
        constexpr Vector2<T>     point(ieee754_t<T> f) const noexcept;
    };

    YQ_INTEGER_1(Segment2)
    YQ_IS_INTEGER_1(Segment2)
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

    YQ_NAN_1(Segment2, Segment2<T>(NAN))
    YQ_ZERO_1(Segment2, Segment2<T>(ZERO))

//  --------------------------------------------------------
//  --------------------------------------------------------

    YQ_IS_FINITE_1( Segment2, is_finite(v.a) && is_finite(v.b))
    YQ_IS_NAN_1(Segment2, is_nan(v.a) || is_nan(v.b))

    template <typename T, typename U>
    requires is_arithmetic_v<T,U>
    constexpr Segment2<product_t<T,U>> operator*(T, const Segment2<T>&) noexcept;

    /*! \brief Creates axially aligned bounding box from the segment
    */
    template <typename T>
    constexpr AxBox2<T>   aabb(const Segment2<T>& seg) noexcept;
    
    /*! \brief Computes the length of the segmetn
    */
    template <typename T>
    T       length(const Segment2<T>& seg);

    /*! \brief Computes the midpoint of the segmetn
    */
    template <typename T>
    constexpr Vector2<T>     midpoint(const Segment2<T>& seg) noexcept;

    /*! \brief Computes a point along the segment based on a fractional position
    
        \param[in]  seg Segment
        \param[in]  f   Fractional point
    */
    template <typename T>
    requires has_ieee754_v<T>
    constexpr Vector2<T>     point(const Segment2<T>& seg, ieee754_t<T> f) noexcept;
}

YQ_TYPE_DECLARE(yq::Segment2D)
YQ_TYPE_DECLARE(yq::Segment2F)
YQ_TYPE_DECLARE(yq::Segment2I)
YQ_TYPE_DECLARE(yq::Segment2U)

