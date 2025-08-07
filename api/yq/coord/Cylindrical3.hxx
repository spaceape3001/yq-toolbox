////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/coord/Cylindrical3.hpp>
#include <yq/vector/Vector3.hpp>
#include <yq/math/trigonometry.hpp>

namespace yq {

    template <typename A, typename L>
    Cylindrical3<A,L>::Cylindrical3(clock_arg_k, const Vector3<L>& v) : 
        angle(atan(v.x, v.y)), radius(v.length()), z(v.z)
    {
    }
    
    template <typename A, typename L>
    Cylindrical3<A,L>::Cylindrical3(euler_k, const Vector3<L>& v) : 
        angle(atan(v.y, v.x)), radius(v.length()), z(v.z)
    {
    }

    template <typename A, typename L>
    Cylindrical3<A,L>::Cylindrical3(const Vector3<L>& v) : Cylindrical3(EULER, v)
    {
    }

    template <typename A, typename L>
    Vector3<L>  Cylindrical3<A,L>::to_clock() const
    {
        return Vector3<L>(radius*sin(angle), radius*cos(angle), z);
    }
    
    template <typename A, typename L>
    Vector3<L>  Cylindrical3<A,L>::to_euler() const
    {
        return Vector3<L>(radius*cos(angle), radius*sin(angle), z);
    }

    template <typename A, typename L>
    Cylindrical3<A,L>::operator Vector3<L> () const
    {
        return to_euler();
    }
    
    template <typename A, typename L>
    Vector3<L>  Cylindrical3<A,L>::operator()(clock_arg_k) const
    {
        return to_clock();
    }
    
    template <typename A, typename L>
    Vector3<L>  Cylindrical3<A,L>::operator()(euler_k) const
    {
        return to_euler();
    }
    
    template <typename A, typename L>
    constexpr Cylindrical3<A,L>    Cylindrical3<A,L>::operator+() const noexcept
    {
        return *this;
    }
    
    template <typename A, typename L>
    Cylindrical3<A,L>    Cylindrical3<A,L>::operator-() const
    {
        return Cylindrical3( -to_euler() );
    }
    
    template <typename A, typename L>
    Cylindrical3<A,L> Cylindrical3<A,L>::operator+(const Cylindrical3&b) const
    {
        return Cylindrical3( to_euler() + b.to_euler());
    }
    
    template <typename A, typename L>
    Cylindrical3<A,L>& Cylindrical3<A,L>::operator+=(const Cylindrical3&b)
    {
        *this = *this + b;
        return *this;
    }
    
    template <typename A, typename L>
    Cylindrical3<A,L> Cylindrical3<A,L>::operator-(const Cylindrical3&b) const
    {
        return Cylindrical3( to_euler() - b.to_euler());
    }
    
    template <typename A, typename L>
    Cylindrical3<A,L>& Cylindrical3<A,L>::operator-=(const Cylindrical3& b)
    {
        *this = *this - b;
        return *this;
    }
    
    template <typename A, typename L>
    template <typename L2>
    requires is_arithmetic_v<L2>
    Cylindrical3<A, product_t<L,L2>> Cylindrical3<A,L>::operator*(L2 b) const
    {
        using p_t = product_t<L,L2>;
    
        Cylindrical3<A, p_t> ret(angle, radius*b.radius, z*b);
        if(ret.radius < zero_v<p_t>)
            ret = ret.to_euler();
            
        return ret;
    }
    
    template <typename A, typename L>
    template <typename L2>
    requires (is_arithmetic_v<L2> && self_multiply_v<L,L2>)
    Cylindrical3<A,L>& Cylindrical3<A,L>::operator *= (L2 b)
    {
        *this = *this * b;
        return *this;
    }

    template <typename A, typename L>
    template <typename L2>
    requires is_arithmetic_v<L2>
    Cylindrical3<A,quotient_t<L,L2>> Cylindrical3<A,L>::operator/(L2 b) const
    {
        using q_t = quotient_t<L,L2>;
        Cylindrical3<A,q_t> ret(angle, radius/b, z/b);
        if(ret.radius < zero_v<q_t>)
            ret = ret.to_euler();
        return ret;
    }
    

    template <typename A, typename L>
    template <typename L2>
    requires (is_arithmetic_v<L2> && self_divide_v<L,L2>)
    Cylindrical3<A,L>& Cylindrical3<A,L>::operator /= (L2 b)
    {
        *this = *this / b;
        return *this;
    }
    
////////////////////////////////////////////////////////////////////////////////

    template <typename A, typename L1, typename L2>
    Cylindrical3<A,product_t<L1,L2>> operator*(L1 a, const Cylindrical3<A,L2>&b) 
    {
        using p_t = product_t<L1,L2>;
        Cylindrical3<A,p_t> ret(b.angle, a*b.distance, a*b.z);
        if(ret.radius < zero_v<p_t>)
            ret = ret.to_euler();
        return ret;
    }
    
}
