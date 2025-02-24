////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_MULTIVECTOR4_HPP 1

#include <yq/typedef/multivector4.hpp>

#include <yq/vector/Vector4.hpp>
#include <yq/vector/Bivector4.hpp>
#include <yq/vector/Trivector4.hpp>
#include <yq/vector/Quadvector4.hpp>

#include <yq/keywords.hpp>
#include <yq/trait/product.hpp>
#include <yq/trait/quotient.hpp>
#include <yq/trait/self_divide.hpp>
#include <yq/trait/self_multiply.hpp>

namespace log4cpp { class CategoryStream; }

namespace yq {

    /*! \brief Four dimensional multivector
    */
    template <typename T>
    struct Multivector4 {
        //! Captures the template parameter
        using component_type    = T;

        //! Scalar component
        T       a;
        
        //! X vector component
        T       x;

        //! Y vector component
        T       y;

        //! Z vector component
        T       z;

        //! W vector component
        T       w;
        
        //! XY bivector component
        T       xy;
        
        //! YZ bivector component
        T       yz;
        
        //! ZW bivector component
        T       zw;
        
        //! WX bivector component
        T       wx;
        
        //! XZ bivector component
        T       xz;
        
        //! YW bivector component
        T       yw;
        
        //! XYZ trivector component
        T       xyz;

        //! YZW trivector component
        T       yzw;

        //! ZWX trivector component
        T       zwx;

        //! WXY trivector component
        T       wxy;

        //! XYZW quadvector component
        T       xyzw;
        
        //! Default constructor
        constexpr Multivector4() noexcept = default;
        
        //! Value-by-value constructor
        constexpr Multivector4(
            T _a, 
            T _x, T _y, T _z, T _w,
            T _xy, T _yz, T _zw, T _wx, T _xz, T _yw,
            T _xyz, T _yzw, T _zwx, T _wxy,
            T _xyzw
        ) noexcept : 
            a(_a), 
            x(_x), y(_y), z(_z), w(_w),
            xy(_xy), yz(_yz), zw(_zw), wx(_wx), xz(_xz), yw(_yw),
            xyz(_xyz), yzw(_yzw), zwx(_zwx), wxy(_wxy),
            xyzw(_xyzw) {}
            
        //! By component constructor (scalar, vector, bivector, trivector, & quadvector)
        constexpr Multivector4(T _a, const Vector4<T>& v, const Bivector4<T>& b, const Trivector4<T>& t, const Quadvector4<T>&q) noexcept : 
            a(_a), 
            x(v.x), y(v.y), z(v.z), w(v.w),
            xy(b.xy), yz(b.yz), zw(b.zw), wx(b.wx), xz(b.xz), yw(b.yw),
            xyz(t.xyz), yzw(t.yzw), zwx(t.zwx), wxy(t.wxy),
            xyzw(q.xyzw) {}
            
        //! Constructor that sets ALL components to the same value
        constexpr Multivector4(all_k, T v) noexcept : 
            a(v), 
            x(v), y(v), z(v), 
            xy(v), yz(v), zw(v), wx(v), xz(v), yw(v),
            xyz(v), yzw(v), zwx(v), wxy(v),
            xyzw(v) {}
            
        //! Constructor that sets all components to NaN
        template <typename=void> requires has_nan_v<T>
        consteval Multivector4(nan_k) noexcept : Multivector4(ALL, nan_v<T>) {}

        //! Constructor that sets all components to one
        consteval Multivector4(one_k) noexcept : Multivector4(ALL, one_v<T>) {}

        //! Constructor that sets all components to zero
        consteval Multivector4(zero_k) noexcept : Multivector4(ALL, zero_v<T>) {}

        //! Converts to another multivector of compatible type
        template <typename U>
        requires std::is_nothrow_convertible_v<T,U>
        explicit constexpr operator Multivector4<U>() const noexcept
        {
            return {
                (U) a,
                (U) x, (U) y, (U) z, (U) w,
                (U) xy, (U) yz, (U) zw, (U) wx, (U) xz, (U) yw,
                (U) xyz, (U) yzw, (U) zwx, (U) wxy,
                (U) xyzw
            };
        }
        
        //! Converts to another multivector of compatible type
        template <typename U>
        requires (std::is_convertible_v<T,U> && !std::is_nothrow_convertible_v<T,U>)
        explicit constexpr operator Multivector4<U>() const 
        {
            return {
                (U) a,
                (U) x, (U) y, (U) z, (U) w,
                (U) xy, (U) yz, (U) zw, (U) wx, (U) xz, (U) yw,
                (U) xyz, (U) yzw, (U) zwx, (U) wxy,
                (U) xyzw
            };
        }

        //! Equality (defaulted) 
        constexpr bool operator==(const Multivector4&) const noexcept = default;
        
        //! Positive/affirmation operator
        constexpr Multivector4  operator+() const noexcept;
        
        //! Negative/negation operator
        constexpr Multivector4  operator-() const noexcept;
        
        //! Adds scalar to multivector, returns result
        constexpr Multivector4  operator+(T b) const noexcept;
        
        //! Adds scalar to this multivector, returns reference
        Multivector4&           operator+=(T b) noexcept;
        
        //! Adds bivector to multivector, returns result
        constexpr Multivector4  operator+(const Bivector4<T>& b) const noexcept;
        
        //! Adds bivector to this multivector, returns reference
        Multivector4&           operator+=(const Bivector4<T>& b) noexcept;
        
        //! Adds two multivectors together, returns result
        constexpr Multivector4  operator+(const Multivector4& b) const noexcept;
        
        //! Adds multivector to this multivector, returns reference
        Multivector4&           operator+=(const Multivector4& b) noexcept;
        
        //! Adds quadvector to multivector, returns result
        constexpr Multivector4  operator+(const Quadvector4<T>& b) const noexcept;
        
        //! Adds quadvector to this multivector, returns reference
        Multivector4&           operator+=(const Quadvector4<T>& b) noexcept;
        
        //! Adds trivector to multivector, returns result
        constexpr Multivector4  operator+(const Trivector4<T>& b) const noexcept;
        
        //! Adds trivector to this multivector, returns reference
        Multivector4&           operator+=(const Trivector4<T>& b) noexcept;
        constexpr Multivector4  operator+(const Vector4<T>&  b) const noexcept;
        Multivector4&           operator+=(const Vector4<T>& b) noexcept;
        
        constexpr Multivector4  operator-(T b) const noexcept;
        Multivector4&           operator-=(T b) noexcept;
        constexpr Multivector4  operator-(const Bivector4<T>& b) const noexcept;
        Multivector4&           operator-=(const Bivector4<T>& b) noexcept;
        constexpr Multivector4  operator-(const Multivector4& b) const noexcept;
        Multivector4&           operator-=(const Multivector4& b) noexcept;
        constexpr Multivector4  operator-(const Quadvector4<T>& b) const noexcept;
        Multivector4&           operator-=(const Quadvector4<T>& b) noexcept;
        constexpr Multivector4  operator-(const Trivector4<T>& b) const noexcept;
        Multivector4&           operator-=(const Trivector4<T>& b) noexcept;
        constexpr Multivector4  operator-(const Vector4<T>&  b) const noexcept;
        Multivector4&           operator-=(const Vector4<T>& b) noexcept;

        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Multivector4<product_t<T,U>> operator*(U b) const noexcept;
        
        template <typename U>
        requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
        Multivector4& operator*=(U b) noexcept;

        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Multivector4<quotient_t<T,U>> operator/(U b) const noexcept;

        template <typename U>
        requires (is_arithmetic_v<U> && self_divide_v<T,U>)
        Multivector4& operator/=(U b) noexcept;

        constexpr Bivector4<T> bivector() const noexcept;
        constexpr Quadvector4<T> quadvector() const noexcept;
        constexpr Trivector4<T> trivector() const noexcept;
        constexpr Vector4<T> vector() const noexcept;
    };

    YQ_IEEE754_1(Multivector4)
    YQ_INTEGER_1(Multivector4)
    YQ_IS_INTEGER_1(Multivector4)

//  --------------------------------------------------------
//  COMPOSITION

    YQ_NAN_1(Multivector4, Multivector4<T>(NAN))
    YQ_ZERO_1(Multivector4, Multivector4<T>(ZERO))

//  --------------------------------------------------------
//  GETTERS

    /*! \brief Extracts the bivector component from the multivector
    */
    template <typename T>
    constexpr Bivector4<T> bivector(const Multivector4<T>& a) noexcept;

    /*! \brief Extracts the quadvector component from the multivector
    */
    template <typename T>
    constexpr Quadvector4<T> quadvector(const Multivector4<T>& a) noexcept;

    /*! \brief Extracts the trivector component from the multivector
    */
    template <typename T>
    constexpr Trivector4<T> trivector(const Multivector4<T>& a) noexcept;

    /*! \brief Extracts the vector component from the multivector
    */
    template <typename T>
    constexpr Vector4<T> vector(const Multivector4<T>& a) noexcept;

//  --------------------------------------------------------
//  BASIC FUNCTIONS
    
    YQ_IS_NAN_1(Multivector4, 
        is_nan(v.a) || 
        is_nan(v.x) || is_nan(v.y) || is_nan(v.z) || is_nan(v.w) ||
        is_nan(v.xy) || is_nan(v.yz) || is_nan(v.zw) || is_nan(v.wx) || is_nan(v.xz) || is_nan(v.yw) ||
        is_nan(v.xyz) || is_nan(v.yzw) || is_nan(v.zwx) || is_nan(v.wxy) ||
        is_nan(v.xyzw)
    )
    YQ_IS_FINITE_1(Multivector4, 
        is_finite(v.a) && 
        is_finite(v.x) && is_finite(v.y) && is_finite(v.z) && is_finite(v.w) &&
        is_finite(v.xy) && is_finite(v.yz) && is_finite(v.zw) && is_finite(v.wx) && is_finite(v.xz) && is_finite(v.yw) &&
        is_finite(v.xyz) && is_finite(v.yzw) && is_finite(v.zwx) && is_finite(v.wxy) &&
        is_finite(v.xyzw)
    )


//  --------------------------------------------------------
//  --------------------------------------------------------


    template <typename T>
    constexpr Multivector4<T> operator+(T a, const Multivector4<T>& b) noexcept;

    template <typename T>
    constexpr Multivector4<T> operator+(T a, const Multivector4<T>& b) noexcept;

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Multivector4<product_t<T,U>> operator*(T a, const Multivector4<U>&b) noexcept;

}

YQ_TYPE_DECLARE(Multivector4D)
YQ_TYPE_DECLARE(Multivector4F)

