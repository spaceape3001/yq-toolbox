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
#include <math/Vector2.hpp>

namespace yq {
    /*! \brief Vector of 3 dimensions
    
        This is a 3 dimensional cartesian vector of the given type.
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Vector3 {
        //! Component data type argument to this structure (ie, template parameter T)
        using component_type = T;

        /*! \brief Creates a unit-vector in the x-dimension.
        */
        static consteval Vector3 unit_x() noexcept;
        /*! \brief Creates a unit-vector in the y-dimension.
        */
        static consteval Vector3 unit_y() noexcept;
        /*! \brief Creates a unit-vector in the z-dimension.
        */
        static consteval Vector3 unit_z() noexcept;

        T       x;
        T       y;
        T       z;
        
        //! Equality operator (using default)
        constexpr bool operator==(const Vector3&) const noexcept = default;

        constexpr operator glm::vec<3, T, glm::defaultp>() const noexcept
        {
            return { x, y, z };
        }

        //! Affirmation
        constexpr Vector3 operator+() const noexcept
        {
            return *this;
        }

        //! Negation
        constexpr Vector3 operator-() const noexcept
        {
            return {-x,-y,-z};
        }

        //! Normalizations operator
        Vector3<quotient_t<T,T>> operator~() const
        {
            auto l = one_v<T>/length();
            return {x/l, y/l, z/l};
        }

        constexpr Vector3 operator+(const Vector3& b) const noexcept
        {
            return {x+b.x, y+b.y, z+b.z};
        }

        Vector3& operator+=(const Vector3& b) noexcept
        {
            x += b.x;
            y += b.y;
            z += b.z;
            return *this;
        }
        
        constexpr Vector3 operator-(const Vector3& b) const noexcept
        {
            return {x-b.x, y-b.y, z-b.z};
        }

        Vector3& operator-=(const Vector3& b) noexcept
        {
            x -= b.x;
            y -= b.y;
            z -= b.z;
            return *this;
        }

        //! TRUE if every component of a is less than b
        constexpr bool operator<<(const Vector3& b) const noexcept
        {
            return (x<b.x) && (y<b.y) && (z<b.z);
        }


        //! TRUE if every component of a is less than (or equal to) b
        constexpr bool operator<<=(const Vector3& b) const noexcept
        {
            return (x<=b.x) && (y<=b.y) && (z<=b.z);
        }

        //! TRUE if every component of a is greater than b
        constexpr bool operator>>(const Vector3& b) const noexcept
        {
            return (x>b.x) && (y>b.y) && (z>b.z);
        }


        //! TRUE if every component of a is greater or equal to b
        constexpr bool operator>>=(const Vector3& b) const noexcept
        {
            return (x>=b.x) && (y>=b.y) && (z>=b.z);
        }

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
            return pred(x, b.x) && pred(y, b.y) && pred(z, b.z);
        }

        
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
            return pred(x, b.x) || pred(y, b.y) || pred(z, b.z);
        }

            
        template <typename R>
        bool close(const Vector3& expected, const R& compare) const
        {
            return compare(length(*this-expected), length(expected));
        }

        //! Most positive component of the vector
        constexpr T cmax() const noexcept
        {
            return max(max(x, y), z);
        }

        //! Most negative component of the vector
        constexpr T cmin() const noexcept
        {
            return min(min(x, y), z);
        }

        //! Product of the vector's components
        constexpr cube_t<T>     cproduct() const noexcept
        {
            return x*y*z;
        }
        
        //! Sum of the vector's components
        constexpr T   csum() const noexcept
        {
            return x + y + z;
        }
        
        //! Absolute value of each component
        constexpr Vector3   eabs() const noexcept
        {
            return { abs(x), abs(y), abs(z) };
        }

        //! Element by element division
        template <typename U>
        constexpr Vector3<quotient_t<T,U>>    ediv(const Vector3&b) const noexcept
        {
            return {x/b.x, y/b.y, z/b.z};
        }

        constexpr Vector3   emax(const Vector3&b) const noexcept
        {
            return {max(x, b.x) && max(y, b.y) && max(z, b.z)};
        }

        constexpr Vector3   emin(const Vector3&b) const noexcept
        {
            return {min(x, b.x) && min(y, b.y) && min(z, b.z)};
        }    

        //! Element by element multiplication
        template <typename U>
        constexpr Vector3<product_t<T,U>>    emul(const Vector3&b) const noexcept
        {
            return {x*b.x, y*b.y, z*b.z};
        }
 
        /*! \brief Square of the vector's length
        
            This returns the SQUARE of the given vector's length.
        */
        constexpr square_t<T> length²() const noexcept
        {
            return x*x + y*y + z*z;
        }    
        
        /*! \brief Length of the vector
            
            This returns the length of this vector.
        */
        T       length() const
        {
            if constexpr (trait::has_sqrt_v<square_t<T>>)
                return sqrt(length²());
            return {};
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
        return {x,y,z};
    }
    
    template <typename T, glm::qualifier Q>
    constexpr Vector3<T> vector(const glm::vec<3,T,Q>& v) noexcept
    {
        return { v.x, v.y, v.z };
    }

    template <typename T>
    consteval Vector3<T> Vector3<T>::unit_x() noexcept
    {
        return {one_v<T>,zero_v<T>,zero_v<T>};
    }

    template <typename T>
    consteval Vector3<T> Vector3<T>::unit_y() noexcept
    {
        return {zero_v<T>,one_v<T>,zero_v<T>};
    }

    template <typename T>
    consteval Vector3<T> Vector3<T>::unit_z() noexcept
    {
        return {zero_v<T>,zero_v<T>,one_v<T>};
    }

    constexpr Vector3D operator "" _x3(unsigned long long int v) noexcept
    {
        return {(double) v, 0., 0.};
    }

    constexpr Vector3D operator "" _x3(long double v) noexcept
    {
        return {(double) v, 0., 0.};
    }

    constexpr Vector3D operator "" _y3(unsigned long long int v) noexcept
    {
        return {0., (double) v, 0.};
    }

    constexpr Vector3D operator "" _y3(long double v) noexcept
    {
        return {0., (double) v, 0.};
    }

    constexpr Vector3D operator "" _z3(unsigned long long int v) noexcept
    {
        return {0., 0., (double) v};
    }

    constexpr Vector3D operator "" _z3(long double v) noexcept
    {
        return {0., 0., (double) v};
    }

    template <typename T>
    constexpr Vector3<T> Vector2<T>::z(T _z) const noexcept
    {
        return { x, y, _z };
    }


    //! Creates a three dimension unit vector
    //!
    //! \param az   Counter-clockwise angle from +x
    //! \param el   Elevation (up) angle from x-y plane
    inline  Vector3D    ccw(Radian az, Radian el)
    {
        double  c  = cos(el);
        return { c*cos(az), c*sin(az), sin(el) };
    }


    //! Creates a three dimension unit vector
    //!
    //! \param az   Clockwise angle from +x
    //! \param el   Elevation (up) angle from x-y plane
    inline Vector3D     clockwise(Radian az, Radian el)
    {
        double  c  = cos(el);
        return { c*sin(az), c*cos(az), sin(el) };
    }

    template <typename T>
    constexpr Vector2<T> xy( const Vector3<T>& a) noexcept
    {
        return { a.x, a.y };
    }

    template <typename T>
    constexpr Vector3<T> xy( const Vector2<T>& a, std::type_identity_t<T> z) noexcept
    {
        return { a.x, a.y, z };
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
    requires (std::is_arithmetic_v<T>)
    constexpr Vector3<product_t<T,U>> operator*(T a, const Vector3<U>&b) noexcept
    {
        return {a*b.x, a*b.y, a*b.z};
    }

    template <typename T, typename U>
    requires (std::is_arithmetic_v<U>)
    constexpr Vector3<product_t<T,U>> operator*(const Vector3<T>& a, U b) noexcept
    {
        return {a.x*b, a.y*b, a.z*b};
    }

    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Vector3<T>& operator*=(Vector3<T>& a, T b) noexcept
    {
        a.x *= b;
        a.y *= b;
        a.z *= b;
        return a;
    }
    
    template <typename T, typename U>
    constexpr Vector3<product_t<T,U>>    mul_elem(const Vector3<T>&a, const Vector3<T>&b) noexcept
    {
        return a.emul(b);
    }
    
//  --------------------------------------------------------
//  DIVISION

    template <typename T, typename U>
    requires (std::is_arithmetic_v<T>)
    constexpr  Vector3<quotient_t<T,U>> operator/(T a, const  Vector3<U>&b) noexcept
    {
        return (a*b) / length2(b);
    }

    template <typename T, typename U>
    requires (std::is_arithmetic_v<U>)
    constexpr  Vector3<quotient_t<T,U>> operator/(const  Vector3<T>& a, U b) noexcept
    {
        return {a.x / b, a.y / b, a.z / b};
    }

    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Vector3<T>& operator/=(Vector3<T>& a, U b) noexcept
    {
        a.x /= b;
        a.y /= b;
        a.z /= b;
        return a;
    }


    template <typename T, typename U>
    constexpr Vector3<quotient_t<T,U>>    div_elem(const Vector3<T>&a, const Vector3<T>&b) noexcept
    {
        return a.ediv(b);
    }

//  --------------------------------------------------------
//  POWERS

    template <typename T>
    constexpr square_t<T> operator^(const Vector3<T>& a,two_t) noexcept
    {
        return a.x*a.x + a.y*a.y + a.z*a.z;
    }    

//  --------------------------------------------------------
//  DOT PRODUCT

    template <typename T, typename U>
    constexpr product_t<T,U> operator DOT (const Vector3<T>& a, const Vector3<U>&b) noexcept
    {
        return a.x*b.x + a.y*b.y + a.z*b.z;
    }


//  --------------------------------------------------------
//  INNER PRODUCT

    template <typename T, typename U>
    constexpr product_t<T,U> operator INNER (const Vector3<T>& a, const Vector3<U>&b) noexcept
    {
        return a.x*b.x + a.y*b.y + a.z*b.z;
    }


//  --------------------------------------------------------
//  OUTER PRODUCT


//  --------------------------------------------------------
//  CROSS PRODUCT


    template <typename T, typename U>
    constexpr Vector3<product_t<T,U>> operator CROSS (const Vector3<T>& a, const Vector3<U>&b) noexcept
    {
        return { 
            a.y*b.z-a.z*b.y, 
            a.z*b.x-a.x*b.z, 
            a.x*b.y-a.y*b.x 
        };
    }

///  --------------------------------------------------------
//  OTIMES PRODUCT

//  --------------------------------------------------------
//  PROJECTIONS

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

    template <typename T>
    constexpr Vector3<T>   abs_elem(const Vector3<T>&a) noexcept
    {
        return a.eabs();
    }

    //! TRUE if every component of a is greater than b
    template <typename T>
    constexpr bool        all_greater(const Vector3<T>& a, const Vector3<T>&b) noexcept
    {
        return a.agreater(b);
    }

    //! TRUE if every component of a is greater or equal to b
    template <typename T>
    constexpr bool        all_greater_equal(const Vector3<T>& a, const Vector3<T>&b) noexcept
    {
        return a.agequal(b);
    }

    //! TRUE if every component of a is less than b
    template <typename T>
    constexpr bool        all_less(const Vector3<T>& a, const Vector3<T>&b) noexcept
    {
        return a.aless(b);
    }

    //! TRUE if every component of a is less than (or equal to) b
    template <typename T>
    constexpr bool        all_less_equal(const Vector3<T>& a, const Vector3<T>&b) noexcept
    {
        return a.alequal(b);
    }

    template <typename T>
    requires (std::is_floating_point_v<T> && trait::has_sqrt_v<T>)
    Radian              angle(const Vector3<T>&a, const Vector3<T>& b)
    {
        return acos( std::clamp<T>( (a*b)/(length(a)*length(b)), -one_v<T>, one_v<T>));
    }
    
    template <typename T, typename DIM1, typename DIM2>
    requires (std::is_floating_point_v<T> && trait::has_sqrt_v<T>)
    Radian             angle(const Vector3<MKS<T,DIM1>>&a, const Vector3<MKS<T,DIM2>>& b)
    {
        using one_t = MKS<T,dim::None>;
        return acos( std::clamp<one_t>( (a*b)/(length(a)*length(b)), -one_v<T>, one_v<T>));
    }

    /*! \brief Counter clockwise (euler) angle
    
        Computes the euler angle of the vector, ie, counter-clockwise from the +X axis.
    */
    template <typename T>
    requires std::is_floating_point_v<T>
    Radian   ccw(const Vector3<T>& a)
    {
        return atan(a.y, a.x);
    }

    /*! \brief Counter clockwise (euler) angle
    
        Computes the euler angle of the vector, ie, counter-clockwise from the +X axis.
    */
    template <typename T, typename DIM>
    requires std::is_floating_point_v<T>
    Radian   ccw(const Vector3<MKS<T,DIM>>& a)
    {
        return atan(a.y, a.x);
    }

    /*! \brief Clockwise angle
    
        Computes the angle of the vector from the +Y axis.
    */
    template <typename T>
    requires std::is_floating_point_v<T>
    MKS<T,dim::Angle>   clockwise(const Vector3<T>& a)
    {
        return atan(a.y, a.x);
    }

    /*! \brief Clockwise angle
    
        Computes the angle of the vector from the +Y axis.
    */
    template <typename T, typename DIM>
    requires std::is_floating_point_v<T>
    MKS<T,dim::Angle>   clockwise(const Vector3<MKS<T,DIM>>& a)
    {
        return atan(a.y, a.x);
    }

    template <typename T>
    constexpr T             component_max(const Vector3<T>&a) noexcept
    {
        return a.cmax();
    }

    template <typename T>
    constexpr T             component_min(const Vector3<T>&a) noexcept
    {
        return a.cmin();
    }

    template <typename T>
    constexpr cube_t<T>       component_product(const Vector3<T>& a) noexcept
    {
        return a.cproduct();
    }
    
    template <typename T>
    constexpr T   component_sum(const Vector3<T>& a) noexcept
    {
        return a.csum();
    }

    template <typename T, typename R>
    bool is_close(const R& compare, const Vector3<T>& actual, const Vector3<T>& expected)
    {
        return compare(length(actual-expected), length(expected));
    }
    
    template <typename T, typename R>
    bool is_close(const R& compare, const Vector3<T>& actual, std::type_identity_t<T> x, std::type_identity_t<T> y, std::type_identity_t<T> z)
    {
        return is_close(compare, actual, Vector3<T>{x, y, z} );
    }

    template <typename T>
    constexpr Vector3<T>   max_elem(const Vector3<T>&a, const Vector3<T>&b) noexcept
    {
        return a.emax(b);
    }

    template <typename T>
    constexpr Vector3<T>   min_elem(const Vector3<T>&a, const Vector3<T>&b) noexcept
    {
        return a.emin(b);
    }    

    /*! \brief Mid-way divide two vectors
    */
    template <typename T>
    constexpr T     midvector(const Vector3<T>& a, const Vector3<T>& b=Vector3<T>{}) noexcept
    {
        if constexpr (has_ieee754_v<T>)
            return ieee754_t<T>(0.5)*(a+b);
        else if constexpr (std::is_integral_v<T>)
            return (a+b) / T(2);
        else
            return {};
    }
}

YQ_TYPE_DECLARE(yq::Vector3D)
YQ_TYPE_DECLARE(yq::Vector3F)
YQ_TYPE_DECLARE(yq::Vector3I)
YQ_TYPE_DECLARE(yq::Vector3U)

