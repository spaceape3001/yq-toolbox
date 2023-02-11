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
        
        /*! \brief Implicit Conversion to floating point sizes
        */
        template <typename U>
        requires (std::is_integral_v<T> && std::is_floating_point_v<U> && !std::is_same_v<T,U>)
        constexpr operator Size4<U>() const 
        {
            return { (U) x, (U) y, (U) z };
        }
        
        //! Duration (W-dimension)
        constexpr T   duration() const { return w; }

        //! Depth (Z-dimension)
        constexpr T   depth() const { return z; }
        
        //! Detects if this object eclipses the other
        constexpr bool   eclipses(const Size4<T>& small) const noexcept
        {
            return (x >= small.x) && (y >= small.y) && (z >= small.z );
        }

        //! Height (Y-dimension)
        constexpr T   height() const { return y; }

        //! Volume of this size
        constexpr fourth_t<T> hypervolume() const noexcept
        {
            return x*y*z*w;
        }


        //! Width (X-dimension)
        constexpr T   width() const { return x; }
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
    constexpr auto    hypervolume(const Size4<T>& size) noexcept
    {
        return size.hypervolume();
    }

    template <typename S, typename T>
    S&  as_stream(S& s, const Size4<T>& v)
    {
        return s << "[" << v.x << "x" << v.y << "x" << v.z << "x" << v.w << "]";
    }
    
    template <typename T>
    Stream& operator<<(Stream&s, const Size4<T>& v)
    {
        return as_stream(s, v);
    }

    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const Size4<T>& v)
    {
        return as_stream(s, v);
    }
}

YQ_TYPE_DECLARE(yq::Size4D)
YQ_TYPE_DECLARE(yq::Size4F)
YQ_TYPE_DECLARE(yq::Size4I)
YQ_TYPE_DECLARE(yq::Size4U)
