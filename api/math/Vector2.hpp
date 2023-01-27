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
#include <math/Units.hpp>
#include <math/trig.hpp>

namespace yq {

    /*! \brief Vector of 2 dimensions
    
        This is a 2 dimensional cartesian vector of the given type.
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Vector2 {
        //! Component data type argument to this structure (ie, template parameter T)
        using component_type = T;

        constexpr Vector2() noexcept = default;
        constexpr Vector2(T _x, T _y) noexcept : x(_x), y(_y) {}
        constexpr Vector2(T _x, T _y, ordered_t) noexcept : x(_x), y(_y) {}
        
        #if 0
        constexpr Vector2(const glm::vec<2, T, glm::defaultp>()& v) : x(v.x), y(v.y) {}
        #endif

        /*! \brief Creates a unit-vector in the x-dimension.
        */
        static consteval Vector2 unit_x() noexcept
        {
            return Vector2(one_v<T>,zero_v<T>);
        }
        
        /*! \brief Creates a unit-vector in the y-dimension.
        */
        static consteval Vector2 unit_y() noexcept
        {
            return Vector2(zero_v<T>,one_v<T>);
        }

        T       x;
        T       y;
        
        //! Equality operator (using default)
        constexpr bool operator==(const Vector2&) const noexcept = default;

        Vector2<quotient_t<T,T>> operator~() const
        {
            auto l = one_v<T>/length();
            return Vector2<quotient_t<T,T>>(x*l, y*l);
        }
        

        constexpr operator glm::vec<2, T, glm::defaultp>() const noexcept
        {
            return { x, y  };
        }

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
        constexpr Vector2 operator-() const noexcept
        {
            return Vector2(-x,-y);
        }

        constexpr Vector2 operator+(const Vector2& b) const noexcept
        {
            return Vector2(x+b.x, y+b.y);
        }
        
        Vector2& operator+=(const Vector2& b) noexcept
        {
            x += b.x;
            y += b.y;
            return *this;
        }

        constexpr Vector2 operator-(const Vector2& b) const noexcept
        {
            return Vector2(x-b.x, y-b.y);
        }

        Vector2& operator-=(const Vector2& b) noexcept
        {
            x -= b.x;
            y -= b.y;
            return *this;
        }


        //! TRUE if the second vector is CLOSE to this vector, as defined by the comparison operator
        template <typename R=Absolute>
        bool close(const Vector2&b, R compare) const 
        {
            return compare((*this-b).length(), b.length());
        }

        //! Returns the most positive component (as defined by the max function)
        constexpr T     cmax() const noexcept
        {
            return max(x, y);
        }

        //! Returns the most negative component (as defined by the min function)
        constexpr T     cmin() const noexcept
        {
            return min(x, y);
        }
    
        //! Returns the product of the components
        constexpr square_t<T>     cproduct() const noexcept
        {
            return x*y;
        }

        //! Returns the sum of the components
        constexpr T   csum() const noexcept
        {
            return x + y;
        }

        //! Element by element absolute value
        constexpr Vector2   eabs() const noexcept
        {
            return Vector2( abs(x), abs(y) );
        }

        //! Element by element division
        template <typename U>
        constexpr Vector2<quotient_t<T,U>>    ediv(const Vector2<U>&b) const noexcept
        {
            return Vector2<quotient_t<T,U>>(x/b.x, y/b.y);
        }

        //! Element by element maximum
        constexpr Vector2   emax(const Vector2&b) const noexcept
        {
            return Vector2(max(x, b.x), max(y, b.y));
        }

        //! Element by element minimum
        constexpr Vector2   emax(T b) const noexcept
        {
            return Vector2(max(x, b), max(y, b));
        }

        //! Element by element minimum
        constexpr Vector2   emin(const Vector2&b) const noexcept
        {
            return Vector2(min(x, b.x), min(y, b.y));
        }

        //! Element by element minimum
        constexpr Vector2   emin(T b) const noexcept
        {
            return Vector2(min(x, b), min(y, b));
        }

        //! Element by element multiplication
        template <typename U>
        constexpr Vector2<product_t<T,U>>    emul(const Vector2<U>&b) const noexcept
        {
            return Vector2<product_t<T,U>>(x*b.x, y*b.y);
        }

        /*! \brief Square of the vector's length
        
            This returns the SQUARE of this vector's length.
        */
        constexpr square_t<T> length²() const noexcept
        {
            return x*x + y*y;
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
        
        constexpr Vector3<T> z(T _z=T{}) const noexcept;

            //  ===================================================================================================
            //  AllComponents Adapters
            //  ===================================================================================================

        /*! Adds a value to all the components
        */
        constexpr Vector2 all_add(T b) const noexcept
        {
            return Vector2( x+b, y+b );
        }
        
        /*! \brief Subtracts value to all components
        */
        constexpr Vector2 all_subtract(T b) const noexcept
        {
            return Vector2( x-b, x-b );
        }

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
        return Vector2D((double) v, 0.);
    }

    constexpr Vector2D operator "" _x2(long double v) noexcept
    {
        return Vector2D((double) v, 0.);
    }

    constexpr Vector2D operator "" _y2(unsigned long long int v) noexcept
    {
        return Vector2D(0., (double) v);
    }

    constexpr Vector2D operator "" _y2(long double v) noexcept
    {
        return Vector2D(0., (double) v);
    }

    //! Creates a two dimension unit vector
    //!
    //! \param az   Counter-clockwise angle from +x
    inline Vector2D     ccw(Radian az)
    {
        return Vector2D(cos(az), sin(az) );
    }

    //! Creates a two dimension unit vector
    //!
    //! \param az    Clockwise angle from +y
    inline Vector2D     clockwise(Radian az)
    {
        return Vector2D( sin(az), cos(az) );
    }

    YQ_NAN_1(Vector2, Vector2<T>{nan_v<T>, nan_v<T>})
    YQ_ONE_1(Vector2, Vector2<T>{one_v<T>, one_v<T>})
    YQ_ZERO_1(Vector2, Vector2<T>{zero_v<T>, zero_v<T>})
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_NAN_1(Vector2, is_nan(v.x) || is_nan(v.y))
    YQ_IS_FINITE_1(Vector2, is_finite(v.x) && is_finite(v.y))
        

    /*! \brief Square of the vector's length
    
        This returns the SQUARE of the given vector's length.
    */
    template <typename T>
    constexpr square_t<T> length²(const Vector2<T>& vec) noexcept
    {
        return vec.length²();
    }    

    /*! \brief Length of the vector
        
        This returns the length of the given vector.
    */
    template <typename T>
    requires trait::has_sqrt_v<T>
    auto    length(const Vector2<T>& a)
    {
        return sqrt(length²(a));
    }



//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires (std::is_arithmetic_v<T>)
    constexpr Vector2<product_t<T,U>> operator*(T a, const Vector2<U>&b) noexcept
    {
        return Vector2<product_t<T,U>>(a*b.x, a*b.y);
    }

    template <typename T, typename U>
    requires (std::is_arithmetic_v<U>)
    constexpr Vector2<product_t<T,U>> operator*(const Vector2<T>& a, U b) noexcept
    {
        return Vector2<product_t<T,U>>(a.x*b, a.y*b);
    }


    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Vector2<T>& operator*=(Vector2<T>& a, U b) noexcept
    {
        a.x *= b;
        a.y *= b;
        return a;
    }
    
    template <typename T, typename U>
    constexpr Vector2<product_t<T,U>>    mul_elem(const Vector2<T>&a, const Vector2<U>&b) noexcept
    {
        return a.emul(b);
    }

//  --------------------------------------------------------
//  DIVISION

    template <typename T, typename U>
    requires (std::is_arithmetic_v<T>)
    constexpr  Vector2<quotient_t<T,U>> operator/(T a, const  Vector2<U>&b) noexcept
    {
        return (a*b) / b.length²();
    }


    template <typename T, typename U>
    requires (std::is_arithmetic_v<U>)
    constexpr  Vector2<quotient_t<T,U>> operator/(const  Vector2<T>& a, U b) noexcept
    {
        return Vector2<product_t<T,U>>(a.x / b, a.y / b);
    }

    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Vector2<T>& operator/=(Vector2<T>& a, U b) noexcept
    {
        a.x /= b;
        a.y /= b;
        return a;
    }

    template <typename T, typename U>
    constexpr Vector2<quotient_t<T,U>>    div_elem(const Vector2<T>&a, const Vector2<U>&b) noexcept
    {
        return a.ediv(b);
    }


//  --------------------------------------------------------
//  POWERS

    template <typename T>
    constexpr square_t<T> operator^(const Vector2<T>& a,two_t) noexcept
    {
        return a.x*a.x + a.y*a.y;
    }    

//  --------------------------------------------------------
//  DOT PRODUCT

    template <typename T, typename U>
    constexpr product_t<T,U> operator DOT (const Vector2<T>& a, const Vector2<U>&b) noexcept
    {
        return a.x*b.x + a.y*b.y;
    }


//  --------------------------------------------------------
//  INNER PRODUCT

    template <typename T, typename U>
    constexpr product_t<T,U> operator INNER (const Vector2<T>& a, const Vector2<U>&b) noexcept
    {
        return a.x*b.x + a.y*b.y;
    }

//  --------------------------------------------------------
//  OUTER PRODUCT


//  --------------------------------------------------------
//  CROSS PRODUCT

    template <typename T, typename U>
    constexpr product_t<T,U> operator CROSS (const Vector2<T>& a, const Vector2<U>&b) noexcept
    {
        return a.x*b.y-a.y*b.x;
    }



///  --------------------------------------------------------
//  OTIMES PRODUCT

//  --------------------------------------------------------
//  PROJECTIONS

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

    template <typename T>
    constexpr Vector2<T>   abs_elem(const Vector2<T>&a) noexcept
    {
        return a.eabs();
    }

    template <typename T>
    requires (std::is_floating_point_v<T> && trait::has_sqrt_v<T>)
    Radian       angle(const Vector2<T>&a, const Vector2<T>& b)
    {
        return acos( std::clamp<T>( (a*b)/(length(a)*length(b)), -one_v<T>, one_v<T>));
    }


    template <typename T, typename DIM1, typename DIM2>
    requires (std::is_floating_point_v<T> && trait::has_sqrt_v<T>)
    Radian      angle(const Vector2<MKS<T,DIM1>>&a, const Vector2<MKS<T,DIM2>>& b)
    {
        using one_t = MKS<T,dim::None>;
        return acos( std::clamp<one_t>( (a*b)/(length(a)*length(b)), -one_v<T>, one_v<T>));
    }

    /*! \brief Counter clockwise (euler) angle
    
        Computes the euler angle of the vector, ie, counter-clockwise from the +X axis.
    */
    template <typename T>
    requires std::is_floating_point_v<T>
    Radian   ccw(const Vector2<T>& a)
    {
        return atan(a.y, a.x);
    }

    /*! \brief Counter clockwise (euler) angle
    
        Computes the euler angle of the vector, ie, counter-clockwise from the +X axis.
    */
    template <typename T, typename DIM>
    requires std::is_floating_point_v<T>
    Radian   ccw(const Vector2<MKS<T,DIM>>& a)
    {
        return atan(a.y, a.x);
    }


    /*! \brief Clockwise angle
    
        Computes the angle of the vector from the +Y axis.
    */
    template <typename T>
    requires std::is_floating_point_v<T>
    MKS<T,dim::Angle>   clockwise(const Vector2<T>& a)
    {
        return atan(a.y, a.x);
    }

    /*! \brief Clockwise angle
    
        Computes the angle of the vector from the +Y axis.
    */
    template <typename T, typename DIM>
    requires std::is_floating_point_v<T>
    MKS<T,dim::Angle>   clockwise(const Vector2<MKS<T,DIM>>& a)
    {
        return atan(a.y, a.x);
    }

    template <typename T>
    constexpr T             component_max(const Vector2<T>&a) noexcept
    {
        return a.cmax();
    }

    template <typename T>
    constexpr T             component_min(const Vector2<T>&a) noexcept
    {
        return a.cmin();
    }

    template <typename T>
    constexpr square_t<T>     component_product(const Vector2<T>& a) noexcept
    {
        return a.cproduct();
    }

    template <typename T>
    constexpr T   component_sum(const Vector2<T>& a) noexcept
    {
        return a.csum();
    }

    /*! \brief "Delta Area"
    
        This is a building block for triangle & polygon area code, computes the "delta area" between two points
        (almost the same as area(aabb(a,b)) but can be negative.)
    */
    template <typename T>
    constexpr square_t<T>    delta_area(const Vector2<T>&a, const Vector2<T>& b) noexcept
    {
        return (b-a).cproduct();
    }

    /*! \brief "Point area" of the points
    
        This is a helper to area and other functions, 
        simply does an "area" of the point deltas, 
        no sign correction, no scaling.
    */
    template <typename T>
    square_t<T>    delta_area(const std::vector<Vector2<T>>& vertex)
    {
        if(vertex.empty())
            return square_t<T>{};

        size_t  n   = vertex.size();
        square_t<T> ret = delta_area(vertex[n-1],vertex[0]);
        --n;
        for(size_t i=0;i<n;++n)
            ret += delta_area(vertex[i], vertex[i+1]);
        return ret;
    }


    template <typename T, typename R>
    bool is_close(const R& compare, const Vector2<T>& actual, const Vector2<T>& expected)
    {
        return compare(length(actual-expected), length(expected));
    }

    template <typename T, typename R>
    bool is_close(const R& compare, const Vector2<T>& actual, std::type_identity_t<T> x, std::type_identity_t<T> y)
    {
        return is_close(compare, actual, Vector2<T>{x, y} );
    }

    template <typename T>
    constexpr Vector2<T>   max_elem(const Vector2<T>&a, const Vector2<T>&b) noexcept
    {
        return a.emax(b);
    }

    template <typename T>
    constexpr Vector2<T>   min_elem(const Vector2<T>&a, const Vector2<T>&b) noexcept
    {
        return a.emin(b);
    }

    /*! \brief Mid-way divide two vectors
    */
    template <typename T>
    constexpr Vector2<T>  midvector(const Vector2<T>& a, const Vector2<T>& b=Vector2<T>{}) noexcept
    {
        if constexpr (has_ieee754_v<T>)
            return ieee754_t<T>(0.5)*(a+b);
        else if constexpr (std::is_integral_v<T>)
            return (a+b) / T(2);
        else
            return {};
    }

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

