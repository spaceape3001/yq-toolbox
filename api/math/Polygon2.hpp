////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "PolygonData.hpp"
#include <math/preamble.hpp>
#include <math/AxBox2.hpp>
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
        
        //! Defaulted equality operator
        constexpr bool operator==(const Polygon2&) const noexcept = default;
        
        operator PolygonData<Vector2<T>>() const 
        {
            return { vertex };
        }

        //! Addsa a point to the polygon
        Polygon2&   operator<<(const Vector2<T>& pt) 
        {
            vertex.push_back(pt);
            return *this;
        }
        
        
        /*! \brief Computes the area of a 2D polygon
        */
        trait::square_t<T>    area() const
        {
            return 0.5*abs(point_area());
        }

        //! Compute the bounding box to this polygon
        AxBox2<T>   bounds() const 
        {
            if(vertex.empty())
                return nan_v<AxBox2<T>>;
            AxBox2<T>   ret;
            ret.lo = ret.hi = vertex.front();
            size_t n = vertex.size();
            for(size_t i=1;i<n;++i)
                ret |= vertex[i];
            return ret;
        }

        //! \brief Tests the polygon to determine if it's points are counter clockwise order
        bool    is_ccw() const
        {
            return point_area() < zero_v<T>;
        }


        //! \brief Tests the polygon to determine if it's points are clockwise order
        bool    is_clockwise() const
        {
            return point_area() > zero_v<T>;
        }
        
        //! Computes the perimeter of the polygon
        //! \note May be less accurate with non-floating point types
        T       perimeter() const
        {
            if(vertex.empty())
                return T{};
            T   ret = (vertex.back()-vertex.front()).length();
            size_t n = vertex.size() - 1;
            for(size_t i=0;i<n;++i)
                ret += (vertex[i+1]-vertex[i]).length();
            return ret;
        }

        /*! \brief "Point area" of the points
        
            This is a helper to area and other functions, 
            simply does an "area" of the point deltas, 
            no sign correction, no scaling.
        */
        trait::square_t<T>    point_area() const
        {
            return delta_area(vertex);
        }
    };


//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Creates a polygon from a box
    */
    template <typename T>
    Polygon2<T> polygon(const AxBox2<T>& ax)
    {
        return { { southwest(ax), southeast(ax), northeast(ax), northwest(ax) } };
    }

    YQ_IEEE754_1(Polygon2)
    YQ_ZERO_1(Polygon2, { })

//  --------------------------------------------------------
//  BASIC FUNCTIONS

    /*! \brief Create an axially aligned bounding box from a polygon
    */
    template <typename T>
    AxBox2<T>   aabb(const Polygon2<T>&poly)
    {
        return poly.bounds();
    }

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
    trait::square_t<T>    area(const Polygon2<T>& poly)
    {
        return poly.area();
    }

    //! \brief Tests the polygon to determine if it's points are counter clockwise order
    template <typename T>
    bool    is_ccw(const Polygon2<T>& poly)
    {
        return poly.is_ccw();
    }


    //! \brief Tests the polygon to determine if it's points are clockwise order
    template <typename T>
    bool    is_clockwise(const Polygon2<T>& poly)
    {
        return poly.is_clockwise();
    }
    
    //! Computes the perimeter of the polygon
    template <typename T>
    T       perimeter(const Polygon2<T>& poly)
    {
        return poly.perimeter();
    }
    
}

YQ_TYPE_DECLARE(yq::Polygon2D)
YQ_TYPE_DECLARE(yq::Polygon2F)

