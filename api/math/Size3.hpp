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
        T   x;
        T   y;
        T   z;
        
        bool    operator==(const Size3&) const noexcept = default;
        
        constexpr T   width() const { return x; }
        constexpr T   height() const { return y; }
        constexpr T   depth() const { return z; }
        
        template <typename U>
        requires (std::is_integral_v<T> && std::is_floating_point_v<U> && !std::is_same_v<T,U>)
        constexpr operator Size3<U>() const 
        {
            return { (U) x, (U) y, (U) z };
        }
        
    };

    YQ_NAN_1(Size3, Size3<T>{ nan_v<T>, nan_v<T>, nan_v<T>  })
    YQ_IS_NAN_1(Size3, is_nan(v.x) || is_nan(v.y) || is_nan(v.z))
    YQ_IS_FINITE_1(Size3, is_finite(v.x) && is_finite(v.y) && is_finite(v.z) )
    YQ_ZERO_1(Size3, Size3<T>{ zero_v<T>, zero_v<T>, zero_v<T> })
    
    template <typename T>
    Size2<T>        xy(const Size3<T>&a)
    {
        return { a.x, a.y };
    }

    
    template <typename T>
    constexpr bool    within(const Size3<T>& big, const Size3<T>& small);
    
    template <typename T>
    constexpr auto    volume(const Size3<T>& sz)
    {
        return sz.x*sz.y*sz.z;
    }


    template <typename T>
    constexpr bool   within(const Size3<T>& big, const Size3<T>& small)
    {
        return (big.x >= small.x) && (big.y >= small.y) && (big.z >= small.z );
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
