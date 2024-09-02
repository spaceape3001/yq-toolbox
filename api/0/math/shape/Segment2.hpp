////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_SEGMENT2_HPP 1

#include <0/math/preamble.hpp>
#include <0/math/vector/Vector2.hpp>

#include <yq/keywords.hpp>
#include <yq/trait/product.hpp>
#include <yq/trait/quotient.hpp>
#include <yq/trait/self_divide.hpp>
#include <yq/trait/self_multiply.hpp>
#include <yq/trait/unity.hpp>

namespace yq {

    /*! \brief Segment in 2D
    */
    template <typename T>
    struct Segment2 {
        //! Capture the template parameter
        using component_type    = T;
    
        //! First point
        Vector2<T>  a;

        //! Second point
        Vector2<T>  b;
        
        //! Default constructor
        constexpr Segment2() noexcept = default;

        //! Component wise constructor (vector and vector)
        constexpr Segment2(const Vector2<T>& _a, const Vector2<T>& _b) : a(_a), b(_b) {}

        //! NaN constructor
        template <typename=void> requires has_nan_v<T>
        constexpr Segment2(nan_t) : Segment2( Vector2<T>(NAN), Vector2<T>(NAN)) {}

        //! Zero constructor
        constexpr Segment2(zero_t) : Segment2( Vector2<T>(ZERO), Vector2<T>(ZERO)) {}

        //! Converter to another segment2 of compatible data types
        template <typename U>
        requires std::is_nothrow_convertible_v<T,U>
        explicit constexpr operator Segment2<U>() const noexcept
        {
            return { (Vector2<U>) a, (Vector2<U>) b };
        }
        
        //! Converter to another segment2 of compatible data types
        template <typename U>
        requires (std::is_convertible_v<T,U> && !std::is_nothrow_convertible_v<T,U>)
        explicit constexpr operator Segment2<U>() const 
        {
            return { (Vector2<U>) a, (Vector2<U>) b };
        }

        //! Defaulted equality
        constexpr bool operator==(const Segment2&) const noexcept = default;

        //! Converts to segment data
        constexpr operator SegmentData<Vector2<T>>() const noexcept;

        //! Affirmation (positive) operator
        constexpr Segment2      operator+() const noexcept;

        //! Negation operator
        constexpr Segment2      operator-() const noexcept;
        
        //! Returns the segment displaced by the given amount
        Segment2                operator+(const Vector2<T>&) const noexcept;

        //! Returns the segment anti-displaced by the given amount
        Segment2                operator-(const Vector2<T>&) const noexcept;
        
        //! Moves the segment by the given amount (ie, added to both a and b)
        Segment2&               operator+=(const Vector2<T>&) noexcept;

        //! Moves the segment opposite to the given amount
        Segment2&               operator-=(const Vector2<T>&) noexcept;
        
        //! Scale the segment on both values
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Segment2<product_t<T,U>>    operator*(U) const noexcept;
        
        //! Self-scaling for the segment
        template <typename U>
        requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
        Segment2<T>&                operator*=(U)  noexcept;
        

        //! Projects segment into one dimension
        template <typename U>
        Segment1<product_t<T,U>>    operator*(const Tensor21<U>&) const noexcept;

        //! Projects segment into two dimensions
        template <typename U>
        Segment2<product_t<T,U>>    operator*(const Tensor22<U>&) const noexcept;

        //! Projects segment into three dimensions
        template <typename U>
        Segment3<product_t<T,U>>    operator*(const Tensor23<U>&) const noexcept;

        //! Projects segment in four dimensions
        template <typename U>
        Segment4<product_t<T,U>>    operator*(const Tensor24<U>&) const noexcept;
        
        //! Self-projection of segment with tensor
        template <typename U>
        requires self_multiply_v<T,U>
        Segment2&                   operator*=(const Tensor22<U>&) noexcept;
        
        //! Returns a scaled down the segment by the specified amount
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Segment2<quotient_t<T,U>>   operator/(U) const noexcept;
        
        //! Self-scaling down this segment by the specified amount
        template <typename U>
        requires (is_arithmetic_v<U> && self_divide_v<T,U>)
        Segment2<T>&                operator/=(U)  noexcept;

        //! Bounding box to this segment
        constexpr AxBox2<T>     bounds() const noexcept;

        //! Net displacement
        constexpr Vector2<T>  delta() const noexcept;
        
        //! Computes the fraction along the segment for given X value
        Expect<unity_t<T>>   fraction_x(T, T ep=zero_v<T>) const noexcept;

        //! Computes the fraction along the segment for given Y value
        Expect<unity_t<T>>   fraction_y(T, T ep=zero_v<T>) const noexcept;

        //! Computes the intercept point for specified X
        //! \param[in]  ep  Delta to consider this segment to have no x-variation (and thus, unsolveable)
        //! \return Returns Point of intercept on the segment
        Expect<Vector2<T>> intercept_x(T, T ep=zero_v<T>) const noexcept;
        
        //! Computes the intercept point for specified Y
        //! \param[in]  ep  Delta to consider this segment to have no y-variation (and thus, unsolveable)
        //! \return Returns Point of intercept on the segment
        Expect<Vector2<T>> intercept_y(T, T ep=zero_v<T>) const noexcept;

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

    /*! \brief Returns a segment scaled by given factor
    */
    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Segment2<product_t<T,U>> operator*(T, const Segment2<U>&) noexcept;

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

