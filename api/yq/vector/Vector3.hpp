////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_VECTOR_3_HPP 1

#include <yq/typedef/vector3.hpp>

#include <yq/keywords.hpp>
#include <yq/macro/operators.hpp>
#include <yq/math/glm.hpp>
#include <yq/meta/InfoBinder.hpp>
#include <yq/trait/cube.hpp>
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

#if YQ_USE_GLM || defined(YQ_FEATURE_GLM)
    #include <yq/math/glm.hpp>
#endif

#include <span>
#include <vector>

namespace log4cpp { class CategoryStream; }

namespace yq {
    template <typename> struct Absolute;
    template <typename> struct AllComponents;
    template <typename> struct AnyComponents;
    template <typename> struct AxBox3;
    template <typename> struct Bivector3;
    template <typename> struct Multivector3;
    template <typename> struct Polygon3;
    template <typename> struct Polyline3;
    template <typename> struct Quaternion3;
    template <typename> struct Segment3;
    template <typename> struct Size3;
    template <typename> struct Sphere3;
    template <typename> struct Tensor31;
    template <typename> struct Tensor32;
    template <typename> struct Tensor33;
    template <typename> struct Tensor34;
    template <typename> struct Tetrahedron3;
    template <typename> struct Triangle3;
    template <typename> struct Trivector3;
    template <typename> struct Vector1;
    template <typename> struct Vector2;
    template <typename> struct Vector4;
    
    class Stream;
    

    /*! \brief Vector of 3 dimensions
    
        This is a 3 dimensional cartesian vector of the given type.
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Vector3 {
        //! Component data type argument to this structure (ie, template parameter T)
        using component_type = T;

        T       x;
        T       y;
        T       z;
        
        constexpr Vector3() noexcept = default;
        constexpr Vector3(T _x, T _y, T _z) noexcept : x(_x), y(_y), z(_z) {}
        constexpr Vector3(all_k, T v) noexcept : x(v), y(v), z(v) {}
        template <typename=void> requires has_nan_v<T>
        consteval Vector3(nan_t) noexcept : Vector3(ALL, nan_v<T>) {}
        consteval Vector3(one_t) noexcept : Vector3(ALL, one_v<T>) {}
        consteval Vector3(x_t) noexcept : x(one_v<T>), y(zero_v<T>), z(zero_v<T>) {}
        constexpr Vector3(x_t, T v) noexcept : x(v), y(zero_v<T>), z(zero_v<T>) {}
        consteval Vector3(y_t) noexcept : x(zero_v<T>), y(one_v<T>), z(zero_v<T>) {}
        constexpr Vector3(y_t, T v) noexcept : x(zero_v<T>), y(v), z(zero_v<T>) {}
        consteval Vector3(z_t) noexcept : x(zero_v<T>), y(zero_v<T>), z(one_v<T>) {}
        constexpr Vector3(z_t, T v) noexcept : x(zero_v<T>), y(zero_v<T>), z(v) {}
        consteval Vector3(zero_k) noexcept : Vector3(ALL, zero_v<T>) {}

        #if YQ_USE_GLM || defined(YQ_FEATURE_GLM)
        template <glm::qualifier Q>
        explicit constexpr Vector3(const glm::vec<3, T, Q>& v) : x(v.x), y(v.y), z(v.z) {}
        #endif

        explicit constexpr Vector3(const Size3<T>&) noexcept;

        template <typename U>
        requires std::is_nothrow_convertible_v<T,U>
        explicit constexpr operator Vector3<U>() const noexcept
        {
            return { (U) x, (U) y, (U) z };
        }
        
        template <typename U>
        requires (std::is_convertible_v<T,U> && !std::is_nothrow_convertible_v<T,U>)
        explicit constexpr operator Vector3<U>() const 
        {
            return { (U) x, (U) y, (U) z };
        }
        

        /*! \brief Creates a unit-vector in the x-dimension.
        */
        static consteval Vector3 unit_x() noexcept
        {
            return Vector3(X);
        }
        
        /*! \brief Creates a unit-vector in the y-dimension.
        */
        static consteval Vector3 unit_y() noexcept
        {
            return Vector3(Y);
        }
        
        /*! \brief Creates a unit-vector in the z-dimension.
        */
        static consteval Vector3 unit_z() noexcept
        {
            return Vector3(Z);
        }

        //! Equality operator (using default)
        constexpr bool operator==(const Vector3&) const noexcept = default;

        #if YQ_USE_GLM || defined(YQ_FEATURE_GLM)
        template <glm::qualifier Q>
        constexpr operator glm::vec<3, T, Q>() const noexcept
        {
            return glm::vec<3, T, Q>( x, y, z );
        }
        #endif

        //! Explicit conversion operator
        template <typename U>
        requires (std::is_convertible_v<T,U> && !std::is_same_v<T,U>)
        explicit operator Vector3<U>() const
        {
            return Vector3<U>( U(x), U(x), U(z) );
        }

        //! Affirmation
        constexpr Vector3 operator+() const noexcept
        {
            return *this;
        }

        //! Negation
        constexpr Vector3 operator-() const noexcept;

        //! Normalizations operator
        Vector3<quotient_t<T,T>> operator~() const;

        //! Square (ie, length2)
        constexpr square_t<T> operator^(two_t) const noexcept;

        //! Addition with number
        constexpr Multivector3<T> operator+(T b) const noexcept;
        
        constexpr AxBox3<T> operator+(const AxBox3<T>&) const noexcept;

        //! Addition with bivector
        constexpr Multivector3<T> operator+(const Bivector3<T>& b) const noexcept;
        
        //! Addition with multivector
        constexpr Multivector3<T> operator+(const Multivector3<T>& b) const noexcept;
        
        Polygon3<T> operator+(const Polygon3<T>&) const;
        Polyline3<T> operator+(const Polyline3<T>&) const;

        constexpr Segment3<T> operator+(const Segment3<T>&) const noexcept;

        constexpr Sphere3<T> operator+(const Sphere3<T>&) const noexcept;

        constexpr Tetrahedron3<T> operator+(const Tetrahedron3<T>&) const noexcept;

        constexpr Triangle3<T> operator+(const Triangle3<T>&) const noexcept;

        //! Addition with trivector
        constexpr Multivector3<T> operator+(const Trivector3<T>& b) const noexcept;

        //! Addition
        constexpr Vector3 operator+(const Vector3& b) const noexcept;

        //! Self-addition
        Vector3& operator+=(const Vector3& b) noexcept;
        
        std::vector<Vector3> operator+(std::span<const Vector3>) const;

        //! Subtraction with number
        constexpr Multivector3<T> operator-(T b) const noexcept;
        
        constexpr AxBox3<T> operator-(const AxBox3<T>&) const noexcept;

        //! Subtraction with bivector
        constexpr Multivector3<T> operator-(const Bivector3<T>& b) const noexcept;
        
        //! Subtraction with multivector
        constexpr Multivector3<T> operator-(const Multivector3<T>& b) const noexcept;

        Polygon3<T> operator-(const Polygon3<T>&) const;
        Polyline3<T> operator-(const Polyline3<T>&) const;

        constexpr Segment3<T> operator-(const Segment3<T>&) const noexcept;

        constexpr Sphere3<T> operator-(const Sphere3<T>&) const noexcept;

        constexpr Tetrahedron3<T> operator-(const Tetrahedron3<T>&) const noexcept;

        constexpr Triangle3<T> operator-(const Triangle3<T>&) const noexcept;

        //! Subtraction with trivector
        constexpr Multivector3<T> operator-(const Trivector3<T>& b) const noexcept;

        //! Subtraction
        constexpr Vector3 operator-(const Vector3& b) const noexcept;

        //! Self-subtraction
        Vector3& operator-=(const Vector3& b) noexcept;

        std::vector<Vector3> operator-(std::span<const Vector3>) const;

        //! Multiplication with scalar
        template <typename U>
        requires (is_arithmetic_v<U>)
        constexpr Vector3<product_t<T,U>> operator*(U b) const noexcept;

        //! Self-multiplication
        template <typename U>
        requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
        Vector3<T>& operator*=(U b) noexcept;

        //! Vector/tensor multiplication
        template <typename U>
        constexpr Vector1<product_t<T,U>> operator*(const Tensor31<U>&b) const noexcept;
        //! Vector/tensor multiplication
        template <typename U>
        constexpr Vector2<product_t<T,U>> operator*(const Tensor32<U>&b) const noexcept;
        //! Vector/tensor multiplication
        template <typename U>
        constexpr Vector3<product_t<T,U>> operator*(const Tensor33<U>&b) const noexcept;
        //! Vector/tensor multiplication
        template <typename U>
        constexpr Vector4<product_t<T,U>> operator*(const Tensor34<U>&b) const noexcept;
        //! Vector/tensor self multiplication
        template <typename U>
        requires (self_multiply_v<T,U>)
        Vector3& operator*=(const Tensor33<U>&b) noexcept;

        //! Geometric product
        template <typename U>
        constexpr Multivector3<product_t<U,T>> operator*(const Vector3<U>&) const noexcept;

        //! Dot product
        template <typename U>
        constexpr product_t<T,U> operator DOT (const Vector3<U>&b) const noexcept;

        //! Inner product
        template <typename U>
        constexpr product_t<T,U> operator INNER (const Vector3<U>&b) const noexcept;

        //! Cross product
        template <typename U>
        constexpr Vector3<product_t<T,U>> operator CROSS (const Vector3<U>&b) const noexcept;

        //! Outer product
        template <typename U>
        constexpr Bivector3<product_t<T,U>> operator OUTER (const Vector3<U>& b) noexcept;

        //! OTIMES Vector1
        template <typename U>
        constexpr Tensor31<product_t<T,U>> operator OTIMES(const Vector1<U>&b) const noexcept;
        //! OTIMES Vector2
        template <typename U>
        constexpr Tensor32<product_t<T,U>> operator OTIMES(const Vector2<U>&b) const noexcept;
        //! OTIMES Vector3
        template <typename U>
        constexpr Tensor33<product_t<T,U>> operator OTIMES(const Vector3<U>&b) const noexcept;
        //! OTIMES Vector4
        template <typename U>
        constexpr Tensor34<product_t<T,U>> operator OTIMES(const Vector4<U>&b) const noexcept;
    
        //! Division
        template <typename U>
        requires (std::is_arithmetic_v<U>)
        constexpr  Vector3<quotient_t<T,U>> operator/(U b) const noexcept;

        //! Self-division
        template <typename U>
        requires (std::is_arithmetic_v<U> && self_divide_v<T,U>)
        Vector3<T>& operator/=(U b) noexcept;

        template <typename U>
        constexpr Multivector3<quotient_t<T,U>>   operator/ (const Vector3<U>&b) const noexcept;

        //! Union
        constexpr AxBox3<T>  operator|(const AxBox3<T>& b) const noexcept;

        //! Create a box as a union of two vectors
        constexpr AxBox3<T> operator|(const Vector3&b) const noexcept;

        template <typename R=Absolute<T>>
        bool close(const Vector3& expected, const R& compare) const;

        //! Most positive component of the vector
        constexpr T cmax() const noexcept;

        //! Most negative component of the vector
        constexpr T cmin() const noexcept;

        //! Product of the vector's components
        constexpr cube_t<T>     cproduct() const noexcept;
        
        //! Sum of the vector's components
        constexpr T   csum() const noexcept;
        
        //! Absolute value of each component
        constexpr Vector3   eabs() const noexcept;

        //! Element by element division
        template <typename U>
        constexpr Vector3<quotient_t<T,U>>    ediv(const Vector3<U>&b) const noexcept;

        //! Biggest (max) applied element by element
        constexpr Vector3   emax(const Vector3&b) const noexcept;

        //! Smallest (min) applied element by element
        constexpr Vector3   emin(const Vector3&b) const noexcept;

        //! Element by element multiplication
        template <typename U>
        constexpr Vector3<product_t<T,U>>    emul(const Vector3<U>&b) const noexcept;
 
        /*! \brief Square of the vector's length
        
            This returns the SQUARE of the given vector's length.
        */
        constexpr square_t<T> length²() const noexcept;
        
        /*! \brief Length of the vector
            
            This returns the length of this vector.
        */
        T       length() const;
        
        Vector2<T>  xy() const;
        Vector2<T>  yz() const;
        Vector2<T>  zx() const;

            //  ===================================================================================================
            //  AllComponents Adapters
            //  ===================================================================================================

        /*! Adds a value to all the elements
        */
        constexpr Vector3 all_add(T b) const noexcept;
        
        //! Decrement all elements
        Vector3&    all_decrement(T b) noexcept;

        //! Increment all elements
        Vector3&    all_increment(T b) noexcept;

        /*! \brief Subtracts value from all elements
        */
        constexpr Vector3 all_subtract(T b) const noexcept;

       /*! Tests every element
            
            This applies the given test to every component, 
            returns TRUE if all tests are true.
            \note y & z component tests may be skipped if the x-component test fails.
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool all_kest(Pred pred) const noexcept;

        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if all tests are true.
            \note y & z component tests may be skipped if the x-component test fails.
            \param[in] b The other vector
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool all_kest(const Vector3& b, Pred pred) const noexcept;

        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if all tests are true.
            \note y & z component tests may be skipped if the x-component test fails.
            \param[in] b The other value
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool all_kest(T b, Pred pred) const noexcept;


            //  ===================================================================================================
            //  AnyComponents Adapters
            //  
            //  The following all_kest() are for the AllComponents Adapters, to apply the test on ALL components,
            //  returning true if all elements are successful
            //  ===================================================================================================
        
        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if any test is true.
            \note y & z component tests may be skipped if the x-component test passes.
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool any_test(Pred pred) const noexcept;
        
        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if any test is true.
            \note y & z component tests may be skipped if the x-component test passes.
            \param[in] b The other vector
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool any_test(const Vector3& b, Pred pred) const noexcept;
        
        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if any test is true.
            \note y & z component tests may be skipped if the x-component test passes.
            \param[in] b The other value
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool any_test(T b, Pred pred) const noexcept;
        
        static bool less_x( const Vector3& a, const Vector3& b)
        { 
            return a.x < b.x; 
        }

        static bool less_y( const Vector3& a, const Vector3& b)
        {
            return a.y < b.y;
        }

        static bool less_z( const Vector3& a, const Vector3& b) 
        {
            return a.z < b.z;
        }
    };

    YQ_IEEE754_1(Vector3)
    YQ_INTEGER_1(Vector3)
    YQ_IS_INTEGER_1(Vector3)
    
//  --------------------------------------------------------
//  COMPOSITION


    /*! \brief Creates a 3 dimensioal vector
    
        Helper function to create a 3 dimensional cartesian vector where the component type is deduced from
        the first argument.
    */
    template <typename T>
    constexpr Vector3<T> vector(T x, std::type_identity_t<T> y, std::type_identity_t<T> z) noexcept
    {
        return Vector3<T>( x,y,z );
    }
    
    #ifdef YQ_USE_GLM
    template <typename T, glm::qualifier Q>
    constexpr Vector3<T> vector(const glm::vec<3,T,Q>& v) noexcept
    {
        return Vector3<T>( v );
    }
    #endif

    constexpr Vector3D operator "" _x3(unsigned long long int v) noexcept
    {
        return Vector3D(X, (double) v);
    }

    constexpr Vector3D operator "" _x3(long double v) noexcept
    {
        return Vector3D(X, (double) v);
    }

    constexpr Vector3D operator "" _y3(unsigned long long int v) noexcept
    {
        return Vector3D(Y, (double) v);
    }

    constexpr Vector3D operator "" _y3(long double v) noexcept
    {
        return Vector3D(Y, (double) v);
    }

    constexpr Vector3D operator "" _z3(unsigned long long int v) noexcept
    {
        return Vector3D(Z, (double) v);
    }

    constexpr Vector3D operator "" _z3(long double v) noexcept
    {
        return Vector3D(Z, (double) v);
    }



    //! Creates a three dimension unit vector
    //!
    //! \param az   Counter-clockwise angle from +x
    //! \param el   Elevation (up) angle from x-y plane
    Vector3D    ccw(Radian az, Radian el);


    //! Creates a three dimension unit vector
    //!
    //! \param az   Clockwise angle from +x
    //! \param el   Elevation (up) angle from x-y plane
    Vector3D     clockwise(Radian az, Radian el);

    template <typename T>
    constexpr Vector2<T> xy( const Vector3<T>& a) noexcept;

    template <typename T>
    constexpr Vector3<T> xy( const Vector2<T>& a, std::type_identity_t<T> z) noexcept;
    
    YQ_NAN_1(Vector3, Vector3<T>(NAN))
    YQ_ONE_1(Vector3, Vector3<T>(ONE))
    YQ_ZERO_1(Vector3, Vector3<T>(ZERO))
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_NAN_1(Vector3, is_nan(v.x) || is_nan(v.y) || is_nan(v.z))
    YQ_IS_FINITE_1(Vector3, is_finite(v.x) && is_finite(v.y) && is_finite(v.z))
    
    /*! \brief Square of the vector's length
    
        This returns the SQUARE of the given vector's length.
    */
    template <typename T>
    constexpr square_t<T> length²(const Vector3<T>& a) noexcept;
    
    /*! \brief Length of the vector
        
        This returns the length of the given vector.
    */
    template <typename T>
    T       length(const Vector3<T>& a);
        
//  --------------------------------------------------------
//  POSITIVE


//  --------------------------------------------------------
//  NORMALIZATION


//  --------------------------------------------------------
//  ADDITION

    template <typename T>
    constexpr Multivector3<T> operator+(T a, const Vector3<T>& b) noexcept;
    template <typename T>
    std::vector<Vector3<T>>   operator+(std::span<const Vector3<T>>, Vector3<T>);

//  --------------------------------------------------------
//  SUBTRACTION

    template <typename T>
    constexpr Multivector3<T> operator-(T a, const Vector3<T>& b) noexcept;
    template <typename T>
    std::vector<Vector3<T>>   operator-(std::span<const Vector3<T>>, Vector3<T>);

//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires (is_arithmetic_v<T>)
    constexpr Vector3<product_t<T,U>> operator*(T a, const Vector3<U>&b) noexcept;
    
    template <typename T, typename U>
    requires (is_arithmetic_v<T>)
    std::vector<Vector3<product_t<T,U>>>   operator*(T a, std::span<const Vector3<U>>);

    template <typename T, typename U>
    requires (is_arithmetic_v<U>)
    std::vector<Vector3<product_t<T,U>>>   operator*(std::span<const Vector3<T>>, U b);

    template <typename T, typename U>
    std::vector<Vector1<product_t<T,U>>> operator*(std::span<const Vector3<T>>, const Tensor31<U>&);
    template <typename T, typename U>
    std::vector<Vector2<product_t<T,U>>> operator*(std::span<const Vector3<T>>, const Tensor32<U>&);
    template <typename T, typename U>
    std::vector<Vector3<product_t<T,U>>> operator*(std::span<const Vector3<T>>, const Tensor33<U>&);
    template <typename T, typename U>
    std::vector<Vector4<product_t<T,U>>> operator*(std::span<const Vector3<T>>, const Tensor34<U>&);

    template <typename T, typename U>
    constexpr Vector3<product_t<T,U>>    mul_elem(const Vector3<T>&a, const Vector3<U>&b) noexcept
    {
        return a.emul(b);
    }
    
//  --------------------------------------------------------
//  DIVISION

    template <typename T, typename U>
    requires (std::is_arithmetic_v<T>)
    constexpr  Vector3<quotient_t<T,U>> operator/(T a, const  Vector3<U>&b) noexcept;

    template <typename T, typename U>
    requires (is_arithmetic_v<U>)
    std::vector<Vector3<quotient_t<T,U>>>   operator/(std::span<const Vector3<T>>, U b);

    template <typename T, typename U>
    constexpr Vector3<quotient_t<T,U>>    div_elem(const Vector3<T>&a, const Vector3<U>&b) noexcept
    {
        return a.ediv(b);
    }

//  --------------------------------------------------------
//  POWERS

//  --------------------------------------------------------
//  DOT PRODUCT

//  --------------------------------------------------------
//  INNER PRODUCT


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
    constexpr Vector3<T>   abs_elem(const Vector3<T>&a) noexcept;

    template <typename T>
    requires (std::is_floating_point_v<T> && has_sqrt_v<T>)
    Radian              angle(const Vector3<T>&a, const Vector3<T>& b);
    
    template <typename T, typename DIM1, typename DIM2>
    requires (std::is_floating_point_v<T> && has_sqrt_v<T>)
    Radian             angle(const Vector3<MKS<T,DIM1>>&a, const Vector3<MKS<T,DIM2>>& b);

    /*! \brief Counter clockwise (euler) angle
    
        Computes the euler angle of the vector, ie, counter-clockwise from the +X axis.
    */
    template <typename T>
    requires std::is_floating_point_v<T>
    Radian   ccw(const Vector3<T>& a);

    /*! \brief Counter clockwise (euler) angle
    
        Computes the euler angle of the vector, ie, counter-clockwise from the +X axis.
    */
    template <typename T, typename DIM>
    requires std::is_floating_point_v<T>
    Radian   ccw(const Vector3<MKS<T,DIM>>& a);

    /*! \brief Clockwise angle
    
        Computes the angle of the vector from the +Y axis.
    */
    template <typename T>
    requires std::is_floating_point_v<T>
    MKS<T,dim::Angle>   clockwise(const Vector3<T>& a);

    /*! \brief Clockwise angle
    
        Computes the angle of the vector from the +Y axis.
    */
    template <typename T, typename DIM>
    requires std::is_floating_point_v<T>
    MKS<T,dim::Angle>   clockwise(const Vector3<MKS<T,DIM>>& a);
    
    template <typename T>
    constexpr T             component_max(const Vector3<T>&a) noexcept;

    template <typename T>
    constexpr T             component_min(const Vector3<T>&a) noexcept;

    template <typename T>
    constexpr cube_t<T>       component_product(const Vector3<T>& a) noexcept;
    
    template <typename T>
    constexpr T   component_sum(const Vector3<T>& a) noexcept;

    template <typename T, typename R>
    bool is_close(const R& compare, const Vector3<T>& actual, const Vector3<T>& expected);
    
    template <typename T, typename R>
    bool is_close(const R& compare, const Vector3<T>& actual, std::type_identity_t<T> x, std::type_identity_t<T> y, std::type_identity_t<T> z);

    template <typename T>
    constexpr Vector3<T>   max_elem(const Vector3<T>&a, const Vector3<T>&b) noexcept;

    template <typename T>
    constexpr Vector3<T>   max_elem(std::initializer_list<Vector3<T>>) noexcept;
    
    template <typename T>
    constexpr Vector3<T>   max_elem(std::span<const Vector3<T>>) noexcept;

    /*! \brief Mid-way divide two vectors
    */
    template <typename T>
    constexpr Vector3<T>     midvector(const Vector3<T>& a, const Vector3<T>& b=Vector3<T>{}) noexcept;

    template <typename T>
    constexpr Vector3<T>   min_elem(const Vector3<T>&a, const Vector3<T>&b) noexcept;

    template <typename T>
    constexpr Vector3<T>   min_elem(std::initializer_list<Vector3<T>>) noexcept;

    template <typename T>
    constexpr Vector3<T>   min_elem(std::span<const Vector3<T>>) noexcept;


    template <typename T>
    AllComponents<Vector3<T>>   all(Vector3<T>& val);
    
    template <typename T>
    AllComponents<const Vector3<T>>   all(const Vector3<T>& val);

    #if 0
    template <typename T>
    ElemComponents<Vector3<T>>   elem(Vector3<T>& val);
    template <typename T>
    ElemComponents<const Vector3<T>>   elem(const Vector3<T>& val);
    #endif

    template <typename T>
    AnyComponents<Vector3<T>>   any(Vector3<T>& val);

    template <typename T>
    AnyComponents<const Vector3<T>>   any(const Vector3<T>& val);

    template <typename S, typename T>
    S&  as_stream(S& s, const Vector3<T>& v);
    
    template <typename T>
    Stream& operator<<(Stream&s, const Vector3<T>& v);

    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const Vector3<T>& v);

    Vector3I    iround(const Vector3D&);
}

YQ_TYPE_DECLARE(yq::Vector3D)
YQ_TYPE_DECLARE(yq::Vector3F)
YQ_TYPE_DECLARE(yq::Vector3I)
YQ_TYPE_DECLARE(yq::Vector3U)

