////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Bivector2.hpp"
#include "Bivector3.hpp"
#include "Bivector4.hpp"

#include "Multivector1.hpp"
#include "Multivector2.hpp"
#include "Multivector3.hpp"
#include "Multivector4.hpp"

#include "Quadvector4.hpp"

#include "Trivector3.hpp"
#include "Trivector4.hpp"

#include "Vector1.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"

#include "vector_math.hpp"

namespace yq {

    //  --------------------------------------------------------
    //  COMPOSITION


    template <typename T>
    constexpr Bivector2<T> bivector(const Multivector2<T>& a)
    {
        return { a.xy };
    }

    template <typename T>
    constexpr Bivector3<T> bivector(const Multivector3<T>& a)
    {
        return { a.xy, a.yz, a.zx };
    }

    template <typename T>
    constexpr Bivector4<T> bivector(const Multivector4<T>& a)
    {
        return { a.xy, a.yz, a.zw, a.wx, a.xz, a.yw };
    }

    template <typename T>
    constexpr Quadvector4<T> quadvector(const Multivector4<T>& a)
    {
        return { a.xyzw };
    }

    template <typename T>
    constexpr Trivector3<T> trivector(const Multivector3<T>& a)
    {
        return { a.xyz };
    }

    template <typename T>
    constexpr Trivector4<T> trivector(const Multivector4<T>& a)
    {
        return { a.xyz, a.yzw, a.zwx, a.wxy };
    }

    template <typename T>
    constexpr Vector1<T> vector(const Multivector1<T>& a)
    {
        return { a.x };
    }

    template <typename T>
    constexpr Vector2<T> vector(const Multivector2<T>& a)
    {
        return { a.x, a.y };
    }

    template <typename T>
    constexpr Vector3<T> vector(const Multivector3<T>& a)
    {
        return { a.x, a.y, a.z };
    }

    template <typename T>
    constexpr Vector4<T> vector(const Multivector4<T>& a)
    {
        return { a.x, a.y, a.z, a.w };
    }

    //  --------------------------------------------------------
    //  BASIC FUNCTIONS

    //  --------------------------------------------------------
    //  POSITIVE
    
    template <typename T>
    constexpr Bivector2<T> operator+(const Bivector2<T>& a)
    {
        return a;
    }

    template <typename T>
    constexpr Bivector3<T> operator+(const Bivector3<T>& a)
    {
        return a;
    }

    template <typename T>
    constexpr Bivector4<T> operator+(const Bivector4<T>& a)
    {
        return a;
    }
    
    template <typename T>
    constexpr Trivector3<T> operator+(const Trivector3<T>&a)
    {
        return a;
    }
    
    template <typename T>
    constexpr Trivector4<T> operator+(const Trivector4<T>&a)
    {
        return a;
    }
    
    template <typename T>
    constexpr Quadvector4<T> operator+(const Quadvector4<T>& a)
    {
        return a;
    }
    
    template <typename T>
    constexpr Multivector1<T> operator+(const Multivector1<T>& a)
    {
        return a;
    }

    template <typename T>
    constexpr Multivector2<T> operator+(const Multivector2<T>& a)
    {
        return a;
    }

    template <typename T>
    constexpr Multivector3<T> operator+(const Multivector3<T>& a)
    {
        return a;
    }

    template <typename T>
    constexpr Multivector4<T> operator+(const Multivector4<T>& a)
    {
        return a;
    }

    //  --------------------------------------------------------
    //  NEGATIVE


    template <typename T>
    constexpr Bivector2<T> operator-(const Bivector2<T>& a)
    {
        return {-a.xy};
    }

    template <typename T>
    constexpr Bivector3<T> operator-(const Bivector3<T>& a)
    {
        return {-a.xy, -a.yz, -a.zx};
    }

    template <typename T>
    constexpr Bivector4<T> operator-(const Bivector4<T>& a)
    {
        return {-a.xy, -a.yz, -a.zw, -a.wx, -a.xz, -a.yw};
    }
    
    template <typename T>
    constexpr Trivector3<T> operator-(const Trivector3<T>&a)
    {
        return {-a.xyz};
    }
    
    template <typename T>
    constexpr Trivector4<T> operator-(const Trivector4<T>&a)
    {
        return {-a.xyz, -a.yzw, -a.zwx, -a.wxy};
    }
    
    template <typename T>
    constexpr Quadvector4<T> operator-(const Quadvector4<T>& a)
    {
        return {-a.xyzw};
    }
    
    template <typename T>
    constexpr Multivector1<T> operator-(const Multivector1<T>& a)
    {
        return {-a.a, -a.x};
    }

    template <typename T>
    constexpr Multivector2<T> operator-(const Multivector2<T>& a)
    {
        return {-a.a, -a.x, -a.y, -a.xy};
    }

    template <typename T>
    constexpr Multivector3<T> operator-(const Multivector3<T>& a)
    {
        return {-a.a, -a.x, -a.y, -a.z, -a.xy, -a.yz, -a.zx, -a.xyz };
    }

    template <typename T>
    constexpr Multivector4<T> operator-(const Multivector4<T>& a)
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
    constexpr Bivector2<T> operator+(const Bivector2<T>& a, const Bivector2<T>& b)
    {
        return {
            a.xy+b.xy
        };
    }

    template <typename T>
    Bivector2<T>& operator+=(Bivector2<T>& a, const Bivector2<T>& b)
    {
        a.xy += b.xy;
        return a;
    }

    template <typename T>
    constexpr Multivector3<T> operator+(Bivector2<T> a, const Multivector2<T>& b)
    {
        return { 
            b.a, 
            b.x, b.y,
            a+b.xy
        };
    }


    template <typename T>
    constexpr Multivector2<T> operator+(Bivector2<T> a, unity_t<T>  b)
    {
        return { 
            b, 
            {}, {},
            a.xy
        };
    }

    template <typename T>
    constexpr Multivector2<T> operator+(Bivector2<T> a, const Vector2<T>& b)
    {
        return { 
            {}, 
            b.x, b.y, 
            a.xy 
        };
    }

    template <typename T>
    constexpr Bivector3<T> operator+(const Bivector3<T>& a, const Bivector3<T>& b)
    {
        return {a.xy+b.xy, a.yz+b.yz, a.zx+b.zx};
    }

    template <typename T>
    Bivector3<T>&       operator+=(Bivector3<T>&a, const Bivector3<T>&b)
    {
        a.xy+=b.xy; a.yz+=b.yz; a.zx+=b.zx;
        return a;
    }

    template <typename T>
    constexpr Multivector3<T> operator+(Bivector3<T> a, const Multivector3<T>& b)
    {
        return { 
            b.a, 
            b.x, b.y, b.z,
            a.xy+b.xy, a.yz+b.yz, a.zx+b.zx,
            b.xyz
        };
    }

    template <typename T>
    constexpr Multivector3<T> operator+(Bivector3<T> a, const Trivector3<T>& b)
    {
        return { 
            {}, 
            {}, {}, {}, 
            a.xy, a.yz, a.zx, 
            b.xyz
        };
    }

    template <typename T>
    constexpr Multivector3<T> operator+(Bivector3<T> a, unity_t<T>  b)
    {
        return { 
            b, 
            {}, {}, {}, 
            a.xy, a.yz, a.zx, 
            {} 
        };
    }


    template <typename T>
    constexpr Multivector3<T> operator+(Bivector3<T> a, const Vector3<T>& b)
    {
        return { 
            {}, 
            b.x, b.y, b.z, 
            a.xy, a.yz, a.zx, 
            {} 
        };
    }

    template <typename T>
    constexpr Bivector4<T> operator+(const Bivector4<T>& a, const Bivector4<T>& b)
    {
        return {a.xy+b.xy, a.yz+b.yz, a.zw+b.zw, a.wx+b.wx, a.xz+b.xz, a.yw+b.yw};
    }

    template <typename T>
    Bivector4<T>&       operator+=(Bivector4<T>&a, const Bivector4<T>&b)
    {
        a.xy+=b.xy; a.yz+=b.yz; a.zw+=b.zw; a.wx+=b.wx; a.xz+=b.xz; a.yw+=b.yw;
        return a;
    }

    template <typename T>
    constexpr Multivector4<T> operator+(Bivector4<T> a, const Multivector4<T>& b)
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
    constexpr Multivector4<T> operator+(Bivector4<T> a, const Quadvector4<T>& b)
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
    constexpr Multivector4<T> operator+(Bivector4<T> a, const Trivector4<T>& b)
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
    constexpr Multivector4<T> operator+(Bivector4<T> a, unity_t<T>  b)
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
    constexpr Multivector4<T> operator+(Bivector4<T> a, const Vector4<T>& b)
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
    constexpr Multivector1<T> operator+(const Multivector1<T>& a, const Multivector1<T>&  b)
    {
        return {
            a.a+b.a,
            a.x+b.x
        };
    }

    template <typename T>
    Multivector1<T>& operator+=(Multivector1<T>& a, const Multivector1<T>& b)
    {
        a.a += b.a;
        a.x += b.x;
        return a;
    }

    template <typename T>
    constexpr Multivector1<T> operator+(const Multivector1<T>& a, unity_t<T>  b)
    {
        return {
            a.a+b,
            a.x
        };
    }

    template <typename T>
    Multivector1<T>& operator+=(Multivector1<T>& a, unity_t<T>  b)
    {
        a.a += b;
        return a;
    }
    

    template <typename T>
    constexpr Multivector1<T> operator+(const Multivector1<T>& a, const Vector1<T>&  b)
    {
        return {
            a.a,
            a.x+b.x
        };
    }

    template <typename T>
    Multivector1<T>& operator+=(Multivector1<T>& a, const Vector1<T>& b)
    {
        a.x += b.x;
        return a;
    }
    
    template <typename T>
    constexpr Multivector2<T> operator+(const Multivector2<T>& a, const Bivector2<T>& b)
    {
        return {
            a.a,
            a.x, a.y,
            a.xy + b.xy
        };
    }

    template <typename T>
    Multivector2<T>& operator+=(Multivector2<T>& a, const Bivector2<T>& b)
    {
        a.xy += b.xy;
        return a;
    }

    template <typename T>
    constexpr Multivector2<T> operator+(const Multivector2<T>& a, const Multivector2<T>&  b)
    {
        return {
            a.a+b.a,
            a.x+b.x, a.y+b.y,
            a.xy+b.xy
        };
    }

    template <typename T>
    Multivector2<T>& operator+=(Multivector2<T>& a, const Multivector2<T>& b)
    {
        a.a += b.a;
        a.x += b.x; a.y += b.y; 
        a.xy += b.xy;
        return a;
    }
        
    template <typename T>
    constexpr Multivector2<T> operator+(const Multivector2<T>& a, unity_t<T>  b)
    {
        return {
            a.a+b,
            a.x, a.y,
            a.xy
        };
    }

    template <typename T>
    Multivector2<T>& operator+=(Multivector2<T>& a, unity_t<T>  b)
    {
        a.a += b;
        return a;
    }



    template <typename T>
    constexpr Multivector2<T> operator+(const Multivector2<T>& a, const Vector2<T>&  b)
    {
        return {
            a.a,
            a.x+b.x, a.y+b.y,
            a.xy
        };
    }

    template <typename T>
    Multivector2<T>& operator+=(Multivector2<T>& a, const Vector2<T>& b)
    {
        a.x += b.x; a.y += b.y; 
        return a;
    }

    template <typename T>
    constexpr Multivector3<T> operator+(const Multivector3<T>& a, const Bivector3<T>& b)
    {
        return {
            a.a,
            a.x, a.y, a.z, 
            a.xy+b.xy, a.yz+b.yz, a.zx+b.zx,
            a.xyz
        };
    }

    template <typename T>
    Multivector3<T>& operator+=(Multivector3<T>& a, const Bivector3<T>& b)
    {
        a.xy+=b.xy; a.yz+=b.yz; a.zx+=b.zx;
        return a;
    }

    template <typename T>
    constexpr Multivector3<T> operator+(const Multivector3<T>& a, const Multivector3<T>&  b)
    {
        return {
            a.a+b.a,
            a.x+b.x, a.y+b.y, a.z+b.z,
            a.xy+b.xy, a.yz+b.yz, a.zx+b.zx,
            a.xyz+b.xyz
        };
    }

    template <typename T>
    Multivector3<T>& operator+=(Multivector3<T>& a, const Multivector3<T>& b)
    {
        a.a += b.a;
        a.x += b.x; a.y += b.y; a.z += b.z;
        a.xy+=b.xy; a.yz+=b.yz; a.zx+=b.zx;
        a.xyz += b.xyz;
        return a;
    }

    template <typename T>
    constexpr Multivector3<T> operator+(const Multivector3<T>& a, const Trivector3<T>& b)
    {
        return {
            a.a,
            a.x, a.y, a.z, 
            a.xy, a.yz, a.zx, 
            a.xyz+b.xyz
        };
    }

    template <typename T>
    Multivector3<T>& operator+=(Multivector3<T>& a, const Trivector3<T>& b)
    {
        a.xyz += b.xyz;
        return a;
    }
    
    template <typename T>
    constexpr Multivector3<T> operator+(const Multivector3<T>& a, unity_t<T>  b)
    {
        return {
            a.a+b,
            a.x, a.y, a.z,
            a.xy, a.yz, a.zx, 
            a.xyz
        };
    }

    template <typename T>
    Multivector3<T>& operator+=(Multivector3<T>& a, unity_t<T>  b)
    {
        a.a += b;
        return a;
    }

    template <typename T>
    constexpr Multivector3<T> operator+(const Multivector3<T>& a, const Vector3<T>&  b)
    {
        return {
            a.a,
            a.x+b.x, a.y+b.y, a.z+b.z,
            a.xy, a.yz, a.zx,
            a.xyz
        };
    }

    template <typename T>
    Multivector3<T>& operator+=(Multivector3<T>& a, const Vector3<T>& b)
    {
        a.x += b.x; a.y += b.y; a.z += b.z;
        return a;
    }
    


    template <typename T>
    constexpr Multivector4<T> operator+(const Multivector4<T>& a, const Bivector4<T>& b)
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
    Multivector4<T>& operator+=(Multivector4<T>& a, const Bivector4<T>& b)
    {
        a.xy+=b.xy; a.yz+=b.yz; a.zw+=b.zw; a.wx+=b.wx; a.xz+=b.xz; a.yw+=b.yw;
        return a;
    }
    
    template <typename T>
    constexpr Multivector4<T> operator+(const Multivector4<T>& a, const Multivector4<T>&  b)
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
    Multivector4<T>& operator+=(Multivector4<T>& a, const Multivector4<T>& b)
    {
        a.a += b.a;
        a.x += b.x; a.y += b.y; a.z += b.z; a.w += b.w;
        a.xy += b.xy; a.yz += b.yz; a.zw += b.zw; a.wx += b.wx; a.xz += b.xz; a.yw += b.yw;
        a.xyz += b.xyz; a.yzw += b.yzw; a.zwx += b.zwx; a.wxy += b.wxy;
        a.xyzw += b.xyzw;
        return a;
    }

    template <typename T>
    constexpr Multivector4<T> operator+(const Multivector4<T>& a, const Quadvector4<T>& b)
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
    Multivector4<T>& operator+=(Multivector4<T>& a, const Quadvector4<T>& b)
    {
        a.xyzw += b.xyzw;
        return a;
    }
    
    template <typename T>
    constexpr Multivector4<T> operator+(const Multivector4<T>& a, const Trivector4<T>& b)
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
    Multivector4<T>& operator+=(Multivector4<T>& a, const Trivector4<T>& b)
    {
        a.xyz+=b.xyz; a.yzw+=b.yzw; a.zwx+=b.zwx; a.wxy+=b.wxy;
        return a;
    }
    
    
    template <typename T>
    constexpr Multivector4<T> operator+(const Multivector4<T>& a, unity_t<T>  b)
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
    Multivector4<T>& operator+=(Multivector4<T>& a, unity_t<T>  b)
    {
        a.a += b;
        return a;
    }


    template <typename T>
    constexpr Multivector4<T> operator+(const Multivector4<T>& a, const Vector4<T>&  b)
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
    Multivector4<T>& operator+=(Multivector4<T>& a, const Vector4<T>& b)
    {
        a.x += b.x; a.y += b.y; a.z += b.z; a.w += b.w;
        return a;
    }

    template <typename T>
    constexpr Quadvector4<T> operator+(const Quadvector4<T>& a, const Quadvector4<T>& b)
    {
        return { a.xyzw + b.xyzw };
    }

    template <typename T>
    Quadvector4<T>& operator+=(Quadvector4<T>& a, const Quadvector4<T>& b)
    {
        a.xyzw += b.xyzw;
        return a;
    }

    template <typename T>
    constexpr Multivector4<T> operator+(Quadvector4<T> a, unity_t<T>  b)
    {
        return { 
            b, 
            {}, {}, {}, {}, 
            {}, {}, {}, {}, {}, {}, 
            {}, {}, {}, {}, 
            a 
        };
    }
    
    
    template <typename T>
    constexpr Trivector4<T> operator+(const Trivector3<T>& a, const Trivector3<T>& b)
    {
        return { a.xyz+b.xyz };
    }

    template <typename T>
    Trivector4<T>& operator+=(Trivector3<T>& a, const Trivector3<T>& b)
    {
        a.xyz+=b.xyz;
        return a;
    }
    
    template <typename T>
    constexpr Multivector3<T> operator+(Trivector3<T> a, unity_t<T>  b)
    {
        return { 
            b, 
            {}, {}, {}, 
            {}, {}, {}, 
            a.xyz 
        };
    }

    template <typename T>
    constexpr Trivector4<T> operator+(const Trivector4<T>& a, const Trivector4<T>& b)
    {
        return { a.xyz+b.xyz, a.yzw+b.yzw, a.zwx+b.zwx, a.wxy+b.wxy };
    }

    template <typename T>
    Trivector4<T>& operator+(Trivector4<T>& a, const Trivector4<T>& b)
    {
        a.xyz+=b.xyz; a.yzw+=b.yzw; a.zwx+=b.zwx; a.wxy+=b.wxy;
        return a;
    }


    template <typename T>
    constexpr Multivector4<T> operator+(Trivector4<T> a, unity_t<T>  b)
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
    constexpr Multivector2<T> operator+(unity_t<T> a, const Bivector2<T>& b)
    {
        return { 
            a, 
            {}, {},
            b 
        };
    }

    template <typename T>
    constexpr Multivector3<T> operator+(unity_t<T> a, const Bivector3<T>& b)
    {
        return { 
            a, 
            {}, {}, {}, 
            b.xy, b.yz, b.zx, 
            {} 
        };
    }

    template <typename T>
    constexpr Multivector4<T> operator+(unity_t<T> a, const Bivector4<T>& b)
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
    constexpr Multivector1<T> operator+(unity_t<T> a, const Multivector1<T>& b)
    {
        return { 
            a+b.a, 
            b.x 
        };
    }

    template <typename T>
    constexpr Multivector2<T> operator+(unity_t<T> a, const Multivector2<T>& b)
    {
        return { 
            a+b.a, 
            b.x, b.y, 
            b.xy
        };
    }

    template <typename T>
    constexpr Multivector3<T> operator+(unity_t<T> a, const Multivector3<T>& b)
    {
        return { 
            a+b.a, 
            b.x, b.y, b.z,
            b.xy, b.yz, b.zx,
            b.xyz
        };
    }

    template <typename T>
    constexpr Multivector4<T> operator+(unity_t<T> a, const Multivector4<T>& b)
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
    constexpr Multivector4<T> operator+(unity_t<T> a, const Quadvector4<T>& b)
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
    constexpr Multivector3<T> operator+(unity_t<T> a, const Trivector3<T>& b)
    {
        return { 
            a, 
            {}, {}, {}, 
            {}, {}, {}, 
            b.xyz
        };
    }

    template <typename T>
    constexpr Multivector4<T> operator+(unity_t<T> a, const Trivector4<T>& b)
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
    constexpr Multivector1<T> operator+(unity_t<T> a, const Vector1<T>& b)
    {
        return { 
            a, 
            b.x 
        };
    }
    
    template <typename T>
    constexpr Multivector2<T> operator+(unity_t<T> a, const Vector2<T>& b)
    {
        return { 
            a, 
            b.x, b.y, 
            {} 
        };
    }

    template <typename T>
    constexpr Multivector3<T> operator+(unity_t<T> a, const Vector3<T>& b)
    {
        return { 
            a, 
            b.x, b.y, b.z, 
            {}, {}, {}, 
            {} 
        };
    }

    template <typename T>
    constexpr Multivector4<T> operator+(unity_t<T> a, const Vector4<T>& b)
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
    constexpr Multivector1<T> operator+(Vector1<T> a, const Multivector1<T>& b)
    {
        return { 
            b.a, 
            a.x+b.x
        };
    }

    template <typename T>
    constexpr Multivector1<T> operator+(Vector1<T> a, unity_t<T>  b)
    {
        return { 
            b, 
            a.x 
        };
    }


    template <typename T>
    constexpr Multivector2<T> operator+(Vector2<T> a, const Bivector2<T>& b)
    {
        return { 
            {}, 
            a.x, a.y, 
            b.xy 
        };
    }

    template <typename T>
    constexpr Multivector2<T> operator+(Vector2<T> a, const Multivector2<T>& b)
    {
        return { 
            b.a, 
            a.x+b.x, a.y+b.y,
            b.xy
        };
    }

    template <typename T>
    constexpr Multivector2<T> operator+(Vector2<T> a, unity_t<T>  b)
    {
        return { 
            b, 
            a.x, a.y, 
            {} 
        };
    }
    
    template <typename T>
    constexpr Multivector3<T> operator+(Vector3<T> a, const Bivector3<T>& b)
    {
        return { 
            {}, 
            a.x, a.y, a.z,
            b.xy, b.yz, b.zx,
            {} 
        };
    }

    template <typename T>
    constexpr Multivector3<T> operator+(Vector3<T> a, const Multivector3<T>& b)
    {
        return { 
            b.a, 
            a.x+b.x, a.y+b.y, a.z+b.z, 
            b.xy, b.yz, b.zx,
            b.xyz
        };
    }

    template <typename T>
    constexpr Multivector3<T> operator+(Vector3<T> a, const Trivector3<T>& b)
    {
        return { 
            {}, 
            a.x, a.y, a.z,
            {}, {}, {}, 
            b.xyz
        };
    }

    template <typename T>
    constexpr Multivector3<T> operator+(Vector3<T> a, unity_t<T>  b)
    {
        return { 
            b, 
            a.x, a.y, a.z,
            {}, {}, {}, 
            {} 
        };
    }

    template <typename T>
    constexpr Multivector4<T> operator+(Vector4<T> a, const Bivector4<T>& b)
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
    constexpr Multivector4<T> operator+(Vector4<T> a, const Multivector4<T>& b)
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
    constexpr Multivector4<T> operator+(Vector4<T> a, const Quadvector4<T>& b)
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
    constexpr Multivector4<T> operator+(Vector4<T> a, const Trivector4<T>& b)
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
    constexpr Multivector4<T> operator+(Vector4<T> a, unity_t<T>  b)
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
    constexpr Bivector2<T> operator-(const Bivector2<T>& a, const Bivector2<T>& b)
    {
        return {
            a.xy-b.xy
        };
    }

    template <typename T>
    Bivector2<T>& operator-=(Bivector2<T>& a, const Bivector2<T>& b)
    {
        a.xy -= b.xy;
        return a;
    }

    template <typename T>
    constexpr Multivector3<T> operator-(Bivector2<T> a, const Multivector2<T>& b)
    {
        return { 
            -b.a, 
            -b.x, -b.y,
            a-b.xy
        };
    }


    template <typename T>
    constexpr Multivector2<T> operator-(Bivector2<T> a, unity_t<T> b)
    {
        return { 
            -b, 
            {}, {},
            a.xy
        };
    }

    template <typename T>
    constexpr Multivector2<T> operator-(Bivector2<T> a, const Vector2<T>& b)
    {
        return { 
            {}, 
            -b.x, -b.y, 
            a.xy 
        };
    }

    template <typename T>
    constexpr Bivector3<T> operator-(const Bivector3<T>& a, const Bivector3<T>& b)
    {
        return {a.xy-b.xy, a.yz-b.yz, a.zx-b.zx};
    }

    template <typename T>
    Bivector3<T>&       operator-=(Bivector3<T>&a, const Bivector3<T>&b)
    {
        a.xy-=b.xy; a.yz-=b.yz; a.zx-=b.zx;
        return a;
    }

    template <typename T>
    constexpr Multivector3<T> operator-(Bivector3<T> a, const Multivector3<T>& b)
    {
        return { 
            -b.a, 
            -b.x, -b.y, -b.z,
            a.xy-b.xy, a.yz-b.yz, a.zx-b.zx,
            -b.xyz
        };
    }

    template <typename T>
    constexpr Multivector3<T> operator-(Bivector3<T> a, const Trivector3<T>& b)
    {
        return { 
            {}, 
            {}, {}, {}, 
            a.xy, a.yz, a.zx, 
            -b.xyz
        };
    }

    template <typename T>
    constexpr Multivector3<T> operator-(Bivector3<T> a, unity_t<T> b)
    {
        return { 
            -b, 
            {}, {}, {}, 
            a.xy, a.yz, a.zx, 
            {} 
        };
    }


    template <typename T>
    constexpr Multivector3<T> operator-(Bivector3<T> a, const Vector3<T>& b)
    {
        return { 
            {}, 
            -b.x, -b.y, -b.z, 
            a.xy, a.yz, a.zx, 
            {} 
        };
    }

    template <typename T>
    constexpr Bivector4<T> operator-(const Bivector4<T>& a, const Bivector4<T>& b)
    {
        return {a.xy-b.xy, a.yz-b.yz, a.zw-b.zw, a.wx-b.wx, a.xz-b.xz, a.yw-b.yw};
    }

    template <typename T>
    Bivector4<T>&       operator-=(Bivector4<T>&a, const Bivector4<T>&b)
    {
        a.xy-=b.xy; a.yz-=b.yz; a.zw-=b.zw; a.wx-=b.wx; a.xz-=b.xz; a.yw-=b.yw;
        return a;
    }

    template <typename T>
    constexpr Multivector4<T> operator-(Bivector4<T> a, const Multivector4<T>& b)
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
    constexpr Multivector4<T> operator-(Bivector4<T> a, const Quadvector4<T>& b)
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
    constexpr Multivector4<T> operator-(Bivector4<T> a, const Trivector4<T>& b)
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
    constexpr Multivector4<T> operator-(Bivector4<T> a, unity_t<T> b)
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
    constexpr Multivector4<T> operator-(Bivector4<T> a, const Vector4<T>& b)
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
    constexpr Multivector1<T> operator-(const Multivector1<T>& a, const Multivector1<T>& b)
    {
        return {
            a.a-b.a,
            a.x-b.x
        };
    }

    template <typename T>
    Multivector1<T>& operator-=(Multivector1<T>& a, const Multivector1<T>& b)
    {
        a.a -= b.a;
        a.x -= b.x;
        return a;
    }

    template <typename T>
    constexpr Multivector1<T> operator-(const Multivector1<T>& a, unity_t<T> b)
    {
        return {
            a.a-b,
            a.x
        };
    }

    template <typename T>
    Multivector1<T>& operator-=(Multivector1<T>& a, unity_t<T> b)
    {
        a.a -= b;
        return a;
    }
    

    template <typename T>
    constexpr Multivector1<T> operator-(const Multivector1<T>& a, const Vector1<T>& b)
    {
        return {
            a.a,
            a.x-b.x
        };
    }

    template <typename T>
    Multivector1<T>& operator-=(Multivector1<T>& a, const Vector1<T>& b)
    {
        a.x -= b.x;
        return a;
    }
    
    template <typename T>
    constexpr Multivector2<T> operator-(const Multivector2<T>& a, const Bivector2<T>& b)
    {
        return {
            a.a,
            a.x, a.y,
            a.xy - b.xy
        };
    }

    template <typename T>
    Multivector2<T>& operator-=(Multivector2<T>& a, const Bivector2<T>& b)
    {
        a.xy -= b.xy;
        return a;
    }

    template <typename T>
    constexpr Multivector2<T> operator-(const Multivector2<T>& a, const Multivector2<T>& b)
    {
        return {
            a.a-b.a,
            a.x-b.x, a.y-b.y,
            a.xy-b.xy
        };
    }

    template <typename T>
    Multivector2<T>& operator-=(Multivector2<T>& a, const Multivector2<T>& b)
    {
        a.a -= b.a;
        a.x -= b.x; a.y -= b.y; 
        a.xy -= b.xy;
        return a;
    }
        
    template <typename T>
    constexpr Multivector2<T> operator-(const Multivector2<T>& a, unity_t<T> b)
    {
        return {
            a.a-b,
            a.x, a.y,
            a.xy
        };
    }

    template <typename T>
    Multivector2<T>& operator-=(Multivector2<T>& a, unity_t<T> b)
    {
        a.a -= b;
        return a;
    }



    template <typename T>
    constexpr Multivector2<T> operator-(const Multivector2<T>& a, const Vector2<T>& b)
    {
        return {
            a.a,
            a.x-b.x, a.y-b.y,
            a.xy
        };
    }

    template <typename T>
    Multivector2<T>& operator-=(Multivector2<T>& a, const Vector2<T>& b)
    {
        a.x -= b.x; a.y -= b.y; 
        return a;
    }

    template <typename T>
    constexpr Multivector3<T> operator-(const Multivector3<T>& a, const Bivector3<T>& b)
    {
        return {
            a.a,
            a.x, a.y, a.z, 
            a.xy-b.xy, a.yz-b.yz, a.zx-b.zx,
            a.xyz
        };
    }

    template <typename T>
    Multivector3<T>& operator-=(Multivector3<T>& a, const Bivector3<T>& b)
    {
        a.xy-=b.xy; a.yz-=b.yz; a.zx-=b.zx;
        return a;
    }

    template <typename T>
    constexpr Multivector3<T> operator-(const Multivector3<T>& a, const Multivector3<T>& b)
    {
        return {
            a.a-b.a,
            a.x-b.x, a.y-b.y, a.z-b.z,
            a.xy-b.xy, a.yz-b.yz, a.zx-b.zx,
            a.xyz-b.xyz
        };
    }

    template <typename T>
    Multivector3<T>& operator-=(Multivector3<T>& a, const Multivector3<T>& b)
    {
        a.a -= b.a;
        a.x -= b.x; a.y -= b.y; a.z -= b.z;
        a.xy-=b.xy; a.yz-=b.yz; a.zx-=b.zx;
        a.xyz -= b.xyz;
        return a;
    }

    template <typename T>
    constexpr Multivector3<T> operator-(const Multivector3<T>& a, const Trivector3<T>& b)
    {
        return {
            a.a,
            a.x, a.y, a.z, 
            a.xy, a.yz, a.zx, 
            a.xyz-b.xyz
        };
    }

    template <typename T>
    Multivector3<T>& operator-=(Multivector3<T>& a, const Trivector3<T>& b)
    {
        a.xyz -= b.xyz;
        return a;
    }
    
    template <typename T>
    constexpr Multivector3<T> operator-(const Multivector3<T>& a, unity_t<T> b)
    {
        return {
            a.a-b,
            a.x, a.y, a.z,
            a.xy, a.yz, a.zx, 
            a.xyz
        };
    }

    template <typename T>
    Multivector3<T>& operator-=(Multivector3<T>& a, unity_t<T> b)
    {
        a.a -= b;
        return a;
    }

    template <typename T>
    constexpr Multivector3<T> operator-(const Multivector3<T>& a, const Vector3<T>& b)
    {
        return {
            a.a,
            a.x-b.x, a.y-b.y, a.z-b.z,
            a.xy, a.yz, a.zx,
            a.xyz
        };
    }

    template <typename T>
    Multivector3<T>& operator-=(Multivector3<T>& a, const Vector3<T>& b)
    {
        a.x -= b.x; a.y -= b.y; a.z -= b.z;
        return a;
    }
    


    template <typename T>
    constexpr Multivector4<T> operator-(const Multivector4<T>& a, const Bivector4<T>& b)
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
    Multivector4<T>& operator-=(Multivector4<T>& a, const Bivector4<T>& b)
    {
        a.xy-=b.xy; a.yz-=b.yz; a.zw-=b.zw; a.wx-=b.wx; a.xz-=b.xz; a.yw-=b.yw;
        return a;
    }
    
    template <typename T>
    constexpr Multivector4<T> operator-(const Multivector4<T>& a, const Multivector4<T>& b)
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
    Multivector4<T>& operator-=(Multivector4<T>& a, const Multivector4<T>& b)
    {
        a.a -= b.a;
        a.x -= b.x; a.y -= b.y; a.z -= b.z; a.w -= b.w;
        a.xy -= b.xy; a.yz -= b.yz; a.zw -= b.zw; a.wx -= b.wx; a.xz -= b.xz; a.yw -= b.yw;
        a.xyz -= b.xyz; a.yzw -= b.yzw; a.zwx -= b.zwx; a.wxy -= b.wxy;
        a.xyzw -= b.xyzw;
        return a;
    }

    template <typename T>
    constexpr Multivector4<T> operator-(const Multivector4<T>& a, const Quadvector4<T>& b)
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
    Multivector4<T>& operator-=(Multivector4<T>& a, const Quadvector4<T>& b)
    {
        a.xyzw -= b.xyzw;
        return a;
    }
    
    template <typename T>
    constexpr Multivector4<T> operator-(const Multivector4<T>& a, const Trivector4<T>& b)
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
    Multivector4<T>& operator-=(Multivector4<T>& a, const Trivector4<T>& b)
    {
        a.xyz-=b.xyz; a.yzw-=b.yzw; a.zwx-=b.zwx; a.wxy-=b.wxy;
        return a;
    }
    
    
    template <typename T>
    constexpr Multivector4<T> operator-(const Multivector4<T>& a, unity_t<T> b)
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
    Multivector4<T>& operator-=(Multivector4<T>& a, unity_t<T> b)
    {
        a.a -= b;
        return a;
    }


    template <typename T>
    constexpr Multivector4<T> operator-(const Multivector4<T>& a, const Vector4<T>& b)
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
    Multivector4<T>& operator-=(Multivector4<T>& a, const Vector4<T>& b)
    {
        a.x -= b.x; a.y -= b.y; a.z -= b.z; a.w -= b.w;
        return a;
    }

    template <typename T>
    constexpr Quadvector4<T> operator-(const Quadvector4<T>& a, const Quadvector4<T>& b)
    {
        return { a.xyzw - b.xyzw };
    }

    template <typename T>
    Quadvector4<T>& operator-=(Quadvector4<T>& a, const Quadvector4<T>& b)
    {
        a.xyzw -= b.xyzw;
        return a;
    }

    template <typename T>
    constexpr Multivector4<T> operator-(Quadvector4<T> a, unity_t<T> b)
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
    constexpr Trivector4<T> operator-(const Trivector3<T>& a, const Trivector3<T>& b)
    {
        return { a.xyz-b.xyz };
    }

    template <typename T>
    Trivector4<T>& operator-=(Trivector3<T>& a, const Trivector3<T>& b)
    {
        a.xyz-=b.xyz;
        return a;
    }
    
    template <typename T>
    constexpr Multivector3<T> operator-(Trivector3<T> a, unity_t<T> b)
    {
        return { 
            -b, 
            {}, {}, {}, 
            {}, {}, {}, 
            a.xyz 
        };
    }

    template <typename T>
    constexpr Trivector4<T> operator-(const Trivector4<T>& a, const Trivector4<T>& b)
    {
        return { a.xyz-b.xyz, a.yzw-b.yzw, a.zwx-b.zwx, a.wxy-b.wxy };
    }

    template <typename T>
    Trivector4<T>& operator-(Trivector4<T>& a, const Trivector4<T>& b)
    {
        a.xyz-=b.xyz; a.yzw-=b.yzw; a.zwx-=b.zwx; a.wxy-=b.wxy;
        return a;
    }


    template <typename T>
    constexpr Multivector4<T> operator-(Trivector4<T> a, unity_t<T> b)
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
    constexpr Multivector2<T> operator-(unity_t<T> a, const Bivector2<T>& b)
    {
        return { 
            a, 
            {}, {},
            -b 
        };
    }

    template <typename T>
    constexpr Multivector3<T> operator-(unity_t<T> a, const Bivector3<T>& b)
    {
        return { 
            a, 
            {}, {}, {}, 
            -b.xy, -b.yz, -b.zx, 
            {} 
        };
    }

    template <typename T>
    constexpr Multivector4<T> operator-(unity_t<T> a, const Bivector4<T>& b)
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
    constexpr Multivector1<T> operator-(unity_t<T> a, const Multivector1<T>& b)
    {
        return { 
            a-b.a, 
            -b.x 
        };
    }

    template <typename T>
    constexpr Multivector2<T> operator-(unity_t<T> a, const Multivector2<T>& b)
    {
        return { 
            a-b.a, 
            -b.x, -b.y, 
            -b.xy
        };
    }

    template <typename T>
    constexpr Multivector3<T> operator-(unity_t<T> a, const Multivector3<T>& b)
    {
        return { 
            a-b.a, 
            -b.x, -b.y, -b.z,
            -b.xy, -b.yz, -b.zx,
            -b.xyz
        };
    }

    template <typename T>
    constexpr Multivector4<T> operator-(unity_t<T> a, const Multivector4<T>& b)
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
    constexpr Multivector4<T> operator-(unity_t<T> a, const Quadvector4<T>& b)
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
    constexpr Multivector3<T> operator-(unity_t<T> a, const Trivector3<T>& b)
    {
        return { 
            a, 
            {}, {}, {}, 
            {}, {}, {}, 
            -b.xyz
        };
    }

    template <typename T>
    constexpr Multivector4<T> operator-(unity_t<T> a, const Trivector4<T>& b)
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
    constexpr Multivector1<T> operator-(unity_t<T> a, const Vector1<T>& b)
    {
        return { 
            a, 
            -b.x 
        };
    }
    
    template <typename T>
    constexpr Multivector2<T> operator-(unity_t<T> a, const Vector2<T>& b)
    {
        return { 
            a, 
            -b.x, -b.y, 
            {} 
        };
    }

    template <typename T>
    constexpr Multivector3<T> operator-(unity_t<T> a, const Vector3<T>& b)
    {
        return { 
            a, 
            -b.x, -b.y, -b.z, 
            {}, {}, {}, 
            {} 
        };
    }

    template <typename T>
    constexpr Multivector4<T> operator-(unity_t<T> a, const Vector4<T>& b)
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
    constexpr Multivector1<T> operator-(Vector1<T> a, const Multivector1<T>& b)
    {
        return { 
            -b.a, 
            a.x-b.x
        };
    }

    template <typename T>
    constexpr Multivector1<T> operator-(Vector1<T> a, unity_t<T> b)
    {
        return { 
            -b, 
            a.x 
        };
    }


    template <typename T>
    constexpr Multivector2<T> operator-(Vector2<T> a, const Bivector2<T>& b)
    {
        return { 
            {}, 
            a.x, a.y, 
            -b.xy 
        };
    }

    template <typename T>
    constexpr Multivector2<T> operator-(Vector2<T> a, const Multivector2<T>& b)
    {
        return { 
            -b.a, 
            a.x-b.x, a.y-b.y,
            -b.xy
        };
    }

    template <typename T>
    constexpr Multivector2<T> operator-(Vector2<T> a, unity_t<T> b)
    {
        return { 
            -b, 
            a.x, a.y, 
            {} 
        };
    }
    
    template <typename T>
    constexpr Multivector3<T> operator-(Vector3<T> a, const Bivector3<T>& b)
    {
        return { 
            {}, 
            a.x, a.y, a.z,
            -b.xy, -b.yz, -b.zx,
            {} 
        };
    }

    template <typename T>
    constexpr Multivector3<T> operator-(Vector3<T> a, const Multivector3<T>& b)
    {
        return { 
            -b.a, 
            a.x-b.x, a.y-b.y, a.z-b.z, 
            -b.xy, -b.yz, -b.zx,
            -b.xyz
        };
    }

    template <typename T>
    constexpr Multivector3<T> operator-(Vector3<T> a, const Trivector3<T>& b)
    {
        return { 
            {}, 
            a.x, a.y, a.z,
            {}, {}, {}, 
            -b.xyz
        };
    }

    template <typename T>
    constexpr Multivector3<T> operator-(Vector3<T> a, unity_t<T> b)
    {
        return { 
            -b, 
            a.x, a.y, a.z,
            {}, {}, {}, 
            {} 
        };
    }

    template <typename T>
    constexpr Multivector4<T> operator-(Vector4<T> a, const Bivector4<T>& b)
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
    constexpr Multivector4<T> operator-(Vector4<T> a, const Multivector4<T>& b)
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
    constexpr Multivector4<T> operator-(Vector4<T> a, const Quadvector4<T>& b)
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
    constexpr Multivector4<T> operator-(Vector4<T> a, const Trivector4<T>& b)
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
    constexpr Multivector4<T> operator-(Vector4<T> a, unity_t<T> b)
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
    Bivector2<T> operator*(T a, const Bivector2<T>& b)
    {
        return { a*b.xy };
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    Bivector3<T> operator*(T a, const Bivector3<T>& b)
    {
        return { a*b.xy, a*b.yz, a*b.zx };
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    Bivector4<T> operator*(T a, const Bivector4<T>& b)
    {
        return { a*b.xy, a*b.yz, a*b.zw, a*b.wx, a*b.xz, a*b.yw };
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    Trivector3<T> operator*(T a, const Trivector3<T>& b)
    {
        return { a*b.xyz };
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    Trivector4<T> operator*(T a, const Trivector4<T>& b)
    {
        return { a*b.xyz, a*b.yzw, a*b.zwx, a*b.wxy, };
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    Quadvector4<T> operator*(T a, const Quadvector4<T>& b)
    {
        return { a*b.xyzw };
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    Multivector1<T> operator*(T a, const Multivector1<T>&b)
    {
        return { a*b.a, a*b.x };
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    Multivector2<T> operator*(T a, const Multivector2<T>&b)
    {
        return { 
            a*b.a, 
            a*b.x, a*b.y, 
            a*b.xy 
        };
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    Multivector3<T> operator*(T a, const Multivector3<T>&b)
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
    Multivector4<T> operator*(T a, const Multivector4<T>&b)
    {
        return { 
            a*b.a, 
            a*b.x, a*b.y, a*b.z, a*b.w,
            a*b.xy, a*b.yz, a*b.zw, a*b.wx, a*b.xz, a*b.yw,
            a*b.xyz, a*b.yzw, a*b.zwx, a*b.wxy,
            a*b.xyz
        };
    }

    //  --------------------------------------------------------
    //  DIVISION

    //  --------------------------------------------------------
    //  DOT PRODUCT


    //  --------------------------------------------------------
    //  INNER PRODUCT


    //  --------------------------------------------------------
    //  OUTER PRODUCT


    ///  --------------------------------------------------------
    //  OTIMES PRODUCT

    //  --------------------------------------------------------
    //  PROJECTIONS

    //  --------------------------------------------------------
    //  ADVANCED FUNCTIONS


    //  --------------------------------------------------------
    //  CONDITIONAL INCLUDES




}

