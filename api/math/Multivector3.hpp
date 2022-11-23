////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>
#include <math/Vector3.hpp>
#include <math/Bivector3.hpp>
#include <math/Trivector3.hpp>

namespace yq {

    /*! \brief Three dimensional multivector
    */
    template <typename T>
    struct Multivector3 {
        unity_t<T>      a;
        T               x, y, z;
        square_t<T>     xy, yz, zx;
        cube_t<T>       xyz;
        
        constexpr bool operator==(const Multivector3&) const noexcept = default;
    };

    YQ_IEEE754_1(Multivector3)

//  --------------------------------------------------------
//  COMPOSITION

    YQ_NAN_1(Multivector3, Multivector3<T>{
        nan_v<unity_t<T>>, 
        nan_v<T>, nan_v<T>, nan_v<T>, 
        nan_v<square_t<T>>, nan_v<square_t<T>>, nan_v<square_t<T>>, 
        nan_v<cube_t<T>>
    })
    YQ_ZERO_1(Multivector3, Multivector3<T>{
        zero_v<unity_t<T>>, 
        zero_v<T>, zero_v<T>, zero_v<T>, 
        zero_v<square_t<T>>, zero_v<square_t<T>>, zero_v<square_t<T>>, 
        zero_v<cube_t<T>>
    })

//  --------------------------------------------------------
//  GETTERS

    template <typename T>
    constexpr Bivector3<T> bivector(const Multivector3<T>& a) noexcept
    {
        return { a.xy, a.yz, a.zx };
    }

    template <typename T>
    constexpr Trivector3<T> trivector(const Multivector3<T>& a) noexcept
    {
        return { a.xyz };
    }

    template <typename T>
    constexpr Vector3<T> vector(const Multivector3<T>& a) noexcept
    {
        return { a.x, a.y, a.z };
    }

//  --------------------------------------------------------
//  BASIC FUNCTIONS
    
    /*! \brief Checks for finiteness
    */
    template <typename T>
    constexpr bool is_finite(const Multivector3<T>&v)
    { 
        return
            is_finite(v.a) && 
            is_finite(v.x) && is_finite(v.y) && is_finite(v.z) && 
            is_finite(v.xy) && is_finite(v.yz) && is_finite(v.zx) && 
            is_finite(v.xyz)
        ;
    }

    YQ_IS_NAN_1(Multivector3, 
        is_nan(v.a) || 
        is_nan(v.x) || is_nan(v.y) || is_nan(v.z) || 
        is_nan(v.xy) || is_nan(v.yz) || is_nan(v.zx) || 
        is_nan(v.xyz)
    )


//  --------------------------------------------------------
//  POSITIVE

    template <typename T>
    constexpr Multivector3<T> operator+(const Multivector3<T>& a) noexcept
    {
        return a;
    }

//  --------------------------------------------------------
//  NEGATIVE

    template <typename T>
    constexpr Multivector3<T> operator-(const Multivector3<T>& a) noexcept
    {
        return {-a.a, -a.x, -a.y, -a.z, -a.xy, -a.yz, -a.zx, -a.xyz };
    }

//  --------------------------------------------------------
//  NORMALIZATION


//  --------------------------------------------------------
//  ADDITION

    template <typename T>
    constexpr Multivector3<T> operator+(const Bivector3<T>& a, const Multivector3<T>& b) noexcept
    {
        return { 
            b.a, 
            b.x, b.y, b.z,
            a.xy+b.xy, a.yz+b.yz, a.zx+b.zx,
            b.xyz
        };
    }

    template <typename T>
    constexpr Multivector3<T> operator+(const Bivector3<T>& a, const Trivector3<T>& b) noexcept
    {
        return { 
            {}, 
            {}, {}, {}, 
            a.xy, a.yz, a.zx, 
            b.xyz
        };
    }

    template <typename T>
    constexpr Multivector3<T> operator+(const Bivector3<T>& a, unity_t<T>  b) noexcept
    {
        return { 
            b, 
            {}, {}, {}, 
            a.xy, a.yz, a.zx, 
            {} 
        };
    }


    template <typename T>
    constexpr Multivector3<T> operator+(const Bivector3<T>& a, const Vector3<T>& b) noexcept
    {
        return { 
            {}, 
            b.x, b.y, b.z, 
            a.xy, a.yz, a.zx, 
            {} 
        };
    }


    template <typename T>
    constexpr Multivector3<T> operator+(const Multivector3<T>& a, const Bivector3<T>& b) noexcept
    {
        return {
            a.a,
            a.x, a.y, a.z, 
            a.xy+b.xy, a.yz+b.yz, a.zx+b.zx,
            a.xyz
        };
    }

    template <typename T>
    Multivector3<T>& operator+=(Multivector3<T>& a, const Bivector3<T>& b) noexcept
    {
        a.xy+=b.xy; a.yz+=b.yz; a.zx+=b.zx;
        return a;
    }

    template <typename T>
    constexpr Multivector3<T> operator+(const Multivector3<T>& a, const Multivector3<T>& b) noexcept
    {
        return {
            a.a+b.a,
            a.x+b.x, a.y+b.y, a.z+b.z,
            a.xy+b.xy, a.yz+b.yz, a.zx+b.zx,
            a.xyz+b.xyz
        };
    }

    template <typename T>
    Multivector3<T>& operator+=(Multivector3<T>& a, const Multivector3<T>& b) noexcept
    {
        a.a += b.a;
        a.x += b.x; a.y += b.y; a.z += b.z;
        a.xy+=b.xy; a.yz+=b.yz; a.zx+=b.zx;
        a.xyz += b.xyz;
        return a;
    }

    template <typename T>
    constexpr Multivector3<T> operator+(const Multivector3<T>& a, const Trivector3<T>& b) noexcept
    {
        return {
            a.a,
            a.x, a.y, a.z, 
            a.xy, a.yz, a.zx, 
            a.xyz+b.xyz
        };
    }

    template <typename T>
    Multivector3<T>& operator+=(Multivector3<T>& a, const Trivector3<T>& b) noexcept
    {
        a.xyz += b.xyz;
        return a;
    }
    
    template <typename T>
    constexpr Multivector3<T> operator+(const Multivector3<T>& a, unity_t<T>  b) noexcept
    {
        return {
            a.a+b,
            a.x, a.y, a.z,
            a.xy, a.yz, a.zx, 
            a.xyz
        };
    }

    template <typename T>
    Multivector3<T>& operator+=(Multivector3<T>& a, unity_t<T>  b) noexcept
    {
        a.a += b;
        return a;
    }

    template <typename T>
    constexpr Multivector3<T> operator+(const Multivector3<T>& a, const Vector3<T>&  b) noexcept
    {
        return {
            a.a,
            a.x+b.x, a.y+b.y, a.z+b.z,
            a.xy, a.yz, a.zx,
            a.xyz
        };
    }

    template <typename T>
    Multivector3<T>& operator+=(Multivector3<T>& a, const Vector3<T>& b) noexcept
    {
        a.x += b.x; a.y += b.y; a.z += b.z;
        return a;
    }

    
    template <typename T>
    constexpr Multivector3<T> operator+(Trivector3<T> a, const Bivector3<T>& b) noexcept
    {
        return { 
            {}, 
            {}, {}, {},
            b.xy, b.yz, b.zx,
            a.xyz 
        };
    }
    
    template <typename T>
    constexpr Multivector3<T> operator+(Trivector3<T> a, const Multivector3<T>& b) noexcept
    {
        return { 
            b.a, 
            b.x, b.y, b.z,
            b.xy, b.yz, b.zx,
            a.xyz + b.xyz
        };
    }
    
    
    template <typename T>
    constexpr Multivector3<T> operator+(Trivector3<T> a, unity_t<T>  b) noexcept
    {
        return { 
            b, 
            {}, {}, {}, 
            {}, {}, {}, 
            a.xyz 
        };
    }    
        
    template <typename T>
    constexpr Multivector3<T> operator+(Trivector3<T> a, const Vector3<T>&  b) noexcept
    {
        return { 
            {}, 
            b.x, b.y, b.z,
            {}, {}, {}, 
            a.xyz 
        };
    }
    
    template <typename T>
    constexpr Multivector3<T> operator+(unity_t<T> a, const Bivector3<T>& b) noexcept
    {
        return { 
            a, 
            {}, {}, {}, 
            b.xy, b.yz, b.zx, 
            {} 
        };
    }

    template <typename T>
    constexpr Multivector3<T> operator+(unity_t<T> a, const Multivector3<T>& b) noexcept
    {
        return { 
            a+b.a, 
            b.x, b.y, b.z,
            b.xy, b.yz, b.zx,
            b.xyz
        };
    }

    template <typename T>
    constexpr Multivector3<T> operator+(unity_t<T> a, const Trivector3<T>& b) noexcept
    {
        return { 
            a, 
            {}, {}, {}, 
            {}, {}, {}, 
            b.xyz
        };
    }

    template <typename T>
    constexpr Multivector3<T> operator+(unity_t<T> a, const Vector3<T>& b) noexcept
    {
        return { 
            a, 
            b.x, b.y, b.z, 
            {}, {}, {}, 
            {} 
        };
    }

    template <typename T>
    constexpr Multivector3<T> operator+(const Vector3<T>& a, const Bivector3<T>& b) noexcept
    {
        return { 
            {}, 
            a.x, a.y, a.z,
            b.xy, b.yz, b.zx,
            {} 
        };
    }

    template <typename T>
    constexpr Multivector3<T> operator+(const Vector3<T>& a, const Multivector3<T>& b) noexcept
    {
        return { 
            b.a, 
            a.x+b.x, a.y+b.y, a.z+b.z, 
            b.xy, b.yz, b.zx,
            b.xyz
        };
    }

    template <typename T>
    constexpr Multivector3<T> operator+(const Vector3<T>& a, const Trivector3<T>& b) noexcept
    {
        return { 
            {}, 
            a.x, a.y, a.z,
            {}, {}, {}, 
            b.xyz
        };
    }

    template <typename T>
    constexpr Multivector3<T> operator+(const Vector3<T>& a, unity_t<T>  b) noexcept
    {
        return { 
            b, 
            a.x, a.y, a.z,
            {}, {}, {}, 
            {} 
        };
    }
    
//  --------------------------------------------------------
//  SUBTRACTION

    template <typename T>
    constexpr Multivector3<T> operator-(const Bivector3<T>& a, const Multivector3<T>& b) noexcept
    {
        return { 
            -b.a, 
            -b.x, -b.y, -b.z,
            a.xy-b.xy, a.yz-b.yz, a.zx-b.zx,
            -b.xyz
        };
    }

    template <typename T>
    constexpr Multivector3<T> operator-(const Bivector3<T>& a, const Trivector3<T>& b) noexcept
    {
        return { 
            {}, 
            {}, {}, {}, 
            a.xy, a.yz, a.zx, 
            -b.xyz
        };
    }

    template <typename T>
    constexpr Multivector3<T> operator-(const Bivector3<T>& a, unity_t<T> b) noexcept
    {
        return { 
            -b, 
            {}, {}, {}, 
            a.xy, a.yz, a.zx, 
            {} 
        };
    }


    template <typename T>
    constexpr Multivector3<T> operator-(const Bivector3<T>& a, const Vector3<T>& b) noexcept
    {
        return { 
            {}, 
            -b.x, -b.y, -b.z, 
            a.xy, a.yz, a.zx, 
            {} 
        };
    }

    template <typename T>
    constexpr Multivector3<T> operator-(const Multivector3<T>& a, const Bivector3<T>& b) noexcept
    {
        return {
            a.a,
            a.x, a.y, a.z, 
            a.xy-b.xy, a.yz-b.yz, a.zx-b.zx,
            a.xyz
        };
    }

    template <typename T>
    Multivector3<T>& operator-=(Multivector3<T>& a, const Bivector3<T>& b) noexcept
    {
        a.xy-=b.xy; a.yz-=b.yz; a.zx-=b.zx;
        return a;
    }

    template <typename T>
    constexpr Multivector3<T> operator-(const Multivector3<T>& a, const Multivector3<T>& b) noexcept
    {
        return {
            a.a-b.a,
            a.x-b.x, a.y-b.y, a.z-b.z,
            a.xy-b.xy, a.yz-b.yz, a.zx-b.zx,
            a.xyz-b.xyz
        };
    }

    template <typename T>
    Multivector3<T>& operator-=(Multivector3<T>& a, const Multivector3<T>& b) noexcept
    {
        a.a -= b.a;
        a.x -= b.x; a.y -= b.y; a.z -= b.z;
        a.xy-=b.xy; a.yz-=b.yz; a.zx-=b.zx;
        a.xyz -= b.xyz;
        return a;
    }

    template <typename T>
    constexpr Multivector3<T> operator-(const Multivector3<T>& a, const Trivector3<T>& b) noexcept
    {
        return {
            a.a,
            a.x, a.y, a.z, 
            a.xy, a.yz, a.zx, 
            a.xyz-b.xyz
        };
    }

    template <typename T>
    Multivector3<T>& operator-=(Multivector3<T>& a, const Trivector3<T>& b) noexcept
    {
        a.xyz -= b.xyz;
        return a;
    }
    
    template <typename T>
    constexpr Multivector3<T> operator-(const Multivector3<T>& a, unity_t<T> b) noexcept
    {
        return {
            a.a-b,
            a.x, a.y, a.z,
            a.xy, a.yz, a.zx, 
            a.xyz
        };
    }

    template <typename T>
    Multivector3<T>& operator-=(Multivector3<T>& a, unity_t<T> b) noexcept
    {
        a.a -= b;
        return a;
    }

    template <typename T>
    constexpr Multivector3<T> operator-(const Multivector3<T>& a, const Vector3<T>& b) noexcept
    {
        return {
            a.a,
            a.x-b.x, a.y-b.y, a.z-b.z,
            a.xy, a.yz, a.zx,
            a.xyz
        };
    }

    template <typename T>
    Multivector3<T>& operator-=(Multivector3<T>& a, const Vector3<T>& b) noexcept
    {
        a.x -= b.x; a.y -= b.y; a.z -= b.z;
        return a;
    }
    

    template <typename T>
    constexpr Multivector3<T> operator-(Trivector3<T> a, const Bivector3<T>& b) noexcept
    {
        return { 
            {}, 
            {}, {}, {},
            -b.xy, -b.yz, -b.zx,
            a.xyz 
        };
    }
    
    template <typename T>
    constexpr Multivector3<T> operator-(Trivector3<T> a, const Multivector3<T>& b) noexcept
    {
        return { 
            -b.a, 
            -b.x, -b.y, -b.z,
            -b.xy, -b.yz, -b.zx,
            a.xyz - b.xyz
        };
    }
    

    template <typename T>
    constexpr Multivector3<T> operator-(Trivector3<T> a, unity_t<T> b) noexcept
    {
        return { 
            -b, 
            {}, {}, {}, 
            {}, {}, {}, 
            a.xyz 
        };
    }

    template <typename T>
    constexpr Multivector3<T> operator-(Trivector3<T> a, const Vector3<T>& b) noexcept
    {
        return { 
            {}, 
            -b.x, -b.y, -b.z,
            {}, {}, {}, 
            a.xyz 
        };
    }

    template <typename T>
    constexpr Multivector3<T> operator-(unity_t<T> a, const Bivector3<T>& b) noexcept
    {
        return { 
            a, 
            {}, {}, {}, 
            -b.xy, -b.yz, -b.zx, 
            {} 
        };
    }

    template <typename T>
    constexpr Multivector3<T> operator-(unity_t<T> a, const Multivector3<T>& b) noexcept
    {
        return { 
            a-b.a, 
            -b.x, -b.y, -b.z,
            -b.xy, -b.yz, -b.zx,
            -b.xyz
        };
    }

    template <typename T>
    constexpr Multivector3<T> operator-(unity_t<T> a, const Trivector3<T>& b) noexcept
    {
        return { 
            a, 
            {}, {}, {}, 
            {}, {}, {}, 
            -b.xyz
        };
    }

    template <typename T>
    constexpr Multivector3<T> operator-(unity_t<T> a, const Vector3<T>& b) noexcept
    {
        return { 
            a, 
            -b.x, -b.y, -b.z, 
            {}, {}, {}, 
            {} 
        };
    }

    template <typename T>
    constexpr Multivector3<T> operator-(const Vector3<T>& a, const Bivector3<T>& b) noexcept
    {
        return { 
            {}, 
            a.x, a.y, a.z,
            -b.xy, -b.yz, -b.zx,
            {} 
        };
    }

    template <typename T>
    constexpr Multivector3<T> operator-(const Vector3<T>& a, const Multivector3<T>& b) noexcept
    {
        return { 
            -b.a, 
            a.x-b.x, a.y-b.y, a.z-b.z, 
            -b.xy, -b.yz, -b.zx,
            -b.xyz
        };
    }

    template <typename T>
    constexpr Multivector3<T> operator-(const Vector3<T>& a, const Trivector3<T>& b) noexcept
    {
        return { 
            {}, 
            a.x, a.y, a.z,
            {}, {}, {}, 
            -b.xyz
        };
    }

    template <typename T>
    constexpr Multivector3<T> operator-(const Vector3<T>& a, unity_t<T> b) noexcept
    {
        return { 
            -b, 
            a.x, a.y, a.z,
            {}, {}, {}, 
            {} 
        };
    }
        
//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Multivector3<T> operator*(T a, const Multivector3<T>&b) noexcept
    {
        return { 
            a*b.a, 
            a*b.x, a*b.y, a*b.z,
            a*b.xy, a*b.yz, a*b.zx,
            a*b.xyz
        };
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Multivector3<T> operator*(const Multivector3<T>& a, T b) noexcept
    {
        return { 
            a.a*b, 
            a.x*b, a.y*b, a.z*b,
            a.xy*b, a.yz*b, a.zx*b,
            a.xyz*b
        };
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    Multivector3<T>& operator*=(Multivector3<T>& a, T b) noexcept
    {
        a.a  *=b; 
        a.x  *=b; a.y *=b; a.z *=b;
        a.xy *=b; a.yz*=b; a.zx*=b;
        a.xyz*=b;
        return a;
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Multivector3<T>   operator* (const Vector3<T>&a, const Vector3<T>&b) 
    {
        return {
            a.x*b.x+a.y*b.y+a.z*b.z, 
            0., 0., 0., 
            a.x*b.y-a.y*b.x, a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z,
            0.
        };
    }


//  --------------------------------------------------------
//  DIVISION

    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Multivector3<T> operator/(const Multivector3<T>& a, T b) noexcept
    {
        return { 
            a.a/b, 
            a.x/b, a.y/b, a.z/b,
            a.xy/b, a.yz/b, a.zx/b,
            a.xyz/b
        };
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    Multivector3<T>& operator/=(Multivector3<T>& a, T b) noexcept
    {
        a.a  /=b; 
        a.x  /=b; a.y /=b; a.z /=b;
        a.xy /=b; a.yz/=b; a.zx/=b;
        a.xyz/=b;
        return a;
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Multivector3<T>   operator/ (const Vector3<T>&a, const Vector3<T>&b) 
    {
        return (a * b) / length2(b);
    }

//  --------------------------------------------------------
//  POWERS

//  --------------------------------------------------------
//  DOT PRODUCT


//  --------------------------------------------------------
//  INNER PRODUCT


//  --------------------------------------------------------
//  OUTER PRODUCT


//  --------------------------------------------------------
//  CROSS PRODUCT


///  --------------------------------------------------------
//  OTIMES PRODUCT

//  --------------------------------------------------------
//  UNIONS

//  --------------------------------------------------------
//  INTERSECTIONS


//  --------------------------------------------------------
//  PROJECTIONS

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS


}

YQ_TYPE_DECLARE(Multivector3D)
YQ_TYPE_DECLARE(Multivector3F)
