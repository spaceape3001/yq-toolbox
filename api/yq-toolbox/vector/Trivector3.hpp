////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_TRIVECTOR3_HPP 1

#include <yq-toolbox/typedef/trivector3.hpp>

#include <yq-toolbox/keywords.hpp>
#include <yq-toolbox/meta/InfoBinder.hpp>
#include <yq-toolbox/trait/cube.hpp>
#include <yq-toolbox/trait/has_is_finite.hpp>
#include <yq-toolbox/trait/has_nan.hpp>
#include <yq-toolbox/trait/has_one.hpp>
#include <yq-toolbox/trait/has_zero.hpp>
#include <yq-toolbox/trait/ieee754.hpp>
#include <yq-toolbox/trait/integer.hpp>
#include <yq-toolbox/trait/is_arithmetic.hpp>
#include <yq-toolbox/trait/is_integral.hpp>
#include <yq-toolbox/trait/product.hpp>
#include <yq-toolbox/trait/quotient.hpp>
#include <yq-toolbox/trait/self_divide.hpp>
#include <yq-toolbox/trait/self_multiply.hpp>

namespace log4cpp { class CategoryStream; }

namespace yq {
    class Stream;
    
    template <typename> struct Bivector3;
    template <typename> struct Multivector3;
    template <typename> struct Vector3;


    /*! \brief 3D Tri-vector */
    template <typename T>
    struct Trivector3 {
        //! Our argument type
        using component_type = T;
        
        //! XYZ component (which for 3-dimension is only one)
        T     xyz;

		//! Default constructor
        constexpr Trivector3() noexcept = default;
        
        //! Component wise constructor (which is only one)
        constexpr Trivector3(T _xyz) noexcept : xyz(_xyz) {}
        
        //! Constructs all components to same value (here to allow for templated cases, otherwise redundant)
        constexpr Trivector3(all_t, T v) noexcept : xyz(v) {}
        
        //! Constructs to not-a-number
        template <typename=void> requires has_nan_v<T>
        consteval Trivector3(nan_t) noexcept : Trivector3(ALL, nan_v<T>) {}
        
        //! Constructs to a size of one, the unit trivector
        consteval Trivector3(one_t) noexcept : Trivector3(ALL, one_v<T>) {}
        
        //! Constructs to a value in the XYZ component
        constexpr Trivector3(xyz_t, T v) noexcept : xyz(v) {}

        //! Constructs to a unit value in the XYZ component
        consteval Trivector3(xyz_t) noexcept : Trivector3(XYZ, one_v<T>) {}
        
        //! Constructs to a zero trivector
        consteval Trivector3(zero_t) noexcept : Trivector3(ALL, zero_v<T>) {}
        
        //! Converts to another Trivector3 of convertible data type
        template <typename U>
        requires std::is_nothrow_convertible_v<T,U>
        explicit constexpr operator Trivector3<U>() const noexcept
        {
            return { (U) xyz };
        }
        
        //! Converts to another Trivector3 of convertible data type
        template <typename U>
        requires (std::is_convertible_v<T,U> && !std::is_nothrow_convertible_v<T,U>)
        explicit constexpr operator Trivector3<U>() const 
        {
            return { (U) xyz };
        }

        //! Defaulted comparison operator
        constexpr auto operator<=>(const Trivector3&) const noexcept = default;

        /*! \brief Affirmation (positive) operator
        */
        constexpr Trivector3 operator+() const noexcept;

        /*! \brief Negation operator
        */
        constexpr Trivector3 operator-() const noexcept;

        //! Adds scalar to trivector
        constexpr Multivector3<T> operator+(T b) const noexcept;
        
        //! Adds trivectors 
        constexpr Trivector3 operator+(const Trivector3& b) const noexcept;
        
        //! Self-incrementing adding right trivector into this trivector
        Trivector3& operator+=(const Trivector3& b) noexcept;
        
        //! Adds bivector to this trivector, returns the multivector result
        constexpr Multivector3<T> operator+(const Bivector3<T>& b) const noexcept;
        
        //! Adds multivector to this trivector, returns the multivector result
        constexpr Multivector3<T> operator+(const Multivector3<T>& b) const noexcept;
        
        //! Adds a vector to this trivector, returns the multivector result
        constexpr Multivector3<T> operator+(const Vector3<T>& b) const noexcept;
        
        //! Subtracts a scalar from this trivector, returns the mulltivector result
        constexpr Multivector3<T> operator-(T b) const noexcept;
        
        //! Subtracts one trivector from another, returns the trivector result
        constexpr Trivector3 operator-(const Trivector3& b) const noexcept;
        
        //! Self-subtracts a trivector from this trivector
        Trivector3& operator-=(const Trivector3& b) noexcept;
        
        //! Subtracts a bivector from this trivector, returns the multivector result
        constexpr Multivector3<T> operator-(const Bivector3<T>& b) const noexcept;
        
        //! Subtracts a multivector from this trivector, returns the multivector result
        constexpr Multivector3<T> operator-(const Multivector3<T>& b) const noexcept;

        //! Subtracts a vector from this trivector, returns the multivector result
        constexpr Multivector3<T> operator-(const Vector3<T>& b) const noexcept;

        //! Multiplies a scalar with this trivector, returning the trivector result
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Trivector3<product_t<T,U>> operator*(U b) const noexcept;

        //! Self-scalign multiplication
        template <typename U>
        requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
        Trivector3& operator*=(U b) noexcept;

        //! Divides a scalar against this trivector, returns the trivector result
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Trivector3<quotient_t<T,U>> operator/(const U b) const noexcept;

        //! Self-dividing this trivector by the given scalar, returns a reference
        template <typename U>
        requires (is_arithmetic_v<U> && self_divide_v<T,U>)
        constexpr Trivector3& operator/=(U b) noexcept;
    };

    YQ_IEEE754_1(Trivector3)
    YQ_INTEGER_1(Trivector3)
    YQ_IS_INTEGER_1(Trivector3)

//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Literal to construct a trivector
    */
    constexpr Trivector3D   operator "" _xyz3(unsigned long long int v) noexcept
    {
        return Trivector3D(XYZ, (double) v);
    }

    /*! \brief Literal to construct a trivector
    */
    constexpr Trivector3D   operator "" _xyz3(long double v) noexcept
    {
        return Trivector3D(XYZ, (double) v);
    }

    YQ_NAN_1(Trivector3, Trivector3<T>{nan_v<cube_t<T>>})
    YQ_ZERO_1(Trivector3, Trivector3<T>{zero_v<cube_t<T>>})
    
//  --------------------------------------------------------
//  GETTERS

//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_NAN_1(Trivector3, is_nan(v.xyz))
    YQ_IS_FINITE_1(Trivector3, is_finite(v.xyz))


//  --------------------------------------------------------
//  --------------------------------------------------------

    //! Adds scalar with trivector, returns the multivector result
    template <typename T>
    constexpr Multivector3<T> operator+(T a, const Trivector3<T>& b) noexcept;

    //! Subtracts the trivector from the scalar, returns the multivector result
    template <typename T>
    constexpr Multivector3<T> operator-(T a, const Trivector3<T>& b) noexcept;

    /*! \brief Scaling multiplication of trivector
    
        This will (scale) multiply a trivector, returns the result.
    */
    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Trivector3<T> operator*(T a, const Trivector3<U>& b) noexcept;



}

YQ_TYPE_DECLARE(yq::Trivector3D)
YQ_TYPE_DECLARE(yq::Trivector3F)

