////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__VECTOR_3__HPP 1
#include <math/preamble.hpp>
#include <math/Absolute.hpp>
#include <math/Units.hpp>
#include <math/trig.hpp>
#include <math/AllComponents.hpp>
#include <math/AnyComponents.hpp>

namespace yq {

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
        constexpr Vector3(all_t, T v) noexcept : x(v), y(v), z(v) {}
        constexpr Vector3(ordered_t, T _x, T _y, T _z) noexcept : x(_x), y(_y), z(_z) {}
        consteval Vector3(x_t) noexcept : x(one_v<T>), y(zero_v<T>), z(zero_v<T>) {}
        constexpr Vector3(x_t, T v) noexcept : x(v), y(zero_v<T>), z(zero_v<T>) {}
        consteval Vector3(y_t) noexcept : x(zero_v<T>), y(one_v<T>), z(zero_v<T>) {}
        constexpr Vector3(y_t, T v) noexcept : x(zero_v<T>), y(v), z(zero_v<T>) {}
        consteval Vector3(z_t) noexcept : x(zero_v<T>), y(zero_v<T>), z(one_v<T>) {}
        constexpr Vector3(z_t, T v) noexcept : x(zero_v<T>), y(zero_v<T>), z(v) {}
        consteval Vector3(zero_t) noexcept : Vector3(all_, zero_v<T>) {}

        template <glm::qualifier Q>
        explicit constexpr Vector3(const glm::vec<3, T, Q>& v) : x(v.x), y(v.y), z(v.z) {}

        /*! \brief Creates a unit-vector in the x-dimension.
        */
        static consteval Vector3 unit_x() noexcept
        {
            return Vector3(x_);
        }
        
        /*! \brief Creates a unit-vector in the y-dimension.
        */
        static consteval Vector3 unit_y() noexcept
        {
            return Vector3(y_);
        }
        
        /*! \brief Creates a unit-vector in the z-dimension.
        */
        static consteval Vector3 unit_z() noexcept
        {
            return Vector3(z_);
        }

        //! Equality operator (using default)
        constexpr bool operator==(const Vector3&) const noexcept = default;

        constexpr operator glm::vec<3, T, glm::defaultp>() const noexcept;

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
        
        //! Addition with bivector
        constexpr Multivector3<T> operator+(const Bivector3<T>& b) const noexcept;
        
        //! Addition with multivector
        constexpr Multivector3<T> operator+(const Multivector3<T>& b) const noexcept;

        //! Addition with trivector
        constexpr Multivector3<T> operator+(const Trivector3<T>& b) const noexcept;

        //! Addition
        constexpr Vector3 operator+(const Vector3& b) const noexcept;

        //! Self-addition
        Vector3& operator+=(const Vector3& b) noexcept;
        
        //! Subtraction with number
        constexpr Multivector3<T> operator-(T b) const noexcept;
        
        //! Subtraction with bivector
        constexpr Multivector3<T> operator-(const Bivector3<T>& b) const noexcept;
        
        //! Subtraction with multivector
        constexpr Multivector3<T> operator-(const Multivector3<T>& b) const noexcept;

        //! Subtraction with trivector
        constexpr Multivector3<T> operator-(const Trivector3<T>& b) const noexcept;

        //! Subtraction
        constexpr Vector3 operator-(const Vector3& b) const noexcept;

        //! Self-subtraction
        Vector3& operator-=(const Vector3& b) noexcept;

        //! Multiplication with scalar
        template <typename U>
        requires (trait::is_arithmetic_v<U>)
        constexpr Vector3<product_t<T,U>> operator*(U b) const noexcept;

        //! Self-multiplication
        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
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
        requires (trait::self_mul_v<T,U>)
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
        requires (std::is_arithmetic_v<U> && trait::self_div_v<T,U>)
        Vector3<T>& operator/=(U b) noexcept;

        template <typename R>
        bool close(const Vector3& expected, const R& compare) const
        {
            return compare(length(*this-expected), length(expected));
        }

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

            //  ===================================================================================================
            //  AllComponents Adapters
            //  ===================================================================================================

        /*! Adds a value to all the elements
        */
        constexpr Vector3 all_add(T b) const noexcept;
        
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
        constexpr bool all_test(Pred pred) const noexcept
        {
            return pred(x) && pred(y) && pred(z);
        }

        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if all tests are true.
            \note y & z component tests may be skipped if the x-component test fails.
            \param[in] b The other vector
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool all_test(const Vector3& b, Pred pred) const noexcept
        {
            return pred(x, b.x) && pred(y, b.y) && pred(z, b.z);
        }

        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if all tests are true.
            \note y & z component tests may be skipped if the x-component test fails.
            \param[in] b The other value
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool all_test(T b, Pred pred) const noexcept
        {
            return pred(x, b) && pred(y, b) && pred(z, b);
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
            \note y & z component tests may be skipped if the x-component test passes.
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool any_test(Pred pred) const noexcept
        {
            return pred(x) || pred(y) || pred(z);
        }
        
        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if any test is true.
            \note y & z component tests may be skipped if the x-component test passes.
            \param[in] b The other vector
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool any_test(const Vector3& b, Pred pred) const noexcept
        {
            return pred(x, b.x) || pred(y, b.y) || pred(z, b.z);
        }
        
        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if any test is true.
            \note y & z component tests may be skipped if the x-component test passes.
            \param[in] b The other value
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool any_test(T b, Pred pred) const noexcept
        {
            return pred(x, b) || pred(y, b) || pred(z, b);
        }

    };

    YQ_IEEE754_1(Vector3)
    
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
    
    template <typename T, glm::qualifier Q>
    constexpr Vector3<T> vector(const glm::vec<3,T,Q>& v) noexcept
    {
        return Vector3<T>( v.x, v.y, v.z );
    }

    constexpr Vector3D operator "" _x3(unsigned long long int v) noexcept
    {
        return Vector3D(x_, (double) v);
    }

    constexpr Vector3D operator "" _x3(long double v) noexcept
    {
        return Vector3D(x_, (double) v);
    }

    constexpr Vector3D operator "" _y3(unsigned long long int v) noexcept
    {
        return Vector3D(y_, (double) v);
    }

    constexpr Vector3D operator "" _y3(long double v) noexcept
    {
        return Vector3D(y_, (double) v);
    }

    constexpr Vector3D operator "" _z3(unsigned long long int v) noexcept
    {
        return Vector3D(z_, (double) v);
    }

    constexpr Vector3D operator "" _z3(long double v) noexcept
    {
        return Vector3D(z_, (double) v);
    }



    //! Creates a three dimension unit vector
    //!
    //! \param az   Counter-clockwise angle from +x
    //! \param el   Elevation (up) angle from x-y plane
    inline  Vector3D    ccw(Radian az, Radian el)
    {
        double  c  = cos(el);
        return Vector3D( c*cos(az), c*sin(az), sin(el) );
    }


    //! Creates a three dimension unit vector
    //!
    //! \param az   Clockwise angle from +x
    //! \param el   Elevation (up) angle from x-y plane
    inline Vector3D     clockwise(Radian az, Radian el)
    {
        double  c  = cos(el);
        return Vector3D(  c*sin(az), c*cos(az), sin(el) );
    }

    template <typename T>
    constexpr Vector2<T> xy( const Vector3<T>& a) noexcept
    {
        return Vector2<T>( a.x, a.y );
    }

    template <typename T>
    constexpr Vector3<T> xy( const Vector2<T>& a, std::type_identity_t<T> z) noexcept
    {
        return Vector3<T>( a.x, a.y, z );
    }
    
    YQ_NAN_1(Vector3, Vector3<T>{nan_v<T>, nan_v<T>, nan_v<T>})
    YQ_ONE_1(Vector3, Vector3<T>{one_v<T>, one_v<T>, one_v<T>})
    YQ_ZERO_1(Vector3, Vector3<T>{zero_v<T>, zero_v<T>, zero_v<T>})
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_NAN_1(Vector3, is_nan(v.x) || is_nan(v.y) || is_nan(v.z))
    YQ_IS_FINITE_1(Vector3, is_finite(v.x) && is_finite(v.y) && is_finite(v.z))
    
    /*! \brief Square of the vector's length
    
        This returns the SQUARE of the given vector's length.
    */
    template <typename T>
    constexpr square_t<T> length²(const Vector3<T>& a) noexcept
    {
        return a.length²();
    }    
    
    /*! \brief Length of the vector
        
        This returns the length of the given vector.
    */
    template <typename T>
    T       length(const Vector3<T>& a)
    {
        return a.length();
    }
        
//  --------------------------------------------------------
//  POSITIVE


//  --------------------------------------------------------
//  NORMALIZATION


//  --------------------------------------------------------
//  ADDITION


//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires (trait::is_arithmetic_v<T>)
    constexpr Vector3<product_t<T,U>> operator*(T a, const Vector3<U>&b) noexcept
    {
        return Vector3<product_t<T,U>>(a*b.x, a*b.y, a*b.z);
    }

    
    template <typename T, typename U>
    constexpr Vector3<product_t<T,U>>    mul_elem(const Vector3<T>&a, const Vector3<U>&b) noexcept
    {
        return a.emul(b);
    }
    
//  --------------------------------------------------------
//  DIVISION

    template <typename T, typename U>
    requires (std::is_arithmetic_v<T>)
    constexpr  Vector3<quotient_t<T,U>> operator/(T a, const  Vector3<U>&b) noexcept
    {
        return (a*b) / b.length²();
    }


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
    requires (std::is_floating_point_v<T> && trait::has_sqrt_v<T>)
    Radian              angle(const Vector3<T>&a, const Vector3<T>& b);
    
    template <typename T, typename DIM1, typename DIM2>
    requires (std::is_floating_point_v<T> && trait::has_sqrt_v<T>)
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
    constexpr Vector3<T>   min_elem(const Vector3<T>&a, const Vector3<T>&b) noexcept;

    /*! \brief Mid-way divide two vectors
    */
    template <typename T>
    constexpr Vector3<T>     midvector(const Vector3<T>& a, const Vector3<T>& b=Vector3<T>{}) noexcept;

    template <typename T>
    AllComponents<Vector3<T>>   all(const Vector3<T>& val)
    {
        return AllComponents<Vector3<T>>(val);
    }
    
    template <typename T>
    AllComponents<Vector3<T>>   elem(const Vector3<T>& val)
    {
        return AllComponents<Vector3<T>>(val);
    }

    template <typename T>
    AnyComponents<Vector3<T>>   any(const Vector3<T>& val)
    {
        return AnyComponents<Vector3<T>>(val);
    }
}

YQ_TYPE_DECLARE(yq::Vector3D)
YQ_TYPE_DECLARE(yq::Vector3F)
YQ_TYPE_DECLARE(yq::Vector3I)
YQ_TYPE_DECLARE(yq::Vector3U)

