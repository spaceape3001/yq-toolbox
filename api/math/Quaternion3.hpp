////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>
#include <math/Tensor33.hpp>

namespace yq {

    /*! \brief Quaternion (3D)
    */
    template <typename T>
    struct Quaternion3 {
        using component_type = T;

        T w, x, y, z;

        //! Equality operator (using default)
        constexpr bool operator==(const Quaternion3&) const noexcept = default;
    };

    YQ_IEEE754_1(Quaternion3)

//  --------------------------------------------------------
//  COMPOSITION

    YQ_NAN_1(Quaternion3, Vector4<T>{nan_v<T>, nan_v<T>, nan_v<T>, nan_v<T>})
    YQ_ZERO_1(Quaternion3, Vector4<T>{zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>})

    /*! \brief Creates a quaternion
    */
    template <typename T>
    constexpr Quaternion3<T> quaternion(T w, std::type_identity_t<T> x, std::type_identity_t<T> y, std::type_identity_t<T> z)
    {
        return {w,x,y,z};
    }

    template <typename T>
    Quaternion3<T>  rotor_x(MKS<T,dim::Angle> v)
    {
        return Quaternion3<T>(cos(0.5*v), sin(0.5*v), 0., 0.);
    }

    template <typename T>
    Quaternion3<T>  rotor_y(MKS<T,dim::Angle> v)
    {
        return Quaternion3<T>(cos(0.5*v), 0., sin(0.5*v), 0.);
    }

    template <typename T>
    Quaternion3<T>  rotor_z(MKS<T,dim::Angle> v)
    {
        return Quaternion3<T>(cos(0.5*v), 0., 0., sin(0.5*v));
    }

//  --------------------------------------------------------
//  GETTERS

//  --------------------------------------------------------
//  SETTERS


//  --------------------------------------------------------
//  BASIC FUNCTIONS

    template <typename T>
    constexpr Quaternion3<T> conjugate(const Quaternion3<T>&a)  
    { 
        return Quaternion3(a.w,-a.x,-a.y,-a.z); 
    }

    template <typename T>
    constexpr square_t<T>  length2(const Quaternion3<T>&a)
    {
        return a.w*a.w+a.x*a.x+a.y*a.y+a.z*a.z;
    }

    template <typename T>
    constexpr square_t<T>  operator^(const Quaternion3<T>&a, two_t)
    {
        return a.w*a.w+a.x*a.x+a.y*a.y+a.z*a.z;
    }

    template <typename T>
    requires trait::has_sqrt_v<T>
    constexpr T  length(const Quaternion3<T>&a) 
    {
        return sqrt(length2(a));
    }
    

    YQ_IS_NAN_1(Quaternion3, is_nan(v.x) || is_nan(v.y) || is_nan(v.z) || is_nan(v.w))
    YQ_IS_FINITE_1(Quaternion3, is_finite(v.x) && is_finite(v.y) && is_finite(v.z) && is_finite(v.w))
        

//  --------------------------------------------------------
//  POSITIVE

    template <typename T>
    constexpr const Quaternion3<T>&  operator+(const Quaternion3<T>& a) 
    { 
        return a; 
    }

//  --------------------------------------------------------
//  NEGATIVE

    template <typename T>
    constexpr Quaternion3<T> operator-(const Quaternion3<T>&a)  
    { 
        return {-a.w, -a.x, -a.y, -a.z};
    }


//  --------------------------------------------------------
//  NORMALIZATION

    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Quaternion3<T> operator~(const Quaternion3<T>& a)
    {
        T l = length(a);
        return {a.w/l, a.x/l, a.y/l, a.z/l};
    }


//  --------------------------------------------------------
//  ADDITION

    template <typename T>
    constexpr Quaternion3<T>  operator+ (const Quaternion3<T>&a, const Quaternion3<T>&b) 
    {
        return {a.w+b.w,a.x+b.x,a.y+b.y,a.z+b.z};
    }

    template <typename T>
    Quaternion3<T>& operator+=(Quaternion3<T>&a, const Quaternion3<T>&b)
    {
        a.w += b.w;
        a.x += b.x;
        a.y += b.y;
        a.z += b.z;
        return a;
    }

//  --------------------------------------------------------
//  SUBTRACTION

    template <typename T>
    constexpr Quaternion3<T>  operator- (const Quaternion3<T>&a, const Quaternion3<T>&b) 
    {
        return {a.w-b.w,a.x-b.x,a.y-b.y,a.z-b.z};
    }

    template <typename T>
    Quaternion3<T>& operator-=(Quaternion3<T>&a, const Quaternion3<T>&b)
    {
        a.w -= b.w;
        a.x -= b.x;
        a.y -= b.y;
        a.z -= b.z;
        return a;
    }

//  --------------------------------------------------------
//  MULTIPLICATION

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
    

    template <typename T, typename U>
    requires (std::is_arithmetic_v<T>)
    constexpr Quaternion3<product_t<T,U>>  operator*(T a, const Quaternion3<U>&b)
    {
        return {a*b.w,a*b.x,a*b.y,a*b.z};
    }

    template <typename T, typename U>
    requires (std::is_arithmetic_v<U>)
    constexpr Quaternion3<product_t<T,U>>  operator* (const Quaternion3<T>&a, U b) 
    {
        return {a.w*b,a.x*b,a.y*b,a.z*b};
    }


    template <typename T, typename U>
    constexpr Quaternion3<product_t<T,U>>  operator* (const Quaternion3<T>&a, const Quaternion3<U>&b) 
    {
        return {
            a.w*b.w -a.x*b.x -a.y*b.y -a.z*b.z,
            a.w*b.x +a.x*b.w +a.y*b.z -a.z*b.y,
            a.w*b.y -a.x*b.z +a.y*b.w +a.z*b.x,
            a.w*b.z +a.x*b.y -a.y*b.x +a.z*b.w
        };
    }


    template <typename T, typename U>
    requires (std::is_floating_point_v<T> && std::is_floating_point_v<U>)
    Vector3<product_t<T,U>>   operator* (const Quaternion3<T>& a, const Vector3<U>&b)
    {
        // Quaternion3D Multiplication is Associative, i.e. Q1*Q2*Q3 == Q1*(Q2*Q3)
        // We're going to do the vecAsQuat * ~a portion first, removing the portions of the multiply
        // that would just equate to zero anyways

        // q will be the vector, represented as a quaternion, when multiplied with the conjugate of This
        Quaternion3<product_t<T,U>> q(
                                a.x*b.x +   a.y*b.y + a.z*b.z,   // w*b.w will always equal zero
                a.w*b.x   +                 a.y*b.z - a.z*b.y,   // x*b.w will always equal zero
                a.w*b.y   +                 a.z*b.x - a.x*b.z,   // y*b.w will always equal zero
                a.w*b.z   +                 a.x*b.y - a.y*b.x ); // z*b.w will always equal zero

        // Next part is the a * q

        // W will always be zero and since we return a Vec3D, we're not even using it -- don't need to calculate it
        // If we throw out the calculations for W, we wind up with this for the multiply
        return {
            a.w*q.x + a.x*q.w + a.y*q.z - a.z*q.y,
            a.w*q.y + a.y*q.w + a.z*q.x - a.x*q.z,
            a.w*q.z + a.z*q.w + a.x*q.y - a.y*q.x 
        };
    }

    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Quaternion3<T>& operator*=(Quaternion3<T>&a, U b)
    {
        a.w *= b;
        a.x *= b;
        a.y *= b;
        a.z *= b;
        return a;
    }

    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Quaternion3<T>& operator*=(Quaternion3<T>&a, const Quaternion3<U>&b) 
    {
        post_mult(a, b);
        return a;
    }


//  --------------------------------------------------------
//  DIVISION

    template <typename T,typename U>
    requires (std::is_arithmetic_v<T>)
    constexpr Quaternion3<quotient_t<T,U>>  operator/ (const Quaternion3<T>&a, U b) 
    {
        return {a.w/b,a.x/b,a.y/b,a.z/b};
    }

    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Quaternion3<T>& operator/=(Quaternion3<T>&a, U b)
    {
        a.w /= b;
        a.x /= b;
        a.y /= b;
        a.z /= b;
        return a;
    }

//  --------------------------------------------------------
//  DOT PRODUCT


//  --------------------------------------------------------
//  INNER PRODUCT


//  --------------------------------------------------------
//  OUTER PRODUCT


///  --------------------------------------------------------
//  OTIMES PRODUCT

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

    template <typename T>
    requires std::is_floating_point_v<T>
    Quaternion3<T>  hpr(const MKS<T,dim::Angle>& hdg, const MKS<T,dim::Angle>& pitch, const MKS<T,dim::Angle>& roll)
    {
        return rotor_z(hdg) * rotor_y(pitch) * rotor_x(pitch);
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    Quaternion3<T>  quaternion(const Tensor33<T>& t)
    {
        Quaternion3<T>  ret;
        ret.w	= T(0.5) * sqrt(std::max(zero_v<T>, one_v<T>+t.xx+t.yy+t.zz));
        ret.x	= T(0.5) * sqrt(std::max(zero_v<T>, one_v<T>+t.xx-t.yy-t.zz));
        ret.y	= T(0.5) * sqrt(std::max(zero_v<T>, one_v<T>-t.xx+t.yy-t.zz));
        ret.z	= T(0.5) * sqrt(std::max(zero_v<T>, one_v<T>-t.xx-t.yy+t.zz));

        ret.x	= copysign(ret.x, t.zy-t.yz);
        ret.y	= copysign(ret.y, t.xz-t.zx);
        ret.z	= copysign(ret.z, t.yx-t.xy);
        return ret;
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    Tensor33<T>     tensor(const Quaternion3<T>& q)
    {
        return columns( q * Vector3<T>::unit_x(), q * Vector3<T>::unit_y(), q * Vector3<T>::unit_z());
    }

}


YQ_TYPE_DECLARE(yq::Quaternion3D)
YQ_TYPE_DECLARE(yq::Quaternion3F)
