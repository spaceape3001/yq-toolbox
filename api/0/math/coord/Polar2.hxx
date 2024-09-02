////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/math/coord/Polar2.hpp>
#include <0/math/vector/Vector2.hpp>
#include <0/math/trig.hpp>

namespace yq {

    template <typename A, typename L>
    Polar2<A,L>::Polar2(clock_arg_t, const Vector2<L>& v) : 
        angle(atan(v.x, v.y)), radius(v.length())
    {
    }
    
    template <typename A, typename L>
    Polar2<A,L>::Polar2(euler_t, const Vector2<L>& v) : 
        angle(atan(v.y, v.x)), radius(v.length())
    {
    }

    template <typename A, typename L>
    Polar2<A,L>::Polar2(const Vector2<L>& v) : Polar2(EULER, v)
    {
    }

    template <typename A, typename L>
    Vector2<L>  Polar2<A,L>::to_clock() const
    {
        return Vector2<L>(radius*sin(angle), radius*cos(angle));
    }
    
    template <typename A, typename L>
    Vector2<L>  Polar2<A,L>::to_euler() const
    {
        return Vector2<L>(radius*cos(angle), radius*sin(angle));
    }

    template <typename A, typename L>
    Polar2<A,L>::operator Vector2<L> () const
    {
        return to_euler();
    }
    
    template <typename A, typename L>
    Vector2<L>  Polar2<A,L>::operator()(clock_arg_t) const
    {
        return to_clock();
    }
    
    template <typename A, typename L>
    Vector2<L>  Polar2<A,L>::operator()(euler_t) const
    {
        return to_euler();
    }
    
    template <typename A, typename L>
    constexpr Polar2<A,L>    Polar2<A,L>::operator+() const noexcept
    {
        return *this;
    }
    
    template <typename A, typename L>
    Polar2<A,L>    Polar2<A,L>::operator-() const
    {
        return Polar2( -to_euler() );
    }
    
    template <typename A, typename L>
    Polar2<A,L> Polar2<A,L>::operator+(const Polar2&b) const
    {
        return Polar2( to_euler() + b.to_euler());
    }
    
    template <typename A, typename L>
    Polar2<A,L>& Polar2<A,L>::operator+=(const Polar2&b)
    {
        *this = *this + b;
        return *this;
    }
    
    template <typename A, typename L>
    Polar2<A,L> Polar2<A,L>::operator-(const Polar2&b) const
    {
        return Polar2( to_euler() - b.to_euler());
    }
    
    template <typename A, typename L>
    Polar2<A,L>& Polar2<A,L>::operator-=(const Polar2& b)
    {
        *this = *this - b;
        return *this;
    }
    
    template <typename A, typename L>
    template <typename L2>
    requires is_arithmetic_v<L2>
    Polar2<A, product_t<L,L2>> Polar2<A,L>::operator*(L2 b) const
    {
        using p_t = product_t<L,L2>;
    
        Polar2<A, p_t> ret(angle, radius*b.radius);
        if(ret.radius < zero_v<p_t>)
            ret = ret.to_euler();
            
        return ret;
    }
    
    template <typename A, typename L>
    template <typename L2>
    requires (is_arithmetic_v<L2> && self_multiply_v<L,L2>)
    Polar2<A,L>& Polar2<A,L>::operator *= (L2 b)
    {
        *this = *this * b;
        return *this;
    }

    template <typename A, typename L>
    template <typename L2>
    requires is_arithmetic_v<L2>
    Polar2<A,quotient_t<L,L2>> Polar2<A,L>::operator/(L2 b) const
    {
        using q_t = quotient_t<L,L2>;
        Polar2<A,q_t> ret(angle, radius/b);
        if(ret.radius < zero_v<q_t>)
            ret = ret.to_euler();
        return ret;
    }
    

    template <typename A, typename L>
    template <typename L2>
    requires (is_arithmetic_v<L2> && self_divide_v<L,L2>)
    Polar2<A,L>& Polar2<A,L>::operator /= (L2 b)
    {
        *this = *this / b;
        return *this;
    }
    
////////////////////////////////////////////////////////////////////////////////

    template <typename A, typename L1, typename L2>
    Polar2<A,product_t<L1,L2>> operator*(L1 a, const Polar2<A,L2>&b) 
    {
        using p_t = product_t<L1,L2>;
        Polar2<A,p_t> ret(b.angle, a*b.distance);
        if(ret.radius < zero_v<p_t>)
            ret = ret.to_euler();
        return ret;
    }
    
}

