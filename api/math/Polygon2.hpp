////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>
#include <math/Vector2.hpp>

namespace yq {

    /*! \brief Structure for polygon data
    */
    template <typename T>
    struct Polygon2 {
        //! Capture the template parameter
        using component_type    = T;
        
        //! Vertex data
        std::vector<Vector2<T>>     vertex;
        
        constexpr Polygon2() noexcept = default;
        Polygon2(const std::vector<Vector2<T>>&);
        Polygon2(std::vector<Vector2<T>>&&);
        Polygon2(std::span<const Vector2<T>>);
        Polygon2(std::initializer_list<Vector2<T>>);
        
        explicit Polygon2(const AxBox2<T>&);
        explicit Polygon2(const Triangle2<T>&);
        
        
        //! Defaulted equality operator
        constexpr bool operator==(const Polygon2&) const noexcept = default;
        
        operator PolygonData<Vector2<T>>() const;

        //! Addsa a point to the polygon
        Polygon2&   operator<<(const Vector2<T>& pt);
        
        
        /*! \brief Computes the area of a 2D polygon
        */
        constexpr trait::square_t<T>    area() const noexcept;

        //! Compute the bounding box to this polygon
        constexpr AxBox2<T>   bounds() const noexcept;

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
        constexpr trait::square_t<T>    point_area() const noexcept;
    };


//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Creates a polygon from a box
    */
    template <typename T>
    Polygon2<T> polygon(const AxBox2<T>& ax);

    template <typename T>
    Polygon2<T> polygon(std::vector<Vector2<T>>&& pts);

    template <typename T>
    Polygon2<T> polygon(std::span<const Vector2<T>> pts);

    template <typename T>
    Polygon2<T> polygon(std::initializer_list<const Vector2<T>> pts);

    template <typename T>
    Polygon2<T> polygon(const Triangle2<T>& ax);

    YQ_IEEE754_1(Polygon2)
    YQ_ZERO_1(Polygon2, { })

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
    trait::square_t<T>    area(const Polygon2<T>& poly);

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

