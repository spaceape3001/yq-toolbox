////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "PolygonData.hpp"
#include <math/preamble.hpp>
#include <math/AxBox3.hpp>
#include <math/Vector3.hpp>

namespace yq {

//  --------------------------------------------------------
//  COMPOSITION

    YQ_IEEE754_1(Polygon3)
    YQ_ZERO_1(Polygon3, { })

//  --------------------------------------------------------
//  BASIC FUNCTIONS

    template <typename T>
    bool is_finite(const Polygon3<T>& poly)
    {
        for(auto& v : poly.vertex)
            if(!is_finite(v))
                return false;
        return true;
    }
    
    template <typename T>
    bool is_nan(const Polygon3<T>& poly)
    {
        for(auto& v : poly.vertex)
            if(is_nan(v))
                return true;
        return false;
    }


    template <typename T>
    AxBox3<T>   aabb(const Polygon3<T>&poly)
    {
        if(poly.vertex.empty())
            return nan_v<AxBox2<T>>;
        AxBox3<T>   ret;
        ret.lo = ret.hi = poly.vertex.front();
        size_t n = poly.vertex.size();
        for(size_t i=1;i<n;++i){
            ret.lo = min_elem(ret.lo, poly.vertex[i]);
            ret.hi = max_elem(ret.hi, poly.vertex[i]);
        }
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

    template <typename T>
    requires trait::has_sqrt_v<square_t<T>>
    T       perimeter(const Polygon3<T>& poly)
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

YQ_TYPE_DECLARE(yq::Polygon3D)
YQ_TYPE_DECLARE(yq::Polygon3F)

