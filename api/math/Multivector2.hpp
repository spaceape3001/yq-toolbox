////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>
#include <math/Vector2.hpp>
#include <math/Bivector2.hpp>

namespace yq {

    /*! \brief Two dimensional multivector
    */
    template <typename T>
    struct Multivector2 {
        unity_t<T>      a;
        T               x, y;
        square_t<T>     xy;
        
        constexpr bool operator==(const Multivector2&) const noexcept = default;
    };

    YQ_IEEE754_1(Multivector2)

//  --------------------------------------------------------
//  COMPOSITION

    YQ_NAN_1(Multivector2, Multivector2<T>{nan_v<unity_t<T>>, nan_v<T>, nan_v<T>, nan_v<square_t<T>>})
    YQ_ZERO_1(Multivector2, Multivector2<T>{zero_v<unity_t<T>>, zero_v<T>, zero_v<T>, zero_v<square_t<T>>})

//  --------------------------------------------------------
//  GETTERS

    template <typename T>
    constexpr Bivector2<T> bivector(const Multivector2<T>& a) noexcept
    {
        return { a.xy };
    }

    template <typename T>
    constexpr Vector2<T> vector(const Multivector2<T>& a) noexcept
    {
        return { a.x, a.y };
    }

//  --------------------------------------------------------
//  BASIC FUNCTIONS
    
    /*! \brief Checks for finiteness
    */
    template <typename T>
    constexpr bool is_finite(const Multivector2<T>&v)
    { 
        return is_finite(v.a) && is_finite(v.x) && is_finite(v.y) && is_finite(v.xy);
    }
    
    YQ_IS_NAN_1(Multivector2, is_nan(v.a) || is_nan(v.x) || is_nan(v.y) || is_nan(v.xy))


//  --------------------------------------------------------
//  POSITIVE

    template <typename T>
    constexpr Multivector2<T> operator+(const Multivector2<T>& a) noexcept
    {
        return a;
    }

//  --------------------------------------------------------
//  NEGATIVE

    template <typename T>
    constexpr Multivector2<T> operator-(const Multivector2<T>& a) noexcept
    {
        return {-a.a, -a.x, -a.y, -a.xy};
    }



//  --------------------------------------------------------
//  NORMALIZATION


//  --------------------------------------------------------
//  ADDITION

    template <typename T>
    constexpr Multivector2<T> operator+(Bivector2<T> a, const Multivector2<T>& b) noexcept
    {
        return { 
            b.a, 
            b.x, b.y,
            a+b.xy
        };
    }


    template <typename T>
    constexpr Multivector2<T> operator+(Bivector2<T> a, unity_t<T>  b) noexcept
    {
        return { 
            b, 
            {}, {},
            a.xy
        };
    }

    template <typename T>
    constexpr Multivector2<T> operator+(Bivector2<T> a, const Vector2<T>& b) noexcept
    {
        return { 
            {}, 
            b.x, b.y, 
            a.xy 
        };
    }

    template <typename T>
    constexpr Multivector2<T> operator+(const Multivector2<T>& a, const Bivector2<T>& b) noexcept
    {
        return {
            a.a,
            a.x, a.y,
            a.xy + b.xy
        };
    }

    template <typename T>
    Multivector2<T>& operator+=(Multivector2<T>& a, const Bivector2<T>& b) noexcept
    {
        a.xy += b.xy;
        return a;
    }

    template <typename T>
    constexpr Multivector2<T> operator+(const Multivector2<T>& a, const Multivector2<T>&  b) noexcept
    {
        return {
            a.a+b.a,
            a.x+b.x, a.y+b.y,
            a.xy+b.xy
        };
    }

    template <typename T>
    Multivector2<T>& operator+=(Multivector2<T>& a, const Multivector2<T>& b) noexcept
    {
        a.a += b.a;
        a.x += b.x; a.y += b.y; 
        a.xy += b.xy;
        return a;
    }
        
    template <typename T>
    constexpr Multivector2<T> operator+(const Multivector2<T>& a, unity_t<T>  b) noexcept
    {
        return {
            a.a+b,
            a.x, a.y,
            a.xy
        };
    }

    template <typename T>
    Multivector2<T>& operator+=(Multivector2<T>& a, unity_t<T>  b) noexcept
    {
        a.a += b;
        return a;
    }


    template <typename T>
    constexpr Multivector2<T> operator+(const Multivector2<T>& a, const Vector2<T>&  b) noexcept
    {
        return {
            a.a,
            a.x+b.x, a.y+b.y,
            a.xy
        };
    }

    template <typename T>
    Multivector2<T>& operator+=(Multivector2<T>& a, const Vector2<T>& b) noexcept
    {
        a.x += b.x; a.y += b.y; 
        return a;
    }

    template <typename T>
    constexpr Multivector2<T> operator+(unity_t<T> a, const Bivector2<T>& b) noexcept
    {
        return { 
            a, 
            {}, {},
            b 
        };
    }


    template <typename T>
    constexpr Multivector2<T> operator+(unity_t<T> a, const Multivector2<T>& b) noexcept
    {
        return { 
            a+b.a, 
            b.x, b.y, 
            b.xy
        };
    }

    template <typename T>
    constexpr Multivector2<T> operator+(unity_t<T> a, const Vector2<T>& b) noexcept
    {
        return { 
            a, 
            b.x, b.y, 
            {} 
        };
    }

    template <typename T>
    constexpr Multivector2<T> operator+(Vector2<T> a, const Bivector2<T>& b) noexcept
    {
        return { 
            {}, 
            a.x, a.y, 
            b.xy 
        };
    }

    template <typename T>
    constexpr Multivector2<T> operator+(Vector2<T> a, const Multivector2<T>& b) noexcept
    {
        return { 
            b.a, 
            a.x+b.x, a.y+b.y,
            b.xy
        };
    }

    template <typename T>
    constexpr Multivector2<T> operator+(Vector2<T> a, unity_t<T>  b) noexcept
    {
        return { 
            b, 
            a.x, a.y, 
            {} 
        };
    }



//  --------------------------------------------------------
//  SUBTRACTION


    template <typename T>
    constexpr Multivector2<T> operator-(Bivector2<T> a, const Multivector2<T>& b) noexcept
    {
        return { 
            -b.a, 
            -b.x, -b.y,
            a-b.xy
        };
    }


    template <typename T>
    constexpr Multivector2<T> operator-(Bivector2<T> a, unity_t<T> b) noexcept
    {
        return { 
            -b, 
            {}, {},
            a.xy
        };
    }

    template <typename T>
    constexpr Multivector2<T> operator-(Bivector2<T> a, const Vector2<T>& b) noexcept
    {
        return { 
            {}, 
            -b.x, -b.y, 
            a.xy 
        };
    }

   template <typename T>
    constexpr Multivector2<T> operator-(const Multivector2<T>& a, const Bivector2<T>& b) noexcept
    {
        return {
            a.a,
            a.x, a.y,
            a.xy - b.xy
        };
    }

    template <typename T>
    Multivector2<T>& operator-=(Multivector2<T>& a, const Bivector2<T>& b) noexcept
    {
        a.xy -= b.xy;
        return a;
    }

    template <typename T>
    constexpr Multivector2<T> operator-(const Multivector2<T>& a, const Multivector2<T>& b) noexcept
    {
        return {
            a.a-b.a,
            a.x-b.x, a.y-b.y,
            a.xy-b.xy
        };
    }

    template <typename T>
    Multivector2<T>& operator-=(Multivector2<T>& a, const Multivector2<T>& b) noexcept
    {
        a.a -= b.a;
        a.x -= b.x; a.y -= b.y; 
        a.xy -= b.xy;
        return a;
    }
        
    template <typename T>
    constexpr Multivector2<T> operator-(const Multivector2<T>& a, unity_t<T> b) noexcept
    {
        return {
            a.a-b,
            a.x, a.y,
            a.xy
        };
    }

    template <typename T>
    Multivector2<T>& operator-=(Multivector2<T>& a, unity_t<T> b) noexcept
    {
        a.a -= b;
        return a;
    }



    template <typename T>
    constexpr Multivector2<T> operator-(const Multivector2<T>& a, const Vector2<T>& b) noexcept
    {
        return {
            a.a,
            a.x-b.x, a.y-b.y,
            a.xy
        };
    }

    template <typename T>
    Multivector2<T>& operator-=(Multivector2<T>& a, const Vector2<T>& b) noexcept
    {
        a.x -= b.x; a.y -= b.y; 
        return a;
    }
    
    template <typename T>
    constexpr Multivector2<T> operator-(unity_t<T> a, const Bivector2<T>& b) noexcept
    {
        return { 
            a, 
            {}, {},
            -b 
        };
    }    

    template <typename T>
    constexpr Multivector2<T> operator-(unity_t<T> a, const Multivector2<T>& b) noexcept
    {
        return { 
            a-b.a, 
            -b.x, -b.y, 
            -b.xy
        };
    }

    template <typename T>
    constexpr Multivector2<T> operator-(unity_t<T> a, const Vector2<T>& b) noexcept
    {
        return { 
            a, 
            -b.x, -b.y, 
            {} 
        };
    }

    template <typename T>
    constexpr Multivector2<T> operator-(Vector2<T> a, const Bivector2<T>& b) noexcept
    {
        return { 
            {}, 
            a.x, a.y, 
            -b.xy 
        };
    }

    template <typename T>
    constexpr Multivector2<T> operator-(Vector2<T> a, const Multivector2<T>& b) noexcept
    {
        return { 
            -b.a, 
            a.x-b.x, a.y-b.y,
            -b.xy
        };
    }

    template <typename T>
    constexpr Multivector2<T> operator-(Vector2<T> a, unity_t<T> b) noexcept
    {
        return { 
            -b, 
            a.x, a.y, 
            {} 
        };
    }

    
//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Multivector2<T> operator*(T a, const Multivector2<T>&b) noexcept
    {
        return { 
            a*b.a, 
            a*b.x, a*b.y, 
            a*b.xy 
        };
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Multivector2<T> operator*(const Multivector2<T>& a, T b) noexcept
    {
        return { 
            a.a*b, 
            a.x*b, a.y*b, 
            a.xy*b 
        };
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    Multivector2<T>& operator*=(Multivector2<T>& a, T b) noexcept
    {
        a.a  *= b;
        a.x  *= b; a.y *= b; 
        a.xy *= b;
        return a;
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Multivector2<T>   operator* (const Vector2<T>&a, const Vector2<T>&b) 
    {
        return { a.x*b.x+a.y*b.y, 0., 0., a.x*b.y-a.y*b.x };
    }

//  --------------------------------------------------------
//  DIVISION

    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Multivector2<T> operator/(const Multivector2<T>& a, T b) noexcept
    {
        return { 
            a.a/b, 
            a.x/b, a.y/b, 
            a.xy/b 
        };
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    Multivector2<T>& operator/=(Multivector2<T>& a, T b) noexcept
    {
        a.a  /= b;
        a.x  /= b; a.y /= b; 
        a.xy /= b;
        return a;
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Multivector2<T>   operator/ (const Vector2<T>&a, const Vector2<T>&b) 
    {
        return (a * b) / length2(b);
    }

//  --------------------------------------------------------
//  POWERS

//  --------------------------------------------------------
//  DOT PRODUCT


//  --------------------------------------------------------
//  INNER PRODUCT


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

YQ_TYPE_DECLARE(Multivector2D)
YQ_TYPE_DECLARE(Multivector2F)
