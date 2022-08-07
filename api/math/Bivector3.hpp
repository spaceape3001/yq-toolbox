////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>

namespace yq {

    /*! \brief 3D Bivector
    
        Bivector in the three dimensional case.
    */
    template <typename T>
    struct Bivector3 {
        using component_type = T;
        square_t<T>     xy, yz, zx;
        bool operator==(const Bivector3&) const noexcept = default;
    };

    YQ_IEEE754_1(Bivector3)

//  --------------------------------------------------------
//  COMPOSITION

    
    constexpr Bivector3D   operator "" _xy3(unsigned long long int v) noexcept
    {
        return {(double) v, 0., 0.};
    }

    constexpr Bivector3D   operator "" _xy3(long double v) noexcept
    {
        return {(double) v, 0., 0.};
    }

    constexpr Bivector3D   operator "" _yz3(unsigned long long int v) noexcept
    {
        return {0., (double) v,  0.};
    }

    constexpr Bivector3D   operator "" _xz3(long double v) noexcept
    {
        return {0., (double) v, 0.};
    }

    constexpr Bivector3D   operator "" _zx3(unsigned long long int v) noexcept
    {
        return {0., 0., (double) v};
    }

    constexpr Bivector3D   operator "" _zx3(long double v) noexcept
    {
        return {0., 0., (double) v};
    }

    YQ_NAN_1(Bivector3, Bivector3<T>{nan_v<square_t<T>>, nan_v<square_t<T>>, nan_v<square_t<T>>})
    YQ_ZERO_1(Bivector3, Bivector3<T>{zero_v<square_t<T>>, zero_v<square_t<T>>, zero_v<square_t<T>>})

//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_NAN_1(Bivector3, is_nan(v.xy) || is_nan(v.yz) || is_nan(v.zx))
    YQ_IS_FINITE_1(Bivector3, is_finite(v.xy) && is_finite(v.yz) && is_finite(v.zx))


//  --------------------------------------------------------
//  POSITIVE

    template <typename T>
    constexpr Bivector3<T> operator+(const Bivector3<T>& a) noexcept
    {
        return a;
    }

//  --------------------------------------------------------
//  NEGATIVE

    template <typename T>
    constexpr Bivector3<T> operator-(const Bivector3<T>& a) noexcept
    {
        return {-a.xy, -a.yz, -a.zx};
    }

//  --------------------------------------------------------
//  NORMALIZATION


//  --------------------------------------------------------
//  ADDITION

    template <typename T>
    constexpr Bivector3<T> operator+(const Bivector3<T>& a, const Bivector3<T>& b) noexcept
    {
        return {a.xy+b.xy, a.yz+b.yz, a.zx+b.zx};
    }

    template <typename T>
    Bivector3<T>&       operator+=(Bivector3<T>&a, const Bivector3<T>&b) noexcept
    {
        a.xy+=b.xy; a.yz+=b.yz; a.zx+=b.zx;
        return a;
    }


//  --------------------------------------------------------
//  SUBTRACTION


    template <typename T>
    constexpr Bivector3<T> operator-(const Bivector3<T>& a, const Bivector3<T>& b) noexcept
    {
        return {a.xy-b.xy, a.yz-b.yz, a.zx-b.zx};
    }

    template <typename T>
    Bivector3<T>&       operator-=(Bivector3<T>&a, const Bivector3<T>&b) noexcept
    {
        a.xy-=b.xy; a.yz-=b.yz; a.zx-=b.zx;
        return a;
    }

//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T>
    requires std::is_floating_point_v<T>
    Bivector3<T> operator*(T a, const Bivector3<T>& b) noexcept
    {
        return { a*b.xy, a*b.yz, a*b.zx };
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    Bivector3<T> operator*(const Bivector3<T>& a, T  b) noexcept
    {
        return { a.xy*b, a.yz*b, a.zx*b };
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    Bivector3<T>& operator*=(Bivector3<T>& a, T  b) noexcept
    {
        a.xy*=b, a.yz*=b, a.zx*=b;
        return a;
    }

//  --------------------------------------------------------
//  DIVISION

    template <typename T>
    requires std::is_floating_point_v<T>
    Bivector3<T> operator/(const Bivector3<T>& a, T  b) noexcept
    {
        return { a.xy/b, a.yz/b, a.zx/b };
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    Bivector3<T>& operator/=(Bivector3<T>& a, T  b) noexcept
    {
        a.xy/=b, a.yz/=b, a.zx/=b;
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

    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Bivector3<T> operator OUTER (const Vector3<T>&a, const Vector3<T>& b) noexcept
    {
        return { a.x*b.y-a.y*b.x, a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z };
    }

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

YQ_TYPE_DECLARE(yq::Bivector3D)
YQ_TYPE_DECLARE(yq::Bivector3F)

