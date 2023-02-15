////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>

namespace yq {

    /*! Size object
    */
    template <typename T>
    struct Size3 {

        //! Capture our template argument
        using component_type    = T;

        //! X-size
        T   x;
        
        //! Y-size
        T   y;
        
        //! Z-size
        T   z;
        
        constexpr Size3() noexcept = default;
        constexpr Size3(T _x, T _y, T _z) noexcept : x(_x), y(_y), z(_z) {}
        constexpr Size3(all_t, T v) noexcept : x(v), y(v), z(v) {}
        
        template <typename=void> requires has_nan_v<T>
        consteval Size3(nan_t) : Size3(ALL, nan_v<T>) {}
        consteval Size3(zero_t) : Size3(ALL, zero_v<T>) {}

        template <typename U>
        requires std::is_nothrow_convertible_v<T,U>
        explicit constexpr operator Size3<U>() const noexcept
        {
            return { (U) x, (U) y, (U) z };
        }
        
        template <typename U>
        requires (std::is_convertible_v<T,U> && !std::is_nothrow_convertible_v<T,U>)
        explicit constexpr operator Size3<U>() const 
        {
            return { (U) x, (U) y, (U) z };
        }

        //! Defaulted comparison operator
        constexpr bool    operator==(const Size3&) const noexcept = default;
        
        
        constexpr Size3 operator+() const noexcept;
        constexpr Size3 operator-() const noexcept;
        
        constexpr Size3 operator+(const Size3&) const noexcept;
        Size3& operator+=(const Size3&) noexcept;

        constexpr Size3 operator-(const Size3&) const noexcept;
        Size3& operator-=(const Size3&) noexcept;
        
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Size3<product_t<T,U>> operator*(U) const noexcept;
        
        template <typename U>
        requires (is_arithmetic_v<U> && self_mul_v<T,U>)
        Size3& operator*=(U) noexcept;
        
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Size3<quotient_t<T,U>> operator/(U) const noexcept;
        
        template <typename U>
        requires (is_arithmetic_v<U> && self_div_v<T,U>)
        Size3& operator/=(U) noexcept;
                
        //! Depth (Z-dimension)
        constexpr T   depth() const;
        
        //! Detects if this object eclipses the other
        constexpr bool   eclipses(const Size3<T>& small) const noexcept;

        //! Height (Y-dimension)
        constexpr T   height() const;

        //! Volume of this size
        constexpr cube_t<T> volume() const noexcept;

        //! Width (X-dimension)
        constexpr T   width() const;
        
        //! Swizzles the x/y components to a Size2
        constexpr Size2<T>  xy() const noexcept;
    };

    YQ_IEEE754_1(Size3)
    YQ_INTEGER_1(Size3)
    YQ_IS_INTEGER_1(Size3)

    YQ_NAN_1(Size3, Size3<T>(NAN))
    YQ_ZERO_1(Size3, Size3<T>(ZERO))
    
    YQ_IS_NAN_1(Size3, is_nan(v.x) || is_nan(v.y) || is_nan(v.z))
    YQ_IS_FINITE_1(Size3, is_finite(v.x) && is_finite(v.y) && is_finite(v.z) )
    
    //! Computes volume of the size
    template <typename T>
    constexpr auto    volume(const Size3<T>& size) noexcept;

    template <typename S, typename T>
    S&  as_stream(S& s, const Size3<T>& v);
    
    template <typename T>
    Stream& operator<<(Stream&s, const Size3<T>& v);

    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const Size3<T>& v);

    template <typename T, typename U>
    requires is_arithmetic_v<T,U>
    constexpr Size3<product_t<T,U>> operator*(T a, const Size3<U>& b) noexcept;
}

YQ_TYPE_DECLARE(yq::Size3D)
YQ_TYPE_DECLARE(yq::Size3F)
YQ_TYPE_DECLARE(yq::Size3I)
YQ_TYPE_DECLARE(yq::Size3U)
