////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__VECTOR_1__HPP 1
#include <math/preamble.hpp>

namespace yq {
    /*! \brief Vector of 1 dimension
    
        This is a 1 dimensional cartesian vector of the given type.
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Vector1 {
        //! Component data type argument to this structure (ie, template parameter T)
        using component_type = T;

        /*! \brief Creates a unit-vector in the x-dimension.
        */
        static consteval Vector1 unit_x() noexcept;

        T       x;;
        
        //! Equality operator (using default)
        constexpr bool operator==(const Vector1&) const noexcept = default;

        constexpr Vector1 operator+() const noexcept
        {
            return *this;
        }

        constexpr Vector1 operator-() const noexcept
        {
            return {-x};
        }

        constexpr operator glm::vec<1, T, glm::defaultp>() const noexcept
        {
            return { x  };
        }

        /*! \brief Square of the vector's length
        
            This returns the SQUARE of the given vector's length.
        */
        constexpr square_t<T> length2() const noexcept
        {
            return x*x;
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
    constexpr Vector1<T> vector(T x) noexcept
    {
        return {x};
    }
    
    template <typename T, glm::qualifier Q>
    constexpr Vector1<T> vector(const glm::vec<1,T,Q>& v) noexcept
    {
        return { v.x };
    }
    
    template <typename T>
    consteval Vector1<T> Vector1<T>::unit_x() noexcept
    {
        return {one_v<T>};
    }

    constexpr Vector1D operator "" _x1(unsigned long long int v) noexcept
    {
        return {(double) v};
    }

    constexpr Vector1D operator "" _x1(long double v) noexcept
    {
        return {(double) v};
    }

    YQ_NAN_1(Vector1, Vector1<T>{nan_v<T>})
    YQ_ONE_1(Vector1, Vector1<T>{one_v<T>})
    YQ_ZERO_1(Vector1, Vector1<T>{zero_v<T>})
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_NAN_1(Vector1, is_nan(v.x))
    YQ_IS_FINITE_1(Vector1, is_finite(v.x))
        
    /*! \brief Square of the vector's length
    
        This returns the SQUARE of the given vector's length.
    */
    template <typename T>
    constexpr square_t<T> length2(const Vector1<T>& vec) noexcept
    {
        return vec.length2();
    }    
    

    /*! \brief Length of the vector
        
        This returns the length of the given vector.
    */
    template <typename T>
    requires trait::has_abs_v<T>
    constexpr auto    length(const Vector1<T>& a) noexcept
    {
        return abs(a.x);
    }

//  --------------------------------------------------------
//  POSITIVE



//  --------------------------------------------------------
//  NORMALIZATION

    template <typename T>
    requires trait::has_copysign_v<T>
    constexpr Vector1<T> operator~(const Vector1<T>& a) noexcept
    {
        return Vector1<T>(copysign(one_v<T>, a.x));
    }

//  --------------------------------------------------------
//  ADDITION

    template <typename T>
    constexpr Vector1<T> operator+(const Vector1<T>& a, const Vector1<T>& b) noexcept
    {
        return {a.x+b.x};
    }

    template <typename T>
    Vector1<T>& operator+=(Vector1<T>& a, const Vector1<T>& b) noexcept
    {
        a.x += b.x;
        return a;
    }

//  --------------------------------------------------------
//  SUBTRACTION

    template <typename T>
    constexpr Vector1<T> operator-(const Vector1<T>& a, const Vector1<T>& b) noexcept
    {
        return {a.x-b.x};
    }

    template <typename T>
    Vector1<T>& operator-=(Vector1<T>& a, const Vector1<T>& b) noexcept
    {
        a.x -= b.x;
        return a;
    }

//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires (std::is_arithmetic_v<T>)
    constexpr Vector1<product_t<T,U>> operator*(T a, const Vector1<U>&b) noexcept
    {
        return {a*b.x};
    }

    template <typename T, typename U>
    requires (std::is_arithmetic_v<U>)
    constexpr Vector1<product_t<T,U>> operator*(const Vector1<T>& a, U b) noexcept
    {
        return {a.x*b};
    }

    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Vector1<T>& operator*=(Vector1<T>& a, T b) noexcept
    {
        a.x *= b;
        return a;
    }

    template <typename T, typename U>
    constexpr product_t<T,U> operator*(const Vector1<T>&a, const Vector1<U>& b) noexcept
    {
        return a.x*b.x;
    }

    template <typename T, typename U>
    constexpr Vector1<product_t<T,U>>    mul_elem(const Vector1<T>&a, const Vector1<T>&b) noexcept
    {
        return {a.x*b.x};
    }

//  --------------------------------------------------------
//  DIVISION

    template <typename T, typename U>
    requires (std::is_arithmetic_v<T>)
    constexpr  Vector1<quotient_t<T,U>> operator/(T a, const  Vector1<U>&b) noexcept
    {
        return (a*b) / length2(b);
    }

    template <typename T, typename U>
    requires (std::is_arithmetic_v<U>)
    constexpr  Vector1<quotient_t<T,U>> operator/(const  Vector1<T>& a, U b) noexcept
    {
        return {a.x / b};
    }

    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Vector1<T>& operator/=(Vector1<T>& a, U b) noexcept
    {
        a.x /= b;
        return a;
    }

    template <typename T, typename U>
    constexpr quotient_t<T,U> operator/(const Vector1<T>&a, const Vector1<U>& b) noexcept
    {
        return (a*b)/length2(b);
    }

    template <typename T, typename U>
    constexpr Vector1<quotient_t<T,U>>    div_elem(const Vector1<T>&a, const Vector1<T>&b) noexcept
    {
        return {a.x/b.x};
    }

//  --------------------------------------------------------
//  POWERS

    /*! \brief Square of the vector's length
    
        This returns the SQUARE of the given vector's length.
    */
    template <typename T>
    constexpr square_t<T> operator^(const Vector1<T>& a,two_t) noexcept
    {
        return a.x*a.x;
    }    

//  --------------------------------------------------------
//  DOT PRODUCT

    template <typename T, typename U>
    constexpr product_t<T,U> operator DOT (const Vector1<T>& a, const Vector1<U>&b) noexcept
    {
        return a.x*b.x;
    }


//  --------------------------------------------------------
//  INNER PRODUCT


    template <typename T, typename U>
    constexpr product_t<T,U> operator INNER (const Vector1<T>& a, const Vector1<U>&b) noexcept
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
    constexpr Vector1<T>   abs_elem(const Vector1<T>&a) noexcept
    {
        return {abs(a.x)};
    }

    //! TRUE if every component of a is greater than b
    template <typename T>
    constexpr bool        all_greater(const Vector1<T>& a, const Vector1<T>&b) noexcept
    {
        return (a.x>b.x);
    }

    //! TRUE if every component of a is greater or equal to b
    template <typename T>
    constexpr bool        all_greater_equal(const Vector1<T>& a, const Vector1<T>&b) noexcept
    {
        return (a.x>=b.x);
    }

    //! TRUE if every component of a is less than b
    template <typename T>
    constexpr bool        all_less(const Vector1<T>& a, const Vector1<T>&b) noexcept
    {
        return (a.x<b.x);
    }

    //! TRUE if every component of a is less than (or equal to) b
    template <typename T>
    constexpr bool        all_less_equal(const Vector1<T>& a, const Vector1<T>&b) noexcept
    {
        return (a.x<=b.x);
    }
  
    template <typename T>
    constexpr T             component_max(const Vector1<T>&a) noexcept
    {
        return a.x;
    }

    template <typename T>
    constexpr T             component_min(const Vector1<T>&a) noexcept
    {
        return a.x;
    }

    template <typename T>
    constexpr T                   component_product(const Vector1<T>& a) noexcept
    {
        return a.x;
    }

    template <typename T>
    constexpr T                   component_sum(const Vector1<T>& a) noexcept
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
    constexpr Vector1<T>   max_elem(const Vector1<T>&a, const Vector1<T>&b) noexcept
    {
        return {max(a.x, b.x)};
    }

    template <typename T>
    constexpr Vector1<T>   min_elem(const Vector1<T>&a, const Vector1<T>&b) noexcept
    {
        return {min(a.x, b.x)};
    }
}

YQ_TYPE_DECLARE(yq::Vector1D)
YQ_TYPE_DECLARE(yq::Vector1F)
YQ_TYPE_DECLARE(yq::Vector1I)
YQ_TYPE_DECLARE(yq::Vector1U)

