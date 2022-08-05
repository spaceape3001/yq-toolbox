////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__VECTOR_4__HPP 1
#include <math/preamble.hpp>
#include <math/Units.hpp>
#include <math/trig.hpp>

namespace yq {
    /*! \brief Vector of 4 dimension(s)
    
        This is a 4 dimensional cartesian vector of the given type.
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Vector4 {
        //! Component data type argument to this structure (ie, template parameter T)
        using component_type = T;
        
        /*! \brief Creates a unit-vector in the $(bit)s dimension.
        */
        static consteval Vector4 unit_x();
        /*! \brief Creates a unit-vector in the $(bit)s dimension.
        */
        static consteval Vector4 unit_y();
        /*! \brief Creates a unit-vector in the $(bit)s dimension.
        */
        static consteval Vector4 unit_z();
        /*! \brief Creates a unit-vector in the $(bit)s dimension.
        */
        static consteval Vector4 unit_w();

        //! Component for the $(bit)s dimension.
        T       x;
        //! Component for the $(bit)s dimension.
        T       y;
        //! Component for the $(bit)s dimension.
        T       z;
        //! Component for the $(bit)s dimension.
        T       w;;
        
        //! Equality operator (using default)
        constexpr bool operator==(const Vector4&) const noexcept = default;
        
        constexpr operator glm::vec<4, T, glm::defaultp>() const noexcept
        {
            return { x, y, z, w };
        }
    };
    
    YQ_IEEE754_1(Vector4)
    

//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Creates a 4 dimensioal vector
    
        Helper function to create a 4 dimensional cartesian vector where the component type is deduced from
        the first argument.
    */
    template <typename T>
    constexpr Vector4<T> vector(T x, std::type_identity_t<T> y, std::type_identity_t<T> z, std::type_identity_t<T> w)
    {
        return {x,y,z,w};
    }
    
    template <typename T, glm::qualifier Q>
    constexpr Vector4<T> vector(const glm::vec<4,T,Q>& v)
    {
        return { v.x, v.y, v.z, v.w };
    }

    template <typename T>
    consteval Vector4<T> Vector4<T>::unit_x()
    {
        return {one_v<T>,zero_v<T>,zero_v<T>,zero_v<T>};
    }

    template <typename T>
    consteval Vector4<T> Vector4<T>::unit_y()
    {
        return {zero_v<T>,one_v<T>,zero_v<T>,zero_v<T>};
    }

    template <typename T>
    consteval Vector4<T> Vector4<T>::unit_z()
    {
        return {zero_v<T>,zero_v<T>,one_v<T>,zero_v<T>};
    }

    template <typename T>
    consteval Vector4<T> Vector4<T>::unit_w()
    {
        return {zero_v<T>,zero_v<T>,zero_v<T>,one_v<T>};
    }

    constexpr Vector4D operator "" _x4(unsigned long long int v)
    {
        return {(double) v, 0., 0., 0.};
    }

    constexpr Vector4D operator "" _x4(long double v)
    {
        return {(double) v, 0., 0., 0.};
    }

    constexpr Vector4D operator "" _y4(unsigned long long int v)
    {
        return {0., (double) v, 0., 0.};
    }

    constexpr Vector4D operator "" _y4(long double v)
    {
        return {0., (double) v, 0., 0.};
    }

    constexpr Vector4D operator "" _z4(unsigned long long int v)
    {
        return {0., 0., (double) v, 0.};
    }

    constexpr Vector4D operator "" _z4(long double v)
    {
        return {0., 0., (double) v, 0.};
    }

    constexpr Vector4D operator "" _w4(unsigned long long int v)
    {
        return {0., 0., 0., (double) v};
    }

    constexpr Vector4D operator "" _w4(long double v)
    {
        return {0., 0., 0., (double) v};
    }

    YQ_NAN_1(Vector4, Vector4<T>{nan_v<T>, nan_v<T>, nan_v<T>, nan_v<T>})
    YQ_ZERO_1(Vector4, Vector4<T>{zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>})
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_NAN_1(Vector4, is_nan(v.x) || is_nan(v.y) || is_nan(v.z) || is_nan(v.w))
    YQ_IS_FINITE_1(Vector4, is_finite(v.x) && is_finite(v.y) && is_finite(v.z) && is_finite(v.w))

    /*! \brief Square of the vector's length
    
        This returns the SQUARE of the given vector's length.
    */
    template <typename T>
    constexpr square_t<T> length2(const Vector4<T>& a)
    {
        return a.x*a.x + a.y*a.y + a.z*a.z + a.w*a.w;
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
    constexpr Vector4<T> operator+(const Vector4<T>& a)
    {
        return a;
    }

//  --------------------------------------------------------
//  NEGATIVE

    template <typename T>
    constexpr Vector4<T> operator-(const Vector4<T>&a)
    {
        return {-a.x,-a.y,-a.z,-a.w};
    }

//  --------------------------------------------------------
//  NORMALIZATION

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
    constexpr Vector4<T> operator+(const Vector4<T>& a, const Vector4<T>& b)
    {
        return {a.x+b.x, a.y+b.y, a.z+b.z, a.w+b.w};
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
    constexpr Vector4<T> operator-(const Vector4<T>& a, const Vector4<T>& b)
    {
        return {a.x-b.x, a.y-b.y, a.z-b.z, a.w-b.w};
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
    constexpr Vector4<product_t<T,U>> operator*(T a, const Vector4<U>&b)
    {
        return {a*b.x, a*b.y, a*b.z, a*b.w};
    }
    
    template <typename T, typename U>
    requires (std::is_arithmetic_v<U>)
    constexpr Vector4<product_t<T,U>> operator*(const Vector4<T>& a, U b)
    {
        return {a.x*b, a.y*b, a.z*b, a.w*b};
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
    Vector4<product_t<T,U>>    mul_elem(const Vector4<T>&a, const Vector4<T>&b)
    {
        return {a.x*b.x, a.y*b.y, a.z*b.z, a.w*b.w};
    }
    
//  --------------------------------------------------------
//  DIVISION

    template <typename T, typename U>
    requires (std::is_arithmetic_v<T>)
    constexpr  Vector4<quotient_t<T,U>> operator/(T a, const  Vector4<U>&b)
    {
        return (a*b) / length2(b);
    }

    template <typename T, typename U>
    requires (std::is_arithmetic_v<U>)
    constexpr  Vector4<quotient_t<T,U>> operator/(const  Vector4<T>& a, U b)
    {
        return {a.x / b, a.y / b, a.z / b, a.w / b};
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
    Vector4<quotient_t<T,U>>    div_elem(const Vector4<T>&a, const Vector4<T>&b)
    {
        return {a.x/b.x, a.y/b.y, a.z/b.z, a.w/b.w};
    }

//  --------------------------------------------------------
//  POWERS

    template <typename T>
    constexpr square_t<T> operator^(const Vector4<T>& a,two_t)
    {
        return a.x*a.x + a.y*a.y + a.z*a.z + a.w*a.w;
    }    

//  --------------------------------------------------------
//  DOT PRODUCT

    template <typename T, typename U>
    constexpr product_t<T,U> operator DOT (const Vector4<T>& a, const Vector4<U>&b)
    {
        return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
    }

//  --------------------------------------------------------
//  INNER PRODUCT

    template <typename T, typename U>
    constexpr product_t<T,U> operator INNER (const Vector4<T>& a, const Vector4<U>&b)
    {
        return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
    }

//  --------------------------------------------------------
//  OUTER PRODUCT


//  --------------------------------------------------------
//  CROSS PRODUCT


///  --------------------------------------------------------
//  OTIMES PRODUCT

//  --------------------------------------------------------
//  PROJECTIONS

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

    template <typename T>
    Vector4<T>   abs_elem(const Vector4<T>&a)
    {
        return { abs(a.x), abs(a.y), abs(a.z), abs(a.w) };
    }

    //! TRUE if every component of a is greater than b
    template <typename T>
    constexpr bool        all_greater(const Vector4<T>& a, const Vector4<T>&b)
    {
        return (a.x>b.x) && (a.y>b.y) && (a.z>b.z) && (a.w>b.w);
    }

    //! TRUE if every component of a is greater or equal to b
    template <typename T>
    constexpr bool        all_greater_equal(const Vector4<T>& a, const Vector4<T>&b)
    {
        return (a.x>=b.x) && (a.y>=b.y) && (a.z>=b.z) && (a.w>=b.w);
    }
    
    //! TRUE if every component of a is less than b
    template <typename T>
    constexpr bool        all_less(const Vector4<T>& a, const Vector4<T>&b)
    {
        return (a.x<b.x) && (a.y<b.y) && (a.z<b.z) && (a.w<b.w);
    }

    //! TRUE if every component of a is less than (or equal to) b
    template <typename T>
    constexpr bool        all_less_equal(const Vector4<T>& a, const Vector4<T>&b)
    {
        return (a.x<=b.x) && (a.y<=b.y) && (a.z<=b.z) && (a.w<=b.w);
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

    template <typename T>
    fourth_t<T>     component_product(const Vector4<T>& a)
    {
        return a.x*a.y*a.z*a.w;
    }
    

    template <typename T>
    T   component_sum(const Vector4<T>& a)
    {
        return a.x + a.y + a.z + a.w;
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
    constexpr Vector4<T>   max_elem(const Vector4<T>&a, const Vector4<T>&b)
    {
        return {max(a.x, b.x) && max(a.y, b.y) && max(a.z, b.z) && max(a.w, b.w)};
    }
    
    template <typename T>
    constexpr Vector4<T>   min_elem(const Vector4<T>&a, const Vector4<T>&b)
    {
        return {min(a.x, b.x) && min(a.y, b.y) && min(a.z, b.z) && min(a.w, b.w)};
    }

}

YQ_TYPE_DECLARE(yq::Vector4D)
YQ_TYPE_DECLARE(yq::Vector4F)
YQ_TYPE_DECLARE(yq::Vector4I)
YQ_TYPE_DECLARE(yq::Vector4U)

