////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_VECTOR_2_HPP 1

#include <yq/typedef/vector2.hpp>

#include <yq/keywords.hpp>
#include <yq/macro/operators.hpp>
#include <yq/math/glm.hpp>
#include <yq/meta/InfoBinder.hpp>
#include <yq/trait/has_nan.hpp>
#include <yq/trait/has_is_finite.hpp>
#include <yq/trait/has_one.hpp>
#include <yq/trait/has_sqrt.hpp>
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
#include <yq/unit/declare.hpp>

#include <span>
#include <vector>

namespace log4cpp { class CategoryStream; }

namespace yq {
    template <typename> struct Absolute;
    template <typename> struct AllComponents;
    template <typename> struct AnyComponents;
    template <typename> struct AxBox2;
    template <typename> struct Bivector2;
    template <typename> struct Circle2;
    template <typename> struct Multivector2;
    template <typename> struct Polygon2;
    template <typename> struct Polyline2;
    template <typename> struct Quadrilateral2;
    template <typename> struct Rectangle2;
    template <typename> struct Segment2;
    template <typename> struct Size2;
    template <typename> struct Spinor2;
    template <typename> struct Tensor21;
    template <typename> struct Tensor22;
    template <typename> struct Tensor23;
    template <typename> struct Tensor24;
    template <typename> struct Triangle2;
    template <typename> struct Vector1;
    template <typename> struct Vector3;
    template <typename> struct Vector4;
    
    class Stream;

    /*! \brief Vector of 2 dimensions
    
        This is a 2 dimensional cartesian vector of the given type.
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Vector2 {
        //! Component data type argument to this structure (ie, template parameter T)
        using component_type = T;

        T       x;
        T       y;
        
        constexpr Vector2() noexcept = default;
        constexpr Vector2(T _x, T _y) noexcept : x(_x), y(_y) {}
        constexpr Vector2(all_k, T v) noexcept : x(v), y(v) {}
        template <typename=void> requires has_nan_v<T>
        consteval Vector2(nan_k) noexcept : Vector2(ALL, nan_v<T>) {}
        consteval Vector2(one_k) noexcept : Vector2(ALL, one_v<T>) {}
        consteval Vector2(x_k) noexcept : x(one_v<T>), y(zero_v<T>) {}
        constexpr Vector2(x_k, T v) noexcept : x(v), y(zero_v<T>) {}
        consteval Vector2(y_k) noexcept : x(zero_v<T>), y(one_v<T>) {}
        constexpr Vector2(y_k, T v) noexcept : x(zero_v<T>), y(v) {}
        consteval Vector2(zero_k) noexcept : Vector2(ALL, zero_v<T>) {}
        
        explicit constexpr Vector2(const Size2<T>&) noexcept;

        template <typename U>
        requires std::is_nothrow_convertible_v<T,U>
        explicit constexpr operator Vector2<U>() const noexcept
        {
            return { (U) x, (U) y };
        }
        
        template <typename U>
        requires (std::is_convertible_v<T,U> && !std::is_nothrow_convertible_v<T,U>)
        explicit constexpr operator Vector2<U>() const 
        {
            return { (U) x, (U) y };
        }
        
        
        #ifdef YQ_USE_GLM
        template <glm::qualifier Q>
        explicit constexpr Vector2(const glm::vec<2, T, Q>& v) : x(v.x), y(v.y) {}
        #endif

        /*! \brief Creates a unit-vector in the x-dimension.
        */
        static consteval Vector2 unit_x() noexcept
        {
            return Vector2(X);
        }
        
        /*! \brief Creates a unit-vector in the y-dimension.
        */
        static consteval Vector2 unit_y() noexcept
        {
            return Vector2(Y);
        }

        //! An explicit cast when its "ambiguous"
        template <typename U>
        constexpr Vector2<U>  cast() const
        {
            return { (U) x, (U) y };
        }
        
        //! Equality operator (using default)
        constexpr bool operator==(const Vector2&) const noexcept = default;

        #ifdef YQ_USE_GLM
        template <glm::qualifier Q>
        constexpr operator glm::vec<2, T, Q>() const noexcept
        {
            return glm::vec<2, T, Q>( x, y );
        }
        #endif

        //! Explicit conversion operator
        template <typename U>
        requires (std::is_convertible_v<T,U> && !std::is_same_v<T,U>)
        explicit operator Vector2<U>() const
        {
            return Vector2<U>( U(x), U(x) );
        }
        
        //! Affirmation (positive) operator
        constexpr Vector2 operator+() const noexcept
        {
            return *this;
        }

        //! Negation (negative) operator
        constexpr Vector2 operator-() const noexcept;

        //! Normalization of vector (ie, unit length)
        Vector2<quotient_t<T,T>> operator~() const;

        //! Squares the vector (ie, length square)
        constexpr square_t<T> operator^(two_k) const noexcept;

        //! Addition with number
        constexpr Multivector2<T> operator+(T b) const noexcept;
        
        constexpr AxBox2<T> operator+(const AxBox2<T>&) const noexcept;

        //! Addition with bivector
        constexpr Multivector2<T> operator+(const Bivector2<T>& b) const noexcept;
        
        constexpr Circle2<T> operator+(const Circle2<T>&) const noexcept;
        
        //! Addition with multivector
        constexpr Multivector2<T> operator+(const Multivector2<T>& b) const noexcept;

        Polygon2<T> operator+(const Polygon2<T>&) const;
        Polyline2<T> operator+(const Polyline2<T>&) const;

        constexpr Quadrilateral2<T>   operator+(const Quadrilateral2<T>&) const noexcept;
        
        constexpr Rectangle2<T> operator+(const Rectangle2<T>&) const noexcept;

        constexpr Segment2<T> operator+(const Segment2<T>&) const noexcept;
        
        constexpr Rectangle2<T> operator+(const Size2<T>&) const noexcept;
        
        constexpr Triangle2<T> operator+(const Triangle2<T>&) const noexcept;

        //! Addition to vector
        constexpr Vector2 operator+(const Vector2& b) const noexcept;
        
        std::vector<Vector2<T>> operator+(std::span<const Vector2>) const;
        
        //! Self-addition to vector
        Vector2& operator+=(const Vector2& b) noexcept;

        //! Subtraction with number
        constexpr Multivector2<T> operator-(T b) const noexcept;
        
        constexpr AxBox2<T> operator-(const AxBox2<T>&) const noexcept;

        //! Subtraction with bivector
        constexpr Multivector2<T> operator-(const Bivector2<T>& b) const noexcept;
        
        constexpr Circle2<T> operator-(const Circle2<T>&) const noexcept;

        //! Subtraction with multivector
        constexpr Multivector2<T> operator-(const Multivector2<T>& b) const noexcept;

        Polygon2<T> operator-(const Polygon2<T>&) const;
        Polyline2<T> operator-(const Polyline2<T>&) const;
        
        constexpr Quadrilateral2<T>   operator-(const Quadrilateral2<T>&) const noexcept;

        constexpr Segment2<T> operator-(const Segment2<T>&) const noexcept;

        constexpr Triangle2<T> operator-(const Triangle2<T>&) const noexcept;

        //! Subtraction
        constexpr Vector2 operator-(const Vector2& b) const noexcept;
        std::vector<Vector2<T>> operator-(std::span<const Vector2>) const;

        //! Self-subtraction
        Vector2& operator-=(const Vector2& b) noexcept;

        //! Multiplication (scalar)
        template <typename U>
        requires (is_arithmetic_v<U>)
        constexpr Vector2<product_t<T,U>> operator*(U b) const noexcept;

        //! Self-multiplication
        template <typename U>
        requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
        Vector2<T>& operator*=(U b) noexcept;
        
        template <typename U>
        constexpr Vector1<product_t<T,U>> operator*(const Tensor21<U>&) const noexcept;
        template <typename U>
        constexpr Vector2<product_t<T,U>> operator*(const Tensor22<U>&) const noexcept;
        template <typename U>
        constexpr Vector3<product_t<T,U>> operator*(const Tensor23<U>&) const noexcept;
        template <typename U>
        constexpr Vector4<product_t<T,U>> operator*(const Tensor24<U>&) const noexcept;
        
        template <typename U>
        requires self_multiply_v<T,U>
        Vector2&  operator*=(const Tensor22<U>&) noexcept;

        //! Geometric product
        template <typename U>
        constexpr Multivector2<product_t<T,U>> operator*(const Vector2<U>&) const noexcept;

        //! Dot product
        template <typename U>
        constexpr product_t<T,U> operator DOT (const Vector2<U>&b) const noexcept;

        //! Inner product
        template <typename U>
        constexpr product_t<T,U> operator INNER (const Vector2<U>&b) const noexcept;

        //! Cross product
        template <typename U>
        constexpr product_t<T,U> operator CROSS (const Vector2<U>&b) const noexcept;

        template <typename U>
        constexpr Bivector2<product_t<T,U>> operator OUTER (const Vector2<U>& b) const noexcept;

        //! OTIMES Vector1
        template <typename U>
        constexpr Tensor21<product_t<T,U>> operator OTIMES(const Vector1<U>&b) const noexcept;
        //! OTIMES Vector2
        template <typename U>
        constexpr Tensor22<product_t<T,U>> operator OTIMES(const Vector2<U>&b) const noexcept;
        //! OTIMES Vector3
        template <typename U>
        constexpr Tensor23<product_t<T,U>> operator OTIMES(const Vector3<U>&b) const noexcept;
        //! OTIMES Vector4
        template <typename U>
        constexpr Tensor24<product_t<T,U>> operator OTIMES(const Vector4<U>&b) const noexcept;

        //! Division
        template <typename U>
        requires (is_arithmetic_v<U>)
        constexpr  Vector2<quotient_t<T,U>> operator/(U b) const noexcept;

        //! Self-division
        template <typename U>
        requires (is_arithmetic_v<U> && self_divide_v<T,U>)
        Vector2<T>& operator/=(U b) noexcept;
        
        template <typename U>
        constexpr Multivector2<quotient_t<T,U>>   operator/ (const Vector2<U>&b) const noexcept;

        //! Union
        constexpr AxBox2<T> operator|(const AxBox2<T>&b) const noexcept;

        //! Create a box as a union of two vectors
        constexpr AxBox2<T> operator|(const Vector2&b) const noexcept;
        
        template <typename=void>
        Radian ccw_x() const;

        template <typename=void>
        Radian clockwise_y() const;

        //! TRUE if the second vector is CLOSE to this vector, as defined by the comparison operator
        template <typename R=Absolute<T>>
        bool close(const Vector2&b, R compare) const;

        //! Returns the most positive component (as defined by the max function)
        constexpr T     cmax() const noexcept;

        //! Returns the most negative component (as defined by the min function)
        constexpr T     cmin() const noexcept;
    
        //! Returns the product of the components
        constexpr square_t<T>     cproduct() const noexcept;

        //! Returns the sum of the components
        constexpr T   csum() const noexcept;

        //! Element by element absolute value
        constexpr Vector2   eabs() const noexcept;

        //! Element by element division
        template <typename U>
        constexpr Vector2<quotient_t<T,U>>    ediv(const Vector2<U>&b) const noexcept;

        //! Element by element maximum
        constexpr Vector2   emax(const Vector2&b) const noexcept;

        //! Element by element minimum
        constexpr Vector2   emax(T b) const noexcept;

        //! Element by element minimum
        constexpr Vector2   emin(const Vector2&b) const noexcept;

        //! Element by element minimum
        constexpr Vector2   emin(T b) const noexcept;

        //! Element by element multiplication
        template <typename U>
        constexpr Vector2<product_t<T,U>>    emul(const Vector2<U>&b) const noexcept;

        /*! \brief Square of the vector's length
        
            This returns the SQUARE of this vector's length.
        */
        constexpr square_t<T> length²() const noexcept;
        
        /*! \brief Length of the vector
            
            This returns the length of this vector.
        */
        T       length() const;
        
        constexpr Vector3<T> z(T _z=T{}) const noexcept;

            //  ===================================================================================================
            //  AllComponents Adapters
            //  ===================================================================================================

        /*! Adds a value to all the components
        */
        constexpr Vector2 all_add(T b) const noexcept;
        
        //! Decrement all elements
        Vector2&    all_decrement(T b) noexcept;

        //! Increment all elements
        Vector2&    all_increment(T b) noexcept;

        /*! \brief Subtracts value to all components
        */
        constexpr Vector2 all_subtract(T b) const noexcept;

       /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if all tests are true.
            \note y test may be skipped if the x-component test fails.
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool all_test(Pred pred) const noexcept;

        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if all tests are true.
            \note y test may be skipped if the x-component test fails.
            \param[in] b The other vector
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool all_test(const Vector2& b, Pred pred) const noexcept;

        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if all tests are true.
            \note y test may be skipped if the x-component test fails.
            \param[in] b The other value
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool all_test(T b, Pred pred) const noexcept;


            //  ===================================================================================================
            //  AnyComponents Adapters
            //  
            //  The following all_test() are for the AllComponents Adapters, to apply the test on ALL components,
            //  returning true if all elements are successful
            //  ===================================================================================================
        
        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if any test is true.
            \note y component test may be skipped if the x-component test passes.
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool any_test(Pred pred) const noexcept;
        
        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if any test is true.
            \note y component test may be skipped if the x-component test passes.
            \param[in] b The other vector
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool any_test(const Vector2& b, Pred pred) const noexcept;
        
        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if any test is true.
            \note y component test may be skipped if the x-component test passes.
            \param[in] b The other value
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool any_test(T b, Pred pred) const noexcept;
        
            //  ===================================================================================================
            //  ElemComponents Adapters
            //  
            //  The following are for the ElemComponents Adapters
            //  ===================================================================================================

        static bool less_x( const Vector2& a, const Vector2& b) 
        {
            return a.x < b.x;
        }

        static bool less_y( const Vector2& a, const Vector2& b) 
        {
            return a.y < b.y;
        }
    };

    YQ_IEEE754_1(Vector2)
    YQ_INTEGER_1(Vector2)
    YQ_IS_INTEGER_1(Vector2)
    
//  --------------------------------------------------------
//  COMPOSITION


    /*! \brief Creates a 2 dimensioal vector
    
        Helper function to create a 2 dimensional cartesian vector where the component type is deduced from
        the first argument.
    */
    template <typename T>
    constexpr Vector2<T> vector(T x, std::type_identity_t<T> y) noexcept
    {
        return Vector2<T>(x,y);
    }
    
    #ifdef YQ_USE_GLM
    template <typename T, glm::qualifier Q>
    constexpr Vector2<T> vector(const glm::vec<2,T,Q>& v) noexcept
    {
        return Vector2<T>( v.x, v.y );
    }
    #endif

    constexpr Vector2D operator ""_x2(unsigned long long int v) noexcept
    {
        return Vector2D(X, (double) v);
    }

    constexpr Vector2D operator ""_x2(long double v) noexcept
    {
        return Vector2D(X, (double) v);
    }

    constexpr Vector2D operator ""_y2(unsigned long long int v) noexcept
    {
        return Vector2D(Y, (double) v);
    }

    constexpr Vector2D operator ""_y2(long double v) noexcept
    {
        return Vector2D(Y, (double) v);
    }

    //! Creates a two dimension unit vector
    //!
    //! \param az   Counter-clockwise angle from +x
    inline Vector2D     ccw(Radian az);

    //! Creates a two dimension unit vector
    //!
    //! \param az    Clockwise angle from +y
    inline Vector2D     clockwise(Radian az);

    YQ_NAN_1(Vector2, Vector2<T>(NAN))
    YQ_ONE_1(Vector2, Vector2<T>(ONE))
    YQ_ZERO_1(Vector2, Vector2<T>(ZERO))
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_NAN_1(Vector2, is_nan(v.x) || is_nan(v.y))
    YQ_IS_FINITE_1(Vector2, is_finite(v.x) && is_finite(v.y))
        

    /*! \brief Square of the vector's length
    
        This returns the SQUARE of the given vector's length.
    */
    template <typename T>
    constexpr square_t<T> length²(const Vector2<T>& vec) noexcept;

    /*! \brief Length of the vector
        
        This returns the length of the given vector.
    */
    template <typename T>
    requires has_sqrt_v<T>
    auto    length(const Vector2<T>& a);

//  --------------------------------------------------------
//  ADDITION

    //! Adds scalar with vector
    template <typename T>
    constexpr Multivector2<T> operator+(T a, const Vector2<T>& b) noexcept;
    template <typename T>
    std::vector<Vector2<T>>   operator+(std::span<const Vector2<T>>, Vector2<T>);

//  --------------------------------------------------------
//  SUBTRACTION

    template <typename T>
    constexpr Multivector2<T> operator-(T a, const Vector2<T>& b) noexcept;
    template <typename T>
    std::vector<Vector2<T>>   operator-(std::span<const Vector2<T>>, Vector2<T>);


//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires (is_arithmetic_v<T>)
    constexpr Vector2<product_t<T,U>> operator*(T a, const Vector2<U>&b) noexcept;

    template <typename T, typename U>
    requires (is_arithmetic_v<T>)
    std::vector<Vector2<product_t<T,U>>>   operator*(T a, std::span<const Vector2<U>>);

    template <typename T, typename U>
    requires (is_arithmetic_v<U>)
    std::vector<Vector2<product_t<T,U>>>   operator*(std::span<const Vector2<T>>, U b);

    template <typename T, typename U>
    std::vector<Vector1<product_t<T,U>>> operator*(std::span<const Vector2<T>>, const Tensor21<U>&);
    template <typename T, typename U>
    std::vector<Vector2<product_t<T,U>>> operator*(std::span<const Vector2<T>>, const Tensor22<U>&);
    template <typename T, typename U>
    std::vector<Vector3<product_t<T,U>>> operator*(std::span<const Vector2<T>>, const Tensor23<U>&);
    template <typename T, typename U>
    std::vector<Vector4<product_t<T,U>>> operator*(std::span<const Vector2<T>>, const Tensor24<U>&);

    template <typename T, typename U>
    constexpr Vector2<product_t<T,U>>    mul_elem(const Vector2<T>&a, const Vector2<U>&b) noexcept;

//  --------------------------------------------------------
//  DIVISION

    template <typename T, typename U>
    requires (is_arithmetic_v<T>)
    constexpr  Vector2<quotient_t<T,U>> operator/(T a, const  Vector2<U>&b) noexcept;

    template <typename T, typename U>
    requires (is_arithmetic_v<U>)
    std::vector<Vector2<quotient_t<T,U>>>   operator/(std::span<const Vector2<T>>, U b);

    template <typename T, typename U>
    constexpr Vector2<quotient_t<T,U>>    div_elem(const Vector2<T>&a, const Vector2<U>&b) noexcept;


//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

    template <typename T>
    constexpr Vector2<T>   abs_elem(const Vector2<T>&a) noexcept;

    template <typename T>
    requires (std::is_floating_point_v<T> && has_sqrt_v<T>)
    Radian       angle(const Vector2<T>&a, const Vector2<T>& b);


    template <typename T, typename DIM1, typename DIM2>
    requires (std::is_floating_point_v<T> && has_sqrt_v<T>)
    Radian      angle(const Vector2<MKS<T,DIM1>>&a, const Vector2<MKS<T,DIM2>>& b);

    /*! \brief Counter clockwise (euler) angle
    
        Computes the euler angle of the vector, ie, counter-clockwise from the +X axis.
    */
    template <typename T>
    requires std::is_floating_point_v<T>
    Radian   ccw(const Vector2<T>& a);

    /*! \brief Counter clockwise (euler) angle
    
        Computes the euler angle of the vector, ie, counter-clockwise from the +X axis.
    */
    template <typename T, typename DIM>
    requires std::is_floating_point_v<T>
    Radian   ccw(const Vector2<MKS<T,DIM>>& a);


    /*! \brief Clockwise angle
    
        Computes the angle of the vector from the +Y axis.
    */
    template <typename T>
    requires std::is_floating_point_v<T>
    MKS<T,dim::Angle>   clockwise(const Vector2<T>& a);

    /*! \brief Clockwise angle
    
        Computes the angle of the vector from the +Y axis.
    */
    template <typename T, typename DIM>
    requires std::is_floating_point_v<T>
    MKS<T,dim::Angle>   clockwise(const Vector2<MKS<T,DIM>>& a);

    template <typename T>
    constexpr T             component_max(const Vector2<T>&a) noexcept;

    template <typename T>
    constexpr T             component_min(const Vector2<T>&a) noexcept;

    template <typename T>
    constexpr square_t<T>     component_product(const Vector2<T>& a) noexcept;

    template <typename T>
    constexpr T   component_sum(const Vector2<T>& a) noexcept;

    /*! \brief "Delta Area"
    
        This is a building block for triangle & polygon area code, computes the "delta area" between two points
        (almost the same as area(aabb(a,b)) but can be negative.)
    */
    template <typename T>
    constexpr square_t<T>    delta_area(const Vector2<T>&a, const Vector2<T>& b) noexcept;

    /*! \brief "Point area" of the points
    
        This is a helper to area and other functions, 
        simply does an "area" of the point deltas, 
        no sign correction, no scaling.
    */
    template <typename T>
    constexpr square_t<T>    delta_area(const std::span<Vector2<T>>& vertex) noexcept;


    template <typename T, typename R>
    bool is_close(const R& compare, const Vector2<T>& actual, const Vector2<T>& expected);

    template <typename T, typename R>
    bool is_close(const R& compare, const Vector2<T>& actual, std::type_identity_t<T> x, std::type_identity_t<T> y);

    template <typename T>
    constexpr Vector2<T>   max_elem(const Vector2<T>&a, const Vector2<T>&b) noexcept;

    template <typename T>
    constexpr Vector2<T>   max_elem(std::initializer_list<Vector2<T>>) noexcept;
    
    template <typename T>
    constexpr Vector2<T>   max_elem(std::span<const Vector2<T>>) noexcept;

    /*! \brief Mid-way divide two vectors
    */
    template <typename T>
    constexpr Vector2<T>  midvector(const Vector2<T>& a, const Vector2<T>& b=Vector2<T>{}) noexcept;

    template <typename T>
    constexpr Vector2<T>   min_elem(const Vector2<T>&a, const Vector2<T>&b) noexcept;

    template <typename T>
    constexpr Vector2<T>   min_elem(std::initializer_list<Vector2<T>>) noexcept;

    template <typename T>
    constexpr Vector2<T>   min_elem(std::span<const Vector2<T>>) noexcept;

    template <typename T>
    AllComponents<Vector2<T>>   all(Vector2<T>& val);

    template <typename T>
    AllComponents<const Vector2<T>>   all(const Vector2<T>& val);
    
    #if 0
    template <typename T>
    ElemComponents<Vector2<T>>   elem(Vector2<T>& val);

    template <typename T>
    ElemComponents<const Vector2<T>>   elem(const Vector2<T>& val);
    #endif

    template <typename T>
    AnyComponents<Vector2<T>>   any(Vector2<T>& val);
    
    template <typename T>
    AnyComponents<const Vector2<T>>   any(const Vector2<T>& val);

    template <typename S, typename T>
    S&  as_stream(S& s, const Vector2<T>& v);
    
    template <typename T>
    Stream& operator<<(Stream&s, const Vector2<T>& v);

    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const Vector2<T>& v);
    
    Vector2I    iround(const Vector2D&);
}

YQ_TYPE_DECLARE(yq::Vector2D)
YQ_TYPE_DECLARE(yq::Vector2F)
YQ_TYPE_DECLARE(yq::Vector2I)
YQ_TYPE_DECLARE(yq::Vector2U)
YQ_TYPE_DECLARE(yq::Vector2M)
YQ_TYPE_DECLARE(yq::Vector2CM)
YQ_TYPE_DECLARE(yq::Vector2MM)

