////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_SEGMENT4_HPP 1

#include <yq/typedef/segment4.hpp>

#include <yq/keywords.hpp>
#include <yq/core/Expect.hpp>
#include <yq/trait/is_floating_point.hpp>
#include <yq/trait/product.hpp>
#include <yq/trait/quotient.hpp>
#include <yq/trait/self_divide.hpp>
#include <yq/trait/self_multiply.hpp>
#include <yq/trait/unity.hpp>
#include <yq/vector/Vector4.hpp>

namespace log4cpp { class CategoryStream; }

namespace yq {
    template <typename> struct Segment1;
    template <typename> struct Segment2;
    template <typename> struct Segment3;
    template <typename> struct SegmentData;
    template <typename> struct Tensor41;
    template <typename> struct Tensor42;
    template <typename> struct Tensor43;
    template <typename> struct Tensor44;

    /*! \brief Segment in 4D
    */
    template <typename T>
    struct Segment4 {
        //! Capture the template parameter
        using component_type    = T;
    
        
        //! First point
        Vector4<T>  a;
        
        //! Second point
        Vector4<T>  b;
        
        //! Default constructor
        constexpr Segment4() noexcept = default;
        
        //! Component wise constructor (vector and vector)
        constexpr Segment4(const Vector4<T>& _a, const Vector4<T>& _b) : a(_a), b(_b) {}
        
        //! NaN constructor
        template <typename=void> requires has_nan_v<T>
        constexpr Segment4(nan_t) : Segment4( Vector4<T>(NAN), Vector4<T>(NAN)) {}
        
        //! Zero constructor
        constexpr Segment4(zero_k) : Segment4( Vector4<T>(ZERO), Vector4<T>(ZERO)) {}

        //! Converter to another segment4 of compatible data types
        template <typename U>
        requires std::is_nothrow_convertible_v<T,U>
        explicit constexpr operator Segment4<U>() const noexcept
        {
            return { (Vector4<U>) a, (Vector4<U>) b };
        }
        
        //! Converter to another segment4 of compatible data types
        template <typename U>
        requires (std::is_convertible_v<T,U> && !std::is_nothrow_convertible_v<T,U>)
        explicit constexpr operator Segment4<U>() const 
        {
            return { (Vector4<U>) a, (Vector4<U>) b };
        }

        //! Defaulted equality
        constexpr bool operator==(const Segment4&) const noexcept = default;

        //! Converts to segment data
        constexpr operator SegmentData<Vector4<T>>() const noexcept;

        //! Affirmation (positive) operator
        constexpr Segment4      operator+() const noexcept;
        
        //! Negation operator
        constexpr Segment4      operator-() const noexcept;
        
        //! Returns the segment displaced by the given amount
        Segment4                operator+(const Vector4<T>&) const noexcept;

        //! Returns the segment anti-displaced by the given amount
        Segment4                operator-(const Vector4<T>&) const noexcept;
        
        //! Moves the segment by the given amount (ie, added to both a and b)
        Segment4&               operator+=(const Vector4<T>&) noexcept;
        
        //! Moves the segment opposite to the given amount
        Segment4&               operator-=(const Vector4<T>&) noexcept;
        
        //! Scale the segment on both values
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Segment4<product_t<T,U>>    operator*(U) const noexcept;
        
        //! Self-scaling for the segment
        template <typename U>
        requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
        Segment4<T>&                operator*=(U)  noexcept;
        
        //! Projects segment into one dimension
        template <typename U>
        Segment1<product_t<T,U>>    operator*(const Tensor41<U>&) const noexcept;

        //! Projects segment into two dimensions
        template <typename U>
        Segment2<product_t<T,U>>    operator*(const Tensor42<U>&) const noexcept;

        //! Projects segment into three dimensions
        template <typename U>
        Segment3<product_t<T,U>>    operator*(const Tensor43<U>&) const noexcept;

        //! Projects segment in four dimensions
        template <typename U>
        Segment4<product_t<T,U>>    operator*(const Tensor44<U>&) const noexcept;
        
        //! Self-projection of segment with tensor
        template <typename U>
        requires self_multiply_v<T,U>
        Segment4&                   operator*=(const Tensor44<U>&) noexcept;

        //! Returns a scaled down the segment by the specified amount
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Segment4<quotient_t<T,U>>   operator/(U) const noexcept;
        
        //! Self-scaling down this segment by the specified amount
        template <typename U>
        requires (is_arithmetic_v<U> && self_divide_v<T,U>)
        Segment4<T>&                operator/=(U)  noexcept;

        //! Bounding box to this segment
        constexpr AxBox4<T>     bounds() const noexcept;
        
        //! Net displacement
        constexpr Vector4<T>  delta() const noexcept;
        
        //! Computes the fraction along the segment for given X value
        template <typename=void>
        requires is_floating_point_v<T>
        Expect<unity_t<T>>  fraction_x(T, T ep=zero_v<T>) const noexcept;

        //! Computes the fraction along the segment for given Y value
        template <typename=void>
        requires is_floating_point_v<T>
        Expect<unity_t<T>>  fraction_y(T, T ep=zero_v<T>) const noexcept;

        //! Computes the fraction along the segment for given Z value
        template <typename=void>
        requires is_floating_point_v<T>
        Expect<unity_t<T>>  fraction_z(T, T ep=zero_v<T>) const noexcept;

        //! Computes the fraction along the segment for given W value
        template <typename=void>
        requires is_floating_point_v<T>
        Expect<unity_t<T>>  fraction_w(T, T ep=zero_v<T>) const noexcept;
        
        
        //! Computes the intercept point for specified X
        //! \param[in]  ep  Delta to consider this segment to have no x-variation (and thus, unsolveable)
        //! \return Returns Point of intercept on the segment
        template <typename=void>
        requires is_floating_point_v<T>
        Expect<Vector4<T>>  intercept_x(T, T ep=zero_v<T>) const noexcept;
        
        //! Computes the intercept point for specified Y
        //! \param[in]  ep  Delta to consider this segment to have no y-variation (and thus, unsolveable)
        //! \return Returns Point of intercept on the segment
        template <typename=void>
        requires is_floating_point_v<T>
        Expect<Vector4<T>>  intercept_y(T, T ep=zero_v<T>) const noexcept;

        //! Computes the intercept point for specified Z
        //! \param[in]  ep  Delta to consider this segment to have no z-variation (and thus, unsolveable)
        //! \return Returns Point of intercept on the segment
        template <typename=void>
        requires is_floating_point_v<T>
        Expect<Vector4<T>>  intercept_z(T, T ep=zero_v<T>) const noexcept;

        //! Computes the intercept point for specified W
        //! \param[in]  ep  Delta to consider this segment to have no w-variation (and thus, unsolveable)
        //! \return Returns Point of intercept on the segment
        template <typename=void>
        requires is_floating_point_v<T>
        Expect<Vector4<T>>  intercept_w(T, T ep=zero_v<T>) const noexcept;
        
        //! Length of the segment
        T   length() const;

        //! Square of the length
        constexpr square_t<T> length²() const noexcept;
        
        //! Segment mid-point
        Vector4<T>  midpoint() const;

        /*! \brief Computes a point along the segment based on a fractional position
        
            \param[in]  f   Fractional point
        */
        template <typename=void>
        requires has_ieee754_v<T>
        constexpr Vector4<T>     point(ieee754_t<T> f) const noexcept;

    };

    YQ_IEEE754_1(Segment4)
    YQ_INTEGER_1(Segment4)
    YQ_IS_INTEGER_1(Segment4)


//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Creates segment from two points
    */
    template <typename T>
    constexpr Segment4<T> segment(const Vector4<T>& a, const Vector4<T>& b) noexcept
    {
        return { a, b };
    }

    YQ_NAN_1(Segment4, Segment4<T>(NAN))
    YQ_ZERO_1(Segment4, Segment4<T>(ZERO))

//  --------------------------------------------------------
//  --------------------------------------------------------

    YQ_IS_FINITE_1( Segment4, is_finite(v.a) && is_finite(v.b))
    YQ_IS_NAN_1(Segment4, is_nan(v.a) || is_nan(v.b))
    
    /*! \brief Right side scaling of the segment
    */
    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Segment4<product_t<T,U>> operator*(T, const Segment4<U>&) noexcept;

    /*! \brief Creates axially aligned bounding box from the segment
    */
    template <typename T>
    constexpr AxBox4<T>   aabb(const Segment4<T>& seg) noexcept;

    /*! \brief Computes the length of the segmetn
    */
    template <typename T>
    T       length(const Segment4<T>& seg);

    /*! \brief Computes the midpoint of the segmetn
    */
    template <typename T>
    constexpr Vector4<T>     midpoint(const Segment4<T>& seg) noexcept;
    
    /*! \brief Computes a point along the segment based on a fractional position
    
        \param[in]  seg Segment
        \param[in]  f   Fractional point
    */
    template <typename T>
    requires has_ieee754_v<T>
    constexpr Vector4<T>     point(const Segment4<T>& seg, ieee754_t<T> f) noexcept;
}

YQ_TYPE_DECLARE(yq::Segment4D)
YQ_TYPE_DECLARE(yq::Segment4F)
YQ_TYPE_DECLARE(yq::Segment4I)
YQ_TYPE_DECLARE(yq::Segment4U)

