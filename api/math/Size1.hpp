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
        
        constexpr Size1() noexcept = default;
        constexpr Size1(T _x) noexcept : x(_x) {}
        constexpr Size1(all_t, T v) noexcept : x(v) {}
        
        template <typename=void> requires has_nan_v<T>
        consteval Size1(nan_t) : Size1(ALL, nan_v<T>) {}
        consteval Size1(zero_t) : Size1(ALL, zero_v<T>) {}
        
        
        //! Defaulted comparsion operator
        constexpr bool    operator==(const Size1&) const noexcept = default;
        
        template <typename U>
        requires std::is_nothrow_convertible_v<T,U>
        explicit constexpr operator Size1<U>() const noexcept
        {
            return { (U) x };
        }
        
        template <typename U>
        requires (std::is_convertible_v<T,U> && !std::is_nothrow_convertible_v<T,U>)
        explicit constexpr operator Size1<U>() const 
        {
            return { (U) x };
        }

        //! Tests to see if the left fully encloses the right
        constexpr bool  contains(const Size1& b) const noexcept
        {
            return (x >= b.x);
        }
        
        constexpr T         length() const noexcept { return x; }

        //! Width (X-dimension)
        constexpr T         width() const { return x; }
    };

    YQ_IEEE754_1(Size1)
    YQ_INTEGER_1(Size1)
    YQ_IS_INTEGER_1(Size1)

    YQ_NAN_1(Size1, Size1<T>(NAN))
    YQ_ZERO_1(Size1, Size1<T>(ZERO))
    
    YQ_IS_NAN_1(Size1, is_nan(v.x) )
    YQ_IS_FINITE_1(Size1, is_finite(v.x) )

    
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
