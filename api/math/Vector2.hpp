////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__VECTOR_2__HPP 1

#include <math/preamble.hpp>
#include <math/Absolute.hpp>
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

        /*! \brief Creates a unit-vector in the x-dimension.
        */
        static consteval Vector2 unit_x() noexcept;
        /*! \brief Creates a unit-vector in the y-dimension.
        */
        static consteval Vector2 unit_y() noexcept;

        T       x;
        T       y;;
        
        //! Equality operator (using default)
        constexpr bool operator==(const Vector2&) const noexcept = default;

        template <typename=void>
        requires trait::has_sqrt_v<T>
        Vector2<quotient_t<T,T>> operator~() const
        {
            auto l = one_v<T>/length();
            return {x/l, y/l};
        }
        

        constexpr operator glm::vec<2, T, glm::defaultp>() const noexcept
        {
            return { x, y  };
        }
        
        //! Affirmation (positive) operator
        constexpr Vector2<T> operator+() const noexcept
        {
            return *this;
        }

        //! Negation (negative) operator
        constexpr Vector2<T> operator-() const noexcept
        {
            return {-x,-y};
        }

        //! TRUE if every component of this vector is greater to b
        constexpr bool  agreat(const Vector2&b) const noexcept
        {
            return (x>b.x) && (y>b.y);
        }

        //! TRUE if every component of this vector is greater or equal to b
        constexpr bool  agequal(const Vector2&b) const noexcept
        {
            return (x>=b.x) && (y>=b.y);
        }

        //! TRUE if every component of this vector is less than b
        constexpr bool  aless(const Vector2&b) const noexcept
        {
            return (x<b.x) && (y<b.y);
        }

        //! TRUE if every component of a this vector is less than (or equal to) b
        constexpr bool  alequal(const Vector2&b) const noexcept
        {
            return (x<=b.x) && (y<=b.y);
        }
        
        //! TRUE if the second vector is CLOSE to this vector, as defined by the comparison operator
        template <typename R=Absolute>
        constexpr bool close(const Vector2&b, R compare) const 
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
            return { abs(x), abs(y) };
        }

        //! Element by element division
        template <typename U>
        constexpr Vector2<quotient_t<T,U>>    ediv(const Vector2&b) const noexcept
        {
            return {x/b.x, y/b.y};
        }

        //! Element by element maximum
        constexpr Vector2   emax(const Vector2&b) const noexcept
        {
            return {max(x, b.x), max(y, b.y)};
        }

        //! Element by element minimum
        constexpr Vector2   emax(T b) const noexcept
        {
            return {max(x, b), max(y, b)};
        }

        //! Element by element minimum
        constexpr Vector2   emin(const Vector2&b) const noexcept
        {
            return {min(x, b.x), min(y, b.y)};
        }

        //! Element by element minimum
        constexpr Vector2   emin(T b) const noexcept
        {
            return {min(x, b), min(y, b)};
        }

        //! Element by element multiplication
        template <typename U>
        constexpr Vector2<product_t<T,U>>    emul(const Vector2<U>&b) const noexcept
        {
            return {x*b.x, y*b.y};
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
            if constexpr (trait::has_sqrt_v<T>)
                return sqrt(length²());
            return {};
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
        return {x,y};
    }
    
    template <typename T, glm::qualifier Q>
    constexpr Vector2<T> vector(const glm::vec<2,T,Q>& v) noexcept
    {
        return { v.x, v.y };
    }


    template <typename T>
    consteval Vector2<T> Vector2<T>::unit_x() noexcept
    {
        return {one_v<T>,zero_v<T>};
    }

    template <typename T>
    consteval Vector2<T> Vector2<T>::unit_y() noexcept
    {
        return {zero_v<T>,one_v<T>};
    }

    constexpr Vector2D operator "" _x2(unsigned long long int v) noexcept
    {
        return {(double) v, 0.};
    }

    constexpr Vector2D operator "" _x2(long double v) noexcept
    {
        return {(double) v, 0.};
    }

    constexpr Vector2D operator "" _y2(unsigned long long int v) noexcept
    {
        return {0., (double) v};
    }

    constexpr Vector2D operator "" _y2(long double v) noexcept
    {
        return {0., (double) v};
    }

    //! Creates a two dimension unit vector
    //!
    //! \param az   Counter-clockwise angle from +x
    inline Vector2D     ccw(Radian az)
    {
        return { cos(az), sin(az) };
    }

    //! Creates a two dimension unit vector
    //!
    //! \param az    Clockwise angle from +y
    inline Vector2D     clockwise(Radian az)
    {
        return { sin(az), cos(az) };
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
//  NORMALIZATION


//  --------------------------------------------------------
//  ADDITION

    template <typename T>
    constexpr Vector2<T> operator+(const Vector2<T>& a, const Vector2<T>& b) noexcept
    {
        return {a.x+b.x, a.y+b.y};
    }
    
    template <typename T>
    Vector2<T>& operator+=(Vector2<T>& a, const Vector2<T>& b) noexcept
    {
        a.x += b.x;
        a.y += b.y;
        return a;
    }

//  --------------------------------------------------------
//  SUBTRACTION

    template <typename T>
    constexpr Vector2<T> operator-(const Vector2<T>& a, const Vector2<T>& b) noexcept
    {
        return {a.x-b.x, a.y-b.y};
    }

    template <typename T>
    Vector2<T>& operator-=(Vector2<T>& a, const Vector2<T>& b) noexcept
    {
        a.x -= b.x;
        a.y -= b.y;
        return a;
    }

//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires (std::is_arithmetic_v<T>)
    constexpr Vector2<product_t<T,U>> operator*(T a, const Vector2<U>&b) noexcept
    {
        return {a*b.x, a*b.y};
    }

    template <typename T, typename U>
    requires (std::is_arithmetic_v<U>)
    constexpr Vector2<product_t<T,U>> operator*(const Vector2<T>& a, U b) noexcept
    {
        return {a.x*b, a.y*b};
    }


    template <typename T, typename U>
    requires (std::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Vector2<T>& operator*=(Vector2<T>& a, T b) noexcept
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
        return (a*b) / length²(b);
    }


    template <typename T, typename U>
    requires (std::is_arithmetic_v<U>)
    constexpr  Vector2<quotient_t<T,U>> operator/(const  Vector2<T>& a, U b) noexcept
    {
        return {a.x / b, a.y / b};
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

    //! TRUE if every component of a is greater than b
    template <typename T>
    constexpr bool        all_greater(const Vector2<T>& a, const Vector2<T>&b) noexcept
    {
        return a.agreat(b);
    }

    //! TRUE if every component of a is greater or equal to b
    template <typename T>
    constexpr bool        all_greater_equal(const Vector2<T>& a, const Vector2<T>&b) noexcept
    {
        return a.agequal(b);
    }

    //! TRUE if every component of a is less than b
    template <typename T>
    constexpr bool        all_less(const Vector2<T>& a, const Vector2<T>&b) noexcept
    {
        return a.aless(b);
    }

    //! TRUE if every component of a is less than (or equal to) b
    template <typename T>
    constexpr bool        all_less_equal(const Vector2<T>& a, const Vector2<T>&b) noexcept
    {
        return a.alequal(b);
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
        return (b.x-a.x)*(b.y-a.y);
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


}

YQ_TYPE_DECLARE(yq::Vector2D)
YQ_TYPE_DECLARE(yq::Vector2F)
YQ_TYPE_DECLARE(yq::Vector2I)
YQ_TYPE_DECLARE(yq::Vector2U)

