////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/Vector1.hpp>
#include <math/Vector2.hpp>
#include <math/Vector3.hpp>
#include <math/Vector4.hpp>
#include <math/Units.hpp>
#include <math/trig.hpp>

namespace yq {

//  --------------------------------------------------------
//  COMPOSITION

    //! Creates a two dimension unit vector
    //!
    //! \param az   Counter-clockwise angle from +x
    inline Vector2D     ccw(Radian az)
    {
        return { cos(az), sin(az) };
    }
    
    //! Creates a three dimension unit vector
    //!
    //! \param az   Counter-clockwise angle from +x
    //! \param el   Elevation (up) angle from x-y plane
    inline  Vector3D    ccw(Radian az, Radian el)
    {
        double  c  = cos(el);
        return { c*cos(az), c*sin(az), sin(el) };
    }

    //! Creates a two dimension unit vector
    //!
    //! \param az    Clockwise angle from +x
    inline Vector2D     clockwise(Radian az)
    {
        return { sin(az), cos(az) };
    }

    //! Creates a three dimension unit vector
    //!
    //! \param az   Clockwise angle from +x
    //! \param el   Elevation (up) angle from x-y plane
    inline Vector3D     clockwise(Radian az, Radian el)
    {
        double  c  = cos(el);
        return { c*sin(az), c*cos(az), sin(el) };
    }

    template <typename T>
    Vector2<T> xy( const Vector3<T>& a)
    {
        return { a.x, a.y };
    }

    template <typename T>
    Vector3<T> xy( const Vector2<T>& a, std::type_identity_t<T> z)
    {
        return { a.x, a.y, z };
    }

//  --------------------------------------------------------
//  GETTERS

//  --------------------------------------------------------
//  SETTERS


//  --------------------------------------------------------
//  BASIC FUNCTIONS

    /*! \brief Square of the vector's length
    
        This returns the SQUARE of the given vector's length.
    */
    template <typename T>
    constexpr square_t<T> length2(const Vector1<T>& a)
    {
        return a.x*a.x;
    }    
    

    /*! \brief Square of the vector's length
    
        This returns the SQUARE of the given vector's length.
    */
    template <typename T>
    constexpr square_t<T> length2(const Vector2<T>& a)
    {
        return a.x*a.x + a.y*a.y;
    }    
    
    /*! \brief Square of the vector's length
    
        This returns the SQUARE of the given vector's length.
    */
    template <typename T>
    constexpr square_t<T> length2(const Vector3<T>& a)
    {
        return a.x*a.x + a.y*a.y + a.z*a.z;
    }    
    
    /*! \brief Square of the vector's length
    
        This returns the SQUARE of the given vector's length.
    */
    template <typename T>
    constexpr square_t<T> length2(const Vector4<T>& a)
    {
        return a.x*a.x + a.y*a.y + a.z*a.z + a.w*a.w;
    }    
    
    template <typename T>
    constexpr square_t<T> operator^(const Vector1<T>& a,two_t)
    {
        return a.x*a.x;
    }    

    template <typename T>
    constexpr square_t<T> operator^(const Vector2<T>& a,two_t)
    {
        return a.x*a.x + a.y*a.y;
    }    

    template <typename T>
    constexpr square_t<T> operator^(const Vector3<T>& a,two_t)
    {
        return a.x*a.x + a.y*a.y + a.z*a.z;
    }    

    template <typename T>
    constexpr square_t<T> operator^(const Vector4<T>& a,two_t)
    {
        return a.x*a.x + a.y*a.y + a.z*a.z + a.w*a.w;
    }    

    /*! \brief Length of the vector
        
        This returns the length of the given vector.
    */
    template <typename T>
    requires trait::has_abs_v<T>
    auto    length(const Vector1<T>& a)
    {
        return abs(a.x);
    }
    
    /*! \brief Length of the vector
        
        This returns the length of the given vector.
    */
    template <typename T>
    requires trait::has_sqrt_v<T>
    auto    length(const Vector2<T>& a)
    {
        return sqrt(length2(a));
    }

    /*! \brief Length of the vector
        
        This returns the length of the given vector.
    */
    template <typename T>
    requires trait::has_sqrt_v<T>
    auto    length(const Vector3<T>& a)
    {
        return sqrt(length2(a));
    }

    
    /*! \brief Length of the vector
        
        This returns the length of the given vector.
    */
    template <typename T>
    requires trait::has_sqrt_v<T>
    auto    length(const Vector4<T>& a)
    {
        return sqrt(length2(a));
    }

//  --------------------------------------------------------
//  POSITIVE

    template <typename T>
    constexpr Vector1<T> operator+(const Vector1<T>& a)
    {
        return a;
    }

    template <typename T>
    constexpr Vector2<T> operator+(const Vector2<T>& a)
    {
        return a;
    }

    template <typename T>
    constexpr Vector3<T> operator+(const Vector3<T>& a)
    {
        return a;
    }

    template <typename T>
    constexpr Vector4<T> operator+(const Vector4<T>& a)
    {
        return a;
    }

//  --------------------------------------------------------
//  NEGATIVE

    template <typename T>
    constexpr Vector1<T> operator-(const Vector1<T>&a)
    {
        return {-a.x};
    }

    template <typename T>
    constexpr Vector2<T> operator-(const Vector2<T>&a)
    {
        return {-a.x,-a.y};
    }

    template <typename T>
    constexpr Vector3<T> operator-(const Vector3<T>&a)
    {
        return {-a.x,-a.y,-a.z};
    }

    template <typename T>
    constexpr Vector4<T> operator-(const Vector4<T>&a)
    {
        return {-a.x,-a.y,-a.z,-a.w};
    }

//  --------------------------------------------------------
//  NORMALIZATION

    template <typename T>
    requires trait::has_copysign_v<T>
    Vector1<T> operator~(const Vector1<T>& a)
    {
        return Vector1<T>(copysign(one_v<T>, a.x));
    }

    template <typename T>
    requires trait::has_sqrt_v<T>
    Vector2<quotient_t<T,T>> operator~(const Vector2<T>& a)
    {
        auto l = one_v<T>/length(a);
        return {a.x/l, a.y/l};
    }

    template <typename T>
    requires trait::has_sqrt_v<T>
    Vector3<quotient_t<T,T>> operator~(const Vector3<T>& a)
    {
        auto l = one_v<T>/length(a);
        return {a.x/l, a.y/l, a.z/l};
    }

    template <typename T>
    requires trait::has_sqrt_v<T>
    Vector4<quotient_t<T,T>> operator~(const Vector4<T>& a)
    {
        auto l = one_v<T>/length(a);
        return {a.x/l, a.y/l, a.z/l, a.w/l};
    }


//  --------------------------------------------------------
//  ADDITION

    template <typename T>
    constexpr Vector1<T> operator+(const Vector1<T>& a, const Vector1<T>& b)
    {
        return {a.x+b.x};
    }

    template <typename T>
    constexpr Vector2<T> operator+(const Vector2<T>& a, const Vector2<T>& b)
    {
        return {a.x+b.x, a.y+b.y};
    }
    
    template <typename T>
    constexpr Vector3<T> operator+(const Vector3<T>& a, const Vector3<T>& b)
    {
        return {a.x+b.x, a.y+b.y, a.z+b.z};
    }

    template <typename T>
    constexpr Vector4<T> operator+(const Vector4<T>& a, const Vector4<T>& b)
    {
        return {a.x+b.x, a.y+b.y, a.z+b.z, a.w+b.w};
    }

    template <typename T>
    Vector1<T>& operator+=(Vector1<T>& a, const Vector1<T>& b)
    {
        a.x += b.x;
        return a;
    }
    
    template <typename T>
    Vector2<T>& operator+=(Vector2<T>& a, const Vector2<T>& b)
    {
        a.x += b.x;
        a.y += b.y;
        return a;
    }

    template <typename T>
    Vector3<T>& operator+=(Vector3<T>& a, const Vector3<T>& b)
    {
        a.x += b.x;
        a.y += b.y;
        a.z += b.z;
        return a;
    }

    template <typename T>
    Vector4<T>& operator+=(Vector4<T>& a, const Vector4<T>& b)
    {
        a.x += b.x;
        a.y += b.y;
        a.z += b.z;
        a.w += b.w;
        return a;
    }


//  --------------------------------------------------------
//  SUBTRACTION

    template <typename T>
    constexpr Vector1<T> operator-(const Vector1<T>& a, const Vector1<T>& b)
    {
        return {a.x-b.x};
    }

    template <typename T>
    constexpr Vector2<T> operator-(const Vector2<T>& a, const Vector2<T>& b)
    {
        return {a.x-b.x, a.y-b.y};
    }

    template <typename T>
    constexpr Vector3<T> operator-(const Vector3<T>& a, const Vector3<T>& b)
    {
        return {a.x-b.x, a.y-b.y, a.z-b.z};
    }
    
    template <typename T>
    constexpr Vector4<T> operator-(const Vector4<T>& a, const Vector4<T>& b)
    {
        return {a.x-b.x, a.y-b.y, a.z-b.z, a.w-b.w};
    }
    
    template <typename T>
    Vector1<T>& operator-=(Vector1<T>& a, const Vector1<T>& b)
    {
        a.x -= b.x;
        return a;
    }

    template <typename T>
    Vector2<T>& operator-=(Vector2<T>& a, const Vector2<T>& b)
    {
        a.x -= b.x;
        a.y -= b.y;
        return a;
    }

    template <typename T>
    Vector3<T>& operator-=(Vector3<T>& a, const Vector3<T>& b)
    {
        a.x -= b.x;
        a.y -= b.y;
        a.z -= b.z;
        return a;
    }
    
    template <typename T>
    Vector4<T>& operator-=(Vector4<T>& a, const Vector4<T>& b)
    {
        a.x -= b.x;
        a.y -= b.y;
        a.z -= b.z;
        a.w -= b.w;
        return a;
    }


//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires (std::is_arithmetic_v<T>)
    constexpr Vector1<product_t<T,U>> operator*(T a, const Vector1<U>&b)
    {
        return {a*b.x};
    }

    template <typename T, typename U>
    requires (std::is_arithmetic_v<T>)
    constexpr Vector2<product_t<T,U>> operator*(T a, const Vector2<U>&b)
    {
        return {a*b.x, a*b.y};
    }

    template <typename T, typename U>
    requires (std::is_arithmetic_v<T>)
    constexpr Vector3<product_t<T,U>> operator*(T a, const Vector3<U>&b)
    {
        return {a*b.x, a*b.y, a*b.z};
    }

    template <typename T, typename U>
    requires (std::is_arithmetic_v<T>)
    constexpr Vector4<product_t<T,U>> operator*(T a, const Vector4<U>&b)
    {
        return {a*b.x, a*b.y, a*b.z, a*b.w};
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U>)
    constexpr Vector1<product_t<T,U>> operator*(const Vector1<T>& a, U b)
    {
        return {a.x*b};
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U>)
    constexpr Vector2<product_t<T,U>> operator*(const Vector2<T>& a, U b)
    {
        return {a.x*b, a.y*b};
    }
    
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U>)
    constexpr Vector3<product_t<T,U>> operator*(const Vector3<T>& a, U b)
    {
        return {a.x*b, a.y*b, a.z*b};
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U>)
    constexpr Vector4<product_t<T,U>> operator*(const Vector4<T>& a, U b)
    {
        return {a.x*b, a.y*b, a.z*b, a.w*b};
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Vector1<T>& operator*=(Vector1<T>& a, T b)
    {
        a.x *= b;
        return a;
    }

    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Vector2<T>& operator*=(Vector2<T>& a, T b)
    {
        a.x *= b;
        a.y *= b;
        return a;
    }

    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Vector3<T>& operator*=(Vector3<T>& a, T b)
    {
        a.x *= b;
        a.y *= b;
        a.z *= b;
        return a;
    }

    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Vector4<T>& operator*=(Vector4<T>& a, T b)
    {
        a.x *= b;
        a.y *= b;
        a.z *= b;
        a.w *= b;
        return a;
    }

    template <typename T, typename U>
    product_t<T,U> operator*(const Vector1<T>&a, const Vector1<U>& b)
    {
        return a.x*b.x;
    }

    template <typename T, typename U>
    Vector1<product_t<T,U>>    mul_elem(const Vector1<T>&a, const Vector1<T>&b)
    {
        return {a.x*b.x};
    }

    template <typename T, typename U>
    Vector2<product_t<T,U>>    mul_elem(const Vector2<T>&a, const Vector2<T>&b)
    {
        return {a.x*b.x, a.y*b.y};
    }

    template <typename T, typename U>
    Vector3<product_t<T,U>>    mul_elem(const Vector3<T>&a, const Vector3<T>&b)
    {
        return {a.x*b.x, a.y*b.y, a.z*b.z};
    }

    template <typename T, typename U>
    Vector4<product_t<T,U>>    mul_elem(const Vector4<T>&a, const Vector4<T>&b)
    {
        return {a.x*b.x, a.y*b.y, a.z*b.z, a.w*b.w};
    }

//  --------------------------------------------------------
//  DIVISION

    template <typename T, typename U>
    requires (std::is_arithmetic_v<T>)
    constexpr  Vector1<quotient_t<T,U>> operator/(T a, const  Vector1<U>&b)
    {
        return (a*b) / length2(b);
    }

    template <typename T, typename U>
    requires (std::is_arithmetic_v<T>)
    constexpr  Vector2<quotient_t<T,U>> operator/(T a, const  Vector2<U>&b)
    {
        return (a*b) / length2(b);
    }


    template <typename T, typename U>
    requires (std::is_arithmetic_v<T>)
    constexpr  Vector3<quotient_t<T,U>> operator/(T a, const  Vector3<U>&b)
    {
        return (a*b) / length2(b);
    }

    template <typename T, typename U>
    requires (std::is_arithmetic_v<T>)
    constexpr  Vector4<quotient_t<T,U>> operator/(T a, const  Vector4<U>&b)
    {
        return (a*b) / length2(b);
    }

    template <typename T, typename U>
    requires (std::is_arithmetic_v<U>)
    constexpr  Vector1<quotient_t<T,U>> operator/(const  Vector1<T>& a, U b)
    {
        return {a.x / b};
    }

    template <typename T, typename U>
    requires (std::is_arithmetic_v<U>)
    constexpr  Vector2<quotient_t<T,U>> operator/(const  Vector2<T>& a, U b)
    {
        return {a.x / b, a.y / b};
    }


    template <typename T, typename U>
    requires (std::is_arithmetic_v<U>)
    constexpr  Vector3<quotient_t<T,U>> operator/(const  Vector3<T>& a, U b)
    {
        return {a.x / b, a.y / b, a.z / b};
    }

    template <typename T, typename U>
    requires (std::is_arithmetic_v<U>)
    constexpr  Vector4<quotient_t<T,U>> operator/(const  Vector4<T>& a, U b)
    {
        return {a.x / b, a.y / b, a.z / b, a.w / b};
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Vector1<T>& operator/=(Vector1<T>& a, U b)
    {
        a.x /= b;
        return a;
    }

    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Vector2<T>& operator/=(Vector2<T>& a, U b)
    {
        a.x /= b;
        a.y /= b;
        return a;
    }

    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Vector3<T>& operator/=(Vector3<T>& a, U b)
    {
        a.x /= b;
        a.y /= b;
        a.z /= b;
        return a;
    }

    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Vector4<T>& operator/=(Vector4<T>& a, U b)
    {
        a.x /= b;
        a.y /= b;
        a.z /= b;
        a.w /= b;
        return a;
    }

    template <typename T, typename U>
    quotient_t<T,U> operator/(const Vector1<T>&a, const Vector1<U>& b)
    {
        return (a*b)/length2(b);
    }

    template <typename T, typename U>
    Vector1<quotient_t<T,U>>    div_elem(const Vector1<T>&a, const Vector1<T>&b)
    {
        return {a.x/b.x};
    }

    template <typename T, typename U>
    Vector2<quotient_t<T,U>>    div_elem(const Vector2<T>&a, const Vector2<T>&b)
    {
        return {a.x/b.x, a.y/b.y};
    }


    template <typename T, typename U>
    Vector3<quotient_t<T,U>>    div_elem(const Vector3<T>&a, const Vector3<T>&b)
    {
        return {a.x/b.x, a.y/b.y, a.z/b.z};
    }
    
    template <typename T, typename U>
    Vector4<quotient_t<T,U>>    div_elem(const Vector4<T>&a, const Vector4<T>&b)
    {
        return {a.x/b.x, a.y/b.y, a.z/b.z, a.w/b.w};
    }

//  --------------------------------------------------------
//  DOT PRODUCT

    template <typename T, typename U>
    constexpr product_t<T,U> operator DOT (const Vector1<T>& a, const Vector1<U>&b)
    {
        return a.x*b.x;
    }

    template <typename T, typename U>
    constexpr product_t<T,U> operator DOT (const Vector2<T>& a, const Vector2<U>&b)
    {
        return a.x*b.x + a.y*b.y;
    }

    template <typename T, typename U>
    constexpr product_t<T,U> operator DOT (const Vector3<T>& a, const Vector3<U>&b)
    {
        return a.x*b.x + a.y*b.y + a.z*b.z;
    }

    template <typename T, typename U>
    constexpr product_t<T,U> operator DOT (const Vector4<T>& a, const Vector4<U>&b)
    {
        return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
    }

//  --------------------------------------------------------
//  INNER PRODUCT

    template <typename T, typename U>
    constexpr product_t<T,U> operator INNER (const Vector1<T>& a, const Vector1<U>&b)
    {
        return a.x*b.x;
    }

    template <typename T, typename U>
    constexpr product_t<T,U> operator INNER (const Vector2<T>& a, const Vector2<U>&b)
    {
        return a.x*b.x + a.y*b.y;
    }

    template <typename T, typename U>
    constexpr product_t<T,U> operator INNER (const Vector3<T>& a, const Vector3<U>&b)
    {
        return a.x*b.x + a.y*b.y + a.z*b.z;
    }


    template <typename T, typename U>
    constexpr product_t<T,U> operator INNER (const Vector4<T>& a, const Vector4<U>&b)
    {
        return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
    }

//  --------------------------------------------------------
//  CROSS PRODUCT

    template <typename T, typename U>
    constexpr product_t<T,U> operator CROSS (const Vector2<T>& a, const Vector2<U>&b)
    {
        return a.x*b.y-a.y*b.x;
    }

    template <typename T, typename U>
    constexpr Vector3<product_t<T,U>> operator CROSS (const Vector3<T>& a, const Vector3<U>&b)
    {
        return { 
            a.y*b.z-a.z*b.y, 
            a.z*b.x-a.x*b.z, 
            a.x*b.y-a.y*b.x 
        };
    }

//  --------------------------------------------------------
//  OUTER PRODUCT


///  --------------------------------------------------------
//  OTIMES PRODUCT

//  --------------------------------------------------------
//  PROJECTIONS

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

    template <typename T>
    Vector1<T>   abs_elem(const Vector1<T>&a)
    {
        return {abs(a.x)};
    }

    template <typename T>
    Vector2<T>   abs_elem(const Vector2<T>&a)
    {
        return { abs(a.x), abs(a.y) };
    }

    template <typename T>
    Vector3<T>   abs_elem(const Vector3<T>&a)
    {
        return { abs(a.x), abs(a.y), abs(a.z) };
    }

    template <typename T>
    Vector4<T>   abs_elem(const Vector4<T>&a)
    {
        return { abs(a.x), abs(a.y), abs(a.z), abs(a.w) };
    }

    //! TRUE if every component of a is greater than b
    template <typename T>
    constexpr bool        all_greater(const Vector1<T>& a, const Vector1<T>&b)
    {
        return (a.x>b.x);
    }

    //! TRUE if every component of a is greater than b
    template <typename T>
    constexpr bool        all_greater(const Vector2<T>& a, const Vector2<T>&b)
    {
        return (a.x>b.x) && (a.y>b.y);
    }

    //! TRUE if every component of a is greater than b
    template <typename T>
    constexpr bool        all_greater(const Vector3<T>& a, const Vector3<T>&b)
    {
        return (a.x>b.x) && (a.y>b.y) && (a.z>b.z);
    }

    //! TRUE if every component of a is greater than b
    template <typename T>
    constexpr bool        all_greater(const Vector4<T>& a, const Vector4<T>&b)
    {
        return (a.x>b.x) && (a.y>b.y) && (a.z>b.z) && (a.w>b.w);
    }

    //! TRUE if every component of a is greater or equal to b
    template <typename T>
    constexpr bool        all_greater_equal(const Vector1<T>& a, const Vector1<T>&b)
    {
        return (a.x>=b.x);
    }

    //! TRUE if every component of a is greater or equal to b
    template <typename T>
    constexpr bool        all_greater_equal(const Vector2<T>& a, const Vector2<T>&b)
    {
        return (a.x>=b.x) && (a.y>=b.y);
    }
    
    //! TRUE if every component of a is greater or equal to b
    template <typename T>
    constexpr bool        all_greater_equal(const Vector3<T>& a, const Vector3<T>&b)
    {
        return (a.x>=b.x) && (a.y>=b.y) && (a.z>=b.z);
    }

    //! TRUE if every component of a is greater or equal to b
    template <typename T>
    constexpr bool        all_greater_equal(const Vector4<T>& a, const Vector4<T>&b)
    {
        return (a.x>=b.x) && (a.y>=b.y) && (a.z>=b.z) && (a.w>=b.w);
    }
    

    //! TRUE if every component of a is less than b
    template <typename T>
    constexpr bool        all_less(const Vector1<T>& a, const Vector1<T>&b)
    {
        return (a.x<b.x);
    }

    //! TRUE if every component of a is less than b
    template <typename T>
    constexpr bool        all_less(const Vector2<T>& a, const Vector2<T>&b)
    {
        return (a.x<b.x) && (a.y<b.y);
    }

    //! TRUE if every component of a is less than b
    template <typename T>
    constexpr bool        all_less(const Vector3<T>& a, const Vector3<T>&b)
    {
        return (a.x<b.x) && (a.y<b.y) && (a.z<b.z);
    }

    //! TRUE if every component of a is less than b
    template <typename T>
    constexpr bool        all_less(const Vector4<T>& a, const Vector4<T>&b)
    {
        return (a.x<b.x) && (a.y<b.y) && (a.z<b.z) && (a.w<b.w);
    }

    //! TRUE if every component of a is less than (or equal to) b
    template <typename T>
    constexpr bool        all_less_equal(const Vector1<T>& a, const Vector1<T>&b)
    {
        return (a.x<=b.x);
    }

    //! TRUE if every component of a is less than (or equal to) b
    template <typename T>
    constexpr bool        all_less_equal(const Vector2<T>& a, const Vector2<T>&b)
    {
        return (a.x<=b.x) && (a.y<=b.y);
    }

    //! TRUE if every component of a is less than (or equal to) b
    template <typename T>
    constexpr bool        all_less_equal(const Vector3<T>& a, const Vector3<T>&b)
    {
        return (a.x<=b.x) && (a.y<=b.y) && (a.z<=b.z);
    }

    //! TRUE if every component of a is less than (or equal to) b
    template <typename T>
    constexpr bool        all_less_equal(const Vector4<T>& a, const Vector4<T>&b)
    {
        return (a.x<=b.x) && (a.y<=b.y) && (a.z<=b.z) && (a.w<=b.w);
    }

    template <typename T>
    requires (std::is_floating_point_v<T> && trait::has_sqrt_v<T>)
    Radian       angle(const Vector2<T>&a, const Vector2<T>& b)
    {
        return acos( std::clamp<T>( (a*b)/(length(a)*length(b)), -one_v<T>, one_v<T>));
    }

    template <typename T, typename DIM1, typename DIM2>
    requires (std::is_floating_point_v<T> && trait::has_sqrt_v<T>)
    Radian      angle(const Vector2<MKS<T,DIM1>>&a, const Vector2<MKS<T,DIM2>>& b)
    {
        using one_t = MKS<T,dim::None>;
        return acos( std::clamp<one_t>( (a*b)/(length(a)*length(b)), -one_v<T>, one_v<T>));
    }

    template <typename T>
    requires (std::is_floating_point_v<T> && trait::has_sqrt_v<T>)
    Radian              angle(const Vector3<T>&a, const Vector3<T>& b)
    {
        return acos( std::clamp<T>( (a*b)/(length(a)*length(b)), -one_v<T>, one_v<T>));
    }
    
    template <typename T, typename DIM1, typename DIM2>
    requires (std::is_floating_point_v<T> && trait::has_sqrt_v<T>)
    Radian             angle(const Vector3<MKS<T,DIM1>>&a, const Vector3<MKS<T,DIM2>>& b)
    {
        using one_t = MKS<T,dim::None>;
        return acos( std::clamp<one_t>( (a*b)/(length(a)*length(b)), -one_v<T>, one_v<T>));
    }


    template <typename T>
    requires (std::is_floating_point_v<T> && trait::has_sqrt_v<T>)
    Radian       angle(const Vector4<T>&a, const Vector4<T>& b)
    {
        return acos( std::clamp<T>( (a*b)/(length(a)*length(b)), -one_v<T>, one_v<T>));
    }
    
    template <typename T, typename DIM1, typename DIM2>
    requires (std::is_floating_point_v<T> && trait::has_sqrt_v<T>)
    Radian       angle(const Vector4<MKS<T,DIM1>>&a, const Vector4<MKS<T,DIM2>>& b)
    {
        using one_t = MKS<T,dim::None>;
        return acos( std::clamp<one_t>( (a*b)/(length(a)*length(b)), -one_v<T>, one_v<T>));
    }
    
    /*! \brief Counter clockwise (euler) angle
    
        Computes the euler angle of the vector, ie, counter-clockwise from the +X axis.
    */
    template <typename T>
    requires std::is_floating_point_v<T>
    Radian   ccw(const Vector2<T>& a)
    {
        return atan(a.y, a.x);
    }

    /*! \brief Counter clockwise (euler) angle
    
        Computes the euler angle of the vector, ie, counter-clockwise from the +X axis.
    */
    template <typename T, typename DIM>
    requires std::is_floating_point_v<T>
    Radian   ccw(const Vector2<MKS<T,DIM>>& a)
    {
        return atan(a.y, a.x);
    }
    
    /*! \brief Counter clockwise (euler) angle
    
        Computes the euler angle of the vector, ie, counter-clockwise from the +X axis.
    */
    template <typename T>
    requires std::is_floating_point_v<T>
    Radian   ccw(const Vector3<T>& a)
    {
        return atan(a.y, a.x);
    }

    /*! \brief Counter clockwise (euler) angle
    
        Computes the euler angle of the vector, ie, counter-clockwise from the +X axis.
    */
    template <typename T, typename DIM>
    requires std::is_floating_point_v<T>
    Radian   ccw(const Vector3<MKS<T,DIM>>& a)
    {
        return atan(a.y, a.x);
    }


    /*! \brief Clockwise angle
    
        Computes the angle of the vector from the +Y axis.
    */
    template <typename T>
    requires std::is_floating_point_v<T>
    MKS<T,dim::Angle>   clockwise(const Vector2<T>& a)
    {
        return atan(a.y, a.x);
    }

    /*! \brief Clockwise angle
    
        Computes the angle of the vector from the +Y axis.
    */
    template <typename T, typename DIM>
    requires std::is_floating_point_v<T>
    MKS<T,dim::Angle>   clockwise(const Vector2<MKS<T,DIM>>& a)
    {
        return atan(a.y, a.x);
    }

    /*! \brief Clockwise angle
    
        Computes the angle of the vector from the +Y axis.
    */
    template <typename T>
    requires std::is_floating_point_v<T>
    MKS<T,dim::Angle>   clockwise(const Vector3<T>& a)
    {
        return atan(a.y, a.x);
    }

    /*! \brief Clockwise angle
    
        Computes the angle of the vector from the +Y axis.
    */
    template <typename T, typename DIM>
    requires std::is_floating_point_v<T>
    MKS<T,dim::Angle>   clockwise(const Vector3<MKS<T,DIM>>& a)
    {
        return atan(a.y, a.x);
    }

    template <typename T>
    square_t<T>     component_product(const Vector2<T>& a)
    {
        return a.x*a.y;
    }

    template <typename T>
    cube_t<T>       component_product(const Vector3<T>& a)
    {
        return a.x*a.y*a.z;
    }

    template <typename T>
    fourth_t<T>     component_product(const Vector4<T>& a)
    {
        return a.x*a.y*a.z*a.w;
    }
    
    template <typename T>
    T   component_sum(const Vector2<T>& a)
    {
        return a.x + a.y;
    }

    template <typename T>
    T   component_sum(const Vector3<T>& a)
    {
        return a.x + a.y + a.z;
    }

    template <typename T>
    T   component_sum(const Vector4<T>& a)
    {
        return a.x + a.y + a.z + a.w;
    }

    template <typename T, typename R>
    bool is_close(const R& compare, const Vector1<T>& actual, const Vector1<T>& expected)
    {
        return compare(length(actual-expected), length(expected));
    }

    template <typename T, typename R>
    bool is_close(const R& compare, const Vector1<T>& actual, std::type_identity_t<T> x)
    {
        return is_close(compare, actual, Vector1<T>{x} );
    }

    template <typename T, typename R>
    bool is_close(const R& compare, const Vector2<T>& actual, const Vector2<T>& expected)
    {
        return compare(length(actual-expected), length(expected));
    }

    template <typename T, typename R>
    bool is_close(const R& compare, const Vector2<T>& actual, std::type_identity_t<T> x, std::type_identity_t<T> y)
    {
        return is_close(compare, actual, Vector2<T>{x, y} );
    }

    template <typename T, typename R>
    bool is_close(const R& compare, const Vector3<T>& actual, const Vector3<T>& expected)
    {
        return compare(length(actual-expected), length(expected));
    }
    
    template <typename T, typename R>
    bool is_close(const R& compare, const Vector3<T>& actual, std::type_identity_t<T> x, std::type_identity_t<T> y, std::type_identity_t<T> z)
    {
        return is_close(compare, actual, Vector3<T>{x, y, z} );
    }

    template <typename T, typename R>
    bool is_close(const R& compare, const Vector4<T>& actual, const Vector4<T>& expected)
    {
        return compare(length(actual-expected), length(expected));
    }
    
    template <typename T, typename R>
    bool is_close(const R& compare, const Vector4<T>& actual, std::type_identity_t<T> x, std::type_identity_t<T> y, std::type_identity_t<T> z,std::type_identity_t<T>w)
    {
        return is_close(compare, actual, Vector4<T>{x, y, z, w} );
    }

    template <typename T>
    constexpr Vector1<T>   max_elem(const Vector1<T>&a, const Vector1<T>&b)
    {
        return {max(a.x, b.x)};
    }

    template <typename T>
    constexpr Vector2<T>   max_elem(const Vector2<T>&a, const Vector2<T>&b)
    {
        return {max(a.x, b.x) && max(a.y, b.y)};
    }

    template <typename T>
    constexpr Vector3<T>   max_elem(const Vector3<T>&a, const Vector3<T>&b)
    {
        return {max(a.x, b.x) && max(a.y, b.y) && max(a.z, b.z)};
    }
    
    template <typename T>
    constexpr Vector4<T>   max_elem(const Vector4<T>&a, const Vector4<T>&b)
    {
        return {max(a.x, b.x) && max(a.y, b.y) && max(a.z, b.z) && max(a.w, b.w)};
    }
    
    template <typename T>
    constexpr Vector1<T>   min_elem(const Vector1<T>&a, const Vector1<T>&b)
    {
        return {min(a.x, b.x)};
    }

    template <typename T>
    constexpr Vector2<T>   min_elem(const Vector2<T>&a, const Vector2<T>&b)
    {
        return {min(a.x, b.x) && min(a.y, b.y)};
    }

    template <typename T>
    constexpr Vector3<T>   min_elem(const Vector3<T>&a, const Vector3<T>&b)
    {
        return {min(a.x, b.x) && min(a.y, b.y) && min(a.z, b.z)};
    }    
    
    template <typename T>
    constexpr Vector4<T>   min_elem(const Vector4<T>&a, const Vector4<T>&b)
    {
        return {min(a.x, b.x) && min(a.y, b.y) && min(a.z, b.z) && min(a.w, b.w)};
    }


//  --------------------------------------------------------
//  CONDITIONAL INCLUDES

}
