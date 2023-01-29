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
    struct Size1 {
        
        //! Capture our template argument
        using component_type    = T;
    
        //! X-size
        T   x;
        
        //! Defaulted comparsion operator
        constexpr bool    operator==(const Size1&) const noexcept = default;
        
        /*! \brief Implicit Conversion to floating point sizes
        */
        template <typename U>
        requires (std::is_integral_v<T> && std::is_floating_point_v<U> && !std::is_same_v<T,U>)
        constexpr operator Size1<U>() const 
        {
            return { (U) x };
        }

        //! Tests to see if the left fully encloses the right
        bool                contains(const Size1& b) const noexcept
        {
            return (x >= b.x);
        }

        //! Width (X-dimension)
        constexpr T         width() const { return x; }
    };

    YQ_NAN_1(Size1, Size1<T>{ nan_v<T> })
    YQ_IS_NAN_1(Size1, is_nan(v.x) )
    YQ_IS_FINITE_1(Size1, is_finite(v.x) )
    YQ_ZERO_1(Size1, Size1<T>{ zero_v<T> })
    
    
    /*! \brief Streams the size to a stream-like object */
    template <typename S, typename T>
    S&  as_stream(S& s, const Size1<T>& v)
    {
        return s << "[" << v.x << "]";
    }
    
    /*! \brief Streams to a stream
    */
    template <typename T>
    Stream& operator<<(Stream&s, const Size1<T>& v)
    {
        return as_stream(s, v);
    }

    /*! \brief Streams to to a logging stream
    */
    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const Size1<T>& v)
    {
        return as_stream(s, v);
    }
}

YQ_TYPE_DECLARE(yq::Size1D)
YQ_TYPE_DECLARE(yq::Size1F)
YQ_TYPE_DECLARE(yq::Size1I)
YQ_TYPE_DECLARE(yq::Size1U)
