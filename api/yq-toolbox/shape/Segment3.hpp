////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#define YQ_MATH_SEGMENT3_HPP 1

#include <yq/typedef/segment3.hpp>

#include <yq-toolbox/keywords.hpp>
#include <yq-toolbox/basic/Expect.hpp>
#include <yq/trait/is_floating_point.hpp>
#include <yq/trait/product.hpp>
#include <yq/trait/quotient.hpp>
#include <yq/trait/self_divide.hpp>
#include <yq/trait/self_multiply.hpp>
#include <yq/trait/unity.hpp>
#include <yq-toolbox/vector/Vector3.hpp>

namespace log4cpp { class CategoryStream; }

namespace yq {
    template <typename> struct Segment1;
    template <typename> struct Segment2;
    template <typename> struct Segment4;
    template <typename> struct SegmentData;
    template <typename> struct Tensor31;
    template <typename> struct Tensor32;
    template <typename> struct Tensor33;
    template <typename> struct Tensor34;

    /*! \brief Segment in 3D
    */
    template <typename T>
    struct Segment3 {
        //! Capture the template parameter
        using component_type    = T;
    
        //! First point
        Vector3<T>  a;

        //! Second point
        Vector3<T>  b;
        
        //! Default constructor
        constexpr Segment3() noexcept = default;

        //! Component wise constructor (vector and vector)
        constexpr Segment3(const Vector3<T>& _a, const Vector3<T>& _b) : a(_a), b(_b) {}

        //! NaN constructor
        template <typename=void> requires has_nan_v<T>
        constexpr Segment3(nan_t) : Segment3( Vector3<T>(NAN), Vector3<T>(NAN)) {}

        //! Zero constructor
        constexpr Segment3(zero_t) : Segment3( Vector3<T>(ZERO), Vector3<T>(ZERO)) {}

        //! Converter to another segment3 of compatible data types
        template <typename U>
        requires std::is_nothrow_convertible_v<T,U>
        explicit constexpr operator Segment3<U>() const noexcept
        {
            return { (Vector3<U>) a, (Vector3<U>) b };
        }
        
        //! Converter to another segment3 of compatible data types
        template <typename U>
        requires (std::is_convertible_v<T,U> && !std::is_nothrow_convertible_v<T,U>)
        explicit constexpr operator Segment3<U>() const 
        {
            return { (Vector3<U>) a, (Vector3<U>) b };
        }

        //! Defaulted equality
        constexpr bool operator==(const Segment3&) const noexcept = default;

        //! Converts to segment data
        constexpr operator SegmentData<Vector3<T>>() const noexcept;

        //! Affirmation (positive) operator
        constexpr Segment3      operator+() const noexcept;

        //! Negation operator
        constexpr Segment3      operator-() const noexcept;
        
        
        //! Returns the segment displaced by the given amount
        Segment3                operator+(const Vector3<T>&) const noexcept;

        //! Returns the segment anti-displaced by the given amount
        Segment3                operator-(const Vector3<T>&) const noexcept;
        
        //! Moves the segment by the given amount (ie, added to both a and b)
        Segment3&               operator+=(const Vector3<T>&) noexcept;

        //! Moves the segment opposite to the given amount
        Segment3&               operator-=(const Vector3<T>&) noexcept;
        
        //! Scale the segment on both values
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Segment3<product_t<T,U>>    operator*(U) const noexcept;
        
        //! Self-scaling for the segment
        template <typename U>
        requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
        Segment3<T>&                operator*=(U)  noexcept;
        
        //! Projects segment into one dimension
        template <typename U>
        Segment1<product_t<T,U>>    operator*(const Tensor31<U>&) const noexcept;

        //! Projects segment into two dimensions
        template <typename U>
        Segment2<product_t<T,U>>    operator*(const Tensor32<U>&) const noexcept;

        //! Projects segment into three dimensions
        template <typename U>
        Segment3<product_t<T,U>>    operator*(const Tensor33<U>&) const noexcept;

        //! Projects segment in four dimensions
        template <typename U>
        Segment4<product_t<T,U>>    operator*(const Tensor34<U>&) const noexcept;
        
        //! Self-projection of segment with tensor
        template <typename U>
        requires self_multiply_v<T,U>
        Segment3&                   operator*=(const Tensor33<U>&) noexcept;
        
        //! Returns a scaled down the segment by the specified amount
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Segment3<quotient_t<T,U>>   operator/(U) const noexcept;
        
        //! Self-scaling down this segment by the specified amount
        template <typename U>
        requires (is_arithmetic_v<U> && self_divide_v<T,U>)
        Segment3<T>&                operator/=(U)  noexcept;


        //! Bounding box to this segment
        constexpr AxBox3<T>     bounds() const noexcept;

        //! Net displacement
        constexpr Vector3<T>  delta() const noexcept;
        
        //! Computes the fraction along the segment for given X value
        Expect<unity_t<T>>   fraction_x(T, T ep=zero_v<T>) const noexcept;

        //! Computes the fraction along the segment for given Y value
        Expect<unity_t<T>>   fraction_y(T, T ep=zero_v<T>) const noexcept;

        //! Computes the fraction along the segment for given Z value
        Expect<unity_t<T>>   fraction_z(T, T ep=zero_v<T>) const noexcept;

        //! Computes the intercept point for specified X
        //! \param[in]  ep  Delta to consider this segment to have no x-variation (and thus, unsolveable)
        //! \return Returns Point of intercept on the segment
        Expect<Vector3<T>> intercept_x(T, T ep=zero_v<T>) const noexcept;
        
        //! Computes the intercept point for specified Y
        //! \param[in]  ep  Delta to consider this segment to have no y-variation (and thus, unsolveable)
        //! \return Returns Point of intercept on the segment
        Expect<Vector3<T>> intercept_y(T, T ep=zero_v<T>) const noexcept;

        //! Computes the intercept point for specified Z
        //! \param[in]  ep  Delta to consider this segment to have no z-variation (and thus, unsolveable)
        //! \return Returns Point of intercept on the segment
        Expect<Vector3<T>> intercept_z(T, T ep=zero_v<T>) const noexcept;


        //! Length of the segment
        T   length() const;

        //! Square of the length
        constexpr square_t<T> length²() const noexcept;
        
        //! Segment mid-point
        constexpr Vector3<T>  midpoint() const noexcept;

        /*! \brief Computes a point along the segment based on a fractional position
        
            \param[in]  f   Fractional point
        */
        template <typename=void>
        requires has_ieee754_v<T>
        constexpr Vector3<T>     point(ieee754_t<T> f) const noexcept;
    };

    YQ_INTEGER_1(Segment3)
    YQ_IS_INTEGER_1(Segment3)
    YQ_IEEE754_1(Segment3)

//  --------------------------------------------------------
//  COMPOSITION


    YQ_NAN_1(Segment3, Segment3<T>(NAN))
    YQ_ZERO_1(Segment3, Segment3<T>(ZERO))

    /*! \brief Creates segment from two points
    */
    template <typename T>
    constexpr Segment3<T> segment(const Vector3<T>& a, const Vector3<T>& b) noexcept
    {
        return { a, b };
    }

//  --------------------------------------------------------
//  --------------------------------------------------------

    YQ_IS_FINITE_1( Segment3, is_finite(v.a) && is_finite(v.b))
    YQ_IS_NAN_1(Segment3, is_nan(v.a) || is_nan(v.b))

    //! Scales right segment by left factor
    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Segment3<product_t<T,U>> operator*(T, const Segment3<U>&) noexcept;

    /*! \brief Creates axially aligned bounding box from the segment
    */
    template <typename T>
    constexpr AxBox3<T>   aabb(const Segment3<T>& seg) noexcept;


    /*! \brief Computes the length of the segmetn
    */
    template <typename T>
    T       length(const Segment3<T>& seg);

    /*! \brief Computes the midpoint of the segmetn
    */
    template <typename T>
    constexpr Vector3<T>     midpoint(const Segment3<T>& seg) noexcept;

    /*! \brief Computes a point along the segment based on a fractional position
    
        \param[in]  seg Segment
        \param[in]  f   Fractional point
    */
    template <typename T>
    requires has_ieee754_v<T>
    constexpr Vector3<T>     point(const Segment3<T>& seg, ieee754_t<T> f) noexcept;
}

YQ_TYPE_DECLARE(yq::Segment3D)
YQ_TYPE_DECLARE(yq::Segment3F)
YQ_TYPE_DECLARE(yq::Segment3I)
YQ_TYPE_DECLARE(yq::Segment3U)

