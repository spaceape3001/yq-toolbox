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

    template <typename T>
    template <typename>
    requires std::is_floating_point_v<T>
    Spinor2<T>::Spinor2(ccw_k, MKS<T,dim::Angle>v)
    {
        w   = cos(T(0.5)*v);
        z   = sin(T(0.5)*v);
    }
    
    template <typename T>
    template <typename>
    requires std::is_floating_point_v<T>
    Spinor2<T>::Spinor2(clockwise_k, MKS<T,dim::Angle>v) : Spinor2(CCW, -v)
    {
    }
    
    template <typename T>
    template <typename>
    requires std::is_floating_point_v<T>
    Spinor2<T>::Spinor2(hpr_k, MKS<T,dim::Angle> hdg_or_yaw) : Spinor2(CLOCKWISE, hdg_or_yaw)
    {
    }

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
        return {-w, -z};
    }

    template <typename T>
    template <typename>
    requires std::is_floating_point_v<T>
    Spinor2<T> Spinor2<T>::operator~() const
    {
        T l = 1./length();
        return Spinor2<T>(w*l, z*l);
    }

    template <typename T>
    constexpr square_t<T>  Spinor2<T>::operator^(two_k) const noexcept
    {
        return length²();
    }

    template <typename T>
    constexpr Spinor2<T>  Spinor2<T>::operator+ (const Spinor2<T>&b) const noexcept
    {
        return Spinor2(w+b.w,z+b.z);
    }

    template <typename T>
    Spinor2<T>& Spinor2<T>::operator+=(const Spinor2<T>&b) noexcept
    {
        w += b.w;
        z += b.z;
        return *this;
    }

    template <typename T>
    constexpr Spinor2<T>  Spinor2<T>::operator- (const Spinor2<T>&b)  const noexcept
    {
        return Spinor2(w-b.w,z-b.z);
    }

    template <typename T>
    Spinor2<T>& Spinor2<T>::operator-=(const Spinor2<T>&b) noexcept
    {
        w -= b.w;
        z -= b.z;
        return *this;
    }

    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U>)
    constexpr Spinor2<product_t<T,U>>  Spinor2<T>::operator* (U b) const noexcept
    {
        return Spinor2<product_t<T,U>>(w*b,z*b);
    }

    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
    Spinor2<T>& Spinor2<T>::operator*=(U b) noexcept
    {
        w *= b;
        z *= b;
        return *this;
    }


    template <typename T>
        template <typename U>
    constexpr Spinor2<product_t<T,U>>  Spinor2<T>::operator* (const Spinor2<U>&b) const noexcept
    {
        return Spinor2(
            w*b.w -z*b.z,
            w*b.z +z*b.w
        );
    }

    template <typename T>
        template <typename U>
    requires self_multiply_v<T,U>
    Spinor2<T>& Spinor2<T>::operator*=(const Spinor2<U>&b) noexcept
    {
        if constexpr (std::is_floating_point_v<T>){
            post_mult(*this, b);
        } else {
            *this = *this * b;
        }
        return *this;
    }


    
    #ifdef YQ_MATH_VECTOR_2_HPP
    template <typename T>
        template <typename U>
    requires (std::is_floating_point_v<T> && std::is_floating_point_v<U>)
    constexpr Vector2<product_t<T,U>>   Spinor2<T>::operator* (const Vector2<U>&b) const noexcept
    {
        // Spinor2D Multiplication is Associative, i.e. Q1*Q2*Q3 == Q1*(Q2*Q3)
        // We're going to do the vecAsQuat * ~a portion first, removing the portions of the multiply
        // that would just equate to zero anyways

        // q will be the vector, represented as a quaternion, when multiplied with the conjugate of This
        product_t<T,U> qx =  w*b.x - z*b.y; 
        product_t<T,U> qy =  w*b.y + z*b.x; 
        
        // Next part is the a * q

        // W will always be zero and since we return a Vec3D, we're not even using it -- don't need to calculate it
        // If we throw out the calculations for W, we wind up with this for the multiply
        return Vector2<product_t<T,U>>(
            w*qx + z*qy,
            w*qy + z*qx
        );
    }
    #endif

    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<T>)
    constexpr Spinor2<quotient_t<T,U>>  Spinor2<T>::operator/ (U b) const noexcept
    {
        return {w/b,z/b};
    }

    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_divide_v<T,U>)
    Spinor2<T>& Spinor2<T>::operator/=(U b) noexcept
    {
        w /= b;
        z /= b;
        return *this;
    }

//  --------------------------------------------------------
//  CLASS METHODS

    template <typename T>
        //template <typename>
    //requires std::is_floating_point_v<T>
    Radian               Spinor2<T>::angle() const
    {
        return 2. * atan( abs(z), w);
    }

    template <typename T>
    constexpr Spinor2<T>    Spinor2<T>::conj() const noexcept
    { 
        return Spinor2(w,-z); 
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
        return w*w+z*z;
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
        return {a*b.w,a*b.z};
    }

    template <typename T>
    constexpr Spinor2<T> conjugate(const Spinor2<T>&a)  
    { 
        return Spinor2(a.w,-a.z); 
    }


    template <typename T, typename R>
    bool is_close(const R& compare, const Spinor2<T>& actual, const Spinor2<T>& expected)
    {
        return compare(length(actual-expected), length(expected));
    }
    
    template <typename T, typename R>
    bool is_close(const R& compare, const Spinor2<T>& actual, std::type_identity_t<T> w, std::type_identity_t<T> z)
    {
        return is_close(compare, actual, Spinor2<T>(w, z) );
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


    template <typename T>
    requires std::is_floating_point_v<T>
    void    pre_mult(const Spinor2<T>&a, Spinor2<T>&b)
    {
        b.z = b.z*a.w + b.w*a.z;
        b.w = b.w*a.w - b.z*a.z;
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    void    post_mult(Spinor2<T>&a, const Spinor2<T>&b)
    {
        a.z = a.w*b.z  + a.z*b.w;
        a.w = a.w*b.w  - a.z*b.z;
    }
    
    #if YQ_MATH_TENSOR_3_3_HPP
    template <typename T>
    requires std::is_floating_point_v<T>
    Spinor2<T>  spinor(const Tensor22<T>& t)
    {
        return Spinor2<T>(t);
    }
    #endif
    
}
