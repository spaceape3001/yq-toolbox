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


        T       x;
        
        constexpr Vector1() noexcept = default;
        constexpr Vector1(T _x) noexcept : x(_x) {}
        constexpr Vector1(all_t, T v) noexcept : x(v) {}
        consteval Vector1(nan_t) noexcept : Vector1(ALL, nan_v<T>) {}
        consteval Vector1(one_t) noexcept : Vector1(ALL, one_v<T>) {}
        constexpr Vector1(x_t, T v) noexcept : x(v) {}
        consteval Vector1(x_t) noexcept : x(one_v<T>) {}
        consteval Vector1(zero_t) noexcept : Vector1(ALL, zero_v<T>) {}

        template <glm::qualifier Q>
        explicit constexpr Vector1(const glm::vec<1, T, Q>& v) : x(v.x) {}

        /*! \brief Creates a unit-vector in the x-dimension.
        */
        static consteval Vector1 unit_x() noexcept
        {
            return Vector1(x_t());
        }
        
        //constexpr Vector1(const glm::vec<1, T, glm::defaultp>& v) noexcept : x(v.x) {}
        
        //! Equality operator (using default)
        constexpr bool operator==(const Vector1&) const noexcept = default;

        //! Implicit conversion to GLM vector
        constexpr operator glm::vec<1, T, glm::defaultp>() const noexcept;
        
        //! Explicit conversion operator
        template <typename U>
        requires (std::is_convertible_v<T,U> && !std::is_same_v<T,U>)
        explicit operator Vector1<U>() const
        {
            return Vector1<U>( U(x));
        }
        

        //! Affirmation operator
        constexpr Vector1 operator+() const noexcept
        {
            return *this;
        }

        //! Negation operator
        constexpr Vector1 operator-() const noexcept;

        //! Normalizes the vector
        constexpr Vector1<T> operator~() const noexcept;

        //! Squares the vector
        constexpr square_t<T> operator^(two_t) const noexcept;

        //! Addition with scalar
        constexpr Multivector1<T> operator+(T b) const noexcept;

        //! Addition with multivector
        constexpr Multivector1<T> operator+(const Multivector1<T>& b) const noexcept;
        
        //! Addition
        constexpr Vector1 operator+(const Vector1& b) const noexcept;

        //! Self-addition
        Vector1& operator+=(const Vector1& b) noexcept;

        //! Subtraction with scalar
        constexpr Multivector1<T> operator-(T b) const noexcept;
        
        //! Subtraction with multivector
        constexpr Multivector1<T> operator-(const Multivector1<T>& b) const noexcept;
        
        //! Subtraction
        constexpr Vector1 operator-(const Vector1& b) const noexcept;

        //! Self-subtraction
        Vector1& operator-=(const Vector1& b) noexcept;
        
        //! Multiplication with scalar
        template <typename U>
        requires (trait::is_arithmetic_v<U>)
        constexpr Vector1<product_t<T,U>> operator*(U b) const noexcept;
        
        //! Self-multiplication with scalar
        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
        Vector1<T>& operator*=(U b) noexcept;

        //! Vector/tensor multiplication
        template <typename U>
        constexpr Vector1<product_t<T,U>> operator*(const Tensor11<U>&) const noexcept;

        //! Vector/tensor multiplication
        template <typename U>
        constexpr Vector2<product_t<T,U>> operator*(const Tensor12<U>&) const noexcept;

        //! Vector/tensor multiplication
        template <typename U>
        constexpr Vector3<product_t<T,U>> operator*(const Tensor13<U>&) const noexcept;

        //! Vector/tensor multiplication
        template <typename U>
        constexpr Vector4<product_t<T,U>> operator*(const Tensor14<U>&) const noexcept;
        
        //! Vector/tensor self-multiplication
        template <typename U>
        requires trait::self_mul_v<T,U>
        Vector1&  operator*=(const Tensor11<U>&) noexcept;

        //! Geometric product (scalar in 1D)
        template <typename U>
        constexpr product_t<T,U> operator*(const Vector1<U>& b) const noexcept;

        //! Dot product
        template <typename U>
        constexpr product_t<T,U> operator DOT (const Vector1<U>&b) const noexcept;
        
        //! Inner product
        template <typename U>
        constexpr product_t<T,U> operator INNER (const Vector1<U>&b) const noexcept;

        //! OTIMES Vector1
        template <typename U>
        constexpr Tensor11<product_t<T,U>> operator OTIMES(const Vector1<U>&b) const noexcept;
        //! OTIMES Vector2
        template <typename U>
        constexpr Tensor12<product_t<T,U>> operator OTIMES(const Vector2<U>&b) const noexcept;
        //! OTIMES Vector3
        template <typename U>
        constexpr Tensor13<product_t<T,U>> operator OTIMES(const Vector3<U>&b) const noexcept;
        //! OTIMES Vector4
        template <typename U>
        constexpr Tensor14<product_t<T,U>> operator OTIMES(const Vector4<U>&b) const noexcept;

        //! Scalar division
        template <typename U>
        requires (trait::is_arithmetic_v<U>)
        constexpr  Vector1<quotient_t<T,U>> operator/(U b) const noexcept;

        //! Self-division with scalar
        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_div_v<T,U>)
        Vector1<T>& operator/=(U b) noexcept;

        //! Division with vector
        template <typename U>
        constexpr quotient_t<T,U> operator/(const Vector1<U>& b) const noexcept;

        //! TRUE if the second vector is CLOSE to this vector, as defined by the comparison operator
        template <typename R=Absolute>
        bool close(const Vector1&b, R compare) const 
        {
            return compare((*this-b).length(), b.length());
        }

        //! Component-wise max value
        constexpr T cmax() const noexcept;
        
        //! Component-wise min value
        constexpr T cmin() const noexcept;

        //! Component-wise product
        constexpr T cproduct() const noexcept;

        //! Component-wise sum
        constexpr T csum() const noexcept;
        
            //   the e's are here for consistency... not like they're really needed on 1D vectors

        //! Element by element absolute value
        constexpr Vector1   eabs() const noexcept;

        //! Element by element division
        template <typename U>
        constexpr Vector1<quotient_t<T,U>>    ediv(const Vector1<U>&b) const noexcept;

        //! Element by element maximum
        constexpr Vector1   emax(const Vector1&b) const noexcept;

        //! Element by element minimum
        constexpr Vector1   emax(T b) const noexcept;

        //! Element by element minimum
        constexpr Vector1   emin(const Vector1&b) const noexcept;

        //! Element by element minimum
        constexpr Vector1   emin(T b) const noexcept;

        //! Element by element multiplication
        template <typename U>
        constexpr Vector1<product_t<T,U>>    emul(const Vector1<U>&b) const noexcept;

        /*! \brief Square of the vector's length
        
            This returns the SQUARE of the given vector's length.
        */
        constexpr square_t<T> length²() const noexcept;

        /*! \brief Length of the vector
            
            This returns the length of the given vector.
        */
        constexpr T    length() const noexcept;


            //  ===================================================================================================
            //  AllComponents Adapters
            //  ===================================================================================================
        
        /*! Adds a value to all the elements
        */
        constexpr Vector1 all_add(T b) const noexcept;
        
        /*! \brief Subtracts value from all elements
        */
        constexpr Vector1 all_subtract(T b) const noexcept;

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
        return Vector1<T>(x);
    }
    
    template <typename T, glm::qualifier Q>
    constexpr Vector1<T> vector(const glm::vec<1,T,Q>& v) noexcept
    {
        return Vector1( v.x);
    }

    constexpr Vector1D operator "" _x1(unsigned long long int v) noexcept
    {
        return Vector1D(x_, (double) v);
    }

    constexpr Vector1D operator "" _x1(long double v) noexcept
    {
        return Vector1D(x_, (double) v);
    }

    YQ_NAN_1(Vector1, Vector1<T>(NAN))
    YQ_ONE_1(Vector1, Vector1<T>(ONE))
    YQ_ZERO_1(Vector1, Vector1<T>(ZERO))
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_NAN_1(Vector1, is_nan(v.x))
    YQ_IS_FINITE_1(Vector1, is_finite(v.x))
        
    /*! \brief Square of the vector's length
    
        This returns the SQUARE of the given vector's length.
    */
    template <typename T>
    constexpr square_t<T> length²(const Vector1<T>& vec) noexcept;
    

    /*! \brief Length of the vector
        
        This returns the length of the given vector.
    */
    template <typename T>
    constexpr T  length(const Vector1<T>& vec) noexcept;


//  --------------------------------------------------------
//  ADDITION

    template <typename T>
    constexpr Multivector1<T> operator+(T a, const Vector1<T>& b) noexcept;

//  --------------------------------------------------------
//  SUBTRACTION

    template <typename T>
    constexpr Multivector1<T> operator-(T a, const Vector1<T>& b) noexcept;

//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires (trait::is_arithmetic_v<T>)
    constexpr Vector1<product_t<T,U>> operator*(T a, const Vector1<U>&b) noexcept;



    template <typename T, typename U>
    constexpr Vector1<product_t<T,U>>    mul_elem(const Vector1<T>&a, const Vector1<U>&b) noexcept;

//  --------------------------------------------------------
//  DIVISION

    template <typename T, typename U>
    requires (trait::is_arithmetic_v<T>)
    constexpr  Vector1<quotient_t<T,U>> operator/(T a, const  Vector1<U>&b) noexcept;


    template <typename T, typename U>
    constexpr Vector1<quotient_t<T,U>>    div_elem(const Vector1<T>&a, const Vector1<U>&b) noexcept;

//  --------------------------------------------------------
//  POWERS


//  --------------------------------------------------------
//  DOT PRODUCT

//  --------------------------------------------------------
//  INNER PRODUCT

//  --------------------------------------------------------
//  OUTER PRODUCT

///  --------------------------------------------------------
//  OTIMES PRODUCT

//  --------------------------------------------------------
//  PROJECTIONS

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

    template <typename T>
    constexpr Vector1<T>   abs_elem(const Vector1<T>&a) noexcept;

    template <typename T>
    constexpr T             component_max(const Vector1<T>&a) noexcept;

    template <typename T>
    constexpr T             component_min(const Vector1<T>&a) noexcept;

    template <typename T>
    constexpr T                   component_product(const Vector1<T>& a) noexcept;

    template <typename T>
    constexpr T                   component_sum(const Vector1<T>& a) noexcept;

    template <typename T, typename R>
    bool is_close(const R& compare, const Vector1<T>& actual, const Vector1<T>& expected)
    {
        return compare(length(actual-expected), length(expected));
    }

    template <typename T, typename R>
    bool is_close(const R& compare, const Vector1<T>& actual, std::type_identity_t<T> x)
    {
        return is_close(compare, actual, Vector1<T>(x) );
    }
    
    template <typename T>
    constexpr Vector1<T>   max_elem(const Vector1<T>&a, const Vector1<T>&b) noexcept;

    template <typename T>
    constexpr Vector1<T>   min_elem(const Vector1<T>&a, const Vector1<T>&b) noexcept;

    /*! \brief Mid-way divide two vectors
    */
    template <typename T>
    constexpr Vector1<T>        midvector(const Vector1<T>& a, const Vector1<T>& b=Vector1<T>{}) noexcept;

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

