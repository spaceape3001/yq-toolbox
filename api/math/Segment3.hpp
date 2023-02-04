////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <math/preamble.hpp>
#include <math/Vector3.hpp>

namespace yq {

    template <typename T>
    struct Segment3 {
        //! Capture the template parameter
        using component_type    = T;
    
        Vector3<T>  a, b;
        
        constexpr Segment3() noexcept = default;
        constexpr Segment3(const Vector3<T>& _a, const Vector3<T>& _b) : a(_a), b(_b) {}
        template <typename=void> requires trait::has_nan_v<T>
        constexpr Segment3(nan_t) : Segment3( Vector3<T>(NAN), Vector3<T>(NAN)) {}
        constexpr Segment3(zero_t) : Segment3( Vector3<T>(ZERO), Vector3<T>(ZERO)) {}

        //! Defaulted equality
        constexpr bool operator==(const Segment3&) const noexcept = default;

        constexpr operator SegmentData<Vector3<T>>() const noexcept;

        constexpr Segment3      operator+() const noexcept;
        constexpr Segment3      operator-() const noexcept;
        
        
        Segment3                operator+(const Vector3<T>&) const noexcept;
        Segment3                operator-(const Vector3<T>&) const noexcept;
        
        Segment3&               operator+=(const Vector3<T>&) noexcept;
        Segment3&               operator-=(const Vector3<T>&) noexcept;
        
        template <typename U>
        requires trait::is_arithmetic_v<U>
        constexpr Segment3<product_t<T,U>>    operator*(U) const noexcept;
        
        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
        Segment3<T>&                operator*=(U)  noexcept;
        
        template <typename U>
        Segment1<product_t<T,U>>    operator*(const Tensor31<U>&) const noexcept;

        template <typename U>
        Segment2<product_t<T,U>>    operator*(const Tensor32<U>&) const noexcept;

        template <typename U>
        Segment3<product_t<T,U>>    operator*(const Tensor33<U>&) const noexcept;

        template <typename U>
        Segment4<product_t<T,U>>    operator*(const Tensor34<U>&) const noexcept;
        
        template <typename U>
        requires trait::self_mul_v<T,U>
        Segment3&                   operator*=(const Tensor33<U>&) noexcept;
        
        template <typename U>
        requires trait::is_arithmetic_v<U>
        constexpr Segment3<quotient_t<T,U>>   operator/(U) const noexcept;
        
        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_div_v<T,U>)
        Segment3<T>&                operator/=(U)  noexcept;


        constexpr AxBox3<T>     bounds() const noexcept;

        //! Net displacement
        constexpr Vector3<T>  delta() const noexcept;
        
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

    template <typename T, typename U>
    requires trait::is_arithmetic_v<T,U>
    constexpr Segment3<product_t<T,U>> operator*(T, const Segment3<T>&) noexcept;

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

