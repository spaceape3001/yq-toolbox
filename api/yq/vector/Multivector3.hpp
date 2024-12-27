////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_MULTIVECTOR3_HPP 1

#include <yq/typedef/multivector3.hpp>

#include <yq/vector/Vector3.hpp>
#include <yq/vector/Bivector3.hpp>
#include <yq/vector/Trivector3.hpp>

#include <yq/keywords.hpp>
#include <yq/trait/product.hpp>
#include <yq/trait/quotient.hpp>
#include <yq/trait/self_divide.hpp>
#include <yq/trait/self_multiply.hpp>

namespace log4cpp { class CategoryStream; }

namespace yq {

    /*! \brief Three dimensional multivector
    */
    template <typename T>
    struct Multivector3 {
        //! Captures the template parameter
        using component_type    = T;

        //! Scalar
        T   a;
        
        //! X (vector component)
        T   x;
        
        //! Y (vector component)
        T   y;
        
        //! Z (vector component)
        T   z;
        
        //! XY (bivector component)
        T   xy;
        
        //! YZ (bivector component)
        T   yz;
        
        //! ZX (bivector component)
        T   zx;
        
        //! XYZ (trivector component)
        T   xyz;
        
        //! Default constructor
        constexpr Multivector3() noexcept = default;
        
        //! Number-by-number constructor
        constexpr Multivector3(T _a, T _x, T _y, T _z, T _xy, T _yz, T _zx, T _xyz) noexcept : 
            a(_a), x(_x), y(_y), z(_z), xy(_xy), yz(_yz), zx(_zx), xyz(_xyz) {}
            
        //! Component by component constructor
        constexpr Multivector3(T _a, const Vector3<T>& v, const Bivector3<T>& b, const Trivector3<T>& t) noexcept : 
            a(_a), x(v.x), y(v.y), z(v.z), xy(b.xy), yz(b.yz), zx(b.zx), xyz(t.xyz) {}

        //! Constructs by setting all sub-values to same value
        constexpr Multivector3(all_k, T v) noexcept : a(v), x(v), y(v), z(v), xy(v), yz(v), zx(v), xyz(v) {}
        
        //! Constructs ALL values to not-a-number
        template <typename=void> requires has_nan_v<T>
        consteval Multivector3(nan_k) noexcept : Multivector3(ALL, nan_v<T>) {}
        
        //! Constructs ALL values to be one
        consteval Multivector3(one_k) noexcept : Multivector3(ALL, one_v<T>) {}
        
        //! Constructs ALL values to be zero
        consteval Multivector3(zero_k) noexcept : Multivector3(ALL, zero_v<T>) {}

        //! Converts this multivector to another of compatible type
        template <typename U>
        requires std::is_nothrow_convertible_v<T,U>
        explicit constexpr operator Multivector3<U>() const noexcept
        {
            return {
                (U) a,
                (U) x, (U) y, (U) z,
                (U) xy, (U) yz, (U) zx,
                (U) xyz
            };
        }
        
        //! Converts this multivector to another of compatible type
        template <typename U>
        requires (std::is_convertible_v<T,U> && !std::is_nothrow_convertible_v<T,U>)
        explicit constexpr operator Multivector3<U>() const 
        {
            return {
                (U) a,
                (U) x, (U) y, (U) z,
                (U) xy, (U) yz, (U) zx,
                (U) xyz
            };
        }

        //! Equality operator (defaulted)
        constexpr bool operator==(const Multivector3&) const noexcept = default;

        //! Positive (affirm) operator (to compliment the negation)
        constexpr Multivector3 operator+() const noexcept;
        
        //! Negation operator
        constexpr Multivector3 operator-() const noexcept;

        //! Addition of a scalar to this multivector, returns result
        constexpr Multivector3  operator+(T b) const noexcept;
        
        //! Self-adds scalar to this multivector, returns reference
        Multivector3&           operator+=(T b) noexcept;
        
        //! Addition of a bivector to this multivector, returns result
        constexpr Multivector3  operator+(const Bivector3<T>& b) const noexcept;

        //! Self adds bivector to this multivector, returns reference
        Multivector3&           operator+=(const Bivector3<T>& b) noexcept;
        
        //! Adds two multivectors, returns result
        constexpr Multivector3  operator+(const Multivector3& b) const noexcept;
        
        //! Self adds multivector to this multivector, returns reference
        Multivector3&           operator+=(const Multivector3& b) noexcept;
        
        //! Adds trivector to this multivector, returns result
        constexpr Multivector3  operator+(const Trivector3<T>& b) const noexcept;
        
        //! Self adds trivector to this multivector, returns reference
        Multivector3&           operator+=(const Trivector3<T>& b) noexcept;
        
        //! Adds vector to multivector, returns result
        constexpr Multivector3  operator+(const Vector3<T>&  b) const noexcept;
        
        //! Self adds vector to this multivector, returns reference
        Multivector3&           operator+=(const Vector3<T>& b) noexcept;

        constexpr Multivector3  operator-(T b) const noexcept;
        Multivector3&           operator-=(T b) noexcept;
        constexpr Multivector3  operator-(const Bivector3<T>& b) const noexcept;
        Multivector3&           operator-=(const Bivector3<T>& b) noexcept;
        constexpr Multivector3  operator-(const Multivector3& b) const noexcept;
        Multivector3&           operator-=(const Multivector3& b) noexcept;
        constexpr Multivector3  operator-(const Trivector3<T>& b) const noexcept;
        Multivector3&           operator-=(const Trivector3<T>& b) noexcept;
        constexpr Multivector3  operator-(const Vector3<T>&  b) const noexcept;
        Multivector3&           operator-=(const Vector3<T>& b) noexcept;

        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Multivector3<product_t<T,U>> operator*(U b) const noexcept;

        template <typename U>
        requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
        Multivector3& operator*=(U b) noexcept;

        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Multivector3<quotient_t<T,U>> operator/(U b) const noexcept;

        template <typename U>
        requires (is_arithmetic_v<U> && self_divide_v<T,U>)
        Multivector3& operator/=(U b) noexcept;

        constexpr Bivector3<T>  bivector() const noexcept;
        constexpr Trivector3<T> trivector() const noexcept;
        constexpr Vector3<T>    vector() const noexcept;
    };

    YQ_IEEE754_1(Multivector3)
    YQ_INTEGER_1(Multivector3)
    YQ_IS_INTEGER_1(Multivector3)

//  --------------------------------------------------------
//  COMPOSITION

    YQ_NAN_1(Multivector3, Multivector3<T>(NAN))
    YQ_ZERO_1(Multivector3, Multivector3<T>(ZERO))

//  --------------------------------------------------------
//  GETTERS

    template <typename T>
    constexpr Bivector3<T> bivector(const Multivector3<T>& a) noexcept;

    template <typename T>
    constexpr Trivector3<T> trivector(const Multivector3<T>& a) noexcept;

    template <typename T>
    constexpr Vector3<T> vector(const Multivector3<T>& a) noexcept;
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS
    
    YQ_IS_NAN_1(Multivector3, 
        is_nan(v.a) || 
        is_nan(v.x) || is_nan(v.y) || is_nan(v.z) || 
        is_nan(v.xy) || is_nan(v.yz) || is_nan(v.zx) || 
        is_nan(v.xyz)
    )
    YQ_IS_FINITE_1(Multivector3, 
        is_finite(v.a) && 
        is_finite(v.x) && is_finite(v.y) && is_finite(v.z) && 
        is_finite(v.xy) && is_finite(v.yz) && is_finite(v.zx) && 
        is_finite(v.xyz)
    )


//  --------------------------------------------------------
//  --------------------------------------------------------

    
    template <typename T>
    constexpr Multivector3<T> operator+(T a, const Multivector3<T>& b) noexcept;
    template <typename T>
    constexpr Multivector3<T> operator-(T a, const Multivector3<T>& b) noexcept;

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Multivector3<product_t<T,U>> operator*(T a, const Multivector3<U>&b) noexcept;



}

YQ_TYPE_DECLARE(Multivector3D)
YQ_TYPE_DECLARE(Multivector3F)
