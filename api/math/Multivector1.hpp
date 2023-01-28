////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>
#include <math/Vector1.hpp>

namespace yq {

    /*! \brief One dimensional multivector
    */
    template <typename T>
    struct Multivector1 {
        
        //! Captures the template parameter
        using component_type    = T;
    
        //! Scalar
        unity_t<T>  a;
        
        //! X
        T           x;
        
        //! Defaulted equality
        constexpr bool operator==(const Multivector1&) const noexcept = default;
    };

    YQ_IEEE754_1(Multivector1)

//  --------------------------------------------------------
//  COMPOSITION

    YQ_NAN_1(Multivector1, Multivector1<T>{nan_v<unity_t<T>>, nan_v<T>})
    YQ_ZERO_1(Multivector1, Multivector1<T>{zero_v<unity_t<T>>, zero_v<T>})
    
//  --------------------------------------------------------
//  GETTERS

    //! Extracts the vector part
    template <typename T>
    constexpr Vector1<T> vector(const Multivector1<T>& a) noexcept
    {
        return { a.x };
    }

//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_NAN_1(Multivector1, is_nan(v.a) || is_nan(v.x) )
    YQ_IS_FINITE_1(Multivector1, is_finite(v.a) && is_finite(v.x))

//  --------------------------------------------------------
//  POSITIVE
    
    //! Affirmation operator (to complement the negative)
    template <typename T>
    constexpr Multivector1<T> operator+(const Multivector1<T>& a) noexcept
    {
        return a;
    }

//  --------------------------------------------------------
//  NEGATIVE

    //! Negation operatpr
    template <typename T>
    constexpr Multivector1<T> operator-(const Multivector1<T>& a) noexcept
    {
        return {-a.a, -a.x};
    }

//  --------------------------------------------------------
//  NORMALIZATION


//  --------------------------------------------------------
//  ADDITION

    //! Adds two multivectors together
    template <typename T>
    constexpr Multivector1<T> operator+(const Multivector1<T>& a, const Multivector1<T>&  b) noexcept
    {
        return {
            a.a+b.a,
            a.x+b.x
        };
    }

    //! Self-addition operator (right added into left term)
    template <typename T>
    Multivector1<T>& operator+=(Multivector1<T>& a, const Multivector1<T>& b) noexcept
    {
        a.a += b.a;
        a.x += b.x;
        return a;
    }

    //! Adds left multivector with right scalar
    template <typename T>
    constexpr Multivector1<T> operator+(const Multivector1<T>& a, unity_t<T>  b) noexcept
    {
        return {
            a.a+b,
            a.x
        };
    }

    //! Self-addition operator, adding right scalar into left multivector
    template <typename T>
    Multivector1<T>& operator+=(Multivector1<T>& a, unity_t<T>  b) noexcept
    {
        a.a += b;
        return a;
    }
    

    //! Adds left multivector with right vector
    template <typename T>
    constexpr Multivector1<T> operator+(const Multivector1<T>& a, const Vector1<T>&  b) noexcept
    {
        return {
            a.a,
            a.x+b.x
        };
    }

    //! Self-addition operator, adding right vector into left multivector
    template <typename T>
    Multivector1<T>& operator+=(Multivector1<T>& a, const Vector1<T>& b) noexcept
    {
        a.x += b.x;
        return a;
    }
    
    //! Adds left scalar with right multivector
    template <typename T>
    constexpr Multivector1<T> operator+(unity_t<T> a, const Multivector1<T>& b) noexcept
    {
        return { 
            a+b.a, 
            b.x 
        };
    }


    
//  --------------------------------------------------------
//  SUBTRACTION

    //! Subtracts two multivectors
    template <typename T>
    constexpr Multivector1<T> operator-(const Multivector1<T>& a, const Multivector1<T>& b) noexcept
    {
        return {
            a.a-b.a,
            a.x-b.x
        };
    }

    //! Self-subtraction operator, subtracting right term from left-in-place
    template <typename T>
    Multivector1<T>& operator-=(Multivector1<T>& a, const Multivector1<T>& b) noexcept
    {
        a.a -= b.a;
        a.x -= b.x;
        return a;
    }
    
    //! Subtracts scalar from multivector
    template <typename T>
    constexpr Multivector1<T> operator-(const Multivector1<T>& a, unity_t<T> b) noexcept
    {
        return {
            a.a-b,
            a.x
        };
    }

    //! Self-subtraction operator, subtracting right scalar from left multivector in-place
    template <typename T>
    Multivector1<T>& operator-=(Multivector1<T>& a, unity_t<T> b) noexcept
    {
        a.a -= b;
        return a;
    }
    
    //! Subtracts vector from multivector
    template <typename T>
    constexpr Multivector1<T> operator-(const Multivector1<T>& a, const Vector1<T>& b) noexcept
    {
        return {
            a.a,
            a.x-b.x
        };
    }

    //! Self-subtraction operator, subtracting right vector from left multivector in-place
    template <typename T>
    Multivector1<T>& operator-=(Multivector1<T>& a, const Vector1<T>& b) noexcept
    {
        a.x -= b.x;
        return a;
    }
    
    //! Subtracts multivector from scalar
    template <typename T>
    constexpr Multivector1<T> operator-(unity_t<T> a, const Multivector1<T>& b) noexcept
    {
        return { 
            a-b.a, 
            -b.x 
        };
    }




//  --------------------------------------------------------
//  MULTIPLICATION

    //! Multiplies scalar with multivector
    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Multivector1<T> operator*(T a, const Multivector1<T>&b) noexcept
    {
        return { a*b.a, a*b.x };
    }

    //! Multiplies multivector with scalar
    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Multivector1<T> operator*(const Multivector1<T>& a, T b) noexcept
    {
        return { a.a*b, a.x*b };
    }

    //! Self-scaling multiplication of multivector with scalar
    template <typename T>
    requires std::is_floating_point_v<T>
    Multivector1<T>& operator*=(Multivector1<T>& a, T b) noexcept
    {
        a.a*=b; a.x*=b;
        return a;
    }

    //! Multiplies vector with multivector
    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Multivector1<T> operator*(const Vector1<T>& a, const Multivector1<T>& b) noexcept
    {
        return Multivector1<T>( a.x * b.x, a.x * b.a);
    }

    //! Multiplies multivecotr with vector
    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Multivector1<T> operator*(const Multivector1<T>& a, const Vector1<T>& b) noexcept
    {
        return Multivector1<T>( a.x*b.x, a.a*b.x );
    }

    //! Self-multiplication, multiplying left term (in place) with right vector
    template <typename T>
    requires std::is_floating_point_v<T>
    Multivector1<T>& operator*=(Multivector1<T>& a, const Vector1<T>& b) noexcept
    {
        a.x *= b.x;
        a.a *= b.x;
        return a;
    }

    //! Multiplies two multivectors
    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Multivector1<T> operator*(const Multivector1<T>& a, const Multivector1<T>& b) noexcept
    {
        return Multivector1<T>( a.a*b.a+a.x*b.x, a.a*b.x+a.x*b.a );
    }
    
    //! Self-multiplication, multiplies left term (in place) with right multivector
    template <typename T>
    requires std::is_floating_point_v<T>
    Multivector1<T> operator*=(Multivector1<T>& a, const Multivector1<T>& b) noexcept
    {
        a   = a*b;
        return a;
    }

//  --------------------------------------------------------
//  DIVISION

    //! Scaling division, dividing multivector by scalar
    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Multivector1<T> operator/(const Multivector1<T>& a, T b) noexcept
    {
        return { a.a/b, a.x/b };
    }

    //! Self-scaling division, dividing the left multivector in place with scalar
    template <typename T>
    requires std::is_floating_point_v<T>
    Multivector1<T>& operator/=(Multivector1<T>& a, T b) noexcept
    {
        a.a/=b; a.x/=b;
        return a;
    }
    
    //  NOTE we're missing some others divisions... TODO

//  --------------------------------------------------------
//  POWERS

    //  Exponentials could be interesting... TODO

//  --------------------------------------------------------
//  DOT PRODUCT


//  --------------------------------------------------------
//  INNER PRODUCT

    //! Inner product of two multivectors
    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr double   operator INNER(const Multivector1<T>& a, const Multivector1<T>&b)  noexcept
    {
        return a.x * b.x;
    }

    //! Inner product of a multivector and vector
    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr double   operator INNER(const Multivector1<T>& a, const Vector1<T>&b)  noexcept
    {
        return a.x * b.x;
    }

    //! Inner product of vector and multivector
    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr double   operator INNER(const Vector1<T>& a, const Multivector1<T>&b)  noexcept
    {
        return a.x * b.x;
    }

//  --------------------------------------------------------
//  OUTER PRODUCT

    // one dimensional space has no non-zero outer products

//  --------------------------------------------------------
//  CROSS PRODUCT

    // one dimensional space has no non-zero cross products

///  --------------------------------------------------------
//  OTIMES PRODUCT

//  --------------------------------------------------------
//  UNIONS

//  --------------------------------------------------------
//  INTERSECTIONS


//  --------------------------------------------------------
//  PROJECTIONS

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

}

YQ_TYPE_DECLARE(Multivector1D)
YQ_TYPE_DECLARE(Multivector1F)
