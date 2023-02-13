////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "preamble.hpp"

namespace yq {

    /*! Size object
    */
    template <typename T>
    struct Size4 {

        //! Capture our template argument
        using component_type    = T;

        //! X-size
        T   x;
        
        //! Y-size
        T   y;
        
        //! Z-size
        T   z;
        
        //! W-size
        T   w;

        constexpr Size4() noexcept = default;
        constexpr Size4(T _x, T _y, T _z, T _w) noexcept : x(_x), y(_y), z(_z), w(_w) {}
        constexpr Size4(all_t, T v) noexcept : x(v), y(v), z(v), w(v) {}
        
        template <typename=void> requires has_nan_v<T>
        consteval Size4(nan_t) : Size4(ALL, nan_v<T>) {}
        consteval Size4(zero_t) : Size4(ALL, zero_v<T>) {}


        //! Defaulted comparison operator
        constexpr bool    operator==(const Size4&) const noexcept = default;
        
        /*! \brief Conversion to other types sizes
        */
        template <typename U>
        requires std::is_nothrow_convertible_v<T,U>
        explicit constexpr operator Size4<U>() const noexcept
        {
            return { (U) x, (U) y, (U) z, (U) w };
        }
        
        template <typename U>
        requires (std::is_convertible_v<T,U> && !std::is_nothrow_convertible_v<T,U>)
        explicit constexpr operator Size4<U>() const 
        {
            return { (U) x, (U) y, (U) z, (U) w };
        }
        
        constexpr Size4 operator+() const noexcept;
        constexpr Size4 operator-() const noexcept;
        
        constexpr Size4 operator+(const Size4&) const noexcept;
        Size4& operator+=(const Size4&) noexcept;

        constexpr Size4 operator-(const Size4&) const noexcept;
        Size4& operator-=(const Size4&) noexcept;
        
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Size4<product_t<T,U>> operator*(U) const noexcept;
        
        template <typename U>
        requires (is_arithmetic_v<U> && self_mul_v<T,U>)
        Size4& operator*=(U) noexcept;
        
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Size4<quotient_t<T,U>> operator/(U) const noexcept;
        
        template <typename U>
        requires (is_arithmetic_v<U> && self_div_v<T,U>)
        Size4& operator/=(U) noexcept;


        //! Duration (W-dimension)
        constexpr T   duration() const;

        //! Depth (Z-dimension)
        constexpr T   depth() const;
        
        //! Detects if this object eclipses the other
        constexpr bool   eclipses(const Size4<T>& small) const noexcept;

        //! Height (Y-dimension)
        constexpr T   height() const;

        //! Volume of this size
        constexpr fourth_t<T> hypervolume() const noexcept;


        //! Width (X-dimension)
        constexpr T   width() const;
    };

    YQ_IEEE754_1(Size4)
    YQ_INTEGER_1(Size4)
    YQ_IS_INTEGER_1(Size4)

    YQ_NAN_1(Size4, Size4<T>(NAN))
    YQ_ZERO_1(Size4, Size4<T>(ZERO))
    YQ_IS_NAN_1(Size4, is_nan(v.x) || is_nan(v.y) || is_nan(v.z) || is_nan(v.w))
    YQ_IS_FINITE_1(Size4, is_finite(v.x) && is_finite(v.y) && is_finite(v.z)&& is_finite(v.w) )
    
    //! Computes volume of the size
    template <typename T>
    constexpr auto    hypervolume(const Size4<T>& size) noexcept;

    template <typename S, typename T>
    S&  as_stream(S& s, const Size4<T>& v);
    
    template <typename T>
    Stream& operator<<(Stream&s, const Size4<T>& v);

    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const Size4<T>& v);
}

YQ_TYPE_DECLARE(yq::Size4D)
YQ_TYPE_DECLARE(yq::Size4F)
YQ_TYPE_DECLARE(yq::Size4I)
YQ_TYPE_DECLARE(yq::Size4U)
