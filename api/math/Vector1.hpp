////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__VECTOR_1__HPP 1
#include <math/preamble.hpp>
#include <math/Absolute.hpp>
#include <math/AllComponents.hpp>
#include <math/AnyComponents.hpp>

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
        constexpr Vector1<T> operator~() const noexcept
        {
            if constexpr (trait::has_copysign_v<T>)
                return Vector1<T>(copysign(one_v<T>, x));
            return {};
        }

        constexpr Vector1 operator+(const Vector1& b) const noexcept
        {
            return {x+b.x};
        }

        Vector1& operator+=(const Vector1& b) noexcept
        {
            x += b.x;
            return *this;
        }

        constexpr Vector1 operator-(const Vector1& b) const noexcept
        {
            return {x-b.x};
        }

        Vector1& operator-=(const Vector1& b) noexcept
        {
            x -= b.x;
            return *this;
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


            //  ===================================================================================================
            //  AllComponents Adapters
            //  ===================================================================================================
        
        /*! Adds a value to all the elements
        */
        constexpr Vector1 all_add(T b) const noexcept
        {
            return { x + b };
        }
        
        /*! \brief Subtracts value from all elements
        */
        constexpr Vector1 all_subtract(T b) const noexcept
        {
            return { x - b };
        }

       /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if all tests are true.
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool all_test(Pred pred) const noexcept
        {
            return pred(x);
        }

        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if all tests are true.
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool all_test(const Vector1& b, Pred pred) const noexcept
        {
            return pred(x, b.x);
        }

        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if all tests are true.
            \param[in] b The other value
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool all_test(T b, Pred pred) const noexcept
        {
            return pred(x, b.x);
        }
        

            //  ===================================================================================================
            //  AnyComponents Adapters
            //  ===================================================================================================

        
        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if any test is true.
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool any_test(Pred pred) const noexcept
        {
            return pred(x);
        }
        
        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if any test is true.
            \param[in] b The other vector
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool any_test(const Vector1& b, Pred pred) const noexcept
        {
            return pred(x, b.x);
        }
        
        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if any test is true.
            \param[in] b The other value
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool any_test(T b, Pred pred) const noexcept
        {
            return pred(x, b.x);
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

    /*! \brief Mid-way divide two vectors
    */
    template <typename T>
    constexpr T     midvector(const Vector1<T>& a, const Vector1<T>& b=Vector1<T>{}) noexcept
    {
        if constexpr (has_ieee754_v<T>)
            return ieee754_t<T>(0.5)*(a+b);
        else if constexpr (std::is_integral_v<T>)
            return (a+b) / T(2);
        else
            return {};
    }

    template <typename T>
    AllComponents<Vector1<T>>   all(const Vector1<T>& val)
    {
        return { val };
    }
    
    template <typename T>
    AllComponents<Vector1<T>>   elem(const Vector1<T>& val)
    {
        return { val };
    }

    template <typename T>
    AnyComponents<Vector1<T>>   any(const Vector1<T>& val)
    {
        return { val };
    }
}

YQ_TYPE_DECLARE(yq::Vector1D)
YQ_TYPE_DECLARE(yq::Vector1F)
YQ_TYPE_DECLARE(yq::Vector1I)
YQ_TYPE_DECLARE(yq::Vector1U)

