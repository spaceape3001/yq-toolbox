////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_SPINOR2_HPP 1

#include <yq/keywords.hpp>
#include <yq/macro/operators.hpp>
#include <yq/meta/InfoBinder.hpp>
#include <yq/trait/fourth.hpp>
#include <yq/trait/has_nan.hpp>
#include <yq/trait/has_is_finite.hpp>
#include <yq/trait/has_one.hpp>
#include <yq/trait/has_sqrt.hpp>
#include <yq/trait/has_zero.hpp>
#include <yq/trait/ieee754.hpp>
#include <yq/trait/integer.hpp>
#include <yq/trait/inverse.hpp>
#include <yq/trait/is_arithmetic.hpp>
#include <yq/trait/is_integral.hpp>
#include <yq/trait/product.hpp>
#include <yq/trait/quotient.hpp>
#include <yq/trait/self_divide.hpp>
#include <yq/trait/self_multiply.hpp>
#include <yq/trait/square.hpp>
#include <yq/typedef/spinor2.hpp>
#include <yq/unit/declare.hpp>

namespace log4cpp { class CategoryStream; }

namespace yq {
    template <typename, typename> struct MKS;
    template <typename> struct Multivector2;
    template <typename> struct Tensor22;
    template <typename> struct Vector2;
    class Stream;


    /*! \brief 2D Spiny thing, the square of it, does rotations like quaternions in 3D 
        
        \note  Warning... we're doing multiplications like ... it's a slight 
        bastardization from what a proper spinor is
    */
    template <typename T>
    struct Spinor2 {
        
        static_assert(std::is_floating_point_v<T>, "Should only be used with floating point types");
        
        //! Capture our template parameter for the component type
        using component_type = T;

        //! Scalar component
        T   a;
        
        //! Bivector component
        T   xy;

        //! Default constructor (which does nothing)
        constexpr Spinor2(){}

        //! Component wise constructor
        constexpr Spinor2(T _a, T _xy) : a(_a), xy(_xy) {}
        
        //! Initializes to all components having the same value
        constexpr Spinor2(all_k, T v) : a(v), xy(v) {}
        
        //! Initializes to an identity spinor
        consteval Spinor2(identity_k) : a(one_v<T>), xy(zero_v<T>) {}
        
        //! Initializes all components to not-a-number
        consteval Spinor2(nan_k) : Spinor2(ALL, nan_v<T>) {}
        
        //! Initializes to a unit spinor in W (rest are zero)
        consteval Spinor2(xy_k) noexcept : a(zero_v<T>), xy(one_v<T>) {}
        
        //! Initializes to a single value on the W-component
        constexpr Spinor2(xy_k, T v) noexcept :  a(zero_v<T>), xy(v) {}
        
        //! Initializes to all zeros
        consteval Spinor2(zero_k) : Spinor2(ALL, zero_v<T>) {}
        
        //! Constructs spinor from multivector (vector bits will be lost)
        explicit constexpr Spinor2(const Multivector2<T>&);
        
        //! Creates a spinor that effects a specified counter-clockwise rotation 
        Spinor2(ccw_k, Radian);
        
        //! Creates a spinor that effects a specified clockwise rotation 
        Spinor2(clockwise_k, Radian);

        //! Defaulted equality operator
        constexpr bool operator==(const Spinor2&) const noexcept = default;

        //! Postive affirmation operator
        Spinor2             operator+() const;
        
        //! Negation operator
        Spinor2             operator-() const;

        //! Normalization operator (ie, returns a normalized spinor)
        Spinor2<T>          operator~() const;
        
        //! Operator for our square
        constexpr Spinor2   operator^(two_k) const noexcept;

        //! Adds two spinors together, returns result
        constexpr Spinor2           operator+ (const Spinor2&b) const noexcept;
        
        //! Adds right hand spinor to this one, returns reference
        Spinor2&    operator+=(const Spinor2<T>&b) noexcept;
        
        //! Subtracts right spinor from the left, returns the result
        constexpr Spinor2   operator- (const Spinor2&b) const noexcept;
        
        //  Others to do....
        
        //! Subtracts right hand spinor from this one, returns reference
        Spinor2&            operator-=(const Spinor2&b) noexcept;

        //! Multiplies spinor by a scaling arithmetic type, returns the result
        constexpr Spinor2<T>  operator* (T b) const noexcept;

        //! Self-multiplies this spinor by the right hand term, returns reference
        Spinor2& operator*=(T b) noexcept;

        //! Multiplies two spinors, returns the result
        constexpr Spinor2<T>  operator* (const Spinor2&b) const noexcept;

        //! Self-Multiplies this spinor by the right hand one, returns reference
        Spinor2<T>& operator*=(const Spinor2&b) noexcept;

        //! Multiplies (or rotates) spinor with vector, returns result
        template <typename U>
        constexpr Vector2<product_t<T,U>>   operator* (const Vector2<U>&b) const noexcept;

        //! Divides spinor by scalar, returns result
        constexpr Spinor2<T>  operator/ (T b) const noexcept;
        
        //! Self-divides this spinor by the scalar, returns reference
        Spinor2& operator/=(T b) noexcept;

        //template <typename>
        //requires std::is_floating_point_v<T>
        
        //! Computes/returns the angle of rotation for this spinor
        Radian                  angle() const;

        //! Computes/returns the angle of rotation for this spinor in a counter-clockwise fashion
        Radian                  angle(ccw_k) const;

        //! Computes/returns the angle of rotation for this spinor in a clockwise fashion
        Radian                  angle(clockwise_k) const;

        //! Computes/returns the angle of rotation for this spinor in a heading/clockwise fashion
        Radian                  angle(heading_k) const;
        
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

    //! Creates a spinor from the two arguments
    template <typename T>
    constexpr Spinor2<T> spinor(T a, std::type_identity_t<T> xy)
    {
        return {a,xy};
    }

    //template <typename T>
    //requires std::is_floating_point_v<T>
    //Spinor2<T>  spinor(const Tensor22<T>& t);
    
    //! Extracts a spinor from the multivector
    template <typename T>
    Spinor2<T>      spinor(const Multivector2<T>&);

    //! Conjugate of the given spinor
    template <typename T>
    constexpr Spinor2<T> conjugate(const Spinor2<T>&a);

    //! Length of the spinor (sum of squares of components)
    template <typename T>
    constexpr square_t<T>  length²(const Spinor2<T>&a);

    template <typename T>
    constexpr T  length(const Spinor2<T>&a);
    

    YQ_IS_NAN_1(Spinor2, is_nan(v.a) || is_nan(v.xy))
    YQ_IS_FINITE_1(Spinor2, is_finite(v.a) && is_finite(v.xy))
        
    template <typename T, typename U>
    requires (is_arithmetic_v<T>)
    constexpr Spinor2<product_t<T,U>>  operator*(T a, const Spinor2<U>&b);

    template <typename T, typename R>
    bool is_close(const R& compare, const Spinor2<T>& actual, const Spinor2<T>& expected);
    
    template <typename T, typename R>
    bool is_close(const R& compare, const Spinor2<T>& actual, std::type_identity_t<T>a, std::type_identity_t<T> xy);

    template <typename S, typename T>
    S&  as_stream(S& s, const Spinor2<T>& v);
    
    template <typename T>
    Stream& operator<<(Stream&s, const Spinor2<T>& v);

    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const Spinor2<T>& v);

}

YQ_TYPE_DECLARE(yq::Spinor2D)
YQ_TYPE_DECLARE(yq::Spinor2F)
