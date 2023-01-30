////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>
#include <math/Vector2.hpp>
#include <math/Bivector2.hpp>

namespace yq {

    /*! \brief Two dimensional multivector
    */
    template <typename T>
    struct Multivector2 {

        //! Captures the template parameter
        using component_type    = T;

        //! Scalar
        T               a;
        
        //! X (vector component)
        T               x;
        
        //! Y (vector component)
        T               y;
        
        //! XY (bivector component)
        T               xy;
        
        constexpr Multivector2() noexcept = default;
        constexpr Multivector2(T _a, T _x, T _y, T _xy) noexcept : a(_a), x(_x), y(_y), xy(_xy) {}
        constexpr Multivector2(T _a, const Vector2<T>& v, const Bivector2<T>& b) noexcept : a(_a), x(v.x), y(v.y), xy(b.xy) {}
        constexpr Multivector2(all_t, T v) noexcept : a(v), x(v), y(v), xy(v) {}
        consteval Multivector2(nan_t) noexcept : Multivector2(ALL, nan_v<T>) {}
        consteval Multivector2(one_t) noexcept : Multivector2(ALL, one_v<T>) {}
        consteval Multivector2(zero_t) noexcept : Multivector2(ALL, zero_v<T>) {}

        //! Defaulted equality operator
        constexpr bool operator==(const Multivector2&) const noexcept = default;

        constexpr Multivector2<T> operator+() const noexcept;
        constexpr Multivector2<T> operator-() const noexcept;
        
        constexpr Multivector2<T> operator+(T b) const noexcept;
        Multivector2<T>& operator+=(T b) noexcept;
        
        constexpr Multivector2<T> operator+(const Bivector2<T>& b) const noexcept;
        Multivector2<T>& operator+=(const Bivector2<T>& b) noexcept;
        
        constexpr Multivector2<T> operator+(const Multivector2<T>& b) const noexcept;
        Multivector2<T>& operator+=(const Multivector2<T>& b) noexcept;
        
        constexpr Multivector2<T> operator+(const Vector2<T>& b) const noexcept;
        Multivector2<T>& operator+=(const Vector2<T>& b) noexcept;

        constexpr Multivector2<T> operator-(T b) const noexcept;
        Multivector2<T>& operator-=(T b) noexcept;
        
        constexpr Multivector2<T> operator-(const Bivector2<T>& b) const noexcept;
        Multivector2<T>& operator-=(const Bivector2<T>& b) noexcept;
        
        constexpr Multivector2<T> operator-(const Multivector2<T>& b) const noexcept;
        Multivector2<T>& operator-=(const Multivector2<T>& b) noexcept;
        
        constexpr Multivector2<T> operator-(const Vector2<T>& b) const noexcept;
        Multivector2<T>& operator-=(const Vector2<T>& b) noexcept;
        
        template <typename U>
        requires trait::is_arithmetic_v<U>
        constexpr Multivector2<product_t<T,U>> operator*(U b) const noexcept;

        template <typename U>
        requires trait::is_arithmetic_v<U>
        Multivector2<T>& operator*=(U b) noexcept;

        template <typename U>
        requires trait::is_arithmetic_v<U>
        constexpr Multivector2<quotient_t<T,U>> operator/(U b) const noexcept;

        template <typename U>
        requires trait::is_arithmetic_v<U>
        Multivector2<T>& operator/=(U b) noexcept;

        constexpr Bivector2<T>  bivector() const noexcept;
        constexpr Vector2<T>    vector() const noexcept;
        
    };

    YQ_IEEE754_1(Multivector2)

//  --------------------------------------------------------
//  COMPOSITION

    YQ_NAN_1(Multivector2, Multivector2<T>{nan_v<unity_t<T>>, nan_v<T>, nan_v<T>, nan_v<square_t<T>>})
    YQ_ZERO_1(Multivector2, Multivector2<T>{zero_v<unity_t<T>>, zero_v<T>, zero_v<T>, zero_v<square_t<T>>})

//  --------------------------------------------------------
//  GETTERS

    //! Extracts the bivector part
    template <typename T>
    constexpr Bivector2<T> bivector(const Multivector2<T>& a) noexcept;

    //! Extracts the vector part
    template <typename T>
    constexpr Vector2<T> vector(const Multivector2<T>& a) noexcept;

//  --------------------------------------------------------
//  BASIC FUNCTIONS
    
    YQ_IS_NAN_1(Multivector2, is_nan(v.a) || is_nan(v.x) || is_nan(v.y) || is_nan(v.xy))
    YQ_IS_FINITE_1(Multivector2, is_finite(v.a) && is_finite(v.x) && is_finite(v.y) && is_finite(v.xy))


//  --------------------------------------------------------
//  --------------------------------------------------------

    template <typename T>
    constexpr Multivector2<T> operator+(T a, const Multivector2<T>& b) noexcept;


    template <typename T>
    constexpr Multivector2<T> operator-(T a, const Multivector2<T>& b) noexcept;


    
    template <typename T, typename U>
    requires trait::is_arithmetic_v<U>
    constexpr Multivector2<product_t<T,U>> operator*(T a, const Multivector2<U>&b) noexcept;

}

YQ_TYPE_DECLARE(Multivector2D)
YQ_TYPE_DECLARE(Multivector2F)
