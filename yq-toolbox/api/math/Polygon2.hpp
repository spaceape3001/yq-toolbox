////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "PolygonData.hpp"
#include <math/preamble.hpp>
#include <math/Vector2.hpp>

namespace yq {

    YQ_IEEE754_1(Polygon2)
    YQ_ZERO_1(Polygon2, { })

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
}

YQ_TYPE_DECLARE(yq::Polygon2D)
YQ_TYPE_DECLARE(yq::Polygon2F)

