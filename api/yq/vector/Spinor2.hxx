////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the quaternion3 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <yq/vector/Spinor2.hpp>
#include <yq/unit/literals.hpp>
#include <yq/math/trigonometry.hpp>
#include <yq/trait/has_abs.hpp>
#include <algorithm>

namespace yq {
//  --------------------------------------------------------
//  CONSTRUCTORS

    #ifdef YQ_MATH_MULTIVECTOR_2_HPP
    template <typename T>
    constexpr Spinor2<T>::Spinor2(const Multivector2<T>&v) : a(v.a), xy(v.xy)
    {
    }
    #endif

    template <typename T>
    Spinor2<T>::Spinor2(ccw_k, Radian v)
    {
        a   = cos(v);
        xy  = sin(v);
    }
        
    template <typename T>
    Spinor2<T>::Spinor2(clockwise_k, Radian v) : Spinor2(CCW, -v)
    {
    }

#if 0
    #ifdef YQ_MATH_TENSOR_2_2_HPP
    template <typename T>
        template <typename>
    requires std::is_floating_point_v<T>
    Spinor2<T>::Spinor2(const Tensor22<T>&t)
    {
        w	= T(0.5) * sqrt(std::max(zero_v<T>, one_v<T>+t.xx+t.yy));
        z	= T(0.5) * sqrt(std::max(zero_v<T>, one_v<T>-t.xx-t.yy));

        z	= copysign(z, t.yx-t.xy);
    }
    #endif
#endif

//  --------------------------------------------------------
//  CLASS OPERATORS

    template <typename T>
    Spinor2<T>      Spinor2<T>::operator+() const
    {
        return *this;
    }
    
    template <typename T>
    Spinor2<T>      Spinor2<T>::operator-() const
    {
        return {-a, -xy};
    }

    template <typename T>
    Spinor2<T> Spinor2<T>::operator~() const
    {
        T l = 1./length();
        return Spinor2<T>(a*l, xy*l);
    }

    template <typename T>
    constexpr Spinor2<T>  Spinor2<T>::operator^(two_k) const noexcept
    {
        return *this * *this;
    }

    template <typename T>
    constexpr Spinor2<T>  Spinor2<T>::operator+ (const Spinor2<T>&b) const noexcept
    {
        return Spinor2(a+b.a,xy+b.xy);
    }

    template <typename T>
    Spinor2<T>& Spinor2<T>::operator+=(const Spinor2<T>&b) noexcept
    {
        a  += b.a;
        xy += b.xy;
        return *this;
    }

    template <typename T>
    constexpr Spinor2<T>  Spinor2<T>::operator- (const Spinor2<T>&b)  const noexcept
    {
        return Spinor2(a-b.a,xy-b.xy);
    }

    template <typename T>
    Spinor2<T>& Spinor2<T>::operator-=(const Spinor2<T>&b) noexcept
    {
        a  -= b.a;
        xy -= b.xy;
        return *this;
    }

    template <typename T>
    constexpr Spinor2<T>  Spinor2<T>::operator* (T b) const noexcept
    {
        return Spinor2<T>(a*b,xy*b);
    }

    template <typename T>
    Spinor2<T>& Spinor2<T>::operator*=(T b) noexcept
    {
        a  *= b;
        xy *= b;
        return *this;
    }


    template <typename T>
    constexpr Spinor2<T>  Spinor2<T>::operator* (const Spinor2&b) const noexcept
    {
        return {
            a*b.a-xy*b.xy,
            xy*b.a+a*b.xy
        };
    }

    template <typename T>
    Spinor2<T>& Spinor2<T>::operator*=(const Spinor2&b) noexcept
    {
        *this = *this * b;
        return *this;
    }

    
    #ifdef YQ_MATH_VECTOR_2_HPP
    template <typename T>
        template <typename U>
    constexpr Vector2<product_t<T,U>>   Spinor2<T>::operator* (const Vector2<U>&b) const noexcept
    {
        return {
            a*b.x - xy*b.y,
            a*b.y + xy*b.x
        };
    }
    #endif

    template <typename T>
    constexpr Spinor2<T>  Spinor2<T>::operator/ (T b) const noexcept
    {
        return {a/b,xy/b};
    }

    template <typename T>
    Spinor2<T>& Spinor2<T>::operator/=(T b) noexcept
    {
        a /= b;
        xy /= b;
        return *this;
    }

//  --------------------------------------------------------
//  CLASS METHODS

    template <typename T>
    Radian               Spinor2<T>::angle() const
    {
        return atan(xy, a);
    }

    template <typename T>
    Radian               Spinor2<T>::angle(ccw_k) const
    {
        return angle();
    }

    template <typename T>
    Radian               Spinor2<T>::angle(clockwise_k) const
    {
        return -angle();
    }

    template <typename T>
    Radian               Spinor2<T>::angle(heading_k) const
    {
        return -angle();
    }

    template <typename T>
    constexpr Spinor2<T>    Spinor2<T>::conj() const noexcept
    { 
        return Spinor2(a,-xy); 
    }

    template <typename T>
    constexpr Spinor2<T>    Spinor2<T>::conjugate() const noexcept
    {
        return conj();
    }

    template <typename T>
    constexpr Spinor2<inverse_t<T>>   Spinor2<T>::inverse() const noexcept
    {
        return conj() / length²();
    }

    template <typename T>
    constexpr square_t<T>    Spinor2<T>::length²() const noexcept
    {
        return a*a+xy*xy;
    }
    
    template <typename T>
    T   Spinor2<T>::length() const
    {
        if constexpr (has_sqrt_v<T>)
            return sqrt(length²());
        return {};
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename T, typename U>
    requires (is_arithmetic_v<T>)
    constexpr Spinor2<product_t<T,U>>  operator*(T a, const Spinor2<U>&b)
    {
        return {a*b.a,a*b.xy};
    }

    template <typename T>
    constexpr Spinor2<T> conjugate(const Spinor2<T>&a)  
    { 
        return Spinor2(a.a,-a.xy); 
    }

    template <typename T, typename R>
    bool is_close(const R& compare, const Spinor2<T>& actual, const Spinor2<T>& expected)
    {
        return compare(length(actual-expected), length(expected));
    }
    
    template <typename T, typename R>
    bool is_close(const R& compare, const Spinor2<T>& actual, std::type_identity_t<T> a, std::type_identity_t<T> xy)
    {
        return is_close(compare, actual, Spinor2<T>(a, xy) );
    }

    template <typename T>
    constexpr square_t<T>  length²(const Spinor2<T>&a)
    {
        return a.length²();
    }

    template <typename T>
    constexpr T  length(const Spinor2<T>&a) 
    {
        return a.length();
    }

    #ifdef YQ_MATH_MULTIVECTOR_2_HPP
    template <typename T>
    Spinor2<T>      spinor(const Multivector2<T>& v)
    {
        return { v.a, v.xy };
    }
    #endif

    #if 0

    #if YQ_MATH_TENSOR_2_2_HPP
    template <typename T>
    requires std::is_floating_point_v<T>
    Spinor2<T>  spinor(const Tensor22<T>& t)
    {
        return Spinor2<T>(t);
    }
    #endif
    #endif
    
    template <typename S, typename T>
    S&  as_stream(S& s, const Spinor2<T>& v)
    {
        return s << "(" << v.a << "," << v.xy << ")";
    }
    
    #ifdef YQ_BASIC_STREAM_HPP_
    template <typename T>
    Stream& operator<<(Stream&s, const Spinor2<T>& v)
    {
        return as_stream(s, v);
    }
    #endif

    #ifdef _LOG4CPP_CATEGORYSTREAM_HH
    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const Spinor2<T>& v)
    {
        return as_stream(s, v);
    }
    #endif
}
