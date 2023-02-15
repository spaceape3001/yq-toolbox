////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>

namespace yq {

    /*! Size object to hold a simple x/y dimensions
    
        This implicitly defines a region of zero to X-/Y-.
    */
    template <typename T>
    struct Size2 {
        
        //! Capture our template argument
        using component_type    = T;
    
        //! X-size
        T   x;
        
        //! Y-size
        T   y;

        constexpr Size2() noexcept = default;
        constexpr Size2(T _x, T _y) noexcept : x(_x), y(_y) {}
        constexpr Size2(all_t, T v) noexcept : x(v), y(v) {}
        
        template <typename=void> requires has_nan_v<T>
        consteval Size2(nan_t) : Size2(ALL, nan_v<T>) {}
        consteval Size2(zero_t) : Size2(ALL, zero_v<T>) {}
        
        template <typename U>
        requires std::is_nothrow_convertible_v<T,U>
        explicit constexpr operator Size2<U>() const noexcept
        {
            return { (U) x, (U) y };
        }
        
        template <typename U>
        requires (std::is_convertible_v<T,U> && !std::is_nothrow_convertible_v<T,U>)
        explicit constexpr operator Size2<U>() const 
        {
            return { (U) x, (U) y };
        }

        //! Defaulted comparsion operator
        constexpr bool    operator==(const Size2&) const noexcept = default;
        
        
        constexpr Size2 operator+() const noexcept;
        constexpr Size2 operator-() const noexcept;
        
        constexpr Size2 operator+(const Size2&) const noexcept;
        Size2& operator+=(const Size2&) noexcept;

        constexpr Size2 operator-(const Size2&) const noexcept;
        Size2& operator-=(const Size2&) noexcept;
        
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Size2<product_t<T,U>> operator*(U) const noexcept;
        
        template <typename U>
        requires (is_arithmetic_v<U> && self_mul_v<T,U>)
        Size2& operator*=(U) noexcept;
        
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Size2<quotient_t<T,U>> operator/(U) const noexcept;
        
        template <typename U>
        requires (is_arithmetic_v<U> && self_div_v<T,U>)
        Size2& operator/=(U) noexcept;
      
        //! Returns the area
        constexpr square_t<T> area() const noexcept;

        //! Tests to see if the left fully encloses the right
        bool                eclipses(const Size2& b) const noexcept;
        
        //! Height (Y-dimension)
        constexpr T         height() const noexcept;

        //! Width (X-dimension)
        constexpr T         width() const noexcept;

        /*! \brief Shrinks to fit the given frame

            This shrinks a size to fit the given frame (no spillage), preserving aspect ratio.

            \param[in]  frame   Desired frame
        */
        Size2               shrink_to_fit(const Size2& frame) const;
    };

    YQ_IEEE754_1(Size2)
    YQ_INTEGER_1(Size2)
    YQ_IS_INTEGER_1(Size2)
    
    YQ_NAN_1(Size2, Size2<T>(NAN))
    YQ_ZERO_1(Size2, Size2<T>(ZERO))

    YQ_IS_NAN_1(Size2, is_nan(v.x) || is_nan(v.y) )
    YQ_IS_FINITE_1(Size2, is_finite(v.x) && is_finite(v.y) )
    
    
    /*! \brief Computes the area of this size
    */
    template <typename T>
    constexpr auto    area(const Size2<T>& sz) noexcept;
    
    /*! \brief Shrinks a size to fit the frame
        
        This shrinks a size to fit the given frame (no spillage), preserving aspect ratio.
        
        \param[in]  dims    Size being shrunk
        \param[in]  frame   Desired frame
    */
    template <typename T>
    Size2<T>  shrink_to_fit_within(const Size2<T>& dims, const Size2<T>& frame);
    
    /*! \brief Streams the size to a stream-like object */
    template <typename S, typename T>
    S&  as_stream(S& s, const Size2<T>& v);
    
    /*! \brief Streams to a stream
    */
    template <typename T>
    Stream& operator<<(Stream&s, const Size2<T>& v);

    /*! \brief Streams to to a logging stream
    */
    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const Size2<T>& v);

    template <typename T, typename U>
    requires is_arithmetic_v<T,U>
    constexpr Size2<product_t<T,U>> operator*(T a, const Size2<U>& b) noexcept;
}

YQ_TYPE_DECLARE(yq::Size2D)
YQ_TYPE_DECLARE(yq::Size2F)
YQ_TYPE_DECLARE(yq::Size2I)
YQ_TYPE_DECLARE(yq::Size2U)
