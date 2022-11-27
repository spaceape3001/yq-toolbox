////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>

namespace yq {
    /*! \brief Four dimensional bivector
    
        Bivector for four dimensions.
    */
    template <typename T>
    struct Bivector4 {
        using component_type = T;
        square_t<T>     xy, yz, zw, wx, xz, yw;
        bool operator==(const Bivector4&) const noexcept = default;
    };
    
    YQ_IEEE754_1(Bivector4)


//  --------------------------------------------------------
//  COMPOSITION

    constexpr Bivector4D   operator "" _xy4(unsigned long long int v) noexcept
    {
        return {(double) v, 0., 0., 0., 0., 0.};
    }

    constexpr Bivector4D   operator "" _xy4(long double v) noexcept
    {
        return {(double) v, 0., 0., 0., 0., 0.};
    }

    constexpr Bivector4D   operator "" _yz4(unsigned long long int v) noexcept
    {
        return {0., (double) v,  0., 0., 0., 0.}; 
    }

    constexpr Bivector4D   operator "" _yz4(long double v) noexcept
    {
        return {0., (double) v, 0., 0., 0., 0.};
    }

    constexpr Bivector4D   operator "" _zw4(unsigned long long int v) noexcept
    {
        return {0., 0., (double) v,  0., 0., 0.};
    }

    constexpr Bivector4D   operator "" _xw4(long double v) noexcept
    {
        return {0., 0., (double) v, 0., 0., 0.};
    }

    constexpr Bivector4D   operator "" _wx4(unsigned long long int v) noexcept
    {
        return {0., 0., 0., (double) v,  0., 0. };
    }

    constexpr Bivector4D   operator "" _wx4(long double v) noexcept
    {
        return {0., 0., 0., (double) v, 0., 0.};
    }

    constexpr Bivector4D   operator "" _xz4(unsigned long long int v) noexcept
    {
        return {0., 0., 0., 0., (double) v,  0. };
    }

    constexpr Bivector4D   operator "" _xz4(long double v) noexcept
    {
        return {0., 0., 0., 0., (double) v,  0.};
    }

    constexpr Bivector4D   operator "" _yw4(unsigned long long int v) noexcept
    {
        return {0., 0., 0., 0., 0., (double) v};
    }

    constexpr Bivector4D   operator "" _yw4(long double v) noexcept
    {
        return {0., 0., 0., 0., 0., (double) v};
    }
    
    YQ_NAN_1(Bivector4, Bivector4<T>{
        nan_v<square_t<T>>, nan_v<square_t<T>>, nan_v<square_t<T>>, 
        nan_v<square_t<T>>, nan_v<square_t<T>>, nan_v<square_t<T>>
    })
    YQ_ZERO_1(Bivector4, Bivector4<T>{
        zero_v<square_t<T>>, zero_v<square_t<T>>, zero_v<square_t<T>>,
        zero_v<square_t<T>>, zero_v<square_t<T>>, zero_v<square_t<T>>
    })

//  --------------------------------------------------------
//  BASIC FUNCTIONS
    
    YQ_IS_NAN_1(Bivector4, 
        is_nan(v.xy) || is_nan(v.yz) || is_nan(v.zw) || 
        is_nan(v.wx) || is_nan(v.xz) || is_nan(v.yw)
    )
    YQ_IS_FINITE_1(Bivector4, 
        is_finite(v.xy) && is_finite(v.yz) && is_finite(v.zw) && 
        is_finite(v.wx) && is_finite(v.xz) && is_finite(v.yw)
    )


//  --------------------------------------------------------
//  POSITIVE

    template <typename T>
    constexpr Bivector4<T> operator+(const Bivector4<T>& a) noexcept
    {
        return a;
    }

//  --------------------------------------------------------
//  NEGATIVE

    template <typename T>
    constexpr Bivector4<T> operator-(const Bivector4<T>& a) noexcept
    {
        return {-a.xy, -a.yz, -a.zw, -a.wx, -a.xz, -a.yw};
    }


//  --------------------------------------------------------
//  NORMALIZATION


//  --------------------------------------------------------
//  ADDITION

    template <typename T>
    constexpr Bivector4<T> operator+(const Bivector4<T>& a, const Bivector4<T>& b) noexcept
    {
        return {a.xy+b.xy, a.yz+b.yz, a.zw+b.zw, a.wx+b.wx, a.xz+b.xz, a.yw+b.yw};
    }

    template <typename T>
    Bivector4<T>&       operator+=(Bivector4<T>&a, const Bivector4<T>&b) noexcept
    {
        a.xy+=b.xy; a.yz+=b.yz; a.zw+=b.zw; a.wx+=b.wx; a.xz+=b.xz; a.yw+=b.yw;
        return a;
    }

//  --------------------------------------------------------
//  SUBTRACTION

    template <typename T>
    constexpr Bivector4<T> operator-(const Bivector4<T>& a, const Bivector4<T>& b) noexcept
    {
        return {a.xy-b.xy, a.yz-b.yz, a.zw-b.zw, a.wx-b.wx, a.xz-b.xz, a.yw-b.yw};
    }

    template <typename T>
    Bivector4<T>&       operator-=(Bivector4<T>&a, const Bivector4<T>&b) noexcept
    {
        a.xy-=b.xy; a.yz-=b.yz; a.zw-=b.zw; a.wx-=b.wx; a.xz-=b.xz; a.yw-=b.yw;
        return a;
    }

//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Bivector4<T> operator*(T a, const Bivector4<T>& b) noexcept
    {
        return { a*b.xy, a*b.yz, a*b.zw, a*b.wx, a*b.xz, a*b.yw };
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Bivector4<T> operator*(const Bivector4<T>& a, T b) noexcept
    {
        return { a.xy*b, a.yz*b, a.zw*b, a.wx*b, a.xz*b, a.yw*b };
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    Bivector4<T>& operator*=(Bivector4<T>& a, T b) noexcept
    {
        a.xy*=b, a.yz*=b, a.zw*=b, a.wx*=b, a.xz*=b, a.yw*=b;
        return a;
    }


//  --------------------------------------------------------
//  DIVISION

    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Bivector4<T> operator/(const Bivector4<T>& a, T b) noexcept
    {
        return { a.xy/b, a.yz/b, a.zw/b, a.wx/b, a.xz/b, a.yw/b };
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    Bivector4<T>& operator/=(Bivector4<T>& a, T b) noexcept
    {
        a.xy/=b, a.yz/=b, a.zw/=b, a.wx/=b, a.xz/=b, a.yw/=b;
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
    constexpr Bivector4<T> operator OUTER (const Vector4<T>&a, const Vector4<T>& b) noexcept
    {
        return { a.x*b.y-a.y*b.x, a.y*b.z-a.z*b.y, a.z*b.w-a.w*b.z, a.w*b.x-a.x*b.w, a.x*b.z-a.z*b.x, a.y*b.w-a.w*b.y };
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

YQ_TYPE_DECLARE(yq::Bivector4D)
YQ_TYPE_DECLARE(yq::Bivector4F)

