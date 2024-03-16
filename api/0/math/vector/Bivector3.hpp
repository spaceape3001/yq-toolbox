////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_BIVECTOR3_HPP 1

#include <0/math/preamble.hpp>

namespace yq {

    /*! \brief 3D Bivector
    
        Bivector in the three dimensional case.
    */
    template <typename T>
    struct Bivector3 {

        //! Component type
        using component_type = T;
        
        //! XY component
        T     xy;

        //! YZ component
        T     yz;

        //! ZX component
        T     zx;

        //! Default constructor
        constexpr Bivector3() noexcept = default;
        
        //! Component wise constructor
        constexpr Bivector3(T _xy, T _yz, T _zx) noexcept : xy(_xy), yz(_yz), zx(_zx) {}
        
        //! Constructs all component to same value
        constexpr Bivector3(all_t, T v) noexcept : xy(v), yz(v), zx(v) {}
        
        //! Constructs to NaN
        consteval Bivector3(nan_t) noexcept : Bivector3(ALL, nan_v<T>) {}

        //! Constructs to all ones
        consteval Bivector3(one_t) noexcept : Bivector3(ALL, one_v<T>) {}
        
        //! Constructs a bivector with the XY component set as given
        constexpr Bivector3(xy_t, T v) noexcept : xy(v), yz(zero_v<T>), zx(zero_v<T>) {}
        
        //! Constructs a unit bivector in the XY component
        consteval Bivector3(xy_t) noexcept : Bivector3(XY, one_v<T>) {}
        
        //! Constructs a bivector with the YZ component set as given
        constexpr Bivector3(yz_t, T v) noexcept : xy(zero_v<T>), yz(v), zx(zero_v<T>) {}

        //! Constructs a unit bivector in the YZ component
        consteval Bivector3(yz_t) noexcept : Bivector3(YZ, one_v<T>) {}
        constexpr Bivector3(zx_t, T v) noexcept : xy(zero_v<T>), yz(zero_v<T>), zx(v) {}
        consteval Bivector3(zx_t) noexcept : Bivector3(ZX, one_v<T>) {}
        consteval Bivector3(zero_t) noexcept : Bivector3(ALL, zero_v<T>) {}

        template <typename U>
        requires std::is_nothrow_convertible_v<T,U>
        explicit constexpr operator Bivector3<U>() const noexcept
        {
            return { (U) xy, (U) yz, (U) zx };
        }
        
        template <typename U>
        requires (std::is_convertible_v<T,U> && !std::is_nothrow_convertible_v<T,U>)
        explicit constexpr operator Bivector3<U>() const 
        {
            return { (U) xy, (U) yz, (U) zx };
        }
        
        //! Defaulted comparison operator
        constexpr bool operator==(const Bivector3&) const noexcept = default;

        constexpr Bivector3         operator+() const noexcept;
        constexpr Bivector3         operator-() const noexcept;

        constexpr Multivector3<T>   operator+(T b) const noexcept;
        constexpr Bivector3         operator+(const Bivector3& b) const noexcept;
        Bivector3&                  operator+=(const Bivector3&b) noexcept;
        constexpr Multivector3<T>   operator+(const Multivector3<T>& b) const noexcept;
        constexpr Multivector3<T>   operator+(const Trivector3<T>& b) const noexcept;
        constexpr Multivector3<T>   operator+(const Vector3<T>& b) const noexcept;

        constexpr Multivector3<T>   operator-(T b) const noexcept;
        constexpr Bivector3         operator-(const Bivector3& b) const noexcept;
        Bivector3&                  operator-=(const Bivector3&b) noexcept;
        constexpr Multivector3<T>   operator-(const Multivector3<T>& b) const noexcept;
        constexpr Multivector3<T>   operator-(const Trivector3<T>& b) const noexcept;
        constexpr Multivector3<T>   operator-(const Vector3<T>& b) const noexcept;

        template <typename U>
        requires is_arithmetic_v<U>
        Bivector3<product_t<T,U>> operator*(U b) const noexcept;
        
        template <typename U>
        requires (is_arithmetic_v<U> && self_mul_v<T,U>)
        Bivector3<product_t<T,U>>& operator*=(U b) noexcept;
        
        template <typename U>
        requires is_arithmetic_v<T>
        Bivector3<quotient_t<T,U>> operator/(U b) const noexcept;
        
        template <typename U>
        requires (is_arithmetic_v<T> && self_div_v<T,U>)
        Bivector3& operator/=(U b) noexcept;

    };

    YQ_INTEGER_1(Bivector3)
    YQ_IS_INTEGER_1(Bivector3)
    YQ_IEEE754_1(Bivector3)

//  --------------------------------------------------------
//  COMPOSITION

    
    /*! \brief Literal constructor
    */
    constexpr Bivector3D   operator "" _xy3(unsigned long long int v) noexcept
    {
        return Bivector3D(XY, (double) v);
    }

    /*! \brief Literal constructor
    */
    constexpr Bivector3D   operator "" _xy3(long double v) noexcept
    {
        return Bivector3D(XY, (double) v);
    }

    /*! \brief Literal constructor
    */
    constexpr Bivector3D   operator "" _yz3(unsigned long long int v) noexcept
    {
        return Bivector3D(YZ, (double) v);
    }

    /*! \brief Literal constructor
    */
    constexpr Bivector3D   operator "" _yz3(long double v) noexcept
    {
        return Bivector3D(YZ, (double) v);
    }

    /*! \brief Literal constructor
    */
    constexpr Bivector3D   operator "" _zx3(unsigned long long int v) noexcept
    {
        return Bivector3D(ZX, (double) v);
    }

    /*! \brief Literal constructor
    */
    constexpr Bivector3D   operator "" _zx3(long double v) noexcept
    {
        return Bivector3D(ZX, (double) v);
    }

    YQ_NAN_1(Bivector3, Bivector3<T>{nan_v<square_t<T>>, nan_v<square_t<T>>, nan_v<square_t<T>>})
    YQ_ZERO_1(Bivector3, Bivector3<T>{zero_v<square_t<T>>, zero_v<square_t<T>>, zero_v<square_t<T>>})

//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_NAN_1(Bivector3, is_nan(v.xy) || is_nan(v.yz) || is_nan(v.zx))
    YQ_IS_FINITE_1(Bivector3, is_finite(v.xy) && is_finite(v.yz) && is_finite(v.zx))


//  --------------------------------------------------------
//  --------------------------------------------------------

template <typename T>
    constexpr Multivector3<T> operator+(T a, const Bivector3<T>& b) noexcept;

    template <typename T>
    constexpr Multivector3<T> operator-(T a, const Bivector3<T>& b) noexcept;
    
    template <typename T, typename U>
    requires is_arithmetic_v<T>
    Bivector3<product_t<T,U>> operator*(T a, const Bivector3<U>& b) noexcept;
    
}

YQ_TYPE_DECLARE(yq::Bivector3D)
YQ_TYPE_DECLARE(yq::Bivector3F)

