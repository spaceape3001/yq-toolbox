////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_VECTOR_1_HPP 1

#include <yq/typedef/vector1.hpp>

#include <yq/keywords.hpp>
#include <yq/macro/operators.hpp>
#include <yq/math/glm.hpp>
#include <yq/meta/MetaBinder.hpp>
#include <yq/trait/has_nan.hpp>
#include <yq/trait/has_is_finite.hpp>
#include <yq/trait/has_one.hpp>
#include <yq/trait/has_zero.hpp>
#include <yq/trait/ieee754.hpp>
#include <yq/trait/integer.hpp>
#include <yq/trait/is_arithmetic.hpp>
#include <yq/trait/is_integral.hpp>
#include <yq/trait/product.hpp>
#include <yq/trait/quotient.hpp>
#include <yq/trait/self_divide.hpp>
#include <yq/trait/self_multiply.hpp>
#include <yq/trait/square.hpp>

#if YQ_USE_GLM
    #include <yq/math/glm.hpp>
#endif

#include <span>
#include <vector>

namespace log4cpp { class CategoryStream; }

namespace yq {
    template <typename> struct Absolute;
    template <typename> struct AllComponents;
    template <typename> struct AnyComponents;
    template <typename> struct AxBox1;
    template <typename> struct Multivector1;
    template <typename> struct Segment1;
    template <typename> struct Size1;
    template <typename> struct Tensor11;
    template <typename> struct Tensor12;
    template <typename> struct Tensor13;
    template <typename> struct Tensor14;
    template <typename> struct Vector2;
    template <typename> struct Vector3;
    template <typename> struct Vector4;

    class Stream;

    /*! \brief Vector of 1 dimension
    
        This is a 1 dimensional cartesian vector of the given type.
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Vector1 {
        //! Component data type argument to this structure (ie, template parameter T)
        using component_type = T;


        T       x;
        
        // TODO -- refactor these operators, methods back out of the structure        
        constexpr Vector1() noexcept = default;
        constexpr Vector1(T _x) noexcept : x(_x) {}
        constexpr Vector1(all_k, T v) noexcept : x(v) {}
        template <typename=void> requires has_nan_v<T>
        consteval Vector1(nan_k) noexcept : Vector1(ALL, nan_v<T>) {}
        template <typename=void> requires has_one_v<T>
        consteval Vector1(one_k) noexcept : Vector1(ALL, one_v<T>) {}
        constexpr Vector1(x_k, T v) noexcept : x(v) {}
        template <typename=void> requires has_one_v<T>
        consteval Vector1(x_k) noexcept : x(one_v<T>) {}
        template <typename=void> requires has_zero_v<T>
        consteval Vector1(zero_k) noexcept : Vector1(ALL, zero_v<T>) {}

        #if YQ_USE_GLM
        template <glm::qualifier Q>
        requires std::is_floating_point_v<T>
        explicit constexpr Vector1(const glm::vec<1, T, Q>& v) : x(v.x) {}
        #endif

        explicit constexpr Vector1(const Size1<T>&) noexcept;

        template <typename U>
        requires std::is_nothrow_convertible_v<T,U>
        explicit constexpr operator Vector1<U>() const noexcept
        {
            return { (U) x };
        }
        
        template <typename U>
        requires (std::is_convertible_v<T,U> && !std::is_nothrow_convertible_v<T,U>)
        explicit constexpr operator Vector1<U>() const 
        {
            return { (U) x };
        }

        /*! \brief Creates a unit-vector in the x-dimension.
        */
        static consteval Vector1 unit_x() noexcept
        {
            return Vector1(X);
        }
        
        //constexpr Vector1(const glm::vec<1, T, glm::defaultp>& v) noexcept : x(v.x) {}
        
        //! Equality operator (using default)
        constexpr bool operator==(const Vector1&) const noexcept = default;

        #ifdef YQ_USE_GLM
        //! Implicit conversion to GLM vector
        template <glm::qualifier Q>
        requires std::is_floating_point_v<T>
        constexpr operator glm::vec<1, T, Q>() const noexcept
        {
            return glm::vec<1, T, Q>(x);
        }
        #endif
        
        //! Explicit conversion operator
        template <typename U>
        requires (std::is_convertible_v<T,U> && !std::is_same_v<T,U>)
        explicit operator Vector1<U>() const
        {
            return Vector1<U>( U(x));
        }

        //! An explicit cast when its "ambiguous"
        template <typename U>
        constexpr Vector1<U>  cast() const
        {
            return { (U) x };
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
        constexpr square_t<T> operator^(two_k) const noexcept;

        //! Addition with scalar
        constexpr Multivector1<T> operator+(T b) const noexcept;

        //! Addition with a box
        constexpr AxBox1<T> operator+(const AxBox1<T>&) const noexcept;

        //! Addition with multivector
        constexpr Multivector1<T> operator+(const Multivector1<T>& b) const noexcept;
        
        //! Addition with a segment
        constexpr Segment1<T> operator+(const Segment1<T>&) const noexcept;
        
        //! Addition
        constexpr Vector1 operator+(const Vector1& b) const noexcept;

        //! Self-addition
        Vector1& operator+=(const Vector1& b) noexcept;

        //! Span-wise addition (results in a vector)
        std::vector<Vector1> operator+(std::span<const Vector1>) const;

        //! Subtraction with scalar
        constexpr Multivector1<T> operator-(T b) const noexcept;
        
        //! Subtraction with a box
        constexpr AxBox1<T> operator-(const AxBox1<T>&) const noexcept;

        //! Subtraction with multivector
        constexpr Multivector1<T> operator-(const Multivector1<T>& b) const noexcept;
        
        //! Subtraction with a segment
        constexpr Segment1<T> operator-(const Segment1<T>&) const noexcept;

        //! Subtraction
        constexpr Vector1 operator-(const Vector1& b) const noexcept;

        //! Self-subtraction
        Vector1& operator-=(const Vector1& b) noexcept;
        
        std::vector<Vector1> operator-(std::span<const Vector1>) const;

        //! Multiplication with scalar
        template <typename U>
        requires (is_arithmetic_v<U>)
        constexpr Vector1<product_t<T,U>> operator*(U b) const noexcept;
        
        //! Self-multiplication with scalar
        template <typename U>
        requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
        Vector1<T>& operator*=(U b) noexcept;

        template <typename U>
        constexpr Multivector1<product_t<T,U>> operator*(const Multivector1<U>& b) const noexcept;

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
        requires self_multiply_v<T,U>
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

        template <typename U>
        constexpr product_t<T,U>   operator INNER(const Multivector1<T>&b) const noexcept;

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
        requires (is_arithmetic_v<U>)
        constexpr  Vector1<quotient_t<T,U>> operator/(U b) const noexcept;

        //! Self-division with scalar
        template <typename U>
        requires (is_arithmetic_v<U> && self_divide_v<T,U>)
        Vector1<T>& operator/=(U b) noexcept;

        //! Division with vector
        template <typename U>
        constexpr quotient_t<T,U> operator/(const Vector1<U>& b) const noexcept;

        //! Union with a box
        constexpr AxBox1<T> operator|(const AxBox1<T>&b) const noexcept;
        //! Create a box as a union of two vectors
        constexpr AxBox1<T> operator|(const Vector1&b) const noexcept;

        //! TRUE if the second vector is CLOSE to this vector, as defined by the comparison operator
        template <typename R=Absolute<T>>
        bool close(const Vector1&b, R compare) const;

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
        
        //! Decrement all elements
        Vector1&    all_decrement(T b) noexcept;

        //! Increment all elements
        Vector1&    all_increment(T b) noexcept;

        /*! \brief Subtracts value from all elements
        */
        constexpr Vector1 all_subtract(T b) const noexcept;

       /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if all tests are true.
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool all_test(Pred pred) const noexcept;

        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if all tests are true.
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool all_test(const Vector1& b, Pred pred) const noexcept;

        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if all tests are true.
            \param[in] b The other value
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool all_test(T b, Pred pred) const noexcept;
        

            //  ===================================================================================================
            //  AnyComponents Adapters
            //  ===================================================================================================

        
        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if any test is true.
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool any_test(Pred pred) const noexcept;
        
        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if any test is true.
            \param[in] b The other vector
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool any_test(const Vector1& b, Pred pred) const noexcept;
        
        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if any test is true.
            \param[in] b The other value
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool any_test(T b, Pred pred) const noexcept;
        
        static bool less_x( const Vector1& a, const Vector1& b) 
        {
            return a.x < b.x;
        }

    };

    YQ_IEEE754_1(Vector1)
    YQ_INTEGER_1(Vector1)
    YQ_IS_INTEGER_1(Vector1)


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
    
    #ifdef YQ_USE_GLM
    template <typename T, glm::qualifier Q>
    constexpr Vector1<T> vector(const glm::vec<1,T,Q>& v) noexcept
    {
        return Vector1( v.x);
    }
    #endif

    constexpr Vector1D operator ""_x1(unsigned long long int v) noexcept
    {
        return Vector1D(X, (double) v);
    }

    constexpr Vector1D operator ""_x1(long double v) noexcept
    {
        return Vector1D(X, (double) v);
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
//  IDENTITY


//  --------------------------------------------------------
//  ADDITION

    template <typename T>
    constexpr Multivector1<T> operator+(T a, const Vector1<T>& b) noexcept;
    
    template <typename T>
    std::vector<Vector1<T>>   operator+(std::span<const Vector1<T>>, Vector1<T>);

//  --------------------------------------------------------
//  SUBTRACTION

    template <typename T>
    constexpr Multivector1<T> operator-(T a, const Vector1<T>& b) noexcept;
    template <typename T>
    std::vector<Vector1<T>>   operator-(std::span<const Vector1<T>>, Vector1<T>);

//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires (is_arithmetic_v<T>)
    constexpr Vector1<product_t<T,U>> operator*(T a, const Vector1<U>&b) noexcept;

    template <typename T, typename U>
    requires (is_arithmetic_v<T>)
    std::vector<Vector1<product_t<T,U>>>   operator*(T a, std::span<const Vector1<U>>);

    template <typename T, typename U>
    requires (is_arithmetic_v<U>)
    std::vector<Vector1<product_t<T,U>>> operator*(std::span<const Vector1<T>>, U b);

    template <typename T, typename U>
    std::vector<Vector1<product_t<T,U>>> operator*(std::span<const Vector1<T>>, const Tensor11<U>&);
    template <typename T, typename U>
    std::vector<Vector2<product_t<T,U>>> operator*(std::span<const Vector1<T>>, const Tensor12<U>&);
    template <typename T, typename U>
    std::vector<Vector3<product_t<T,U>>> operator*(std::span<const Vector1<T>>, const Tensor13<U>&);
    template <typename T, typename U>
    std::vector<Vector4<product_t<T,U>>> operator*(std::span<const Vector1<T>>, const Tensor14<U>&);

    template <typename T, typename U>
    constexpr Vector1<product_t<T,U>>    mul_elem(const Vector1<T>&a, const Vector1<U>&b) noexcept;

//  --------------------------------------------------------
//  DIVISION

    template <typename T, typename U>
    requires (is_arithmetic_v<T>)
    constexpr  Vector1<quotient_t<T,U>> operator/(T a, const  Vector1<U>&b) noexcept;

    template <typename T, typename U>
    requires (is_arithmetic_v<U>)
    std::vector<Vector1<quotient_t<T,U>>>   operator/(std::span<Vector1<T>>, U b);

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
    constexpr Vector1<T>   max_elem(std::initializer_list<Vector1<T>>) noexcept;
    
    template <typename T>
    constexpr Vector1<T>   max_elem(std::span<const Vector1<T>>) noexcept;

    /*! \brief Mid-way divide two vectors
    */
    template <typename T>
    constexpr Vector1<T>        midvector(const Vector1<T>& a, const Vector1<T>& b=Vector1<T>{}) noexcept;

    template <typename T>
    constexpr Vector1<T>   min_elem(const Vector1<T>&a, const Vector1<T>&b) noexcept;

    template <typename T>
    constexpr Vector1<T>   min_elem(std::initializer_list<Vector1<T>>) noexcept;

    template <typename T>
    constexpr Vector1<T>   min_elem(std::span<const Vector1<T>>) noexcept;

    template <typename T>
    AllComponents<Vector1<T>>   all(Vector1<T>& val);

    template <typename T>
    AllComponents<const Vector1<T>>   all(const Vector1<T>& val);
    
    #if 0
    template <typename T>
    ElemComponents<Vector1<T>>   elem(Vector1<T>& val);

    template <typename T>
    ElemComponents<const Vector1<T>>   elem(const Vector1<T>& val);
    #endif

    template <typename T>
    AnyComponents<Vector1<T>>   any(Vector1<T>& val);

    template <typename T>
    AnyComponents<const Vector1<T>>   any(const Vector1<T>& val);

    template <typename S, typename T>
    S&  as_stream(S& s, const Vector1<T>& v);
    
    template <typename T>
    Stream& operator<<(Stream&s, const Vector1<T>& v);

    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const Vector1<T>& v);

    Vector1I    iround(const Vector1D&);
}

YQ_TYPE_DECLARE(yq::Vector1D)
YQ_TYPE_DECLARE(yq::Vector1F)
YQ_TYPE_DECLARE(yq::Vector1I)
YQ_TYPE_DECLARE(yq::Vector1U)

