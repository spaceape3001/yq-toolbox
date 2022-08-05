////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__VECTOR_3__HPP 1
#include <math/preamble.hpp>
#include <math/Units.hpp>
#include <math/trig.hpp>
#include <math/Vector2.hpp>

namespace yq {
    /*! \brief Vector of 3 dimensions
    
        This is a 3 dimensional cartesian vector of the given type.
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Vector3 {
        //! Component data type argument to this structure (ie, template parameter T)
        using component_type = T;

        /*! \brief Creates a unit-vector in the x-dimension.
        */
        static consteval Vector3 unit_x() noexcept;
        /*! \brief Creates a unit-vector in the y-dimension.
        */
        static consteval Vector3 unit_y() noexcept;
        /*! \brief Creates a unit-vector in the z-dimension.
        */
        static consteval Vector3 unit_z() noexcept;

        T       x;
        T       y;
        T       z;;
        
        //! Equality operator (using default)
        constexpr bool operator==(const Vector3&) const noexcept = default;

        constexpr operator glm::vec<3, T, glm::defaultp>() const noexcept
        {
            return { x, y, z };
        }
    };

    YQ_IEEE754_1(Vector3)
    
//  --------------------------------------------------------
//  COMPOSITION


    /*! \brief Creates a 3 dimensioal vector
    
        Helper function to create a 3 dimensional cartesian vector where the component type is deduced from
        the first argument.
    */
    template <typename T>
    constexpr Vector3<T> vector(T x, std::type_identity_t<T> y, std::type_identity_t<T> z) noexcept
    {
        return {x,y,z};
    }
    
    template <typename T, glm::qualifier Q>
    constexpr Vector3<T> vector(const glm::vec<3,T,Q>& v) noexcept
    {
        return { v.x, v.y, v.z };
    }

    template <typename T>
    consteval Vector3<T> Vector3<T>::unit_x() noexcept
    {
        return {one_v<T>,zero_v<T>,zero_v<T>};
    }

    template <typename T>
    consteval Vector3<T> Vector3<T>::unit_y() noexcept
    {
        return {zero_v<T>,one_v<T>,zero_v<T>};
    }

    template <typename T>
    consteval Vector3<T> Vector3<T>::unit_z() noexcept
    {
        return {zero_v<T>,zero_v<T>,one_v<T>};
    }

    constexpr Vector3D operator "" _x3(unsigned long long int v) noexcept
    {
        return {(double) v, 0., 0.};
    }

    constexpr Vector3D operator "" _x3(long double v) noexcept
    {
        return {(double) v, 0., 0.};
    }

    constexpr Vector3D operator "" _y3(unsigned long long int v) noexcept
    {
        return {0., (double) v, 0.};
    }

    constexpr Vector3D operator "" _y3(long double v) noexcept
    {
        return {0., (double) v, 0.};
    }

    constexpr Vector3D operator "" _z3(unsigned long long int v) noexcept
    {
        return {0., 0., (double) v};
    }

    constexpr Vector3D operator "" _z3(long double v) noexcept
    {
        return {0., 0., (double) v};
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
    constexpr Vector2<T> xy( const Vector3<T>& a) noexcept
    {
        return { a.x, a.y };
    }

    template <typename T>
    constexpr Vector3<T> xy( const Vector2<T>& a, std::type_identity_t<T> z) noexcept
    {
        return { a.x, a.y, z };
    }
    
    YQ_NAN_1(Vector3, Vector3<T>{nan_v<T>, nan_v<T>, nan_v<T>})
    YQ_ZERO_1(Vector3, Vector3<T>{zero_v<T>, zero_v<T>, zero_v<T>})
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_NAN_1(Vector3, is_nan(v.x) || is_nan(v.y) || is_nan(v.z))
    YQ_IS_FINITE_1(Vector3, is_finite(v.x) && is_finite(v.y) && is_finite(v.z))
    
    /*! \brief Square of the vector's length
    
        This returns the SQUARE of the given vector's length.
    */
    template <typename T>
    constexpr square_t<T> length2(const Vector3<T>& a) noexcept
    {
        return a.x*a.x + a.y*a.y + a.z*a.z;
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
        
//  --------------------------------------------------------
//  POSITIVE

    template <typename T>
    constexpr Vector3<T> operator+(const Vector3<T>& a) noexcept
    {
        return a;
    }


//  --------------------------------------------------------
//  NEGATIVE

    template <typename T>
    constexpr Vector3<T> operator-(const Vector3<T>&a) noexcept
    {
        return {-a.x,-a.y,-a.z};
    }

//  --------------------------------------------------------
//  NORMALIZATION

    template <typename T>
    requires trait::has_sqrt_v<T>
    Vector3<quotient_t<T,T>> operator~(const Vector3<T>& a)
    {
        auto l = one_v<T>/length(a);
        return {a.x/l, a.y/l, a.z/l};
    }

//  --------------------------------------------------------
//  ADDITION

    template <typename T>
    constexpr Vector3<T> operator+(const Vector3<T>& a, const Vector3<T>& b) noexcept
    {
        return {a.x+b.x, a.y+b.y, a.z+b.z};
    }

    template <typename T>
    Vector3<T>& operator+=(Vector3<T>& a, const Vector3<T>& b) noexcept
    {
        a.x += b.x;
        a.y += b.y;
        a.z += b.z;
        return a;
    }

    
//  --------------------------------------------------------
//  SUBTRACTION

    template <typename T>
    constexpr Vector3<T> operator-(const Vector3<T>& a, const Vector3<T>& b) noexcept
    {
        return {a.x-b.x, a.y-b.y, a.z-b.z};
    }

    template <typename T>
    Vector3<T>& operator-=(Vector3<T>& a, const Vector3<T>& b) noexcept
    {
        a.x -= b.x;
        a.y -= b.y;
        a.z -= b.z;
        return a;
    }

//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires (std::is_arithmetic_v<T>)
    constexpr Vector3<product_t<T,U>> operator*(T a, const Vector3<U>&b) noexcept
    {
        return {a*b.x, a*b.y, a*b.z};
    }

    template <typename T, typename U>
    requires (std::is_arithmetic_v<U>)
    constexpr Vector3<product_t<T,U>> operator*(const Vector3<T>& a, U b) noexcept
    {
        return {a.x*b, a.y*b, a.z*b};
    }

    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Vector3<T>& operator*=(Vector3<T>& a, T b) noexcept
    {
        a.x *= b;
        a.y *= b;
        a.z *= b;
        return a;
    }
    
    template <typename T, typename U>
    constexpr Vector3<product_t<T,U>>    mul_elem(const Vector3<T>&a, const Vector3<T>&b) noexcept
    {
        return {a.x*b.x, a.y*b.y, a.z*b.z};
    }
    
//  --------------------------------------------------------
//  DIVISION

    template <typename T, typename U>
    requires (std::is_arithmetic_v<T>)
    constexpr  Vector3<quotient_t<T,U>> operator/(T a, const  Vector3<U>&b) noexcept
    {
        return (a*b) / length2(b);
    }

    template <typename T, typename U>
    requires (std::is_arithmetic_v<U>)
    constexpr  Vector3<quotient_t<T,U>> operator/(const  Vector3<T>& a, U b) noexcept
    {
        return {a.x / b, a.y / b, a.z / b};
    }

    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Vector3<T>& operator/=(Vector3<T>& a, U b) noexcept
    {
        a.x /= b;
        a.y /= b;
        a.z /= b;
        return a;
    }


    template <typename T, typename U>
    constexpr Vector3<quotient_t<T,U>>    div_elem(const Vector3<T>&a, const Vector3<T>&b) noexcept
    {
        return {a.x/b.x, a.y/b.y, a.z/b.z};
    }

//  --------------------------------------------------------
//  POWERS

    template <typename T>
    constexpr square_t<T> operator^(const Vector3<T>& a,two_t) noexcept
    {
        return a.x*a.x + a.y*a.y + a.z*a.z;
    }    

//  --------------------------------------------------------
//  DOT PRODUCT

    template <typename T, typename U>
    constexpr product_t<T,U> operator DOT (const Vector3<T>& a, const Vector3<U>&b) noexcept
    {
        return a.x*b.x + a.y*b.y + a.z*b.z;
    }


//  --------------------------------------------------------
//  INNER PRODUCT

    template <typename T, typename U>
    constexpr product_t<T,U> operator INNER (const Vector3<T>& a, const Vector3<U>&b) noexcept
    {
        return a.x*b.x + a.y*b.y + a.z*b.z;
    }


//  --------------------------------------------------------
//  OUTER PRODUCT


//  --------------------------------------------------------
//  CROSS PRODUCT


    template <typename T, typename U>
    constexpr Vector3<product_t<T,U>> operator CROSS (const Vector3<T>& a, const Vector3<U>&b) noexcept
    {
        return { 
            a.y*b.z-a.z*b.y, 
            a.z*b.x-a.x*b.z, 
            a.x*b.y-a.y*b.x 
        };
    }

///  --------------------------------------------------------
//  OTIMES PRODUCT

//  --------------------------------------------------------
//  PROJECTIONS

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

    template <typename T>
    constexpr Vector3<T>   abs_elem(const Vector3<T>&a) noexcept
    {
        return { abs(a.x), abs(a.y), abs(a.z) };
    }

    //! TRUE if every component of a is greater than b
    template <typename T>
    constexpr bool        all_greater(const Vector3<T>& a, const Vector3<T>&b) noexcept
    {
        return (a.x>b.x) && (a.y>b.y) && (a.z>b.z);
    }

    //! TRUE if every component of a is greater or equal to b
    template <typename T>
    constexpr bool        all_greater_equal(const Vector3<T>& a, const Vector3<T>&b) noexcept
    {
        return (a.x>=b.x) && (a.y>=b.y) && (a.z>=b.z);
    }

    //! TRUE if every component of a is less than b
    template <typename T>
    constexpr bool        all_less(const Vector3<T>& a, const Vector3<T>&b) noexcept
    {
        return (a.x<b.x) && (a.y<b.y) && (a.z<b.z);
    }

    //! TRUE if every component of a is less than (or equal to) b
    template <typename T>
    constexpr bool        all_less_equal(const Vector3<T>& a, const Vector3<T>&b) noexcept
    {
        return (a.x<=b.x) && (a.y<=b.y) && (a.z<=b.z);
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
    constexpr T             component_max(const Vector3<T>&a) noexcept
    {
        return max(max(a.x, a.y), a.z);
    }

    template <typename T>
    constexpr T             component_min(const Vector3<T>&a) noexcept
    {
        return max(max(a.x, a.y), a.z);
    }

    template <typename T>
    constexpr cube_t<T>       component_product(const Vector3<T>& a) noexcept
    {
        return a.x*a.y*a.z;
    }
    
    template <typename T>
    constexpr T   component_sum(const Vector3<T>& a) noexcept
    {
        return a.x + a.y + a.z;
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

    template <typename T>
    constexpr Vector3<T>   max_elem(const Vector3<T>&a, const Vector3<T>&b) noexcept
    {
        return {max(a.x, b.x) && max(a.y, b.y) && max(a.z, b.z)};
    }

    template <typename T>
    constexpr Vector3<T>   min_elem(const Vector3<T>&a, const Vector3<T>&b) noexcept
    {
        return {min(a.x, b.x) && min(a.y, b.y) && min(a.z, b.z)};
    }    
}

YQ_TYPE_DECLARE(yq::Vector3D)
YQ_TYPE_DECLARE(yq::Vector3F)
YQ_TYPE_DECLARE(yq::Vector3I)
YQ_TYPE_DECLARE(yq::Vector3U)

