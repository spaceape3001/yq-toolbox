////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_POLYGON3_HPP 1

#include <math/preamble.hpp>
#include <math/vector/Vector3.hpp>

namespace yq {

    /*! \brief Structure for polygon data
    */
    template <typename T>
    struct Polygon3 {
        //! Capture the template parameter
        using component_type    = T;
        
        //! Vertex data
        std::vector<Vector3<T>>  vertex;
        
        //! Default constructor
        constexpr Polygon3() noexcept = default;

        //! Constructor by copy from vector
        Polygon3(const std::vector<Vector3<T>>&);

        //! Constructor by moving in from vector
        Polygon3(std::vector<Vector3<T>>&&);

        //! Constructor by copy from span
        Polygon3(std::span<const Vector3<T>>);

        //! Constructor by copy from initializer list
        Polygon3(std::initializer_list<Vector3<T>>);

        //! Constructor by copy from triangle
        explicit Polygon3(const Triangle3<T>&);

        //! Converts to polygon of compatible data type
        template <typename U>
        requires std::is_convertible_v<T,U>
        explicit operator Polygon3<U>() const;

        //! Defaulted equality operator
        constexpr bool operator==(const Polygon3&) const noexcept = default;
        
        //! Converts to polygon data
        operator PolygonData<Vector3<T>>() const;

        //! Addsa a point to the polygon
        Polygon3&   operator<<(const Vector3<T>& pt);

        //! Positive affirmation operator
        const Polygon3&    operator+() const;

        //! Negation operator
        Polygon3           operator-() const;
        
        //! Returns a shifted polygon by the given displacement
        Polygon3   operator+(const Vector3<T>&) const;

        //! Displaces this polygon by the given displacement
        Polygon3&  operator+=(const Vector3<T>&);
        
        //! Returns an shifted polygon by the given anti-displacement
        Polygon3   operator-(const Vector3<T>&) const;

        //! Displaces this polygon by the given anti displacement
        Polygon3&  operator-=(const Vector3<T>&);

        //! Returns a scaled polygon by the given right hand term
        template <typename U>
        requires is_arithmetic_v<U>
        Polygon3<product_t<T,U>> operator*(U) const;
        
        //! Scales this polygon by the given amount
        template <typename U>
        requires (is_arithmetic_v<U> && self_mul_v<T,U>)
        Polygon3& operator*=(U);


        //! Projects this polygon into two dimensions
        template <typename U>
        Polygon2<product_t<T,U>>   operator*(const Tensor32<U>&) const;

        //! Projects this polygon to another three dimension space
        template <typename U>
        Polygon3<product_t<T,U>>   operator*(const Tensor33<U>&) const;

        //! Projects this polygon into four dimensions
        template <typename U>
        Polygon4<product_t<T,U>>   operator*(const Tensor34<U>&) const;
        
        //! Self-projects this polygon
        template <typename U>
        requires self_mul_v<T,U>
        Polygon3&  operator*=(const Tensor33<U>&);

        //! Returns a polygon with every element divided by the given amount
        template <typename U>
        requires is_arithmetic_v<U>
        Polygon3<quotient_t<T,U>> operator/(U) const;
        
        //! Divides every element by the given amount
        template <typename U>
        requires (is_arithmetic_v<U> && self_div_v<T,U>)
        Polygon3& operator/=(U);

        
        /*! \brief Computes the axially aligned bounding box of this polygon
        */
        constexpr AxBox3<T>   bounds() const noexcept;
        
        //! Geometric center of the polygon (ie, average of the points)
        constexpr Vector3<T>    centroid() const noexcept;

        //! Computes the perimeter of the polygon (ie, sum of lengths of the segments)
        //! \note accuracy may vary on integral types
        T       perimeter() const;
        
        //! Walks the segments of this polygon
        template <typename Pred>
        void    segments(Pred) const;
        
        //! Converts the polygon to segments
        std::vector<Segment3<T>>    segments() const;
    };
    
//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Creates a polygon from points
    */
    template <typename T>
    Polygon3<T> polygon(std::vector<Vector3<T>>&& pts);

    /*! \brief Creates a polygon from points
    */
    template <typename T>
    Polygon3<T> polygon(std::span<const Vector3<T>> pts);

    /*! \brief Creates a polygon from points
    */
    template <typename T>
    Polygon3<T> polygon(std::initializer_list<const Vector3<T>> pts);

    /*! \brief Creates a polygon from a triangle
    */
    template <typename T>
    Polygon3<T> polygon(const Triangle3<T>& ax);

    YQ_IEEE754_1(Polygon3)
    YQ_INTEGER_1(Polygon3)
    YQ_IS_INTEGER_1(Polygon3)
    YQ_ZERO_1(Polygon3, { })

//  --------------------------------------------------------
//  BASIC FUNCTIONS

    /*! \brief Scales the right polygon by the left amount
    */
    template <typename T, typename U>
    requires is_arithmetic_v<T>
    Polygon3<product_t<T,U>> operator*(T, const Polygon3<U>&b);

    /*! \brief Create an axially aligned bounding box from a polygon
    */
    template <typename T>
    AxBox3<T>   aabb(const Polygon3<T>&poly);

    //! Computes the centroid of the given polygon
    template <typename T>
    Vector3<T>  centroid(const Polygon3<T>& poly);

    //! Tests that all vertices are finite
    template <typename T>
    bool is_finite(const Polygon3<T>& poly)
    {
        for(auto& v : poly.vertex)
            if(!is_finite(v))
                return false;
        return true;
    }
    
    //! Tests for any vertice that is not-a-number
    template <typename T>
    bool is_nan(const Polygon3<T>& poly)
    {
        for(auto& v : poly.vertex)
            if(is_nan(v))
                return true;
        return false;
    }

    //! Computes the perimeter of the polygon
    template <typename T>
    T       perimeter(const Polygon3<T>& poly);

}

YQ_TYPE_DECLARE(yq::Polygon3D)
YQ_TYPE_DECLARE(yq::Polygon3F)

