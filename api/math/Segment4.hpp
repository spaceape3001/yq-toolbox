////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <math/preamble.hpp>
#include <math/Vector4.hpp>

namespace yq {

    template <typename T>
    struct Segment4 {
        //! Capture the template parameter
        using component_type    = T;
    
        Vector4<T>  a, b;
        
        constexpr Segment4() noexcept = default;
        constexpr Segment4(const Vector4<T>& _a, const Vector4<T>& _b) : a(_a), b(_b) {}
        template <typename=void> requires has_nan_v<T>
        constexpr Segment4(nan_t) : Segment4( Vector4<T>(NAN), Vector4<T>(NAN)) {}
        constexpr Segment4(zero_t) : Segment4( Vector4<T>(ZERO), Vector4<T>(ZERO)) {}

        template <typename U>
        requires std::is_nothrow_convertible_v<T,U>
        explicit constexpr operator Segment4<U>() const noexcept
        {
            return { (Vector4<U>) a, (Vector4<U>) b };
        }
        
        template <typename U>
        requires (std::is_convertible_v<T,U> && !std::is_nothrow_convertible_v<T,U>)
        explicit constexpr operator Segment4<U>() const 
        {
            return { (Vector4<U>) a, (Vector4<U>) b };
        }

        //! Defaulted equality
        constexpr bool operator==(const Segment4&) const noexcept = default;

        constexpr operator SegmentData<Vector4<T>>() const noexcept;

        constexpr Segment4      operator+() const noexcept;
        constexpr Segment4      operator-() const noexcept;
        
        
        Segment4                operator+(const Vector4<T>&) const noexcept;
        Segment4                operator-(const Vector4<T>&) const noexcept;
        
        Segment4&               operator+=(const Vector4<T>&) noexcept;
        Segment4&               operator-=(const Vector4<T>&) noexcept;
        
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Segment4<product_t<T,U>>    operator*(U) const noexcept;
        
        template <typename U>
        requires (is_arithmetic_v<U> && self_mul_v<T,U>)
        Segment4<T>&                operator*=(U)  noexcept;
        

        template <typename U>
        Segment1<product_t<T,U>>    operator*(const Tensor41<U>&) const noexcept;

        template <typename U>
        Segment2<product_t<T,U>>    operator*(const Tensor42<U>&) const noexcept;

        template <typename U>
        Segment3<product_t<T,U>>    operator*(const Tensor43<U>&) const noexcept;

        template <typename U>
        Segment4<product_t<T,U>>    operator*(const Tensor44<U>&) const noexcept;
        
        template <typename U>
        requires self_mul_v<T,U>
        Segment4&                   operator*=(const Tensor44<U>&) noexcept;

        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Segment4<quotient_t<T,U>>   operator/(U) const noexcept;
        
        template <typename U>
        requires (is_arithmetic_v<U> && self_div_v<T,U>)
        Segment4<T>&                operator/=(U)  noexcept;

        constexpr AxBox4<T>     bounds() const noexcept;
        
        //! Net displacement
        constexpr Vector4<T>  delta() const noexcept;
        
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
    
    template <typename T, typename U>
    requires is_arithmetic_v<T,U>
    constexpr Segment4<product_t<T,U>> operator*(T, const Segment4<T>&) noexcept;

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

