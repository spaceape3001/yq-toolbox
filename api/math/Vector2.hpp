////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__VECTOR_2__HPP 1
#include <math/preamble.hpp>
#include <math/Units.hpp>
#include <math/trig.hpp>

namespace yq {
    /*! \brief Vector of 2 dimension(s)
    
        This is a 2 dimensional cartesian vector of the given type.
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Vector2 {
        //! Component data type argument to this structure (ie, template parameter T)
        using component_type = T;

        /*! \brief Creates a unit-vector in the $(bit)s dimension.
        */
        static consteval Vector2 unit_x();
        /*! \brief Creates a unit-vector in the $(bit)s dimension.
        */
        static consteval Vector2 unit_y();

        //! Component for the $(bit)s dimension.
        T       x;
        //! Component for the $(bit)s dimension.
        T       y;;
        
        //! Equality operator (using default)
        constexpr bool operator==(const Vector2&) const noexcept = default;

        constexpr operator glm::vec<2, T, glm::defaultp>() const noexcept
        {
            return { x, y  };
        }
    };

    YQ_IEEE754_1(Vector2)
    
//  --------------------------------------------------------
//  COMPOSITION


    /*! \brief Creates a 2 dimensioal vector
    
        Helper function to create a 2 dimensional cartesian vector where the component type is deduced from
        the first argument.
    */
    template <typename T>
    constexpr Vector2<T> vector(T x, std::type_identity_t<T> y)
    {
        return {x,y};
    }
    
    template <typename T, glm::qualifier Q>
    constexpr Vector2<T> vector(const glm::vec<2,T,Q>& v)
    {
        return { v.x, v.y };
    }


    template <typename T>
    consteval Vector2<T> Vector2<T>::unit_x()
    {
        return {one_v<T>,zero_v<T>};
    }

    template <typename T>
    consteval Vector2<T> Vector2<T>::unit_y()
    {
        return {zero_v<T>,one_v<T>};
    }

    constexpr Vector2D operator "" _x2(unsigned long long int v)
    {
        return {(double) v, 0.};
    }

    constexpr Vector2D operator "" _x2(long double v)
    {
        return {(double) v, 0.};
    }

    constexpr Vector2D operator "" _y2(unsigned long long int v)
    {
        return {0., (double) v};
    }

    constexpr Vector2D operator "" _y2(long double v)
    {
        return {0., (double) v};
    }

    //! Creates a two dimension unit vector
    //!
    //! \param az   Counter-clockwise angle from +x
    inline Vector2D     ccw(Radian az)
    {
        return { cos(az), sin(az) };
    }

    //! Creates a two dimension unit vector
    //!
    //! \param az    Clockwise angle from +y
    inline Vector2D     clockwise(Radian az)
    {
        return { sin(az), cos(az) };
    }

    YQ_NAN_1(Vector2, Vector2<T>{nan_v<T>, nan_v<T>})
    YQ_ZERO_1(Vector2, Vector2<T>{zero_v<T>, zero_v<T>})
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_NAN_1(Vector2, is_nan(v.x) || is_nan(v.y))
    YQ_IS_FINITE_1(Vector2, is_finite(v.x) && is_finite(v.y))
        

    /*! \brief Square of the vector's length
    
        This returns the SQUARE of the given vector's length.
    */
    template <typename T>
    constexpr square_t<T> length2(const Vector2<T>& a)
    {
        return a.x*a.x + a.y*a.y;
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

//  --------------------------------------------------------
//  POSITIVE

    template <typename T>
    constexpr Vector2<T> operator+(const Vector2<T>& a)
    {
        return a;
    }


//  --------------------------------------------------------
//  NEGATIVE

    template <typename T>
    constexpr Vector2<T> operator-(const Vector2<T>&a)
    {
        return {-a.x,-a.y};
    }


//  --------------------------------------------------------
//  NORMALIZATION


    template <typename T>
    requires trait::has_sqrt_v<T>
    Vector2<quotient_t<T,T>> operator~(const Vector2<T>& a)
    {
        auto l = one_v<T>/length(a);
        return {a.x/l, a.y/l};
    }
    
//  --------------------------------------------------------
//  ADDITION

    template <typename T>
    constexpr Vector2<T> operator+(const Vector2<T>& a, const Vector2<T>& b)
    {
        return {a.x+b.x, a.y+b.y};
    }
    
    template <typename T>
    Vector2<T>& operator+=(Vector2<T>& a, const Vector2<T>& b)
    {
        a.x += b.x;
        a.y += b.y;
        return a;
    }

//  --------------------------------------------------------
//  SUBTRACTION

    template <typename T>
    constexpr Vector2<T> operator-(const Vector2<T>& a, const Vector2<T>& b)
    {
        return {a.x-b.x, a.y-b.y};
    }

    template <typename T>
    Vector2<T>& operator-=(Vector2<T>& a, const Vector2<T>& b)
    {
        a.x -= b.x;
        a.y -= b.y;
        return a;
    }

//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires (std::is_arithmetic_v<T>)
    constexpr Vector2<product_t<T,U>> operator*(T a, const Vector2<U>&b)
    {
        return {a*b.x, a*b.y};
    }

    template <typename T, typename U>
    requires (std::is_arithmetic_v<U>)
    constexpr Vector2<product_t<T,U>> operator*(const Vector2<T>& a, U b)
    {
        return {a.x*b, a.y*b};
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
    Vector2<product_t<T,U>>    mul_elem(const Vector2<T>&a, const Vector2<T>&b)
    {
        return {a.x*b.x, a.y*b.y};
    }

//  --------------------------------------------------------
//  DIVISION

    template <typename T, typename U>
    requires (std::is_arithmetic_v<T>)
    constexpr  Vector2<quotient_t<T,U>> operator/(T a, const  Vector2<U>&b)
    {
        return (a*b) / length2(b);
    }


    template <typename T, typename U>
    requires (std::is_arithmetic_v<U>)
    constexpr  Vector2<quotient_t<T,U>> operator/(const  Vector2<T>& a, U b)
    {
        return {a.x / b, a.y / b};
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
    Vector2<quotient_t<T,U>>    div_elem(const Vector2<T>&a, const Vector2<T>&b)
    {
        return {a.x/b.x, a.y/b.y};
    }


//  --------------------------------------------------------
//  POWERS

    template <typename T>
    constexpr square_t<T> operator^(const Vector2<T>& a,two_t)
    {
        return a.x*a.x + a.y*a.y;
    }    

//  --------------------------------------------------------
//  DOT PRODUCT

    template <typename T, typename U>
    constexpr product_t<T,U> operator DOT (const Vector2<T>& a, const Vector2<U>&b)
    {
        return a.x*b.x + a.y*b.y;
    }


//  --------------------------------------------------------
//  INNER PRODUCT

    template <typename T, typename U>
    constexpr product_t<T,U> operator INNER (const Vector2<T>& a, const Vector2<U>&b)
    {
        return a.x*b.x + a.y*b.y;
    }

//  --------------------------------------------------------
//  OUTER PRODUCT


//  --------------------------------------------------------
//  CROSS PRODUCT

    template <typename T, typename U>
    constexpr product_t<T,U> operator CROSS (const Vector2<T>& a, const Vector2<U>&b)
    {
        return a.x*b.y-a.y*b.x;
    }



///  --------------------------------------------------------
//  OTIMES PRODUCT

//  --------------------------------------------------------
//  PROJECTIONS

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

    template <typename T>
    Vector2<T>   abs_elem(const Vector2<T>&a)
    {
        return { abs(a.x), abs(a.y) };
    }

    //! TRUE if every component of a is greater than b
    template <typename T>
    constexpr bool        all_greater(const Vector2<T>& a, const Vector2<T>&b)
    {
        return (a.x>b.x) && (a.y>b.y);
    }

    //! TRUE if every component of a is greater or equal to b
    template <typename T>
    constexpr bool        all_greater_equal(const Vector2<T>& a, const Vector2<T>&b)
    {
        return (a.x>=b.x) && (a.y>=b.y);
    }

    //! TRUE if every component of a is less than b
    template <typename T>
    constexpr bool        all_less(const Vector2<T>& a, const Vector2<T>&b)
    {
        return (a.x<b.x) && (a.y<b.y);
    }

    //! TRUE if every component of a is less than (or equal to) b
    template <typename T>
    constexpr bool        all_less_equal(const Vector2<T>& a, const Vector2<T>&b)
    {
        return (a.x<=b.x) && (a.y<=b.y);
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

    template <typename T>
    square_t<T>     component_product(const Vector2<T>& a)
    {
        return a.x*a.y;
    }

    template <typename T>
    T   component_sum(const Vector2<T>& a)
    {
        return a.x + a.y;
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

    template <typename T>
    constexpr Vector2<T>   max_elem(const Vector2<T>&a, const Vector2<T>&b)
    {
        return {max(a.x, b.x) && max(a.y, b.y)};
    }


    template <typename T>
    constexpr Vector2<T>   min_elem(const Vector2<T>&a, const Vector2<T>&b)
    {
        return {min(a.x, b.x) && min(a.y, b.y)};
    }


}

YQ_TYPE_DECLARE(yq::Vector2D)
YQ_TYPE_DECLARE(yq::Vector2F)
YQ_TYPE_DECLARE(yq::Vector2I)
YQ_TYPE_DECLARE(yq::Vector2U)

