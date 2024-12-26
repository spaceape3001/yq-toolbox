////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_CYLINDRICAL3_HPP 1

#include <yq/keywords.hpp>
#include <yq/meta/InfoBinder.hpp>
#include <yq/trait/has_nan.hpp>
#include <yq/trait/has_one.hpp>
#include <yq/trait/has_zero.hpp>
#include <yq/trait/is_arithmetic.hpp>
#include <yq/trait/is_floating_point.hpp>
#include <yq/trait/product.hpp>
#include <yq/trait/quotient.hpp>
#include <yq/trait/self_divide.hpp>
#include <yq/trait/self_multiply.hpp>
#include <yq/typedef/cylindrical3.hpp>

namespace yq {
    template <typename> struct Vector3;

    /*! \brief Cylindrical coordinates
    
        This is a polar coordinate container, assumes the rotation is 
        euler convention (ie, starts at +x, swings through +y, and cycles back around).
    */
    template <typename A, typename L>
    struct Cylindrical3 {
        static_assert(is_floating_point_v<A> && is_floating_point_v<L>);
        //static_assert(has_sqrt_v<square_t<L>>, "Basically needs trig too");

        //! Angular data
        A       angle;
        
        //! Radian data
        L       radius;
        
        //! Z data
        L       z;
        
        //! Default constructor
        constexpr Cylindrical3() noexcept = default;
        
        //! Component consturctor
        constexpr Cylindrical3(A _a, L _d, L _z) noexcept : angle(_a), radius(_d), z(_z) {};

        //! Not a number constructor
        template <typename=void> requires (has_nan_v<A> && has_nan_v<L>)
        consteval Cylindrical3(nan_t) noexcept : angle(nan_v<A>), radius(nan_v<L>), z(nan_v<L>) {}

        //! Constructs to a unit size in each coordinate
        consteval Cylindrical3(unit_t) noexcept : angle(zero_v<A>), radius(one_v<L>), z(one_v<L>) {}
        
        //! Constructs to a zero
        consteval Cylindrical3(zero_k) noexcept : angle(zero_v<A>), radius(zero_v<L>), z(zero_v<L>) {}

        //! Creates a polar assuming euler convention
        Cylindrical3(const Vector3<L>&);
        
        //! Creates a polar assuming clock convention
        Cylindrical3(clock_arg_t, const Vector3<L>&);
        //! Creates a polar assuming euler convention
        Cylindrical3(euler_t, const Vector3<L>&);
        
        //! Converts to a L-based 3D vector
        operator Vector3<L> () const;
        
        //! Constructs a L-based 3D vector using angle as clockwise
        Vector3<L>  operator()(clock_arg_t) const;
        
        //! Constructs a L-based 3D vector using angle as counter-clockwise
        Vector3<L>  operator()(euler_t) const;

        //! Converts to a vector assuming this polar represents a clock angle
        Vector3<L>  to_clock() const;
        
        //! Converts to a vector assuming this polar is a typical euler rotation (the default)
        Vector3<L>  to_euler() const;
        
        //! Equality operator
        constexpr bool    operator==(const Cylindrical3&) const noexcept = default;
        
        constexpr Cylindrical3    operator+() const noexcept;
        Cylindrical3    operator-() const;
        
        Cylindrical3 operator+(const Cylindrical3&) const;
        Cylindrical3& operator+=(const Cylindrical3&);
        Cylindrical3 operator-(const Cylindrical3&) const;
        Cylindrical3& operator-=(const Cylindrical3&);
        
        template <typename L2>
        requires is_arithmetic_v<L2>
        Cylindrical3<A, product_t<L,L2>> operator*(L2) const;
        
        template <typename L2>
        requires (is_arithmetic_v<L2> && self_multiply_v<L,L2>)
        Cylindrical3& operator *= (L2);

        template <typename L2>
        requires is_arithmetic_v<L2>
        Cylindrical3<A,quotient_t<L,L2>> operator/(L2) const;

        template <typename L2>
        requires (is_arithmetic_v<L2> && self_divide_v<L,L2>)
        Cylindrical3& operator /= (L2);
    };
    
    template <typename A, typename L1, typename L2>
    Cylindrical3<A,product_t<L1,L2>> operator*(L1, const Cylindrical3<A,L2>&);
    
}

YQ_TYPE_DECLARE(yq::Cylindrical3D)
YQ_TYPE_DECLARE(yq::Cylindrical3M)

