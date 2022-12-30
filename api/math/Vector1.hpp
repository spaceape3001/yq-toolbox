////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__VECTOR_1__HPP 1
#include <math/preamble.hpp>
#include <math/Absolute.hpp>

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

        //! Implicit conversion to GLM vector
        constexpr operator glm::vec<1, T, glm::defaultp>() const noexcept
        {
            return { x  };
        }

        //! Affirmation operator
        constexpr Vector1 operator+() const noexcept
        {
            return *this;
        }

        //! Negation operator
        constexpr Vector1 operator-() const noexcept
        {
            return {-x};
        }

        //! Normalizes the vector
        template <typename=void>
        requires trait::has_copysign_v<T>
        constexpr Vector1<T> operator~() const noexcept
        {
            return Vector1<T>(copysign(one_v<T>, x));
        }

        //! TRUE if every component of this vector is greater to b
        constexpr bool  agreat(const Vector1&b) const noexcept
        {
            return (x>b.x);
        }

        //! TRUE if every component of this vector is greater or equal to b
        constexpr bool  agequal(const Vector1&b) const noexcept
        {
            return (x>=b.x);
        }

        //! TRUE if every component of this vector is less than b
        constexpr bool  aless(const Vector1&b) const noexcept
        {
            return (x<b.x);
        }

        //! TRUE if every component of a this vector is less than (or equal to) b
        constexpr bool  alequal(const Vector1&b) const noexcept
        {
            return (x<=b.x);
        }
        
                //! TRUE if the second vector is CLOSE to this vector, as defined by the comparison operator
        template <typename R=Absolute>
        bool close(const Vector1&b, R compare) const 
        {
            return compare((*this-b).length(), b.length());
        }

        //! Component-wise max value
        constexpr T cmax() const noexcept
        {
            return x;
        }
        
        //! Component-wise min value
        constexpr T cmin() const noexcept
        {
            return x;
        }

        //! Component-wise product
        constexpr T cproduct() const noexcept
        {
            return x;
        }

        //! Component-wise sum
        constexpr T csum() const noexcept
        {
            return x;
        }
        
            //   the e's are here for consistency... not like they're really needed on 1D vectors

        //! Element by element absolute value
        constexpr Vector1   eabs() const noexcept
        {
            return { abs(x) };
        }

        //! Element by element division
        template <typename U>
        constexpr Vector1<quotient_t<T,U>>    ediv(const Vector1&b) const noexcept
        {
            return {x/b.x};
        }

        //! Element by element maximum
        constexpr Vector1   emax(const Vector1&b) const noexcept
        {
            return {max(x, b.x)};
        }

        //! Element by element minimum
        constexpr Vector1   emax(T b) const noexcept
        {
            return {max(x, b)};
        }

        //! Element by element minimum
        constexpr Vector1   emin(const Vector1&b) const noexcept
        {
            return {min(x, b.x)};
        }

        //! Element by element minimum
        constexpr Vector1   emin(T b) const noexcept
        {
            return {min(x, b)};
        }

        //! Element by element multiplication
        template <typename U>
        constexpr Vector1<product_t<T,U>>    emul(const Vector1<U>&b) const noexcept
        {
            return {x*b.x};
        }

        /*! \brief Square of the vector's length
        
            This returns the SQUARE of the given vector's length.
        */
        constexpr square_t<T> length²() const noexcept
        {
            return x*x;
        }    

        /*! \brief Length of the vector
            
            This returns the length of the given vector.
        */
        constexpr T    length() const noexcept
        {
            if constexpr (trait::has_abs_v<T>)
                return abs(x);
            if(x < T{})
                return -x;
            return x;
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
    constexpr square_t<T> length²(const Vector1<T>& vec) noexcept
    {
        return vec.length²();
    }    
    

    /*! \brief Length of the vector
        
        This returns the length of the given vector.
    */
    template <typename T>
    constexpr T  length(const Vector1<T>& vec) noexcept
    {
        return vec.length();
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
        return a.eabs();
    }

    //! TRUE if every component of a is greater than b
    template <typename T>
    constexpr bool        all_greater(const Vector1<T>& a, const Vector1<T>&b) noexcept
    {
        return a.agreat(b);
    }

    //! TRUE if every component of a is greater or equal to b
    template <typename T>
    constexpr bool        all_greater_equal(const Vector1<T>& a, const Vector1<T>&b) noexcept
    {
        return a.agequal(b);
    }

    //! TRUE if every component of a is less than b
    template <typename T>
    constexpr bool        all_less(const Vector1<T>& a, const Vector1<T>&b) noexcept
    {
        return a.aless(b);
    }

    //! TRUE if every component of a is less than (or equal to) b
    template <typename T>
    constexpr bool        all_less_equal(const Vector1<T>& a, const Vector1<T>&b) noexcept
    {
        return a.alequal(b);
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
        return a.emax(b);
    }

    template <typename T>
    constexpr Vector1<T>   min_elem(const Vector1<T>&a, const Vector1<T>&b) noexcept
    {
        return a.emin(b);
    }
}

YQ_TYPE_DECLARE(yq::Vector1D)
YQ_TYPE_DECLARE(yq::Vector1F)
YQ_TYPE_DECLARE(yq::Vector1I)
YQ_TYPE_DECLARE(yq::Vector1U)

