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
        unity_t<T>  a;
        T           x;
        
        constexpr bool operator==(const Multivector1&) const noexcept = default;
    };

    YQ_IEEE754_1(Multivector1)

//  --------------------------------------------------------
//  COMPOSITION

    YQ_NAN_1(Multivector1, Multivector1<T>{nan_v<unity_t<T>>, nan_v<T>})
    YQ_ZERO_1(Multivector1, Multivector1<T>{zero_v<unity_t<T>>, zero_v<T>})
    
//  --------------------------------------------------------
//  GETTERS

    template <typename T>
    constexpr Vector1<T> vector(const Multivector1<T>& a) noexcept
    {
        return { a.x };
    }

//  --------------------------------------------------------
//  BASIC FUNCTIONS

    /*! \brief Checks for finiteness
    */
    template <typename T>
    constexpr bool is_finite(const Multivector1<T>&v)
    { 
        return is_finite(v.a) && is_finite(v.x);
    }
    
    YQ_IS_NAN_1(Multivector1, is_nan(v.a) || is_nan(v.x) )

//  --------------------------------------------------------
//  POSITIVE

    template <typename T>
    constexpr Multivector1<T> operator+(const Multivector1<T>& a) noexcept
    {
        return a;
    }

//  --------------------------------------------------------
//  NEGATIVE

    template <typename T>
    constexpr Multivector1<T> operator-(const Multivector1<T>& a) noexcept
    {
        return {-a.a, -a.x};
    }

//  --------------------------------------------------------
//  NORMALIZATION


//  --------------------------------------------------------
//  ADDITION

    template <typename T>
    constexpr Multivector1<T> operator+(const Multivector1<T>& a, const Multivector1<T>&  b) noexcept
    {
        return {
            a.a+b.a,
            a.x+b.x
        };
    }

    template <typename T>
    Multivector1<T>& operator+=(Multivector1<T>& a, const Multivector1<T>& b) noexcept
    {
        a.a += b.a;
        a.x += b.x;
        return a;
    }

    template <typename T>
    constexpr Multivector1<T> operator+(const Multivector1<T>& a, unity_t<T>  b) noexcept
    {
        return {
            a.a+b,
            a.x
        };
    }

    template <typename T>
    Multivector1<T>& operator+=(Multivector1<T>& a, unity_t<T>  b) noexcept
    {
        a.a += b;
        return a;
    }
    

    template <typename T>
    constexpr Multivector1<T> operator+(const Multivector1<T>& a, const Vector1<T>&  b) noexcept
    {
        return {
            a.a,
            a.x+b.x
        };
    }

    template <typename T>
    Multivector1<T>& operator+=(Multivector1<T>& a, const Vector1<T>& b) noexcept
    {
        a.x += b.x;
        return a;
    }
    
    template <typename T>
    constexpr Multivector1<T> operator+(unity_t<T> a, const Multivector1<T>& b) noexcept
    {
        return { 
            a+b.a, 
            b.x 
        };
    }

    template <typename T>
    constexpr Multivector1<T> operator+(unity_t<T> a, const Vector1<T>& b) noexcept
    {
        return { 
            a, 
            b.x 
        };
    }

    template <typename T>
    constexpr Multivector1<T> operator+(Vector1<T> a, const Multivector1<T>& b) noexcept
    {
        return { 
            b.a, 
            a.x+b.x
        };
    }

    template <typename T>
    constexpr Multivector1<T> operator+(Vector1<T> a, unity_t<T>  b) noexcept
    {
        return { 
            b, 
            a.x 
        };
    }
    
    
//  --------------------------------------------------------
//  SUBTRACTION

    template <typename T>
    constexpr Multivector1<T> operator-(const Multivector1<T>& a, const Multivector1<T>& b) noexcept
    {
        return {
            a.a-b.a,
            a.x-b.x
        };
    }

    template <typename T>
    Multivector1<T>& operator-=(Multivector1<T>& a, const Multivector1<T>& b) noexcept
    {
        a.a -= b.a;
        a.x -= b.x;
        return a;
    }

    template <typename T>
    constexpr Multivector1<T> operator-(const Multivector1<T>& a, unity_t<T> b) noexcept
    {
        return {
            a.a-b,
            a.x
        };
    }

    template <typename T>
    Multivector1<T>& operator-=(Multivector1<T>& a, unity_t<T> b) noexcept
    {
        a.a -= b;
        return a;
    }
    


    template <typename T>
    constexpr Multivector1<T> operator-(const Multivector1<T>& a, const Vector1<T>& b) noexcept
    {
        return {
            a.a,
            a.x-b.x
        };
    }

    template <typename T>
    Multivector1<T>& operator-=(Multivector1<T>& a, const Vector1<T>& b) noexcept
    {
        a.x -= b.x;
        return a;
    }
    
    template <typename T>
    constexpr Multivector1<T> operator-(unity_t<T> a, const Multivector1<T>& b) noexcept
    {
        return { 
            a-b.a, 
            -b.x 
        };
    }

    template <typename T>
    constexpr Multivector1<T> operator-(unity_t<T> a, const Vector1<T>& b) noexcept
    {
        return { 
            a, 
            -b.x 
        };
    }

    template <typename T>
    constexpr Multivector1<T> operator-(Vector1<T> a, const Multivector1<T>& b) noexcept
    {
        return { 
            -b.a, 
            a.x-b.x
        };
    }

    template <typename T>
    constexpr Multivector1<T> operator-(Vector1<T> a, unity_t<T> b) noexcept
    {
        return { 
            -b, 
            a.x 
        };
    }


//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Multivector1<T> operator*(T a, const Multivector1<T>&b) noexcept
    {
        return { a*b.a, a*b.x };
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Multivector1<T> operator*(const Multivector1<T>& a, T b) noexcept
    {
        return { a.a*b, a.x*b };
    }


    template <typename T>
    requires std::is_floating_point_v<T>
    Multivector1<T>& operator*=(Multivector1<T>& a, T b) noexcept
    {
        a.a*=b; a.x*=b;
        return a;
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Multivector1<T> operator*(const Vector1<T>& a, const Multivector1<T>& b) noexcept
    {
        return Multivector1<T>( a.x * b.x, a.x * b.a);
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Multivector1<T> operator*(const Multivector1<T>& a, const Vector1<T>& b) noexcept
    {
        return Multivector1<T>( a.x*b.x, a.a*b.x );
    }


    template <typename T>
    requires std::is_floating_point_v<T>
    Multivector1<T>& operator*=(Multivector1<T>& a, const Vector1<T>& b) noexcept
    {
        a.x *= b.x;
        a.a *= b.x;
        return a;
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Multivector1<T> operator*(const Multivector1<T>& a, const Multivector1<T>& b) noexcept
    {
        return Multivector1<T>( a.a*b.a+a.x*b.x, a.a*b.x+a.x*b.a );
    }
    
    template <typename T>
    requires std::is_floating_point_v<T>
    Multivector1<T> operator*=(Multivector1<T>& a, const Multivector1<T>& b) noexcept
    {
        a   = a*b;
        return a;
    }

//  --------------------------------------------------------
//  DIVISION

    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Multivector1<T> operator/(const Multivector1<T>& a, T b) noexcept
    {
        return { a.a/b, a.x/b };
    }


    template <typename T>
    requires std::is_floating_point_v<T>
    Multivector1<T>& operator/=(Multivector1<T>& a, T b) noexcept
    {
        a.a/=b; a.x/=b;
        return a;
    }

//  --------------------------------------------------------
//  POWERS

//  --------------------------------------------------------
//  DOT PRODUCT


//  --------------------------------------------------------
//  INNER PRODUCT

    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr double   operator INNER(const Multivector1<T>& a, const Multivector1<T>&b)  noexcept
    {
        return a.x * b.x;
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr double   operator INNER(const Multivector1<T>& a, const Vector1<T>&b)  noexcept
    {
        return a.x * b.x;
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr double   operator INNER(const Vector1<T>& a, const Multivector1<T>&b)  noexcept
    {
        return a.x * b.x;
    }

//  --------------------------------------------------------
//  OUTER PRODUCT


//  --------------------------------------------------------
//  CROSS PRODUCT


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
