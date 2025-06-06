////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_POLYGON2_HPP 1

#include <yq/typedef/polygon2.hpp>

#include <yq/vector/Vector2.hpp>

#include <yq/keywords.hpp>
#include <yq/trait/product.hpp>
#include <yq/trait/quotient.hpp>
#include <yq/trait/self_divide.hpp>
#include <yq/trait/self_multiply.hpp>

namespace log4cpp { class CategoryStream; }

namespace yq {
    template <typename> struct Polygon3;
    template <typename> struct Polygon4;
    template <typename> struct PolygonData;
    template <typename> struct Tensor22;
    template <typename> struct Tensor23;
    template <typename> struct Tensor24;

    /*! \brief Structure for polygon data
    */
    template <typename T>
    struct Polygon2 {
        //! Capture the template parameter
        using component_type    = T;
        
        //! Vertex data
        std::vector<Vector2<T>>     vertex;
        
        //! Default constructor
        constexpr Polygon2() noexcept = default;
        
        //! Constructor by copy from vector
        Polygon2(const std::vector<Vector2<T>>&);

        //! Constructor by moving in from vector
        Polygon2(std::vector<Vector2<T>>&&);

        //! Constructor by copy from span
        Polygon2(std::span<const Vector2<T>>);

        //! Constructor by copy from initializer list
        Polygon2(std::initializer_list<Vector2<T>>);
        
        //! Constructor from axially aligned bounding box
        explicit Polygon2(const AxBox2<T>&);

        //! Constructor by quadrilateral
        explicit Polygon2(const Quadrilateral2<T>&);

        //! Constructor by copy from rectangle
        explicit Polygon2(const Rectangle2<T>&);

        //! Constructor by copy from triangle
        explicit Polygon2(const Triangle2<T>&);
        
        //! Converts to polygon of compatible data type
        template <typename U>
        requires std::is_convertible_v<T,U>
        explicit operator Polygon2<U>() const;

        //! Defaulted equality operator
        constexpr bool operator==(const Polygon2&) const noexcept = default;
        
        //! Converts to polygon data
        operator PolygonData<Vector2<T>>() const;

        //! Addsa a point to the polygon
        Polygon2&   operator<<(const Vector2<T>& pt);
        
        //! Positive affirmation operator
        const Polygon2&    operator+() const;
        
        //! Negation operator
        Polygon2           operator-() const;
        
        //! Returns a shifted polygon by the given displacement
        Polygon2   operator+(const Vector2<T>&) const;
        
        //! Displaces this polygon by the given displacement
        Polygon2&  operator+=(const Vector2<T>&);
        
        //! Returns an shifted polygon by the given anti-displacement
        Polygon2   operator-(const Vector2<T>&) const;

        //! Displaces this polygon by the given anti displacement
        Polygon2&  operator-=(const Vector2<T>&);

        //! Returns a scaled polygon by the given right hand term
        template <typename U>
        requires is_arithmetic_v<U>
        Polygon2<product_t<T,U>> operator*(U) const;
        
        //! Scales this polygon by the given amount
        template <typename U>
        requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
        Polygon2& operator*=(U);

        //! Projects this polygon to another two dimension space
        template <typename U>
        Polygon2<product_t<T,U>>   operator*(const Tensor22<U>&) const;
        
        //! Projects this polygon into three dimensions
        template <typename U>
        Polygon3<product_t<T,U>>   operator*(const Tensor23<U>&) const;
        
        //! Projects this polygon into four dimensions
        template <typename U>
        Polygon4<product_t<T,U>>   operator*(const Tensor24<U>&) const;
        
        //! Self-projects this polygon
        template <typename U>
        requires self_multiply_v<T,U>
        Polygon2&  operator*=(const Tensor22<U>&);
        
        
        //! Returns a polygon with every element divided by the given amount
        template <typename U>
        requires is_arithmetic_v<U>
        Polygon2<quotient_t<T,U>> operator/(U) const;
        
        //! Divides every element by the given amount
        template <typename U>
        requires (is_arithmetic_v<U> && self_divide_v<T,U>)
        Polygon2& operator/=(U);

        
        /*! \brief Computes the area of a 2D polygon
        */
        constexpr square_t<T>    area() const noexcept;

        //! Compute the bounding box to this polygon
        constexpr AxBox2<T>   bounds() const noexcept;

        //! Geometric center of the polygon (ie, average of the points)
        constexpr Vector2<T>    centroid() const noexcept;
        
        //! \brief Tests the polygon to determine if it's points are counter clockwise order
        constexpr bool    is_ccw() const noexcept;


        //! \brief Tests the polygon to determine if it's points are clockwise order
        constexpr bool    is_clockwise() const noexcept;
        
        //! Computes the perimeter of the polygon
        //! \note May be less accurate with non-floating point types
        T       perimeter() const;

        /*! \brief "Point area" of the points
        
            This is a helper to area and other functions, 
            simply does an "area" of the point deltas, 
            no sign correction, no scaling.
        */
        constexpr square_t<T>    point_area() const noexcept;

        //! Walks the segments of this polygon
        template <typename Pred>
        void    segments(Pred) const;
        
        //! Segments of this polygon
        std::vector<Segment2<T>>    segments() const;
        
        size_t  count() const { return vertex.size(); }
    };


//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Creates a polygon from a box
    */
    template <typename T>
    Polygon2<T> polygon(const AxBox2<T>& ax);

    /*! \brief Creates a polygon from points
    */
    template <typename T>
    Polygon2<T> polygon(std::vector<Vector2<T>>&& pts);

    /*! \brief Creates a polygon from points
    */
    template <typename T>
    Polygon2<T> polygon(std::span<const Vector2<T>> pts);

    /*! \brief Creates a polygon from points
    */
    template <typename T>
    Polygon2<T> polygon(std::initializer_list<const Vector2<T>> pts);

    /*! \brief Creates a polygon from a triangle
    */
    template <typename T>
    Polygon2<T> polygon(const Triangle2<T>& ax);

    YQ_IEEE754_1(Polygon2)
    YQ_INTEGER_1(Polygon2)
    YQ_IS_INTEGER_1(Polygon2)
    YQ_ZERO_1(Polygon2, Polygon2<T>())

//  --------------------------------------------------------
//  BASIC FUNCTIONS

    /*! \brief Create an axially aligned bounding box from a polygon
    */
    template <typename T>
    AxBox2<T>   aabb(const Polygon2<T>&poly);

    //! Tests that all vertices are finite
    template <typename T>
    bool is_finite(const Polygon2<T>& poly)
    {
        for(auto& v : poly.vertex)
            if(!is_finite(v))
                return false;
        return true;
    }
    
    //! Tests for any vertice that is not-a-number
    template <typename T>
    bool is_nan(const Polygon2<T>& poly)
    {
        for(auto& v : poly.vertex)
            if(is_nan(v))
                return true;
        return false;
    }

//  --------------------------------------------------------
//  UTILITY FUNCTIONS (FOR OTHER ADVANCED THINGS TO WORK)

        //  AREA HELPERS

//  --------------------------------------------------------
//  POSITIVE


//  --------------------------------------------------------
//  NEGATIVE


//  --------------------------------------------------------
//  NORMALIZATION


//  --------------------------------------------------------
//  ADDITION


//  --------------------------------------------------------
//  SUBTRACTION


//  --------------------------------------------------------
//  MULTIPLICATION

    /*! \brief Scales the right polygon by the left amount
    */
    template <typename T, typename U>
    requires is_arithmetic_v<T>
    Polygon2<product_t<T,U>> operator*(T, const Polygon2<U>&b);

//  --------------------------------------------------------
//  DIVISION

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
//  UNIONS

//  --------------------------------------------------------
//  INTERSECTIONS


//  --------------------------------------------------------
//  PROJECTIONS

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

    
    /*! \brief Computes the area of a 2D polygon
    */
    template <typename T>
    square_t<T>    area(const Polygon2<T>& poly);

    //! Computes the centroid of the given polygon
    template <typename T>
    Vector2<T>  centroid(const Polygon2<T>& poly);

    //! \brief Tests the polygon to determine if it's points are counter clockwise order
    template <typename T>
    bool    is_ccw(const Polygon2<T>& poly);

    //! \brief Tests the polygon to determine if it's points are clockwise order
    template <typename T>
    bool    is_clockwise(const Polygon2<T>& poly);
    
    //! Computes the perimeter of the polygon
    template <typename T>
    T       perimeter(const Polygon2<T>& poly);
    
}

YQ_TYPE_DECLARE(yq::Polygon2D)
YQ_TYPE_DECLARE(yq::Polygon2F)
YQ_TYPE_DECLARE(yq::Polygon2I)
YQ_TYPE_DECLARE(yq::Polygon2U)

