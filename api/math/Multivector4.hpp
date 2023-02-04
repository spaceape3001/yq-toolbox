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
        //! Captures the template parameter
        using component_type    = T;

        T       a;
        T       x, y, z, w;
        T       xy, yz, zw, wx, xz, yw;
        T       xyz, yzw, zwx, wxy;
        T       xyzw;
        
        constexpr Multivector4() noexcept = default;
        constexpr Multivector4(
            T _a, 
            T _x, T _y, T _z, T _w,
            T _xy, T _yz, T _zw, T _wx, T _xz, T _yw,
            T _xyz, T _yzw, T _zwx, T _wxy,
            T _xyzw
        ) noexcept : 
            a(_a), 
            x(_x), y(_y), z(_z), w(_w),
            xy(_xy), yz(_yz), zw(_zw), wx(_wx), xz(_xz), yw(_yw),
            xyz(_xyz), yzw(_yzw), zwx(_zwx), wxy(_wxy),
            xyzw(_xyzw) {}
        constexpr Multivector4(T _a, const Vector4<T>& v, const Bivector4<T>& b, const Trivector4<T>& t, const Quadvector4<T>&q) noexcept : 
            a(_a), 
            x(v.x), y(v.y), z(v.z), w(v.w),
            xy(b.xy), yz(b.yz), zw(b.zw), wx(b.wx), xz(b.xz), yw(b.yw),
            xyz(t.xyz), yzw(t.yzw), zwx(t.zwx), wxy(t.wxy),
            xyzw(q.xyzw) {}
        constexpr Multivector4(all_t, T v) noexcept : 
            a(v), 
            x(v), y(v), z(v), 
            xy(v), yz(v), zw(v), wx(v), xz(v), yw(v),
            xyz(v), yzw(v), zwx(v), wxy(v),
            xyzw(v) {}
        template <typename=void> requires trait::has_nan_v<T>
        consteval Multivector4(nan_t) noexcept : Multivector4(ALL, nan_v<T>) {}
        consteval Multivector4(one_t) noexcept : Multivector4(ALL, one_v<T>) {}
        consteval Multivector4(zero_t) noexcept : Multivector4(ALL, zero_v<T>) {}

        //! Equality (defaulted) 
        constexpr bool operator==(const Multivector4&) const noexcept = default;
    };

    YQ_IEEE754_1(Multivector4)

//  --------------------------------------------------------
//  COMPOSITION

    YQ_NAN_1(Multivector4, Multivector4<T>(NAN))
    YQ_ZERO_1(Multivector4, Multivector4<T>(ZERO))

//  --------------------------------------------------------
//  GETTERS

    /*! \brief Extracts the bivector component from the multivector
    */
    template <typename T>
    constexpr Bivector4<T> bivector(const Multivector4<T>& a) noexcept
    {
        return { a.xy, a.yz, a.zw, a.wx, a.xz, a.yw };
    }

    /*! \brief Extracts the quadvector component from the multivector
    */
    template <typename T>
    constexpr Quadvector4<T> quadvector(const Multivector4<T>& a) noexcept
    {
        return { a.xyzw };
    }

    /*! \brief Extracts the trivector component from the multivector
    */
    template <typename T>
    constexpr Trivector4<T> trivector(const Multivector4<T>& a) noexcept
    {
        return { a.xyz, a.yzw, a.zwx, a.wxy };
    }

    /*! \brief Extracts the vector component from the multivector
    */
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

    /*! \brief Affirmation operator
    */
    template <typename T>
    constexpr Multivector4<T> operator+(const Multivector4<T>& a) noexcept
    {
        return a;
    }

//  --------------------------------------------------------
//  NEGATIVE

    /*! Negation operator
    */
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




    /*! Multivector/Bivector addition
    */
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

    /*! Multivector/Bivector self-addition
    */
    template <typename T>
    Multivector4<T>& operator+=(Multivector4<T>& a, const Bivector4<T>& b) noexcept
    {
        a.xy+=b.xy; a.yz+=b.yz; a.zw+=b.zw; a.wx+=b.wx; a.xz+=b.xz; a.yw+=b.yw;
        return a;
    }
    
    /*! Multivector/Multivector addition
    */
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

    /*! Multivector/Multivector self addition
    */
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

    /*! Multivector/quadvector addition
    */
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

    /*! Multivector/quadvector self addition
    */
    template <typename T>
    Multivector4<T>& operator+=(Multivector4<T>& a, const Quadvector4<T>& b) noexcept
    {
        a.xyzw += b.xyzw;
        return a;
    }
    
    /*! Multivector/trivector addition
    */
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

    /*! Multivector/trivector self-addition
    */
    template <typename T>
    Multivector4<T>& operator+=(Multivector4<T>& a, const Trivector4<T>& b) noexcept
    {
        a.xyz+=b.xyz; a.yzw+=b.yzw; a.zwx+=b.zwx; a.wxy+=b.wxy;
        return a;
    }
    
    /*! Multivector/scalar addition
    */
    template <typename T>
    constexpr Multivector4<T> operator+(const Multivector4<T>& a, T  b) noexcept
    {
        return {
            a.a+b,
            a.x, a.y, a.z, a.w,
            a.xy, a.yz, a.zw, a.wx, a.xz, a.yw, 
            a.xyz, a.yzw, a.zwx, a.wxy, 
            a.xyzw
        };
    }
    
    /*! Multivector/scalar self addition
    */
    template <typename T>
    Multivector4<T>& operator+=(Multivector4<T>& a, T  b) noexcept
    {
        a.a += b;
        return a;
    }

    /*! Multivector/vector addition
    */
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

    /*! Multivector/vector self addition
    */
    template <typename T>
    Multivector4<T>& operator+=(Multivector4<T>& a, const Vector4<T>& b) noexcept
    {
        a.x += b.x; a.y += b.y; a.z += b.z; a.w += b.w;
        return a;
    }



    /*! scalar/multivector addition
    */
    template <typename T>
    constexpr Multivector4<T> operator+(T a, const Multivector4<T>& b) noexcept
    {
        return { 
            a+b.a, 
            b.x, b.y, b.z, b.w,
            b.xy, b.yz, b.zw, b.wx, b.xz, b.yw,
            b.xyz, b.yzw, b.zwx, b.wxy,
            b.xyzw
        };
    }

//  --------------------------------------------------------
//  SUBTRACTION



    /*! Multivector/bivector subtraction
    */
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

    /*! Multivector/bivector self subtraction
    */
    template <typename T>
    Multivector4<T>& operator-=(Multivector4<T>& a, const Bivector4<T>& b) noexcept
    {
        a.xy-=b.xy; a.yz-=b.yz; a.zw-=b.zw; a.wx-=b.wx; a.xz-=b.xz; a.yw-=b.yw;
        return a;
    }
    
    /*! Multivector/multivector subtraction
    */
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

    /*! Multivector/multivector self subtraction
    */
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

    /*! Multivector/quadvector subtraction
    */
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

    /*! Multivector/quadvector self-subtraction
    */
    template <typename T>
    Multivector4<T>& operator-=(Multivector4<T>& a, const Quadvector4<T>& b) noexcept
    {
        a.xyzw -= b.xyzw;
        return a;
    }
    
    /*! Multivector/trivector subtraction
    */
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

    /*! Multivector/trivector self subtraction
    */
    template <typename T>
    Multivector4<T>& operator-=(Multivector4<T>& a, const Trivector4<T>& b) noexcept
    {
        a.xyz-=b.xyz; a.yzw-=b.yzw; a.zwx-=b.zwx; a.wxy-=b.wxy;
        return a;
    }
        
    /*! Multivector/scalar subtraction
    */
    template <typename T>
    constexpr Multivector4<T> operator-(const Multivector4<T>& a, T b) noexcept
    {
        return {
            a.a-b,
            a.x, a.y, a.z, a.w,
            a.xy, a.yz, a.zw, a.wx, a.xz, a.yw, 
            a.xyz, a.yzw, a.zwx, a.wxy, 
            a.xyzw
        };
    }

    /*! Multivector/scalar self subtraction
    */
    template <typename T>
    Multivector4<T>& operator-=(Multivector4<T>& a, T b) noexcept
    {
        a.a -= b;
        return a;
    }

    /*! Multivector/vector subtraction
    */
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

    /*! Multivector/vector self subtraction
    */
    template <typename T>
    Multivector4<T>& operator-=(Multivector4<T>& a, const Vector4<T>& b) noexcept
    {
        a.x -= b.x; a.y -= b.y; a.z -= b.z; a.w -= b.w;
        return a;
    }




    /*! Scalar/multivector subtraction
    */
    template <typename T>
    constexpr Multivector4<T> operator-(T a, const Multivector4<T>& b) noexcept
    {
        return { 
            a-b.a, 
            -b.x, -b.y, -b.z, -b.w,
            -b.xy, -b.yz, -b.zw, -b.wx, -b.xz, -b.yw,
            -b.xyz, -b.yzw, -b.zwx, -b.wxy,
            -b.xyzw
        };
    }


//  --------------------------------------------------------
//  MULTIPLICATION

    /*! Scalar/multivector multiplication
    */
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

    /*! Multivector/Scalar multiplication
    */
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

    /*! Multivector/Scalar self-multiplication
    */
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

//  --------------------------------------------------------
//  DIVISION

    /*! Multivector/Scalar division
    */
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

    /*! Multivector/Scalar self-division
    */
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

