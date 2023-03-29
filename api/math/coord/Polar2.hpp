////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_POLAR2_HPP 1

#include <math/preamble.hpp>

namespace yq {
    /*! \brief Polar coordinates
    
        This is a polar coordinate container, assumes the rotation is 
        euler convention (ie, starts at +x, swings through +y, and cycles back around).
    */
    template <typename A, typename L>
    struct Polar2 {
        static_assert(has_sqrt_v<square_t<L>>, "Basically needs trig too");

        A       angle;
        L       radius;
        
        constexpr Polar2() noexcept = default;
        constexpr Polar2(A _a, L _d) noexcept : angle(_a), radius(_d) {};

        template <typename=void> requires (has_nan_v<A> && has_nan_v<L>)
        consteval Polar2(nan_t) noexcept : angle(nan_v<A>), radius(nan_v<L>) {}

        consteval Polar2(unit_t) noexcept : angle(zero_v<A>), radius(one_v<L>) {}
        consteval Polar2(zero_t) noexcept : angle(zero_v<A>), radius(zero_v<L>) {}

        //! Creates a polar assuming euler convention
        Polar2(const Vector2<L>&);
        //! Creates a polar assuming clock convention
        Polar2(clock_arg_t, const Vector2<L>&);
        //! Creates a polar assuming euler convention
        Polar2(euler_t, const Vector2<L>&);
        
        operator Vector2<L> () const;
        
        Vector2<L>  operator()(clock_arg_t) const;
        Vector2<L>  operator()(euler_t) const;

        //! Converts to a vector assuming this polar represents a clock angle
        Vector2<L>  to_clock() const;
        
        //! Converts to a vector assuming this polar is a typical euler rotation (the default)
        Vector2<L>  to_euler() const;
        
        constexpr bool    operator==(const Polar2&) const noexcept = default;
        
        constexpr Polar2    operator+() const noexcept;
        Polar2    operator-() const;
        
        Polar2 operator+(const Polar2&) const;
        Polar2& operator+=(const Polar2&);
        Polar2 operator-(const Polar2&) const;
        Polar2& operator-=(const Polar2&);
        
        template <typename L2>
        requires is_arithmetic_v<L2>
        Polar2<A, product_t<L,L2>> operator*(L2) const;
        
        template <typename L2>
        requires (is_arithmetic_v<L2> && self_mul_v<L,L2>)
        Polar2& operator *= (L2);

        template <typename L2>
        requires is_arithmetic_v<L2>
        Polar2<A,quotient_t<L,L2>> operator/(L2) const;

        template <typename L2>
        requires (is_arithmetic_v<L2> && self_div_v<L,L2>)
        Polar2& operator /= (L2);
    };
    
    template <typename A, typename L1, typename L2>
    Polar2<A,product_t<L1,L2>> operator*(L1, const Polar2<A,L2>&);
    
}
