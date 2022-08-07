////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>
#include <math/Vector4.hpp>
#include <math/Bivector4.hpp>
#include <math/Trivector4.hpp>
#include <math/Quadvector4.hpp>

namespace yq {

    /*! \brief Four dimensional multivector
    */
    template <typename T>
    struct Multivector4 {
        unity_t<T>      a;
        T               x, y, z, w;
        square_t<T>     xy, yz, zw, wx, xz, yw;
        cube_t<T>       xyz, yzw, zwx, wxy;
        fourth_t<T>     xyzw;
        
        constexpr bool operator==(const Multivector4&) const noexcept = default;
    };

    YQ_IEEE754_1(Multivector4)

//  --------------------------------------------------------
//  COMPOSITION

    YQ_NAN_1(Multivector4, Multivector4<T>{
        nan_v<unity_t<T>>, 
        nan_v<T>, nan_v<T>, nan_v<T>, nan_v<T>, 
        nan_v<square_t<T>>, nan_v<square_t<T>>, nan_v<square_t<T>>, nan_v<square_t<T>>, nan_v<square_t<T>>, nan_v<square_t<T>>, 
        nan_v<cube_t<T>>, nan_v<cube_t<T>>, nan_v<cube_t<T>>, nan_v<cube_t<T>>,
        nan_v<fourth_t<T>>
    })
    YQ_ZERO_1(Multivector4, Multivector4<T>{
        zero_v<unity_t<T>>, 
        zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
        zero_v<square_t<T>>, zero_v<square_t<T>>, zero_v<square_t<T>>, zero_v<square_t<T>>, zero_v<square_t<T>>, zero_v<square_t<T>>, 
        zero_v<cube_t<T>>, zero_v<cube_t<T>>, zero_v<cube_t<T>>, zero_v<cube_t<T>>,
        zero_v<fourth_t<T>>
    })

//  --------------------------------------------------------
//  GETTERS

    template <typename T>
    constexpr Bivector4<T> bivector(const Multivector4<T>& a) noexcept
    {
        return { a.xy, a.yz, a.zw, a.wx, a.xz, a.yw };
    }

    template <typename T>
    constexpr Quadvector4<T> quadvector(const Multivector4<T>& a) noexcept
    {
        return { a.xyzw };
    }


    template <typename T>
    constexpr Trivector4<T> trivector(const Multivector4<T>& a) noexcept
    {
        return { a.xyz, a.yzw, a.zwx, a.wxy };
    }

    template <typename T>
    constexpr Vector4<T> vector(const Multivector4<T>& a) noexcept
    {
        return { a.x, a.y, a.z, a.w };
    }


//  --------------------------------------------------------
//  BASIC FUNCTIONS
    
    YQ_IS_NAN_1(Multivector4, 
        is_nan(v.a) || 
        is_nan(v.x) || is_nan(v.y) || is_nan(v.z) || is_nan(v.w) ||
        is_nan(v.xy) || is_nan(v.yz) || is_nan(v.zw) || is_nan(v.wx) || is_nan(v.xz) || is_nan(v.yw) ||
        is_nan(v.xyz) || is_nan(v.yzw) || is_nan(v.zwx) || is_nan(v.wxy) ||
        is_nan(v.xyzw)
    )
    YQ_IS_FINITE_1(Multivector4, 
        is_finite(v.a) && 
        is_finite(v.x) && is_finite(v.y) && is_finite(v.z) && is_finite(v.w) &&
        is_finite(v.xy) && is_finite(v.yz) && is_finite(v.zw) && is_finite(v.wx) && is_finite(v.xz) && is_finite(v.yw) &&
        is_finite(v.xyz) && is_finite(v.yzw) && is_finite(v.zwx) && is_finite(v.wxy) &&
        is_finite(v.xyzw)
    )


//  --------------------------------------------------------
//  POSITIVE

    template <typename T>
    constexpr Multivector4<T> operator+(const Multivector4<T>& a) noexcept
    {
        return a;
    }

//  --------------------------------------------------------
//  NEGATIVE

    template <typename T>
    constexpr Multivector4<T> operator-(const Multivector4<T>& a) noexcept
    {
        return {
            -a.a, 
            -a.x, -a.y, -a.z, -a.w,
            -a.xy, -a.yz, -a.zw, -a.wx, -a.xz, -a.yw,
            -a.xyz, -a.yzw, -a.zwx, -a.wxy, 
            -a.xyzw
        };
    }

//  --------------------------------------------------------
//  NORMALIZATION


//  --------------------------------------------------------
//  ADDITION

    template <typename T>
    constexpr Multivector4<T> operator+(const Bivector4<T>& a, const Multivector4<T>& b) noexcept
    {
        return { 
            b.a,
            b.x, b.y, b.z, b.w,
            a.xy+b.xy, a.yz+b.yz, a.zw+b.zw, a.wx+b.wx, a.xz+b.xz, a.yw+b.yw,
            b.xyz, b.yzw, b.zwx, b.wxy,
            b.xyzw
        
        };
    }

    template <typename T>
    constexpr Multivector4<T> operator+(const Bivector4<T>& a, const Quadvector4<T>& b) noexcept
    {
        return { 
            {}, 
            {}, {}, {}, {}, 
            a.xy, a.yz, a.zw, a.wx, a.xz, a.yw, 
            {}, {}, {}, {}, 
            b.xyzw
        };
    }


    template <typename T>
    constexpr Multivector4<T> operator+(const Bivector4<T>& a, const Trivector4<T>& b) noexcept
    {
        return { 
            {}, 
            {}, {}, {}, {}, 
            a.xy, a.yz, a.zw, a.wx, a.xz, a.yw, 
            b.xyz, b.yzw, b.zwx, b.wxy,
            {} 
        };
    }

    template <typename T>
    constexpr Multivector4<T> operator+(const Bivector4<T>& a, unity_t<T>  b) noexcept
    {
        return { 
            b, 
            {}, {}, {}, {}, 
            a.xy, a.yz, a.zw, a.wx, a.xz, a.yw, 
            {}, {}, {}, {}, 
            {} 
        };
    }


    template <typename T>
    constexpr Multivector4<T> operator+(const Bivector4<T>& a, const Vector4<T>& b) noexcept
    {
        return { 
            {}, 
            b.x, b.y, b.z, b.w,
            a.xy, a.yz, a.zw, a.wx, a.xz, a.yw, 
            {}, {}, {}, {}, 
            {} 
        };
    }


    template <typename T>
    constexpr Multivector4<T> operator+(const Multivector4<T>& a, const Bivector4<T>& b) noexcept
    {
        return {
            a.a,
            a.x, a.y, a.z, a.w, 
            a.xy+b.xy, a.yz+b.yz, a.zw+b.zw, a.wx+b.wx, a.xz+b.xz, a.yw+b.yw,
            a.xyz, a.yzw, a.zwx, a.wxy, 
            a.xyzw
        };
    }

    template <typename T>
    Multivector4<T>& operator+=(Multivector4<T>& a, const Bivector4<T>& b) noexcept
    {
        a.xy+=b.xy; a.yz+=b.yz; a.zw+=b.zw; a.wx+=b.wx; a.xz+=b.xz; a.yw+=b.yw;
        return a;
    }
    
    template <typename T>
    constexpr Multivector4<T> operator+(const Multivector4<T>& a, const Multivector4<T>&  b) noexcept
    {
        return {
            a.a+b.a,
            a.x+b.x, a.y+b.y, a.z+b.z, a.w+b.w,
            a.xy+b.xy, a.yz+b.yz, a.zw+b.zw, a.wx+b.wx, a.xz+b.xz, a.yw+b.yw,
            a.xyz+b.xyz, a.yzw+b.yzw, a.zwx+b.zwx, a.wxy+b.wxy,
            a.xyzw+b.xyzw
        };
    }

    template <typename T>
    Multivector4<T>& operator+=(Multivector4<T>& a, const Multivector4<T>& b) noexcept
    {
        a.a += b.a;
        a.x += b.x; a.y += b.y; a.z += b.z; a.w += b.w;
        a.xy += b.xy; a.yz += b.yz; a.zw += b.zw; a.wx += b.wx; a.xz += b.xz; a.yw += b.yw;
        a.xyz += b.xyz; a.yzw += b.yzw; a.zwx += b.zwx; a.wxy += b.wxy;
        a.xyzw += b.xyzw;
        return a;
    }

    template <typename T>
    constexpr Multivector4<T> operator+(const Multivector4<T>& a, const Quadvector4<T>& b) noexcept
    {
        return {
            a.a,
            a.x, a.y, a.z, a.w, 
            a.xy, a.yz, a.zw, a.wx, a.xz, a.yw, 
            a.xyz, a.yzw, a.zwx, a.wxy, 
            a.xyzw+b.xyzw
        };
    }

    template <typename T>
    Multivector4<T>& operator+=(Multivector4<T>& a, const Quadvector4<T>& b) noexcept
    {
        a.xyzw += b.xyzw;
        return a;
    }
    
    template <typename T>
    constexpr Multivector4<T> operator+(const Multivector4<T>& a, const Trivector4<T>& b) noexcept
    {
        return {
            a.a,
            a.x, a.y, a.z, a.w, 
            a.xy, a.yz, a.zw, a.wx, a.xz, a.yw, 
            a.xyz+b.xyz, a.yzw+b.yzw, a.zwx+b.zwx, a.wxy+b.wxy,
            a.xyzw
        };
    }

    template <typename T>
    Multivector4<T>& operator+=(Multivector4<T>& a, const Trivector4<T>& b) noexcept
    {
        a.xyz+=b.xyz; a.yzw+=b.yzw; a.zwx+=b.zwx; a.wxy+=b.wxy;
        return a;
    }
    
    
    template <typename T>
    constexpr Multivector4<T> operator+(const Multivector4<T>& a, unity_t<T>  b) noexcept
    {
        return {
            a.a+b,
            a.x, a.y, a.z, a.w,
            a.xy, a.yz, a.zw, a.wx, a.xz, a.yw, 
            a.xyz, a.yzw, a.zwx, a.wxy, 
            a.xyzw
        };
    }

    template <typename T>
    Multivector4<T>& operator+=(Multivector4<T>& a, unity_t<T>  b) noexcept
    {
        a.a += b;
        return a;
    }


    template <typename T>
    constexpr Multivector4<T> operator+(const Multivector4<T>& a, const Vector4<T>&  b) noexcept
    {
        return {
            a.a,
            a.x+b.x, a.y+b.y, a.z+b.z, a.w+b.w,
            a.xy, a.yz, a.zw, a.wx, a.xz, a.yw, 
            a.xyz, a.yzw, a.zwx, a.wxy, 
            a.xyzw
        };
    }

    template <typename T>
    Multivector4<T>& operator+=(Multivector4<T>& a, const Vector4<T>& b) noexcept
    {
        a.x += b.x; a.y += b.y; a.z += b.z; a.w += b.w;
        return a;
    }

    template <typename T>
    constexpr Multivector4<T> operator+(Quadvector4<T> a, const Bivector4<T>& b) noexcept
    {
        return { 
            {}, 
            {}, {}, {}, {}, 
            b.xy, b.yz, b.zw, b.wx, b.xz, b.yw,
            {}, {}, {}, {}, 
            a.xyza 
        };
    }
    
    template <typename T>
    constexpr Multivector4<T> operator+(Quadvector4<T> a, const Multivector4<T>& b) noexcept
    {
        return {
            b.a, 
            b.x, b.y, b.z, b.w, 
            b.xy, b.yz, b.zw, b.wx, b.xz, b.yw,
            b.xyz, b.yzw, b.zwx, b.wxy,
            a.xyzw + b.xyzw
        };
    }

    template <typename T>
    constexpr Multivector4<T> operator+(Quadvector4<T> a, const Trivector4<T>& b) noexcept
    {
        return { 
            {}, 
            {}, {}, {}, {}, 
            {}, {}, {}, {}, {}, {}, 
            b.xyz, b.yzw, b.zwx, b.wxy, 
            a.xyzw 
        };
    }

    template <typename T>
    constexpr Multivector4<T> operator+(Quadvector4<T> a, unity_t<T>  b) noexcept
    {
        return { 
            b, 
            {}, {}, {}, {}, 
            {}, {}, {}, {}, {}, {}, 
            {}, {}, {}, {}, 
            a.xyzw 
        };
    }
    
    template <typename T>
    constexpr Multivector4<T> operator+(Quadvector4<T> a, const Vector4<T>& b) noexcept
    {
        return { 
            {}, 
            b.x, b.y, b.z, b.w, 
            {}, {}, {}, {}, {}, {}, 
            {}, {}, {}, {}, 
            a.xyzw 
        };
    }

    template <typename T>
    constexpr Multivector4<T> operator+(const Trivector4<T>& a, const Bivector4<T>& b) noexcept
    {
        return { 
            {}, 
            {}, {}, {}, {}, 
            b.xy, b.yz, b.zw, b.wx, b.xz, b.yw,
            a.xyz, a.yzw, a.zwx, a.wxy, 
            {} 
        };
    }

    template <typename T>
    constexpr Multivector4<T> operator+(const Trivector4<T>& a, const Multivector4<T>& b) noexcept
    {
        return { 
            b.a, 
            b.x, b.y, b.z, b.w, 
            b.xy, b.yz, b.zw, b.wx, b.xz, b.yw,
            a.xyz+b.xyz, a.yzw+b.yzw, a.zwx+b.zwx, a.wxy+b.wxy,
            b.xyzw
        };
    }

    template <typename T>
    constexpr Multivector4<T> operator+(const Trivector4<T>& a, const Quadvector4<T>& b) noexcept
    {
        return { 
            {}, 
            {}, {}, {}, {}, 
            {}, {}, {}, {}, {}, {}, 
            a.xyz, a.yzw, a.zwx, a.wxy, 
            b.xyzw 
        };
    }

    template <typename T>
    constexpr Multivector4<T> operator+(const Trivector4<T>& a, unity_t<T>  b) noexcept
    {
        return { 
            b, 
            {}, {}, {}, {}, 
            {}, {}, {}, {}, {}, {}, 
            a.xyz, a.yzw, a.zwx, a.wxy, 
            {} 
        };
    }
        

    template <typename T>
    constexpr Multivector4<T> operator+(const Trivector4<T>& a, const Vector4<T>& b) noexcept
    {
        return { 
            {}, 
            b.x, b.y, b.z, b.w, 
            {}, {}, {}, {}, {}, {}, 
            a.xyz, a.yzw, a.zwx, a.wxy, 
            {} 
        };
    }

    template <typename T>
    constexpr Multivector4<T> operator+(unity_t<T> a, const Bivector4<T>& b) noexcept
    {
        return { 
            a, 
            {}, {}, {}, {}, 
            b.xy, b.yz, b.zw, b.wx, b.xz, b.yw, 
            {}, {}, {}, {}, 
            {} 
        };
    }


    template <typename T>
    constexpr Multivector4<T> operator+(unity_t<T> a, const Multivector4<T>& b) noexcept
    {
        return { 
            a+b.a, 
            b.x, b.y, b.z, b.w,
            b.xy, b.yz, b.zw, b.wx, b.xz, b.yw,
            b.xyz, b.yzw, b.zwx, b.wxy,
            b.xyzw
        };
    }


    template <typename T>
    constexpr Multivector4<T> operator+(unity_t<T> a, const Quadvector4<T>& b) noexcept
    {
        return { 
            a,
            {}, {}, {}, {}, 
            {}, {}, {}, {}, {}, {}, 
            {}, {}, {}, {}, 
            b.xyzw 
        };
    }

    template <typename T>
    constexpr Multivector4<T> operator+(unity_t<T> a, const Trivector4<T>& b) noexcept
    {
        return { 
            a, 
            {}, {}, {}, {}, 
            {}, {}, {}, {}, {}, {}, 
            b.xyz, b.yzw, b.zwx, b.wxy, 
            {} 
        };
    }


    template <typename T>
    constexpr Multivector4<T> operator+(unity_t<T> a, const Vector4<T>& b) noexcept
    {
        return { 
            a, 
            b.x, b.y, b.z, b.w, 
            {}, {}, {}, {}, {}, {}, 
            {}, {}, {}, {}, 
            {} 
        };
    }

    template <typename T>
    constexpr Multivector4<T> operator+(const Vector4<T>& a, const Bivector4<T>& b) noexcept
    {
        return { 
            {}, 
            a.x, a.y, a.z, a.w, 
            b.xy, b.yz, b.zw, b.wx, b.xz, b.yw,
            {}, {}, {}, {}, 
            {} 
        };
    }

    template <typename T>
    constexpr Multivector4<T> operator+(const Vector4<T>& a, const Multivector4<T>& b) noexcept
    {
        return { 
            b.a, 
            a.x+b.x, a.y+b.y, a.z+b.z, a.w+b.w, 
            b.xy, b.yz, b.zw, b.wx, b.xz, b.yw,
            b.xyz, b.yzw, b.zwx, b.wxy,
            b.xyzw
        };
    }

    template <typename T>
    constexpr Multivector4<T> operator+(const Vector4<T>& a, const Quadvector4<T>& b) noexcept
    {
        return { 
            {}, 
            a.x, a.y, a.z, a.w, 
            {}, {}, {}, {}, {}, {}, 
            {}, {}, {}, {}, 
            b.xyzw
        };
    }

    template <typename T>
    constexpr Multivector4<T> operator+(const Vector4<T>& a, const Trivector4<T>& b) noexcept
    {
        return { 
            {}, 
            a.x, a.y, a.z, a.w, 
            {}, {}, {}, {}, {}, {}, 
            b.xyz, b.yzw, b.zwx, b.wxy,
            {} 
        };
    }    

    template <typename T>
    constexpr Multivector4<T> operator+(const Vector4<T>& a, unity_t<T>  b) noexcept
    {
        return { 
            b, 
            a.x, a.y, a.z, a.w, 
            {}, {}, {}, {}, {}, {}, 
            {}, {}, {}, {}, 
            {} 
        };
    }


//  --------------------------------------------------------
//  SUBTRACTION

    template <typename T>
    constexpr Multivector4<T> operator-(const Bivector4<T>& a, const Multivector4<T>& b) noexcept
    {
        return { 
            -b.a,
            -b.x, -b.y, -b.z, -b.w,
            a.xy-b.xy, a.yz-b.yz, a.zw-b.zw, a.wx-b.wx, a.xz-b.xz, a.yw-b.yw,
            -b.xyz, -b.yzw, -b.zwx, -b.wxy,
            -b.xyzw
        
        };
    }

    template <typename T>
    constexpr Multivector4<T> operator-(const Bivector4<T>& a, const Quadvector4<T>& b) noexcept
    {
        return { 
            {}, 
            {}, {}, {}, {}, 
            a.xy, a.yz, a.zw, a.wx, a.xz, a.yw, 
            {}, {}, {}, {}, 
            -b.xyzw
        };
    }


    template <typename T>
    constexpr Multivector4<T> operator-(const Bivector4<T>& a, const Trivector4<T>& b) noexcept
    {
        return { 
            {}, 
            {}, {}, {}, {}, 
            a.xy, a.yz, a.zw, a.wx, a.xz, a.yw, 
            -b.xyz, -b.yzw, -b.zwx, -b.wxy,
            {} 
        };
    }

    template <typename T>
    constexpr Multivector4<T> operator-(const Bivector4<T>& a, unity_t<T> b) noexcept
    {
        return { 
            -b, 
            {}, {}, {}, {}, 
            a.xy, a.yz, a.zw, a.wx, a.xz, a.yw, 
            {}, {}, {}, {}, 
            {} 
        };
    }


    template <typename T>
    constexpr Multivector4<T> operator-(const Bivector4<T>& a, const Vector4<T>& b) noexcept
    {
        return { 
            {}, 
            -b.x, -b.y, -b.z, -b.w,
            a.xy, a.yz, a.zw, a.wx, a.xz, a.yw, 
            {}, {}, {}, {}, 
            {} 
        };
    }


    template <typename T>
    constexpr Multivector4<T> operator-(const Multivector4<T>& a, const Bivector4<T>& b) noexcept
    {
        return {
            a.a,
            a.x, a.y, a.z, a.w, 
            a.xy-b.xy, a.yz-b.yz, a.zw-b.zw, a.wx-b.wx, a.xz-b.xz, a.yw-b.yw,
            a.xyz, a.yzw, a.zwx, a.wxy, 
            a.xyzw
        };
    }

    template <typename T>
    Multivector4<T>& operator-=(Multivector4<T>& a, const Bivector4<T>& b) noexcept
    {
        a.xy-=b.xy; a.yz-=b.yz; a.zw-=b.zw; a.wx-=b.wx; a.xz-=b.xz; a.yw-=b.yw;
        return a;
    }
    
    template <typename T>
    constexpr Multivector4<T> operator-(const Multivector4<T>& a, const Multivector4<T>& b) noexcept
    {
        return {
            a.a-b.a,
            a.x-b.x, a.y-b.y, a.z-b.z, a.w-b.w,
            a.xy-b.xy, a.yz-b.yz, a.zw-b.zw, a.wx-b.wx, a.xz-b.xz, a.yw-b.yw,
            a.xyz-b.xyz, a.yzw-b.yzw, a.zwx-b.zwx, a.wxy-b.wxy,
            a.xyzw-b.xyzw
        };
    }

    template <typename T>
    Multivector4<T>& operator-=(Multivector4<T>& a, const Multivector4<T>& b) noexcept
    {
        a.a -= b.a;
        a.x -= b.x; a.y -= b.y; a.z -= b.z; a.w -= b.w;
        a.xy -= b.xy; a.yz -= b.yz; a.zw -= b.zw; a.wx -= b.wx; a.xz -= b.xz; a.yw -= b.yw;
        a.xyz -= b.xyz; a.yzw -= b.yzw; a.zwx -= b.zwx; a.wxy -= b.wxy;
        a.xyzw -= b.xyzw;
        return a;
    }

    template <typename T>
    constexpr Multivector4<T> operator-(const Multivector4<T>& a, const Quadvector4<T>& b) noexcept
    {
        return {
            a.a,
            a.x, a.y, a.z, a.w, 
            a.xy, a.yz, a.zw, a.wx, a.xz, a.yw, 
            a.xyz, a.yzw, a.zwx, a.wxy, 
            a.xyzw-b.xyzw
        };
    }

    template <typename T>
    Multivector4<T>& operator-=(Multivector4<T>& a, const Quadvector4<T>& b) noexcept
    {
        a.xyzw -= b.xyzw;
        return a;
    }
    
    template <typename T>
    constexpr Multivector4<T> operator-(const Multivector4<T>& a, const Trivector4<T>& b) noexcept
    {
        return {
            a.a,
            a.x, a.y, a.z, a.w, 
            a.xy, a.yz, a.zw, a.wx, a.xz, a.yw, 
            a.xyz-b.xyz, a.yzw-b.yzw, a.zwx-b.zwx, a.wxy-b.wxy,
            a.xyzw
        };
    }

    template <typename T>
    Multivector4<T>& operator-=(Multivector4<T>& a, const Trivector4<T>& b) noexcept
    {
        a.xyz-=b.xyz; a.yzw-=b.yzw; a.zwx-=b.zwx; a.wxy-=b.wxy;
        return a;
    }
    
    
    template <typename T>
    constexpr Multivector4<T> operator-(const Multivector4<T>& a, unity_t<T> b) noexcept
    {
        return {
            a.a-b,
            a.x, a.y, a.z, a.w,
            a.xy, a.yz, a.zw, a.wx, a.xz, a.yw, 
            a.xyz, a.yzw, a.zwx, a.wxy, 
            a.xyzw
        };
    }

    template <typename T>
    Multivector4<T>& operator-=(Multivector4<T>& a, unity_t<T> b) noexcept
    {
        a.a -= b;
        return a;
    }


    template <typename T>
    constexpr Multivector4<T> operator-(const Multivector4<T>& a, const Vector4<T>& b) noexcept
    {
        return {
            a.a,
            a.x-b.x, a.y-b.y, a.z-b.z, a.w-b.w,
            a.xy, a.yz, a.zw, a.wx, a.xz, a.yw, 
            a.xyz, a.yzw, a.zwx, a.wxy, 
            a.xyzw
        };
    }

    template <typename T>
    Multivector4<T>& operator-=(Multivector4<T>& a, const Vector4<T>& b) noexcept
    {
        a.x -= b.x; a.y -= b.y; a.z -= b.z; a.w -= b.w;
        return a;
    }


    template <typename T>
    constexpr Multivector4<T> operator-(Quadvector4<T> a, const Bivector4<T>& b) noexcept
    {
        return { 
            {}, 
            {}, {}, {}, {}, 
            -b.xy, -b.yz, -b.zw, -b.wx, -b.xz, -b.yw,
            {}, {}, {}, {}, 
            a 
        };
    }
    
    template <typename T>
    constexpr Multivector4<T> operator-(Quadvector4<T> a, const Multivector4<T>& b) noexcept
    {
        return {
            -b.a, 
            -b.x, -b.y, -b.z, -b.w, 
            -b.xy, -b.yz, -b.zw, -b.wx, -b.xz, -b.yw,
            -b.xyz, -b.yzw, -b.zwx, -b.wxy,
            a.xyzw -b.xyzw
        };
    }

    template <typename T>
    constexpr Multivector4<T> operator-(Quadvector4<T> a, const Trivector4<T>& b) noexcept
    {
        return { 
            {}, 
            {}, {}, {}, {}, 
            {}, {}, {}, {}, {}, {}, 
            -b.xyz, -b.yzw, -b.zwx, -b.wxy, 
            a 
        };
    }

    template <typename T>
    constexpr Multivector4<T> operator-(Quadvector4<T> a, unity_t<T> b) noexcept
    {
        return { 
            -b, 
            {}, {}, {}, {}, 
            {}, {}, {}, {}, {}, {}, 
            {}, {}, {}, {}, 
            a 
        };
    }

    template <typename T>
    constexpr Multivector4<T> operator-(Quadvector4<T> a, const Vector4<T>& b) noexcept
    {
        return { 
            {}, 
            -b.x, -b.y, -b.z, -b.w, 
            {}, {}, {}, {}, {}, {}, 
            {}, {}, {}, {}, 
            a 
        };
    }

    
    template <typename T>
    constexpr Multivector4<T> operator-(const Trivector4<T>& a, const Bivector4<T>& b) noexcept
    {
        return { 
            {}, 
            {}, {}, {}, {}, 
            -b.xy, -b.yz, -b.zw, -b.wx, -b.xz, -b.yw,
            a.xyz, a.yzw, a.zwx, a.wxy, 
            {} 
        };
    }

    template <typename T>
    constexpr Multivector4<T> operator-(const Trivector4<T>& a, const Multivector4<T>& b) noexcept
    {
        return { 
            -b.a, 
            -b.x, -b.y, -b.z, -b.w, 
            -b.xy, -b.yz, -b.zw, -b.wx, -b.xz, -b.yw,
            a.xyz-b.xyz, a.yzw-b.yzw, a.zwx-b.zwx, a.wxy-b.wxy,
            -b.xyzw
        };
    }

    template <typename T>
    constexpr Multivector4<T> operator-(const Trivector4<T>& a, const Quadvector4<T>& b) noexcept
    {
        return { 
            {}, 
            {}, {}, {}, {}, 
            {}, {}, {}, {}, {}, {}, 
            a.xyz, a.yzw, a.zwx, a.wxy, 
            -b.xyzw 
        };
    }
    


    template <typename T>
    constexpr Multivector4<T> operator-(const Trivector4<T>& a, unity_t<T> b) noexcept
    {
        return { 
            -b, 
            {}, {}, {}, {}, 
            {}, {}, {}, {}, {}, {}, 
            a.xyz, a.yzw, a.zwx, a.wxy, 
            {} 
        };
    }
        
    template <typename T>
    constexpr Multivector4<T> operator-(const Trivector4<T>& a, const Vector4<T>& b) noexcept
    {
        return { 
            {}, 
            -b.x, -b.y, -b.z, -b.w, 
            {}, {}, {}, {}, {}, {}, 
            a.xyz, a.yzw, a.zwx, a.wxy, 
            {} 
        };
    }



    template <typename T>
    constexpr Multivector4<T> operator-(unity_t<T> a, const Bivector4<T>& b) noexcept
    {
        return { 
            a, 
            {}, {}, {}, {}, 
            -b.xy, -b.yz, -b.zw, -b.wx, -b.xz, -b.yw, 
            {}, {}, {}, {}, 
            {} 
        };
    }



    template <typename T>
    constexpr Multivector4<T> operator-(unity_t<T> a, const Multivector4<T>& b) noexcept
    {
        return { 
            a-b.a, 
            -b.x, -b.y, -b.z, -b.w,
            -b.xy, -b.yz, -b.zw, -b.wx, -b.xz, -b.yw,
            -b.xyz, -b.yzw, -b.zwx, -b.wxy,
            -b.xyzw
        };
    }


    template <typename T>
    constexpr Multivector4<T> operator-(unity_t<T> a, const Quadvector4<T>& b) noexcept
    {
        return { 
            a,
            {}, {}, {}, {}, 
            {}, {}, {}, {}, {}, {}, 
            {}, {}, {}, {}, 
            -b.xyzw 
        };
    }


    template <typename T>
    constexpr Multivector4<T> operator-(unity_t<T> a, const Trivector4<T>& b) noexcept
    {
        return { 
            a, 
            {}, {}, {}, {}, 
            {}, {}, {}, {}, {}, {}, 
            -b.xyz, -b.yzw, -b.zwx, -b.wxy, 
            {} 
        };
    }

    template <typename T>
    constexpr Multivector4<T> operator-(unity_t<T> a, const Vector4<T>& b) noexcept
    {
        return { 
            a, 
            -b.x, -b.y, -b.z, -b.w, 
            {}, {}, {}, {}, {}, {}, 
            {}, {}, {}, {}, 
            {} 
        };
    }


    


    template <typename T>
    constexpr Multivector4<T> operator-(const Vector4<T>& a, const Bivector4<T>& b) noexcept
    {
        return { 
            {}, 
            a.x, a.y, a.z, a.w, 
            -b.xy, -b.yz, -b.zw, -b.wx, -b.xz, -b.yw,
            {}, {}, {}, {}, 
            {} 
        };
    }

    template <typename T>
    constexpr Multivector4<T> operator-(const Vector4<T>& a, const Multivector4<T>& b) noexcept
    {
        return { 
            -b.a, 
            a.x-b.x, a.y-b.y, a.z-b.z, a.w-b.w, 
            -b.xy, -b.yz, -b.zw, -b.wx, -b.xz, -b.yw,
            -b.xyz, -b.yzw, -b.zwx, -b.wxy,
            -b.xyzw
        };
    }

    template <typename T>
    constexpr Multivector4<T> operator-(const Vector4<T>& a, const Quadvector4<T>& b) noexcept
    {
        return { 
            {}, 
            a.x, a.y, a.z, a.w, 
            {}, {}, {}, {}, {}, {}, 
            {}, {}, {}, {}, 
            -b.xyzw
        };
    }

    template <typename T>
    constexpr Multivector4<T> operator-(const Vector4<T>& a, const Trivector4<T>& b) noexcept
    {
        return { 
            {}, 
            a.x, a.y, a.z, a.w, 
            {}, {}, {}, {}, {}, {}, 
            -b.xyz, -b.yzw, -b.zwx, -b.wxy,
            {} 
        };
    }    

    template <typename T>
    constexpr Multivector4<T> operator-(const Vector4<T>& a, unity_t<T> b) noexcept
    {
        return { 
            -b, 
            a.x, a.y, a.z, a.w, 
            {}, {}, {}, {}, {}, {}, 
            {}, {}, {}, {}, 
            {} 
        };
    }



//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Multivector4<T> operator*(T a, const Multivector4<T>&b) noexcept
    {
        return { 
            a*b.a, 
            a*b.x, a*b.y, a*b.z, a*b.w,
            a*b.xy, a*b.yz, a*b.zw, a*b.wx, a*b.xz, a*b.yw,
            a*b.xyz, a*b.yzw, a*b.zwx, a*b.wxy,
            a*b.xyzw
        };
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Multivector4<T> operator*(const Multivector4<T>&a, T b) noexcept
    {
        return { 
            a.a*b, 
            a.x*b, a.y*b, a.z*b, a.w*b,
            a.xy*b, a.yz*b, a.zw*b, a.wx*b, a.xz*b, a.yw*b,
            a.xyz*b, a.yzw*b, a.zwx*b, a.wxy*b,
            a.xyzw*b
        };
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    Multivector4<T>& operator*=(Multivector4<T>& a, T b) noexcept
    {
        a.a   *=b; 
        a.x   *=b; a.y  *=b; a.z  *=b; a.w  *=b;
        a.xy  *=b; a.yz *=b; a.zw *=b; a.wx *=b; a.xz *=b; a.yw *=b;
        a.xyz *=b; a.yzw*=b; a.zwx*=b; a.wxy*=b;
        a.xyzw*=b;
        return a;
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Multivector4<T>   operator* (const Vector4<T>&a, const Vector4<T>&b) 
    {
        return {
            a.x*b.x+a.y*b.y+a.z*b.z+a.w*b.w, 0., 0., 0., 0.,
            a.x*b.y-a.y*b.x, a.y*b.z-a.z*b.y, a.z*b.w-a.w*b.z, a.w*b.x-a.x*b.w, a.x*b.z-a.z*b.x, a.y*b.w-a.w*b.y,
            0., 0., 0., 0., 0.
        };
    }

//  --------------------------------------------------------
//  DIVISION

    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Multivector4<T> operator/(const Multivector4<T>&a, T b) noexcept
    {
        return { 
            a.a/b, 
            a.x/b, a.y/b, a.z/b, a.w/b,
            a.xy/b, a.yz/b, a.zw/b, a.wx/b, a.xz/b, a.yw/b,
            a.xyz/b, a.yzw/b, a.zwx/b, a.wxy/b,
            a.xyzw/b
        };
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    Multivector4<T>& operator/=(Multivector4<T>& a, T b) noexcept
    {
        a.a   /=b; 
        a.x   /=b; a.y  /=b; a.z  /=b; a.w  /=b;
        a.xy  /=b; a.yz /=b; a.zw /=b; a.wx /=b; a.xz /=b; a.yw /=b;
        a.xyz /=b; a.yzw/=b; a.zwx/=b; a.wxy/=b;
        a.xyzw/=b;
        return a;
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Multivector4<T>   operator/ (const Vector4<T>&a, const Vector4<T>&b) 
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

YQ_TYPE_DECLARE(Multivector4D)
YQ_TYPE_DECLARE(Multivector4F)

