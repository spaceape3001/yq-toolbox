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
        
        template <typename=void> requires trait::has_nan_v<T>
        consteval Size2(nan_t) : Size2(ALL, nan_v<T>) {}
        consteval Size2(zero_t) : Size2(ALL, zero_v<T>) {}
        
        //! Defaulted comparsion operator
        constexpr bool    operator==(const Size2&) const noexcept = default;
        
        /*! \brief Implicit Conversion to floating point sizes
        */
        template <typename U>
        requires (std::is_integral_v<T> && std::is_floating_point_v<U> && !std::is_same_v<T,U>)
        constexpr operator Size2<U>() const 
        {
            return { (U) x, (U) y };
        }
      
        //! Returns the area
        constexpr trait::square_t<T> area() const noexcept
        {
            return x*y;
        }

        //! Tests to see if the left fully encloses the right
        bool                eclipses(const Size2& b) const noexcept
        {
            return (x >= b.x) && (y >= b.y);
        }
        
        //! Height (Y-dimension)
        constexpr T         height() const { return y; }

        //! Width (X-dimension)
        constexpr T         width() const { return x; }

        /*! \brief Shrinks to fit the given frame

            This shrinks a size to fit the given frame (no spillage), preserving aspect ratio.

            \param[in]  frame   Desired frame
        */
        Size2               shrink_to_fit(const Size2& frame) const
        {
            using sq_t  = decltype(T()*T());
            
            //  --------------------------------------
            //  Check for reasons to not do the math...
        
            if(frame.eclipses(*this))           // we already fit
                return *this;
            if(frame.area() == zero_v<sq_t>)     // frame is bogus
                return *this;
            if(area() == zero_v<sq_t>)    // dims is bogus
                return *this;

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
            
            if(y*frame.x > x*frame.y){
                return Size2<T>{ (x * frame.y)/y , frame.y };
            } else {
                return Size2<T>{ frame.x, (y*frame.x)/x };
            }
        }
    };

    YQ_NAN_1(Size2, Size2<T>(NAN))
    YQ_ZERO_1(Size2, Size2<T>(ZERO))

    YQ_IS_NAN_1(Size2, is_nan(v.x) || is_nan(v.y) )
    YQ_IS_FINITE_1(Size2, is_finite(v.x) && is_finite(v.y) )
    
    
    /*! \brief Computes the area of this size
    */
    template <typename T>
    constexpr auto    area(const Size2<T>& sz) noexcept
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
        return dims.shrink_to_fit(frame);
        
    }
    
    /*! \brief Streams the size to a stream-like object */
    template <typename S, typename T>
    S&  as_stream(S& s, const Size2<T>& v)
    {
        return s << "[" << v.x << "x" << v.y << "]";
    }
    
    /*! \brief Streams to a stream
    */
    template <typename T>
    Stream& operator<<(Stream&s, const Size2<T>& v)
    {
        return as_stream(s, v);
    }

    /*! \brief Streams to to a logging stream
    */
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
