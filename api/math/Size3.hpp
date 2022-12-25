////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Size2.hpp"

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
        
        //! Defaulted comparison operator
        constexpr bool    operator==(const Size3&) const noexcept = default;
        
        /*! \brief Implicit Conversion to floating point sizes
        */
        template <typename U>
        requires (std::is_integral_v<T> && std::is_floating_point_v<U> && !std::is_same_v<T,U>)
        constexpr operator Size3<U>() const 
        {
            return { (U) x, (U) y, (U) z };
        }
        
        //! Depth (Z-dimension)
        constexpr T   depth() const { return z; }
        
        //! Detects if this object eclipses the other
        constexpr bool   eclipses(const Size3<T>& small) const noexcept
        {
            return (x >= small.x) && (y >= small.y) && (z >= small.z );
        }

        //! Height (Y-dimension)
        constexpr T   height() const { return y; }

        //! Volume of this size
        constexpr cube_t<T> volume() const noexcept
        {
            return x*y*z;
        }

        //! Width (X-dimension)
        constexpr T   width() const { return x; }
        
        //! Swizzles the x/y components to a Size2
        constexpr Size2<T>  xy() const noexcept { return { x, y }; }
    };

    YQ_NAN_1(Size3, Size3<T>{ nan_v<T>, nan_v<T>, nan_v<T>  })
    YQ_IS_NAN_1(Size3, is_nan(v.x) || is_nan(v.y) || is_nan(v.z))
    YQ_IS_FINITE_1(Size3, is_finite(v.x) && is_finite(v.y) && is_finite(v.z) )
    YQ_ZERO_1(Size3, Size3<T>{ zero_v<T>, zero_v<T>, zero_v<T> })
    
    //! Computes volume of the size
    template <typename T>
    constexpr auto    volume(const Size3<T>& size) noexcept
    {
        return size.volume();
    }

    template <typename S, typename T>
    S&  as_stream(S& s, const Size3<T>& v)
    {
        return s << "[" << v.x << "x" << v.y << "x" << v.z << "]";
    }
    
    template <typename T>
    Stream& operator<<(Stream&s, const Size3<T>& v)
    {
        return as_stream(s, v);
    }

    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const Size3<T>& v)
    {
        return as_stream(s, v);
    }
}

YQ_TYPE_DECLARE(yq::Size3D)
YQ_TYPE_DECLARE(yq::Size3F)
YQ_TYPE_DECLARE(yq::Size3I)
YQ_TYPE_DECLARE(yq::Size3U)
