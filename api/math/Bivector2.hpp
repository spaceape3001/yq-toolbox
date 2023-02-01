////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>

namespace yq {
    /*! \brief 2D Bivector
    
        Two dimensional bivector
    */
    template <typename T>
    struct Bivector2 {
    
        //! Component type
        using component_type = T;
        
        //! The value... since it's a unit area, square of T
        T               xy;
        
        constexpr Bivector2() noexcept = default;
        constexpr Bivector2(T _xy) noexcept : xy(_xy) {}
        constexpr Bivector2(all_t, T v) noexcept : xy(v) {}
        consteval Bivector2(nan_t) noexcept : Bivector2(ALL, nan_v<T>) {}
        consteval Bivector2(one_t) noexcept : Bivector2(ALL, one_v<T>) {}
        constexpr Bivector2(xy_t, T v) noexcept : xy(v) {}
        consteval Bivector2(xy_t) noexcept : Bivector2(XY, one_v<T>) {}
        consteval Bivector2(zero_t) noexcept : Bivector2(ALL, zero_v<T>) {}
        
        
        //! Defaulted comparison operator
        constexpr auto operator<=>(const Bivector2&) const noexcept = default;
        
        /*! \brief Affirmation (positive) operator
        
            \note Here to complement the negation operator
        */
        constexpr Bivector2 operator+() const noexcept;

        /*! \brief Negation operator of a bivector
        */
        constexpr Bivector2 operator-() const noexcept;
        
        constexpr Multivector2<T> operator+(T b) const noexcept;
        constexpr Bivector2<T> operator+(const Bivector2<T>& b) const noexcept;
        Bivector2<T>& operator+=(const Bivector2<T>& b) noexcept;
        constexpr Multivector2<T> operator+(const Multivector2<T>& b) const noexcept;
        constexpr Multivector2<T> operator+(const Vector2<T>& b) const noexcept;

        constexpr Multivector2<T> operator-(T b) const noexcept;
        constexpr Bivector2<T> operator-( const Bivector2<T>& b) const noexcept;
        Bivector2<T>& operator-=(const Bivector2<T>& b) noexcept;
        constexpr Multivector2<T> operator-(const Multivector2<T>& b) const noexcept;
        constexpr Multivector2<T> operator-(const Vector2<T>& b) const noexcept;

        template <typename U>
        requires trait::is_arithmetic_v<U>
        constexpr Bivector2<product_t<T,U>> operator*(U b) const noexcept;

        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
        Bivector2<T>& operator*=(U b) noexcept;

        template <typename U>
        requires trait::is_arithmetic_v<T>
        constexpr Bivector2<quotient_t<T,U>> operator/(U b) noexcept;

        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_div_v<T,U>)
        Bivector2<T>& operator/=(U b) noexcept;
    };

    YQ_IEEE754_1(Bivector2)

//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Literal constructor
    */
    constexpr Bivector2D  operator "" _xy2(unsigned long long int v) noexcept
    {
        return Bivector2D(XY, (double) v);
    }

    /*! \brief Literal constructor
    */
    constexpr Bivector2D  operator "" _xy2(long double v) noexcept
    {
        return Bivector2D(XY, (double) v);
    }

    
    YQ_NAN_1(Bivector2, Bivector2<T>(NAN))
    YQ_ZERO_1(Bivector2, Bivector2<T>(ZERO))
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_NAN_1(Bivector2, is_nan(v.xy))
    YQ_IS_FINITE_1(Bivector2, is_finite(v.xy))


//  --------------------------------------------------------
//  --------------------------------------------------------

    template <typename T>
    constexpr Multivector2<T> operator+(T a, const Bivector2<T>& b) noexcept;

    template <typename T>
    constexpr Multivector2<T> operator-(T a, const Bivector2<T>& b) noexcept;

    /*! \brief Scaling multiplication operator
    
        \note currently limited to floating points due to uncertainty 
    */
    template <typename T, typename U>
    requires trait::is_arithmetic_v<T>
    constexpr Bivector2<product_t<T,U>> operator*(T a, const Bivector2<U>& b) noexcept;


}

YQ_TYPE_DECLARE(yq::Bivector2D)
YQ_TYPE_DECLARE(yq::Bivector2F)

