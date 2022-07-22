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
    struct Size2 {
        T   x;
        T   y;
        
        bool    operator==(const Size2&) const noexcept = default;
        
        constexpr T   width() const { return x; }
        constexpr T   height() const { return y; }
        
        template <typename U>
        requires (std::is_integral_v<T> && std::is_floating_point_v<U> && !std::is_same_v<T,U>)
        constexpr operator Size2<U>() const 
        {
            return { (U) x, (U) y };
        }
        
    };

    YQ_NAN_1(Size2, Size2<T>{ nan_v<T>, nan_v<T> })
    YQ_IS_NAN_1(Size2, is_nan(v.x) || is_nan(v.y) )
    YQ_IS_FINITE_1(Size2, is_finite(v.x) && is_finite(v.y) )
    YQ_ZERO_1(Size2, Size2<T>{ zero_v<T>, zero_v<T> })
    
    
    template <typename T>
    constexpr bool    within(const Size2<T>& big, const Size2<T>& small);
    
    template <typename T>
    constexpr auto    area(const Size2<T>& sz)
    {
        return sz.x*sz.y;
    }
    
    /*! \brief Shrinks a size to fit the frame
        
        This shrinks a size to fit the given frame (no spillage), preserving aspect ratio.
        
        \param[in]  dims    Size being shrunk
        \param[in]  frame   Desired frame
    */
    template <typename T>
    Size2<T>  shrink_to_fit_within(const Size2<T>& dims, const Size2<T>& frame)
    {
        using sq_t  = decltype(T()*T());
    
        if(within(frame, dims))
            return dims;
        if(area(frame) == zero_v<sq_t>)  // frame is bogus
            return dims;
        if(area(dims) == zero_v<sq_t>)    // dims is bogus
            return dims;

        /*
            The relative "shrink" factor in each dimension
            
            fx = dims.x / frame.x
            fy = dims.y / frame.y
            
            And the greater one dictates which axis is held constant 
            while the other is shrunk by the same amount.  However
            the above would decimate precision with integer numbers,
            therefore we need to rewrite the conditional to avoid.
            
            dims.y      dims.x
            -------  > --------
            frame.y     frame.x
            
            dims.y * frame.x > dim.x * frame.y
            
            Still have the issue of integer overflow... 
            address that later if that becomes a concern.
        */
        
        if(dims.y*frame.x > dims.x*frame.y){
            return Size2<T>{ (dims.x * frame.y)/dims.y , frame.y };
        } else {
            return Size2<T>{ frame.x, (dims.y*frame.x)/dims.x };
        }
        
    }

    template <typename T>
    constexpr bool   within(const Size2<T>& big, const Size2<T>& small)
    {
        return (big.x >= small.x) && (big.y >= small.y);
    }

    template <typename S, typename T>
    S&  as_stream(S& s, const Size2<T>& v)
    {
        return s << "[" << v.x << "x" << v.y << "]";
    }
    
    template <typename T>
    Stream& operator<<(Stream&s, const Size2<T>& v)
    {
        return as_stream(s, v);
    }

    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const Size2<T>& v)
    {
        return as_stream(s, v);
    }
}

YQ_TYPE_DECLARE(yq::Size2D)
YQ_TYPE_DECLARE(yq::Size2F)
YQ_TYPE_DECLARE(yq::Size2I)
YQ_TYPE_DECLARE(yq::Size2U)
