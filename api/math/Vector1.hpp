////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__VECTOR_1__HPP 1
#include <math/preamble.hpp>

namespace yq {
    /*! \brief Vector of 1 dimension(s)
    
        This is a 1 dimensional cartesian vector of the given type.
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Vector1 {
        //! Component data type argument to this structure (ie, template parameter T)
        using component_type = T;

        /*! \brief Creates a unit-vector in the $(bit)s dimension.
        */
        static consteval Vector1 unit_x();

        //! Component for the $(bit)s dimension.
        T       x;;
        
        //! Equality operator (using default)
        constexpr bool operator==(const Vector1&) const noexcept = default;

        constexpr operator glm::vec<1, T, glm::defaultp>() const noexcept
        {
            return { x  };
        }
    };

    YQ_IEEE754_1(Vector1)


//  --------------------------------------------------------
//  COMPOSITION

    
    /*! \brief Creates a 1 dimensioal vector
    
        Helper function to create a 1 dimensional cartesian vector where the component type is deduced from
        the first argument.
    */
    template <typename T>
    constexpr Vector1<T> vector(T x)
    {
        return {x};
    }
    
    template <typename T, glm::qualifier Q>
    constexpr Vector1<T> vector(const glm::vec<1,T,Q>& v)
    {
        return { v.x };
    }
    
    template <typename T>
    consteval Vector1<T> Vector1<T>::unit_x()
    {
        return {one_v<T>};
    }

    constexpr Vector1D operator "" _x1(unsigned long long int v)
    {
        return {(double) v};
    }

    constexpr Vector1D operator "" _x1(long double v)
    {
        return {(double) v};
    }

    YQ_NAN_1(Vector1, Vector1<T>{nan_v<T>})
    YQ_ZERO_1(Vector1, Vector1<T>{zero_v<T>})
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_NAN_1(Vector1, is_nan(v.x))
    YQ_IS_FINITE_1(Vector1, is_finite(v.x))
        
    /*! \brief Square of the vector's length
    
        This returns the SQUARE of the given vector's length.
    */
    template <typename T>
    constexpr square_t<T> length2(const Vector1<T>& a)
    {
        return a.x*a.x;
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

//  --------------------------------------------------------
//  POSITIVE

    template <typename T>
    constexpr Vector1<T> operator+(const Vector1<T>& a)
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


//  --------------------------------------------------------
//  NORMALIZATION

    template <typename T>
    requires trait::has_copysign_v<T>
    Vector1<T> operator~(const Vector1<T>& a)
    {
        return Vector1<T>(copysign(one_v<T>, a.x));
    }

//  --------------------------------------------------------
//  ADDITION

    template <typename T>
    constexpr Vector1<T> operator+(const Vector1<T>& a, const Vector1<T>& b)
    {
        return {a.x+b.x};
    }

    template <typename T>
    Vector1<T>& operator+=(Vector1<T>& a, const Vector1<T>& b)
    {
        a.x += b.x;
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
    Vector1<T>& operator-=(Vector1<T>& a, const Vector1<T>& b)
    {
        a.x -= b.x;
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
    requires (std::is_arithmetic_v<U>)
    constexpr Vector1<product_t<T,U>> operator*(const Vector1<T>& a, U b)
    {
        return {a.x*b};
    }

    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Vector1<T>& operator*=(Vector1<T>& a, T b)
    {
        a.x *= b;
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

//  --------------------------------------------------------
//  DIVISION

    template <typename T, typename U>
    requires (std::is_arithmetic_v<T>)
    constexpr  Vector1<quotient_t<T,U>> operator/(T a, const  Vector1<U>&b)
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
    requires (std::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Vector1<T>& operator/=(Vector1<T>& a, U b)
    {
        a.x /= b;
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

//  --------------------------------------------------------
//  POWERS

    /*! \brief Square of the vector's length
    
        This returns the SQUARE of the given vector's length.
    */
    template <typename T>
    constexpr square_t<T> operator^(const Vector1<T>& a,two_t)
    {
        return a.x*a.x;
    }    

//  --------------------------------------------------------
//  DOT PRODUCT

    template <typename T, typename U>
    constexpr product_t<T,U> operator DOT (const Vector1<T>& a, const Vector1<U>&b)
    {
        return a.x*b.x;
    }


//  --------------------------------------------------------
//  INNER PRODUCT


    template <typename T, typename U>
    constexpr product_t<T,U> operator INNER (const Vector1<T>& a, const Vector1<U>&b)
    {
        return a.x*b.x;
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

    //! TRUE if every component of a is greater than b
    template <typename T>
    constexpr bool        all_greater(const Vector1<T>& a, const Vector1<T>&b)
    {
        return (a.x>b.x);
    }

    //! TRUE if every component of a is greater or equal to b
    template <typename T>
    constexpr bool        all_greater_equal(const Vector1<T>& a, const Vector1<T>&b)
    {
        return (a.x>=b.x);
    }

    //! TRUE if every component of a is less than b
    template <typename T>
    constexpr bool        all_less(const Vector1<T>& a, const Vector1<T>&b)
    {
        return (a.x<b.x);
    }

    //! TRUE if every component of a is less than (or equal to) b
    template <typename T>
    constexpr bool        all_less_equal(const Vector1<T>& a, const Vector1<T>&b)
    {
        return (a.x<=b.x);
    }
  
    template <typename T>
    T                   component_product(const Vector1<T>& a)
    {
        return a.x;
    }

    template <typename T>
    T                   component_sum(const Vector1<T>& a)
    {
        return a.x;
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

    template <typename T>
    constexpr Vector1<T>   max_elem(const Vector1<T>&a, const Vector1<T>&b)
    {
        return {max(a.x, b.x)};
    }

    template <typename T>
    constexpr Vector1<T>   min_elem(const Vector1<T>&a, const Vector1<T>&b)
    {
        return {min(a.x, b.x)};
    }
}

YQ_TYPE_DECLARE(yq::Vector1D)
YQ_TYPE_DECLARE(yq::Vector1F)
YQ_TYPE_DECLARE(yq::Vector1I)
YQ_TYPE_DECLARE(yq::Vector1U)

