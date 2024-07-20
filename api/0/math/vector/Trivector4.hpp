////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_TRIVECTOR4_HPP 1


#include <0/math/preamble.hpp>

namespace yq {
    /*! \brief 4D Tri-vector */
    template <typename T>
    struct Trivector4 {

        //! Component type
        using component_type = T;
        
        //! XYZ Component
        T     xyz;
        
        //! YZW Component
        T     yzw;
        
        //! ZWX Component
        T     zwx;
        
        //! WXY Component
        T     wxy;

        //! Default constructor
        constexpr Trivector4() noexcept = default;
        
        //! Component-wise constructor
        constexpr Trivector4(T _xyz, T _yzw, T _zwx, T _wxy) noexcept : xyz(_xyz), yzw(_yzw), zwx(_zwx), wxy(_wxy) {}
        
        //! Constructs all components to same value
        constexpr Trivector4(all_t, T v) noexcept : xyz(v), yzw(v), zwx(v), wxy(v) {}
        
        //! Constructs the trivector to not-a-number
        template <typename=void> requires has_nan_v<T>
        consteval Trivector4(nan_t) noexcept : Trivector4(ALL, nan_v<T>) {}
        
        //! Constructs the trivector to all ones
        consteval Trivector4(one_t) noexcept : Trivector4(ALL, one_v<T>) {}
        
        //! Constructs to the specified value in WXY component, all others zero
        constexpr Trivector4(wxy_t, T v) noexcept : xyz(zero_v<T>), yzw(zero_v<T>), zwx(zero_v<T>), wxy(v) {}
        
        //! Constructs to a unit trivector in the WXY component
        consteval Trivector4(wxy_t) noexcept : Trivector4(WXY, one_v<T>) {}
        
        //! Constructs to the specified value in XYZ component, all others zero
        constexpr Trivector4(xyz_t, T v) noexcept : xyz(v), yzw(zero_v<T>), zwx(zero_v<T>), wxy(zero_v<T>) {}
        
        //! Constructs to a unit trivector in the XYZ component
        consteval Trivector4(xyz_t) noexcept : Trivector4(XYZ, one_v<T>) {}
        
        //! Construct to the specified value in YZW component, all others zero
        constexpr Trivector4(yzw_t, T v) noexcept : xyz(zero_v<T>), yzw(v), zwx(zero_v<T>), wxy(zero_v<T>) {}
        
        //! Constructs to a unit trivector in the YZW component
        consteval Trivector4(yzw_t) noexcept : Trivector4(YZW, one_v<T>) {}
        
        //! Construct to the specified value in ZWX component, all others zero
        constexpr Trivector4(zwx_t, T v) noexcept : xyz(zero_v<T>), yzw(zero_v<T>), zwx(v), wxy(zero_v<T>) {}
        
        //! Constructs to a unit trivector in the ZWX component
        consteval Trivector4(zwx_t) noexcept : Trivector4(ZWX, one_v<T>) {}
        
        //! Constructs to a zero trivector
        consteval Trivector4(zero_t) noexcept : Trivector4(ALL, zero_v<T>) {}

        //! Converts to another trivector of compatible type
        template <typename U>
        requires std::is_nothrow_convertible_v<T,U>
        explicit constexpr operator Trivector4<U>() const noexcept
        {
            return { (U) xyz, (U) yzw, (U) zwx, (U) wxy };
        }
        
        //! Converts to another trivector of compatible type
        template <typename U>
        requires (std::is_convertible_v<T,U> && !std::is_nothrow_convertible_v<T,U>)
        explicit constexpr operator Trivector4<U>() const 
        {
            return { (U) xyz, (U) yzw, (U) zwx, (U) wxy };
        }

        //! Defaulted comparison operator
        constexpr bool operator==(const Trivector4&) const noexcept = default;

        /*! \brief Affirmation (positive) operator
        
            \note Here to complement the negation operator
        */
        constexpr Trivector4 operator+() const noexcept;

        /*! \brief Negation operator
        */
        constexpr Trivector4 operator-() const noexcept;

        //! Adds scalar to trivector, returns multivector
        constexpr Multivector4<T>   operator+(T b) const noexcept;
        
        //! Adds bivector to trivector, returns multivector
        constexpr Multivector4<T>   operator+(const Bivector4<T>& b) const noexcept;
        
        //! Adds multivector to trivector, returns multivector
        constexpr Multivector4<T>   operator+(const Multivector4<T>& b) const noexcept;
        
        //! Adds quadvector to trivector, returns multivector
        constexpr Multivector4<T>   operator+(const Quadvector4<T>& b) const noexcept;
        
        //! Adds trivector to this trivector, returns trivector
        constexpr Trivector4        operator+(const Trivector4& b) const noexcept;
        
        //! Self increments left trivector with the right hand term
        Trivector4&                 operator+=(const Trivector4& b) noexcept;
        
        //! Adds vector to this trivector, returns multivector
        constexpr Multivector4<T>   operator+(const Vector4<T>& b) const noexcept;

        constexpr Multivector4<T>   operator-(T b) const noexcept;
        constexpr Multivector4<T>   operator-(const Bivector4<T>& b) const noexcept;
        constexpr Multivector4<T>   operator-(const Multivector4<T>& b) const noexcept;
        constexpr Multivector4<T>   operator-(const Quadvector4<T>& b) const noexcept;
        constexpr Trivector4        operator-(const Trivector4& b) const noexcept;
        Trivector4&                 operator-=(const Trivector4& b) noexcept;
        constexpr Multivector4<T>   operator-(const Vector4<T>& b) const noexcept;

        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Trivector4<product_t<T,U>> operator*(U b) const noexcept;

        template <typename U>
        requires (is_arithmetic_v<U> && self_mul_v<T,U>)
        Trivector4& operator*=(U b) noexcept;

        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Trivector4<quotient_t<T,U>> operator/(U b) const noexcept;

        template <typename U>
        requires (is_arithmetic_v<U> && self_div_v<T,U>)
        Trivector4& operator/=(U b) noexcept;
    };

    YQ_IEEE754_1(Trivector4)
    YQ_INTEGER_1(Trivector4)
    YQ_IS_INTEGER_1(Trivector4)


//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Literal to construct a trivector
    */
    constexpr Trivector4D   operator "" _xyz4(unsigned long long int v) noexcept
    {
        return Trivector4D(XYZ, (double) v);
    }

    /*! \brief Literal to construct a trivector
    */
    constexpr Trivector4D   operator "" _xyz4(long double v) noexcept
    {
        return Trivector4D(XYZ, (double) v);
    }

    /*! \brief Literal to construct a trivector
    */
    constexpr Trivector4D   operator "" _yzw4(unsigned long long int v) noexcept
    {
        return Trivector4D(YZW, (double) v);
    }

    /*! \brief Literal to construct a trivector
    */
    constexpr Trivector4D   operator "" _yzw4(long double v) noexcept
    {
        return Trivector4D(YZW, (double) v);
    }

    /*! \brief Literal to construct a trivector
    */
    constexpr Trivector4D   operator "" _zwx4(unsigned long long int v) noexcept
    {
        return Trivector4D(ZWX, (double) v);
    }

    /*! \brief Literal to construct a trivector
    */
    constexpr Trivector4D   operator "" _zwx4(long double v) noexcept
    {
        return Trivector4D(ZWX, (double) v);
    }

    /*! \brief Literal to construct a trivector
    */
    constexpr Trivector4D   operator "" _wxy4(unsigned long long int v) noexcept
    {
        return Trivector4D(WXY, (double) v);
    }

    /*! \brief Literal to construct a trivector
    */
    constexpr Trivector4D   operator "" _wxy4(long double v) noexcept
    {
        return Trivector4D(WXY, (double) v);
    }

    YQ_NAN_1(Trivector4, Trivector4<T>{nan_v<cube_t<T>>, nan_v<cube_t<T>>, nan_v<cube_t<T>>, nan_v<cube_t<T>>})
    YQ_ZERO_1(Trivector4, Trivector4<T>{zero_v<cube_t<T>>, nan_v<cube_t<T>>, nan_v<cube_t<T>>, nan_v<cube_t<T>>})
    

//  --------------------------------------------------------
//  GETTERS


//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_NAN_1(Trivector4, is_nan(v.xyz) || is_nan(v.yzw) || is_nan(v.zwx) || is_nan(v.wxy))
    YQ_IS_FINITE_1(Trivector4, is_finite(v.xyz) && is_finite(v.yzw) && is_finite(v.zwx) && is_finite(v.wxy))


//  --------------------------------------------------------
//  --------------------------------------------------------

    template <typename T>
    constexpr Multivector4<T> operator+(T a, const Trivector4<T>& b) noexcept;

    template <typename T>
    constexpr Multivector4<T> operator-(T a, const Trivector4<T>& b) noexcept;

    /*! \brief Scaling multiplication of trivector
    
        This will (scale) multiply a trivector, returns the result.
    */
    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Trivector4<product_t<T,U>> operator*(T a, const Trivector4<U>& b) noexcept;
}

YQ_TYPE_DECLARE(yq::Trivector4D)
YQ_TYPE_DECLARE(yq::Trivector4F)

