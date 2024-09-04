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

#include <0/math/vector/Quaternion3.hpp>
#include <yq/math/unit/literals.hpp>
#include <yq/math/trigonometry.hpp>

namespace yq {

    #ifdef YQ_MATH_TENSOR_3_3_HPP
    template <typename T>
        template <typename>
    requires std::is_floating_point_v<T>
    Quaternion3<T>::Quaternion3(const Tensor33<T>&t)
    {
        w	= T(0.5) * sqrt(std::max(zero_v<T>, one_v<T>+t.xx+t.yy+t.zz));
        x	= T(0.5) * sqrt(std::max(zero_v<T>, one_v<T>+t.xx-t.yy-t.zz));
        y	= T(0.5) * sqrt(std::max(zero_v<T>, one_v<T>-t.xx+t.yy-t.zz));
        z	= T(0.5) * sqrt(std::max(zero_v<T>, one_v<T>-t.xx-t.yy+t.zz));

        x	= copysign(x, t.zy-t.yz);
        y	= copysign(y, t.xz-t.zx);
        z	= copysign(z, t.yx-t.xy);
    }
    #endif

    template <typename T>
    template <typename>
    requires std::is_floating_point_v<T>
    Quaternion3<T>::Quaternion3(ccw_t, x_t, MKS<T,dim::Angle>v)
    {
        w   = cos(T(0.5)*v);
        x   = sin(T(0.5)*v);
        y   = zero_v<T>;
        z   = zero_v<T>;
    }
    
    template <typename T>
    template <typename>
    requires std::is_floating_point_v<T>
    Quaternion3<T>::Quaternion3(clockwise_t, x_t, MKS<T,dim::Angle>v) : Quaternion3(CCW,X,-v)
    {
    }
    
    template <typename T>
    template <typename>
    requires std::is_floating_point_v<T>
    Quaternion3<T>::Quaternion3(ccw_t, y_t, MKS<T,dim::Angle>v)
    {
        w   = cos(T(0.5)*v);
        x   = zero_v<T>;
        y   = sin(T(0.5)*v);
        z   = zero_v<T>;
    }

    template <typename T>
    template <typename>
    requires std::is_floating_point_v<T>
    Quaternion3<T>::Quaternion3(clockwise_t, y_t, MKS<T,dim::Angle>v) : Quaternion3(CCW,Y,-v)
    {
    }

    template <typename T>
    template <typename>
    requires std::is_floating_point_v<T>
    Quaternion3<T>::Quaternion3(ccw_t, z_t, MKS<T,dim::Angle>v)
    {
        w   = cos(T(0.5)*v);
        x   = zero_v<T>;
        y   = zero_v<T>;
        z   = sin(T(0.5)*v);
    }
    

    template <typename T>
    template <typename>
    requires std::is_floating_point_v<T>
    Quaternion3<T>::Quaternion3(clockwise_t, z_t, MKS<T,dim::Angle>v) : Quaternion3(CCW,Z,-v)
    {
    }

    #ifdef YQ_MATH_VECTOR_3_HPP
    template <typename T>
    template <typename>
    requires std::is_floating_point_v<T>
    Quaternion3<T>::Quaternion3(ccw_t, const Vector3<T>&a, MKS<T,dim::Angle>v)
    {
        if(a.length²() == (T) 0.){
            w   = (T) 1.;
            x   = (T) 0.;
            y   = (T) 0.;
            z   = (T) 0.;
        } else {
            w   = cos(T(0.5)*v);
            auto b = T(0.5) * ~a;
            x   = b.x;
            y   = b.y;
            z   = b.z;
        }
    }
    #endif

    #ifdef YQ_MATH_VECTOR_3_HPP
    template <typename T>
    template <typename>
    requires std::is_floating_point_v<T>
    Quaternion3<T>::Quaternion3(clockwise_t, const Vector3<T>&a, MKS<T,dim::Angle>v) : Quaternion3(CCW, a, -v) 
    {
    }
    #endif

    template <typename T>
    template <typename>
    requires std::is_floating_point_v<T>
    Quaternion3<T>::Quaternion3(hpr_t, MKS<T,dim::Angle> hdg_or_yaw, MKS<T,dim::Angle> pitch, MKS<T,dim::Angle> roll) :
        Quaternion3(Quaternion3(CCW, Z, roll)*Quaternion3(CCW, Y,pitch)*Quaternion3(CCW, X,hdg_or_yaw))
    {
    }
    
    #ifdef YQ_USE_GLM
    template <typename T>
    constexpr Quaternion3<T>::operator glm::qua<T,glm::defaultp>() const noexcept 
    {
        return glm::qua<T,glm::defaultp>(w,x,y,z);
    }
    #endif

    template <typename T>
    Quaternion3<T>      Quaternion3<T>::operator+() const
    {
        return *this;
    }
    
    template <typename T>
    Quaternion3<T>      Quaternion3<T>::operator-() const
    {
        return {-w, -x, -y, -z};
    }

    template <typename T>
    template <typename>
    requires std::is_floating_point_v<T>
    Quaternion3<T> Quaternion3<T>::operator~() const
    {
        T l = 1./length();
        return Quaternion3<T>(w*l, x*l, y*l, z*l);
    }

    template <typename T>
    constexpr square_t<T>  Quaternion3<T>::operator^(two_t) const noexcept
    {
        return length²();
    }

    template <typename T>
    constexpr Quaternion3<T>  Quaternion3<T>::operator+ (const Quaternion3<T>&b) const noexcept
    {
        return Quaternion3(w+b.w,x+b.x,y+b.y,z+b.z);
    }

    template <typename T>
    Quaternion3<T>& Quaternion3<T>::operator+=(const Quaternion3<T>&b) noexcept
    {
        w += b.w;
        x += b.x;
        y += b.y;
        z += b.z;
        return *this;
    }

    template <typename T>
    constexpr Quaternion3<T>  Quaternion3<T>::operator- (const Quaternion3<T>&b)  const noexcept
    {
        return Quaternion3(w-b.w,x-b.x,y-b.y,z-b.z);
    }

    template <typename T>
    Quaternion3<T>& Quaternion3<T>::operator-=(const Quaternion3<T>&b) noexcept
    {
        w -= b.w;
        x -= b.x;
        y -= b.y;
        z -= b.z;
        return *this;
    }

    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U>)
    constexpr Quaternion3<product_t<T,U>>  Quaternion3<T>::operator* (U b) const noexcept
    {
        return Quaternion3<product_t<T,U>>(w*b,x*b,y*b,z*b);
    }

    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
    Quaternion3<T>& Quaternion3<T>::operator*=(U b) noexcept
    {
        w *= b;
        x *= b;
        y *= b;
        z *= b;
        return *this;
    }


    template <typename T>
        template <typename U>
    constexpr Quaternion3<product_t<T,U>>  Quaternion3<T>::operator* (const Quaternion3<U>&b) const noexcept
    {
        return Quaternion3(
            w*b.w -x*b.x -y*b.y -z*b.z,
            w*b.x +x*b.w +y*b.z -z*b.y,
            w*b.y -x*b.z +y*b.w +z*b.x,
            w*b.z +x*b.y -y*b.x +z*b.w
        );
    }

    template <typename T>
        template <typename U>
    requires self_multiply_v<T,U>
    Quaternion3<T>& Quaternion3<T>::operator*=(const Quaternion3<U>&b) noexcept
    {
        if constexpr (std::is_floating_point_v<T>){
            post_mult(*this, b);
        } else {
            *this = *this * b;
        }
        return *this;
    }

    #ifdef YQ_MATH_VECTOR_3_HPP
    template <typename T>
        template <typename U>
    requires (std::is_floating_point_v<T> && std::is_floating_point_v<U>)
    constexpr Vector3<product_t<T,U>>   Quaternion3<T>::operator* (const Vector3<U>&b) const noexcept
    {
        // Quaternion3D Multiplication is Associative, i.e. Q1*Q2*Q3 == Q1*(Q2*Q3)
        // We're going to do the vecAsQuat * ~a portion first, removing the portions of the multiply
        // that would just equate to zero anyways

        // q will be the vector, represented as a quaternion, when multiplied with the conjugate of This
        Quaternion3<product_t<T,U>> q(
                                x*b.x +   y*b.y + z*b.z,   // w*b.w will always equal zero
                w*b.x   +                 y*b.z - z*b.y,   // x*b.w will always equal zero
                w*b.y   +                 z*b.x - x*b.z,   // y*b.w will always equal zero
                w*b.z   +                 x*b.y - y*b.x ); // z*b.w will always equal zero

        // Next part is the a * q

        // W will always be zero and since we return a Vec3D, we're not even using it -- don't need to calculate it
        // If we throw out the calculations for W, we wind up with this for the multiply
        return Vector3<product_t<T,U>>(
            w*q.x + x*q.w + y*q.z - z*q.y,
            w*q.y + y*q.w + z*q.x - x*q.z,
            w*q.z + z*q.w + x*q.y - y*q.x 
        );
    }
    #endif

    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<T>)
    constexpr Quaternion3<quotient_t<T,U>>  Quaternion3<T>::operator/ (U b) const noexcept
    {
        return {w/b,x/b,y/b,z/b};
    }

    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_divide_v<T,U>)
    Quaternion3<T>& Quaternion3<T>::operator/=(U b) noexcept
    {
        w /= b;
        x /= b;
        y /= b;
        z /= b;
        return *this;
    }

    #ifdef YQ_MATH_VECTOR_3_HPP
    template <typename T>
    Vector3<unity_t<T>>  Quaternion3<T>::axis() const
    {
        Vector3<T>  ret(x,y,z);
        square_t<T> l2  = ret.length2();
        if(l2 == zero_v<square_t<T>>)
            return Vector3<unity_t<T>>(Z);
        return ret / sqrt(l2);
    }
    #endif

    template <typename T>
    constexpr Quaternion3<T>    Quaternion3<T>::conj() const noexcept
    { 
        return Quaternion3(w,-x,-y,-z); 
    }

    template <typename T>
    constexpr Quaternion3<T>    Quaternion3<T>::conjugate() const noexcept
    {
        return conj();
    }

    template <typename T>
    constexpr Quaternion3<inverse_t<T>>   Quaternion3<T>::inverse() const noexcept
    {
        return conj() / length²();
    }

    template <typename T>
    constexpr square_t<T>    Quaternion3<T>::length²() const noexcept
    {
        return w*w+x*x+y*y+z*z;
    }
    
    template <typename T>
    T   Quaternion3<T>::length() const
    {
        if constexpr (has_sqrt_v<T>)
            return sqrt(length²());
        return {};
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    
    template <typename T, typename U>
    requires (is_arithmetic_v<T>)
    constexpr Quaternion3<product_t<T,U>>  operator*(T a, const Quaternion3<U>&b)
    {
        return {a*b.w,a*b.x,a*b.y,a*b.z};
    }

    template <typename T>
    constexpr Quaternion3<T> conjugate(const Quaternion3<T>&a)  
    { 
        return Quaternion3(a.w,-a.x,-a.y,-a.z); 
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    Quaternion3<T>  hpr(const MKS<T,dim::Angle>& hdg, const MKS<T,dim::Angle>& pitch, const MKS<T,dim::Angle>& roll)
    {
        return Quaternion3<T>(HPR, hdg, pitch, roll);
    }

    template <typename T>
    constexpr square_t<T>  length²(const Quaternion3<T>&a)
    {
        return a.length²();
    }

    template <typename T>
    constexpr T  length(const Quaternion3<T>&a) 
    {
        return a.length();
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    void    pre_mult(const Quaternion3<T>&a, Quaternion3<T>&b)
    {
        T W = b.w*a.w - b.x*a.x - b.y*a.y - b.z*a.z;
        T X = b.x*a.w + b.w*a.x + b.z*a.y - b.y*a.z;
        T Y = b.y*a.w + b.w*a.y + b.x*a.z - b.z*a.x;

        // We can get away with modifying one at the end here without putting it in a temporary variable
        b.z = b.z*a.w + b.w*a.z + b.y*a.x - b.x*a.y;

        b.y = Y;
        b.x = X;
        b.w = W;
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    void    post_mult(Quaternion3<T>&a, const Quaternion3<T>&b)
    {
        T W = a.w*b.w - a.x*b.x - a.y*b.y - a.z*b.z;
        T X = a.w*b.x + a.x*b.w + a.y*b.z - a.z*b.y;
        T Y = a.w*b.y + a.y*b.w + a.z*b.x - a.x*b.z;

        a.z = a.w*b.z + a.z*b.w + a.x*b.y - a.y*b.x;

        a.y = Y;
        a.x = X;
        a.w = W;
    }

    #if YQ_MATH_TENSOR_3_3_HPP
    template <typename T>
    requires std::is_floating_point_v<T>
    Quaternion3<T>  quaternion(const Tensor33<T>& t)
    {
        return Quaternion3<T>(t);
    }
    #endif
    
    template <typename T>
    Quaternion3<T>  rotor_x(MKS<T,dim::Angle> v)
    {
        return Quaternion3<T>(CCW, X, v);
    }

    template <typename T>
    Quaternion3<T>  rotor_y(MKS<T,dim::Angle> v)
    {
        return Quaternion3<T>(CCW, Y, v);
    }

    template <typename T>
    Quaternion3<T>  rotor_z(MKS<T,dim::Angle> v)
    {
        return Quaternion3<T>(CCW, Z, v);
    }


}
