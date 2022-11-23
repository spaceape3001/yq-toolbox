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

//  --------------------------------------------------------
//  COMPOSITION

    template <typename T>
    Polygon2<T> polygon(const AxBox2<T>& ax)
    {
        return { { southwest(ax), southeast(ax), northeast(ax), northwest(ax) } };
    }

    YQ_IEEE754_1(Polygon2)
    YQ_ZERO_1(Polygon2, { })

//  --------------------------------------------------------
//  BASIC FUNCTIONS

    template <typename T>
    AxBox2<T>   aabb(const Polygon2<T>&poly)
    {
        if(poly.vertex.empty())
            return nan_v<AxBox2<T>>;
        AxBox2<T>   ret;
        ret.lo = ret.hi = poly.vertex.front();
        size_t n = poly.vertex.size();
        for(size_t i=1;i<n;++i){
            ret.lo = min_elem(ret.lo, poly.vertex[i]);
            ret.hi = max_elem(ret.hi, poly.vertex[i]);
        }
        return ret;
    }

    template <typename T>
    bool is_finite(const Polygon2<T>& poly)
    {
        for(auto& v : poly.vertex)
            if(!is_finite(v))
                return false;
        return true;
    }
    
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

    /*! \brief "Point area" of the points
    
        This is a helper to area and other functions, 
        simply does an "area" of the point deltas, 
        no sign correction, no scaling.
    */
    template <typename T>
    square_t<T>    point_area(const std::vector<Vector2<T>>& vertex)
    {
        if(vertex.empty())
            return square_t<T>{};
        
        auto cross = [&](size_t a, size_t b){
            auto& va = vertex[a];
            auto& vb = vertex[b];
            return (vb.x-va.x)*(vb.y-va.y);
        };
        
        size_t  n   = vertex.size();
        square_t<T> ret = delta_area(vertex[n-1],vertex[0]);
        --n;
        for(size_t i=0;i<n;++n)
            ret += delta_area(vertex[i], vertex[i+1]);
        return ret;
    }

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
    square_t<T>    area(const Polygon2<T>& poly)
    {
        return 0.5*abs(point_area(poly.vertex));
    }


    template <typename T>
    bool    is_ccw(const Polygon2<T>& poly)
    {
        return point_area(poly.vertex) < zero_v<T>;
    }


    template <typename T>
    bool    is_clockwise(const Polygon2<T>& poly)
    {
        return point_area(poly.vertex) > zero_v<T>;
    }
    

    template <typename T>
    requires has_sqrt_v<square_t<T>>
    T       perimeter(const Polygon2<T>& poly)
    {
        if(poly.vertex.empty())
            return T{};
        T   ret = length(poly.vertex.back()-poly.vertex.front());
        size_t n = poly.vertex.size() - 1;
        for(size_t i=0;i<n;++i)
            ret += length(poly.vertex[i+1]-poly.vertex[i]);
        return ret;
    }
    
}

YQ_TYPE_DECLARE(yq::Polygon2D)
YQ_TYPE_DECLARE(yq::Polygon2F)

