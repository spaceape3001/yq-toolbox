////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__VECTOR_2__HPP 1

#include <math/preamble.hpp>
#include <math/Absolute.hpp>
#include <math/AllComponents.hpp>
#include <math/AnyComponents.hpp>

namespace yq {

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
        constexpr Vector2(all_t, T v) noexcept : x(v), y(v) {}
        template <typename=void> requires trait::has_nan_v<T>
        consteval Vector2(nan_t) noexcept : Vector2(ALL, nan_v<T>) {}
        consteval Vector2(one_t) noexcept : Vector2(ALL, one_v<T>) {}
        consteval Vector2(x_t) noexcept : x(one_v<T>), y(zero_v<T>) {}
        constexpr Vector2(x_t, T v) noexcept : x(v), y(zero_v<T>) {}
        consteval Vector2(y_t) noexcept : x(zero_v<T>), y(one_v<T>) {}
        constexpr Vector2(y_t, T v) noexcept : x(zero_v<T>), y(v) {}
        consteval Vector2(zero_t) noexcept : Vector2(ALL, zero_v<T>) {}
        
        
        template <glm::qualifier Q>
        explicit constexpr Vector2(const glm::vec<2, T, Q>& v) : x(v.x), y(v.y) {}

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

        //! Equality operator (using default)
        constexpr bool operator==(const Vector2&) const noexcept = default;

        constexpr operator glm::vec<2, T, glm::defaultp>() const noexcept;

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
        Vector2<trait::quotient_t<T,T>> operator~() const;

        //! Squares the vector (ie, length square)
        constexpr trait::square_t<T> operator^(two_t) const noexcept;

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

        constexpr Segment2<T> operator+(const Segment2<T>&) const noexcept;
        
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

        constexpr Segment2<T> operator-(const Segment2<T>&) const noexcept;

        constexpr Triangle2<T> operator-(const Triangle2<T>&) const noexcept;

        //! Subtraction
        constexpr Vector2 operator-(const Vector2& b) const noexcept;
        std::vector<Vector2<T>> operator-(std::span<const Vector2>) const;

        //! Self-subtraction
        Vector2& operator-=(const Vector2& b) noexcept;

        //! Multiplication (scalar)
        template <typename U>
        requires (trait::is_arithmetic_v<U>)
        constexpr Vector2<trait::product_t<T,U>> operator*(U b) const noexcept;

        //! Self-multiplication
        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
        Vector2<T>& operator*=(U b) noexcept;
        
        template <typename U>
        constexpr Vector1<trait::product_t<T,U>> operator*(const Tensor21<U>&) const noexcept;
        template <typename U>
        constexpr Vector2<trait::product_t<T,U>> operator*(const Tensor22<U>&) const noexcept;
        template <typename U>
        constexpr Vector3<trait::product_t<T,U>> operator*(const Tensor23<U>&) const noexcept;
        template <typename U>
        constexpr Vector4<trait::product_t<T,U>> operator*(const Tensor24<U>&) const noexcept;
        
        template <typename U>
        requires trait::self_mul_v<T,U>
        Vector2&  operator*=(const Tensor22<U>&) noexcept;

        //! Geometric product
        template <typename U>
        constexpr Multivector2<trait::product_t<T,U>> operator*(const Vector2<U>&) const noexcept;

        //! Dot product
        template <typename U>
        constexpr trait::product_t<T,U> operator DOT (const Vector2<U>&b) const noexcept;

        //! Inner product
        template <typename U>
        constexpr trait::product_t<T,U> operator INNER (const Vector2<U>&b) const noexcept;

        //! Cross product
        template <typename U>
        constexpr trait::product_t<T,U> operator CROSS (const Vector2<U>&b) const noexcept;

        template <typename U>
        constexpr Bivector2<trait::product_t<T,U>> operator OUTER (const Vector2<U>& b) const noexcept;

        //! OTIMES Vector1
        template <typename U>
        constexpr Tensor21<trait::product_t<T,U>> operator OTIMES(const Vector1<U>&b) const noexcept;
        //! OTIMES Vector2
        template <typename U>
        constexpr Tensor22<trait::product_t<T,U>> operator OTIMES(const Vector2<U>&b) const noexcept;
        //! OTIMES Vector3
        template <typename U>
        constexpr Tensor23<trait::product_t<T,U>> operator OTIMES(const Vector3<U>&b) const noexcept;
        //! OTIMES Vector4
        template <typename U>
        constexpr Tensor24<trait::product_t<T,U>> operator OTIMES(const Vector4<U>&b) const noexcept;

        //! Division
        template <typename U>
        requires (trait::is_arithmetic_v<U>)
        constexpr  Vector2<trait::quotient_t<T,U>> operator/(U b) const noexcept;

        //! Self-division
        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_div_v<T,U>)
        Vector2<T>& operator/=(U b) noexcept;
        
        template <typename U>
        constexpr Multivector2<trait::quotient_t<T,U>>   operator/ (const Vector2<U>&b) const noexcept;

        //! Union
        constexpr AxBox2<T> operator|(const AxBox2<T>&b) const noexcept;

        //! Create a box as a union of two vectors
        constexpr AxBox2<T> operator|(const Vector2&b) const noexcept;

        //! TRUE if the second vector is CLOSE to this vector, as defined by the comparison operator
        template <typename R=Absolute>
        bool close(const Vector2&b, R compare) const 
        {
            return compare((*this-b).length(), b.length());
        }

        //! Returns the most positive component (as defined by the max function)
        constexpr T     cmax() const noexcept;

        //! Returns the most negative component (as defined by the min function)
        constexpr T     cmin() const noexcept;
    
        //! Returns the product of the components
        constexpr trait::square_t<T>     cproduct() const noexcept;

        //! Returns the sum of the components
        constexpr T   csum() const noexcept;

        //! Element by element absolute value
        constexpr Vector2   eabs() const noexcept;

        //! Element by element division
        template <typename U>
        constexpr Vector2<trait::quotient_t<T,U>>    ediv(const Vector2<U>&b) const noexcept;

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
        constexpr Vector2<trait::product_t<T,U>>    emul(const Vector2<U>&b) const noexcept;

        /*! \brief Square of the vector's length
        
            This returns the SQUARE of this vector's length.
        */
        constexpr trait::square_t<T> length²() const noexcept;
        
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
        constexpr bool all_test(Pred pred) const noexcept
        {
            return pred(x) && pred(y);
        }

        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if all tests are true.
            \note y test may be skipped if the x-component test fails.
            \param[in] b The other vector
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool all_test(const Vector2& b, Pred pred) const noexcept
        {
            return pred(x, b.x) && pred(y, b.y);
        }

        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if all tests are true.
            \note y test may be skipped if the x-component test fails.
            \param[in] b The other value
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool all_test(T b, Pred pred) const noexcept
        {
            return pred(x, b) && pred(y, b);
        }


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
        constexpr bool any_test(Pred pred) const noexcept
        {
            return pred(x) || pred(y);
        }
        
        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if any test is true.
            \note y component test may be skipped if the x-component test passes.
            \param[in] b The other vector
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool any_test(const Vector2& b, Pred pred) const noexcept
        {
            return pred(x, b.x) || pred(y, b.y);
        }
        
        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if any test is true.
            \note y component test may be skipped if the x-component test passes.
            \param[in] b The other value
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool any_test(T b, Pred pred) const noexcept
        {
            return pred(x, b) || pred(y, b);
        }
        
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
    
    template <typename T, glm::qualifier Q>
    constexpr Vector2<T> vector(const glm::vec<2,T,Q>& v) noexcept
    {
        return Vector2<T>( v.x, v.y );
    }

    constexpr Vector2D operator "" _x2(unsigned long long int v) noexcept
    {
        return Vector2D(X, (double) v);
    }

    constexpr Vector2D operator "" _x2(long double v) noexcept
    {
        return Vector2D(X, (double) v);
    }

    constexpr Vector2D operator "" _y2(unsigned long long int v) noexcept
    {
        return Vector2D(Y, (double) v);
    }

    constexpr Vector2D operator "" _y2(long double v) noexcept
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
    constexpr trait::square_t<T> length²(const Vector2<T>& vec) noexcept;

    /*! \brief Length of the vector
        
        This returns the length of the given vector.
    */
    template <typename T>
    requires trait::has_sqrt_v<T>
    auto    length(const Vector2<T>& a);

//  --------------------------------------------------------
//  ADDITION

    //! Adds scalar with vector
    template <typename T>
    constexpr Multivector2<T> operator+(T a, const Vector2<T>& b) noexcept;
    template <typename T>
    std::vector<Vector2<T>>   operator+(std::span<Vector2<T>>, Vector2<T>);

//  --------------------------------------------------------
//  SUBTRACTION

    template <typename T>
    constexpr Multivector2<T> operator-(T a, const Vector2<T>& b) noexcept;
    template <typename T>
    std::vector<Vector2<T>>   operator-(std::span<Vector2<T>>, Vector2<T>);


//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires (trait::is_arithmetic_v<T>)
    constexpr Vector2<trait::product_t<T,U>> operator*(T a, const Vector2<U>&b) noexcept;

    template <typename T, typename U>
    std::vector<Vector1<trait::product_t<T,U>>> operator*(std::span<const Vector2<T>>, const Tensor21<U>&);
    template <typename T, typename U>
    std::vector<Vector2<trait::product_t<T,U>>> operator*(std::span<const Vector2<T>>, const Tensor22<U>&);
    template <typename T, typename U>
    std::vector<Vector3<trait::product_t<T,U>>> operator*(std::span<const Vector2<T>>, const Tensor23<U>&);
    template <typename T, typename U>
    std::vector<Vector4<trait::product_t<T,U>>> operator*(std::span<const Vector2<T>>, const Tensor24<U>&);

    template <typename T, typename U>
    constexpr Vector2<trait::product_t<T,U>>    mul_elem(const Vector2<T>&a, const Vector2<U>&b) noexcept;

//  --------------------------------------------------------
//  DIVISION

    template <typename T, typename U>
    requires (trait::is_arithmetic_v<T>)
    constexpr  Vector2<trait::quotient_t<T,U>> operator/(T a, const  Vector2<U>&b) noexcept;


    template <typename T, typename U>
    constexpr Vector2<trait::quotient_t<T,U>>    div_elem(const Vector2<T>&a, const Vector2<U>&b) noexcept;


//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

    template <typename T>
    constexpr Vector2<T>   abs_elem(const Vector2<T>&a) noexcept;

    template <typename T>
    requires (std::is_floating_point_v<T> && trait::has_sqrt_v<T>)
    Radian       angle(const Vector2<T>&a, const Vector2<T>& b);


    template <typename T, typename DIM1, typename DIM2>
    requires (std::is_floating_point_v<T> && trait::has_sqrt_v<T>)
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
    constexpr trait::square_t<T>     component_product(const Vector2<T>& a) noexcept;

    template <typename T>
    constexpr T   component_sum(const Vector2<T>& a) noexcept;

    /*! \brief "Delta Area"
    
        This is a building block for triangle & polygon area code, computes the "delta area" between two points
        (almost the same as area(aabb(a,b)) but can be negative.)
    */
    template <typename T>
    constexpr trait::square_t<T>    delta_area(const Vector2<T>&a, const Vector2<T>& b) noexcept;

    /*! \brief "Point area" of the points
    
        This is a helper to area and other functions, 
        simply does an "area" of the point deltas, 
        no sign correction, no scaling.
    */
    template <typename T>
    constexpr trait::square_t<T>    delta_area(const std::span<Vector2<T>>& vertex) noexcept;


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
    AllComponents<Vector2<T>>   all(const Vector2<T>& val)
    {
        return { val };
    }
    
    template <typename T>
    AllComponents<Vector2<T>>   elem(const Vector2<T>& val)
    {
        return { val };
    }

    template <typename T>
    AnyComponents<Vector2<T>>   any(const Vector2<T>& val)
    {
        return { val };
    }
    

}

YQ_TYPE_DECLARE(yq::Vector2D)
YQ_TYPE_DECLARE(yq::Vector2F)
YQ_TYPE_DECLARE(yq::Vector2I)
YQ_TYPE_DECLARE(yq::Vector2U)

