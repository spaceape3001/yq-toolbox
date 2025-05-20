////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_SPINOR2_HPP 1

#include <yq/typedef/spinor2.hpp>
#include <yq/keywords.hpp>
#include <yq/meta/InfoBinder.hpp>
#include <yq/trait/has_identity.hpp>
#include <yq/trait/has_is_finite.hpp>
#include <yq/trait/has_nan.hpp>
#include <yq/trait/has_one.hpp>
#include <yq/trait/has_zero.hpp>
#include <yq/trait/ieee754.hpp>
#include <yq/trait/is_arithmetic.hpp>
#include <yq/trait/inverse.hpp>
#include <yq/trait/product.hpp>
#include <yq/trait/quotient.hpp>
#include <yq/trait/self_divide.hpp>
#include <yq/trait/self_multiply.hpp>
#include <yq/trait/square.hpp>
#include <yq/trait/unity.hpp>
#include <yq/unit/declare.hpp>
#include <yq/unit/dims.hpp>

namespace log4cpp { class CategoryStream; }

namespace yq {
    template <typename, typename> struct MKS;
    template <typename> struct Tensor22;
    template <typename> struct Vector2;
    class Stream;


    /*! \brief 2D Spiny thing, does rotations like spinors in 3D 
        
        \note  We're using "Z" as the other component, so it's like 3D in that respect
    */
    template <typename T>
    struct Spinor2 {
        //! Capture our template parameter for the component type
        using component_type = T;

        T w;    //!< W component
        T z;    //!< Z component

        constexpr Spinor2(){}

        //! Component wise constructor
        constexpr Spinor2(T _w, T _z) : w(_w), z(_z) {}
        
        //! Initializes to all components having the same value
        constexpr Spinor2(all_k, T v) : w(v), z(v) {}
        
        //! Initializes to an identity spinor
        consteval Spinor2(identity_k) : w(one_v<T>), z(zero_v<T>) {}
        
        //! Initializes all components to not-a-number
        consteval Spinor2(nan_k) : Spinor2(ALL, nan_v<T>) {}
        
        //! Initializes to a unit spinor in W (rest are zero)
        consteval Spinor2(w_k) noexcept : w(one_v<T>), z(zero_v<T>) {}
        
        //! Initializes to a single value on the W-component
        constexpr Spinor2(w_k, T v) noexcept :  w(v), z(zero_v<T>) {}
        
        //! Initializes to a unit spinor in Z
        consteval Spinor2(z_k) noexcept : w(zero_v<T>), z(one_v<T>) {}
        
        //! Initializes to a single value on the Z-component (rest are zero)
        constexpr Spinor2(z_k, T v) noexcept : w(zero_v<T>), z(v) {}
    
        //! Initializes to all zeros
        consteval Spinor2(zero_k) : Spinor2(ALL, zero_v<T>) {}

        template <typename=void>
        requires std::is_floating_point_v<T>
        Spinor2(ccw_k, MKS<T,dim::Angle>v);

        template <typename=void>
        requires std::is_floating_point_v<T>
        Spinor2(clockwise_k, MKS<T,dim::Angle>v);

        template <typename=void>
        requires std::is_floating_point_v<T>
        Spinor2(hpr_k, MKS<T,dim::Angle>v);

        template <typename=void>
        requires std::is_floating_point_v<T>
        explicit Spinor2(const Tensor22<T>&);

        constexpr bool operator==(const Spinor2&) const noexcept = default;

        //! Postive affirmation operator
        Spinor2             operator+() const;
        
        //! Negation operator
        Spinor2             operator-() const;

        //! Normalization operator (ie, returns a normalized spinor)
        template <typename=void>
        requires std::is_floating_point_v<T>
        Spinor2<T>          operator~() const;
        
        //! Operator for length (squared)
        constexpr square_t<T>   operator^(two_k) const noexcept;

        //! Adds two spinors, returns the result
        constexpr Spinor2   operator+ (const Spinor2<T>&b) const noexcept;
        
        //! Adds right hand spinor to this one, returns reference
        Spinor2&            operator+=(const Spinor2<T>&b) noexcept;
        
        //! Subtracts right spinor from the left, returns the result
        constexpr Spinor2   operator- (const Spinor2<T>&b) const noexcept;
        
        //! Subtracts right hand spinor from this one, returns reference
        Spinor2&            operator-=(const Spinor2<T>&b) noexcept;

        //! Multiplies spinor by a scaling arithmetic type, returns the result
        template <typename U>
        requires (is_arithmetic_v<U>)
        constexpr Spinor2<product_t<T,U>>  operator* (U b) const noexcept;

        //! Self-multiplies this spinor by the right hand term, returns reference
        template <typename U>
        requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
        Spinor2& operator*=(U b) noexcept;

        //! Multiplies two spinors, returns the result
        template <typename U>
        constexpr Spinor2<product_t<T,U>>  operator* (const Spinor2<U>&b) const noexcept;

        //! Self-Multiplies this spinor by the right hand one, returns reference
        template <typename U>
        requires self_multiply_v<T,U>
        Spinor2<T>& operator*=(const Spinor2<U>&b) noexcept;

        //! Multiplies (or rotates) spinor with vector, returns result
        template <typename U>
        requires (std::is_floating_point_v<T> && std::is_floating_point_v<U>)
        constexpr Vector2<product_t<T,U>>   operator* (const Vector2<U>&b) const noexcept;

        //! Divides spinor by scalar, returns result
        template <typename U>
        requires (is_arithmetic_v<T>)
        constexpr Spinor2<quotient_t<T,U>>  operator/ (U b) const noexcept;
        
        //! Self-divides this spinor by the scalar, returns reference
        template <typename U>
        requires (is_arithmetic_v<U> && self_divide_v<T,U>)
        Spinor2<T>& operator/=(U b) noexcept;

        //template <typename>
        //requires std::is_floating_point_v<T>
        Radian                      angle() const;
        
                //! Computes & returns the conjugate of this spinor (abbreviated spelling)
        constexpr Spinor2       conj() const noexcept;

        //! Computes & returns the conjugate of this spinor
        constexpr Spinor2       conjugate() const noexcept;
        
        //! Computes & returns the inverse for this spinor
        constexpr Spinor2<inverse_t<T>>   inverse() const noexcept;
        
        //! Computes the square of the length to this spinor
        constexpr square_t<T>    length²() const noexcept;
        
        //! Computes the length to this spinor, returns result
        //! \note the square root must be valid for T^2
        T                        length() const;

    };

    template <typename T>
    constexpr Spinor2<T> spinor(T w, std::type_identity_t<T> z)
    {
        return {w,z};
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    Spinor2<T>  spinor(const Tensor22<T>& t);

    template <typename T>
    constexpr Spinor2<T> conjugate(const Spinor2<T>&a);

    template <typename T>
    constexpr square_t<T>  length²(const Spinor2<T>&a);

    template <typename T>
    constexpr T  length(const Spinor2<T>&a);
    

    YQ_IS_NAN_1(Spinor2, is_nan(v.z) || is_nan(v.w))
    YQ_IS_FINITE_1(Spinor2, is_finite(v.z) && is_finite(v.w))
        

    template <typename T>
    requires std::is_floating_point_v<T>
    void    pre_mult(const Spinor2<T>&a, Spinor2<T>&b);

    template <typename T>
    requires std::is_floating_point_v<T>
    void    post_mult(Spinor2<T>&a, const Spinor2<T>&b);

    template <typename T, typename U>
    requires (is_arithmetic_v<T>)
    constexpr Spinor2<product_t<T,U>>  operator*(T a, const Spinor2<U>&b);

    template <typename T, typename R>
    bool is_close(const R& compare, const Spinor2<T>& actual, const Spinor2<T>& expected);
    
    template <typename T, typename R>
    bool is_close(const R& compare, const Spinor2<T>& actual, std::type_identity_t<T>w, std::type_identity_t<T> z);

    template <typename S, typename T>
    S&  as_stream(S& s, const Spinor2<T>& v);
    
    template <typename T>
    Stream& operator<<(Stream&s, const Spinor2<T>& v);

    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const Spinor2<T>& v);

}

YQ_TYPE_DECLARE(yq::Spinor2D)
YQ_TYPE_DECLARE(yq::Spinor2F)
