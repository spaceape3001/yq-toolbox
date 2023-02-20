////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__VECTOR_4__HPP 1
#include <math/preamble.hpp>

namespace yq {
    
    /*! \brief Vector of 4 dimensions
    
        This is a 4 dimensional cartesian vector of the given type.
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Vector4 {
        //! Component data type argument to this structure (ie, template parameter T)
        using component_type = T;
        
        T       x;
        T       y;
        T       z;
        T       w;
        
        constexpr Vector4() noexcept = default;
        constexpr Vector4(T _x, T _y, T _z, T _w) noexcept : 
            x(_x), y(_y), z(_z), w(_w) {}
        constexpr Vector4(all_t, T v) noexcept : x(v), y(v), z(v), w(v) {}
        template <typename=void> requires has_nan_v<T>
        consteval Vector4(nan_t) noexcept : Vector4(ALL, nan_v<T>) {}
        consteval Vector4(one_t) noexcept : Vector4(ALL, one_v<T>) {}
        consteval Vector4(x_t) noexcept : x(one_v<T>), y(zero_v<T>), z(zero_v<T>), w(zero_v<T>) {}
        constexpr Vector4(x_t, T v) noexcept : x(v), y(zero_v<T>), z(zero_v<T>), w(zero_v<T>) {}
        consteval Vector4(y_t) noexcept : x(zero_v<T>), y(one_v<T>), z(zero_v<T>), w(zero_v<T>) {}
        constexpr Vector4(y_t, T v) noexcept : x(zero_v<T>), y(v), z(zero_v<T>), w(zero_v<T>) {}
        consteval Vector4(z_t) noexcept : x(zero_v<T>), y(zero_v<T>), z(one_v<T>), w(zero_v<T>) {}
        constexpr Vector4(z_t, T v) noexcept : x(zero_v<T>), y(zero_v<T>), z(v), w(zero_v<T>) {}
        consteval Vector4(w_t) noexcept : x(zero_v<T>), y(zero_v<T>), z(zero_v<T>), w(one_v<T>) {}
        constexpr Vector4(w_t, T v) noexcept : x(zero_v<T>), y(zero_v<T>), z(zero_v<T>), w(v) {}
        consteval Vector4(zero_t) noexcept : Vector4(ALL, zero_v<T>) {}

        explicit constexpr Vector4(const Size4<T>&) noexcept;

        template <glm::qualifier Q>
        explicit constexpr Vector4(const glm::vec<4, T, Q>& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
        
        template <typename U>
        requires std::is_nothrow_convertible_v<T,U>
        explicit constexpr operator Vector4<U>() const noexcept
        {
            return { (U) x, (U) y, (U) z, (U) w };
        }
        
        template <typename U>
        requires (std::is_convertible_v<T,U> && !std::is_nothrow_convertible_v<T,U>)
        explicit constexpr operator Vector4<U>() const 
        {
            return { (U) x, (U) y, (U) z, (U) w };
        }
        
        
        /*! \brief Creates a unit-vector in the x-dimension.
        */
        static consteval Vector4 unit_x() noexcept
        {
            return Vector4(X);
        }
        
        /*! \brief Creates a unit-vector in the y-dimension.
        */
        static consteval Vector4 unit_y() noexcept
        {
            return Vector4(Y);
        }
        
        /*! \brief Creates a unit-vector in the z-dimension.
        */
        static consteval Vector4 unit_z() noexcept
        {
            return Vector4(Z);
        }
        
        /*! \brief Creates a unit-vector in the w-dimension.
        */
        static consteval Vector4 unit_w() noexcept
        {
            return Vector4(W);
        }


        //! Equality operator (using default)
        constexpr bool operator==(const Vector4&) const noexcept = default;
        
        //! Affirmation (positive) operator
        constexpr Vector4 operator+() const noexcept
        {
            return *this;
        }

        //! Negation
        constexpr Vector4 operator-() const noexcept;

        //! Normalization
        Vector4<quotient_t<T,T>> operator~() const;

        //! Power (of two)
        constexpr square_t<T> operator^(two_t) const noexcept;

        //! Conversion to GLM library
        constexpr operator glm::vec<4, T, glm::defaultp>() const noexcept;

        //! Explicit conversion operator
        template <typename U>
        requires (std::is_convertible_v<T,U> && !std::is_same_v<T,U>)
        explicit operator Vector4<U>() const
        {
            return Vector4<U>( U(x), U(x), U(z), U(w) );
        }

        //! Addition
        constexpr Vector4 operator+(const Vector4& b) const noexcept;

        constexpr Multivector4<T> operator+(T) const noexcept;

        constexpr AxBox4<T> operator+(const AxBox4<T>&) const noexcept;

        //! Addition with bivector
        constexpr Multivector4<T> operator+(const Bivector4<T>&) const noexcept;
        //! Addition with multivector
        constexpr Multivector4<T> operator+(const Multivector4<T>&) const noexcept;

        Polygon4<T> operator+(const Polygon4<T>&) const;
        Polyline4<T> operator+(const Polyline4<T>&) const;

        //! Addition with quadvector
        constexpr Multivector4<T> operator+(const Quadvector4<T>&) const noexcept;

        constexpr Segment4<T> operator+(const Segment4<T>&) const noexcept;

        constexpr Sphere4<T> operator+(const Sphere4<T>&) const noexcept;

        constexpr Triangle4<T> operator+(const Triangle4<T>&) const noexcept;

        //! Addition with trivector
        constexpr Multivector4<T> operator+(const Trivector4<T>&) const noexcept;
        
        //! Self-addition
        Vector4& operator+=(const Vector4& b) noexcept;

        std::vector<Vector4> operator+(std::span<const Vector4>) const;

        //! Subtraction
        constexpr Vector4 operator-(const Vector4& b) const noexcept;

        //! Addition with scalar
        constexpr Multivector4<T> operator-(T) const noexcept;

        constexpr AxBox4<T> operator-(const AxBox4<T>&) const noexcept;

        //! Addition with bivector
        constexpr Multivector4<T> operator-(const Bivector4<T>&) const noexcept;
        //! Addition with multivector
        constexpr Multivector4<T> operator-(const Multivector4<T>&) const noexcept;

        Polygon4<T> operator-(const Polygon4<T>&) const;
        Polyline4<T> operator-(const Polyline4<T>&) const;

        //! Addition with quadvector
        constexpr Multivector4<T> operator-(const Quadvector4<T>&) const noexcept;


        constexpr Segment4<T> operator-(const Segment4<T>&) const noexcept;

        constexpr Sphere4<T> operator-(const Sphere4<T>&) const noexcept;

        constexpr Triangle4<T> operator-(const Triangle4<T>&) const noexcept;

        //! Addition with trivector
        constexpr Multivector4<T> operator-(const Trivector4<T>&) const noexcept;
        
        //! Self-subtraction
        Vector4& operator-=(const Vector4& b) noexcept;

        std::vector<Vector4> operator-(std::span<const Vector4>) const;

        //! Multiplication with scalar
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Vector4<product_t<T,U>> operator*(U b) const noexcept;

        //! Self-multiplication with scalar
        template <typename U>
        requires (is_arithmetic_v<U> && self_mul_v<T,U>)
        Vector4<T>& operator*=(U b) noexcept;

        //! Multiplication with tensor41
        template <typename U>
        constexpr Vector1<product_t<T,U>> operator*(const Tensor41<U>&b) const noexcept;

        //! Multiplication with tensor42
        template <typename U>
        constexpr Vector2<product_t<T,U>> operator*(const Tensor42<U>&b) const noexcept;

        //! Multiplication with tensor43
        template <typename U>
        constexpr Vector3<product_t<T,U>> operator*(const Tensor43<U>&b) const noexcept;

        //! Multiplication with tensor44
        template <typename U>
        constexpr Vector4<product_t<T,U>> operator*(const Tensor44<U>&b) const noexcept;

        //! Self-multiplication with tensor44
        template <typename U>
        requires self_mul_v<T,U>
        Vector4<T>& operator*=(const Tensor44<U>& b) noexcept;

        //! Geometric product
        template <typename U>
        constexpr Multivector4<product_t<T,U>>   operator*(const Vector4<U>&) const noexcept;


        //! Dot product
        template <typename U>
        constexpr product_t<T,U> operator DOT (const Vector4<U>&b) const noexcept;

        //! Inner product
        template <typename U>
        constexpr product_t<T,U> operator INNER (const Vector4<U>&b) const noexcept;
        
        //! Outer product
        template <typename U>
        constexpr Bivector4<product_t<T,U>> operator OUTER(const Vector4<U>&b) const noexcept;
        
        //! OTIMES product (with vector1)
        template <typename U>
        constexpr Tensor41<product_t<T,U>> operator OTIMES(const Vector1<U>&b) const noexcept;

        //! OTIMES product (with vector2)
        template <typename U>
        constexpr Tensor42<product_t<T,U>> operator OTIMES(const Vector2<U>&b) const noexcept;

        //! OTIMES product (with vector3)
        template <typename U>
        constexpr Tensor43<product_t<T,U>> operator OTIMES(const Vector3<U>&b) const noexcept;

        //! OTIMES product (with vector4)
        template <typename U>
        constexpr Tensor44<product_t<T,U>> operator OTIMES(const Vector4<U>&b) const noexcept;

        //! Division
        template <typename U>
        requires (is_arithmetic_v<U>)
        constexpr  Vector4<quotient_t<T,U>> operator/(U b) const noexcept;
        
        //! Self-division
        template <typename U>
        requires (is_arithmetic_v<U> && self_div_v<T,U>)
        Vector4<T>& operator/=(U b) noexcept;
        
        template <typename U>
        constexpr Multivector4<quotient_t<T,U>>   operator/ (const Vector4<U>&b) const noexcept;

        //! unions with a box
        constexpr AxBox4<T> operator|(const AxBox4<T>&b) const noexcept;

        //! Create a box as a union of two vectors
        constexpr AxBox4<T> operator|(const Vector4&b) const noexcept;

        //! Tests to see if this vector is "close" to the other
        template <typename R=Absolute<T>>
        bool close(const Vector4& expected, const R& compare) const;

        //! Tests to see if this vector is "close" to the other (using length²)
        template <typename R=Absolute<square_t<T>>>
        bool close²(const Vector4& expected, const R& compare) const;

        //! Returns the most positive of the components
        constexpr T             cmax() const noexcept;

        //! Returns the most negative of the components
        constexpr T             cmin() const noexcept;

        //! Returns the product of all components
        constexpr fourth_t<T>   cproduct() const noexcept;

        //! Returns the sum of all components
        constexpr T             csum() const noexcept;

        //! Absolute value of each component
        constexpr Vector4       eabs() const noexcept;

        //! Element by element division
        template <typename U>
        constexpr Vector4<quotient_t<T,U>>  ediv(const Vector4<U>&b) const noexcept;

        //! Maximum applied to each component
        constexpr Vector4   emax(const Vector4&b) const noexcept;
        
        //! Minimum applied to each component
        constexpr Vector4   emin(const Vector4&b) const noexcept;

        //! Element by element multiplication
        template <typename U>
        constexpr Vector4<product_t<T,U>>   emul(const Vector4<U>&b) const noexcept;

        /*! \brief Square of the vector's length
        
            This returns the SQUARE of the given vector's length.
        */
        constexpr square_t<T> length²() const noexcept;

        /*! \brief Length of the vector
            
            This returns the length of the given vector.
        */
        T    length() const;


            //  ===================================================================================================
            //  AllComponents Adapters
            //  ===================================================================================================

        /*! Adds a value to all the elements
        */
        constexpr Vector4 all_add(T b) const noexcept;
        
        //! Decrement all elements
        Vector4&    all_decrement(T b) noexcept;

        //! Increment all elements
        Vector4&    all_increment(T b) noexcept;

        /*! \brief Subtracts value from all elements
        */
        constexpr Vector4 all_subtract(T b) const noexcept;

        /*! Tests every element
            
            This applies the given test to every component, 
            returns TRUE if all tests are true.
            \note y, z, w component tests may be skipped if the x-component test fails.
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool all_test(Pred pred) const noexcept;

        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if all tests are true.
            \note y, z, w component tests may be skipped if the x-component test fails.
            \param[in] b The other vector
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool all_test(const Vector4& b, Pred pred) const noexcept;

        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if all tests are true.
            \note y, z, w component tests may be skipped if the x-component test fails.
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
            \note y, z, w component tests may be skipped if the x-component test passes.
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool any_test(Pred pred) const noexcept;
        
        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if any test is true.
            \note y, z, w component tests may be skipped if the x-component test passes.
            \param[in] b The other vector
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool any_test(const Vector4& b, Pred pred) const noexcept;
        
        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if any test is true.
            \note y, z, w component tests may be skipped if the x-component test passes.
            \param[in] b The other value
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool any_test(T b, Pred pred) const noexcept;

        static bool less_x( const Vector4& a, const Vector4& b) { return a.x < b.x; }
        static bool less_y( const Vector4& a, const Vector4& b) { return a.y < b.y; }
        static bool less_z( const Vector4& a, const Vector4& b) { return a.z < b.z; }
        static bool less_w( const Vector4& a, const Vector4& b) { return a.w < b.w; }
    };
    
    YQ_IEEE754_1(Vector4)
    YQ_INTEGER_1(Vector4)
    YQ_IS_INTEGER_1(Vector4)
    

//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Creates a 4 dimensional vector
    
        Helper function to create a 4 dimensional cartesian vector where the component type is deduced from
        the first argument.
    */
    template <typename T>
    constexpr Vector4<T> vector(T x, std::type_identity_t<T> y, std::type_identity_t<T> z, std::type_identity_t<T> w) noexcept
    {
        return Vector4<T>(x,y,z,w);
    }
    
    template <typename T, glm::qualifier Q>
    constexpr Vector4<T> vector(const glm::vec<4,T,Q>& v) noexcept
    {
        return Vector4<T>( v.x, v.y, v.z, v.w );
    }

    constexpr Vector4D operator "" _x4(unsigned long long int v) noexcept
    {
        return Vector4D(X, (double) v);
    }

    constexpr Vector4D operator "" _x4(long double v) noexcept
    {
        return Vector4D(X, (double) v);
    }

    constexpr Vector4D operator "" _y4(unsigned long long int v) noexcept
    {
        return Vector4D(Y, (double) v);
    }

    constexpr Vector4D operator "" _y4(long double v) noexcept
    {
        return Vector4D(Y, (double) v);
    }

    constexpr Vector4D operator "" _z4(unsigned long long int v) noexcept
    {
        return Vector4D(Z, (double) v);
    }

    constexpr Vector4D operator "" _z4(long double v) noexcept
    {
        return Vector4D(Z, (double) v);
    }

    constexpr Vector4D operator "" _w4(unsigned long long int v) noexcept
    {
        return Vector4D(W, (double) v);
    }

    constexpr Vector4D operator "" _w4(long double v) noexcept
    {
        return Vector4D(W, (double) v);
    }

    YQ_NAN_1(Vector4, Vector4<T>(NAN))
    YQ_ONE_1(Vector4, Vector4<T>(ONE))
    YQ_ZERO_1(Vector4, Vector4<T>(ZERO))
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_NAN_1(Vector4, is_nan(v.x) || is_nan(v.y) || is_nan(v.z) || is_nan(v.w))
    YQ_IS_FINITE_1(Vector4, is_finite(v.x) && is_finite(v.y) && is_finite(v.z) && is_finite(v.w))

    /*! \brief Square of the vector's length
    
        This returns the SQUARE of the given vector's length.
    */
    template <typename T>
    constexpr square_t<T> length²(const Vector4<T>& a) noexcept;

    /*! \brief Length of the vector
        
        This returns the length of the given vector.
    */
    template <typename T>
    auto    length(const Vector4<T>& a);

//  --------------------------------------------------------
//  ADDITION


    template <typename T>
    constexpr Multivector4<T> operator+(T a, const Vector4<T>& b) noexcept;
    template <typename T>
    std::vector<Vector4<T>>   operator+(std::span<Vector4<T>>, Vector4<T>);

//  --------------------------------------------------------
//  SUBTRACTION

    template <typename T>
    constexpr Multivector4<T> operator-(T a, const Vector4<T>& b) noexcept;
    template <typename T>
    std::vector<Vector4<T>>   operator-(std::span<Vector4<T>>, Vector4<T>);

//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires (is_arithmetic_v<T>)
    constexpr Vector4<product_t<T,U>> operator*(T a, const Vector4<U>&b) noexcept;

    template <typename T, typename U>
    requires (is_arithmetic_v<T>)
    std::vector<Vector4<product_t<T,U>>>   operator*(T a, std::span<Vector4<U>>);

    template <typename T, typename U>
    requires (is_arithmetic_v<U>)
    std::vector<Vector4<product_t<T,U>>>   operator*(std::span<Vector4<T>>, U b);

    template <typename T, typename U>
    std::vector<Vector1<product_t<T,U>>> operator*(std::span<const Vector4<T>>, const Tensor41<U>&);
    template <typename T, typename U>
    std::vector<Vector2<product_t<T,U>>> operator*(std::span<const Vector4<T>>, const Tensor42<U>&);
    template <typename T, typename U>
    std::vector<Vector3<product_t<T,U>>> operator*(std::span<const Vector4<T>>, const Tensor43<U>&);
    template <typename T, typename U>
    std::vector<Vector4<product_t<T,U>>> operator*(std::span<const Vector4<T>>, const Tensor44<U>&);

    template <typename T, typename U>
    constexpr Vector4<product_t<T,U>>    mul_elem(const Vector4<T>&a, const Vector4<T>&b) noexcept;
    
//  --------------------------------------------------------
//  DIVISION

    template <typename T, typename U>
    requires (is_arithmetic_v<T>)
    constexpr  Vector4<quotient_t<T,U>> operator/(T a, const  Vector4<U>&b) noexcept;
    
    template <typename T, typename U>
    requires (is_arithmetic_v<U>)
    std::vector<Vector4<quotient_t<T,U>>>   operator/(std::span<Vector4<T>>, U b);

    template <typename T, typename U>
    constexpr Vector4<quotient_t<T,U>>    div_elem(const Vector4<T>&a, const Vector4<U>&b) noexcept;


//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

    template <typename T>
    constexpr Vector4<T>   abs_elem(const Vector4<T>&a) noexcept;


    template <typename T>
    requires (std::is_floating_point_v<T> && has_sqrt_v<T>)
    Radian       angle(const Vector4<T>&a, const Vector4<T>& b);
    
    template <typename T, typename DIM1, typename DIM2>
    requires (std::is_floating_point_v<T> && has_sqrt_v<T>)
    Radian       angle(const Vector4<MKS<T,DIM1>>&a, const Vector4<MKS<T,DIM2>>& b);

    template <typename T>
    constexpr T             component_max(const Vector4<T>&a) noexcept;

    template <typename T>
    constexpr T             component_min(const Vector4<T>&a) noexcept;

    template <typename T>
    constexpr fourth_t<T>     component_product(const Vector4<T>& a) noexcept;

    template <typename T>
    constexpr T   component_sum(const Vector4<T>& a) noexcept;

    template <typename T, typename R>
    bool is_close(const R& compare, const Vector4<T>& actual, const Vector4<T>& expected);
    
    template <typename T, typename R>
    bool is_close(const R& compare, const Vector4<T>& actual, std::type_identity_t<T> x, std::type_identity_t<T> y, std::type_identity_t<T> z,std::type_identity_t<T>w);

    template <typename T>
    constexpr Vector4<T>   max_elem(const Vector4<T>&a, const Vector4<T>&b) noexcept;
    
    template <typename T>
    constexpr Vector4<T>   max_elem(std::initializer_list<Vector4<T>>) noexcept;
    
    template <typename T>
    constexpr Vector4<T>   max_elem(std::span<const Vector4<T>>) noexcept;


    /*! \brief Mid-way divide two vectors
    */
    template <typename T>
    constexpr Vector4<T>    midvector(const Vector4<T>& a, const Vector4<T>& b=Vector4<T>{}) noexcept;

    template <typename T>
    constexpr Vector4<T>   min_elem(const Vector4<T>&a, const Vector4<T>&b) noexcept;

    template <typename T>
    constexpr Vector4<T>   min_elem(std::initializer_list<Vector4<T>>) noexcept;

    template <typename T>
    constexpr Vector4<T>   min_elem(std::span<const Vector4<T>>) noexcept;

    //! All components adapter
    //! Use this to activate the "all" component adapters in vector4
    template <typename T>
    AllComponents<Vector4<T>>   all(Vector4<T>& val);

    //! All components adapter
    //! Use this to activate the "all" component adapters in vector4
    template <typename T>
    AllComponents<const Vector4<T>>   all(const Vector4<T>& val);
    
    #if 0
    template <typename T>
    ElemComponents<Vector4<T>>   elem(Vector4<T>& val);

    template <typename T>
    ElemComponents<const Vector4<T>>   elem(const Vector4<T>& val);
    #endif

    template <typename T>
    AnyComponents<Vector4<T>>   any(Vector4<T>& val);

    template <typename T>
    AnyComponents<const Vector4<T>>   any(const Vector4<T>& val);

    template <typename S, typename T>
    S&  as_stream(S& s, const Vector4<T>& v);
    
    template <typename T>
    Stream& operator<<(Stream&s, const Vector4<T>& v);

    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const Vector4<T>& v);
}

YQ_TYPE_DECLARE(yq::Vector4D)
YQ_TYPE_DECLARE(yq::Vector4F)
YQ_TYPE_DECLARE(yq::Vector4I)
YQ_TYPE_DECLARE(yq::Vector4U)

